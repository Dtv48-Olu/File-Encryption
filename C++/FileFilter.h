#ifndef FILEFILTER_H
#define FILEFILTER_H
#include <iostream>
#include <fstream>



class FileFilter
{
public:
    virtual void doFilter(std::ifstream &in, std::ofstream &out) = 0;
};

#endif // ENCRYPTION_H
