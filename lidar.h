#ifndef LIDAR_H
#define LIDAR_H

#include <Arduino.h>


#define BLOCK_SIZE 42

struct rawBlock_type{
  byte bytes[BLOCK_SIZE];
};


struct dataBlock{
  int rpm;
  uint16_t intensity[6];
  uint16_t dist[6];
};


class Lidar{

    public:

    Lidar(Stream &serial);
    
    void begin();
    void end();
    bool update();

    dataBlock getData();

    bool checkSum(rawBlock_type &rawBlock);



    Stream *_serial;

};




#endif