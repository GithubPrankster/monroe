# The Making of Monroe
* Monroe for the longest time was GL-based. I decided to switch to SDL2's features for drawing
since not only am I focusing on making 2d things to ease myself into stuff, but a few weights are
lifted from me, some creativity possible and a possibility to learn more about implementing
certain things.
# Notes for Goal Boxing
Goal Boxing is a very simple game. You kick a box into a goal and rack up a score in a minute.
Every kick gets you an excited voice line from the announcer (voiced by Nerdy San)
The announcer also says "Gooooooal Boxing!" on the title screen.

Now that I have a good controller I can try supporting it for the game. I may add a check to interrupt
movement for controller or keyboard if the other is trying to be used at the same time. No cheating!

The score is stored in a file as RLE and updated if the newest score is bigger. No. Cheating!!
