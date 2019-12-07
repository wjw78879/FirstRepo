#include "bmpHolder.h"
#include<iostream>

bmpHolder::bmpHolder() {
    m_img.color = nullptr;
    m_img.data = nullptr;
}

bmpHolder::bmpHolder(const char* path) {
    this->read(path);
}

bool bmpHolder::read(const char* path) {
    FILE* file = fopen(path, "rb");
    if(file == NULL)return false;

    fread(&m_img.file.bfType[0], sizeof(char), 1, file);
    fread(&m_img.file.bfType[1], sizeof(char), 1, file);
    fread(&m_img.file.bfSize, sizeof(unsigned int), 1, file);
    fread(&m_img.file.bfReserved1, sizeof(unsigned short int), 1, file);
    fread(&m_img.file.bfReserved2, sizeof(unsigned short int), 1, file);
    fread(&m_img.file.bfOffBits, sizeof(unsigned int), 1, file);

    if(m_img.file.bfType[0] != 'B')return false;
    if(m_img.file.bfType[1] != 'M')return false;
    if(m_img.file.bfReserved1 != 0)return false;
    if(m_img.file.bfReserved2 != 0)return false;

    fread(&m_img.info.biSize, sizeof(unsigned int), 1, file);
    fread(&m_img.info.biWidth, sizeof(unsigned int), 1, file);
    fread(&m_img.info.biHeight, sizeof(unsigned int), 1, file);
    fread(&m_img.info.biPlanes, sizeof(unsigned short int), 1, file);
    fread(&m_img.info.biBitCount, sizeof(unsigned short int), 1, file);
    fread(&m_img.info.biCompression, sizeof(unsigned int), 1, file);
    fread(&m_img.info.biSizeImage, sizeof(unsigned int), 1, file);
    fread(&m_img.info.biXPelsPermeter, sizeof(unsigned int), 1, file);
    fread(&m_img.info.biYPelsPermeter, sizeof(unsigned int), 1, file);
    fread(&m_img.info.biClrUsed, sizeof(unsigned int), 1, file);
    fread(&m_img.info.biClrImportant, sizeof(unsigned int), 1, file);

    if(m_img.info.biPlanes != 1)return false;
    if(m_img.info.biBitCount != 8)return false;
    if(m_img.info.biCompression != 0)return false;
    
    switch(m_img.info.biBitCount) {
    case 1: return false;
    case 4: return false;
    case 24: return false;
    case 8: {
        m_img.color = (RGBQUAD*)malloc(sizeof(RGBQUAD) * 256);
        if(m_img.color == NULL)return false;

        for(int i = 0; i < 256; i++) {
            fread(m_img.color + i, sizeof(RGBQUAD), 1, file);
        }
        break;
    }
    default: return false;
    }

    m_img.data = (PIXEL*)malloc(sizeof(PIXEL) * m_img.info.biSizeImage);
    if(m_img.data == NULL)return false;

    for(int i = 0; i < m_img.info.biSizeImage; i++) {
        fread(m_img.data + i, sizeof(PIXEL), 1, file);
    }

    fclose(file);
    return true;
}

bool bmpHolder::save(const char* path) const {
    FILE* file = fopen(path, "wb");
    if(file == NULL)return false;
    
    fwrite(&m_img.file.bfType[0], sizeof(char), 1, file);
    fwrite(&m_img.file.bfType[1], sizeof(char), 1, file);
    fwrite(&m_img.file.bfSize, sizeof(unsigned int), 1, file);
    fwrite(&m_img.file.bfReserved1, sizeof(unsigned short int), 1, file);
    fwrite(&m_img.file.bfReserved2, sizeof(unsigned short int), 1, file);
    fwrite(&m_img.file.bfOffBits, sizeof(unsigned int), 1, file);

    fwrite(&m_img.info.biSize, sizeof(unsigned int), 1, file);
    fwrite(&m_img.info.biWidth, sizeof(unsigned int), 1, file);
    fwrite(&m_img.info.biHeight, sizeof(unsigned int), 1, file);
    fwrite(&m_img.info.biPlanes, sizeof(unsigned short int), 1, file);
    fwrite(&m_img.info.biBitCount, sizeof(unsigned short int), 1, file);
    fwrite(&m_img.info.biCompression, sizeof(unsigned int), 1, file);
    fwrite(&m_img.info.biSizeImage, sizeof(unsigned int), 1, file);
    fwrite(&m_img.info.biXPelsPermeter, sizeof(unsigned int), 1, file);
    fwrite(&m_img.info.biYPelsPermeter, sizeof(unsigned int), 1, file);
    fwrite(&m_img.info.biClrUsed, sizeof(unsigned int), 1, file);
    fwrite(&m_img.info.biClrImportant, sizeof(unsigned int), 1, file);

    for(int i = 0; i < 256; i++) {
        fwrite(m_img.color + i, sizeof(RGBQUAD), 1, file);
    }

    for(int i = 0; i < m_img.info.biSizeImage; i++) {
        fwrite(m_img.data + i, sizeof(PIXEL), 1, file);
    }

    fclose(file);
    return true;
}

bool bmpHolder::readTXT(const char* path, const unsigned int& rows, const unsigned int& cols) {
    FILE* file = fopen(path, "r");
    if(file == NULL)return false;

    m_img.file.bfType[0] = 'B';
    m_img.file.bfType[1] = 'M';
    m_img.file.bfSize = 1078 + rows * cols;
    m_img.file.bfReserved1 = 0;
    m_img.file.bfReserved2 = 0;
    m_img.file.bfOffBits = 1078;

    m_img.info.biSize = 40;
    m_img.info.biWidth = cols;
    m_img.info.biHeight = rows;
    m_img.info.biPlanes = 1;
    m_img.info.biBitCount = 8;
    m_img.info.biCompression = 0;
    m_img.info.biSizeImage = cols * rows;
    m_img.info.biXPelsPermeter = 0;
    m_img.info.biYPelsPermeter = 0;
    m_img.info.biClrUsed = 0;
    m_img.info.biClrImportant = 0;

    m_img.color = (RGBQUAD*)malloc(sizeof(RGBQUAD) * 256);
    if(m_img.color == NULL)return false;
    for(int i = 0; i < 256; i++) {
        m_img.color[i].rgbBlue = i;
        m_img.color[i].rgbGreen = i;
        m_img.color[i].rgbRed = i;
        m_img.color[i].rgbReserved = 0;
    }

    m_img.data = (PIXEL*)malloc(sizeof(PIXEL) * cols * rows);
    if(m_img.data == NULL)return false;
    float temp = 0;
    for(int r = rows - 1; r >= 0; r--) {
        for(int c = 0; c < cols; c++) {
            fscanf(file, "%f", &temp);
            if(temp < 0)temp = 0.0f;
            if(temp > 1)temp = 1.0f;
            m_img.data[r * cols + c].data = (unsigned char)(temp * 255.0f);
        }
    }
    fclose(file);
    return true;
}

bool bmpHolder::saveTXT(const char* path) const {
    FILE* file = fopen(path, "w");
    if(file == NULL)return false;
    fprintf(file, "%u %u\n", m_img.info.biHeight, m_img.info.biWidth);
    for(int r = m_img.info.biHeight - 1; r >= 0; r--) {
        for(int c = 0; c < m_img.info.biWidth; c++) {
            fprintf(file, "%u ", m_img.data[r * m_img.info.biWidth + c].data);
        }
        fprintf(file, "\n");
    }
    fclose(file);
    return true;
}

RGBQUAD* bmpHolder::getColor() const {
    return m_img.color;
}

bool bmpHolder::setColor(const RGBQUAD* cptr) {
    if(cptr == NULL)return false;
    for(int i = 0; i < 256; i++) {
        m_img.color[i].rgbBlue = cptr[i].rgbBlue;
        m_img.color[i].rgbGreen = cptr[i].rgbGreen;
        m_img.color[i].rgbRed = cptr[i].rgbRed;
        m_img.color[i].rgbReserved = cptr[i].rgbReserved;
    }
    return true;
}