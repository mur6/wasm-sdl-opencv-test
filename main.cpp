#include <fstream>
#include <iostream>
#include <string>

#include <SDL/SDL.h>
#include <opencv2/core/core.hpp>
#include <emscripten.h>
#include <emscripten/bind.h>

//extern "C" int main(int argc, char **argv) {
//  return 0;
//}

void image_output() {
  constexpr int WIDTH = 128;//cols
  constexpr int HEIGHT = 32;//rows
  SDL_Surface *screen = nullptr;
  SDL_Init(SDL_INIT_VIDEO);
  screen = SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_SWSURFACE);

  if (SDL_MUSTLOCK(screen))
    SDL_LockSurface(screen);
   cv::Mat A(HEIGHT, WIDTH, CV_8UC4);
   A.setTo(cv::Scalar(30,200,0));
   std::cout << "A=" << A << std::endl;
   std::cout << "width=" << A.size().width << ", height=" << A.size().height << std::endl;
  cv::Mat B(A.size().height, A.size().width, CV_8UC4, screen->pixels);
  A.copyTo(B);
  std::cout << "B=" << B << std::endl;
//   for (int i = 0; i < 32; i++) {
//     for (int j = 0; j < 32; j++) {
//       int alpha = 255;
//       *((Uint32*)screen->pixels + i * 32 + j) = SDL_MapRGBA(screen->format, i, j, 255-i, alpha);
//     }
//   }
  //std::cout << "DoValidateImageOnlyCanny screen->pixels=" << screen->pixels << std::endl;
  if (SDL_MUSTLOCK(screen))
    SDL_UnlockSurface(screen);
  SDL_Flip(screen);
}

EMSCRIPTEN_BINDINGS(my_module) {
  emscripten::function("image_output", &image_output);
}
