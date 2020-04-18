/**
Made by Ali-Berro 18 April 2020
Under the MIT license, i.e. anybody can edit and redistribute this code
but if you could add a reference it would be KO.ol too :)
**/
#include <iostream>
#include <windows.h>
#include <tlhelp32.h>
using namespace std;

HANDLE hProcess = NULL;

bool ProcessExists(string processName)
{
	HANDLE handle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
	if(handle == INVALID_HANDLE_VALUE)
		return false;
    PROCESSENTRY32 entry;
    entry.dwSize = sizeof(entry);
	if(!Process32First(handle,&entry))
	{
		CloseHandle(handle);
		return false;
	}
    while (Process32Next(handle, &entry))
    {
        if(!strcmp(entry.szExeFile,processName.c_str())){
            CloseHandle(handle);
            hProcess = OpenProcess(PROCESS_ALL_ACCESS,false,entry.th32ProcessID);
            return true;
        }
    }
    CloseHandle(handle);
    return false;
}

bool killProcess()
{
	if(TerminateProcess(hProcess,0))
	{
		CloseHandle(hProcess);
		return true;
	}
	CloseHandle(hProcess);
	return false;
}

int main()
{
	cout << "Running...";
	while(true)
	{
		if(ProcessExists("client.exe")) //Easy-Cafe Systems
		{
			killProcess();
		}
		if(ProcessExists("slTaskList.exe")) //Smart Launch
		{
			killProcess();
		}
		if(ProcessExists("StartKiller.exe")) //Smart Launch
		{
			killProcess();
		}
		Sleep(10);
	}
    return 0;
}
