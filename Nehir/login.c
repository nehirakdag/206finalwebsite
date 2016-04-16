#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "login.h"

// NOTE I CHANGED THIS TO TEST2!!! DONT FORGET TO CHANGE BACK LOL
#define DASHBOARD "../test2.html"
//#define DASHBOARD "../login.html"
#define LOGINPAGE "../login2.html"
//#define USERS "~/public_html/users.txt"
#define USERS "users.txt"

// chmod 755 ON EACH FILE AND FOLDER
// register.c will use MEHTOD = POST!!!!!

char *getUsername(char *data) {
	char *dataDup;
	char *username;

	dataDup = strdup(data);

	strtok(dataDup, "&=");
	username = strtok(NULL, "&=");

	return username;

}

char *getPassword(char *data) {
	char *dataDup;
	char *password;

	dataDup = strdup(data);

	strtok(dataDup, "&=");
	strtok(NULL, "&=");
	strtok(NULL, "&=");
	password = strtok(NULL, "&=");

	return password;
}

BOOLEAN validateInput(char *username, char *password) {
	if(strcmp(username, "") == 0 || strcmp(password, "") == 0) {
		return FALSE;
	}
	if(strcmp(username, " ") == 0 || strcmp(password, " ") == 0) {
		return FALSE;
	}

	FILE *users;
	char line[1000];
	users = fopen(USERS, "r+");

	if(users == NULL) {
		return FALSE;
	}

	while(fgets(line, sizeof(line), users) != NULL) {

		if(strcmp(line, username) == 0) {
			fgets(line, sizeof(line), users);
			if(strcmp(line, password) == 0) {
				return TRUE;
			}
		}
	}

	return FALSE;
}

int main() {
	// initialize the variable to store the query string at
	char *data;
	FILE *dashboard;
	char line[1000];
	char *username;
	char *password;

	// Store the query string environment variable by CGI's GET
	data = getenv("QUERY_STRING");
	
	// get the username and password fields
	username = getUsername(data);
	password = getPassword(data);

	// Print the output to the browser
	printf("Content-Type:text/html\n\n");
	printf("<html>");

	// have the dashboard up and running on the cgi server
	// use fgets to read it line by line
	dashboard = fopen(DASHBOARD, "r+");

	// If the file does not exist, print error and exit program.
	if( dashboard == NULL ) {
		printf("<p>Error! Attempted to access invalid page %s</p>", DASHBOARD);
	}

	printf("<p> Data is: %s</p>\n", data);
	printf("<p> Username is %s</p>\n", username);
	printf("<p> Password is %s</p>\n", password);

	int validInput = validateInput(username, password);

	printf("<p> ValidInput is %d</p>\n", validInput);
	
	while(fgets(line, sizeof(line), dashboard) != NULL) {
		//printf("<p>hmm</p>\n");
		if(strstr(line, "</body>") != NULL) {
			printf("<p>true!!</p>\n");
			
			printf("%s\n", line);
		}
		else{
			printf("%s\n", line);
		}
	}
	fclose(dashboard);

	return 0;
}