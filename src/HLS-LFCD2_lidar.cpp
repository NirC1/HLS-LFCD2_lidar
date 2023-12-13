#include "HLS-LFCD2_lidar.h"

#ifdef DEBUG
    #define _PL(x) Serial.println(x)
    #define _PP(x) Serial.print(x)
#else
    #define _PL(x)
    #define _PP(x)
#endif


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
     

    if((*_serial).available() < BLOCK_SIZE){  // return immedietly if there's not enough bytes
        return false;
    }

    if ((*_serial).peek() != 0xFA){
        while ( (*_serial).peek() != 0xFA ){ (*_serial).read(); }
    }

    rawBlock_type rawBlock;  // holds the raw data

    (*_serial).readBytes(rawBlock.bytes, BLOCK_SIZE); // read

    if(!checkSum(rawBlock)){
        return false;
    }


    int angleIndex = rawBlock.bytes[1] - 0xA0;  // angle index range is 0xA0 to 0xDB  - (0-60)


    if (angleIndex == 0){  // if we got a full revolution 
        updateLidarData();
    }
    

    sensorData[angleIndex].rpm = rawBlock.bytes[2] + (rawBlock.bytes[3] << 8); // get rpm
    

    uint16_t *intensPtr = &sensorData[angleIndex].intensity[0];
    uint16_t *distPtr   = &sensorData[angleIndex].dist[0];

    /*
    ------------------
    |intensity |low  |
    |intensity |high |
    |dist      |low  |
    |dist      |high |
    |reserved  |low  |
    |reserved  |high |
    */
    for (int i = 4; i < 40; i += 6){
        *intensPtr++ = rawBlock.bytes[i] + (rawBlock.bytes[i + 1] << 8);

        *distPtr++ = rawBlock.bytes[i + 2] + (rawBlock.bytes[i + 3] << 8);

    }

    return true;
}


lidarData_type Lidar::getData(){
    return lidarData;
}


bool Lidar::checkSum(rawBlock_type &rawBlock) 
{
    byte sum = 0;
    for (int i = 0; i <= 39; i++)
    {
        /* code */
        sum += rawBlock.bytes[i];
    }

    _PP("ff - sum: ");
    sum = 0xFF - sum;
    _PL(sum);

    _PP("40: ");
    _PL(rawBlock.bytes[40]);

    _PP("41: ");
    _PL(rawBlock.bytes[41]);

    return sum == rawBlock.bytes[40] || sum == rawBlock.bytes[41];
    
}

/**
 * @brief updates the lidarData struct with the data from the sensorData array
*/
void Lidar::updateLidarData()
{
    for (int i = 0; i < 60; i++)
    {
        /* code */
        for (int j = 0; j < 6; j++)
        {
            /* code */
            lidarData.intensity[i * 6 + j] = sensorData[i].intensity[j];
            lidarData.dist[i * 6 + j] = sensorData[i].dist[j];
        }
        
    } 
}
