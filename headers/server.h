#ifndef SERVER_H
#define SERVER_H
#include<deque>
#include"job.h"
#include"server-runner.h"
class Server {
	private:
	std::deque<Job> queue;
	float mu;
	int maxSize;
	ServerRunner * runner;
	public:
	Server(float,int,ServerRunner*);
	~Server();
	bool addJob(Job);
	std::deque<Job> run(float);
};
#endif
