/* Imports */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/* Constants */
#define LONG 40
/* Student Data Structure */
struct Student{
    char name[LONG];
    char num[LONG];
    char email[LONG];
    char essaygrade[LONG];
    char presentgrade[LONG];
    char termgrade[LONG];
}students[LONG];

int total_students = 0 ; //global variable to keep track of number of students
int flip = 0 ; // switch for building the data

/* buildData - called from main(). This function will load data fom a given file into an array of Student Structures */
int buildData(){
  FILE * fp;
  int i = 0,h = 0;
  //char str[LONG];
  char arr[LONG][LONG];

  /* opening file for reading */
  fp = fopen("StudentData.txt" , "r");
  /* Check if opened successfully */
  if(fp == NULL) {
    perror("Error opening fileeee");
    exit(1);
  }

  //get line by line and store into an 3D array 
  while( fgets(arr[i], sizeof(arr[i]), fp) != NULL ) 
  {
    arr[i][strlen(arr[i]) - 1] = '\0';
    i++;
  }
  // Copy array contents over to the student structures
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

  printf("Done reading from file\n");
  
  if(flip==0){ total_students += h ; flip = 1 ;} //total number of students shouldn't change if re reading the file. Only gets updated once.
  printf("Total number of students: %d\n" , h ) ; 

  return total_students ;
}

// writeData - called from main(). This functions writes data back into the given file. Writes data in such a way we can reread it back on next execution 
void writeData() {
  FILE *fp;
  printf("SIZE OF STUDENT IS %d\n", total_students ) ;
  //opening file for reading
  fp = fopen("StudentData.txt" , "w");
  //Check is file opened successfully
  if(fp == NULL) {
    perror("Error opening filee");
    exit(1);
   }
  //write the data to file, each data field is put on its own line. 
  for (size_t i = 0; i < total_students; i++)
  {
    if (students[i].name != " ")
    {
    fprintf(fp, "%s\n", students[i].name);
    fprintf(fp, "%s\n", students[i].num);
    fprintf(fp, "%s\n", students[i].email);
    fprintf(fp, "%s\n", students[i].essaygrade);
    fprintf(fp, "%s\n", students[i].presentgrade);
    fprintf(fp, "%s\n", students[i].termgrade);
    }
  }
  //close file 
  fclose(fp);
}
/* printStudent - Prints Student data for passed student */
void printStudent(struct Student s){

  printf("\nStudent Name: %s\n" , s.name) ;
  printf("-Number: %s\n" , s.num) ;
  printf("-Email: %s\n" , s.email) ;
  printf("-Essay Grade: %s\n" , s.essaygrade) ;
  printf("-Presentation Grade: %s\n" , s.presentgrade) ;
  printf("-Term Grade: %s \n" , s.termgrade) ;
}
/* newStudent - add new student to struct array, recieve input from user */
void newStudent(){ 
  int pos = total_students ; //last position for where to add new student
  //printf("position where adding new student %d\n", pos); 

  printf("Enter new student name:");
  fgets(students[pos].name , LONG , stdin ) ;
  strtok(students[pos].name, "\n");
  printf("Enter new student number:");
  //fgets(newS.num , LONG , stdin ) ;
  fgets(students[pos].num , LONG , stdin ) ;
  strtok(students[pos].num, "\n");
  printf("Enter new student email:");
  //fgets(newS.email , LONG , stdin ) ;
  fgets(students[pos].email , LONG , stdin ) ;
  strtok(students[pos].email, "\n");
  printf("Enter new student essay grade:");
  //fgets(newS.essaygrade , LONG , stdin ) ;
  fgets(students[pos].essaygrade , LONG , stdin ) ;
  strtok(students[pos].essaygrade, "\n");
  printf("Enter new student presentation grade:");
  //fgets(newS.presentgrade , LONG , stdin ) ;
  fgets(students[pos].presentgrade , LONG , stdin ) ;
  strtok(students[pos].presentgrade, "\n");
  printf("Enter new student term grade:");
  //fgets(newS.termgrade , LONG , stdin ) ;
  fgets(students[pos].termgrade , LONG , stdin ) ;
  strtok(students[pos].termgrade, "\n");

  total_students++; //Increases total_students
  //printStudent(students[pos]) ;

  printf("\nDone adding new student.\n" );
  printf("Total number of students: %d\n" , total_students ) ; 
}
//Function prompts for name, number, or email to look up that student and returns int position of student 
int studentLookup(){
  printf("\nLookup student\n");
  struct Student x ;// Looking for student x

  printf("Input field to search by, otherwise leave blank and press enter.\n");
  printf("Student name:");
  fgets(x.name , LONG , stdin );
  strtok(x.name, "\n");
  printf("Student number:");
  fgets(x.num , LONG , stdin );
  strtok(x.num, "\n");
  printf("Student email:");
  fgets(x.email , LONG , stdin );
  strtok(x.email, "\n");

  int pos = total_students ; //position of last student
  //printf("position of last student %d\n", pos );
  printf("\n");
  while(pos != -1){ //while not at the first student
    //strcmp compares both char strings and returns 0 if identical
    int i = strcmp( students[pos].name , x.name ); 
    int j = strcmp( students[pos].num , x.num );
    int k = strcmp( students[pos].email , x.email );

    if ( i==0 || j==0 || k==0 ) return pos ; //If any information of student x matches student[pos] returns pos of student
    pos--; //Decrease position until first student
  }
  return -1; //return -1 if student not found
}
/* deleteStudent - deletes student from struct array. */
void deleteStudent(){
  printf("\nTo delete student:\n");
  struct Student t = {"0"};
  int x = studentLookup(); //Position of student to delete

  if (x != -1)
  {
    strcpy(students[x].name," ");
    strcpy(students[x].num," ");
    strcpy(students[x].email," ");
    strcpy(students[x].essaygrade," ");
    strcpy(students[x].presentgrade," ");
    strcpy(students[x].termgrade," ");
    total_students--; //subtracts the one student deleted from total student count
    printf("Done deleting a student.\n");
    printf("Total number of students: %d\n" , total_students ) ;
  }
  else
  {
    printf("Could not find student.\n");
    printf("Total number of students: %d\n" , total_students ) ;
  }
}
/* retrieveinfo - retrieves info and prints specific student data */
void retrieveInfo(){
  printf("Retrieve information of a student.\n");
  int i = studentLookup() ; //Functions that returns position of student x
  //printf("%d, %s \n", i , students[i].name);
  if (i == -1 ) {printf("Student not found.\n"); return ;} //studentLookup returns -1 if student not found
  
  printStudent(students[i]); //Prints information of student x
  printf("Done retrieving student information.\n") ;
}
/* updateStudent - updates student info */
void updateStudent(){
  printf("\nTo update student:\n");
  int k = studentLookup(); //Position of student to delete
  struct Student x ;// Looking for student x

    if (k != -1)
  {
  printf("Input ALL fields to update.\n");
  printf("Student name:");
  fgets(x.name , LONG , stdin );
  strtok(x.name, "\n");
  printf("Student number:");
  fgets(x.num , LONG , stdin );
  strtok(x.num, "\n");
  printf("Student email:");
  fgets(x.email , LONG , stdin );
  strtok(x.email, "\n");
  printf("Student essay grade::");
  fgets(x.essaygrade , LONG , stdin );
  strtok(x.essaygrade, "\n");
  printf("Student presentation grade:");
  fgets(x.presentgrade , LONG , stdin );
  strtok(x.presentgrade, "\n");
  printf("Student term grade:");
  fgets(x.termgrade , LONG , stdin );
  strtok(x.termgrade, "\n");
  
  strcpy(students[k].name,x.name);
  strcpy(students[k].num,x.num);
  strcpy(students[k].email,x.email);
  strcpy(students[k].essaygrade,x.essaygrade);
  strcpy(students[k].presentgrade,x.presentgrade);
  strcpy(students[k].termgrade,x.termgrade);
    
    printf("Done updating a student.\n");
  }
  else
  {
    printf("Could not find student.\n");
  }

}
/* menu - main menu and driver for program */
void menu(){
  char op[1] ;
  char buf[LONG] ;

  printf("\nClass-roll system function:");

  while( op[0]!= 'q'){
    printf("\nr - read data from file\n");
    printf("w - write data to file\n");
    printf("a - add new student\n");
    printf("d - delete student\n");
    printf("i - retrieve a student information\n");
    printf("u - update\n") ;
    printf("q - exit the system\n\n");

    scanf("%c" , op); //reads in char for switch case

    fgets(buf , LONG, stdin) ; // reads in empty char
    switch(op[0]){ //uses first char typed as the switch option
      case 'r': buildData(); break ;
      case 'w': writeData(); break ;
      case 'a': newStudent(); break ;
      case 'd': deleteStudent(); break ; 
      case 'i': retrieveInfo(); break ;
      case 'u': updateStudent(); break;
      case 'q': exit(0);
      default:
        printf("Wrong commmand. Must be r, w, a, d, i, u, or q to exit program.\n");
    }
  }
}

/* main - driving function for the program */
int main(){
  menu();
  return 0;
}
