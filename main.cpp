#include <iostream>
#include <gif_lib.h>
#include "giflib_to_opencv.h"

#include <opencv2/core.hpp>
#include <fstream>
#include <vector>
#include <string>
#include <GifDecoder.h>


class Trial {
public:
    static std::string encode_gif(std::vector<cv::Mat> image);

    void Test()
    {
        GifDecoder gifDecoder;
        std::ifstream stream("test.gif", std::ios::in | std::ios::binary);
        auto image_content = std::string(std::istreambuf_iterator<char>(stream), std::istreambuf_iterator<char>());
        gifDecoder.SetGifData(image_content);
        cv::Mat gifMat = gifDecoder.DecodeGif();
        std::cout << gifMat << std::endl;
        auto after = gifDecoder.EncodeGif(gifMat);
        std::ofstream out("after.gif");
        out << after;
        out.close();
    }
};




int main() {
    std::cout << "Program Started" << std::endl;
    Trial trial;

    trial.Test();

    std::cout << "Program Ended" << std::endl;
    return 0;
}

