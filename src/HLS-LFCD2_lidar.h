#ifndef LIDAR_H
#define LIDAR_H

#include <Arduino.h>

#define BLOCK_SIZE 42
#define LIDAR_TIME_OUT 5000

struct rawBlock_type {
  byte bytes[BLOCK_SIZE];
};

struct dataBlock_type {
  int rpm;
  uint16_t intensity[6];
  uint16_t dist[6];
};

struct lidarData_type {
  uint16_t rpm;
  uint16_t intensity[360];
  uint16_t dist[360];
};



class Lidar{

    public:

    Lidar(Stream &serial);
    
    void begin();
    void end();
    bool update();
    bool isRunning();
    bool waitForStartup();

    lidarData_type getData();


    dataBlock_type sensorData[60];// this array holds the date of a full revolution
                                  // 60 blocks of 6 measurments each
    lidarData_type lidarData;  // holds the information of a full revolution
    Stream *_serial;

    uint16_t rpm;

    private:

    ulong startTime;

    void updateLidarData();
    bool checksum(rawBlock_type &rawBlock);

};




#endif