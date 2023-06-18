#include "pch.h"
#include "doit.h"
#include <Windows.h>
#include <tlhelp32.h>
#include <iostream>
#include <string>
#include <cstdio>
#include<fstream>
#include <winDNS.h>

using namespace std;

void doit() {
	DWORD pid = GetCurrentProcessId();
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid);
	QWORD dwModuleBaseAddress = 0;
	string modulename = MODULE_NAME;
	wofstream outputFile("list.txt");
	if (hSnapshot != INVALID_HANDLE_VALUE)
	{
		MODULEENTRY32 ModuleEntry32 = { 0 };
		ModuleEntry32.dwSize = sizeof(MODULEENTRY32);
		if (Module32First(hSnapshot, &ModuleEntry32))
		{
			do
			{
				wstring modName(ModuleEntry32.szModule);
				outputFile << modName << "\n";
				if (!modName.compare(L"DiscordHook64.dll")) {
					dwModuleBaseAddress = (DWORD)ModuleEntry32.modBaseAddr;
				}
			} while (Module32Next(hSnapshot, &ModuleEntry32));
		}
		CloseHandle(hSnapshot);
	}
	outputFile << dwModuleBaseAddress << "\n";
}