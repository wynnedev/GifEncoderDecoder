//
// Created by linuxdev on 2/15/22.
//

#ifndef GIFENCODERDECODER_GIFDECODER_H
#define GIFENCODERDECODER_GIFDECODER_H

//std headers
#include <fstream>
#include <iostream>
//lib headers
#include <gif_lib.h>
#include <opencv2/core.hpp>

struct {
    const unsigned char* data;
    int len;
    int pos;
} typedef GifData;



class GifDecoder {
public:
    GifDecoder() = default;
    explicit GifDecoder(std::string gifData) : _gifDataString(gifData){
    }

    cv::Mat DecodeGif();
    unsigned char* EncodeGif(cv::Mat mat);
    void SetGifData(std::string gifData);
private:
    cv::Mat DecodeGifHandler(const unsigned char* buffer, const size_t len);
    std::string _gifDataString;

};

static int GifDataFunction(GifFileType* f, GifByteType* buffer, int size){
    GifData* data = (GifData*) f->UserData;

    size = (size > data->len) ? data->len : size;
    memcpy(buffer, data->data + data->pos, size);
    data->pos += size;
    return size;
}
#endif //GIFENCODERDECODER_GIFDECODER_H
