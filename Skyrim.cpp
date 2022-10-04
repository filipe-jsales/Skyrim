#include "Skyrim.h"
#include <map>
#include <iostream>
using std::cout;
using std::endl;
using std::map;

#include <cmath>

//Instanciação de variáveis statics
int Skyrim::numSkyrimPlayers = 0;
int Skyrim::numPlayersGuild = 0;
const string Skyrim::MAESTRIES[ QUANTITYMAESTRIES ] = {"C","B","A","S"};

int Skyrim::getNumPlayersGuild( )
{ 
    return numPlayersGuild; 
}


Skyrim::Skyrim( )
:logGuildPtr(0), guildName(""), numPlayers( 0 ), MAXSIZENAME( 9 ), check( false ), numPlayersRegistered( 0 )
{  
      logSize = 0;
      numSkyrimPlayers++;  

}

Skyrim::Skyrim( string name, int numPlayers )
:MAXSIZENAME( 9 ), check( false ), numPlayersRegistered( 0 )
{
    nextEntrieInLog = 0;
    logSize = 0;
    logGuildPtr = 0;
    setGuildName( name );
    setNumPlayers( numPlayers );  

    numSkyrimPlayers++;
}

Skyrim::Skyrim( int numPlayers )
:guildName(""), MAXSIZENAME( 9 ), check( false ), numPlayersRegistered( 0 )
{
    nextEntrieInLog = 0;
    logSize = 0;
    logGuildPtr = 0;
    setNumPlayers( numPlayers ); 

    numSkyrimPlayers++;
}

Skyrim::Skyrim( const Skyrim& other )
:MAXSIZENAME( other.MAXSIZENAME ), check( other.check ), numPlayersRegistered( 0 )
{
    this->guildName = other.guildName;
    setNumPlayers( other.numPlayers );

    this->logSize = other.logSize;
    this->nextEntrieInLog = other.nextEntrieInLog;
    this->logGuildPtr = new int[ this->logSize ];
    for( int i = 0; i < nextEntrieInLog; i++ )
        this->logGuildPtr[ i ] = logGuildPtr[ i ];

    this->players.resize( other.players.size() );
    //usando auto
    for( auto i = 0; i < other.players.size( ); i++ )
        this->players[ i ] = other.players[ i ];    

    numSkyrimPlayers++;
}

Skyrim::~Skyrim( )
{
    delete [] logGuildPtr; 

    for( auto i = 0; i < players.size( ); i++ )
        delete this->players[ i ];  
}


 void Skyrim::setGuildName( string name )
{
    if ( name.length( ) <= MAXSIZENAME )
        guildName = name;
    else   
        {
            guildName = name.substr( 0, MAXSIZENAME );
            // throw std::invalid_argument("Nome alterado. Excedeu o valor maximo. \n");
            cout << "Nome alterado. Excedeu o valor maximo. \n";
        }
}


void Skyrim::setNumPlayers( int numPlayers )
{    
    if ( Skyrim::numPlayersGuild > 0 )
        Skyrim::numPlayersGuild -= this->numPlayers;
        
    //Valor inválido para numPlayers
    if ( numPlayers <= 0 )
    {
        // throw std::invalid_argument("Argumento invalido, valor <= 0 \n");
        numPlayers = 0;
        return;
    }    
   
    this->numPlayers = numPlayers;
    Skyrim::numPlayersGuild += this->numPlayers;
    cadastrarJogadores( numPlayers );  
}

string Skyrim::getGuildName( )
{
    return guildName;
} 

void Skyrim::displayMessage( bool check ) const
{
    if( !check )
        return;
    if( guildName.size( ) > 0 )
    {
        cout << "Welcome to the Guild  " << guildName << "\n";
        printListaPlayers( );
        cout << "vagas na guild: \n";
        printHist( );
        return;
    }                 

    cout << "Welcome to the Guild. Guild with no name.";
}

void Skyrim::displayMessage( bool check )
{
    //Atribuição dentro da classe
    this->check = check;

    if( !this->check )
        return;
    if( guildName.size( ) > 0 )
    {
        cout << "Welcome to the Guild " << guildName << "\n";
        printListaPlayers( );
        cout << "vagas na guild: \n";
        printHist( );
        return;
    }         

    cout << "Welcome to the Guild. Guild with no name.\n";    
}

void Skyrim::printGrades( )
{
    for( int i = 0; i < QUANTITYMAESTRIES; i++ )
        cout << MAESTRIES[ i ] << ' ' << '(' <<&MAESTRIES[ i ] << ')' << '\n';
    
}

void Skyrim::cadastrarPlayerSkyrim( const string &newPlayer )
{
    //O vector players pode crescer dinamicamente
    //Mas só pode aceitar numPlayers
    
    if( players.size( ) < numPlayers ) 
    {
        numPlayersRegistered++;
        players.push_back( new string(newPlayer) );        
        return;
    }

    cout << "Could not include " << newPlayer << '.' << " Guild is full.\n";

}

void Skyrim::printListaPlayers( ) const
{
    for( int i = 0; i < players.size( ); i++ )
        cout << *players[ i ] << endl;
}

 void Skyrim::cadastrarJogadores( int numPlayers )
 {
    if ( nextEntrieInLog < logSize )
    {
        logGuildPtr[ nextEntrieInLog++ ] = numPlayers;
        return;
    }

    if( logSize == 0 )
    {
        logSize = 1;
        logGuildPtr = new int[ logSize ];
        logGuildPtr[ nextEntrieInLog++ ] = numPlayers;
        return;
    }       
    //caso memoria esteja cheia, chamar o metodo de aumentar memoria
    aumentarMemoria( numPlayers );    
 }

 void Skyrim::printHist( ) const
 {
    for( int i = 0; i < nextEntrieInLog; i++ )
        cout << logGuildPtr[ i ] << '\n'; 
    
 }

 void Skyrim::aumentarMemoria( int numPlayers ) 
 {    
    cout << "Memoria a mais alocada\n";
    //uso um ponteiro auxiliar pra receber os valoresdo original
    int *logTemp = new int[ logSize ];
    for( int i = 0; i < nextEntrieInLog; i++ )
        logTemp[ i ] = logGuildPtr[ i ];

    //desaloco do original
    delete [] logGuildPtr;
    logSize += int( ceil( logSize * 0.3 ) );//Aumenta a memoria em 30%

    //aloco novamente com a memoria aumentada em 30%
    int *logGuildPtr = new int[ logSize ];
    for( int i = 0; i < nextEntrieInLog; i++ )
        logGuildPtr[ i ] = logTemp[ i ];
    logGuildPtr[ nextEntrieInLog++ ] = numPlayers;

    //desaloco memória do ponteiro auxiliar
    delete [] logTemp;     
      
 }

void Skyrim::cadastrarBounties( int quantidadeBounties)
{
    //cadastra bounties com valor aleatorio
    for (int i=0 ; i<quantidadeBounties; i++)
        bounties.insert(std::pair<int, int>(i, rand()));
}

void Skyrim::completeBounty(int indiceBounty)
{
    std::map<int,int>::iterator it;
    it = bounties.find(indiceBounty);
    if(it != bounties.end()) //Searches the container for an element with a key equivalent to k and returns an iterator to it if found, otherwise it returns an iterator to map::end.
    {
        bounties.erase(bounties.find(indiceBounty));
        cout << "The bounty " << indiceBounty << " was completed!\nCongratulations!\n";
        return;
    }
    cout << "This bounty could not be finished yet.\n";
}

void Skyrim::showBounties()
{
    map<int, int>::iterator itr;
    for (itr = bounties.begin(); itr != bounties.end(); ++itr) {
        cout << '\t' << itr->first << " bounty" << '\t' << itr->second << " golds"
             << '\n';
    }
}