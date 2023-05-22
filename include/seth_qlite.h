#ifndef INCLUDED_SETH_QLITE_H
#define INCLUDED_SETH_QLITE_H

#include <array>
#include <mutex>
#include <sqlite3.h>
#include <string>
#include <unordered_map>

class Seth_Qlite
{
private:
    const std::string db_name;
    sqlite3* db;
    static constexpr std::array<std::string, 9> writeWords
        = { "create", "delete", "alter", "update", "upsert", "truncate", "merge", "replace", "insert" };
    static std::unordered_map<std::string, std::mutex> mutMap;
    bool isPossibleWriteCmd( const std::string& inputStr );
    void call_sqlite3_exec( const std::string& cmd, int ( *callback )( void*, int, char**, char** ) = nullptr, void* passedIn = nullptr );

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