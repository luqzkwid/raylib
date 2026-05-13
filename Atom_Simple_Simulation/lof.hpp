#ifndef LOF_HPP
#define LOF_HPP
#include<string>
class Logger {
public:
  enum LogLevel {LogLevelDebug, LogLevelInfo, LogLevelWarning, LogLevelError};
  Logger(LogLevel l_level);
  void debug(std::string text);
  void info(std::string text);        
  void warn(std::string text);        
  void err(std::string text);
  void SetLogLevel(LogLevel lg_level);
private:
  LogLevel m_loglevel;
};
#endif
