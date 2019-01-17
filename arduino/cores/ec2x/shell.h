#include "WString.h"

#ifdef __cplusplus

String systemCommand(String command);

String systemCommand(char* command);

void goPowerSave();

void goPerformance();

void goOndemand();

int setGovernor(char* governor, int cpu = 0);

String getDate();

String getTime();

#endif