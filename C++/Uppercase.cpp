#include "Uppercase.h"
#include <iostream>

char Uppercase::transform(char ch)
{
    while(ch)
    {
        if(ch >= 'a' && ch <= 'z')
        {
            ch = ch - 'a' + 'A';
        }
        ch++;
    }
    return ch;
}
void Uppercase::doFilter(std::ifstream& in, std::ofstream& out)
{
    //variables
    char letter;
    //Checking if the file is open
    if(in.is_open())
    {
        while(in.is_open())
        {
            // Grabbing by character
            in >> letter;
            // static casting to convert the char into int value
            out << transform(letter);
        }
    }
    else
    {
        std::cout << "Error: File cannot be open" << std::endl;
    }
}
