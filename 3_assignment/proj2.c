#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{

	if(argc < 3)
	{
		printf("Usage: proj2 input_file FCFS|RR|SRJF [qtum]\n");
	}
	else
	{
		typedef struct
		{
			int pid;
			int arrival_time;
			int burst_time;
			int arrived;
		} process;
		int data[1000];//to hold raw data read in
		int c;//number to be read in
		int count = 0;//after read will be num items
		FILE *file;
		file = fopen(argv[1], "r");
		while(fscanf(file, "%i", &c) == 1)
		{
			data[count] = c;
			count = count + 1;
			//printf("%i\n", c);
		}
		//printf("%i\n", count);
		process singProc[count/3]; //count / 3 is num of processes
		c = 0;
		while(c <= count)
		{
			singProc[c/3].pid = data[c];
			singProc[c/3].arrival_time = data[c + 1];
			singProc[c/3].burst_time = data[c + 2];
			singProc[c/3].arrived = 0;
			c = c + 3;
		}

		/*
		for(c = 0;c < count/3; c++)
		{	
			printf("%d, %d, %d\n", singProc[c].pid, singProc[c].arrival_time, singProc[c].burst_time);
		}
		*/
		int sysTime;
		if(strcmp(argv[2], "FCFS") == 0)
		{
			printf("Scheduling algorithm: FCFS\nTotal %d tasks are read from \"%s\". press 'ENTER' to start...\n", count/3, argv[1]);
			getchar();
			printf("============================================================\n");
			sysTime = 0;
			for(c = 0;c < count / 3; c++)
			{	
				int i = 0;
				while(i < singProc[c].burst_time)
				{
					printf("<system time: %d > process %d is running\n", sysTime, singProc[c].pid);
					++sysTime;
					++i;
				}
				printf("<system time: %d > process %d is finished.......\n", sysTime, singProc[c].pid);
			}
			printf("<system time: %d > All processes finish..............\n", sysTime);
			printf("============================================================\n"); 

		}
		else if(strcmp(argv[2], "RR") == 0)
		{	
			if(argc != 4)
			{
				printf("Usage: proj2 input_file FCFS|RR|SRJF [qtum]\n");
			}
			else
			{
				printf("Scheduling algorithm: RR\nTotal %d tasks are read from \"%s\". press 'ENTER' to start...\n", count/3, argv[1]);
				printf("Time Quantum Selected: %d", atoi(argv[3]));
				getchar();
				printf("============================================================\n");
			    sysTime = 0;
				int quantum = atoi(argv[3]);	
				int activeProc = count / 3;
				int numProc = activeProc - 1;
				c = 0;
				int index = 0;
				while(activeProc > 0)
				{
						if(singProc[index].burst_time > 0)
						{
							if(singProc[index].arrival_time > sysTime)
							{
								++index;
								if(index > numProc)
								{
									index = 0;
								}
							}
							else
							{
								while(c < quantum)
								{
									printf("<system time: %d > process %d is running\n", sysTime, singProc[index].pid);
									++sysTime;
									--singProc[index].burst_time;
									if(singProc[index].burst_time <= 0)
									{
										//printf("%d is finished\n", index);
										c = quantum + 1;
										--activeProc;
									}
									++c;
								}
								c = 0;
								++index;
								if(index > numProc)
								{
									index = 0;
								}
							}
						}
						else if(singProc[index].burst_time <= 0)
						{
							//printf("%d is finisdfdfhed\n", index);
							--activeProc;
							++index;
							if(index > numProc)
							{
								index = 0;
							}
						}
						
					
				}

			}
		}
		else if(strcmp(argv[2], "SRTF") == 0)
		{
			printf("Scheduling algorithm: SRTF\nTotal %d tasks are read from \"%s\". press 'ENTER' to start...\n", count/3, argv[1]);
			
			getchar();
			printf("============================================================\n");
			int runNext;
			int lowest = 1000;
			int i;
			sysTime = 0;
			int numProc = 0;
			while(1 == 1)
			{
				for(i = 0; i < count / 3; i++)
				{
					if(sysTime == singProc[i].arrival_time)
					{
						singProc[i].arrived = 1;
						++numProc;
						//printf("<system time: %d>process %d has arrived\n", sysTime, singProc[i].pid);
					}
				}
				for(i = 0; i < count / 3; i++)
				{
					if(singProc[i].arrived == 1 && singProc[i].burst_time < lowest)
					{
						lowest = singProc[i].burst_time;
						runNext = i;
					}
				}
				printf("<system time: %d >process %d is running\n", sysTime, singProc[runNext].pid);
				--singProc[runNext].burst_time;
				if(singProc[runNext].burst_time <= 0)
				{
					printf("<system time: %d >process %d is finished...\n", sysTime+1, singProc[runNext].pid);
					singProc[runNext].arrived = 0;
					--numProc;
					lowest = 100;
				}
				++sysTime;
				if(numProc <= 0)
				{
					printf("<system time: %d >All processes finish...............\n", sysTime);
					printf("============================================================\n");
					break;
				}
			}
		}
		else
		{
			printf("Error\n");
		}
	}
	return 0;
}
