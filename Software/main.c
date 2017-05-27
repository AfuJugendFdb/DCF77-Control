#include <avr/io.h>
#include "dds.h"

#define TIMECODE_LENGTH 1	//Länge des Zeichenstroms anpassen

void sendTimeCode(void);

//Feld anlegen, indem der auszusendende Datenstrom abgelegt ist
//Achtung: wir schreiben Bits, der kleinste Datentyp ist 1 Byte (uint8_t)
//--> Wie viele Bits umfasst unser Datenstrom, und wie viele Bytes brauchen wir dafür?

uint8_t timeCode[TIMECODE_LENGTH] = {	/* ... */	};

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
	
	for(uint8_t i = 0; i < TIMECODE_LENGTH; i++)
	{
		for(uint8_t bitPosition = 0; bitPosition < 8; bitPosition++)
		{
			if((timeCode[i] & (1 << bitPosition)) == 0)
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
}
