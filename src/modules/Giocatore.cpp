#include "Giocatore.hpp"

Giocatore::Giocatore()
{
	lev=1;
	act=AZIONE;
	oro=0;
	exp=0;
	nextLevExp=80;
}

void Giocatore::classChosen(int sel)
{
	switch(sel)
	{
		case 0:						//Guerriero
			str=10;
			dex=10;
			con=12;
			luck=8;
			pot=5;
			equip=Arma(1,"spada");
		break;
		case 1:						//Barbaro
			str=16;
			dex=4;
			con=18;
			luck=2;
			pot=5;
			equip=Arma(1,"mazza");
		break;
		case 2:						//Ladro
			str=4;
			dex=18;
			con=8;
			luck=14;
			pot=7;
			equip=Arma(1,"pugnale");
		break;
		case 3:						//Avventuriero
		{
			str=4;
			dex=4;
			con=4;
			luck=2;
			pot=2;
			int total=39;
			int attr;
			while (total>0)
			{
				attr=(int)rand()%5;
				switch(attr)
				{
					case 0: str++;
					break;
					case 1: dex++;
					break;
					case 2: con++;
					break;
					case 3: luck++;
					break;
					case 4: pot++;
					break;
				}
				total--;
			}
			if (attr>2)
				equip=Arma(1,"mazza");
			else if (attr<2)
				equip=Arma(1,"pugnale");
			else
				equip=Arma(1,"spada");
		}
		break;

	}
	hpmax=40*lev+con*20;
	hp=hpmax;
}

int Giocatore::getOro()
{
    return oro;
}
int Giocatore::getNextExp()
{
	return nextLevExp;
}

int Giocatore::getPot()
{
    return pot;
}
void Giocatore::addPot()
{
    pot++;
}
Arma Giocatore::getInv(int n)
{
    return inventario[n];
}
void Giocatore::setInv(int n, Arma a)
{
    inventario[n]=a;
}
void Giocatore::setOro(int o)
{
    oro=o;
}
void Giocatore::addOro(int o)
{
    oro+=o;
}
void Giocatore::addExp(int e)
{
    exp+=e;
}

void Giocatore::levelup(int stat)
{
    switch(stat)
    {
    case 1:
        str+=2;
        break;
    case 2:
        dex+=2;
        break;
    case 3:
        con+=2;
        hpmax+=40;
        break;
    case 4:
        luck+=2;
        break;
    }
    hpmax+=40;
    hp=hpmax;
    lev++;
    exp=exp-nextLevExp;
    nextLevExp=80+(int)(nextLevExp*lev*0.5);
}

int Giocatore::cambioArma(int pos)
{
    int cambiato=-1;
    if (inventario[pos].isAvailable())
    {
        if (inventario[pos].getStrMin()<=str)
		{
			if(inventario[pos].getDexMin()<=dex)
			{
				cambiato=0;
				Arma temp=equip;
				equip=inventario[pos];
				inventario[pos]=temp;
			}
			else
				cambiato=2;
		}
		else
			cambiato=1;
    }
	return cambiato;
}

void Giocatore::scartaArma(int pos)
{
    inventario[pos].scarta();
}

void Giocatore::vendiArma(int pos)
{
	oro+=inventario[pos].getPrezzo();
	inventario[pos].scarta();
}
int Giocatore::libInventario(){
	int pos=-1;
	int i=0;
	while ((pos==-1) && (i<MAX_ITEM)){
		if (!getInv(i).isAvailable())
			pos=i;
		i++;
	}
	return pos;
}


int Giocatore::usaPozione()
{
    int recuperato=-1;
    if (pot>0)
    {
        pot--;
        act--;
        recuperato=(20+5*lev);
        hp+=recuperato;
        if (hp>hpmax)
		{
			recuperato=hpmax-(hp-recuperato);
			hp=hpmax;
		}
    }
    return recuperato;
}
