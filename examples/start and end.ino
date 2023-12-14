#include <Arduino.h>
#include <HLS-LFCD2_lidar.h>


Lidar lidar(Serial2);

void setup() {

  Serial.begin(115200);

  Serial2.begin(230400, SERIAL_8N1, 21, 22);
  lidar.begin();

  bool started = lidar.waitForStartup();

  if(!started){
    Serial.println("Lidar not started");
    lidar.end();
    while(1);
  }


  ulong t = millis();
  while(millis() - t < 5000){
    lidar.update();
    Serial.println(lidar.rpm);
  }

  lidar.end();

}

void loop() {
}

