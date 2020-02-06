class MHZ14A
{
  public:
  MHZ14A(HardwareSerial* serial)
  {
    this->serial=serial;
//    serial.begin(baudrate);
    delay(100);
  };
  int read()
  {
    int i=0;
    uint8_t response[9]={};
    int result=0;
    serial->write(cmd_read,9);
    while(serial->available()>0)
    {
      response[i++]=serial->read();
    }
    i=0;
    result+=(uint16_t)response[2]<<8;
    result+=response[3];
    
    return result;
  };
  void debug(uint8_t response[])
  {
    int i=0;
    serial->write(cmd_read,9);
    while(serial->available()>0&&i<9)
    {
      response[i++]=serial->read();
    }
    
  };
  void calibrate()
  {
    serial->write(cmd_calibrate_zero,9);
    
  };
  private:
  HardwareSerial* serial;
  int baudrate=9600;
  uint8_t cmd_read[9]={0xff,0x01,0x86,0x00,0x00,0x00,0x00,0x00,0x79};
  uint8_t cmd_calibrate_zero[9]={0xff,0x01,0x87,0x00,0x00,0x00,0x00,0x00,0x78};
  uint8_t cmd_calibrate_span[9]={0xff,0x01,0x88,0x07,0x00,0x00,0x00,0x00,0xA0};
  int time_preheat=3*60*1000;//3min
};
