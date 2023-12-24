#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// Process structure to store process attributes
struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int priority;
    int remaining_time;
};

// Function to compare processes based on priority
struct PriorityCompare {
    bool operator()(const Process& p1, const Process& p2) {
        return p1.priority > p2.priority;
    }
};

int main() {
    int num_processes;
    cout << "Enter the number of processes (up to 5): ";
    cin >> num_processes;

    if (num_processes <= 0 || num_processes > 5) {
        cout << "Invalid number of processes. Please enter a number between 1 and 5." << endl;
        return 1;
    }

    vector<Process> processes(num_processes);
    priority_queue<Process, vector<Process>, PriorityCompare> ready_queue;
    int time_quantum;

    cout << "Enter the time quantum for Round Robin: ";
    cin >> time_quantum;

    // Input process details
    for (int i = 0; i < num_processes; ++i) {
        processes[i].id = i + 1;
        cout << "Enter arrival time for Process " << i + 1 << ": ";
        cin >> processes[i].arrival_time;
        cout << "Enter burst time for Process " << i + 1 << ": ";
        cin >> processes[i].burst_time;
        cout << "Enter priority for Process " << i + 1 << ": ";
        cin >> processes[i].priority;
        processes[i].remaining_time = processes[i].burst_time;
    }

    int current_time = 0;

    while (!ready_queue.empty() || !processes.empty()) {
        // Enqueue processes that have arrived at the current time
        for (int i = 0; i < num_processes; ++i) {
            if (processes[i].arrival_time == current_time) {
                ready_queue.push(processes[i]);
                processes.erase(processes.begin() + i);
                i--; // Adjust index after erasing a process
                num_processes--;
            }
        }

        if (!ready_queue.empty()) {
            Process current_process = ready_queue.top();
            ready_queue.pop();

            // Execute the process using round-robin with time quantum
            int time_slice = min(time_quantum, current_process.remaining_time);
            current_time += time_slice;
            current_process.remaining_time -= time_slice;

            cout << "Process " << current_process.id << " is executing from time " << current_time - time_slice << " to " << current_time << endl;

            if (current_process.remaining_time > 0) {
                ready_queue.push(current_process); // Put back the process if it's not finished
            } else {
                cout << "Process " << current_process.id << " has completed." << endl;
            }
        } else {
            current_time++;
        }
    }

    return 0;
}
