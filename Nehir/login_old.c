#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
  //Prints to browser
  printf("<html>");
  printf(“Content-Type:text/html\n\n”);
 
  //Gets data from CGI 
  char *data = getenv("QUERY_STRING");

  //Stores the login
  char *login = loginToken(data);

  //Checks if the login is not already in use
  int loginIsValid = doesLoginExist(login);
  
  //If login is invalid, directs user to either the landing page or the
  //login page
  if (loginIsValid == 0){
    print("<head><body>Wrong login. Please click
          <a href="LOGIN PAGE HERE">here</a> to return to the login page. Please click <a href="LANDING PAGE HERE">here</a>
          to return to the landing page </head></body></html>");
  }
  
  //If password is invalid, directs user to either the landing page or the
  //login page
  if (passwordIsValid == 0){
          print("<head><body>Wrong password. Please click
          <a href="LOGIN PAGE HERE">here</a> to return to the login page. Please click <a href="LANDING PAGE HERE">here</a>
          to return to the landing page </head></body></html>");
  }

  //If password and login are both valid, directs user to their own
  //dashboard page
  if (loginIsValid == 1 && passwordIsValid == 1){
    system("./dashboard.py" login);
  }

}



//Parse query string for login info
char *loginToken(char *data){
  
  //Initialize a running pointer and point it to the beginning of data
  char *rPointer = strdup(data);

  //Move the pointer 6 characters forward (the string is login=USERNAME,
  //this way it points to user name)
  char *rPointer += 6;
  
  //Initialize a login pointer to store the login and a delim set of chars
  //for the strsep function
  char *login;
  char *delim = " ,\n";

  login = strsep(&rPointer, delim);
  
  return login;
}

//Parse query string for password info
char *passwordToken(char *data){
  
  //Initialize a running pointer and point it to the beginning of data
  char *rPointer = strdup(data);

  //Move the pointer 6 characters forward (the string is login=USERNAME,
  //this way it points to user name)
  char *rPointer += 6;
  
  //Initialize a login pointer to store the login and a delim set of chars
  //for the strsep function
  char *password;
  char *delim = " ,\n";

  login = strsep(&rPointer, delim);
  
  return password;
}

//Checks the users.txt file for the login and password
int loginAndPassword(char *login, char* password){

  //Opens the file and points pointer to it
  FILE *filePointer = fopen("users.txt", "r+");
  
  //Int for line size
  int lineSize = 1000;

  //Allocates space for a line
  char *line = malloc (lineSize);
  
  //Reads a line from file, if equals to the login, return 1
  while (getline(&line, (size_t*)&lineSize, filePointer) != -1){
    if ((strcmp(login, line) == 0)){
      getline(&line, (size_t*)&lineSize, filePointer);
      if ((strcmp(password, line) == 0)){
        return 1;
      }else if ((strcm
    }
    //Else skips three lines to get to the next login
    } else {
      int i = 0;
      while (i < 3){
        getline(&line, (size_t*)&lineSize, filePointer);
      }
    }
  }

  return 0;
}