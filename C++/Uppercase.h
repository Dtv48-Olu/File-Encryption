#ifndef UPPERCASE_H
#define UPPERCASE_H
#include "FileFilter.h"


class Uppercase : public FileFilter
{
public:
    //Function prototypes
    char transform(char ch);

    virtual void doFilter(std::ifstream& in, std::ofstream& out) override;

};

#endif // UPPERCASE_H
