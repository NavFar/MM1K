# Performance Evaluation of a M/M/1/K Queue System
This project trys to find the probebility of blocking and droping of requests in a simple M/M/1/K Queue system.

## Parts
this Project consists of two parts:
- Analytic Evaluation
- Simulation

## Output formats
the output of this program can take multiple lines but every line has the following format:
```
<Probability of block in fixed distribution>    <Probability of drop in fixed distribution>    <Probability of block in exponentioal distribution>    <Probability of drop in exponential distribution>
```

### Analytic Evaluation
This part tries to solve the problem by using an statistical approach. the `analytic.cpp` file is responsible for this section. it is possible to run this file and give the value of `lambda` as input.
Note: the value of `theta` and `mu` will be read from `parameters.conf` file.
simply run :
```
    make analytic
    ./analytic
```
and pass the `lambda` value.

### Simulation
for this section we used the object oriented approach,so there are multiple class that are created for this purpose;
- Job: which is the representation of task that are deliverd to system.
- server: which is the bundle of processing and queuing part of system.
- generator: which is the creator of load for the whole system(based on Fixed and exponential distribution)- 

simplye run:
```
make simulation
./simulation
```
and pass the `lambda` value.

## Multiple Run
there are targets in `Makefile` that will do multiple run of one or both of above programs.
- run : will run both of approaches for `lambda` value of 5 10 15.
- analytic-all-lambda: run the analytic part for every `lambda` values between 0.1 and 20 with 0.1 steps.
- simulation-all-lambda: run the simulation part for every `lambda` values between 0.1 and 20 with 0.1 steps.

## Licence
MIT

