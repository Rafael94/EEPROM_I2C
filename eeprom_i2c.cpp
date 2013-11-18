
#include "eeprom_i2c.h"
#include "Arduino.h"

/// <summary>
/// Initialised the EEPROM Object with the EEPROM Adress
/// </summary>
/// <param name="ideviceaddress">I2C Adress</param>
/// 
eeprom_i2c::eeprom_i2c(int ideviceaddress){
	this->deviceaddress = ideviceaddress;
}

/// <summary>
//	Write Data(Byte) to the eeprom(Array Write)	
/// </summary>
/// <param name="_sEEPROMdataByte">Structur of sEEPROMdataByte with Items</param>
/// <param name="size">Size/Items from _sEEPROMdataByte[]</param>
///
void eeprom_i2c::write(sEEPROMdataByte _sEEPROMdataByte[], unsigned int size) {
	for(byte i=0; i<size;i++){
		this->write(_sEEPROMdataByte[i].blockAddress, _sEEPROMdataByte[i].data);
	}
	
}

/// <summary>
//	Write Data(Boolean) to the eeprom(Array Write)	
/// </summary>
/// <param name="_sEEPROMdataBoolean">Structur of sEEPROMdataBoolean with Items</param>
/// <param name="size">Size/Items from _sEEPROMdataBoolean[]</param>
///
void eeprom_i2c::write(sEEPROMdataBoolean _sEEPROMdataBoolean[], unsigned int size) {
	for(byte i=0; i<size;i++){
		this->write(_sEEPROMdataBoolean[i].blockAddress, _sEEPROMdataBoolean[i].data);
	}
	
}

/// <summary>
//	Write Data(uunsigned Int) to the eeprom(Array Write)	
/// </summary>
/// <param name="_sEEPROMdataUint">Structur of sEEPROMdataUint with Items</param>
/// <param name="size">Size/Items from _sEEPROMdataUint[]</param>
///
void eeprom_i2c::write(sEEPROMdataUint _sEEPROMdataUint[], unsigned int size) {
	for(byte i=0; i<size;i++){
		this->write(_sEEPROMdataUint[i].blockAddress, _sEEPROMdataUint[i].data);
	}	
}

/// <summary>
//	Write Data(Byte) to the eeprom(Single Write)	
/// </summary>
/// <param name="blockAddress">Adress of the the Block</param>
/// <param name="data">Data</param>
///
void eeprom_i2c::write(unsigned int blockAddress, byte data ) {
	 Wire.beginTransmission(deviceaddress);
	 Wire.write(blockAddress);
	 Wire.write(data);
	 Wire.endTransmission();
	 delay(200);
}

/// <summary>
//	Write Data(char) to the eeprom(Array Write)	
/// </summary>
/// <param name="blockAddress">Adress of the the Block</param>
/// <param name="data">Char Array</param>
/// <param name="size">Size of the Char Array</param>
void eeprom_i2c::write(unsigned int blockAddress, char data[], byte size ) {
	 Wire.beginTransmission(deviceaddress);
	 Wire.write(blockAddress);
	 for(int i=0; i<size; i++) {
		Wire.write(data[i]);
	 }
	
	 Wire.endTransmission();
	 delay(200);
}

/// <summary>
//	Write Data(unsigned Int) to the eeprom(Single Write)	
/// </summary>
/// <param name="blockAddressStart">Adress of the the Block</param>
/// <param name="data">Data</param>
///
void eeprom_i2c::write(unsigned int blockAddressStart,  unsigned int data) {
    byte lowByte = (data & 0xFF);
    byte highByte = ((data >> 8) & 0xFF);
    Wire.beginTransmission(deviceaddress);
    Wire.write(blockAddressStart); 
	Wire.write(lowByte);
	Wire.write(highByte);
    Wire.endTransmission();
	delay(200);
}

/// <summary>
//	Write Data(Boolean) to the eeprom(Single Write)	
/// </summary>
/// <param name="blockAddress">Adress of the the Block</param>
/// <param name="data">Data</param>
///
void eeprom_i2c::write( unsigned int blockAddress, bool data ) {
	 Wire.beginTransmission(deviceaddress);
	 Wire.write(blockAddress);
	 Wire.write(data);
	 Wire.endTransmission();
	 delay(200);
}

/// <summary>
//	Read Data(Byte) from the eeprom(Single Read)	
/// </summary>
/// <param name="blockAddress">Adress of the the Block</param>
/// <param name="data">Data</param>
///
void eeprom_i2c::read(unsigned int blockAddress, byte &data) {
    Wire.beginTransmission(deviceaddress);
	Wire.write(blockAddress);
	Wire.endTransmission();
	Wire.requestFrom(blockAddress, 1);
	if(Wire.available()) {
		data = Wire.read();
	}
	Wire.endTransmission();
	delay(200);
}

/// <summary>
//	Read Data(unsigned Int) from the eeprom(Single Read)	
/// </summary>
/// <param name="blockAddressStart">Adress of the the Block</param>
/// <param name="data">Data</param>
///
void eeprom_i2c::read( unsigned int blockAddressStart, unsigned int &data) {
   
	Wire.beginTransmission(deviceaddress);
    Wire.write(blockAddressStart); // MSB
	Wire.endTransmission();
    Wire.requestFrom(blockAddressStart,2);
	if(Wire.available()) data = (unsigned int)Wire.read();
	if(Wire.available()) data |= (((unsigned int)Wire.read()) << 8);
	delay(200);
 }

/// <summary>
//	Read Data(Boolean) from the eeprom(Single Read)	
/// </summary>
/// <param name="blockAddress">Adress of the the Block</param>
/// <param name="data">Data</param>
///
void eeprom_i2c::read(unsigned int blockAddress, bool &data) {
	Wire.beginTransmission(deviceaddress);
	Wire.write(blockAddress);
	 Wire.endTransmission();
	Wire.requestFrom(blockAddress, 1);
	if(Wire.available()) {
		data = bool (Wire.read());
	}
	Wire.endTransmission();
	delay(200);
 }

/// <summary>
//	Read Data(char) to the eeprom(Array Write)	
/// </summary>
/// <param name="blockAddress">Adress of the the Block</param>
/// <param name="data">Char Array</param>
/// <param name="size">Size of the Char Array</param>
void eeprom_i2c::read(unsigned int blockAddress, char data[], byte size) {
	Wire.beginTransmission(deviceaddress);
	Wire.write(blockAddress);
	 Wire.endTransmission();
	Wire.requestFrom(blockAddress, size);
	if(Wire.available()) {
		for(int i=0; i<size; i++) {
			data[i] = (char) Wire.read();
		}
	}
	Wire.endTransmission();
}

/// <summary>
//	Read Data(Byte) to the eeprom(Array Write)	
/// </summary>
/// <param name="_sEEPROMdataByte">Structur of sEEPROMdataByte without Items. The Structur have to initalised with the right Number of Items before this Function is call.</param>
/// <param name="size">Size/Items from _sEEPROMdataByte[]</param>
///
void eeprom_i2c::read(sEEPROMdataByte _sEEPROMdataByte[], unsigned int size) {
	for(byte i=0; i<size;i++){
		this->read(_sEEPROMdataByte[i].blockAddress, _sEEPROMdataByte[i].data);
	}
	
}

/// <summary>
//	Read Data(Boolean) to the eeprom(Array Write)	
/// </summary>
/// <param name="_sEEPROMdataBoolean">Structur of sEEPROMdataBoolean without Items. The Structur have to initalised with the right Number of Items before this Function is call.</param>
/// <param name="size">Size/Items from _sEEPROMdataBoolean[]</param>
///
void eeprom_i2c::read(sEEPROMdataBoolean _sEEPROMdataBoolean[], unsigned int size) {
	for(byte i=0; i<size;i++){
		this->read(_sEEPROMdataBoolean[i].blockAddress, _sEEPROMdataBoolean[i].data);
	}
	
}

/// <summary>
//	Read Data(unsigned Int) to the eeprom(Array Write)	
/// </summary>
/// <param name="_sEEPROMdataUint">Structur of sEEPROMdataUint without Items. The Structur have to initalised with the right Number of Items before this Function is call.</param>
/// <param name="size">Size/Items from _sEEPROMdataUint[]</param>
///
void eeprom_i2c::read(sEEPROMdataUint _sEEPROMdataUint[], unsigned int size) {
	for(byte i=0; i<size;i++){
		this->read(_sEEPROMdataUint[i].blockAddress, _sEEPROMdataUint[i].data);
	}
	
}