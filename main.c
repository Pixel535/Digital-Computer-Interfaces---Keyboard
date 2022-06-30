#include <REGX52.H>

//DEKLARACJA WIERSZY I KOLUMN
sbit W1=P2^0;	  //WIERSZ 1 NA PORCIE 2 I BICIE 0
sbit W2=P2^1;	  //WIERSZ 2 NA PORCIE 2 I BICIE 1
sbit K1=P2^2;	  //KOLUMNA 1 NA PORCIE 2 I BICIE 2
sbit K2=P2^3;	  //KOLUMNA 2 NA PORCIE 2 I BICIE 3

bit klaw=1;		  //ZMIENNA TYPU BIT = 1 - KIEDY NIE MA PRZERWANIA PROGRAM DZIALA W PETLI I JEST BRAK PRZERWANIA
 

void Int0(void) interrupt 0		//FUNKCJA OBSLUGI PRZERWANIA - ZMIANA WARTOSCI ZMIENNEJ KLAW
{
	klaw=0;
}

void Jaki_Klawisz_Wcisniety(void)		//FUNKCJA SPRAWDZAJACA KTORY KLAWISZ JEST WCISNIETY I W ZALEZNOSCI OD WCISNIETEGO PRZYCISKU WYSWIETLENIE JEGO WARTOSCI
{
	 switch(P2)
	 {
	 	case 0xEE: P1='0'; break;
	 	case 0xDE: P1='1'; break;
		case 0xBE: P1='2'; break;
		case 0x7E: P1='3'; break;
	 	case 0xED: P1='4'; break;
		case 0xDD: P1='5'; break;
		case 0xBD: P1='6'; break;
		case 0x7D: P1='7'; break;
		case 0xEB: P1='8'; break;
		case 0xDB: P1='9'; break;
		case 0xBB: P1='A'; break;
		case 0x7B: P1='B'; break;
		case 0xE7: P1='C'; break;
		case 0xD7: P1='D'; break;
		case 0xB7: P1='E'; break;
		case 0x77: P1='F'; break;
		default: P1=0xFF; break; 
	 }

	 
}

void main(void)
{
	P1=0x00;	 //USTAWIENIE WARTOSCI POCZATKOWEJ PORTU 1
	P2=0x7F;	 //USTAWIENIE WARTOSCI POCZATKOWEJ PORTU 2
	EA=1;		 //GLOBALNE WLACZANIE WSZYSTKICH PRZEWAN - JESLI JEST ROWNY 0 ZADNE PRZERWANIE NIE DZIALA
	EX0=1;		 //PRZERWANIE ZEWNETRZNE
	IT0=1;		 //BIT OKRESLAJACY STAN WYPROWADZENIA INT1/INT0 AKTYWUJACY PRZERWANIE - 1 TO PRZERWANIE AKTYWOWANE ZBOCZEN OPADAJACYM; 0 - PRZERWANIE AKTYWOWANE NISKIM POZIOMEM
	while(1)	 //NIESKONCZONE DZIALANIE PROGRAMU 
	{
  		while(klaw)		 //DZIALANIE PETLI DOPOKI NIE MA PRZERWANIA
  		{
	 		switch(P2)	 //ZMIANA BITOW NA WIERSZACH - PORT P2
	 		{
	  			case 0x7F: P2=0xBF; break;
	  			case 0xBF: P2=0xDF; break;
	  			case 0xDF: P2=0xEF; break;
	 			case 0xEF: P2=0x7F; break;
	 		}
  		}

  		Jaki_Klawisz_Wcisniety();	  //WYWOALAIE FUNKCJI WCISNIETYCH KLAWISZY
  		klaw=1;						  //ZMIANA WARTOSCI TYPU BIT
	}

}