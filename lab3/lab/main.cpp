#include <QCoreApplication>
#include <QDebug>

#include <iostream>
#include <fstream>
#include <vector>

struct RGBQUAD {
    char rgbBlue;
    char rgbGreen;
    char rgbRed;
    char rgbReserved;
};

typedef uint32_t DWORD; // Двойное слово - 32 бита (разряда)
typedef uint16_t WORD; // Слово - 16 бит (разрядов)
typedef int32_t LONG;

struct BMPHeader {
    WORD type;
    DWORD size;
    DWORD reserved;
    DWORD offset;
    DWORD dib_size;
    LONG width;
    LONG height;
    WORD planes;
    WORD bpp;
    DWORD compression;
    DWORD image_size;
    LONG x_ppm;
    LONG y_ppm;
    DWORD colors;
    DWORD important;
};

struct BMP_file {
    std::string path;
    BMPHeader header;
    LONG dataSize;
    RGBQUAD* data;
};

BMP_file read_bmp_file(const std::string& filename) {

    BMP_file retFile;
    retFile.path = filename;

    FILE* inStream = fopen(retFile.path.c_str(), "rb");
    if (!inStream) {
        printf("Error: could not open file %s\n", retFile.path.c_str());
        return BMP_file();
    }

    // Read BMP header
    fread(&retFile.header, sizeof(BMPHeader), 1, inStream);

    retFile.header.offset = retFile.header.offset / 8;

    // Read BMP data
    retFile.dataSize = retFile.header.image_size / (4 * 8);
    retFile.data = new RGBQUAD[retFile.dataSize];

    if(fseek(inStream, retFile.header.offset, SEEK_SET)){
        printf("Error: could not seek to RGBQUAD section offset: %i\n", retFile.header.offset);
        return BMP_file();
    }

    int readBytes = -1;
    readBytes = fread(retFile.data, sizeof(RGBQUAD), retFile.dataSize, inStream);


    if(readBytes <= 0) {
        printf("Error: could not read RGBQUAD section RB: %i  OS: %i\n", readBytes, retFile.dataSize);
        return BMP_file();
    }

    retFile.dataSize = readBytes;

    fclose(inStream);

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

uint8_t read_hidden_byte(const RGBQUAD &pixel) {
     uint8_t hiddenByte = ((pixel.rgbRed & 0x3) << 6)
                         | ((pixel.rgbGreen & 0x3) << 4)
                         | ((pixel.rgbBlue & 0x3) << 2);

     return hiddenByte;
}

void write_bmp_file(BMP_file file){
    FILE* outStream = fopen(file.path.c_str(), "wb");
    if(!outStream) {
        printf("Error: could not open file %s\n", file.path.c_str());
        return;
    }

    fwrite(&file.header, sizeof(BMPHeader), 1, outStream);
    fwrite(file.data, sizeof(RGBQUAD), file.dataSize, outStream);


    fclose(outStream);
}


int main(int argc, char *argv[])
{
    auto r = read_bmp_file("./6.bmp");
    for(int i = 0; i < r.dataSize; ++i) {
        std::cout << read_hidden_byte(r.data[i]);
    }

    write_bmp_file(r);

//    std::cout << r.dataSize << " " << sizeof(RGBQUAD) <<  std::endl;
    return 0;
}
