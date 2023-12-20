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
    void scheduleProcesses(const std::vector<Process>& processes) {
        std::cout<<"FCFS Scheduling:\n";
        int current_time=0;
        for(size_t i = 0; i < processes.size(); ++i){
          const  Process& process =processes[i];
            Process.waiting_time = current_time - process.arrival_time;
            current_time += process.burst_time;
            Process.completed = true;
            std::cout<<"Process Executing: "<<process.name<< "Waiting Time: " << process.waiting_time  << ")\n";
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
        std::sort(sortedProcessess.begin(), sortedProcessess.end(), [](const Process& a, const Process& b) {
            return a.burst_time < b.burst_time;
        });
        int current_time = 0;
        for (size_t i = 0; i < sortedProcessess.size(); ++i){
            Process& process = sortedProcessess[i];
            process.waiting_time = current_time - process.arrival_time;
            current_time += process.burst_time;
            process.completed = true;
            std::cout<<"Process Executing: " << process.name << "\n";
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