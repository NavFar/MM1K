#ifndef DPS_RUNNER_H
#define DPS_RUNNER_H
#include<deque>
#include"job.h"
#include"server-runner.h"
class DPSRunner :public ServerRunner {
        public:
                int run(float duration, float mu, std::deque<Job>& queue);
};

#endif
