#include"job.h"
#include"job-type.h"
#include<iostream>
Job::Job(float load, float due, JobType type){
	this->load = load;
	this->due = due;
	this->type = type;
}
void Job::decreaseDue(float duration){
	this->due = this->due- duration;
}
float Job::getLoad(){
	return this->load;
}
void Job::setLoad(float load){
	this->load = load;
}
float Job::getDue(){
	return this->due;
}
void Job::setDue(float due){
	this->due = due;
}
JobType Job::getType(){
	return this->type;
}
void Job::setType(JobType type){
	this->type = type;
}
