// put the object code into a seperate file because main.cpp was getting too long >300 lines
#ifndef BITMAP_H
#define BITMAP_H

/*
Holds the red green and blue values with a range from 0 to 255
*/
struct Pixel
{
    // val ranges 0 - 255
    unsigned char red;
    unsigned char green;
    unsigned char blue;
    bool transparent;
    Pixel() : red(0), green(0), blue(0), transparent(false) {}
    Pixel(unsigned char r, unsigned char g, unsigned char b) : red(r), green(g), blue(b), transparent(false) {}
};

/*
Think it as a very basic image format; stores pixels in a 2D array
*/
class Bitmap
{
private:
    Pixel **pixels; // [y][x]
    int x;
    int y;

public:
    Bitmap(int cols, int rows);
    ~Bitmap();
    void setPixel(int col, int row, unsigned char red, unsigned char green, unsigned char blue);
    bool isPixelTransparent(int col, int row) const;
    void setPixelTransparency(int col, int row, bool transparent);
    Pixel getPixel(int col, int row) const;
    int getWidth() const;
    int getHeight() const;
    Bitmap(const Bitmap &other);
    Bitmap &operator=(const Bitmap &other);
};
#endif