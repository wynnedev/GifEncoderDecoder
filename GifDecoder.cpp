//
// Created by linuxdev on 2/15/22.
//

#include <zconf.h>
#include "GifDecoder.h"

cv::Mat GifDecoder::DecodeGif() {
    return DecodeGifHandler((const unsigned char*) _gifDataString.c_str(), _gifDataString.length());
}

void GifDecoder::SetGifData(std::string gifData) {
    _gifDataString = gifData;
}

cv::Mat GifDecoder::DecodeGifHandler(const unsigned char *buffer, const size_t len) {
    cv::Mat result;
    int error = 0;

    GifData gifData;
    gifData.data = buffer;
    gifData.len = len;
    gifData.pos = 0;

    GifFileType* gifFile = DGifOpen(&gifData, GifDataFunction, &error);

    if(!gifFile || error){
        std::cerr << "Gif Data Open Failed " << error << std::endl;
    }

    error = DGifSlurp(gifFile);

    if(error != GIF_OK){
        std::cerr << "DGifSlurp Failed:" << GifErrorString(error) << std::endl;
        DGifCloseFile(gifFile, &error);
        return result;
    }

    if(gifFile->ImageCount <= 0 || gifFile->Image.Width <= 0 || gifFile->Image.Height <= 0){
        std::cerr << "Gif Image Has No Frames " << std::endl;
        DGifCloseFile(gifFile, &error);
        return result;
    }

    result = cv::Mat(cv::Size(gifFile->Image.Width , gifFile->Image.Height), CV_8UC3);

    const ColorMapObject* ColorMap = (gifFile->Image.ColorMap ? gifFile->Image.ColorMap : gifFile->SColorMap);
    const unsigned char* src = gifFile->SavedImages[0].RasterBits;

    for (int i = 0; i < gifFile->Image.Height; i++)
    {
        unsigned char* dst = result.data + i * result.step[0];
        int loc = gifFile->Image.Width* i;
        for (int j = 0; j < gifFile->Image.Width; j++)
        {
            GifColorType* ColorMapEntry = &(ColorMap->Colors[*(src + loc + j)]);
            //BGR
            *dst++ = ColorMapEntry->Blue;
            *dst++ = ColorMapEntry->Green;
            *dst++ = ColorMapEntry->Red;
        }
    }

    DGifCloseFile(gifFile, &error);
    return result;

    return result;
}

unsigned char *GifDecoder::EncodeGif(cv::Mat mat) {

    Byte* buffer = static_cast<Byte *>(malloc(mat.cols * mat.rows * sizeof(Byte)));
    memcpy(buffer, mat.data, mat.cols * mat.rows * sizeof(Byte));
    return buffer;
}

