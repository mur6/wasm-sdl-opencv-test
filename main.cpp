#include <fstream>
#include <iostream>
#include <string>

#include <SDL/SDL.h>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <emscripten.h>
#include <emscripten/bind.h>


cv::Mat processImage(const cv::Mat& input) {
    cv::Mat gray, blur, detectedEdges;
    // gray
    cv::cvtColor(input, gray, cv::COLOR_RGB2GRAY);
    // blur
    double sigma = 0.91641;
    int filterLength = 9;
    GaussianBlur(gray, blur, cv::Size(filterLength, filterLength), sigma, sigma, cv::BORDER_REPLICATE);
    // canny edge
    double canny_lowThreshold=100, canny_highThreshold=200;
    Canny(blur, detectedEdges, canny_lowThreshold, canny_highThreshold, 3);
    return detectedEdges;
}

void image_input(int offset, size_t size, int width, int height) {
    uint8_t *pos;
    pos = reinterpret_cast<uint8_t *>(offset);
    cv::Mat inputImage(height, width, CV_8UC4, pos);

    //std::cout << "INPUT: width=" << width << ", height=" << height << std::endl;

    SDL_Surface *screen = nullptr;
    SDL_Init(SDL_INIT_VIDEO);
    screen = SDL_SetVideoMode(width, height, 32, SDL_SWSURFACE);

    if (SDL_MUSTLOCK(screen))
        SDL_LockSurface(screen);


    cv::Mat processed = processImage(inputImage);

    cv::Mat outputCanvasImage(inputImage.size().height, inputImage.size().width, CV_8UC4, screen->pixels);

    cv::cvtColor(processed, outputCanvasImage, cv::COLOR_GRAY2RGBA);
    //std::cout << "outputCanvasImage=" << outputCanvasImage << std::endl;
    if (SDL_MUSTLOCK(screen))
        SDL_UnlockSurface(screen);
    SDL_Flip(screen);
}

EMSCRIPTEN_BINDINGS(my_module) {
    emscripten::function("image_input", &image_input);
}
