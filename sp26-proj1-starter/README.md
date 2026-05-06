# 61C Project 1: snek

A C implementation of the classic Snake game, running on a character-based board with support for batch simulation and interactive play.

## Overview

The project implements core Snake game mechanics: a mutable game board, snake movement with directional characters, food consumption, wall/body collision, and multi-snake support. The program reads a board from a `.snk` file, runs one step of `update_game`, and writes the result — or runs interactively with keyboard control.

## Project Structure

```
.
├── src/
│   ├── game.c / game.h           # Core game logic (board, snakes, update, rendering)
│   ├── snake.c                   # Main executable — reads board, runs one update, outputs
│   ├── interactive_snake.c       # Interactive mode with keyboard control and threading
│   ├── snake_utils.c / snake_utils.h  # Utilities: deterministic food, LFSR, direction, random turn
│   ├── asserts.c / asserts.h     # Test assertion framework
│   ├── unit_tests.c              # Autograder unit tests
│   └── custom_tests.c            # Student-written custom tests
├── tests/                        # Integration test fixtures (.snk files: in, out, ref)
├── tools/                        # Helper scripts (hash checking, python runner)
├── Makefile                      # Build system
├── snake                         # Compiled batch-mode executable
├── interactive-snake             # Compiled interactive executable
├── unit-tests                    # Compiled unit test executable
└── custom-tests                  # Compiled custom test executable
```

## Board Characters

| Character | Meaning            |
|-----------|--------------------|
| `WASD`    | Snake head         |
| `^<v>`    | Snake body         |
| `wasd`    | Snake tail         |
| `x`       | Dead snake head    |
| `#`       | Wall               |
| `*`       | Food               |
| ` `       | Empty space        |

## Build & Run

```bash
# Build everything
make all

# Build specific targets
make snake               # Batch mode executable
make interactive-snake   # Interactive mode executable
make unit-tests          # Unit test executable
make custom-tests        # Custom test executable

# Clean build artifacts
make clean
```

## Running Tests

```bash
# Run all integration tests
make run-integration-tests

# Run a single integration test
make 01-simple
make 15-hydra

# Run unit tests
./unit-tests

# Run custom tests
./custom-tests

# Run valgrind on free_game test
make valgrind-test-free-game

# Test nonexistent input file handling
make run-nonexistent-input-file-test
```

## Usage

```bash
# Batch mode — read board, run one update, output
./snake -i tests/01-simple-in.snk -o output.snk
./snake --stdin                    # Read board from stdin

# Interactive mode
./interactive-snake                          # Default board
./interactive-snake -i board.snk             # Load custom board
./interactive-snake -i board.snk -d 0.5      # Set update delay (seconds)

# Interactive controls
#   w/a/s/d  — Move snake up/left/down/right
#   [        — Speed up
#   ]        — Slow down
#   q        — Quit
```

## Implementation Tasks

The project is broken into 7 tasks spanning 2 files:

1. **create_default_game** — Allocate and initialize the default 18×20 board with one snake and food
2. **free_game** — Free all memory associated with a game
3. **print_board** — Print the board to a file pointer
4. **Board helpers + update_game** — Character classification (`is_tail`, `is_head`, `is_snake`), direction mapping (`head_to_body`, `body_to_tail`, `get_next_row`, `get_next_col`), and the main `update_game` loop handling food, movement, and collision
5. **read_line + load_board** — Read a dynamically-sized line and load a full board from a file
6. **find_head + initialize_snakes** — Trace from each tail to find its head, then initialize all snake structs
7. **main** — Wire up argument parsing, board loading, game update, and output

## File Format (.snk)

Snake board files are ASCII text files where each line represents a row of the game board. The board is rectangular and surrounded by `#` wall characters. Snakes are represented by connected sequences of directional characters.

## Deterministic Random

The project uses a 32-bit LFSR (`det_rand`) for deterministic food placement and snake turning, ensuring reproducible test results.
