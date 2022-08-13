
When the game starts the pacman is positioned at his start position (you should decide where it is) without any movement. Once the user selects move direction (using the keys, as listed below) the pacman will continue to move in this direction even if the user doesn’t press any key, as long as the pacman doesn’t hit a wall and the “STAY” key was not pressed. 
Keys:
LEFT
a or A
RIGHT
d or D
UP
w or W
Down
x or X
STAY
s or S


Menu
The game shall have the following entry menu:
(1) Start a new game
(8) Present instructions and keys
(9) EXIT

Pausing a game
Pressing the ESC key during a game pauses the game. It can be good to present a message on screen saying: “Game paused, press ESC again to continue”. But it is not mandatory to present such a message.
When the game is at pause state, pressing ESC would continue the game, with the pacman continuing his movement exactly as it was before pausing, as if the game hadn’t paused.

The screen is consisted of:
walls (you shall use any reasonable char to draw them)
pacman (use @ or any other reasonable char)
2 ghosts (use $ or any other reasonable char)
“breadcrumbs” on all unvisited positions (you shall use any reasonable char to draw them)

The pacman travels on screen and “eats the breadcrumbs”. Each eaten breadcrumb equals a point to be earned. Once all breadcrumbs on screen are eaten the game ends with a happy message of your choice. Pressing any key should get back to the main menu. 

In case a ghost eats the pacman, the player loses one “life”. If all “lives” are gone, there should be a message announcing “Game Over” then after pressing any key the main menu shall be presented. 

The ghosts hover above the breadcrumbs without eating them. You can decide how they go (no need to make them “smart”). Their pace is half the pace of the pacman (for any two steps of the pacman they make 1 step). You may decide if a ghost can go over the other ghost if they meet (i.e. both may share the same position) or not.

The pacman can cross the screen in an invisible tunnel from the rightmost position to the leftmost position of the same row and vice versa, and from the topmost position to the downmost position of the same column and vice versa, if there are no walls at both sides.
Ghosts cannot cross in those invisible tunnels!

Note that there is one screen in Ex1, which looks the same for all games.

Pacman has 3 lives. After losing a life all creatures start from the exact initial position, but without the breadcrumbs that were eaten.
A Fruit
A fruit is a single char “creature”, the char shall be a digit between 5 to 9 selected randomly, that appears at random points in time on screen and travels around randomly at a slow pace. If it meets a ghost it disappears. If the pacman eats the fruit it gets the points as the value of the digit (5 to 9).
The fruit disappears after some time.
There can be only 1 (or zero) Fruits on screen at a certain time.
Fruits cannot cross in the invisible tunnels!

Smarter Ghosts
Game shall have 3 possible levels (either in the main menu or after starting a game):
(a) BEST (b) GOOD and (c) NOVICE
BEST - Ghost try to chase the pacman
GOOD - Ghost try to chase the pacman, but occasionally (randomly, once in ~20 moves) they just change to a random direction and stay with it for 5 moves before being smart again
NOVICE - Ghost just move on screen with a direction selected randomly every 20 moves

Loading Screens from files
The game would look for files in the working directory, with the names pacman_*.screen these files would be loaded in lexicographical order (i.e. pacman_a.screen before pacman_b.screen or pacman_01.screen before pacman_02.screen etc.).
You need to submit 3 screens with your exercise!
If there are no files, a proper message would be presented when trying to start a new game.
The menu should have a new option to allow running a specific screen, by name.
The screen file should be a text file representing the screen, with:
@ - for the position of the pacman (1 and only)
$ - for the initial position of the ghosts (allow any number between 0 to 4)
# - for walls
% - for “empty” positions that should not have a breadcrumb
& - for the position where the points and remaining lives information (“legend”) shall be presented, it is the responsibility of the screen designer (not of your program) to make sure that the & is placed in a position not accessible by the creatures. You may assume that the screen designer follows this instruction. The size of the actual printed legend shall be not more than 3 lines height * 20 characters.
Note that the above chars are mandatory, even if you use other chars for drawing the board on screen. Note also that the file doesn’t contain breadcrumbs and you should add them yourself when drawing the screen.
