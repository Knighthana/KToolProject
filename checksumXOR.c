/**
 * @file checksumXOR.c
 * @author Knightana (https://github.com/Knighthana)
 * @brief a simple program to get XOR checksum from standard input as ASCII
 * @version 0.0.1
 * @date 2023-12-29
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/** set DEBUG macro to 1 if need debug output */
#define DEBUG 0
/** default length of input buffer, count as BYTE, but can be changed by func
 * main's arguments */
#define LEN_INPUTBUFFER 256
static char *argvoption_0 = "--help";
static char *argvoption_1 = "--version";
static char *argvoption_2 = "-inbuf=";
/**
 * @brief parse a 2-combined-byte string into one hexadecimal number
 *
 * @param array
 * @param value
 * @return int
 */
static int parseByte(char array[3], unsigned char *value) {
  *value = 0;
  char temp = 0;
  temp = array[0];
  temp -= '0';
  if (temp < 0 || temp > 9) {
    return -1;
  } else {
    *value = temp << 4;
  }
  temp = array[1];
  temp -= '0';
  if (temp < 0 || temp > 9) {
    return -2;
  } else {
    *value += temp;
  }
  return 0;
}
/**
 * @brief main procedure
 *
 * @param argc count of arguments
 * @param argv variable string of arguments
 * @return int program status, 0 for success
 */
int main(int argc, char *argv[]) {
  size_t i = 0;
  size_t len_inputbuffer = LEN_INPUTBUFFER;
  /** part about how to deal with arguments, boring */
  if (argc > 1) {
    for (i = 1; i < (size_t)argc; i++) {
      if (strncmp(argv[i], argvoption_0, strlen(argvoption_0)) == 0) {
        fprintf(stderr, "\e[32mOptions:\e[0m\n");
        fprintf(stderr, "\
 %s%%d : set inputbuffer to %%d Byte(s), by default 256 Bytes\n",
                argvoption_2);
        fprintf(stderr, "\e[32mUsage:\e[0m\n");
        fprintf(stderr, "\
 Enter a string of byte as bind of 2 hexadecimal numbers without neither prefix nor suffix to get checksum (XOR each byte)\n\
 Or a single 'q' to quit\n");
        fprintf(stderr, "\e[32mNotice:\e[0m\n");
        fprintf(stderr, "\
 if the input are not formatted as 2-bind-hexadecimal numbers, the method how to output is \e[31mU\e[0mndefined \e[31mB\e[0mehavior.\n");
        return 0;
      } else if (strncmp(argv[i], argvoption_1, strlen(argvoption_1)) == 0) {
        fprintf(stderr, "simple XOR checksum tool\nversion 0.0.1\n");
        fprintf(
            stderr,
            "author:Knighhtana issue-contact:https://github.com/Knighthana\n");
        return 0;
      } else if (strncmp(argv[i], argvoption_2, strlen(argvoption_2)) == 0) {
        len_inputbuffer = (int)strtoul(argv[i] + 12, NULL, 10);
        continue;
      } else {
      }
    }
  }
  unsigned char checksum = 0;
  char input[len_inputbuffer];
  char each_hexa_char[3];
  size_t len = 0;
  unsigned char value = 0;
  do {
    printf("Enter a string of hexadecimal numbers or a single 'q' to quit:\n");
    memset(input, 0x0, len_inputbuffer);
    if (NULL == fgets(input, len_inputbuffer, stdin)) {
      break;
    } else if (input[0] == 'q' || input[0] == 'Q') {
      break;
    } else if (input[0] == EOF) {
      break;
    } else {
      len = strlen(input);
      if (input[len - 1] == '\n')
        len--;
#if DEBUG
      fprintf(stderr, "\e[33mD\e[0m:%s:inputlen=%lu\n", __func__, len);
#endif
    }
    checksum = 0;
    for (i = 0; i < len - 1; i++) {
      if (input[i] == ' ') {
        continue;
      } else {
      }
      each_hexa_char[0] = input[i];
      i++;
      if (input[i] == ' ' || !(i < len)) {
        continue;
      } else {
      }
      each_hexa_char[1] = input[i];
      each_hexa_char[2] = 0x0;
#if DEBUG
      fprintf(stderr, "\e[33mD\e[0m:%s:hexachar=%c%c(%d%d)\n", __func__,
              each_hexa_char[0], each_hexa_char[1], each_hexa_char[0],
              each_hexa_char[1]);
#endif
      if (0 == (parseByte(each_hexa_char, &value))) {
        value = value;
        checksum ^= value;
      } else {
        fprintf(stderr, "\e[33mW\e[0m:%s:invalid input detected, ignoring.\n",
                __func__);
        continue;
      }
    }
    printf("checksum=%hhx\n", checksum);
  } while (1);
  printf("Program terminated.\n");
  return 0;
}
