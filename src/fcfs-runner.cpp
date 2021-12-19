#include"fcfs-runner.h"
#include"job.h"
#include<deque>

int FCFSRunner::run(float duration, float mu,std::deque<Job>& queue){
	int droped = 0;
	while(duration>0 && queue.size()>0){
		float passedTime=duration;
		bool frontDone=false;
		duration = duration - queue.front().getLoad();
		if(duration>=0){
			passedTime=queue.front().getLoad();
			frontDone=true;
		}
		else {
			queue.front().setLoad(-1*duration);
		}
		std::deque<Job>::iterator it = queue.begin()+1;
		while(it< queue.end()){
			it->decreaseDue(passedTime/mu);
			if(it->getDue()<=0){
				droped++;
				it= queue.erase(it);
			}
			else
				it++;
		}
		if(frontDone){

			queue.pop_front();
		}

	}
	return droped;

}
