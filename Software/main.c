#include <avr/io.h>
#include "dds.h"

void sendTimeCode(void);

//Datenstrom
uint64_t timeCode = 0x0000000000000000;

int main(void)
{
	DDS_init();
	DDS_reset();
		
	//DDS-Modul auf 77,5kHz einstellen
	//...
	
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

		}
		else
		{
			//Bit ist eine Eins
			//Träger für 200ms abschwächen
		}
		
		//verbleibende Zeit bis zum Ende der Sekunde warten.
	} 
}
