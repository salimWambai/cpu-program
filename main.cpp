#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <deque>
#include <string>
#include <iomanip>

//process class
class Process{
public:
    std::string name;
    int priority;
    int burstTime;
    int arrivalTime;
    int waitingTime;
    double completed;

    Process(const std: string& n, int p, int burst, int arrival)
    : name(n), priority(p), burstTime(burst), arrivalTime(arrival), waitingTime(0),completed(false) {}
};
//scheduler funtion
class Scheduler{
    public:
    virtual void scheduleProcesses(std::vector<Process>& processes) = 0;
};
//FCFS
class FCFS : public Scheduler{
    public:
    void scheduleProcesses(const std::vector<Process>& processes){
        std::cout<<"FCFS Scheduling:\n";
        for(size_t i = 0; i < processes.size(); ++i){
            const Process& Process = processes[i];
            std::cout<<"Process Executing: "<<Process.name<<"\n";
        }
        std::cout<<"\n";
    }
};
