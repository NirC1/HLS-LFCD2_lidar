#ifndef LIDAR_H
#define LIDAR_H

#include <Arduino.h>


#define BLOCK_SIZE 42

struct block{
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
    block getBlock();



    Stream *_serial;

};




#endif