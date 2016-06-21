#ifndef MKF_FILE_HPP
#define MKF_FILE_HPP


#include<cstdio>
#include<string>


void         save_file(const char*  path, const std::string&  s);
std::string  load_file(const char*  path);

std::string  to_string(FILE*  f);

bool  compare_file(FILE*  a, FILE*  b);



#endif




