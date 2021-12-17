#ifndef SERVER_RUNNER_H
#define SERVER_RUNNER_H
#include<deque.h>
class ServerRunner {
	public:
		virtual void run(deque& queue)=0;
};
#endif
