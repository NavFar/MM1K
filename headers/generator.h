#include"job.h"
#include"distribution.h"
class Generator{
	private:
		float lambda;
		float theta;
	public:
		Generator(float, float);
		Job generateJob(Distribution);
		float generateJobInterval();
};
