# Paint-by-Pairs
It is solution to fix paint by pairs problem.
you can play the game online:
http://www.gamesmagazine-online.com/gameslinks/lap_puzzle.html
http://www.conceptispuzzles.com/index.aspx?uri=puzzle/link-a-pix

My program will accept one or two command line arguments. The first argument
is the name of a paint by pairs puzzle board file.
This file begins with the dimensions of the board. Next, we assign numbers
to some of the cells in the board. Each assignment begins with the x and y coordi-
nates of the cell.
My program accept one or two command line arguments. The
first is the name of the input puzzle file. If the second argument is not
provided, your program should find a solution to the puzzle (any solution)
and print that solution to std::cout. If provided, the second argument
will be the string find_all_solutions, and your program should find
all solutions.
A sample full credit output to the puzzle above is shown on the src folder.
First, the output prints the original puzzle board. For numbers greater
than or equal to 10, we switch to capital letters. Then we print the string
\Solution:", followed by the path of coordinates of each stroke, each on
its own line. The strokes may appear in any order (this sample output
has them going from short to long, but that is not required). Similarly,
the path sequence for a stroke may start at either endpoint. After the
strokes, we display a framed ASCII art version of the final image using
'X' for the painted grid cells.
If the second argument find_all_solutions is specified, your program
should output all valid, unique solutions (in any order) and then also
print at the bottom the number of solutions found, e.g., \Found 3
solution(s)". If the puzzle has no solutions, your program should print
\No solutions". Note that we define solution uniqueness by the details
of the strokes. It is possible that two difierent sets of strokes can produce
