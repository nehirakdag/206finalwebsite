#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "seefriends.h"

#define FRIENDS "friends.txt"

int main() {
	FILE *friends;
	char line[1000];
	friends = fopen(FRIENDS, "r+");

	// Store the query string environment variable by CGI's GET
	char *data;
	char *dataDup;
	char *username;

	data = getenv("QUERY_STRING");
	dataDup = strdup(data);
	username = strtok(dataDup, "&=");
	while(strcmp(username, "USERNAME") != 0) {
		username = strtok(NULL, "&=");
	}

	username = strtok(NULL, "&=");

	printf("Content-Type:text/html\n\n");
	printf("<html>");
	printf("<head>");
	printf("<title>See Friends Page</title>\n");
	//printf("<link rel=\"stylesheet\" href=\"../style.css\">");
	printf("</head>");
	printf("<body>");
	printf("<h1 style=\"border:2px black solid\"><center><b>THE TRIANGLE</b></center></h1>");


	printf("<center><font size=\"15\">Friends of user: %s</font></center>\n", username);
	printf("<br>\n");
	printf("<center><img src=\"https://onoitsmyworld.files.wordpress.com/2013/03/full-black-triangle-white-background.jpg\"width=\"700\" height=\"400\"/></center><br /><br />");

	char *token;
	while(fgets(line, sizeof(line), friends) != NULL) {
		token = strtok(line, " \n");
		if(strcmp(token, username) == 0) {
			token = strtok(NULL, " \n");
			while(token != NULL) {
				printf("<center><font size=\"15\"><a href=\"http://cgi.cs.mcgill.ca/~tporta2/profiles/%s.html\"> %s </a></font> </center>", token, token);
				token = strtok(NULL, " \n");
			}
			// printf back to seefriends Page
			printf("<form action=\"../cgi-bin/dashboard.py\" method = \"get\">\n");
			printf("<input type=\"hidden\" name=\"USERNAME\" value=\"%s\"><br>\n", username);
			printf("<input type=\"submit\" value=\"Back to Dashboard!\">\n");
			printf("</form>\n");
			printf("</body>\n");
			printf("</html>\n");

			fclose(friends);
			return 0;
		}
		while(token != NULL) {
			token = strtok(NULL, " \n");
		}
	}

	return 0;
}
