#pragma once 

//#######################################################################################
// D E F I N E S
//#######################################################################################

#if DBG
#define dprintf DbgPrint
#else
#define dprintf
#endif

#define DEVICE_NAME                  L"\\Device\\MyPcHunter"             	// Driver Name
#define SYMBOLIC_LINK_NAME           L"\\DosDevices\\MyPcHunter"            // Symbolic Link Name

//
// Device IO Control Codes
//定义控制码和设置控制派遣函数的通讯方式METHOD_BUFFERED
//
#define IOCTL_BASE          0x800
#define MY_CTL_CODE(i)        \
    CTL_CODE                  \
    (                         \
        FILE_DEVICE_UNKNOWN,  \
        IOCTL_BASE + i,       \
        METHOD_BUFFERED,      \
        FILE_ANY_ACCESS       \
    )

#define KERNAL_GDT_CORES MY_CTL_CODE(0)
#define KERNAL_GDT_ADDR  MY_CTL_CODE(1)
#define KERNAL_GDT_GET   MY_CTL_CODE(2)