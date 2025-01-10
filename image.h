#include <iostream>
#include <cstdio>
#include <stdint.h>
#include <cstdint>
#include <cstring>
#include <string>

using namespace std;

enum imgtype{
    PNG,JPG, BMP, TGA
};

struct image{ 
    //uin8_t is one bite
    //pointer to picture data, each data is one bite
    uint8_t* data=nullptr;
    size_t size=0;
    int w=0,h=0,channels=0;
    //width, height, channels is color values per pixel


    image(const char* filename);//image that takes in file name as parameter
    image(int w, int h, int channels);// blank image to be created
    image(const image& pic); //copy constructor
    ~image();//detructor

    bool read(const char* filename);//function to be called that reads file name
    bool write(const char* filename);//write filename in location

    imgtype getFiletype(const char* filename);
};

