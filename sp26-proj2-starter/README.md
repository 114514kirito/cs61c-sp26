# 61C Project 2: CS61Classify

RISC-V assembly implementation of a two-layer neural network classifier, simulated with the Venus RISC-V simulator.

## Overview

CS61Classify reads two weight matrices and an input matrix from binary files, performs a forward pass through a two-layer neural network (matrix multiply → ReLU → matrix multiply), writes the output to a file, and returns the predicted class via argmax.

## Project Structure

```
.
├── src/                   # RISC-V assembly source files
│   ├── main.s             # Entry point — calls classify
│   ├── classify.s         # Full classification pipeline
│   ├── matmul.s           # Matrix multiplication
│   ├── dot.s              # Dot product with configurable strides
│   ├── read_matrix.s      # Read binary matrix from file
│   ├── write_matrix.s     # Write binary matrix to file
│   ├── relu.s             # ReLU activation (in-place)
│   ├── argmax.s           # Index of maximum element in array
│   ├── abs.s              # Element-wise absolute value
│   └── utils.s            # Utilities: malloc, free, print, exit, compare_int_array
├── coverage-src/          # Additional functions for coverage testing
│   ├── abs_loss.s         # Absolute difference loss
│   ├── squared_loss.s     # Squared difference loss
│   ├── zero_one_loss.s    # 0-1 classification loss
│   └── initialize_zero.s  # Zero-initialized array allocation
├── tests/                 # Binary test fixtures (input/reference files)
├── test-src/              # Generated assembly test files (auto-created)
├── tools/                 # Venus JAR simulator and helper scripts
├── framework.py           # Test framework for assembly unit tests
├── unittests.py           # Unit tests (autograder tests)
├── studenttests.py        # Coverage tests (student-written)
├── test.sh                # Test runner
└── convert.py             # ASCII ↔ binary matrix converter
```

## Usage

### Running Tests

```bash
# Run all unit tests
bash test.sh all

# Run coverage tests
bash test.sh coverage

# Run tests for a specific function
bash test.sh test_abs
bash test.sh test_relu
bash test.sh test_argmax
bash test.sh test_dot
bash test.sh test_matmul
bash test.sh test_read_matrix
bash test.sh test_write_matrix
bash test.sh test_classify
bash test.sh test_chain
```

### Converting Matrix Files

```bash
# ASCII → binary
python3 convert.py input.txt output.bin --to-binary

# Binary → ASCII
python3 convert.py input.bin output.txt --to-ascii
```

### Binary Matrix Format

Binary matrix files store dimensions as two 4-byte signed little-endian integers (rows, cols), followed by the matrix elements in row-major order (each element is a 4-byte signed little-endian integer).

## Classification Pipeline

`classify.s` executes the following steps:

1. **Read** weight matrices m0, m1 and the input matrix from binary files via `read_matrix`
2. **Hidden layer**: `h = matmul(m0, input)` then `relu(h)`
3. **Output layer**: `o = matmul(m1, h)`
4. **Write** output matrix `o` to file via `write_matrix`
5. **Predict**: `argmax(o)` returns the class label
6. If not in silent mode, print the classification and a newline

## Exit Codes

| Code | Meaning                   |
|------|---------------------------|
| 26   | Malloc failure            |
| 27   | File open failure         |
| 28   | File close failure        |
| 29   | File read failure         |
| 30   | File write failure        |
| 31   | Incorrect number of args  |
| 36   | Invalid length/dimension  |
| 37   | Invalid stride            |
| 38   | Invalid matrix dimension  |
