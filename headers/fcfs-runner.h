#ifndef FCFS_RUNNER_H
#define FCFS_RUNNER_H
#include<deque>
#include"job.h"
#include"server-runner.h"
class FCFSRunner :public ServerRunner {
	public:
		int run(float duration, std::deque<Job>& queue);
};
#endif
