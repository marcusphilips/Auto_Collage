/*
Made by Marcell Fulop for Citrus Hack 2022
*/
#include <Magick++.h>
#include <iostream>
#include <string>
#include <filesystem>

using namespace std;
using namespace Magick;


struct Pixel{
    unsigned char red;
    unsigned char green;
    unsigned char blue;
};

int main(int argc, char** argv){
    // need to capture original image files
    string filepath = "./";
    if (argc < 2){
        cout << "Filepath argument missing" << endl;
        return 1;
    }
    char* f = argv[1];
    unsigned i = 0;
    while (f[i] != '\0'){
        filepath.push_back(f[i]);
        i++;
    }
    filepath.push_back('/');
    cout << filepath << endl;
    // point to the folder that contains all the files
    InitializeMagick(*argv);

    return 0;
}