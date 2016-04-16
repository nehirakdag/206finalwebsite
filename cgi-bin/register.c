#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "register.h"

#define USERS "./users.txt"
#define SUCCESSPAGE "../template.html"

// This function takes four strings corresponding to a name, job description,
// username and its associated password.
// It validates if there is no empty input and the username is unique within the system
BOOLEAN validateInput(char *fullName, char *job, char *username, char *password) {
        // there is no match if either of the inputs are empty strings
        // or contain a single space
        if(fullName == NULL || job == NULL || username == NULL || password == NULL) {
                printf("<center><font size=\"15\">Please make a valid registration with no empty fields</font></center>\n");
                return FALSE;
        }
        if(strcmp(fullName, "") == 0 || strcmp(job, "") == 0 || strcmp(username, "") == 0 || strcmp(password, "") == 0) {
                printf("<center><font size=\"15\">Please make a valid registration with no empty fields</font></center>\n");
                return FALSE;
        }
        if(strchr(username, '+') != NULL) {
                printf("<center><font size=\"15\">Usernames can contain no spaces. Please enter a valid username.</font></center>\n");
                return FALSE;
        }

        // initialize the file pointer and open users.txt
        FILE *users;
        char line[1000];
        users = fopen(USERS, "r+");

        // no match if there is no users.txt file
        if(users == NULL) {
                return FALSE;
        }

        // since each line has the ending \n character at the end, we need to add
        // it to our username string for it to match our users.txt lines' format
        char *checkusername = strdup(username);
        strcat(checkusername, "\n");

        // step through each line of users.txt
        while(fgets(line, sizeof(line), users) != NULL) {
                // if a matching username is found, print an error message, close the file and return
                if(strcmp(line, checkusername) == 0) {
                        printf("<center><font size=\"15\">Username already in use! Please enter a different username</font></center>\n");
                        fclose(users);
                         return FALSE;

                 }
        }

        fclose(users);
        return TRUE;
}

void createProfilePage(char *userName) {
        // initialize the file pointer and create a html profile page with the user's name
        FILE *profile;
        char line[1000];
        char *filename;
        filename = calloc(18 + strlen(userName), sizeof(char));

        // the user's profile will be created under the profiles folder as username.html
        strcpy(filename, "../profiles/");
        strcat(filename, userName);
        strcat(filename, ".html");
        profile = fopen(filename, "w+");

        // no match if there is no users.txt file
        if(profile == NULL) {
                return;
        }

        fputs("<html>\n", profile);
        fputs("<body>\n", profile);
        fputs("<title> Profile Page </title></head>\n", profile);
        fputs("<body><h1 style=\"border:2px black solid\"><center><b>THE TRIANGLE</b></center></h1><center><font size=\"15\">", profile);
        fputs("Profile page of user:", profile);
        fputs(userName, profile);
        fputs("</font></center>", profile);
        fputs("</br>", profile);
        fputs("<center><img src=\"https://onoitsmyworld.files.wordpress.com/2013/03/full-black-triangle-white-background.jpg\"width=\"700\" height=\"400\"/></center><br /><br />", profile);
        fputs("<br>\n", profile);
        fputs("<form action=\"../cgi-bin/seefriends.cgi\" method = \"get\">\n", profile);
        fputs("<input type=\"hidden\" name=\"USERNAME\" value=\"", profile);
        fputs(userName, profile);
        fputs("\"<br>\n", profile);
        fputs("<input type=\"submit\" value=\"Back to See Friends!\">\n", profile);
        fputs("</form><br>", profile);
        fputs("<form action=\"../cgi-bin/dashboard.py\" method = \"get\">\n", profile);
        fputs("<input type=\"hidden\" name=\"USERNAME\" value=\"", profile);
        fputs(userName, profile);
        fputs("\"><br>\n", profile);
        fputs("<input type=\"submit\" value=\"Back to Dashboard!\">\n", profile);
        fputs("</form>\n", profile);
         fputs("</body>\n", profile);
        fputs("</html>\n", profile);

        fclose(profile);
        free(filename);

        return;
}

int main() {
        // initialize the variables to be used
        char *data;
        char *dataDup;

        char *username;
        char *password;
        char *fullName;
        char *job;

        // Store the query string environment variable by CGI's GET
        data = getenv("QUERY_STRING");
        // duplicate the data string to a new variable to make sure
        // no data is overwritten
        dataDup = strdup(data);

        // tokenize the input string by the delimiters & and =
        // the input full name will be the second token. The one after NAME=
        strtok(dataDup, "&=");
        fullName = strtok( NULL, "&=");

        // the input job description will be the fourth token. The one after JOB=
        strtok( NULL, "&=");
        job = strtok( NULL, "&=");

        // the input job description will be the sixth token. The one after USERNAME=
        strtok( NULL, "&=");
        username = strtok( NULL, "&=");

        // the input job description will be the eigthth token. The one after PASSWORD=
        strtok( NULL, "&=");
        password = strtok( NULL, "&=");

        // Print the output to the browser
        printf("Content-Type:text/html\n\n");
        printf("<html>");
        printf("<head>");
         printf("<title>Registration Page</title>\n");
        //printf("<link rel=\"stylesheet\" href=\"../style.css\">");
        printf("</head>");
        printf("<body>");
        printf("<h1 style=\"border:2px black solid\"><center><b>THE TRIANGLE</b></center></h1>");

        // check if the input credentials are valid within the server
        int validInput = validateInput(fullName, job, username, password);

        if(!validInput) {
                printf("<br />\n");
                printf("<center><img src=\"https://onoitsmyworld.files.wordpress.com/2013/03/full-black-triangle-white-background.jpg\"width=\"700\" height=\"400\"/></center><br />");
                printf("<br />\n");
                printf("<center><font size=\"15\" style=\"border:5px black solid\"><a href=\"http://cgi.cs.mcgill.ca/~tporta2/index.html\">LANDING PAGE</a></font> </center>");
                printf("<br />\n");
                printf("<center><font size=\"15\" style=\"border:5px black solid\"><a href=\"http://cgi.cs.mcgill.ca/~tporta2/login.html\">LOGIN PAGE</a></font></center>");
                printf("<br />\n");
                printf("</body></html>\n");
        }
        else{
                // initialize the file pointer and open users.txt for writing
                FILE *users;
                char line[1000];
                users = fopen(USERS, "a+");

                // no match if there is no users.txt file
                if(users == NULL) {
                        return FALSE;
                }

                // write the name, job, username and password to users.txt
                // each field will take up a single line
                fputs(fullName, users);
                fputs("\n", users);
                fputs(job, users);
                fputs("\n", users);
                fputs(username, users);
                fputs("\n", users);
                fputs(password, users);
                fputs("\n", users);

                // close the file since we are done writing to it
                fclose(users);

                // create a profile html page for the user. this page will
                // contain the user's status updates and be accessed by the user's friends
                 createProfilePage(username);

                FILE *success;
                success = fopen(SUCCESSPAGE, "r+");

                        // no match if there is no users.txt file
                if(success == NULL) {
                        printf("<p>Error! Attempted to access invalid page %s</p>", SUCCESSPAGE);
                        return FALSE;
                }
                while(fgets(line, sizeof(line), success) != NULL) {
                        // start adding the html lines from the success page
                        // until the end of the file. right before the </body> tag,
                        // add the success message and create a link to go back to the login page
                        if(strstr(line, "</body>") != NULL) {
                                printf("<br />\n");
                                printf("<center><font size=\"15\"><p> Registration successful!</p></font></center>");
                                printf("<br />\n");
                                printf("<center><img src=\"https://onoitsmyworld.files.wordpress.com/2013/03/full-black-triangle-white-background.jpg\"width=\"700\" height=\"400\"/></center><br />");
                                printf("<br />\n");
                                printf("<center><font size=\"15\" style=\"border:5px black solid\"><a href=\"http://cgi.cs.mcgill.ca/~tporta2/login.html\">LOGIN PAGE</a></font></center>");
                                printf("<br />\n");
                                printf("</body></html>\n");
                                printf("%s\n", line);
                        }
                        // if we have not yet reached the final few lines of the file,
                        // write the line to STDOUT
                        else{
                                printf("%s\n", line);
                        }
                }
                // close the file
                fclose(success);
        }



        return 0;
}