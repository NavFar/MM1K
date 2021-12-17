#ifndef FCFS_SERVER_H
#define FCFS_SERVER_H
#include<deque.h>
#include"server-runner.h"
class FCFSServer :public ServerRunner {
	public:
		void run(float duration, std::deque& queue);
};
#endif
