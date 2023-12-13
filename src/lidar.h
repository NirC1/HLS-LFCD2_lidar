#ifndef LIDAR_H
#define LIDAR_H

#include <Arduino.h>

#define BLOCK_SIZE 42

struct rawBlock_type {
  byte bytes[BLOCK_SIZE];
};

struct dataBlock_type {
  int rpm;
  uint16_t intensity[6];
  uint16_t dist[6];
};

struct lidarData_type {
  int rpm;
  uint16_t intensity[360];
  uint16_t dist[360];
};



class Lidar{

    public:

    Lidar(Stream &serial);
    
    void begin();
    void end();
    bool update();

    lidarData_type getData();

    bool checkSum(rawBlock_type &rawBlock);

    dataBlock_type sensorData[60];// this array holds the date of a full revolution
                                  // 60 blocks of 6 measurments each
    lidarData_type lidarData;  // holds the information of a full revolution
    Stream *_serial;

    private:

    void updateLidarData();

};




#endif