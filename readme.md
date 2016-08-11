# Game of Life



> The Game of Life, also known simply as Life, is a cellular automaton devised by the British mathematician John Horton Conway in 1970.

[Source: Wikipedia](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life)

This program is a simulation based on Conway's Game of Life. The program takes input from the user in the form of an `.ini` file. The file dictates the dimensions of the grid, the initial population, and the delay between each generation switch in `milliseconds`.


![gif](https://media.giphy.com/media/3owyp7MtFzp7RlEXqo/giphy.gif "GIF")


## The Golden Four Rules

Four rules are followed in the Game of Life from every cell.

* Any live cell with fewer than two live neighbours dies, as if caused by under-population.
* Any live cell with two or three live neighbours lives on to the next generation.
* Any live cell with more than three live neighbours dies, as if by over-population.
* Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.


## Optimization

The program uses two primary **data structures**. A 2D array for the grid of Cells, and a LinkedList for all *alive* cells. Instead of looping over every single cell, dead or alive, this optimization strategy saves time by looping around *only* the living cells. The LinkedList is used for this purpose, as it has `O(1)` insertion. This means the update generation method's speed went from `O(length * width)` to `O(length * width - DEADCELLS)`. This optimization's best case is when the population of the grid is **not** nearing capacity.

### Example

Instead of searching every single cell in this figure:

![img1](http://imgur.com/5QngK5K "Example Cell Array")

I will only need to search through the cells highlighted in black/pink.

![img2](http://imgur.com/AC1BLsn "Example Cell Array")


## Installation

This program requires Windows to run correcty. However, the source code is provided incase you would like to open and modify it in your editor.

* Download the archive from GitHub in the top right hand corner.

* Open `config.ini` and adjust the values accordingly. Each line must follow the pattern of `valuename=<NON-NEGATIVE INTEGER>` where `<NON-NEGATIVE INTEGER>` is an integer greater than `0`.

..* `population` dictates the starting amount of living cells. It must not be greater than `columns * rows`. 

..* `rows` controls the amount of rows of the grid. If the value is greater than `20`, then it can no longer be printed to the console window.

..* `columns` controls the amount of columns of the grid. If the value is greater than `77`, then it can no longer be printed to the console window.

..* `seed` is the value which handles the pseudo-random placement of the `population` before the first generation begins. A value of `0` will mean a random generation on every execution while any another integer value will lead to the same simulation on every runtime for that value.

..* `print_ms` is the amount of time in `milliseconds` between each generation being printed. If this value is set too low, output to the console window will be severely impacted. Too fast and your `stdout` stream will be overloaded. Printing will depend on your CPU.


## Contact

Please send any questions or concerns to `kev070892@gmail.com`.