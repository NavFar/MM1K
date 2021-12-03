#ifndef JOB_H
#define JOB_H
class Job {
	private:
		float load;
		float due;
	public:
		Job(float,float);
		void decreaseDue(float);
		float getLoad();
		void setLoad(float);
		float getDue();
		void setDue(float);
}; 
#endif
