#include "seth_qlite.h"
#include <iostream>

// function from sqlite documentation example
static int callback( void* NotUsed, int argc, char** argv, char** azColName )
{
    int i;
    for ( i = 0; i < argc; i++ )
    {
        printf( "%s = %s\n", azColName[ i ], argv[ i ] ? argv[ i ] : "NULL" );
    }
    printf( "\n" );
    return 0;
}

int main()
{
    Seth_Qlite db( "test.db" );
    db.execute( "create table if not exists rooms(name text primary key);" );
    db.execute( "insert into rooms values(\'100\'); "
                "insert into rooms values(\'101\'); "
                "insert into rooms values(\'102\');" );
    db.execute( "select * from rooms;", callback );

    return 0;
}