#ifndef COPY_H
#define COPY_H
#include "FileFilter.h"


class Copy : public FileFilter
{
public:
    virtual void doFilter(std::ifstream& in, std::ofstream& out) override;

};

#endif // COPY_H
