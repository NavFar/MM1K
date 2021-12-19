#ifndef PS_RUNNER_H
#define PS_RUNNER_H
#include<deque>
#include"job.h"
#include"server-runner.h"
class PSRunner :public ServerRunner {
        public:
                int run(float duration, float mu, std::deque<Job>& queue);
};

#endif
