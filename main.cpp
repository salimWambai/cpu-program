#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <deque>
#include <string>

//task class
class Task{
    public:
    std::string name;
    int priority;
    int burstTime;
    Task(const std: string& n, int p, int burst)
    : name(n), priority(p), burstTime(burst) {}
};
