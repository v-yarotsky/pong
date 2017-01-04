#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdexcept>
#include <vector>
#include "texture.h"
#include "timer.h"
#include "dot.h"
#include "Platform.h"
#include "constants.h"

class MainWindow {
public:
    MainWindow();
    ~MainWindow();
    void Run();

private:
    void loadMedia();
    void handleSDLError(std::string customMessage);
    void handleIMGError(std::string customMessage);
    void handleMixError(std::string customMessage);
    void handleTTFError(std::string customMessage);
    void handleError(std::string customMessage, std::exception &e);

    SDL_Window  *m_window = nullptr;
    SDL_Renderer *m_renderer = nullptr;
    Texture *m_dotTexture = nullptr;
    Texture *m_platformTexture = nullptr;
    TTF_Font *m_font = nullptr;
};

MainWindow::MainWindow() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        handleSDLError("SDL failed to initialize");
    }
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        handleIMGError("SDL_image failed to initialize");
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 512) < 0) {
        handleMixError("Failed to initialize SDL_mixer");
    }

    if (TTF_Init() == -1) {
        handleTTFError("Failed to initialize SDL_ttf");
    }

    m_window = SDL_CreateWindow("SDL Tutorial",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              SCREEN_WIDTH,
                              SCREEN_HEIGHT,
                              SDL_WINDOW_SHOWN);
    if (m_window == nullptr) {
        handleSDLError("Could not create SDL window");
    }

    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (m_renderer == nullptr) {
        handleSDLError("SDL Failed to initialize renderer");
    }

    loadMedia();
};

MainWindow::~MainWindow() {
    TTF_CloseFont(m_font);
    m_font = nullptr;

    SDL_DestroyWindow(m_window);
    m_window = nullptr;

    SDL_DestroyRenderer(m_renderer);
    m_window = nullptr;

    delete m_dotTexture;
    m_dotTexture = nullptr;

    delete m_platformTexture;
    m_platformTexture = nullptr;

    TTF_Quit();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
};

void MainWindow::Run() {
    bool quit = false;
    SDL_Event e;

    Dot dot(m_dotTexture);
    Platform platform(m_platformTexture);

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            dot.HandleEvent(e);
            platform.HandleEvent(e);
        }

        SDL_SetRenderDrawColor(m_renderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderClear(m_renderer);

        dot.Move();
        dot.Render();

        platform.Move();
        platform.Render();

        SDL_RenderPresent(m_renderer);
    }
};

void MainWindow::loadMedia() {
    m_font = TTF_OpenFont("lazy.ttf", 14);
    if (m_font == nullptr) {
        handleTTFError("Failed to load font");
    }

    try {
        m_dotTexture = new Texture(m_renderer, "dot.png");
        m_platformTexture = new Texture(m_renderer, "platform.png");
    } catch (TextureLoadException &e) {
        handleError("Failed to laod dot texture", e);
    }
}

void MainWindow::handleSDLError(std::string customMessage) {
    std::cerr << customMessage << " SDL Error: " << SDL_GetError() << std::endl;
    exit(EXIT_FAILURE);
};

void MainWindow::handleIMGError(std::string customMessage) {
    std::cerr << customMessage << " SDL_image Error: " << IMG_GetError() << std::endl;
    exit(EXIT_FAILURE);
};

void MainWindow::handleMixError(std::string customMessage) {
    std::cerr << customMessage << " SDL_mixer Error: " << Mix_GetError() << std::endl;
    exit(EXIT_FAILURE);
};

void MainWindow::handleTTFError(std::string customMessage) {
    std::cerr << customMessage << " SDL_ttf Error: " << TTF_GetError() << std::endl;
    exit(EXIT_FAILURE);
};

void MainWindow::handleError(std::string customMessage, std::exception &e) {
    std::cerr << customMessage << " Exception: " << e.what() << std::endl;
    exit(EXIT_FAILURE);
};

int main(int argc, char *argv[]) {
    auto w = MainWindow();
    w.Run();
    return 0;
}
