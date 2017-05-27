//#ifndef _DDS_H_
//#define _DDS_H_

#define DDS_DDR		DDRB
#define DDS_Port	PORTB
#define RST		0	//DDS Reset
#define FQ		1	//DDS Frequency Update
#define CLK		2	//DDS Clock (für serielle Übertragung)
#define DATA	3	//Serielle Datenleitung für den DDS

//Prototypen
void DDS_init(void);
void pulseHigh(uint8_t pin);
void DDS_reset(void);
void DDS_setFrequency(double frequency);
void DDS_sendData(uint8_t c);

//#endif
