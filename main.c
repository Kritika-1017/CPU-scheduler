#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PROCESSES 100

struct Process {
    char pid[10];
    int arrivalTime;
    int serviceTime;
    int finishTime;
    int turnaroundTime;
    float normalizedTurnaroundTime;
    int priority;
};

void printTimeline(const struct Process processes[], int n) {
    printf("Timeline:\n");
    for (int i = 0; i < n; ++i) {
        printf("Process %s: ", processes[i].pid);
        for (int j = 0; j < processes[i].finishTime; ++j) {
            if (j >= processes[i].arrivalTime && j < processes[i].finishTime)
                printf("*");
            else
                printf(".");
        }
        printf("\n");
    }
}

void printStatistics(const struct Process processes[], int n) {
    printf("Process Statistics:\n");
    printf("PID\tTurnaround Time\tNormalized Turnaround Time\n");
    for (int i = 0; i < n; ++i) {
        printf("%s\t%d\t\t%.2f\n", processes[i].pid, processes[i].turnaroundTime, processes[i].normalizedTurnaroundTime);
    }
}

void sortByArrivalTime(struct Process processes[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (processes[j].arrivalTime > processes[j + 1].arrivalTime) {
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}

void sortByServiceTime(struct Process processes[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (processes[j].serviceTime > processes[j + 1].serviceTime) {
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}

void sortByPriority(struct Process processes[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (processes[j].priority > processes[j + 1].priority) {
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}

void firstComeFirstServe(struct Process processes[], int n) {
    sortByArrivalTime(processes, n);
    int currentTime = 0;
    for (int i = 0; i < n; ++i) {
        if (currentTime < processes[i].arrivalTime)
            currentTime = processes[i].arrivalTime;
        processes[i].finishTime = currentTime + processes[i].serviceTime;
        processes[i].turnaroundTime = processes[i].finishTime - processes[i].arrivalTime;
        processes[i].normalizedTurnaroundTime = (float)processes[i].turnaroundTime / processes[i].serviceTime;
        currentTime = processes[i].finishTime;
    }
}

void shortestJobFirst(struct Process processes[], int n) {
    sortByArrivalTime(processes, n);
    struct Process readyQueue[MAX_PROCESSES];
    int currentTime = 0;
    int idx = 0;

    while (idx < n || idx < n) {
        while (idx < n && processes[idx].arrivalTime <= currentTime) {
            readyQueue[idx] = processes[idx];
            ++idx;
        }
        if (idx < n) {
            // Selection Sort
            for (int i = 0; i < idx - 1; ++i) {
                int min_idx = i;
                for (int j = i + 1; j < idx; ++j) {
                    if (readyQueue[j].serviceTime < readyQueue[min_idx].serviceTime) {
                        min_idx = j;
                    }
                }
                struct Process temp = readyQueue[min_idx];
                readyQueue[min_idx] = readyQueue[i];
                readyQueue[i] = temp;
            }
            struct Process process = readyQueue[0];
            for (int i = 0; i < idx - 1; ++i) {
                readyQueue[i] = readyQueue[i + 1];
            }
            idx--;
            process.finishTime = currentTime + process.serviceTime;
            currentTime = process.finishTime;
            for (int i = 0; i < n; ++i) {
                if (strcmp(process.pid, processes[i].pid) == 0) {
                    processes[i] = process;
                    break;
                }
            }
        } else if (idx < n) {
            currentTime = processes[idx].arrivalTime;
        }
    }
}

void longestJobFirst(struct Process processes[], int n) {
    sortByArrivalTime(processes, n);
    struct Process readyQueue[MAX_PROCESSES];
    int currentTime = 0;
    int idx = 0;

    while (idx < n || idx < n) {
        while (idx < n && processes[idx].arrivalTime <= currentTime) {
            readyQueue[idx] = processes[idx];
            ++idx;
        }
        if (idx < n) {
            // Selection Sort
            for (int i = 0; i < idx - 1; ++i) {
                int max_idx = i;
                for (int j = i + 1; j < idx; ++j) {
                    if (readyQueue[j].serviceTime > readyQueue[max_idx].serviceTime) {
                        max_idx = j;
                    }
                }
                struct Process temp = readyQueue[max_idx];
                readyQueue[max_idx] = readyQueue[i];
                readyQueue[i] = temp;
            }
            struct Process process = readyQueue[0];
            for (int i = 0; i < idx - 1; ++i) {
                readyQueue[i] = readyQueue[i + 1];
            }
            idx--;
            process.finishTime = currentTime + process.serviceTime;
            currentTime = process.finishTime;
            for (int i = 0; i < n; ++i) {
                if (strcmp(process.pid, processes[i].pid) == 0) {
                    processes[i] = process;
                    break;
                }
            }
        } else if (idx < n) {
            currentTime = processes[idx].arrivalTime;
        }
    }
}

void priorityScheduling(struct Process processes[], int n) {
    sortByArrivalTime(processes, n);
    struct Process readyQueue[MAX_PROCESSES];
    int currentTime = 0;
    int idx = 0;

    while (idx < n || idx < n)
{
        while (idx < n && processes[idx].arrivalTime <= currentTime) {
            readyQueue[idx] = processes[idx];
            ++idx;
        }
        if (idx < n) {
            // Selection Sort based on priority
            for (int i = 0; i < idx - 1; ++i) {
                int min_idx = i;
                for (int j = i + 1; j < idx; ++j) {
                    if (readyQueue[j].priority < readyQueue[min_idx].priority) {
                        min_idx = j;
                    }
                }
                struct Process temp = readyQueue[min_idx];
                readyQueue[min_idx] = readyQueue[i];
                readyQueue[i] = temp;
            }
            struct Process process = readyQueue[0];
            for (int i = 0; i < idx - 1; ++i) {
                readyQueue[i] = readyQueue[i + 1];
            }
            idx--;
            process.finishTime = currentTime + process.serviceTime;
            currentTime = process.finishTime;
            for (int i = 0; i < n; ++i) {
                if (strcmp(process.pid, processes[i].pid) == 0) {
                    processes[i] = process;
                    break;
                }
            }
        } else if (idx < n) {
            currentTime = processes[idx].arrivalTime;
        }
    }
}

void longestRemainingTimeFirst(struct Process processes[], int n) {
    sortByArrivalTime(processes, n);
    int currentTime = 0;
    struct Process readyQueue[MAX_PROCESSES];
    int idx = 0;
    while (idx < n || idx < n) {
        if (idx < n) {
            int maxTime = -1;
            int maxIdx = -1;
            for (int i = 0; i < n; ++i) {
                if (processes[i].arrivalTime <= currentTime && processes[i].serviceTime > maxTime) {
                    maxTime = processes[i].serviceTime;
                    maxIdx = i;
                }
            }
            if (maxIdx != -1) {
                struct Process process = processes[maxIdx];
                for (int i = maxIdx; i < n - 1; ++i) {
                    processes[i] = processes[i + 1];
                }
                n--;
                for (int i = 0; i < process.serviceTime; ++i) {
                    if (i >= process.arrivalTime && i < currentTime + process.serviceTime)
                        printf("*");
                    else
                        printf(".");
                }
                printf("\n");
                currentTime += process.serviceTime;
            } else {
                currentTime++;
            }
        } else {
            currentTime++;
        }
    }
}

void highestResponseRatioNext(struct Process processes[], int n) {
    sortByArrivalTime(processes, n);
    int currentTime = 0;
    struct Process readyQueue[MAX_PROCESSES];
    int idx = 0;
    while (idx < n || idx < n) {
        if (idx < n) {
            float maxRatio = -1;
            int maxIdx = -1;
            for (int i = 0; i < n; ++i) {
                float ratio = (float)(currentTime - processes[i].arrivalTime + processes[i].serviceTime) / processes[i].serviceTime;
                if (processes[i].arrivalTime <= currentTime && ratio > maxRatio) {
                    maxRatio = ratio;
                    maxIdx = i;
                }
            }
            if (maxIdx != -1) {
                struct Process process = processes[maxIdx];
                for (int i = maxIdx; i < n - 1; ++i) {
                    processes[i] = processes[i + 1];
                }
                n--;
                for (int i = 0; i < process.serviceTime; ++i) {
                    if (i >= process.arrivalTime && i < currentTime + process.serviceTime)
                        printf("*");
                    else
                        printf(".");
                }
                printf("\n");
                currentTime += process.serviceTime;
            } else {
                currentTime++;
            }
        } else {
            currentTime++;
        }
    }
}

void multipleQueueScheduling(struct Process processes[], int n) {
    sortByArrivalTime(processes, n);
    struct Process queues[5][MAX_PROCESSES];
    int front[5] = {0};
    int rear[5] = {0};
    int currentTime = 0;
    int idx = 0;
    while ((rear[0] - front[0] > 0) || idx < n) {
        for (int i = 0; i < 5; ++i) {
            if (rear[i] > front[i]) {
                struct Process cur = queues[i][front[i]];
                front[i]++;
                int executeTime = (cur.serviceTime > 1) ? 1 : cur.serviceTime;
                for (int j = 0; j < executeTime; ++j)
                    printf("*");
                printf("\n");
                cur.serviceTime -= executeTime;
                currentTime += executeTime;
                while (idx < n && processes[idx].arrivalTime <= currentTime) {
                    if (processes[idx].serviceTime > 0 && processes[idx].priority == i) {
                        queues[i][rear[i]] = processes[idx];
                        rear[i]++;
                    }
                    ++idx;
                }
            }
        }
    }
}

void multilevelFeedbackQueueScheduling(struct Process processes[], int n) {
    sortByArrivalTime(processes, n);
    struct Process queues[3][MAX_PROCESSES];
    int front[3] = {0};
    int rear[3] = {0};
    int currentTime = 0;
    int idx = 0;
    while ((rear[0] - front[0] > 0) || (rear[1] -
front[1] > 0) || (rear[2] - front[2] > 0) || idx < n) {
        // High priority queue
        while (rear[0] > front[0]) {
            struct Process cur = queues[0][front[0]];
            front[0]++;
            int executeTime = (cur.serviceTime > 1) ? 1 : cur.serviceTime;
            for (int i = 0; i < executeTime; ++i)
                printf("*");
            printf("\n");
            cur.serviceTime -= executeTime;
            currentTime += executeTime;
            while (idx < n && processes[idx].arrivalTime <= currentTime) {
                if (processes[idx].serviceTime > 0 && processes[idx].priority == 0) {
                    queues[0][rear[0]] = processes[idx];
                    rear[0]++;
                }
                ++idx;
            }
            if (executeTime < 1) // If the process doesn't complete, move it to the next priority level
                queues[1][rear[1]++] = cur;
        }
        // Medium priority queue
        while (rear[1] > front[1]) {
            struct Process cur = queues[1][front[1]];
            front[1]++;
            int executeTime = (cur.serviceTime > 2) ? 2 : cur.serviceTime;
            for (int i = 0; i < executeTime; ++i)
                printf("*");
            printf("\n");
            cur.serviceTime -= executeTime;
            currentTime += executeTime;
            while (idx < n && processes[idx].arrivalTime <= currentTime) {
                if (processes[idx].serviceTime > 0 && processes[idx].priority == 1) {
                    queues[1][rear[1]] = processes[idx];
                    rear[1]++;
                }
                ++idx;
            }
            if (executeTime < 2) // If the process doesn't complete, move it to the next priority level
                queues[2][rear[2]++] = cur;
        }
        // Low priority queue
        while (rear[2] > front[2]) {
            struct Process cur = queues[2][front[2]];
            front[2]++;
            int executeTime = (cur.serviceTime > 4) ? 4 : cur.serviceTime;
            for (int i = 0; i < executeTime; ++i)
                printf("*");
            printf("\n");
            cur.serviceTime -= executeTime;
            currentTime += executeTime;
            while (idx < n && processes[idx].arrivalTime <= currentTime) {
                if (processes[idx].serviceTime > 0 && processes[idx].priority == 2) {
                    queues[2][rear[2]] = processes[idx];
                    rear[2]++;
                }
                ++idx;
            }
            if (executeTime < 4) // If the process doesn't complete, move it to the end of the low priority queue
                queues[2][rear[2]++] = cur;
        }
    }
}

void inputProcesses(struct Process processes[], int *n) {
    printf("Enter the number of processes: ");
    scanf("%d", n);
    for (int i = 0; i < *n; ++i) {
        printf("Enter PID for process %d: ", i + 1);
        scanf("%s", processes[i].pid);
        printf("Enter arrival time for process %d: ", i + 1);
        scanf("%d", &processes[i].arrivalTime);
        printf("Enter service time for process %d: ", i + 1);
        scanf("%d", &processes[i].serviceTime);
        printf("Enter priority for process %d (lower number means higher priority): ", i + 1);
        scanf("%d", &processes[i].priority);
    }
}

void compareSchedulingAlgorithms(struct Process processes[], int n) {
    struct Process allProcesses[MAX_PROCESSES];
    for (int i = 0; i < n; ++i) {
        allProcesses[i] = processes[i];
    }
    char *algorithmNames[] = {
        "First Come First Serve",
        "Shortest Job First",
        "Longest Job First",
        "Priority Scheduling",
        "Longest Remaining Time First",
        "Highest Response Ratio Next",
        "Multiple Queue Scheduling",
        "Multilevel Feedback Queue Scheduling"
    };

    printf("Comparing Scheduling Algorithms:\n");
    printf("----------------------------------------------------\n");
    printf("%-25s%-25s%s\n", "Scheduling Algorithm", "Average Turnaround Time", "Average Normalized Turnaround Time");
    printf("----------------------------------------------------\n");

    for (int i = 0; i < 8; ++i) {
        if (i == 4 || i == 5) {
            printf("%-25s%-25s%s\n", algorithmNames[i], "Not applicable", "");
            continue;
        }

        switch (i) {
            case 0:
                firstComeFirstServe(allProcesses, n);
                break;
            case 1:
                shortestJobFirst(allProcesses, n);
                break;
            case 2:
                longestJobFirst(allProcesses, n);
                break;
            case 3:
                priorityScheduling(allProcesses, n);
                break;
            case 6:
                multipleQueueScheduling(allProcesses, n);
                break;
            case 7:
                multilevelFeedbackQueueScheduling(allProcesses, n);
                break;
        }

        // Calculate average turnaround time and average normalized turnaround time
        double avgTurnaroundTime = 0.0;
        double avgNormalizedTurnaroundTime = 0.0;
        for (int j = 0; j < n; ++j) {
            avgTurnaroundTime += allProcesses[j].turnaroundTime;
            avgNormalizedTurnaroundTime += allProcesses[j].normalizedTurnaroundTime;
        }
        avgTurnaroundTime /= n;
        avgNormalizedTurnaroundTime /= n;

        printf("%-25s%-25.2f%.2f\n", algorithmNames[i], avgTurnaroundTime, avgNormalizedTurnaroundTime);
    }
}

int main() {
    struct Process processes[MAX_PROCESSES];
    int n;
    inputProcesses(processes, &n);

    int choice;
    printf("Choose the scheduling algorithm:\n");
    printf("1. First Come First Serve\n");
    printf("2. Shortest Job First\n");
    printf("3. Longest Job First\n");
    printf("4. Priority Scheduling\n");
    printf("5. Longest Remaining Time First\n");
    printf("6. Highest Response Ratio Next\n");
    printf("7. Multiple Queue Scheduling\n");
    printf("8. Multilevel Feedback Queue Scheduling\n");
    printf("9. Compare Scheduling Algorithms\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("First Come First Serve:\n");
            firstComeFirstServe(processes, n);
            printStatistics(processes, n);
            printTimeline(processes, n);
            break;
        case 2:
            printf("Shortest Job First:\n");
           
            shortestJobFirst(processes, n);
            printStatistics(processes, n);
            printTimeline(processes, n);
            break;
        case 3:
            printf("Longest Job First:\n");
            longestJobFirst(processes, n);
            printStatistics(processes, n);
            printTimeline(processes, n);
            break;
        case 4:
            printf("Priority Scheduling:\n");
            priorityScheduling(processes, n);
            printStatistics(processes, n);
            printTimeline(processes, n);
            break;
        case 5:
            printf("Longest Remaining Time First:\n");
            longestRemainingTimeFirst(processes, n);
            break;
        case 6:
            printf("Highest Response Ratio Next:\n");
            highestResponseRatioNext(processes, n);
            break;
        case 7:
            printf("Multiple Queue Scheduling:\n");
            multipleQueueScheduling(processes, n);
            break;
        case 8:
            printf("Multilevel Feedback Queue Scheduling:\n");
            multilevelFeedbackQueueScheduling(processes, n);
            break;
        case 9:
            compareSchedulingAlgorithms(processes, n);
            break;
        default:
            printf("Invalid choice!\n");
            break;
    }

    return 0;
}

