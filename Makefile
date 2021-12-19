SRCDIR=src/
BINDIR=bin/
BUILDDIR=build/
CC=g++
FLAGS=-I ./headers
all: simulation analytic
run: run-PS
run-%: simulation analytic
	echo -e "Analytic">results.txt;\
	for i in `seq 5 5 15`; do\
		echo $* $$i| $(BINDIR)/analytic >>results.txt;\
	done;\
	echo -e "Simulation">>results.txt;\
	for i in `seq 5 5 15`; do\
		echo $* $$i| $(BINDIR)/simulation >>results.txt;\
	done;
analytic-all-lambda-%: analytic
	for i in `seq 0.1 0.1 20`; do\
		echo $*  $$i | $(BINDIR)/analytic;  \
	done
simulation-all-lambda-%:simulation
	for i in `seq 0.1 0.1 20`; do\
		echo $* $$i | $(BINDIR)/simulation;	\
	done
%.o: $(SRCDIR)%.cpp  
	$(CC) $(FLAGS) -c -o $(BUILDDIR)$@ $< 
simulation: $(SRCDIR)simulation.cpp   generator.o job.o fcfs-runner.o ps-runner.o server.o  
	$(CC) $(FLAGS) -o $(BINDIR)$@ $< $(BUILDDIR)generator.o $(BUILDDIR)job.o $(BUILDDIR)fcfs-runner.o $(BUILDDIR)ps-runner.o  $(BUILDDIR)server.o  
analytic: $(SRCDIR)analytic.cpp
	$(CC) $(FLAGS) -o $(BINDIR)analytic $(SRCDIR)analytic.cpp  
clean:
	rm -rf $(BINDIR)* $(BUILDDIR)*
