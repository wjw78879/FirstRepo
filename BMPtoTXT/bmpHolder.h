#ifndef BMPHOLDER_H
#define BMPHOLDER_H

typedef struct {
    char bfType[2];
    unsigned int bfSize;
    unsigned short int bfReserved1;
    unsigned short int bfReserved2;
    unsigned int bfOffBits;
} BITMAPFILEHEADER;

typedef struct {
    unsigned int biSize;
    unsigned int biWidth;
    unsigned int biHeight;
    unsigned short int biPlanes;
    unsigned short int biBitCount;
    unsigned int biCompression;
    unsigned int biSizeImage;
    unsigned int biXPelsPermeter;
    unsigned int biYPelsPermeter;
    unsigned int biClrUsed;
    unsigned int biClrImportant;
} BITMAPINFOHEADER;

typedef struct{
    unsigned char rgbBlue;
    unsigned char rgbGreen;
    unsigned char rgbRed;
    unsigned char rgbReserved;
} RGBQUAD;

typedef struct {
    unsigned char data;
} PIXEL;

typedef struct {
    BITMAPFILEHEADER file;
    BITMAPINFOHEADER info;
    RGBQUAD* color;
    PIXEL* data;
} bmp;

class bmpHolder {
public:
    bmpHolder();
    bmpHolder(const char* path);

    bool read(const char* path);
    bool save(const char* path) const;

    bool readTXT(const char* path, const unsigned int& rows, const unsigned int& cols);
    bool saveTXT(const char* path) const;

    RGBQUAD* getColor() const;
    bool setColor(const RGBQUAD* cptr);
private:
    bmp m_img;
};

#endif