/*=============================================================================
| Assignment: pa02 - Calculating an 8, 16, or 32 bit
| checksum on an ASCII input file
|
| Author: Terence Wilchcombe
| Language: c
|
| To Compile:
| gcc -o pa02 pa02.c
|
|
| To Execute:
| or c -> ./pa02 inputFile.txt 8
| where inputFile.txt is an ASCII input file
| and the number 8 could also be 16 or 32
| which are the valid checksum sizes, all
| other values are rejected with an error message
| and program termination
|
| Note: All input files are simple 8 bit ASCII input
|
| Class: CIS3360 - Security in Computing - Spring 2022
| Instructor: McAlpin
| Due Date: per assignment (April 3rd)
|
+=============================================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
//Takes the contents from the given file and stores them into a usable list
// checksum function for when size is 8
void cs_eight(char *in_x, int size_var){
//initializing variables
long int checksum = 0;
int x, ct = 0;
//checksum output coding
for (x = 0; x < strlen(in_x); x++)
{
ct++;
checksum = (checksum + in_x[x]) % 256;
}
// "\ n used for formatting issue
printf("\n%2d bit checksum is %8lx for all %4d chars\n", size_var, checksum,
ct);
return;
}
// generates checksum for when 16 bit size variable is used
int cs_sixteen(char *my_list, int size_var){
//initializing variables
long int temp, checksum, wia;
int x, ct = 2;
temp = my_list[0] << 8;
temp = temp + my_list[1];
//performs checksum calculation
for (x = 2; x < strlen(my_list); x++)
{
if (x % 2 == 1)
{
wia = my_list[x-1] << 8;
wia = wia + my_list[x];
temp = (temp + wia) % 65536;
}
ct++;
}
checksum = temp;
printf("%2d bit checksum is %8lx for all %4d chars\n", size_var, checksum,
ct);
return 0;
}
// padding function for when size is 16
char *pad_sixteen(char *my_list, int size_var)
{
//initializing variables
int x, ct = 0;
for (x = 0; x < 256; x++){
if (my_list[x] == '\0'){
break;
}
ct++;
}
 //adds "X" padding character to list and outputs it
if (ct % 2 != 0){
my_list[x] = 'X';
printf("%c\n", my_list[x]);
my_list[x+1] = '\0';
}
return my_list;
}
// generates the checksum for when 32 bit size variable is used
int cs_thirty_two(char *my_list, int size_var){
//declaring variables
int x, ct = 4;
long int temp, wia, checksum;
//initializes checksum calculation
temp = my_list[0] << 8;
temp = (temp + my_list[1]) << 8;
temp = (temp + my_list[2]) << 8;
temp = (temp + my_list[3]);
//preforms checksum calculation for the rest of the list
for (x = 4; x < strlen(my_list); x++){
if (x % 4 == 0){
wia = my_list[x] << 8;
wia = (wia + my_list[x+1]) << 8;
wia = (wia + my_list[x+2]) << 8;
wia = (wia + my_list[x+3]);
temp = (temp + wia) % 4294967296;
}
ct++;
}
checksum = temp;
printf("%2d bit checksum is %8lx for all %4d chars\n", size_var, checksum,
ct);
return 0;
}
// padding function for when size is 32
char *pad_thirty_two (char *my_list, int size_var){
//declares variables
long int checksum = 0;
int x, ct = 0;
for (x = 0; x < 256; x++){
if (my_list[x] == '\0'){
break;
}
ct++;
}
// accounts for cases in which different amounts of padding will be used in 32 bit situations
switch (ct % 4){
case 1:
my_list[x] = 'X';
printf("%c", my_list[x]);
my_list[x+1] = 'X';
printf("%c", my_list[x+1]);
my_list[x+2] = 'X';
printf("%c\n", my_list[x+2]);
my_list[x+3] = '\0';
break;
case 2:
my_list[x] = 'X';
printf("%c", my_list[x]);
my_list[x+1] = 'X';
 printf("%c\n", my_list[x]);
my_list[x+2] = '\0';
 break;
case 3:
my_list[x] = 'X';
printf("%c\n", my_list[x]);
my_list[x+1] = '\0';
break;
default:
break;
}
return my_list;
}
char *file_scanner(char *filename){
//variable declaration
char letter;
int x = 0, y = 0;
char *my_list = malloc(sizeof(char) * 256);
 FILE *fp = fopen(filename, "r");
//defensive coding
if (fp == NULL){
return NULL;
}
//solves formatting issue
printf("\n");
//throws file ocntents into array
while (fscanf(fp, "%c", &letter) != EOF){
printf("%c", letter);
if ((++x) % 80 == 0){
printf("\n");
}
my_list[y++] = letter;
}
my_list[y] = '\0';
fclose(fp);
return my_list;
}
int main(int argc, char **argv){
//declaring variables
char *file, *list_l;
file = argv[1];
int check, size_var;
size_var = atoi(argv[2]);
list_l = file_scanner(file);
//checks to see if the size variable inputted is one of the three allowed variables. if not, prompts user to use the three.
if (size_var != 8 && size_var != 16 && size_var != 32){
fprintf(stderr, "Valid checksum sizes are 8, 16, or 32\n");
}
// 8-bit checksum function runs
if (size_var == 8){
cs_eight(list_l, size_var);
}
// 16-bit checksum function runs
if (size_var == 16){
list_l = pad_sixteen(list_l, size_var);
cs_sixteen(list_l, size_var);
}
 // 32-bit checksum function runs
if (size_var == 32){
list_l = pad_thirty_two( list_l, size_var);
cs_thirty_two( list_l, size_var);
}
return 0;
}
/*=============================================================================
| I [Terence Wilchcombe] ([te750713]) affirm that this program is
| entirely my own work and that I have neither developed my code together with
| any another person, nor copied any code from any other person, nor permitted
| my code to be copied or otherwise used by any other person, nor have I
| copied, modified, or otherwise used programs created by others. I acknowledge
| that any violation of the above terms will be treated as academic dishonesty.
+=============================================================================*/
