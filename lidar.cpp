#include <lidar.h>


block blocks[60];
dataBlock sensorData[60];

Lidar::Lidar(Stream &serial){
    _serial = &serial;

}




void Lidar::begin(){
    (*_serial).write('b');
} 

void Lidar::end(){
    (*_serial).write('e');
}


bool Lidar::update(){

    if((*_serial).available() < BLOCK_SIZE){
        return true;
    }

    if ((*_serial).peek() != 0xFA){
        while ( (*_serial).peek() != 0xFA ){ (*_serial).read(); }
    }

    (*_serial).readBytes(blocks[0].bytes, BLOCK_SIZE);

    

    int angleIndex = blocks[0].bytes[1] - 0xA0;  // a

    sensorData[angleIndex].rpm = blocks[0].bytes[2] + (blocks[0].bytes[3] << 8); // get rpm
    

    uint16_t *intensPtr = &sensorData[angleIndex].intensity[0];
    uint16_t *distPtr = &sensorData[angleIndex].dist[0];

    for (int i = 4; i < 40; i += 6){
        *intensPtr++ = blocks[0].bytes[i] + (blocks[0].bytes[i + 1] << 8);

        *distPtr++ = blocks[0].bytes[i + 2] + (blocks[0].bytes[i + 3] << 8);

    }


    return true;
}


dataBlock Lidar::getData(){
    return sensorData[0];
}


block Lidar::getBlock(){
    return blocks[0];
}