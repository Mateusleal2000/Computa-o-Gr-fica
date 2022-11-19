#ifndef CANVAS_H_
#define CANVAS_H_
#include <SDL2/SDL.h>

#include "../Scene/scene.h"

class Canvas {
   public:
    Canvas(int canvasWidth, int canvasHeight, double z, Scene scene) : scene(scene) {
        this->canvasWidth = canvasWidth;
        this->canvasHeight = canvasHeight;
        this->z = z;
    }
    ~Canvas() {
        if (this->screenSurf != nullptr)
            SDL_FreeSurface(this->screenSurf);
        if (this->surf != nullptr)
            SDL_FreeSurface(surf);
        if (this->window != nullptr)
            SDL_DestroyWindow(this->window);

        SDL_Quit();
    }

    void init();
    void update(unsigned char* pixelArray);
    void eventLoop(std::shared_ptr<Object>& pickedObj);

   private:
    int canvasWidth;
    int canvasHeight;
    double z;
    unsigned char* pixelArray = nullptr;
    Scene scene;
    SDL_Surface* surf = nullptr;
    SDL_Surface* screenSurf = nullptr;
    SDL_Window* window = nullptr;
};

#endif