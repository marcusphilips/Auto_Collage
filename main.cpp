/*
Made by Marcell Fulop for Citrus Hack 2022
*/
#include "bitmap.h"
#include <Magick++.h>
#include <iostream>
#include <string>
#include <filesystem>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>


using namespace std;
using namespace Magick;
namespace fs = std::filesystem;

/*
Take in png and jpeg/jpg. Maybe others
*/
bool isValidFile(string fn);

/*
Reads in the image file and puts it into the bitmap
*/
Bitmap* readImage(string fn);

/*
Takes in bitmap and image and starting coordinates to draw to Image object with the bitmap
*/
void drawToImage(Image &im, Bitmap* from, int startX, int startY);

/*
Slices the images to get a more "collage" feel
*/
void sliceImage(vector<Bitmap*> &b);

int main(int argc, char **argv)
{
    // need to capture original image files
    string filepath = "./";
    if (argc < 2)
    {
        cout << "Filepath argument missing" << endl;
        return 1;
    }
    char *f = argv[1];
    unsigned i = 0;
    while (f[i] != '\0')
    {
        filepath.push_back(f[i]);
        i++;
    }
    filepath.push_back('/');
    // cout << filepath << endl;
    // point to the folder that contains all the files
    InitializeMagick(*argv);
    vector<Bitmap *> bitmaps;
    for (const auto &entry : fs::directory_iterator(filepath))
    {
        if (isValidFile(entry.path().string()))
        {
            // valid file therefore read the image
            // cout << entry.path().string() << endl;
            // readfile
            bitmaps.push_back(readImage(entry.path().string()));
        }
        else
        {
            cout << entry.path().string() << " is an invalid file. Accepting only png, jpg, jpegs" << endl;
        }
    }
    int totalPixelAmount = 0;
    int xSmallest = 0;
    int ySmallest = 0;
    for (unsigned i = 0; i < bitmaps.size(); i++)
    {
        if (ySmallest < bitmaps.at(i)->getHeight())
            ySmallest = bitmaps.at(i)->getHeight();
        if (xSmallest < bitmaps.at(i)->getWidth())
            xSmallest = bitmaps.at(i)->getWidth();
        totalPixelAmount += bitmaps.at(i)->getHeight() * bitmaps.at(i)->getWidth();
    }
    // going to "cut" the bitmaps by just setting a certain portion of the pixels transparent
    // the data underlying the bitmap will still be there so not most memory efficient 
    // need to decide how to cut; four options
    
    sliceImage(bitmaps);

    // will make new image dimensioned sqrt(totalPixelAmount) by sqrt(totalPixelAmount)
    // ie a square
    int n = ((int)sqrt((double)totalPixelAmount));
    Geometry g = Geometry(n, n);
    Quantum q(0);
    Color c(q, q, q); // c is black
    Image output = Image(g, c);
    // output is our "canvas"
    // will be doing sacattering every two images
    // get ready I'm about to make the world's worst collage
    // ok there has to be a better way

    for (Bitmap *b : bitmaps)
    {
        srand(time(nullptr));
        // drawToImage(output, b, 4*(rand() % n) / 5, 4*(rand() % n) / 5);
        // drawToImage(output, b, 4*(rand() % n) / 5, 4*(rand() % n) / 5);
        drawToImage(output, b, 4 * (rand() % n) / 5, 4 * (rand() % n) / 5);
    }
    output.write("testing.jpg");
    cout << "Drawed " << bitmaps.size() << " images to the collage " << endl;
    // for the end
    while (!bitmaps.empty())
    {
        delete bitmaps.back();
        bitmaps.pop_back();
    }
    return 0;
}

bool isValidFile(string fn)
{
    // cout << "Testing:" << fn.substr(fn.size() - 4) << fn.size() << endl;
    if (fn.size() < 4)
        return false;

    // cout << (fn.substr(fn.size() - 4) == ".jpg") << endl;
    if (fn.substr(fn.size() - 4) == ".jpg")
    {
        return true;
    }
    if (fn.substr(fn.size() - 5) == ".jpeg")
    {
        return true;
    }
    if (fn.substr(fn.size() - 4) == ".png")
    {
        return true;
    }
    return false;
}

Bitmap *readImage(string fn)
{
    Image im;
    im.read(fn);
    const int WIDTH = im.columns();
    const int HEIGHT = im.rows();
    Bitmap *b = new Bitmap(WIDTH, HEIGHT);
    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            ColorRGB q = im.pixelColor(x, y);
            b->setPixel(x, y,
                        (unsigned char)(q.red() * 255.0),
                        (unsigned char)(q.green() * 255.0),
                        (unsigned char)(q.blue() * 255.0));
            if (fn.substr(fn.size() - 9) == "_test.png")
            { // both clear
              // cout << "(" << q.red() << ", " << q.green() << ", " << q.blue() << ")" <<endl;
              // cout << "(" << (int)b->getPixel(x, y).red<< ", "<< (int)b->getPixel(x, y).green << "," <<(int)b->getPixel(x, y).blue << ")" << endl;
            }
        }
        // cout << " " << y << endl;
    }
    return b;
}

void drawToImage(Image &im, Bitmap *from, int startX, int startY)
{
    for (unsigned row = 0; row < (unsigned)from->getHeight(); row++)
    {
        for (unsigned col = 0; col < (unsigned)from->getWidth(); col++)
        {
            if (row + startY >= im.rows() && col + startX >= im.columns())
            {
                return;
            }
            if (col + startX >= im.columns())
            {
                continue;
            }
            if (row + startY >= im.rows())
            {
                continue;
            }
            ColorRGB color(
                from->getPixel(col, row).red / 255.0,
                from->getPixel(col, row).green / 255.0,
                from->getPixel(col, row).blue / 255.0);
            im.pixelColor(col + startX, row + startY, color);
        }
    }
}

void sliceImage(vector< Bitmap*> &b){
    int n = b.size();
    for (int i = 0; i < n; i++){
        srand(time(nullptr));
        int choice = rand()%4;
        int* cut0 = new int[2];
        int* cut1 = new int[2];
        // choose to go top down
        // recall [y][x]
        if (choice == 0){
            cut0[0] = 0;
            cut0[1] = b.at(i)->getWidth()/2;
            cut1[0] = b.at(i)->getHeight() - 1;
            cut1[1] = cut0[1];
        }
        // diagnol pointing "southeast"/"northwest"
        else if (choice == 1){
            cut0[0] = 0;
            cut0[1] = 0;
            cut1[0] = b.at(i)->getHeight() - 1;
            cut1[1] = b.at(i)->getWidth() - 1;
        }
        // going horizontal
        else if (choice == 2){
            cut0[0] = b.at(i)->getHeight()/2; 
            cut0[1] = 0;
            cut1[0] = cut0[0];
            cut1[1] = b.at(i)->getHeight() - 1;
        }
        // diagnol pointing "southwest"/"northeast"
        else if (choice == 3){}
    }

}