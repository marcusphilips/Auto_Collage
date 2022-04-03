#include "bitmap.h"
Bitmap::Bitmap(int cols, int rows) : x(cols), y(rows)
{
    pixels = new Pixel *[y];
    for (int i = 0; i < y; i++)
    {
        pixels[i] = new Pixel[x];
    }
}
Bitmap::~Bitmap()
{
    for (int i = 0; i < y; i++)
    {
        delete[] pixels[i];
    }
    delete[] pixels;
}
void Bitmap::setPixel(int col, int row, unsigned char red, unsigned char green, unsigned char blue)
{
    pixels[row][col].red = red;
    pixels[row][col].green = green;
    pixels[row][col].blue = blue;
}
bool Bitmap::isPixelTransparent(int col, int row) const
{
    return pixels[row][col].transparent;
}
void Bitmap::setPixelTransparency(int col, int row, bool transparent)
{
    pixels[row][col].transparent = transparent;
}
Pixel Bitmap::getPixel(int col, int row) const
{
    // does not check if such coordinate is out of bounds
    return pixels[row][col];
}
int Bitmap::getWidth() const
{
    return x;
}
int Bitmap::getHeight() const
{
    return y;
}
Bitmap::Bitmap(const Bitmap &other) : x(other.getWidth()), y(other.getHeight())
{
    for (int i = 0; i < other.getHeight(); i++)
    {
        for (int j = 0; j < other.getWidth(); j++)
        {
            // kinda verbose but just copies pixel data
            setPixel(j, i, other.pixels[j][i].red, other.pixels[j][i].green, other.pixels[j][i].blue);
            setPixelTransparency(j, i, other.isPixelTransparent(j, i));
        }
    }
}
Bitmap &Bitmap::operator=(const Bitmap &other)
{
    if (this == &other)
        return *this;
    Pixel **np = new Pixel *[other.getHeight()];
    for (int i = 0; i < other.getHeight(); i++)
    {
        np[i] = new Pixel[other.getWidth()];
        for (int j = 0; j < other.getWidth(); j++)
        {
            np[j][i] = other.pixels[j][i];
        }
    }

    for (int i = 0; i < y; i++)
    {
        delete[] pixels[i];
    }
    delete[] pixels;
    pixels = np;

    return *this;
}
