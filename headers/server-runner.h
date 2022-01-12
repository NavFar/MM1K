#ifndef SERVER_RUNNER_H
#define SERVER_RUNNER_H
#include<deque>
#include"job.h"
class ServerRunner {
	public:
		virtual std::deque<Job> run(float duration, float mu, std::deque<Job> &queue)=0;
};
#endif
