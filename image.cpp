#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION 
#include "image.h"
#include "stb_image.h"
#include "stb_image_write.h"
 

image::image(const char* filename) {
    cout << "[DEBUG] Constructor: Attempting to load image: " << filename << endl;
    if (read(filename)) {
        size = w * h * channels;
    } else {
        cerr << "[ERROR] Constructor: Failed to load image: " << filename << endl;
        w = h = channels = 0;
        size = 0;
        data = nullptr;
    }
}

image::image(int w, int h, int channels) : w(w), h(h), channels(channels) {
    size = w * h * channels;
    data = new uint8_t[size];
    fill(data, data + size, 0);
}

image::image(const image& pic) : w(pic.w), h(pic.h), channels(pic.channels), size(pic.size) {
    if (pic.data) {
        data = new uint8_t[size];
        memcpy(data, pic.data, size);
    } else {
        data = nullptr;
    }
}

image::~image() {
    if (data) {
        delete[] data;
    }
}

bool image::read(const char* filename) {
    data = stbi_load(filename, &w, &h, &channels, 0);
    if (data) {
        return true;
    } else {
        cerr << "[DEBUG] Read: Failed to load file: " << filename << endl;
        return false;
    }
}

bool image::write(const char* filename) {
    if (!data) {
        cerr << "[ERROR] Write: No image data to write for file: " << filename << endl;
        return false;
    }

    imgtype type = getFiletype(filename);
    int success = 0;

    switch (type) {
        case PNG:
            success = stbi_write_png(filename, w, h, channels, data, w * channels);
            break;
        case BMP:
            success = stbi_write_bmp(filename, w, h, channels, data);
            break;
        case JPG:
            success = stbi_write_jpg(filename, w, h, channels, data, 100);
            break;
        case TGA:
            success = stbi_write_tga(filename, w, h, channels, data);
            break;
        default:
            cerr << "[ERROR] Write: Unsupported file type for: " << filename << endl;
            return false;
    }
    if (success) {
        cout << "[DEBUG] Write: Successfully wrote file: " << filename << endl;
    } else {
        cerr << "[ERROR] Write: Failed to write file: " << filename << endl;
    }
    return success != 0;
}

imgtype image::getFiletype(const char* filename) {
    const char* ext = strchr(filename, '.');
    if (ext) {
        if (strcmp(ext, ".png") == 0) return PNG;
        if (strcmp(ext, ".jpg") == 0) return JPG;
        if (strcmp(ext, ".bmp") == 0) return BMP;
        if (strcmp(ext, ".tga") == 0) return TGA;
    }
    cerr << "[DEBUG] GetFiletype: Unknown or unsupported file type for: " << filename << endl;
    exit(EXIT_FAILURE);
}