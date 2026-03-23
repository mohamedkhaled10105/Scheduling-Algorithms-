#include <iostream>
using namespace std;

#define MAX_PROCESSES 20 

// FCFS which runs processes in order of arrival
double fcfs(int arrival[], int burst[], int n) {
    int currentTime = 0;
    double totalWaiting = 0;

    for (int i = 0; i < n; i++) {
        // if CPU is idle, jump to arrival time
        if (currentTime < arrival[i])
            currentTime = arrival[i];

        // calculate waiting time
        totalWaiting += (currentTime - arrival[i]);

        // run process
        currentTime += burst[i];
    }

    return totalWaiting / n;
}

// SJF which choose process with smallest burst time
double sjf(int arrival[], int burst[], int n) {
    int done[MAX_PROCESSES] = {0}; // track finished processes
    int finished = 0;
    int currentTime = 0;
    double totalWaiting = 0;

    while (finished < n) {
        int index = -1;
        int smallest = 100000;

        // find shortest job that already arrived
        for (int i = 0; i < n; i++) {
            if (done[i] == 0 && arrival[i] <= currentTime && burst[i] < smallest) {
                smallest = burst[i];
                index = i;
            }
        }

        if (index != -1) {
            totalWaiting += (currentTime - arrival[index]);
            currentTime += burst[index];
            done[index] = 1;
            finished++;
        } else {
            // no process ready yet
            currentTime++;
        }
    }

    return totalWaiting / n;
}

// Round Robin scheduling
double roundRobin(int arrival[], int burst[], int n, int quantum) {
    int remaining[MAX_PROCESSES]; // remaining burst time
    int waiting[MAX_PROCESSES] = {0};
    int lastExec[MAX_PROCESSES];

    // initialize arrays
    for (int i = 0; i < n; i++) {
        remaining[i] = burst[i];
        lastExec[i] = arrival[i];
    }

    int queue[MAX_PROCESSES];
    int front = 0, rear = 0;
    int inQueue[MAX_PROCESSES] = {0};

    int currentTime = 0;

    while (true) {
        int done = 1;

        // check if all processes completed
        for (int i = 0; i < n; i++) {
            if (remaining[i] > 0)
                done = 0;
        }

        if (done == 1)
            break;

        // add arrived processes to queue
        for (int i = 0; i < n; i++) {
            if (inQueue[i] == 0 && arrival[i] <= currentTime) {
                queue[rear++] = i;
                inQueue[i] = 1;
            }
        }

        if (front < rear) {
            int i = queue[front++];

            // update waiting time
            waiting[i] += currentTime - lastExec[i];

            // run process for quantum or remaining time
            int execTime;
            if (remaining[i] < quantum) {
                execTime = remaining[i];
            } else {
                execTime = quantum;
            }

            currentTime += execTime;
            remaining[i] -= execTime;
            lastExec[i] = currentTime;

            // check for new arrivals
            for (int j = 0; j < n; j++) {
                if (inQueue[j] == 0 && arrival[j] <= currentTime) {
                    queue[rear++] = j;
                    inQueue[j] = 1;
                }
            }

            // if not finished then add back to queue
            if (remaining[i] > 0) {
                queue[rear++] = i;
            }

        } else {
            
            currentTime++;
        }
    }

    double totalWaiting = 0;
    for (int i = 0; i < n; i++) {
        totalWaiting += waiting[i];
    }

    return totalWaiting / n;
}

int main() {
    int n = 5;

    
    int arrival[MAX_PROCESSES] = {2, 0, 5, 1, 3};
    int burst[MAX_PROCESSES]   = {6, 4, 2, 7, 3};

    double fcfs_avg = fcfs(arrival, burst, n);
    double sjf_avg = sjf(arrival, burst, n);
    double rr_avg = roundRobin(arrival, burst, n, 3);

    
    cout << "FCFS Average Waiting Time: " << fcfs_avg << endl;
    cout << "SJF Average Waiting Time: " << sjf_avg << endl;
    cout << "Round Robin Average Waiting Time: " << rr_avg << endl;

    return 0;
}