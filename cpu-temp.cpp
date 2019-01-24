
#include <stdio.h>
#include "cpu-temp.h"


const char *cpu_temp::sensors[] = {
  "/sys/devices/system/cpu/cpu0/cpufreq/cpu_temp",
  "/sys/devices/system/cpu/cpu0/cpufreq/FakeShmoo_cpu_temp",
  "/sys/class/thermal/thermal_zone1/temp",
  "/sys/class/i2c-adapter/i2c-4/4-004c/temperature",
  "/sys/devices/platform/tegra-i2c.3/i2c-4/4-004c/temperature",
  "/sys/devices/platform/omap/omap_temp_sensor.0/temperature",
  "/sys/devices/platform/tegra_tmon/temp1_input",
  "/sys/kernel/debug/tegra_thermal/temp_tj",
  "/sys/devices/platform/s5p-tmu/temperature",
  "/sys/class/thermal/thermal_zone0/temp",
  "/sys/devices/virtual/thermal/thermal_zone0/temp",
  "/sys/class/hwmon/hwmon0/temp1_input",
  "/sys/devices/virtual/thermal/thermal_zone1/temp",
  "/sys/devices/platform/s5p-tmu/curr_temp"
};

cpu_temp::cpu_temp(){
  this->status = false;
  this->sensor_n = 0;
  this->findSensor();
}

cpu_temp::~cpu_temp(){
}

void cpu_temp::findSensor(){
  FILE * fd;
  this->status = false;
  for (unsigned int n = 0; n < sizeof(cpu_temp::sensors) / sizeof(*cpu_temp::sensors); n++){
    fd = fopen (cpu_temp::sensors[n], "r");
    if (fd != NULL){
      this->sensor_n = n;
      this->status = true;
      fclose(fd);
      break;
    }
  }
}

float cpu_temp::getTemp(){
  float res = 0;
  FILE * fd;
  char buff[8];
  this->status = false;
  fd = fopen (cpu_temp::sensors[this->sensor_n], "r");
  if (fd != NULL){
    fgets(buff, 8, fd);
    fclose(fd);
  }
  sscanf(buff, "%f", &res);
  res = res / 1000;
  if (res != 0) this->status = true;
  return res;
}

bool cpu_temp::getStatus(){
  return this->status;
}
