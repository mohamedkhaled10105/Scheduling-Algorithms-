#include <iostream>
using namespace std;

#define MAX_PROCESSES 20

double fcfs(int arrival[], int burst[], int n) {
    int currentTime = 0;
    double totalWaiting = 0;

    for (int i = 0; i < n; i++) {

        if (currentTime < arrival[i]) {
            currentTime = arrival[i];
        }

        totalWaiting += (currentTime - arrival[i]);

        currentTime += burst[i];
    }

    return totalWaiting / n;
}

int main() {
    int n = 5;

    int arrival[MAX_PROCESSES] = {2, 0, 5, 1, 3};
    int burst[MAX_PROCESSES]   = {6, 4, 2, 7, 3};

    cout << "FCFS: " << fcfs(arrival, burst, n) << endl;

    return 0;
}