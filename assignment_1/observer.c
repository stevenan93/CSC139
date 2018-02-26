//steven an

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int shortFunction();

int main(int argc, char *argv[])
{

	char repTypeName[16];
	char c1, c2;
	int interval, duration;	
	strcpy(repTypeName, "Standard");
	if(argc > 1)
	{
		sscanf(argv[1], "%c%c", &c1, &c2);
		if(c1 != '-')
		{
			fprintf(stderr, "usage: observer [-s][-l int dur]\n");
			exit(1);
		}	
		if(c2 == 's')
		{
			write(STDOUT_FILENO, "SHORT INFO\n", 11);
			//system("top | grep -m1 \"Cpu\"");
			system("top | grep -m1 \"Cpu\" | awk -F'{ |,|  |%|}+' '{print \"User Time: \" $2 \"% | System Time: \" $5 \"% | Idle Time:\"$10\"%\"}'");
			
			write(STDOUT_FILENO, "DISK USAGE\n", 12);
			system("iostat -m | grep \"Device\"");
			system("iostat -m | grep \"sda\"");
			system("grep ctxt /proc/12/status");
			system("echo \"LAST BOOT:\"");
			system("last boot");
			system("echo \"PROCESSES CREATED SINCE BOOT:\"");
			system("cat /proc/stat | grep \"processes\"");

		}
		if(c2 == 'l')
		{
			if(argc < 4 )
			{
				fprintf(stderr, "usage: observer [-s][-l int dur]\n");
				exit(1);
			}
			else
			{
				write(STDOUT_FILENO, "LONG\n", 5);
				//strcpy(repTypeName, "Long");
				interval = atoi(argv[2]);
				duration = atoi(argv[3]);

				system("cat /proc/meminfo | grep \"MemTotal:\"");
				system("cat /proc/meminfo | grep \"MemFree:\"");
			}
		}
	}
	
	write(STDOUT_FILENO, "----DEFAULT INFO----\n", 22); 
	//system call that probes the /proc/cpuinfo file for cpu info
	system("grep -m1 \"model name\" /proc/cpuinfo");
	
	//had to use write instead of printf since stdio.h functions are buffered
	write(STDOUT_FILENO, "Kernel Version : ", 17);

	//system call that probes for kernel version of linux
	system("uname -r");
	
	
	write(STDOUT_FILENO, "System Uptime(DAY:HH:MM:SS) : ", 30);
	
	system("uptime | awk -F\'( |,|:)+\' \'{print $6\":\"$2\":\" $3\":\" $4}\'");
	
	write(STDOUT_FILENO, "Date : ", 7);
	system("date");

	write(STDOUT_FILENO, "Hostname : ", 11);
	system("hostname");

	
	return 0;

}

int shortFunction()
{
	system("top | grep -m1 \"cpu\"");
	return 0;
}
