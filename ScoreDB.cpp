#include "ScoreDB.hpp"
#include "Common.hpp"
#include <iostream>
#include <string>
#include <stdexcept>

ScoreDB& ScoreDB::getInstance()
{
  static ScoreDB instance;
  return instance;
}

ScoreDB::ScoreDB() :
db{nullptr}, errerMessage{nullptr}
{
  if (SQLITE_OK != sqlite3_open(DB_PATH, &db))
    throw std::runtime_error("Failed to open database: " + std::string(sqlite3_errmsg(db)));
  
  sql = "CREATE TABLE IF NOT EXISTS " + std::string(TABLE_NAME) + " (" +
        "ID INTEGER PRIMARY KEY AUTOINCREMENT," +
        "SCORE INTEGER NOT NULL);";

  if(SQLITE_OK != sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errerMessage))
    handleError(errerMessage);
}

ScoreDB::~ScoreDB()
{
  if (!db)
    return;
  sqlite3_close(db);
  db = nullptr;
}

int ScoreDB::getMaxScore()
{
  int max = 0;
  sql = "SELECT MAX(SCORE) FROM " + std::string(TABLE_NAME) + ";";

  auto callBack = [](void* data, int argc, char** argv, char** colNames) -> int {
    if (argv[0])
    {
      int* maxValue = static_cast<int*>(data);
      *maxValue = std::stoi(argv[0]);  
    }
    return 0;
  };

  if (SQLITE_OK != sqlite3_exec(db, sql.c_str(), callBack, &max, &errerMessage))
    handleError(errerMessage);

  return max;  
}

void ScoreDB::addScore(int score)
{
  sql = "INSERT INTO " + std::string(TABLE_NAME) +  " (SCORE) VALUES (" + std::to_string(score) + ")";
  
  if (SQLITE_OK != sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errerMessage))
    handleError(errerMessage);
  else
    std::cout << "Success to add score: " + std::to_string(score) << std::endl;
}

void ScoreDB::handleError(char* errorMessage)
{
  std::string msg = "SQL error: " + std::string(errerMessage);
  sqlite3_free(errerMessage);
  errerMessage = nullptr;
  throw std::runtime_error(msg);
}