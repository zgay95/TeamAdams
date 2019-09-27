/* Imports */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/* Constants */
#define LONG 40
/* Student Data Structure */
struct Student
{
    char name[LONG];
    char num[LONG];
    char email[LONG];
    char essaygrade[LONG];
    char presentgrade[LONG];
    char termgrade[LONG];
};
/* buildData - called from main(). This function will load data fom a given file into an array of Student Structures */
int buildData(struct Student students[LONG])
{
  FILE *fp;
  int i = 0,h = 0;
  char str[LONG];
  char arr[LONG][LONG];

  /* opening file for reading */
  fp = fopen("StudentData.txt" , "r");
  /* Check if opened successfully */
  if(fp == NULL) {
    perror("Error opening file");
    exit(1);
  }
  /* get line by line and store into an 3D array */
  while( fgets(arr[i], sizeof(arr[i]), fp) != NULL ) 
  {
    arr[i][strlen(arr[i]) - 1] = '\0';
    i++;
  }
  /* Copy array contents over to the student structures */
  for (size_t j = 0; j < i; j++)
  {
    strcpy(students[h].name,arr[j]);
    strcpy(students[h].num,arr[++j]);
    strcpy(students[h].email,arr[++j]);
    strncpy(students[h].essaygrade,arr[++j],1);
    strncpy(students[h].presentgrade,arr[++j],1);
    strncpy(students[h].termgrade,arr[++j],1);
    h++;
  }
  /* close file and return the # of students created */
   fclose(fp);
   return h;
}
/* writeData - called from main(). This functions writes data back into the given file. Writes data in such a way we can reread it back on next execution */
void writeData(struct Student students[LONG], int size)
{
  FILE *fp;
  int i = 0, j = 0;
  char str[60];

  /* opening file for reading */
  fp = fopen("StudentData.txt" , "w");
  /* Check is file opened successfully */
  if(fp == NULL) {
    perror("Error opening file");
    exit(1);
   }
  /* write the data to file, each data field is put on its own line. */
  for (size_t i = 0; i < size; i++)
  {
    fprintf(fp, "%s\n", students[i].name);
    fprintf(fp, "%s\n", students[i].num);
    fprintf(fp, "%s\n", students[i].email);
    fprintf(fp, "%s\n", students[i].essaygrade);
    fprintf(fp, "%s\n", students[i].presentgrade);
    fprintf(fp, "%s\n", students[i].termgrade);
  }
  /* close file */
  fclose(fp);
}
/* printData - a util function to print the current state of the student array */
void printData(struct Student students[LONG], int size)
{
    for (size_t i = 0; i < size; i++)
  {
    printf("Name: %s\nNum: %s\nemail: %s\n %s %s %s \n",students[i].name,students[i].num,students[i].email,students[i].essaygrade,students[i].presentgrade,students[i].termgrade);
  }
}


/* main - driving function for the program */
int main()
{
  /* Create array of Student Structs and size. Array has max size of 40. */
  struct Student students[LONG];
  int size = buildData(students);

  //printData(students,size);
  writeData(students,size);
  return 0;
}