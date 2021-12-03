#ifndef SERVER_H
#define SERVER_H
#include<deque>
#include"job.h"

class Server {
	private:
	std::deque<Job> queue;
	float mu;
	int maxSize;
	public:
	Server(float,int);
	bool addJob(Job);
	int run(float);
}
#endif
