all: simulation analytic
job.o: job.cpp
	g++ -c -o job.o job.cpp
generator.o: generator.cpp 
	g++ -c -o generator.o  generator.cpp
server.o: server.cpp  
	g++ -c -o server.o server.cpp 
simulation: server.o generator.o job.o simulation.cpp
	g++ -o simulation server.o generator.o job.o simulation.cpp
analytic:
	g++ -o analytic analytic.cpp  
clean:
	rm -rf *.out *.o analytic simulation
