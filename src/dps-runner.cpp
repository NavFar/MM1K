#include"dps-runner.h"
#include"job-type.h"
#include"job.h"
#include<deque>
#include<vector>
#include<algorithm>
#include<iostream>
std::deque<Job> DPSRunner::run(float duration, float mu, std::deque<Job>& queue){
	std::deque<Job> dropped;
	std::deque<Job>:: iterator it = queue.begin();
	std::vector<float> mileStones;
	mileStones.push_back(duration);
	int numberOfUrgentJob=0;
	while(it < queue.end()){
		if(it->getType()==JobType::Urgent)
			numberOfUrgentJob++;
		if(it->getDue()<=duration)
			mileStones.push_back(it->getDue());
		it++;
	}
	std::vector<float>::iterator mileStonesIt;
	mileStonesIt = std::unique(mileStones.begin(),mileStones.end());
	mileStones.resize(std::distance(mileStones.begin(),mileStonesIt));
	std::sort(mileStones.begin(),mileStones.end());

	float reference = 0;
	mileStonesIt = mileStones.begin();

	while(mileStonesIt<mileStones.end()){
		*mileStonesIt -= reference;
		reference += *mileStonesIt;
		float totalShare= *mileStonesIt * mu / queue.size();
		float share = 0;
		it= queue.begin();
		float urgentShare = *mileStonesIt * mu *0.6666 / numberOfUrgentJob ;
		float normalShare = *mileStonesIt * mu *0.3333 / (queue.size() - numberOfUrgentJob);
		while(it < queue.end()){
			if(numberOfUrgentJob==queue.size()){
				urgentShare = *mileStonesIt * mu / numberOfUrgentJob ;
				normalShare = 0;
			}
			if(numberOfUrgentJob==0){
				normalShare = *mileStonesIt * mu  / queue.size() ;
				urgentShare = 0;

			}
			if(it->getType()==JobType::Urgent)
				share = urgentShare;
			if(it->getType()==JobType::Normal)
				share = normalShare;
			if(it->getLoad()<= share){
				if(it->getType()==JobType::Urgent){
					if(numberOfUrgentJob>1)
						urgentShare+=(share-it->getLoad())/ (numberOfUrgentJob -1);
					numberOfUrgentJob--;
				}
				if(it->getType()==JobType::Normal){

					if(queue.size() - numberOfUrgentJob>1)
						normalShare+=(share-it->getLoad())/ (queue.size() - numberOfUrgentJob -1);
				}

				it = queue.erase(it);
			}else{
				it->decreaseDue(*mileStonesIt);
				if(it->getDue()<=0){
					if(it->getType()==JobType::Urgent)
						numberOfUrgentJob--;
					dropped.push_back(*it);
					it=queue.erase(it);
				}
				else{
					it->setLoad(it->getLoad()-share);
					it++;
				}
			}
		}
		mileStonesIt++;
	}


	return dropped;
}


