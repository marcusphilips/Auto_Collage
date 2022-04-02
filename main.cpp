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
    // val ranges 0 - 255
    unsigned char red;
    unsigned char green;
    unsigned char blue;
    Pixel(): red(0), green(0), blue(0){}
    Pixel(unsigned char r, unsigned char g, unsigned char b): red(r), green(g), blue(b) {}
};

class Bitmap{
    private:
        Pixel** pixels; // [y][x]
        int x;
        int y;
    public:
    Bitmap(int cols, int rows): x(cols), y(rows){
        pixels = new Pixel*[y];
        for (int i = 0; i < y; i++){
            pixels[i] = new Pixel[x];
        }
    }
    void setPixel(int col, int row, unsigned char red, unsigned char green, unsigned char blue){
        pixels[row][col].red = red;
        pixels[row][col].green = green;
        pixels[row][col].blue = blue;
    }
    Pixel getPixel(int col, int row) const {
        // does not check if such coordinate is out of bounds
        return pixels[row][col];
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
            bitmaps.push_back(readImage(entry.path().string()));
       }
       else {
           cout << entry.path().string() << " is an invalid file. Accepting only png, jpg, jpegs" << endl;
       }
    }
   
    return 0;
}

bool isValidFile(string fn){
    if (fn.size() < 4)
        return false;
    if (fn.front() == '.'){
        return false;
    }
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
    Image im;
    im.read(fn);
    const int WIDTH = im.columns();
    const int HEIGHT = im.rows();
    Bitmap b(WIDTH, HEIGHT);
    for (int y = 0; y < HEIGHT; y++){
        for (int x = 0; x < WIDTH; x++){
            ColorRGB q = im.pixelColor(x, y);
            b.setPixel(x, y, 
                (unsigned char)(q.red() * 255), 
                (unsigned char)(q.green() * 255),
                (unsigned char)(q.blue() * 255));
        }
    }
    return b;

}