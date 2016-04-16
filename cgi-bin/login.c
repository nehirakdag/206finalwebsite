#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "login.h"

#define ERRORPAGE "../template.html"
#define LOGINPAGE "../login.html"
#define USERS "./users.txt"

// This function takes in the Query_string environment variable
// and returns the username input
char *getUsername(char *data) {
        // initialize the variables
        char *dataDup;
        char *username;

        // duplicate the data string to a new variable to make sure
        // no data is overwritten
        dataDup = strdup(data);

        // tokenize the input string by the delimiters & and =
        // the input username will be the second token. The one after USERNAME=
        strtok(dataDup, "&=");
        username = strtok(NULL, "&=");

        return username;

}

// This function takes in the Query_string environment variable
// and returns the password input
char *getPassword(char *data) {
        // initialize the variables
        char *dataDup;
        char *password;

        // duplicate the data string to a new variable to make sure
        // no data is overwritten
        dataDup = strdup(data);

        // tokenize the input string by the delimiters & and =
        // the input username will be the fourth token. The one after USERNAME=
        strtok(dataDup, "&=");
        strtok(NULL, "&=");
        strtok(NULL, "&=");
        password = strtok(NULL, "&=");

        return password;
}

// This function takes two strings corresponding to a username and its
// associated password in the system and checks if there is indeed a match
BOOLEAN validateInput(char *username, char *password) {
        // there is no match if either of the inputs are empty strings
        // or contain a single space
        if(username == NULL || password == NULL) {
                printf("<center><font size=\"15\"> Please enter a valid username and password with no empty fields</font></center>\n");
                return FALSE;
        }
        if(strcmp(username, "") == 0 || strcmp(password, "") == 0) {
                printf("<center><font size=\"15\"> Please enter a valid username and password</font></center> \n");
                return FALSE;
        }
        if(strcmp(username, " ") == 0 || strcmp(password, " ") == 0) {
                printf("<center><font size=\"15\"> Please enter a valid username and password</font></center> \n");
                return FALSE;
        }

        // initialize the file pointer and open users.txt
        FILE *users;
        char line[1000];
        users = fopen(USERS, "r+");

        // no match if there is no users.txt file
        if(users == NULL) {
                printf("<center><font size=\"15\"> Error! Attempted to access invalid page %s", ERRORPAGE);
                return FALSE;
        }

        // since each line has the ending \n character at the end, we need to add
        // it to our username and password strings for them to match our users.txt lines' format
        char *checkusername = strdup(username);
        char *checkpassword = strdup(password);

        strcat(checkusername, "\n");
        strcat(checkpassword, "\n");

        //printf("Looking for username %s\n", username);
        // step through each line of users.txt
        while(fgets(line, sizeof(line), users) != NULL) {
                // if the associated username is found, check if the next
                // line is indeed the password input to this function
                //printf("Line is %s\n", line);
                //printf("Length of line is %lu\n", strlen(line));
                //printf("Length of username is %lu\n", strlen(username) );
                        if(strcmp(line, checkusername) == 0) {
                        fgets(line, sizeof(line), users);
                        // if there is a match, return true
                        //printf("Looking for password %s now, in line %s\n", password, line);
                        if(strcmp(line, checkpassword) == 0) {
                                fclose(users);
                                return TRUE;
                        }
                        // if the username was found but passwords didnt match,
                        // print the appropriate error message and return false
                        printf("<center><font size=\"15\"><p> Wrong password, please try again. </p>\n");
                        fclose(users);
                        return FALSE;
                }
        }

        // if the username was never found in the file,
        // print the appropriate error message and return false
        printf("<center><font size=\"15\"><p> Username not found, please try again. </p></font></center>\n");

        // close the users.txt file
        fclose(users);

        return FALSE;
}

int main() {
        // initialize the variables to be used
        char *data;
        FILE *errorPage;
        char line[1000];
        char *username;
        char *password;

        // Store the query string environment variable by CGI's GET
        data = getenv("QUERY_STRING");

        // get the username and password fields from the QUERY_STRING
        username = getUsername(data);
        password = getPassword(data);
	    printf("Content-Type:text/html\n\n");
	    printf("<html>");
        printf("<head>");
        printf("<title>Login Page</title>\n");
  	    printf("</head>");
        printf("<body>");


        // have the dashboard up and running on the cgi server
        // use fgets to read it line by line
        errorPage = fopen(ERRORPAGE, "r+");

        // If the file does not exist, print error and two links back to the landing
        // page and login page
        if( errorPage == NULL ) {
                printf("<h1 style=\"border:2px black solid\"><center><b>THE TRIANGLE</b></center></h1><br />");
                printf("<center><font size=\"15\"><p>Error! Attempted to access invalid page %s</p></font></center></body></html>", ERRORPAGE);
        }

        //printf("<p> Username is %s</p>\n", username);
        //printf("<p> Password is %s</p>\n", password);

        // check if the input credentials are valid within the server
        int validInput = validateInput(username, password);

        //printf("<p> ValidInput is %d</p>\n", validInput);

        // If there is no match, print error and two links back to the landing
        // page and login page
        if(!validInput) {
                printf("<h1 style=\"border:2px black solid\"><center><b>THE TRIANGLE</b></center></h1><br />");
                printf("<center><img src=\"https://onoitsmyworld.files.wordpress.com/2013/03/full-black-triangle-white-background.jpg\"width=\"700\" height=\"400\"/></center><br />");
                printf("<br />\n");
                printf("<center><font size=\"15\" style=\"border:5px black solid\"><a href=\"http://cgi.cs.mcgill.ca/~tporta2/index.html\">LANDING PAGE</a></font> </center>");
                printf("<br />\n");
                printf("<center><font size=\"15\" style=\"border:5px black solid\"><a href=\"http://cgi.cs.mcgill.ca/~tporta2/login.html\">LOGIN PAGE</a></font></center>");
                printf("<br />\n");
                printf("</body></html>\n");
        }

	// If there is a match, print the dashboard for that user
	else{
		/*while(fgets(line, sizeof(line), dashboard) != NULL) {
			// start adding the dashboard at the end of the file, right before /body
			if(strstr(line, "</body>") != NULL) {
				printf("<p>true!!</p>\n");
				
				printf("%s\n", line);
			}
			// if we have not yet reached the final few lines of the file,
			// write the line to STDOUT
			else{
				printf("%s\n", line);
			}
		}*/
		//printf("Calling dashboard\n");
		char *systemCommand;
		systemCommand = (char *)calloc(16 + strlen(username), sizeof(char));
		strcat(systemCommand, "./dashboard.py ");
		strcat(systemCommand, username);
		system(systemCommand);
	}

	// close the dashboard file
	fclose(errorPage);

	return 0;
}

