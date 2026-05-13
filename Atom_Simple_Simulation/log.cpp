#include<iostream>
#include<ctime>
#include<string>
#include"lof.hpp"
Logger::Logger(Logger::LogLevel l_level) : m_loglevel(l_level){}
void SetLogLevel(Logger::LogLevel l_level){
  if(l_level < Logger::LogLevelDebug || l_level > Logger::LogLevelError){
    std::cerr << "LogWarning: LogLevel couldnt be processed. Default: LogLevelWarning\n";
    l_level = Logger::LogLevelWarning;
    return;
  }
}
void Logger::info(std::string text){
  time_t timestamp = time(NULL);
  struct tm datetime = *localtime(&timestamp);
  if(Logger::m_loglevel >= Logger::LogLevelInfo) {
    std::cout << "[INFO]: "
	      << datetime.tm_hour << ":"
	      << datetime.tm_min << ":"
	      << datetime.tm_sec << " :: "
	      << text << "\n";
    return;
  }
  std::cout << "LogError: Level Unsupported.\n";
}
void Logger::debug(std::string text){
  time_t timestamp = time(NULL);
  struct tm datetime = *localtime(&timestamp);
  if(Logger::m_loglevel >= Logger::LogLevelDebug) {
    std::cout << "[DEBUG]: "
	      << datetime.tm_hour << ":"
	      << datetime.tm_min << ":"
	      << datetime.tm_sec << " :: "
	      << text << "\n";
    return;
  }
  std::cout << "LogError: Level Unsupported.\n";
}
void Logger::err(std::string text){
  time_t timestamp = time(NULL);
  struct tm datetime = *localtime(&timestamp);
  if(Logger::m_loglevel >= Logger::LogLevelError) {
    std::cout << "[ERROR]: "
	      << datetime.tm_hour << ":"
	      << datetime.tm_min << ":"
	      << datetime.tm_sec << " :: "
	      << text << "\n";
    return;
  }
  std::cout << "LogError: Level Unsupported.\n";
}
void Logger::warn(std::string text){
  time_t timestamp = time(NULL);
  struct tm datetime = *localtime(&timestamp);
  if(Logger::m_loglevel >= Logger::LogLevelWarning) {
    std::cout << "[WARNING]: "
	      << datetime.tm_hour << ":"
	      << datetime.tm_min << ":"
	      << datetime.tm_sec << " :: "
	      << text << "\n";
    return;
  }
  std::cout << "LogError: Level Unsupported.\n";
}
