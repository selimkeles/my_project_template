// #include <stdlib.h>
// #include <stdio.h>
// #ifdef _WIN32
// #include <windows.h>
// #else
// #include <unistd.h>
// #include <pthread.h>
// #include <signal.h>
// #endif
// #include "TaskScheduler.h"

// void myFunction(void* lpParam);

// TaskScheduler scheduler;

// #ifdef _WIN32
// void CALLBACK myFunction(PVOID lpParam, BOOLEAN TimerOrWaitFired) {
//     scheduler.increaseSystemTime();
// }
// #else
// void myFunction(union sigval sv) {
//     scheduler.increaseSystemTime();
// }
// #endif

// void test(void *) {
//     static int count = 0;
//     count++;
//     if (count >= 10) {
//         scheduler.deleteTask(&test);
//     }
//     #ifdef _WIN32
//     SYSTEMTIME st;
//     GetSystemTime(&st);
//     printf("Current time: %%02d:%02d:%02d:%03d\n",
//            st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
//     #else
//     time_t t = time(NULL);
//     struct tm *tm = localtime(&t);
//     printf("Current date and time: %02d/%02d/%04d %02d:%02d:%02d\n",
//            tm->tm_mday, tm->tm_mon + 1, tm->tm_year + 1900, tm->tm_hour, tm->tm_min, tm->tm_sec);
//     #endif
//     printf("Hello\n\n");
// }

// int main() {
//     #ifdef _WIN32
//     HANDLE hTimer = NULL;
//     HANDLE hTimerQueue = NULL;

//     // Create the timer queue
//     hTimerQueue = CreateTimerQueue();
//     if (hTimerQueue == NULL) {
//         perror("CreateTimerQueue");
//         exit(EXIT_FAILURE);
//     }

//     // Set the timer to call myFunction every 1 millisecond
//     if (!CreateTimerQueueTimer(&hTimer, hTimerQueue, (WAITORTIMERCALLBACK)myFunction, NULL, 0, 1, WT_EXECUTEDEFAULT)) {
//         perror("CreateTimerQueueTimer");
//         exit(EXIT_FAILURE);
//     }
//     #else
//     struct sigevent sev;
//     timer_t timerid;
//     struct itimerspec its;

//     // Set up the timer event
//     sev.sigev_notify = SIGEV_THREAD;
//     sev.sigev_notify_function = myFunction;
//     sev.sigev_value.sival_ptr = NULL;

//     // Create the timer
//     if (timer_create(CLOCK_MONOTONIC, &sev, &timerid) == -1)
//     {
//         perror("timer_create");
//         exit(EXIT_FAILURE);
//     }

//     // Set the timer interval to 1 millisecond
//     its.it_value.tv_sec = 0;
//     its.it_value.tv_nsec = 1000000; // 1 millisecond
//     its.it_interval = its.it_value;

//     // Start the timer
//     if (timer_settime(timerid, 0, &its, NULL) == -1)
//     {
//         perror("timer_settime");
//         exit(EXIT_FAILURE);
//     }
//     #endif

//     Task task1(CallbackTime::CB_50MS, &test);
//     scheduler.addTask(task1);
//     scheduler.run();
//     return 0;
// }