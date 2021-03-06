#include"ps-runner.h"
#include"job.h"
#include<deque>
#include<vector>
#include<algorithm>
std::deque<Job> PSRunner::run(float duration, float mu, std::deque<Job>& queue){
	std::deque<Job> dropped;
	std::sort(queue.begin(),queue.end(),[](Job first, Job second){return first.getLoad()< second.getLoad();});
	std::deque<Job>:: iterator it = queue.begin();
	std::vector<float> mileStones;
	mileStones.push_back(duration);
	while(it < queue.end()){
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
		float share = *mileStonesIt * mu / (float)queue.size();
		it= queue.begin();
		while(it < queue.end()){
			if(it->getLoad()<= share){
				share+= (share-it->getLoad())/ (queue.size() -1);
				it = queue.erase(it);
				continue;
			}
			it->decreaseDue(*mileStonesIt);
			if(it->getDue()<0){
				dropped.push_back(*it);
				it=queue.erase(it);
			}
			else{
				it->setLoad(it->getLoad()-share);
				it++;
			}
		
		}
		mileStonesIt++;
	}


	return dropped;
}


