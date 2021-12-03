class Job {
	private:
		float load;
		float due;
	public:
		Job(float,float);
		float getLoad();
		void setLoad(float);
		float getDue();
		void setDue(float);
}; 
