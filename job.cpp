#include"headers/job.h"
#include<iostream>
Job::Job(float load, float due){
	this->load = load;
	this->due = due;
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
