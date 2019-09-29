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
};

int total_students = 0 ; //global variable to keep track of number of students
int flip = 0 ; // switch for building the data

/* buildData - called from main(). This function will load data fom a given file into an array of Student Structures */
int buildData(struct Student students[LONG]){
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
  printf("Total number of student: %d\n" , h ) ; 

  return total_students ;
}

// writeData - called from main(). This functions writes data back into the given file. Writes data in such a way we can reread it back on next execution 
void writeData(struct Student students[LONG]) {
  FILE *fp;
  //int i = 0, j = 0;
  //char str[60];
  int size = total_students ; //total students to write to file
  printf("SIE OF STUDENT IS %d", size ) ;
  //opening file for reading
  fp = fopen("OutputStudentData.txt" , "w");
  //Check is file opened successfully
  if(fp == NULL) {
    perror("Error opening filee");
    exit(1);
   }
  //write the data to file, each data field is put on its own line. 
  for (size_t i = 0; i < size; i++)
  {
    fprintf(fp, "%s\n", students[i].name);
    fprintf(fp, "%s\n", students[i].num);
    fprintf(fp, "%s\n", students[i].email);
    fprintf(fp, "%s\n", students[i].essaygrade);
    fprintf(fp, "%s\n", students[i].presentgrade);
    fprintf(fp, "%s\n", students[i].termgrade);
  }
  //close file 
  fclose(fp);
}
/* printData - a util function to print the current state of the student array */
void printData(struct Student students[LONG], int size){
    for (size_t i = 0; i < size; i++)
  {
    printf("Name: %s\nNum: %s\nemail: %s\n %s %s %s \n",students[i].name,students[i].num,students[i].email,students[i].essaygrade,students[i].presentgrade,students[i].termgrade);
  }
}

void printStudent(struct Student s){

  printf("\nStudent Name: %s" , s.name) ;
  printf("-Number: %s" , s.num) ;
  printf("-Email: %s" , s.email) ;
  printf("-Essay Grade: %s" , s.essaygrade) ;
  printf("-Presentation Grade: %s" , s.presentgrade) ;
  printf("-Term Grade: %s \n" , s.termgrade) ;
}

void newStudent(struct Student students[LONG]){ 
  int pos = total_students ; //last position for where to add new student
  //printf("position where adding new student %d\n", pos); 

  printf("Enter new student name:");
  fgets(students[pos].name , LONG , stdin ) ;
  printf("Enter new student number:");
  //fgets(newS.num , LONG , stdin ) ;
  fgets(students[pos].num , LONG , stdin ) ;
  printf("Enter new student email:");
  //fgets(newS.email , LONG , stdin ) ;
  fgets(students[pos].email , LONG , stdin ) ;
  printf("Enter new student essay grade:");
  //fgets(newS.essaygrade , LONG , stdin ) ;
  fgets(students[pos].essaygrade , LONG , stdin ) ;
  printf("Enter new student presentation grade:");
  //fgets(newS.presentgrade , LONG , stdin ) ;
  fgets(students[pos].presentgrade , LONG , stdin ) ;
  printf("Enter new student term grade:");
  //fgets(newS.termgrade , LONG , stdin ) ;
  fgets(students[pos].termgrade , LONG , stdin ) ;

  total_students++; //Increases total_students
  //printStudent(students[pos]) ;

  printf("\nDone adding new student.\n" );
  printf("Total number of students: %d\n" , total_students ) ; 
}

//Function prompts for name, number, or email to look up that student and returns int position of student 
int studentLookup(struct Student students[LONG]){
  printf("\nLookup student\n");
  //char buf[LONG];
  struct Student x ;// Looking for student x

  printf("Input field to search by, otherwise leave blank and press enter.\n");
  printf("Student name:");
  fgets(x.name , LONG , stdin ) ;
  printf("Student number:");
  fgets(x.num , LONG , stdin ) ;
  printf("Student email:");
  fgets(x.email , LONG , stdin ) ;

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

void deleteStudent(struct Student students[LONG]){
  printf("\nTo delete student:\n");
  struct Student t = {"0"};
  int pos = total_students ; // position of last student
  int x = studentLookup(students); //Position of student to delete

  students[x] = students[pos] ; //Copies last student on the array into the position where student x is.
  students[pos] = t ;
  total_students--; //subtracts the one student deleted from total student count

  printf("Done deleting a student.\n");
  printf("Total number of students: %d\n" , total_students ) ; 
  return ;
}

void retrieveInfo(struct Student students[LONG]){
  printf("Retrieve information of a student.\n");
  int i = studentLookup(students) ; //Functions that returns position of student x
  //printf("%d, %s \n", i , students[i].name);
  if (i == -1 ) {printf("Student not found.\n"); return ;} //studentLookup returns -1 if student not found
  
  printStudent(students[i]); //Prints information of student x
  printf("Done retrieving student information.\n") ;
}
void updateStudent(struct Student students[LONG]){

}
void menu(){
  struct Student students[LONG];
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
      case 'r': buildData(students); break ;
      case 'w': writeData(students); break ;
      case 'a': newStudent(students); break ;
      case 'd': deleteStudent(students); break ; 
      case 'i': retrieveInfo(students); break ;
      case 'u': break;
      case 'q': exit(0);
      default:
        printf("Wrong commmand. Must be r, w, a, d, i, u, or q to exit program.\n");
    }

  }

}

/* main - driving function for the program */
int main(){
  /* Create array of Student Structs and size. Array has max size of 40. */
  //struct Student students[LONG];
  //int size = buildData(students);

  //printData(students,size);


  //writeData(students,size);

  menu();

  return 0;
}
