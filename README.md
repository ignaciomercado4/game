
# Game: The Game

An undefined theme game

## How to run

### Linux

1.  Go to the project folder.
    
2.  Run:
    
    `./system.sh` 
    
3.  If compilation fails:
    
    -   Install any missing libraries displayed in the console.
        
    -   Check your system’s supported OpenGL version with:
        
        `./system_support.sh` 
        
    
    This project requires **OpenGL 4.3**. Systems that do not support it **will not be able to run the game**.
    
    -   As an alternative, you can change the OpenGL version requested in `src/core/window.c` (warning: may cause errors or break it even more).
        

### Windows

Not officially supported yet.  
You can try compiling with MinGW and debugging manually. A proper Windows setup will probably be added in the future.

----------
## Structure

This game is written in **C**, using **OpenGL** as the graphics API and **GLSL** as the shading language.  
It also includes a small math library I developed for OpenGL 3D graphics: [math_n](https://gist.github.com/ignaciomercado4/2886393488d31b14ed39860f3d0403e9).

### Folder layout

    src/
    │── main.c               # entry point
    │
    ├── core/                # engine core
    │   ├── window.c/.h      # window creation and management
    │   ├── input.c/.h       # input handling
    │   ├── utils.c/.h       # utilities and debugging
    │
    ├── graphics/            # rendering
    │   ├── shader.c/.h      # GLSL shaders
    │   ├── texture.c/.h     # textures
    │   ├── light.c/.h       # lighting
    │   ├── VAO.c/.h         # vertex array objects
    │   ├── VBO.c/.h         # vertex buffer objects
    │
    ├── math/                # math library
    │   ├── math_n.c/.h
    │
    ├── game/                # game logic
    │   ├── camera.c/.h
    │   ├── floor.c/.h
    │   ├── wall.c/.h
    │   ├── level.c/.h
    │   ├── NPC.c/.h
    │
    levels/                  # binary level files
