SRCDIR=src/
BINDIR=bin/
BUILDDIR=build/
CC=g++

all: simulation analytic
run: simulation analytic
	echo -e "Analytic">results.txt;\
	for i in `seq 5 5 15`; do\
		echo $$i| $(BINDIR)/analytic >>results.txt;\
	done;\
	echo -e "Simulation">>results.txt;\
	for i in `seq 5 5 15`; do\
		echo $$i| $(BINDIR)/simulation >>results.txt;\
	done;
analytic-all-lambda: analytic
	for i in `seq 0.1 0.1 20`; do\
		echo  $$i | $(BINDIR)/analytic;  \
	done
simulation-all-lambda:simulation
	for i in `seq 0.1 0.1 20`; do\
		echo $$i | $(BINDIR)/simulation;	\
	done
job.o: $(SRCDIR)job.cpp
	$(CC) -c -o $(BUILDDIR)job.o $(SRCDIR)job.cpp
generator.o: $(SRCDIR)generator.cpp 
	$(CC) -c -o $(BUILDDIR)generator.o  $(SRCDIR)generator.cpp
server.o: $(SRCDIR)server.cpp  
	$(CC) -c -o $(BUILDDIR)server.o $(SRCDIR)server.cpp 
simulation: server.o generator.o job.o $(SRCDIR)simulation.cpp
	$(CC) -o $(BINDIR)simulation $(BUILDDIR)server.o $(BUILDDIR)generator.o $(BUILDDIR)job.o $(SRCDIR)simulation.cpp
analytic: $(SRCDIR)analytic.cpp
	$(CC) -o $(BINDIR)analytic $(SRCDIR)analytic.cpp  
clean:
	rm -rf $(BINDIR)* $(BUILDDIR)*
