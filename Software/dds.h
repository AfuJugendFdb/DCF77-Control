//#ifndef _DDS_H_
//#define _DDS_H_

#define DDS_DDR		DDRD
#define DDS_Port	PORTD
#define RST		7	//DDS Reset
#define FQ		6	//DDS Frequency Update
#define CLK		5	//DDS Clock (für serielle Übertragung)
#define DATA	4	//Serielle Datenleitung für den DDS

//Prototypen
void DDS_init(void);
void pulseHigh(uint8_t pin);
void DDS_reset(void);
void DDS_setFrequency(double frequency);
void DDS_sendData(uint8_t c);

//#endif
