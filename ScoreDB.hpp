#pragma once

#include <sqlite3.h>
#include <string>

class ScoreDB 
{
public:
	static ScoreDB& getInstance();
  
  ScoreDB(const ScoreDB&) = delete;
  ScoreDB& operator=(const ScoreDB&) = delete;

  int getMaxScore();

  void addScore(int score);

private:
	ScoreDB();
  ~ScoreDB();
  void handleError(char* errorMessage);
private:
  sqlite3* db;
  std::string sql;
  char* errerMessage;
};