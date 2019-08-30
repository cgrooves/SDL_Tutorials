#include <stdio.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <string>

// Key press surface constants
enum KeyPressSurfaces
{
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};

// Startup for SDL and main window
bool init();

// Print out SDL error
void printSDLerror(const std::string& errorMsg);

// Load the media
bool loadMedia();

// Free the media, quit SDL
void close();

// Load individual image
SDL_Surface* loadSurface( std::string path );

/// Global variables
/// Window to render to
SDL_Window* gWindow = nullptr;

/// Surface contained by the window
SDL_Surface* gScreenSurface = nullptr;

// Images for key presses
SDL_Surface* gKeyPressSurfaces[ KEY_PRESS_SURFACE_TOTAL ];


// Current surface
SDL_Surface* gCurrentSurface = nullptr;
std::string surfaceImages[ KEY_PRESS_SURFACE_TOTAL ] = {
    "res/press.bmp",
    "res/up.bmp",
    "res/down.bmp",
    "res/left.bmp",
    "res/right.bmp"
};

/// Screen sizes
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main( int argc, char* args[] )
{
    // Start SDL2
    if (!init())
    {
        printf("Failed to initialize!");
    }
    else
    {
        // Load media
        if (!loadMedia())
        {
            printf("Failed to load media!");
        }
        else
        {
            // Main loop
            bool quit = false;
            
            // Event handler
            SDL_Event e;
            
            // set current surface
            gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ];
            
            while( !quit )
            {
                while( SDL_PollEvent(&e) != 0 )
                {
                    if ( e.type == SDL_QUIT )
                    {
                        quit = true;
                    }
                    else if ( e.type == SDL_KEYDOWN )
                    {
                        switch (e.key.keysym.sym)
                        {
                            case SDLK_UP:
                                gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ];
                                break;
                                
                            case SDLK_DOWN:
                                gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ];
                                break;
                                
                            case SDLK_RIGHT:
                                gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ];
                                break;
                                
                            case SDLK_LEFT:
                                gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ];
                                break;
                                
                            default:
                                gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ];
                                break;
                        }
                    }
                }
            
                //Aply the image
                SDL_BlitSurface( gCurrentSurface, nullptr, gScreenSurface, nullptr );
                SDL_UpdateWindowSurface(gWindow);
            }
        }
    }
    
    // Free up resources and quit SDL2
    close();
    
    return 0;
}

bool init()
{
    bool success = true;
    
    // Init SDL2
    if ( SDL_Init(SDL_VideoInit(nullptr)) < 0)
    {
        printSDLerror("Could not initialize SDL!");
        success = false;
    }
    else
    {
        // Create Window
        gWindow = SDL_CreateWindow("Caleb's SDL Tutorial",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
            SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == nullptr)
        {
            printSDLerror("SDL Window couldn't be created!");
            success = false;
        }
        else
        {
            // Get window surface
            gScreenSurface = SDL_GetWindowSurface(gWindow);
        }
    }
    
    return success;
}

void printSDLerror(const std::string& errorMsg)
{
    std::cout << errorMsg << " SDL_Error: " << SDL_GetError() << std::endl;
    return;
}

bool loadMedia()
{
    // Loading success fflag
    bool success = true;
    
    for (unsigned int i = 0; i < KEY_PRESS_SURFACE_TOTAL; ++i)
    {
        gKeyPressSurfaces[i] = loadSurface(surfaceImages[i]);
        
        // Handle an error
        if ( gKeyPressSurfaces[i] == nullptr )
        {
            success = false;
            
            printf("Failed to load %s!\n",surfaceImages[i].c_str());
        }
    }
    return success;
}

void close()
{
    // Deallocate surface
    for (unsigned int i = 0; i < KEY_PRESS_SURFACE_TOTAL; ++i)
    {
        SDL_FreeSurface( gKeyPressSurfaces[i] );
        gKeyPressSurfaces[i] = nullptr;
    }
    
    // Destroy window
    SDL_DestroyWindow(gWindow);
    gWindow = nullptr;
    
    // Quit SDL subsystems
    SDL_Quit();
}

SDL_Surface* loadSurface( std::string path )
{
    SDL_Surface* loadedSurface = SDL_LoadBMP( path.c_str() );
    if (nullptr == loadedSurface)
    {
        printSDLerror("Unable to load image!");
    }
    
    return loadedSurface;
}
