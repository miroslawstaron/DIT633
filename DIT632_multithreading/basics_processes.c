/*
* This is an example of running processes in Windows
* Please note that there is a lot of Windows-specific code here
*/

#include <windows.h>
#include <stdio.h>
#include <tchar.h>

/*
* Function demonstrating the execution of a new process
* For the simplicity reasons, I use notepad.exe here. 
*/
void basics_processes()
{
	// process information
	// includes such parameters like the name of the 
	// newly created window
	STARTUPINFO si;

	// this is the information about the newly 
	// created process
	PROCESS_INFORMATION pi;

	// filling the block of memory with 0's
	// which is needed when initializing the process
	ZeroMemory(&si, sizeof(si));

	// size of the startup process information
	si.cb = sizeof(si);

	// the same for the process information
	ZeroMemory(&pi, sizeof(pi));

	// CreateProcess is the main function to
	// create the new process
	if (!CreateProcess(L"C:\\WINDOWS\\system32\\notepad.exe", // module name which is the Windows cmd command, it should be an L-string. 
		NULL, // Command line.
		NULL, // Process handle not inheritable.
		NULL, // Thread handle not inheritable.
		FALSE, // Set handle inheritance to FALSE.
		0, // No creation flags.
		NULL, // Use parents environment block.
		NULL, // Use parents starting directory.
		&si, // Pointer to STARTUPINFO structure.
		&pi) // Pointer to PROCESS_INFORMATION structure.
		)

		printf("\nCreateProcess() failed.\n\n");

	else

		printf("\nCreateProcess() successful.\n\n");

	// Wait until child process exits (in milliseconds). 
	// If INFINITE, the functions time-out interval never elapses except with user or other intervention.
	WaitForSingleObject(pi.hProcess, INFINITE);

	// Close process and thread handles.
	CloseHandle(pi.hProcess);

	CloseHandle(pi.hThread);
}