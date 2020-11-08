#pragma once
#include <Windows.h>

typedef NTSTATUS(WINAPI* _NtUnmapViewOfSection)(
	HANDLE ProcessHandle,
	PVOID BaseAddress
	);

typedef struct BASE_RELOCATION_TYPEOFFSET {
	USHORT Offset : 12;
	USHORT Type : 4;
} BASE_RELOCATION_TYPEOFFSET, *PBASE_RELOCATION_TYPEOFFSET;

int ProcessHollow(const char* pTarget, const char* pInjection);
