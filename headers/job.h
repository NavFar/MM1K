#include"job-type.h"
#ifndef JOB_H
#define JOB_H
class Job {
	private:
		JobType type;
		float load;
		float due;
	public:
		Job(float,float,JobType);
		void decreaseDue(float);
		float getLoad();
		void setLoad(float);
		float getDue();
		void setDue(float);
		JobType getType();
		void setType(JobType);
}; 
#endif
