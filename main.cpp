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
#include "DotWithParticles.h"
#include "Platform.h"
#include "constants.h"
#include "TextureMap.h"

class Screen {
public:
    virtual ~Screen() {};
    virtual void ProcessFrame() = 0;
    virtual void HandleEvent(SDL_Event &e) = 0;
};

class GameOrchestrator {
public:
    virtual void OnMiss() = 0;
    virtual void OnPlayAgain() = 0;
};

class GameScreen : public Screen {
public:
    GameScreen(GameOrchestrator *orchestrator, TextureMap &textureMap, PlatformPosition platformPosition = PLATFORM_RIGHT)
            : m_orchestrator(orchestrator),
              m_dot(getRandomVelocity(),
                    getRandomVelocity(),
                    textureMap),
              m_platform(platformPosition, textureMap) {
    }

    void HandleEvent(SDL_Event &e) override {
        m_platform.HandleEvent(e);
    }

    void ProcessFrame() override {
        m_platform.Move();
        m_dot.Move(m_platform);
        if (m_dot.GetBox().x > (SCREEN_WIDTH - Dot::DOT_WIDTH)) { // miss
            m_orchestrator->OnMiss();
            m_dot.Reset(getRandomVelocity(), getRandomVelocity());
        } else {
            m_platform.Render();
            m_dot.Render();
        }
    }
private:
    GameOrchestrator *m_orchestrator;
    DotWithParticles m_dot;
    Platform m_platform;

    int getRandomVelocity() const {
        return rand() % 5 + 5;
    }
};

class GameOverScreen : public Screen {
public:
    GameOverScreen(GameOrchestrator *orchestrator, Texture *gameOverTexture)
            : m_orchestrator(orchestrator),
              m_gameOverTexture(gameOverTexture) {
    }

    void HandleEvent(SDL_Event &e) override {
        if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
            m_orchestrator->OnPlayAgain();
        }
    }

    void ProcessFrame() override {
        m_gameOverTexture->Render((SCREEN_WIDTH - m_gameOverTexture->Width()) / 2,
                                  (SCREEN_HEIGHT - m_gameOverTexture->Height()) / 2);
    }
private:
    GameOrchestrator *m_orchestrator;
    Texture *m_gameOverTexture;
};

class MainWindow : public GameOrchestrator {
public:
    MainWindow() {
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

        m_window = SDL_CreateWindow("Pong!!1",
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

        reset();
    }

    ~MainWindow() {
        TTF_CloseFont(m_font);
        SDL_DestroyWindow(m_window);
        SDL_DestroyRenderer(m_renderer);

        delete m_gameOverTexture;

        for (auto const& textureMapTuple : m_textures) {
            delete textureMapTuple.second;
        }

        Mix_FreeChunk(m_miss);

        TTF_Quit();
        Mix_Quit();
        IMG_Quit();
        SDL_Quit();
    }

    void Run() {
        bool quit = false;
        SDL_Event e;
        Timer fpsTimer;

        while (!quit) {
            fpsTimer.Start();

            while (SDL_PollEvent(&e) != 0) {
                if (e.type == SDL_QUIT) {
                    quit = true;
                }
                m_currentScreen->HandleEvent(e);
            }

            SDL_SetRenderDrawColor(m_renderer, 0x00, 0x00, 0x00, 0xFF);
            SDL_RenderClear(m_renderer);

            m_currentScreen->ProcessFrame();
            std::ostringstream livesLabelText("");
            livesLabelText << "Lives: " << m_lives;
            Texture livesLabel(livesLabelText.str(), m_renderer, m_font, {0xFF, 0xFF, 0xFF, 0xFF});
            livesLabel.Render(SCREEN_WIDTH - 100, 10);

            SDL_RenderPresent(m_renderer);

            auto frameTicks = fpsTimer.GetTicks();
            if (frameTicks < TARGET_TICKS_PER_FRAME) {
                SDL_Delay(TARGET_TICKS_PER_FRAME - frameTicks);
            }
        }
    }

    void OnMiss() override {
        Mix_PlayChannel(-1, m_miss, 0);
        m_lives -= 1;
        if (m_lives >= 0) {
            return;
        }
        if (m_currentScreen != nullptr) {
            delete m_currentScreen;
        }
        m_currentScreen = makeGameOverScreen();
    }

    void OnPlayAgain() override {
        reset();
    }

private:
    void loadMedia() {
        m_font = TTF_OpenFont("lazy.ttf", 18);
        if (m_font == nullptr) {
            handleTTFError("Failed to load font");
        }

        try {
            m_gameOverTexture = new Texture("Game Over! Press any key to play again...", m_renderer, m_font, {0xFF, 0xFF, 0xFF, 0xFF});

            m_textures["dot"] = new Texture(m_renderer, "dot.png");
            m_textures["platform"] = new Texture(m_renderer, "platform.png");
            m_textures["particle_red"] = new Texture(m_renderer, "red.bmp", true);
            m_textures["particle_green"] = new Texture(m_renderer, "green.bmp", true);
            m_textures["particle_blue"] = new Texture(m_renderer, "blue.bmp", true);
            m_textures["particle_shimmer"] = new Texture(m_renderer, "shimmer.bmp", true);

        } catch (TextureLoadException &e) {
            handleError("Failed to load dot texture", e);
        }

        m_miss = Mix_LoadWAV("flush.wav");
        if (m_miss == nullptr) {
            handleMixError("Failed to load sample");
        }
    }

    void reset() {
        if (m_currentScreen != nullptr) {
            delete m_currentScreen;
        }
        m_currentScreen = makeGameScreen();
        m_lives = 3;
    }

    Screen* makeGameScreen() {
        return new GameScreen(this, m_textures);
    }

    Screen* makeGameOverScreen() {
        return new GameOverScreen(this, m_gameOverTexture);
    }

    void handleSDLError(std::string customMessage) {
        std::cerr << customMessage << " SDL Error: " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    void handleIMGError(std::string customMessage) {
        std::cerr << customMessage << " SDL_image Error: " << IMG_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    void handleMixError(std::string customMessage) {
        std::cerr << customMessage << " SDL_mixer Error: " << Mix_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    void handleTTFError(std::string customMessage) {
        std::cerr << customMessage << " SDL_ttf Error: " << TTF_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    void handleError(std::string customMessage, std::exception &e) {
        std::cerr << customMessage << " Exception: " << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }

    SDL_Window  *m_window = nullptr;
    SDL_Renderer *m_renderer = nullptr;
    Texture *m_gameOverTexture = nullptr;
    TTF_Font *m_font = nullptr;
    TextureMap m_textures;

    Mix_Chunk *m_miss = nullptr;

    Screen *m_currentScreen = nullptr;

    int m_lives;
};

int main(int argc, char *argv[]) {
    auto w = MainWindow();
    w.Run();
    return 0;
}

