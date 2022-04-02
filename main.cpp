/*
Made by Marcell Fulop for Citrus Hack 2022
*/
#include <Magick++.h>
#include <iostream>
#include <string>
#include <filesystem>
#include <vector>

using namespace std;
using namespace Magick;
namespace fs = std::filesystem;

struct Pixel{
    unsigned char red;
    unsigned char green;
    unsigned char blue;
    Pixel(): red(0), green(0), blue(0){}
    Pixel(unsigned char r, unsigned char g, unsigned char b): red(r), green(g), blue(b) {}
};

struct Bitmap{
    Pixel** pixels; // (x,y)
    private:
        int x;
        int y;
    Bitmap(int cols, int rows): x(cols), y(rows){
        pixels = new Pixel*[y];
        for (int i = 0; i < y; i++){
            pixels[i] = new Pixel[x];
        }

    }
};

/*
Take in png and jpeg/jpg. Maybe others 
*/
bool isValidFile(string fn);

/*
Reads in the image file and puts it into the bitmap
*/
Bitmap readImage(string fn);

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
    vector<Bitmap> bitmaps;
    for (const auto& entry : fs::directory_iterator(filepath)){
       if (isValidFile(entry.path().string())){
           // valid file therefore read the image
            cout << entry.path().string() << endl;
            // readfile
            bitmaps.push_back();
       }
    }
    return 0;
}

bool isValidFile(string fn){
    if (fn.size() < 4)
        return false;
    if (fn.substr(fn.size() - 4) == ".jpg"){
        return true;
    }
    if (fn.substr(fn.size() - 5) == ".jpeg"){
        return true;
    }
    if (fn.substr(fn.size() - 4) == ".png"){
        return true;
    }
    return false;
}

Bitmap readImage(string fn){
    
}