#ifndef INCLUDED_SETH_QLITE_H
#define INCLUDED_SETH_QLITE_H

#include <array>
#include <mutex>
#include <sqlite3.h>
#include <string>

class Seth_Qlite
{
private:
    const std::string db_name;
    sqlite3* db;
    const std::array<std::string, 9> writeWords
        = { "create", "delete", "alter", "update", "upsert", "truncate", "merge", "replace", "insert" };
    static std::mutex mut;
    bool isWriteCmd( const std::string& inputStr );

public:
    Seth_Qlite( const std::string& _db_name );
    Seth_Qlite() = delete;
    Seth_Qlite( const Seth_Qlite& ) = delete;
    Seth_Qlite& operator=( const Seth_Qlite& ) = delete;
    Seth_Qlite( const Seth_Qlite&& ) = delete;
    Seth_Qlite& operator=( const Seth_Qlite&& ) = delete;
    ~Seth_Qlite();

    void execute( const std::string& cmd, int ( *callback )( void*, int, char**, char** ) = nullptr, void* passedIn = nullptr );
    void performWriteOperation(
        const std::string& cmd, int ( *callback )( void*, int, char**, char** ) = nullptr, void* passedIn = nullptr );
};

#endif // INCLUDED_SETH_QLITE_H