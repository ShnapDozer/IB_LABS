#include <QCoreApplication>
#include <QDebug>
#include <iostream>

//typedef unsigned long DWORD; // Двойное слово - 32 бита (разряда)
//typedef unsigned int WORD; // Слово - 16 бит (разрядов)
//typedef signed long LONG;
//typedef unsigned int UINT;

//// Заголовок файла
//typedef struct tagBITMAPFILEHEADER {
//    WORD bfType; // 'BM' = 4D42h
//    DWORD bfSize;
//    WORD bfReserved1;
//    WORD bfReserved2;
//    DWORD bfOffBits; // Смещение к растру
//} BITMAPFILEHEADER;

//// Заголовок Bitmap
//typedef struct tagBITMAPINFOHEADER {
//    DWORD biSize;
//    LONG biWidth;
//    LONG biHeight;
//    WORD biPlanes;
//    WORD biBitCount;
//    DWORD biCompression;
//    DWORD biSizeImage;
//    LONG biXPelsPerMeter;
//    LONG biYPelsPerMeter;
//    DWORD biClrUsed;
//    DWORD biClrImportant;
//} BITMAPINFOHEADER;



#include <fstream>
#include <vector>

struct BMPHeader {
    uint16_t type;
    uint32_t size;
    uint32_t reserved;
    uint32_t offset;
    uint32_t dib_size;
    int32_t width;
    int32_t height;
    uint16_t planes;
    uint16_t bpp;
    uint32_t compression;
    uint32_t image_size;
    int32_t x_ppm;
    int32_t y_ppm;
    uint32_t colors;
    uint32_t important;
};

struct RGBQUAD {
    char rgbBlue;
    char rgbGreen;
    char rgbRed;
    char rgbReserved;
};

struct BMP_file {
    std::string filePath;
    BMPHeader header;
    std::vector<RGBQUAD> data;
};

BMP_file read_bmp_file(const std::string& filename) {

    BMP_file retFile;
    retFile.filePath= filename;
    std::ifstream file(filename, std::ios::binary);

    // Read BMP header
    file.read(reinterpret_cast<char*>(&retFile.header), sizeof(retFile.header));

    // Check if file is BMP
    if (retFile.header.type != 0x4D42) {
        throw std::runtime_error("File is not BMP");
    }

    // Read BMP data
    char* buffer = new char[retFile.header.image_size];
    file.seekg(retFile.header.offset, std::ios::beg);
    file.read(buffer, sizeof(buffer));

    std::cout << retFile.header.image_size << std::endl;
    for(int i = 0; i < retFile.header.image_size; i += 4) {
        retFile.data.push_back({buffer[i], buffer[i+1], buffer[i+2], buffer[i+3]});
    }

    return retFile;
}

void hide_byte_into_pixel(RGBQUAD *pixel, uint8_t hide_byte) {
    pixel->rgbBlue &= (0xFC);
    pixel->rgbBlue |= (hide_byte >> 6) & 0x3;
    pixel->rgbGreen &= (0xFC);
    pixel->rgbGreen |= (hide_byte >> 4) & 0x3;
    pixel->rgbRed &= (0xFC);
    pixel->rgbRed |= (hide_byte >> 2) & 0x3;
    pixel->rgbReserved &= (0xFC);
    pixel->rgbReserved |= (hide_byte) & 0x3;
}

void write_hide_bmp_file(BMP_file file){
    std::ofstream wStream(file.filePath, std::ios::binary);
    wStream.write(reinterpret_cast<const char*>(&file.header), sizeof(BMPHeader));
    wStream.write(reinterpret_cast<const char*>(file.data.data()), sizeof(RGBQUAD) * file.data.size());
    wStream.close();
}

int main(int argc, char *argv[])
{
    auto r = read_bmp_file("./pic.bmp");
    r.filePath = "./pic1.bmp";

    write_hide_bmp_file(r);

    std::cout << r.data.size() << std::endl;
    return 0;
}
