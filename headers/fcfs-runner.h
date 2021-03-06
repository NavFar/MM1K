#ifndef FCFS_RUNNER_H
#define FCFS_RUNNER_H
#include<deque>
#include"job.h"
#include"server-runner.h"
class FCFSRunner :public ServerRunner {
	public:
		std::deque<Job> run(float duration,float mu,std::deque<Job>& queue);
};
#endif
