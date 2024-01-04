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
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
/** set DEBUG macro to 1 if need debug output */
#define DEBUG 0
/** default length of input buffer, count as BYTE, but can be changed by func main's arguments */
#define LEN_INPUTBUFFER 256
static char* argvoption_0 = "--help";
static char* argvoption_1 = "--version";
static char* argvoption_2 = "-inbuf=";
/**
 * @brief main procedure
 * 
 * @param argc count of arguments
 * @param argv variable string of arguments
 * @return int program status, 0 for success
 */
int main(int argc, char* argv[])
{
    size_t i = 0;
    size_t len_inputbuffer = LEN_INPUTBUFFER;
    /** part about how to deal with arguments, boring */
    if(argc > 1){
        for(i = 1; i < (size_t)argc; i++){
            if(strncmp(argv[i], argvoption_0, strlen(argvoption_0)) == 0){
                fprintf(stderr, "\e[32mOptions:\e[0m\n");
                fprintf(stderr, "\
%s%%d : set inputbuffer to %%d Byte(s), by default 256 Bytes\n", argvoption_2);
                fprintf(stderr, "\e[32mUsage:\e[0m\n");
                fprintf(stderr, "\
Enter a string of byte as bind group of 2 hexadecimal numbers without neither prefix nor suffix to get checksum (XOR each byte), \n\
for example just input `01 02 03` to get the XOR checksum equals to (0x01 XOR 0x02 XOR 0x03)\n\
Or a single 'q' to quit\n");
                fprintf(stderr, "\e[32mNotice:\e[0m\n");
                fprintf(stderr, "\
if the input are not formatted as 2-bind-hexadecimal numbers, the method how to output is \e[31mU\e[0mndefined \e[31mB\e[0mehavior. \n\
Each group should be 2 numbers(neither less nor more). `01 02` is acceptable for (0x01 XOR 0x02), but `01 2` doesn't make such output.\n\
");
                return 0;
            }
            else if(strncmp(argv[i], argvoption_1, strlen(argvoption_1)) == 0){
                fprintf(stderr, "simple XOR checksum tool\nversion 0.0.1\n");
                fprintf(stderr, "author:Knightana issue-contact:https://github.com/Knighthana\n");
                return 0;
            }
            else if(strncmp(argv[i], argvoption_2, strlen(argvoption_2)) == 0){
                len_inputbuffer = (int) strtoul(argv[i]+12, NULL, 10);
                continue;
            }
            else{}
        }
    }
    unsigned char checksum = 0;
    char input[len_inputbuffer];
    char each_hexa_char[3];
    size_t len = 0;
    unsigned char value = 0;
    unsigned int value_temp = 0;
    do{
        printf("Enter a string of hexadecimal numbers or a single 'q' to quit:\n");
        memset(input, 0x0, len_inputbuffer);
        if(NULL == fgets(input, len_inputbuffer, stdin)){
            break;
        }
        else if(input[0] == 'q' || input[0] == 'Q'){
            break;
        }
        else if(input[0] == EOF){
            break;
        }
        else{
            len = strlen(input);
            if(input[len - 1] == '\n') len--;
            #if DEBUG
            fprintf(stderr, "\e[33mD\e[0m:%s:inputlen=%lu\n", __func__, len);
            #endif
        }
        checksum = 0;
        for(i = 0; i < len - 1; i++){
            if(input[i] == ' '){
                continue;
            }else{}
            each_hexa_char[0] = input[i];
            i++;
            if(input[i] == ' ' || !(i < len)){
                continue;
            }else{}
            each_hexa_char[1] = input[i];
            each_hexa_char[2] = 0x0;
            #if DEBUG
            fprintf(stderr, "\e[33mD\e[0m:%s:hexachar=%c%c(%d%d),i=%lu,len=%lu\n", __func__, each_hexa_char[0], each_hexa_char[1], each_hexa_char[0], each_hexa_char[1], i, len);
            #endif
            if(1 == (sscanf(each_hexa_char, "%02x", &value_temp))){
                value = (unsigned char)value_temp;
                checksum ^= value;
                #if DEBUG
                fprintf(stderr, "\e[33mD\e[0m:%s:value=%x(%p), i=%lu(%p)\n", __func__, (unsigned int)value, &value, i, &i);
                #endif
            }
            else{
                fprintf(stderr, "\e[33mW\e[0m:%s:invalid input detected, ignoring.\n", __func__);
                continue;
            }
            #if DEBUG
            fprintf(stderr, "\e[33mD\e[0m:%s:loop reaches end, i=%lu\n", __func__, i);
            #endif
        }
        printf("checksum=%hhx\n", checksum);
    }
    while(1);
    printf("Program terminated.\n");
    return 0;
}
