#ifndef SKYRIM_H
#define SKYRIM_H
#include <map>
#include <string>
#include <vector>
using std::string;
using std::vector;
using std::map;

class Skyrim
{
public:

    Skyrim ( );    
    Skyrim( string , int = 0 );
    Skyrim( int );
    Skyrim( const Skyrim & );
    ~Skyrim( );
    
    void setGuildName( string );
    
    string getGuildName( );

    void displayMessage( bool = true ) const;
    void displayMessage( bool = true );

    int getNumAlunos( ) const { return numPlayers; }

    //Implementação no .cpp
    static int getNumPlayersGuild( );// { return numPlayersGuild; }

    static void printGrades( );

    //Para tipos não nativos usar o const _ &
    void cadastrarPlayerSkyrim( const string & );

    void printListaPlayers( ) const;

    void cadastrarJogadores( int );

    void setNumPlayers( int );

    void cadastrarBounties( int );
    void showBounties();
    void completeBounty( int );
private:

    string guildName;
    int numPlayers;
    //Número de players cadastrados em players
    //Usado em cadastrarPlayerSkyrim
    //players[ numPlayersRegistered - 1 ] = newPlayer;
    int numPlayersRegistered;
    const int MAXSIZENAME;
    bool check;
    static int numSkyrimPlayers;
    //Error check. Static não pode numPlayers no .h
    //static int numSkyrimPlayers = 0;

    static int numPlayersGuild;
    
    //Número de MAESTRIES "C","B","A","S"
    static const int QUANTITYMAESTRIES = 4;
    static const string MAESTRIES[ QUANTITYMAESTRIES ];

    //O número de players pode crescer dinamicamente
    vector< string * > players;

    //map de bounties   
    map<int, int> bounties;   

    //Alocação dinâmica de memória
    //Guarda o histórico da quantidade de players
    //que participaram da guild ao longo do tempo
    int *logGuildPtr;

    //Tamanho alocado para logGuildPtr
    int logSize;

    //Quantidade de registros em logGuildPtr
    //Quantidades de players cadastrados ao longo do tempo
    int nextEntrieInLog;

    void printHist( ) const;

    //Método para aumentar a memória disponível em logGuildPtr
    void aumentarMemoria( int );

};

#endif // SKYRIM_H   