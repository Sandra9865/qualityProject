#include <iostream>

#include "ground.h"
#include "position.h"
#include "groundElement.h"
#include "character.h"
#include "monster.h"
#include "smartMonster.h"
#include "blindMonster.h"
#include "adventurer.h"
#include "wall.h"
#include "amulet.h"
#include "outside.h"
#include <memory>
#include "door.h"
#include "viewManager.h"
#include <fstream>



using std::cout;
using std::cin;
using std::ifstream;


ground::ground(){}

ground::ground(int nbl,int nbc):d_nbLines{nbl},d_nbColumns{nbc}{}


int ground::getNbColumns() const
{
    return d_nbColumns;
}
int ground::getNbLines() const
{
    return d_nbLines;
}

int ground::getNbTotalElmts() const
{
    return d_groundElementsTab.size();
}


void ground::setSize(int length,int width) 
{
    d_nbColumns = length;  
    d_nbLines = width;     
} 

void ground::addElementToGround(std::unique_ptr<groundElement> element)
{
    d_groundElementsTab.push_back(std::move(element));
}



void ground::removeElement(int indice)
{
    d_groundElementsTab.erase(d_groundElementsTab.begin() + indice);
}

void ground::buildGround()   //creer un terrain manuellement
{
    cout<<"\n ----- MANUALLY GENERATION FIELD -------\n";

    int c,li;
    do{
        cout<<"Enter a number of columns : \n"; cin>>c;  
        cout<<"Enter a numer of lines : "; cin>>li;  
    }
    while(c<=0 || li<=0);

    d_nbColumns=c;
    d_nbLines=li;

    char l;
    setSize(d_nbColumns,d_nbLines);
    
    cout<<"\n Code :\nS= a smart monster \nB = a blind monster \nW= a wall \nE= empty case\nA= Amulet\nD = door\nO = Outside\nP=Player\n";

    for(int i=0; i<d_nbLines;i++) 
    {
        for(int j=0;j<d_nbColumns;j++) 
        {
            do{
                cout<<"Enter a caracter for the position "<<i<<","<<j<<":";
                cin >>l;
            }while (!(l=='S' || l=='B' || l=='W'|| l=='E'||l=='A'|| l=='P' || l=='D'||l=='O'));

            position pos{i,j};

            if(l=='S') //Monstre voyant a la case [i][j]
            {
                auto p = std::make_unique<smartMonster>(pos);
                addElementToGround(std::move(p));
            }
            else if(l=='B') //Monstre aveugle à la case [i][j]
            {
                auto p = std::make_unique<blindMonster>(pos);
                addElementToGround(std::move(p));
            }
            else if(l=='W') //Mur a la case [i][j]
            {
                auto p = std::make_unique<wall>(pos);
                addElementToGround(std::move(p));
            }
            else if(l=='A') //Amulette à la case [i][j]
            {
                auto p = std::make_unique<amulet>(pos);
                addElementToGround(std::move(p));            
            }
            else if(l=='P') //Personnage
            {
                auto p = std::make_unique<adventurer>(pos);
                addElementToGround(std::move(p));
            }
            else if(l=='D') //Porte
            {
                auto p = std::make_unique<door>(pos);
                addElementToGround(std::move(p));
            }
            else if(l=='O')
            {
                auto p = std::make_unique<outside>(pos);
                addElementToGround(std::move(p));
            }
        }
    }
}

void ground::importGround(std::istream &ist)  
{
    
    int nbcol, nbl;
    char elem;

    ist>>nbl>>nbcol;
    

        int cptl=0; 
        int cptc=0;
        setSize(nbl,nbcol);

        while(!ist.eof() && cptl<d_nbLines && cptc<d_nbColumns)
        {
            position pos{cptl,cptc};
            ist>>elem;

            if(elem=='S') //Monstre voyant a la case [i][j]
            {
                auto p = std::make_unique<smartMonster>(pos);
                addElementToGround(std::move(p));
            }
            else if(elem=='B') //Monstre aveugle à la case [i][j]
            {
                auto p = std::make_unique<blindMonster>(pos);
                addElementToGround(std::move(p));
            }
            else if(elem=='W') //Mur a la case [i][j]
            {
                auto p = std::make_unique<wall>(pos);
                addElementToGround(std::move(p));
            }
            else if(elem=='A') //Amulette à la case [i][j]
            {
                auto p = std::make_unique<amulet>(pos);
                addElementToGround(std::move(p));  
          
            }
            else if(elem=='P') //Personnage
            {
                auto p = std::make_unique<adventurer>(pos);
                addElementToGround(std::move(p));

            }
            else if(elem=='D') //Porte
            {
                auto p = std::make_unique<door>(pos);
                addElementToGround(std::move(p));
            }
            else if(elem=='O') //Dehors
            {
                auto p = std::make_unique<outside>(pos);
                addElementToGround(std::move(p));
            }

            cptc++;

            if(cptc==nbcol)
            {
                cptc=0;
                cptl++;
            }

        }


    }
    
char  ground::typeOf(int indice) const
{
   
    auto e= d_groundElementsTab[indice].get();
    char t;

    if(indice==-1)  
    {
        t= 'E';
    }
    else if(dynamic_cast<blindMonster*>(e))
    {
        t= 'B';
    }
    else if(dynamic_cast<amulet*>(e))
    {
        t= 'A';
    }
    else if(dynamic_cast<adventurer*>(e))
    {
        t= 'P';
    }
    else if(dynamic_cast<smartMonster*>(e))
    {
        t= 'S';
    }
    else if(dynamic_cast<wall*>(e))
    {
        t= 'W';
    }
    else if(dynamic_cast<door*>(e))
    {
        t='D';
    }
    else if(dynamic_cast<outside*>(e))
    {
        t='O';
    }
    return t;

}

std::vector<int> ground::getIndicePos(const position &p) const
{
    int indice=0;
    position pos;
    std::vector<int>T;

    for(const auto &elem : d_groundElementsTab)
    {
        pos = elem->getPosition();

        if( (pos.getColumn()==p.getColumn()) && (pos.getLine()==p.getLine()))
        {
            T.push_back(indice);
        }

        indice++;
    }
    
    return T;
}

position ground::posOf(int indice) const
{
    auto e= d_groundElementsTab[indice].get();
    return e->getPosition();
}