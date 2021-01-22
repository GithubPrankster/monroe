# DONE!
* `cute_sound.h` + `stb_vorbis.c` usage: *"what do you mean, "WAV", "OGG"? you ok in the head buddy?"*
* Framebuffer freedom: Because you believe in 320x180 rule.
* Update sound to use PhysFS-based fileops: You think you could get away with not loading from the .7z?
* Organize types/naming: We can all agree a sprite isn't merely a quad
* Input Handling: A controller for you and me, and me and you
* Fixed-Point movement: floats are for chumps! 16.16 is the way to go.
# Monroe TODO
* Blend Function Chooser: cause *you* can be choosy.
* Animation support: NOTE maybe readoff a separate .anim file for specs for now
* * Fixed-Point platformer physics: just enough for a box and a cool dude
* * High Organizing: Abstract implementation into functions for update/init/exit etc. Don't tell anyone
    engines are kinda like this.
* * Timer: 1 minute and you're out!
* * Joystick Handling: Something to do with your hands that won't make you go blind
* * * Barebones GUI: just enough for a cool (and omnious) countdown
* * * RLE Score File: noob-proof achievement tracking
* * * Woah, an actual game! (Goal Boxing)
# Notes for Goal Boxing
Goal Boxing is a very simple game. You kick a box into a goal and rack up a score in a minute.
Every kick gets you an excited voice line from the announcer (voiced by Nerdy San)
The announcer also says "Gooooooal Boxing!" on the title screen.

Now that I have a good controller I can try supporting it for the game. I may add a check to interrupt
movement for controller or keyboard if the other is trying to be used at the same time. No cheating!

The score is stored in a file as RLE and updated if the newest score is bigger. No. Cheating!!
