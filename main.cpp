#include "Skyrim.cpp"
#include "Skyrim.h"
#include <map>
#include <iterator>
#include <vector>
#include <cstdlib>
using std::map;
using std::vector;

//This is where the execution of program begins
int main()
{
    
   Skyrim skyrim1( "Winterhold", 3 );
   skyrim1.cadastrarPlayerSkyrim("Archer");
   skyrim1.cadastrarPlayerSkyrim("Archer");
   skyrim1.cadastrarPlayerSkyrim("Archer");
   skyrim1.displayMessage();
   skyrim1.cadastrarJogadores(10);
   Skyrim *skyrimPtr;
   int newPlayers = 5;

   //Criando uma lista de classes
   vector< string * > classes;
   classes.push_back( new string( "Archer") );  
   classes.push_back( new string( "Orc") );
   classes.push_back( new string( "Human") ); 
   classes.push_back( new string( "Khajiit") ); 

   
   skyrimPtr = new Skyrim( "BloodBorn", 3 );

   skyrimPtr->displayMessage( );
   //setting new players
   skyrimPtr->setNumPlayers( newPlayers );
   // skyrimPtr->cadastrarPlayerSkyrim("Orc");   
   cout << "Apos adicionar novas vagas: \n";
   skyrimPtr->displayMessage( );   

   //Cadastrando os classes da lista no Skyrim 
   for( int i = 0; i < classes.size(); i++ )
      skyrimPtr->cadastrarPlayerSkyrim( *classes[ i ] );
   
   skyrimPtr->displayMessage( );

   Skyrim *skyrimPtr_extra = new Skyrim( *skyrimPtr ); //copia
   cout << "\n\nImprimindo informacoes de skyrimPtr_extra.\n";
   skyrimPtr_extra->displayMessage( );

   //Desalocando memória
   for( int i = 0; i < classes.size(); i++ )
      delete classes[ i ];

   skyrimPtr = 0; 
   skyrimPtr_extra = 0;
   delete skyrimPtr;
   delete skyrimPtr_extra;

   // Skyrim skyrim;
   // skyrim.cadastrarBounties(5);
   // skyrim.showBounties();
   // skyrim.completeBounty(0);
   // skyrim.showBounties();
   // skyrim.completeBounty(0);
   

   return 0;
}