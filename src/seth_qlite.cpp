#include "seth_qlite.h"
#include <algorithm>
#include <iostream>
#include <mutex>
#include <stdexcept>

namespace
{
    std::string strToLower( const std::string& inputStr )
    {
        std::string outputStr;
        std::ranges::transform( inputStr, std::back_inserter( outputStr ), ::tolower );
        return outputStr;
    }

};

std::unordered_map<std::string, std::mutex> Seth_Qlite::mutMap;

Seth_Qlite::Seth_Qlite( const std::string& _db_name )
    : db_name( _db_name )
    , db( nullptr )

{
    int rc = sqlite3_open( db_name.c_str(), &db );
    if ( rc )
    {
        std::string msg = std::string( "Can't open database: " ) + sqlite3_errmsg( db );
        sqlite3_close( db );
        throw std::runtime_error( msg );
    }
}

void Seth_Qlite::call_sqlite3_exec( const std::string& cmd, int ( *callback )( void*, int, char**, char** ), void* passedIn )
{
    char* zErrMsg = nullptr;
    int rc = sqlite3_exec( db, cmd.c_str(), callback, passedIn, &zErrMsg );
    if ( rc != SQLITE_OK )
    {
        std::string errMsg = std::string( "SQL error: " ) + zErrMsg;
        sqlite3_free( zErrMsg );
        throw std::runtime_error( errMsg );
    }
}

void Seth_Qlite::execute( const std::string& cmd, int ( *callback )( void*, int, char**, char** ), void* passedIn )
{
    if ( isPossibleWriteCmd( cmd ) )
    {
        return performWriteOperation( cmd, callback, passedIn );
    }
    std::cout << "Command: \'" << cmd << "\' does not use a mutex\n\n";
    call_sqlite3_exec( cmd, callback, passedIn );
}

void Seth_Qlite::performWriteOperation( const std::string& cmd, int ( *callback )( void*, int, char**, char** ), void* passedIn )
{
    std::lock_guard<std::mutex> lock( mutMap[ db_name ] );
    std::cout << "Command: \'" << cmd << "\' uses a mutex at address " << &( mutMap[ db_name ] ) << "\n\n";
    call_sqlite3_exec( cmd, callback, passedIn );
}

bool Seth_Qlite::isPossibleWriteCmd( const std::string& inputStr )
{
    std::string lowered = strToLower( inputStr );
    if ( std::ranges::find_if( writeWords, [ & ]( const auto& word ) { return lowered.find( word ) != std::string::npos; } )
        != writeWords.end() )
    {
        return true;
    }
    return false;
}

Seth_Qlite::~Seth_Qlite()
{
    sqlite3_close( db );
}