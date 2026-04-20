#ifndef EPR_GRAPHICS_DRIVER_SDL_WRAPPER_HPP
#define EPR_GRAPHICS_DRIVER_SDL_WRAPPER_HPP

#ifdef EPR_HAS_SDL3

#include <SDL3/SDL.h>
#include <epr/graphics/core/viewport.hpp>

namespace epr::graphics {
    class SDLWrapper {
    public:
        SDL_Window* sdl_window;
        SDL_Renderer* sdl_renderer;
        SDL_Texture* sdl_texture;

        SDLWrapper(SDL_InitFlags flags, int w, int h, const char *window_name, int scale) {
            SDL_Init(flags);

            sdl_window = SDL_CreateWindow(window_name, w * scale, h * scale, 0);
            sdl_renderer = SDL_CreateRenderer(sdl_window, NULL);
            sdl_texture = SDL_CreateTexture(sdl_renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, w, h);
        }

        void show_viewport(epr::graphics::Viewport &viewport) {
            int pitch = viewport.w * sizeof(uint32_t);
            SDL_UpdateTexture(sdl_texture, nullptr, viewport.at(0, 0), pitch);

            SDL_RenderClear(sdl_renderer);
            SDL_RenderTexture(sdl_renderer, sdl_texture, nullptr, nullptr);
            SDL_RenderPresent(sdl_renderer);
        }

        ~SDLWrapper() {
            SDL_DestroyTexture(sdl_texture);
            SDL_DestroyRenderer(sdl_renderer);
            SDL_DestroyWindow(sdl_window);
            SDL_Quit();
        }
    };
}

#endif

#endif