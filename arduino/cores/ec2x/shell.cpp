#include "shell.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

String systemCommand(String command) {
    return systemCommand(command.c_str());
}

String systemCommand(const char* command) {
  FILE *fp;

  /* Open the command for reading. */
  fp = popen(command, "r");
  if (fp == NULL) {
    printf("Failed to run command\n" );
    exit(1);
  }

  char path[1024];
  String ret = "";
  /* Read the output a line at a time - output it. */
  while (fgets(path, sizeof(path)-1, fp) != NULL) {
    ret += path;
  }

  ret.trim();

  /* close */
  pclose(fp);

  return ret;
}

int setGovernor(const char* governor, int cpu) {
  char cmd[1024];
  snprintf(cmd, sizeof(cmd), "echo %s > /sys/devices/system/cpu/cpu%d/cpufreq/scaling_governor", governor, cpu);
  return system(cmd);
}

void goPowerSave() {
  setGovernor("powersave", 0);
}

void goPerformance() {
  setGovernor("performance", 0);
}

void goOndemand() {
  setGovernor("ondemand", 0);
}

String getTime() {
  return systemCommand("date +\%H:\%M:\%S");
}

String getDate() {
  return systemCommand("date +\%d/\%m/\%y");
}