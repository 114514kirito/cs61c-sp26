import sys
import unittest
from framework import AssemblyTest, print_coverage, _venus_default_args
from tools.check_hashes import check_hashes

"""
Coverage tests for project 2 is meant to make sure you understand
how to test RISC-V code based on function descriptions.
Before you attempt to write these tests, it might be helpful to read
unittests.py and framework.py.
Like project 1, you can see your coverage score by submitting to gradescope.
The coverage will be determined by how many lines of code your tests run,
so remember to test for the exceptions!
"""

"""
abs_loss
# =======================================================
# FUNCTION: Get the absolute difference of 2 int arrays,
#   store in the result array and compute the sum
# Arguments:
#   a0 (int*) is the pointer to the start of arr0
#   a1 (int*) is the pointer to the start of arr1
#   a2 (int)  is the length of the arrays
#   a3 (int*) is the pointer to the start of the result array

# Returns:
#   a0 (int)  is the sum of the absolute loss
# Exceptions:
# - If the length of the array is less than 1,
#   this function terminates the program with error code 36.
# =======================================================
"""


class TestAbsLoss(unittest.TestCase):
    def test_simple(self):
        t = AssemblyTest(self, "../coverage-src/abs_loss.s")
        array0 = t.array([1, 2, 3, 4, 5])
        array1 = t.array([6, 4, 2, 0, 8])
        result = t.array([-1, -1, -1, -1, -1])
        t.input_array("a0", array0)
        t.input_array("a1", array1)
        t.input_scalar("a2", len(array0))
        t.input_array("a3", result)
        t.call("abs_loss")
        t.check_array(result, [5, 2, 1, 4, 3])
        t.check_scalar("a0", 15)
        t.execute()

    def test_length_1(self):
        t = AssemblyTest(self, "../coverage-src/abs_loss.s")
        array0 = t.array([7])
        array1 = t.array([3])
        result = t.array([-1])
        t.input_array("a0", array0)
        t.input_array("a1", array1)
        t.input_scalar("a2", 1)
        t.input_array("a3", result)
        t.call("abs_loss")
        t.check_array(result, [4])
        t.check_scalar("a0", 4)
        t.execute()

    def test_negative(self):
        t = AssemblyTest(self, "../coverage-src/abs_loss.s")
        array0 = t.array([-5, 10, -3])
        array1 = t.array([2, -4, -3])
        result = t.array([-1, -1, -1])
        t.input_array("a0", array0)
        t.input_array("a1", array1)
        t.input_scalar("a2", len(array0))
        t.input_array("a3", result)
        t.call("abs_loss")
        t.check_array(result, [7, 14, 0])
        t.check_scalar("a0", 21)
        t.execute()

    def test_invalid_n(self):
        t = AssemblyTest(self, "../coverage-src/abs_loss.s")
        array0 = t.array([1, 2])
        array1 = t.array([3, 4])
        result = t.array([-1, -1])
        t.input_array("a0", array0)
        t.input_array("a1", array1)
        t.input_scalar("a2", 0)
        t.input_array("a3", result)
        t.call("abs_loss")
        t.execute(code=36)

    @classmethod
    def tearDownClass(cls):
        print_coverage("abs_loss.s", verbose=False)


"""
squared_loss
# =======================================================
# FUNCTION: Get the squared difference of 2 int arrays,
#   store in the result array and compute the sum
# Arguments:
#   a0 (int*) is the pointer to the start of arr0
#   a1 (int*) is the pointer to the start of arr1
#   a2 (int)  is the length of the arrays
#   a3 (int*) is the pointer to the start of the result array

# Returns:
#   a0 (int)  is the sum of the squared loss
# Exceptions:
# - If the length of the array is less than 1,
#   this function terminates the program with error code 36.
# =======================================================
"""


class TestSquaredLoss(unittest.TestCase):
    def test_simple(self):
        t = AssemblyTest(self, "../coverage-src/squared_loss.s")
        array0 = t.array([1, 2, 3])
        array1 = t.array([4, 5, 6])
        result = t.array([-1, -1, -1])
        t.input_array("a0", array0)
        t.input_array("a1", array1)
        t.input_scalar("a2", len(array0))
        t.input_array("a3", result)
        t.call("squared_loss")
        # (1-4)^2=9, (2-5)^2=9, (3-6)^2=9 → sum=27
        t.check_array(result, [9, 9, 9])
        t.check_scalar("a0", 27)
        t.execute()

    def test_length_1(self):
        t = AssemblyTest(self, "../coverage-src/squared_loss.s")
        array0 = t.array([10])
        array1 = t.array([7])
        result = t.array([-1])
        t.input_array("a0", array0)
        t.input_array("a1", array1)
        t.input_scalar("a2", 1)
        t.input_array("a3", result)
        t.call("squared_loss")
        t.check_array(result, [9])
        t.check_scalar("a0", 9)
        t.execute()

    def test_negative(self):
        t = AssemblyTest(self, "../coverage-src/squared_loss.s")
        array0 = t.array([-3, -1])
        array1 = t.array([1, -5])
        result = t.array([-1, -1])
        t.input_array("a0", array0)
        t.input_array("a1", array1)
        t.input_scalar("a2", len(array0))
        t.input_array("a3", result)
        t.call("squared_loss")
        # (-3-1)^2=16, (-1-(-5))^2=16 → sum=32
        t.check_array(result, [16, 16])
        t.check_scalar("a0", 32)
        t.execute()

    def test_invalid_n(self):
        t = AssemblyTest(self, "../coverage-src/squared_loss.s")
        array0 = t.array([1, 2])
        array1 = t.array([3, 4])
        result = t.array([-1, -1])
        t.input_array("a0", array0)
        t.input_array("a1", array1)
        t.input_scalar("a2", -1)
        t.input_array("a3", result)
        t.call("squared_loss")
        t.execute(code=36)

    @classmethod
    def tearDownClass(cls):
        print_coverage("squared_loss.s", verbose=False)


"""
zero_one_loss
# =======================================================
# FUNCTION: Generates a 0-1 classifer array inplace in the result array,
#  where result[i] = (arr0[i] == arr1[i])
# Arguments:
#   a0 (int*) is the pointer to the start of arr0
#   a1 (int*) is the pointer to the start of arr1
#   a2 (int)  is the length of the arrays
#   a3 (int*) is the pointer to the start of the result array

# Returns:
#   NONE
# Exceptions:
# - If the length of the array is less than 1,
#   this function terminates the program with error code 36.
# =======================================================
"""


class TestZeroOneLoss(unittest.TestCase):
    def test_simple(self):
        t = AssemblyTest(self, "../coverage-src/zero_one_loss.s")
        array0 = t.array([1, 2, 3, 4, 5])
        array1 = t.array([1, 0, 3, 0, 6])
        result = t.array([-1, -1, -1, -1, -1])
        t.input_array("a0", array0)
        t.input_array("a1", array1)
        t.input_scalar("a2", len(array0))
        t.input_array("a3", result)
        t.call("zero_one_loss")
        # 1==1→1, 2!=0→0, 3==3→1, 4!=0→0, 5!=6→0
        t.check_array(result, [1, 0, 1, 0, 0])
        t.execute()

    def test_all_equal(self):
        t = AssemblyTest(self, "../coverage-src/zero_one_loss.s")
        array0 = t.array([5, 5, 5])
        array1 = t.array([5, 5, 5])
        result = t.array([-1, -1, -1])
        t.input_array("a0", array0)
        t.input_array("a1", array1)
        t.input_scalar("a2", len(array0))
        t.input_array("a3", result)
        t.call("zero_one_loss")
        t.check_array(result, [1, 1, 1])
        t.execute()

    def test_all_unequal(self):
        t = AssemblyTest(self, "../coverage-src/zero_one_loss.s")
        array0 = t.array([1, 2, 3])
        array1 = t.array([4, 5, 6])
        result = t.array([-1, -1, -1])
        t.input_array("a0", array0)
        t.input_array("a1", array1)
        t.input_scalar("a2", len(array0))
        t.input_array("a3", result)
        t.call("zero_one_loss")
        t.check_array(result, [0, 0, 0])
        t.execute()

    def test_length_1_equal(self):
        t = AssemblyTest(self, "../coverage-src/zero_one_loss.s")
        array0 = t.array([42])
        array1 = t.array([42])
        result = t.array([-1])
        t.input_array("a0", array0)
        t.input_array("a1", array1)
        t.input_scalar("a2", 1)
        t.input_array("a3", result)
        t.call("zero_one_loss")
        t.check_array(result, [1])
        t.execute()

    def test_invalid_n(self):
        t = AssemblyTest(self, "../coverage-src/zero_one_loss.s")
        array0 = t.array([1, 2])
        array1 = t.array([3, 4])
        result = t.array([-1, -1])
        t.input_array("a0", array0)
        t.input_array("a1", array1)
        t.input_scalar("a2", 0)
        t.input_array("a3", result)
        t.call("zero_one_loss")
        t.execute(code=36)

    @classmethod
    def tearDownClass(cls):
        print_coverage("zero_one_loss.s", verbose=False)


"""
initialize_zero
# =======================================================
# FUNCTION: Initialize a zero array with the given length
# Arguments:
#   a0 (int) size of the array

# Returns:
#   a0 (int*)  is the pointer to the zero array
# Exceptions:
# - If the length of the array is less than 1,
#   this function terminates the program with error code 36.
# - If malloc fails, this function terminates the program with exit code 26.
# =======================================================
"""


class TestInitializeZero(unittest.TestCase):
    def test_simple(self):
        t = AssemblyTest(self, "../coverage-src/initialize_zero.s")
        t.input_scalar("a0", 5)
        t.call("initialize_zero")
        t.check_array_pointer("a0", [0, 0, 0, 0, 0])
        t.execute()

    def test_length_1(self):
        t = AssemblyTest(self, "../coverage-src/initialize_zero.s")
        t.input_scalar("a0", 1)
        t.call("initialize_zero")
        t.check_array_pointer("a0", [0])
        t.execute()

    def test_length_10(self):
        t = AssemblyTest(self, "../coverage-src/initialize_zero.s")
        t.input_scalar("a0", 10)
        t.call("initialize_zero")
        t.check_array_pointer("a0", [0, 0, 0, 0, 0, 0, 0, 0, 0, 0])
        t.execute()

    def test_invalid_n(self):
        t = AssemblyTest(self, "../coverage-src/initialize_zero.s")
        t.input_scalar("a0", 0)
        t.call("initialize_zero")
        t.execute(code=36)

    def test_fail_malloc(self):
        t = AssemblyTest(self, "../coverage-src/initialize_zero.s")
        t.input_scalar("a0", 5)
        t.call("initialize_zero")
        t.execute(fail="malloc", code=26)

    @classmethod
    def tearDownClass(cls):
        print_coverage("initialize_zero.s", verbose=False)


if __name__ == "__main__":
    split_idx = sys.argv.index("--")
    for arg in sys.argv[split_idx + 1 :]:
        _venus_default_args.append(arg)

    check_hashes()

    unittest.main(argv=sys.argv[:split_idx])
