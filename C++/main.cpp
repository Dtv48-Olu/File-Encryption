// Olutoye O
// odufowokantoye@outlook
// Date Started: 7-13-24
// Description: The following project purpose is demostrate a simpilistic version of file encryption and proper c++ security pratices
#include <iostream>
#include <string>
#include <fstream>
#include "Encryption.h"
#include "Uppercase.h"
#include "Copy.h"

// Driver pgrogram
int main() {
    using std::cin;
    using std::cout;
    using std::ifstream;
    using std::ofstream;
    using std::string;
    using std::endl;
    // Variables
    string FileName;
    // prompt
    cout << "Please input the FileName to be read" << endl;
    cin >> FileName;
    ifstream Input_File(FileName);
    ofstream Output_File("EncryptionDefault.txt");
    ofstream Output_File2("Encryption12.txt");
    ofstream Output_File3("Encryption-4.txt");
    ofstream Output_File4("Uppercase.txt");
    ofstream Output_File5("Copy.txt");
    // Encryption test
    Encryption obj;
    obj.doFilter(Input_File, Output_File);
    Encryption obj2(12);
    obj.doFilter(Input_File, Output_File2);
    Encryption obj3(-4);
    obj.doFilter(Input_File, Output_File3);
    // Uppercase test
    Uppercase obj4;
    obj4.doFilter(Input_File, Output_File4);
    // Copy test
    Copy obj5;
    obj5.doFilter(Input_File, Output_File5);
    return 0;
}
