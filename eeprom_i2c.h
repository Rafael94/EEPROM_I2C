// eeprom.h
#ifndef EEPROM_I2C_h
#define EEPROM_I2C_h



#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#ifndef TwoWire_h
	#include "Wire.h"
#endif

struct sEEPROMdataByte {
		unsigned int blockAddress;
		byte data;
};
struct sEEPROMdataUint {
		unsigned int blockAddress;
		unsigned int data;
};
struct sEEPROMdataBoolean {
		unsigned int blockAddress;
		boolean data;
};

class eeprom_i2c {
private:
	int deviceaddress;
public:
	
	eeprom_i2c(int ideviceaddress);
	//write
	//ArrayWrite
	void write( sEEPROMdataBoolean  _sEEPROMdataBoolean[], unsigned int size);
	void write( sEEPROMdataByte _sEEPROMdataByte[], unsigned int size);
	void write( sEEPROMdataUint _sEEPROMdataUint[], unsigned int size);
	void write( unsigned int blockAddressStart,  char data[], byte size);
	//Single Write
	void write( unsigned int blockAddress, byte data );
	void write( unsigned int blockAddress,  bool data);
	void write( unsigned int blockAddressStart,  unsigned int data);
	//read
	//array read
	void read( sEEPROMdataBoolean  _sEEPROMdataBoolean[], unsigned int size);
	void read( sEEPROMdataByte _sEEPROMdataByte[], unsigned int size);
	void read( sEEPROMdataUint _sEEPROMdataUint[], unsigned int size);
	void read( unsigned int blockAddress, char data[], byte size);
	//single Read
	void read( unsigned int blockAddress, byte &data);
	void read( unsigned int blockAddress, bool &data);
	void read( unsigned int blockAddress, unsigned int &data);
	
};

#endif