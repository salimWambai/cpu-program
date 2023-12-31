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

    
    Process(const string& n, int p, int burst, int arrival)
        : name(n), priority(p), burst_time(burst), arrival_time(arrival), waiting_time(0), completed(false) {}
};
//scheduler funtion
class Scheduler{
    public:
    virtual void scheduleProcesses(vector<Process>& processes) = 0;
};
//FCFS
class FCFS : public Scheduler{
    public:
    void scheduleProcesses(vector<Process>& processes) {
        cout<<"FCFS Scheduling:\n";
        int current_time = 0;
        for(size_t i = 0; i < processes.size(); ++i){
           Process& process = processes[i];
           process.waiting_time = current_time - process.arrival_time;
            current_time += process.burst_time;
             process.completed = true;
            cout<<"Process Executing: "<<process.name<< "Waiting Time: " << process.waiting_time  << ")\n";
        }
        cout<<"\n";
    }
};
//SJF
class SJF : public Scheduler{
    public:
    void scheduleProcesses(const vector<Process>& processes){
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
            process.completed ;
            cout<<"Process Executing: " << process.name << "\n";
        }
        cout<<"\n";
    }
};

//RR scheduling
class RoundRobin : public Scheduler{
    public:
    void scheduleProcesses(vector<Process>& processes) {
        cout<<"RoundRobin:  \n";
        int timeQuantum;
        cout<<"Enter time quantum for Round Robin: ";
        cin>> timeQuantum;
        deque<Process> processQueue(processes.begin(), processes.end());
        while (!processQueue.empty()) {
            Process& process = processQueue.front();
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
    void scheduleProcesses(vector<Process>& processes) {
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
        cout<<"\n";
    }
};

//statistics function
void displayStats (const vector<Process>& processes){
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

    cout << "Select mode: \n";
    cout << "1. Pree,ptive : \n";
    cout << "2. Non-Preemptive: \n";
    cout << "Enter Number : \n";

    int modeChoice;
    cin >> modeChoice;
    vector<Process> processes;
    ifstream file("inout.txt");
    if (!file.is_open()){
        cerr<<"Error Opening file 'input.txt'. Please make sure the file is in the correct location. \n";
        return 1; 
    }
    //data read process from fle to store in vector process
    string name;
    int priority, burst_time, arrival_time;
    while (file >> name >> priority >> burst_time >> arrival_time){
        processes.push_back(Process(name, priority, burst_time, arrival_time));
    }

    Scheduler* scheduler = nullptr;
    //instance of selected scheduling algo

    switch (choice){
        case 1:
        scheduler = new FCFS();
        break;
        case 2:
        scheduler = new SJF();
        break;
        case 3:
        scheduler = new RoundRobin();
        break;
        case 4:
        scheduler = new PriorityAlgo();
        break;
        default:
        cerr << "Invalid Choice. Exiting...\n";
        return 1;
    
        }
        //selected scheduling algo
        scheduler->scheduleProcesses(processes);

        //stats dispaly
        displayStats(processes);

        //additional options
        cout << "Select Option:\n";
        cout << "1. Show Result\n";
        cout << "2. End Program\n";
        cout << "Enter the corresponding number: ";

        int option;
        cin >> option;

        if (option == 1) {
            displayStats(processes);

        } else if (option == 2 ) {
            ofstream outputFIle("output.txt");
            if (!outputFIle.is_open()){
                cerr << "Error opening file 'output.txt'.\n";
                return 1;
            }
            //to write in output file
            for (const Process& process : processes){
                outp << process.name << "\t" << process.waiting_time << "\n";

            }
            

            
        }

}
