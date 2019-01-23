
#ifndef __CPU_TEMP_H__
#define __CPU_TEMP_H__

class cpu_temp {
  public:
    cpu_temp();
    ~cpu_temp();
    float getTemp();
    bool getStatus();
  private:
    bool status;
    unsigned int sensor_n;
    static const char *sensors[];
    void findSensor();
};

#endif // __CPU_TEMP_H__
