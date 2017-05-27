/****************************************************************
* Ansteuerung des DDS-Moduls AD9850
* Portierung des Arduino-Codes von Matthias Busse, http://www.nmea.de/schaltung/sch-dds9850.html
*****************************************************************/

#include <avr/io.h>
#include "dds.h"

//Example for usage
// int example_main()
// {
//	 DDS_init();
//	 DDS_reset();
//	
//	 DDS_setFrequency(14318000);
//	
//	 while(1)
//	 {		
//	 }
//	
//	 return 0;
//}

//Funktionen

void DDS_init(void)
{
	DDS_DDR = 0xFF; //Alles Ausgänge, hier der gesamte Port
	DDS_Port = 0x00; //Alle Pins auf low setzen
}

void pulseHigh(uint8_t pin)
{
	DDS_Port |= (1<<pin); //Pin auf High setzen
	for(volatile uint8_t i = 0; i < 8; i++) {} //Etwas tun, um wegoptimieren zu verhindern
	DDS_Port &= ~(1<<pin); //Pin auf low setzen
}

void DDS_reset(void)
{
	pulseHigh(RST);
	pulseHigh(CLK);
	pulseHigh(FQ);
}

void DDS_setFrequency(double frequency)
{
	frequency = frequency/1000000*4294967295/125; //frequency/34359738360000 // für 125MHz-Quarz
	long int y = frequency;
	//Frequenz byteweise übertragen
	DDS_sendData(y); //Low-Byte der Frequenz übertragen (w4)
	DDS_sendData(y>>8); //w3
	DDS_sendData(y>>16); //w2
	DDS_sendData(y>>24); //High-Byte der Frequenz übertragen (w1)
	DDS_sendData(0x00); //Keine Phase
	pulseHigh(FQ); //Frequenz/Schieberegister-Inhalt übernehmen
}

void DDS_sendData(uint8_t c)
{
	for(uint8_t i = 0; i < 8; i++) {
		uint8_t out = (c>>i) & 0x01; //Byte seriell übertragen: um i-te Stelle nach rechts shiften und LSB ausmaskieren
		DDS_Port = (out << DATA); //out hat Information an LSB-Stelle --> auf DATA-Pin-Stelle shiften und ausgeben
		pulseHigh(CLK); //Schieberegister weiterschieben
	}
}
