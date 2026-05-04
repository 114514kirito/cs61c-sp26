#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "asserts.h"
// Necessary due to static functions in game.c
#include "game.c"

/* Look at asserts.c for some helpful assert functions */

int greater_than_forty_two(int x) { return x > 42; }

bool is_vowel(char c) {
  char *vowels = "aeiouAEIOU";
  for (int i = 0; i < strlen(vowels); i++) {
    if (c == vowels[i]) {
      return true;
    }
  }
  return false;
}

/*
  Example 1: Returns true if all test cases pass. False otherwise.
    The function greater_than_forty_two(int x) will return true if x > 42. False otherwise.
    Note: This test is NOT comprehensive
*/
bool test_greater_than_forty_two() {
  int testcase_1 = 42;
  bool output_1 = greater_than_forty_two(testcase_1);
  if (!assert_false("output_1", output_1)) {
    return false;
  }

  int testcase_2 = -42;
  bool output_2 = greater_than_forty_two(testcase_2);
  if (!assert_false("output_2", output_2)) {
    return false;
  }

  int testcase_3 = 4242;
  bool output_3 = greater_than_forty_two(testcase_3);
  if (!assert_true("output_3", output_3)) {
    return false;
  }

  return true;
}

/*
  Example 2: Returns true if all test cases pass. False otherwise.
    The function is_vowel(char c) will return true if c is a vowel (i.e. c is a,e,i,o,u)
    and returns false otherwise
    Note: This test is NOT comprehensive
*/
bool test_is_vowel() {
  char testcase_1 = 'a';
  bool output_1 = is_vowel(testcase_1);
  if (!assert_true("output_1", output_1)) {
    return false;
  }

  char testcase_2 = 'e';
  bool output_2 = is_vowel(testcase_2);
  if (!assert_true("output_2", output_2)) {
    return false;
  }

  char testcase_3 = 'i';
  bool output_3 = is_vowel(testcase_3);
  if (!assert_true("output_3", output_3)) {
    return false;
  }

  char testcase_4 = 'o';
  bool output_4 = is_vowel(testcase_4);
  if (!assert_true("output_4", output_4)) {
    return false;
  }

  char testcase_5 = 'u';
  bool output_5 = is_vowel(testcase_5);
  if (!assert_true("output_5", output_5)) {
    return false;
  }

  char testcase_6 = 'k';
  bool output_6 = is_vowel(testcase_6);
  if (!assert_false("output_6", output_6)) {
    return false;
  }

  return true;
}

/* Task 4.1 */
// --- 下面是各个函数的单元测试 ---

bool test_is_tail() {
    // 技巧：把每个断言的结果存下来再 AND，这样即使中间有失败的，后续的断言也会继续执行打印出信息
    bool t1 = assert_true("is_tail('w')", is_tail('w'));
    bool t2 = assert_true("is_tail('d')", is_tail('d'));
    bool t3 = assert_false("is_tail('W')", is_tail('W')); // 大写不应该属于 tail
    bool t4 = assert_false("is_tail('^')", is_tail('^'));
    return t1 && t2 && t3 && t4;
}

bool test_is_head() {
    bool t1 = assert_true("is_head('W')", is_head('W'));
    bool t2 = assert_true("is_head('x')", is_head('x')); // 死亡状态下的蛇头
    bool t3 = assert_false("is_head('w')", is_head('w'));
    bool t4 = assert_false("is_head(' ')", is_head(' '));
    return t1 && t2 && t3 && t4;
}

bool test_is_snake() {
    bool t1 = assert_true("is_snake('w')", is_snake('w'));
    bool t2 = assert_true("is_snake('^')", is_snake('^'));
    bool t3 = assert_true("is_snake('D')", is_snake('D'));
    bool t4 = assert_false("is_snake(' ')", is_snake(' ')); // 空格不是蛇
    bool t5 = assert_false("is_snake('#')", is_snake('#')); // 墙壁不是蛇
    return t1 && t2 && t3 && t4 && t5;
}

bool test_body_to_tail() {
    bool t1 = assert_equals_char("body_to_tail('^')", 'w', body_to_tail('^'));
    bool t2 = assert_equals_char("body_to_tail('<')", 'a', body_to_tail('<'));
    bool t3 = assert_equals_char("body_to_tail('v')", 's', body_to_tail('v'));
    bool t4 = assert_equals_char("body_to_tail('>')", 'd', body_to_tail('>'));
    return t1 && t2 && t3 && t4;
}

bool test_head_to_body() {
    bool t1 = assert_equals_char("head_to_body('W')", '^', head_to_body('W'));
    bool t2 = assert_equals_char("head_to_body('A')", '<', head_to_body('A'));
    bool t3 = assert_equals_char("head_to_body('S')", 'v', head_to_body('S'));
    bool t4 = assert_equals_char("head_to_body('D')", '>', head_to_body('D'));
    return t1 && t2 && t3 && t4;
}

bool test_get_next_row() {
    // 设置当前行为 5 来进行测试
    bool t1 = assert_equals_unsigned_int("get_next_row(5, 'v')", 6, get_next_row(5, 'v'));
    bool t2 = assert_equals_unsigned_int("get_next_row(5, 'S')", 6, get_next_row(5, 'S'));
    bool t3 = assert_equals_unsigned_int("get_next_row(5, '^')", 4, get_next_row(5, '^'));
    bool t4 = assert_equals_unsigned_int("get_next_row(5, 'w')", 4, get_next_row(5, 'w'));
    bool t5 = assert_equals_unsigned_int("get_next_row(5, '<')", 5, get_next_row(5, '<')); // 不改变行的方向
    return t1 && t2 && t3 && t4 && t5;
}

bool test_get_next_col() {
    // 设置当前列为 5 来进行测试
    bool t1 = assert_equals_unsigned_int("get_next_col(5, '>')", 6, get_next_col(5, '>'));
    bool t2 = assert_equals_unsigned_int("get_next_col(5, 'd')", 6, get_next_col(5, 'd'));
    bool t3 = assert_equals_unsigned_int("get_next_col(5, '<')", 4, get_next_col(5, '<'));
    bool t4 = assert_equals_unsigned_int("get_next_col(5, 'A')", 4, get_next_col(5, 'A'));
    bool t5 = assert_equals_unsigned_int("get_next_col(5, '^')", 5, get_next_col(5, '^')); // 不改变列的方向
    return t1 && t2 && t3 && t4 && t5;
}

bool test_customs() {
  if (!test_greater_than_forty_two()) {
    printf("%s\n", "test_greater_than_forty_two failed.");
    return false;
  }
  if (!test_is_vowel()) {
    printf("%s\n", "test_is_vowel failed.");
    return false;
  }
  if (!test_is_tail()) {
    printf("%s\n", "test_is_tail failed");
    return false;
  }
  if (!test_is_head()) {
    printf("%s\n", "test_is_head failed");
    return false;
  }
  if (!test_is_snake()) {
    printf("%s\n", "test_is_snake failed");
    return false;
  }
  if (!test_body_to_tail()) {
    printf("%s\n", "test_body_to_tail failed");
    return false;
  }
  if (!test_head_to_body()) {
    printf("%s\n", "test_head_to_body failed");
    return false;
  }
  if (!test_get_next_row()) {
    printf("%s\n", "test_get_next_row failed");
    return false;
  }
  if (!test_get_next_col()) {
    printf("%s\n", "test_get_next_col failed");
    return false;
  }
  return true;
}

int main(int argc, char *argv[]) {
  init_colors();

  if (!test_and_print("custom", test_customs)) {
    return 0;
  }
  bool success = true;
    
  printf("Starting custom tests...\n\n");

  // 使用 asserts.h 提供的 test_and_print 来优雅地运行并输出测试结果
  success &= test_and_print("test_is_tail", test_is_tail);
  success &= test_and_print("test_is_head", test_is_head);
  success &= test_and_print("test_is_snake", test_is_snake);
  success &= test_and_print("test_body_to_tail", test_body_to_tail);
  success &= test_and_print("test_head_to_body", test_head_to_body);
  success &= test_and_print("test_get_next_row", test_get_next_row);
  success &= test_and_print("test_get_next_col", test_get_next_col);

  if (success) {
      printf("\n✅ ALL TESTS PASSED! YOU ARE AWESOME!\n");
      return 0;
  } else {
      printf("\n❌ SOME TESTS FAILED. CHECK THE LOGS ABOVE.\n");
      return 1;
  }  

  return 0;
}
