#include <avr/io.h>
#include <util/delay.h>
#include "dds.h"

void sendTimeCode(void);

//Datenstrom
//					MESZ			Begin Zeit		Min Einer		Min Einer	Min Zehner		Parität			Std Einer	Std Einer		Std Zehner		Parität	  	KaltagEiner 	KaltagEiner 	KaltagZehner Wotag			Wotag			MonEiner		MonEiner		MonEiner	JahrEiner		JahrEiner		JahrEiner		JahrZehner	Parität
uint64_t timeCode = (1ULL << 17) | (1ULL << 20) | (1ULL << 21) | (1ULL << 23) | (1ULL << 25) | (1ULL << 28) | (1ULL << 29) | (1ULL << 31) | (1ULL << 33) | (1ULL << 35)| (1ULL << 39) | (1ULL << 36) | (1ULL << 41) | (1ULL << 43) | (1ULL << 44) | (1ULL << 47) | (1ULL << 46) | (1ULL << 45) | (1ULL << 52) | (1ULL << 51) | (1ULL << 50) | (1ULL << 54) | (0ULL << 58);
//15:15Uhr 29.7.17

int main(void)
{
	DDRB = 0xFF;
	PORTB = 0x1;
	
	
	_delay_ms(1000);
	DDS_init();
	DDS_reset();
		
	//DDS-Modul auf 77,5kHz einstellen
	//...
	DDS_setFrequency(3580000);
	
	while(1)
	{
		sendTimeCode();
	}
	
	return 0;
}

void sendTimeCode(void)
{
	//Zeichenstrom Bit für Bit abtasten
	
	for(uint8_t bitPosition = 0; bitPosition < 64; bitPosition++)
	{
		if((timeCode & (1 << bitPosition)) == 0)
		{
			//Bit ist eine Null
			//Träger für 100ms abschwächen
			//Abschwächung durch Schalten eines Pins aktivieren für die entsprechende Zeitdauer
			PORTB = 0;
			_delay_ms(100);
			PORTB = 1;
			_delay_ms(900);
		}
		else
		{
			//Bit ist eine Eins
			//Träger für 200ms abschwächen
			PORTB = 0;
			_delay_ms(200);
			PORTB = 1;
			_delay_ms(800);
		}
		
	} 
}
