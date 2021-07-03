// Listing 19-5: kIOMessage constants for interest notification messages

#define kIOMessageServiceIsTerminated      IOKit_common_msg(0x010) // removal
#define kIOMessageServiceIsSuspended       IOKit_common_msg(0x020)
#define kIOMessageServiceIsResumed         IOKit_common_msg(0x030)
#define kIOMessageServiceIsRequestingClose IOKit_common_msg(0x100)
#define kIOMessageServiceIsAttemptingOpen  IOKit_common_msg(0x101)
#define kIOMessageServiceWasClosed         IOKit_common_msg(0x110)
#define kIOMessageServiceBusyStateChange   IOKit_common_msg(0x120)
#define kIOMessageServicePropertyChange    IOKit_common_msg(0x130)
//
// These are considered deprecated
//
#define kIOMessageCanDevicePowerOff        IOKit_common_msg(0x200)
#define kIOMessageDeviceWillPowerOff       IOKit_common_msg(0x210)
#define kIOMessageDeviceWillNotPowerOff    IOKit_common_msg(0x220)
#define kIOMessageDeviceHasPoweredOn       IOKit_common_msg(0x230)
#define kIOMessageCanSystemPowerOff        IOKit_common_msg(0x240)
//
// These are wrapped by IOPMLib's IORegisterForSystemPower
//
#define kIOMessageSystemWillPowerOff       IOKit_common_msg(0x250)
#define kIOMessageSystemWillNotPowerOff    IOKit_common_msg(0x260)
#define kIOMessageCanSystemSleep           IOKit_common_msg(0x270)
#define kIOMessageSystemWillSleep          IOKit_common_msg(0x280)
#define kIOMessageSystemWillNotSleep       IOKit_common_msg(0x290)
#define kIOMessageSystemHasPoweredOn       IOKit_common_msg(0x300)
#define kIOMessageSystemWillRestart        IOKit_common_msg(0x310)
#define kIOMessageSystemWillPowerOn        IOKit_common_msg(0x320)