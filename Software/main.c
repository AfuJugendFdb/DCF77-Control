#include <avr/io.h>
#include <util/delay.h>
#include "dds.h"

#define TX_Frequency 77500

void sendTimeCode(uint64_t code);

//Datenstrom
//					MESZ			Begin Zeit		Min Einer		Min Einer	Min Zehner		Parität			Std Einer	Std Einer		Std Zehner		Parität	  	KaltagEiner 	KaltagEiner 	KaltagZehner Wotag			Wotag			MonEiner		MonEiner		MonEiner	JahrEiner		JahrEiner		JahrEiner		JahrZehner	Parität
//uint64_t timeCode = (1ULL << 17) | (1ULL << 20) | (1ULL << 21) | (1ULL << 23) | (1ULL << 25) | (1ULL << 28) | (1ULL << 29) | (1ULL << 31) | (1ULL << 33) | (1ULL << 35)| (1ULL << 39) | (1ULL << 36) | (1ULL << 41) | (1ULL << 43) | (1ULL << 44) | (1ULL << 47) | (1ULL << 46) | (1ULL << 45) | (1ULL << 52) | (1ULL << 51) | (1ULL << 50) | (1ULL << 54) | (0ULL << 58);
//15:15Uhr 29.7.17
//uint8_t timeCode = 0xF0;

//22:11 Uhr, DO 27.7.2017
uint64_t timeCode1 = 0b01010000000101100100110001000010001011100100111100111010000;
uint64_t timeCode2 = 0b01010000000101100100101001000010001011100100111100111010000;
uint64_t timeCode3 = 0b01010000000101100100111001000010001011100100111100111010000;
uint64_t timeCode4 = 0b01010000000101100100100101000010001011100100111100111010000;

//28:11 Uhr, DO 27.7.2017
uint64_t timeCode5 = 0b01010000000101100100110001000000101011100100111100111010000;
uint64_t timeCode6 = 0b01010000000101100100101001000000101011100100111100111010000;
uint64_t timeCode7 = 0b01010000000101100100111001000000101011100100111100111010000;
uint64_t timeCode8 = 0b01010000000101100100100101000000101011100100111100111010000;

//22:11 Uhr, DO 37.7.2017
uint64_t timeCode9 = 0b01010000000101100100110001000010001011101100111100111010001;
uint64_t timeCode10 = 0b01010000000101100100101001000010001011101100111100111010001;
uint64_t timeCode11 = 0b01010000000101100100111001000010001011101100111100111010001;
uint64_t timeCode12 = 0b01010000000101100100100101000010001011101100111100111010001;



int main(void)
{
	DDRB = 0xFF;
	PORTB = 0x1;
	
	
	_delay_ms(1000);
	DDS_init();
	DDS_reset();
		
	//DDS-Modul auf 77,5kHz einstellen
	//...
	DDS_setFrequency(TX_Frequency);
	
	while(1)
	{
		sendTimeCode(timeCode9);
		sendTimeCode(timeCode10);
		sendTimeCode(timeCode11);
		sendTimeCode(timeCode12);
	}
	
	return 0;
}

void sendTimeCode(uint64_t code)
{
	//Zeichenstrom Bit für Bit abtasten
	for(int8_t bitPosition = 58; bitPosition >= 0; bitPosition--)
	{
		if((code & (1ULL << bitPosition)) == 0)
		{
			//Bit ist eine Null
			//Träger für 100ms abschwächen
			//Abschwächung durch Schalten eines Pins aktivieren für die entsprechende Zeitdauer
			DDS_setFrequency(10);
			_delay_ms(99);
			DDS_setFrequency(TX_Frequency);
			_delay_ms(899);
		}
		else
		{
			//Bit ist eine Eins
			//Träger für 200ms abschwächen
			DDS_setFrequency(10);
			_delay_ms(199);
			DDS_setFrequency(TX_Frequency);
			_delay_ms(799);
		}
	} 
	//59. Bit: Dauerton
	_delay_ms(999);
}
