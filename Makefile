all: simulation analytic
run: simulation analytic
	echo -e "Analytic">results.txt;\
	for i in `seq 5 5 15`; do\
		echo $$i| ./analytic >>results.txt;\
	done;\
	echo -e "Simulation">>results.txt;\
	for i in `seq 5 5 15`; do\
		echo $$i| ./simulation >>results.txt;\
	done;
analytic-all-lambda: analytic
	for i in `seq 0.1 0.1 20`; do\
		echo  $$i | ./analytic;  \
	done
simulation-all-lambda:simulation
	for i in `seq 0.1 0.1 20`; do\
		echo $$i | ./simulation;	\
	done
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
	rm -rf *.out *.o analytic simulation results.txt
