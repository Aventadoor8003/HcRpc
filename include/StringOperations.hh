#ifndef _STRING_OPS_HH_
#define _STRING_OPS_HH_
#include <string>

/// @brief Check if a string is a correct ip address with port number
/// @param addrString 
bool isAddrString(std::string& addrString);

/// @brief Split a ip address from an input string
/// @param input 
/// @return ip address string
std::string getIpAddr(std::string input);

/// @brief Get a port number from input
/// @param input 
/// @return port number
int getPort(std::string input);

/// @brief Print string while printing CR and LF
/// @param str 
//void printWithCRLF(const char* str);

/// @brief Print string while printing CR and LF
/// @param str 
void printWithCRLF(std::string& str);

/// @brief 
/// @param msg 
/// @return 
bool isCommand(std::string& msg);

/// @brief Get command from an input string
/// @param str 
/// @return command
std::string getCommand(std::string& str);

/// @brief Get args from an input string
/// @param str 
/// @return args
std::string getArgs(std::string& str); 


#endif