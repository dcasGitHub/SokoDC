**Reminder:** Always start `dcdev` before using `make`.

# Reference Material

- [Starting Point](<https://dcemulation.org/?title=Introduction_to_SDL_2D_Graphics>)
- [Archived SDL 1.2 Documentation](<https://jprzywoski.github.io/sdl-docs/>)
- [SDL 1.2 Tutorials](<https://lazyfoo.net/SDL_tutorials/>)
- [Game Loop Reference](<https://members.loria.fr/PGaudry/static/Methodo/moving-sprites.html>)

# Code Snippets

```c
SDL_Surface *crate_sprites[10]; // array to store 10 crate sprites
SDL_Rect crate_positions[10]; // array to store 10 crate positions

// Initialize the array
for (int i = 0; i < 10; i++) {
    crate_sprites[i] = IMG_Load("assets/crate.png");
    // Initialize crate_positions array as needed
    crate_positions[i].x = 0; // default x position
    crate_positions[i].y = 0; // default y position
    crate_positions[i].w = 0; // default width
    crate_positions[i].h = 0; // default height
}
```
