#include <iostream>
#include <fstream>
#include <algorithm>
#include <memory>
#include <deque>
#include <string>
#include <iomanip>
#include <unistd.h>
#include <list>
using namespace std;
void displayUsage();
//process class
class Process {
public:
    std::string name;
    int priority;
    int burst_time;
    int arrival_time;
    int waiting_time;
    bool completed;

    
    Process(const string& n, int p, int burst, int arrival)
        : name(n), priority(p), burst_time(burst), arrival_time(arrival), waiting_time(0), completed(false) {}
};
//scheduler funtion
class Scheduler{
    public:
    virtual void scheduleProcesses(list<Process>& processes) = 0;
};
//FCFS
 
class FCFS : public Scheduler {
public:
    void scheduleProcesses(list<Process>& processes) {
        cout << "FCFS Scheduling:\n";
        int current_time = 0;
        for (auto& process : processes) {
            process.waiting_time = current_time - process.arrival_time;
            current_time += process.burst_time;
            process.completed = true;
            cout << "Process Executing: " << process.name << " (Waiting Time: " << process.waiting_time << ")\n";
        }

        double average_waiting_time_fcfs = 0;
        for (const Process& process : processes) {
            average_waiting_time_fcfs += process.waiting_time;
        }
        average_waiting_time_fcfs /= processes.size();
        cout << "Average Waiting Time (FCFS): " << fixed << setprecision(2) << average_waiting_time_fcfs << "\n";
    }
};

 // SJF class

class SJF : public Scheduler {
public:
    void scheduleProcesses(list<Process>& processes) override {
        cout << "SJF Scheduling:\n";

        processes.sort([](const Process& a, const Process& b) {
            if (a.burst_time != b.burst_time) {
                return a.burst_time < b.burst_time;
            } else {
                return a.arrival_time < b.arrival_time;
            }
        });

        int current_time = 0;
        double total_waiting_time_sjf = 0;

        for (auto& process : processes) {
            process.waiting_time += current_time - process.arrival_time;
            current_time += process.burst_time;
            total_waiting_time_sjf += process.waiting_time;
            process.completed = true;
            cout << "Process Executing: " << process.name << " (Waiting Time: " << process.waiting_time << ")\n";
        }

        double average_waiting_time_sjf = total_waiting_time_sjf / processes.size();
        cout << "\nAverage Waiting Time (SJF): " << fixed << setprecision(2) << average_waiting_time_sjf << "\n";
    }

    // Function to calculate SJF averages
    void calculateSJFAverages(list<Process>& processes) {
        double average_waiting_time_sjf = 0;
        int accumulated_waiting_time = 0;
        for (auto& process : processes) {
            process.waiting_time = accumulated_waiting_time;
            accumulated_waiting_time += process.burst_time;
            average_waiting_time_sjf += process.waiting_time;
        }
    }
};

 

//  RoundRobin class
class RoundRobin : public Scheduler {
public:
    void scheduleProcesses(list<Process>& processes) override {
        cout << "RoundRobin:  \n";
        int timeQuantum;
        cout << "Enter time quantum for Round Robin: ";
        cin >> timeQuantum;
        deque<Process> processQueue(processes.begin(), processes.end());

        double average_waiting_time_rr = 0;  // Declare the variable here

        while (!processQueue.empty()) {
            Process& process = processQueue.front();
            processQueue.pop_front();
            if (process.burst_time > timeQuantum) {
                process.burst_time -= timeQuantum;
                processQueue.push_back(process);
            } else {
                process.waiting_time += (processQueue.size() - 1) * timeQuantum;
                process.completed = true;
                cout << "Process Executing: " << process.name << " (Waiting Time: " << process.waiting_time << ")\n";
            }
        }

        // double total_waiting_time_rr = 0;

        for (const Process& process : processes) {
            average_waiting_time_rr += process.waiting_time;
        }
        average_waiting_time_rr /= processes.size();
        cout << "Average Waiting Time (Round Robin): " << fixed << setprecision(2) << average_waiting_time_rr << "\n";
    }
};


//   PriorityAlgo class
class PriorityAlgo : public Scheduler {
public:
    void scheduleProcesses(list<Process>& processes) {
        cout << "Priority Scheduling: \n";
        processes.sort([](const Process& a, const Process& b) {
            return a.priority > b.priority;
        });
        int current_time = 0;
        for (auto& process : processes) {
            process.waiting_time = current_time - process.arrival_time;
            current_time += process.burst_time;
            process.completed = true;
            cout << "Process Executing " << process.name << " (Waiting Time: " << process.waiting_time << ")\n";
        }

        double average_waiting_time_priority = 0;
        for (const Process& process : processes) {
            average_waiting_time_priority += process.waiting_time;
        }
        average_waiting_time_priority /= processes.size();
        cout << "Average Waiting Time (Priority Scheduling): " << fixed << setprecision(2) << average_waiting_time_priority << "\n";
    }
};


//statistics function
void displayStats(const list<Process>& processes, const string& schedulingMethod) {
    cout << "Scheduling Method: " << schedulingMethod << "\n";
    cout << "Process Waiting Times:\n";

    // Display process names and waiting times vertically
    for (const Process& process : processes) {
        cout << process.name << ":\t" << process.waiting_time << " ms\n";
    }

    // Average waiting time calculation
    double average_waiting_time = 0;
    for (const Process& process : processes) {
        average_waiting_time += process.waiting_time;
    }
    average_waiting_time /= processes.size();

    // Display average waiting time
    cout << "Average Waiting Time: " << fixed << setprecision(2) << average_waiting_time << " ms\n";
}


void displayUsage() {
    std::cout << "Usage: YourProgram -f inputFileName -o outputFileName\n";
}
//user main function UI
int main (int argc, char *argv[]){
   string inputFileName, outputFileName;
    int opt;
    while ((opt = getopt(argc, argv, "f:o:")) != -1){
        switch (opt){
            case 'f':
            inputFileName = optarg;
            break;
            case 'o':
             outputFileName = optarg;
            break;
            default:
            displayUsage();
            return 1;
        }
    }

  if (inputFileName.empty() || outputFileName.empty()){
    displayUsage();
    return 1;
}

    cout << "Select Scheduling Method: \n";
    cout << "1. FCFS\n";
    cout << "2. SJF\n";
    cout << "3. Round Robin\n";
    cout << "4. Priority Scheduling\n";
    cout << "Choose a Number: ";

    int choice;
    cin>> choice;
    int modeChoice;
    cout << "Select mode: \n";
    cout << "1. Preemptive : \n";
    cout << "2. Non-Preemptive: \n";
    cout << "3. off: \n";
    cout << "Enter Number : \n";
    cin >> modeChoice;
    if (modeChoice < 1 || modeChoice > 3) {
    cerr << "Invalid mode choice. Exiting...\n";
    return 1;
}

      //additional options
        cout << "Select Option:\n";
        cout << "1. Show Result\n";
        cout << "2. End Program\n";
        cout << "Enter the corresponding number: ";

        int option;
        cin >> option;
    list<Process> processes;
    ifstream file(inputFileName);
    if (!file.is_open()){
        cerr<<"Error Opening file '" << inputFileName << "' . Please make sure the file is in the correct location. \n";
        return 1; 
    }
    cout << "File Opened \n";
    //data read process from fle to store in list process
    string name;
    int priority, burst_time, arrival_time;
   while (file >> name >> priority >> burst_time >> arrival_time) {
    cout << "Read: " << name << " " << priority << " " << burst_time << " " << arrival_time << endl;
    processes.emplace_back(name, priority, burst_time, arrival_time);
}

   file.close();

    Scheduler* scheduler = nullptr;
    //instance of selected scheduling algo

if (choice == 1) {
    scheduler = new FCFS();
    displayStats(processes, "First Come First Served");
} else if (choice == 2) {
    scheduler = new SJF();
    displayStats(processes, "Shortest Job First");
     dynamic_cast<SJF*>(scheduler)->calculateSJFAverages(processes);
} else if (choice == 3) {
    scheduler = new RoundRobin();
    displayStats(processes, "Round Robin");
} else if (choice == 4) {
    scheduler = new PriorityAlgo();
    displayStats(processes, "Priority Scheduling");
} else {
    cerr << "Invalid Choice. Exiting...\n";
    return 1;
}
// Error handling for invalid user input
if (choice < 1 || choice > 4) {
    cerr << "Invalid choice. Exiting...\n";
    return 1;
}
scheduler->scheduleProcesses(processes);

if (option == 1) {
   displayStats(processes, "Unknown Scheduling Method");

} else if (option == 2) {
    ofstream outputFile(outputFileName);
    if (!outputFile.is_open()) {
        cerr << "Error opening file '" << outputFileName << "'.\n";
        return 1;
    }
    // Write to the output file
    for (const Process &process : processes) {
        outputFile << process.name << "\t" << process.waiting_time << "\n";
    }
    // Close the output file
    outputFile.close();
} else {
    cerr << "Invalid option. Exiting...\n";
    return 1;
}

// Clean up
delete scheduler;
return 0;

};