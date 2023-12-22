#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <deque>
#include <string>
#include <iomanip>
using namespace std;

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
        cout<<"FCFS Scheduling:\n";
        int current_time = 0;
        for(size_t i = 0; i < processes.size(); ++i){
           const Process& process =processes[i];
            process.waiting_time = current_time - process.arrival_time;
            current_time += process.burst_time;
            Process.completed = true;
            cout<<"Process Executing: "<<process.name<< "Waiting Time: " << process.waiting_time  << ")\n";
        }
        cout<<"\n";
    }
};
//SJF
class SJF : public Scheduler{
    public:
    void scheduleProcesses(const std::vector<Process>& processes){
        cout<<"SJF Scheduling :\n";
        vector<Process> sortedProcessess = processes;
        sort(sortedProcessess.begin(), sortedProcessess.end(), [](const Process& a, const Process& b) {
            return a.burst_time < b.burst_time;
        });
        int current_time = 0;
        for (size_t i = 0; i < sortedProcessess.size(); ++i){
            Process& process = sortedProcessess[i];
            process.waiting_time = current_time - process.arrival_time;
            current_time += process.burst_time;
            process.completed = true;
            cout<<"Process Executing: " << process.name << "\n";
        }
        cout<<"\n";
    }
};

//RR scheduling
class RoundRobin : public Scheduler{
    public:
    void scheduleProcesses(const std::vector<Process>& processess){
        cout<<"RoundRobin:  \n";
        int timeQuantum;
        cout<<"Enter time quantum for Round Robin: ";
        cin>> timeQuantum;
        deque<Process> processQueue (Process.begin(), Process.end());
        while (!processQueue.empty()) {
            Process process = processQueue.front();
            processQueue.pop_front();
            if (process.burst_time > timeQuantum) {
                process.burst_time -= timeQuantum;
                processQueue.push_back(process);
            }
            else{
                process.waiting_time += processQueue.size() * timeQuantum;
                process.completed = true;
                cout<<"Process Executing: "<< process.name<< "Waiting TIme: " <<process.waiting_time <<  "\n";
            }
        }
        cout<<"\n";

    }
};
//Priority scheduling
class PriorityAlgo : public Scheduler {
    public:
    void scheduleProcesses(std::vector<Process>& processes) {
        cout<<"Priority Scheduling: \n";
        sort(processes.begin(), processes.end(), [](const Process& a, const Process& b){
            return a.priority > b.priority;
        });
        int current_time = 0;
        for (size_t i = 0; i <processes.size(); ++i){
            Process& process = processes[i];
            process.waiting_time = current_time - process.arrival_time;
            current_time += process.burst_time;
            process.completed = true;
            cout << "Process Executing " << process.name << " (Waiting Time: " << process.waiting_time << ")\n"; 
        }
        cout<<"\n;"
    }
};

//statistics function
void displayStats (const std::vector<Process>& processes){
    cout << "Process\tWaiting Time\n";
    for(const Process& process : processes){
        cout << process.name << "\t" << process.waiting_time << "\n";

    }
    //average WT
    double average_waiting_time = 0;
    for(const Process& process : processes){
        average_waiting_time += process.waiting_time;
    }
    average_waiting_time /= processes.size();
    cout << "\nAverage Waiting Time: " << fixed << setprecision(2) << average_waiting_time << "\n";

}
//user main function UI
int main (){
    cout << "Select Scheduling Method: \n";
    cout << "1. FCFS\n";
    cout << "2. SJF\n";
    cout << "3. Round Robin\n";
    cout << "4. Priority Scheduling\n";
    cout << "Choose a Number: ";

    int choice;
    cin>> choice;
    
}