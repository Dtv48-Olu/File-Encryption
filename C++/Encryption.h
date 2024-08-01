#ifndef ENCRYPTION_H
#define ENCRYPTION_H
#include "FileFilter.h"
#include <iostream>


class Encryption:public FileFilter
{
private:
    int Key;
public:
    /**
     *
     * Default constructor
     */
    Encryption(); // Setting the default key to five
    Encryption(int Key_value); // Overloaded constructor
    // Mutator
    void setKey(int num){Key = num;}
    // Overidden doFilter prototype
    virtual void doFilter(std::ifstream & in, std::ofstream & out);

};

#endif // ENCRYPTION_H
