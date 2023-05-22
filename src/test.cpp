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

    Seth_Qlite db2( "test2.db" );
    db2.execute( "CREATE TABLE contacts (contact_id INTEGER PRIMARY KEY,"
                 "first_name TEXT NOT NULL,"
                 "last_name TEXT NOT NULL,"
                 "email TEXT NOT NULL UNIQUE,"
                 "phone TEXT NOT NULL UNIQUE);" );
    db2.execute( "insert into contacts values(341, \'John\', \'Smith\', \'john.smith@something.com\', \'555-1234\'); "
                 "insert into contacts values(799, \'Bob\', \'Francis\', \'bob.francis@something.com\', \'555-2112\'); "
                 "insert into contacts values(510, \'Susan\', \'Hammond\', \'susan.hammond@something.com\', \'555-9138\');" );
    db2.execute( "select * from contacts;", callback );

    return 0;
}