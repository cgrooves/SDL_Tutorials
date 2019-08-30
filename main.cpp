#include <stdio.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <string>

// Startup for SDL and main window
bool init();

// Print out SDL error
void printSDLerror(const std::string& errorMsg);

// Load the media
bool loadMedia();

// Free the media, quit SDL
void close();

/// Global variables
/// Window to render to
SDL_Window* gWindow = nullptr;

/// Surface contained by the window
SDL_Surface* gScreenSurface = nullptr;

/// The image to load and show on the screen
SDL_Surface* gHellowWorld = nullptr;

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
            
            while( !quit )
            {
                while( SDL_PollEvent(&e) != 0 )
                {
                    switch( e.type )
                    {
                        case SDL_QUIT:
                            quit = true;
                            break;
                        default:
                            printf("other action %u\n", e.type);
                            break;
                    }
                }
            
                //Aply the image
                SDL_BlitSurface( gHellowWorld, nullptr, gScreenSurface, nullptr );
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
    
    // Load splash image
    gHellowWorld = SDL_LoadBMP( "res/hello_world.bmp" );
    if (gHellowWorld == nullptr)
    {
        printSDLerror("Unable to load the image!");
        success = false;
    }
    
    return success;
}

void close()
{
    // Deallocate surface
    SDL_FreeSurface( gHellowWorld );
    gHellowWorld = nullptr;
    
    // Destroy window
    SDL_DestroyWindow(gWindow);
    gWindow = nullptr;
    
    // Quit SDL subsystems
    SDL_Quit();
}
