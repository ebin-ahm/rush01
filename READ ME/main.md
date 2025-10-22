Purpose

main.c is the program entry point. It:

    parses the 16 clues from argv[1],

    initializes the grid[4][4] to zeros,

    calls solve(grid, clues), and

    prints either the solved grid or Error. 

Inputs & Outputs

    Input: a single string containing 16 digits (1..4) separated by spaces.

    Output: a 4×4 grid of digits (1..4) separated by spaces and newlines, or Error.

Data Shapes

    int clues[4][4]:

    clues[0][c] = top clue for column c

    clues[1][c] = bottom clue for column c

    clues[2][r] = left clue for row r

    clues[3][r] = right clue for row r (see parser.c README for mapping)

int grid[4][4]: all zeros initially, then filled by the solver. 


    Lifecycle
    main()
        ├─ parse_clues(argv[1], clues)
        ├─ zero-initialize grid
        ├─ if (!solve(grid, clues)) → print "Error"
        └─ else print_grid(grid)


All four nested loops in print_grid just format nicely. putnbr_c writes a single ASCII digit. 

Error Conditions

    Missing or extra arguments

    Bad clue string (not exactly 16 values 1..4)

    No solution exists

    These all lead to Error and exit code 1.