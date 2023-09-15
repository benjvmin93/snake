# The game

Simple snake game on Linux terminal using ncurses C library. I started it for fun and to distract myself.

# Setup

You need to install ncurses library on Linux device according to your distribution.
For example on Ubuntu you need to type : `sudo apt-get install libncurses5-dev libncursesw5-dev`

# Start a game

1. `make && export SNAKE_ENV=`
2. `./snake {CIRCUIT_HEIGHT} {CIRCUIT_WIDTH}`

# Debug mode

If you discovered a bug or just because you want, you can try running the game in a debug mode which is allowing you to run the game step by step and give you further information when the program crashes and under the printed game board.

Just run : 
1. `make debug && export SNAKE_ENV=DEBUG`
2. `./dbg-snake [CIRCUIT_HEIGHT] [CIRCUIT_WIDTH]`

# Next features

- Add colors 
- Improve interface
