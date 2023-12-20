#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <deque>
#include <string>
#include <iomanip>

//process class
class Process {
public:
    std::string name;
    int priority;
    int burst_time;
    int arrival_time;
    int waiting_time;
    double completed;

    
    Process(const std::string& n, int p, int burst, int arrival)
        : name(n), priority(p), burst_time(burst), arrival_time(arrival), waiting_time(0), completed(false) {}
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
//SJF
class SJF : public Scheduler{
    public:
    void scheduleProcesses(const std::vector<Process>& processes){
        std::cout<<"SJF Scheduling :\n";
        std::vector<Process> sortedProcessess = processes;
        std::sort(sortedProcessess.begin(), sortedProcessess.end(), CompareBustTime());
        for (size_t i = 0; i < sortedProcessess.size(); ++i){
            const Process& Process = sortedProcessess[i];
            std::cout<<"Process Executing: " << Process.name << "\n";
        }
        std::cout<<"\n";
    }
};

private:{
    struct CompareBurstTime {
        bool operator()(const Task& a, const Task& b) const {
            return a.burstTime < b.burstTime;
        }
    };

};