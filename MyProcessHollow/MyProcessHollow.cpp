#pragma once
#include <stdio.h>
#include <Windows.h>
#include <winternl.h>
#include "hollow.h"

int main(int argc, char* argv[])
{
	if (argc != 3)		//Make sure this program is started by others.
	{
		printf("Do not open this program directly！\r\n");
		return 1;
	}
	char* pTarget = new char[strlen(argv[1])];
	char* pInjection = new char[strlen(argv[2])];
	memcpy(pTarget, argv[1], strlen(argv[1]));
	memcpy(pInjection, argv[2], strlen(argv[2]));
	int nRet = ProcessHollow(pTarget, pInjection);
	delete[] pTarget;
	delete[] pInjection;
	
    return nRet;
}