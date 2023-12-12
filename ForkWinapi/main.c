#include <stdio.h>
#include <windows.h>
#include <conio.h>


BOOL fork(char *name)
{
	if (name == NULL)return -1;

	LPWSTR title = "New process";
	
	HANDLE mutex = CreateMutex(NULL, TRUE, L"NewProcess");
	if (GetLastError() == ERROR_ALREADY_EXISTS) {
		HWND existingApp = FindWindow(0, (LPWSTR)title);
		if (existingApp) SetForegroundWindow(existingApp);
		return; 
	}

	PROCESS_INFORMATION proccessInformation;
	STARTUPINFO startupInfo;

	ZeroMemory(&proccessInformation, sizeof(proccessInformation));
	ZeroMemory(&startupInfo, sizeof(startupInfo));

	startupInfo.cb = sizeof(startupInfo);
	startupInfo.lpTitle = title;

	BOOL ret = CreateProcessA(
		name,
		NULL,
		NULL,
		NULL,
		TRUE,
		NORMAL_PRIORITY_CLASS | CREATE_NEW_CONSOLE | CREATE_NEW_PROCESS_GROUP,
		NULL,
		NULL,
		&startupInfo,
		&proccessInformation
	);

	WaitForSingleObject(proccessInformation.hProcess, INFINITE);

	DWORD exitcode;
	if (!GetExitCodeProcess(proccessInformation.hProcess, &exitcode)) {
		printf("Could not get process exit code. (%ld)", GetLastError());
		CloseHandle(proccessInformation.hProcess);
		CloseHandle(proccessInformation.hThread);
		return 1;
	}
	CloseHandle(proccessInformation.hProcess);
	CloseHandle(proccessInformation.hThread);
	printf("Process returned: %ld", exitcode);
}

int main(int argc, char* argv[])
{
	fork(argv[0]);
	while (_getch() != ' ');
	return 0;
}