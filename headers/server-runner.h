#ifndef SERVER_RUNNER_H
#define SERVER_RUNNER_H
#include<deque>
#include"job.h"
class ServerRunner {
	public:
		virtual void run(float duration,std::deque<Job> &queue)=0;
};
#endif
