
all: login register seeafriend

login: login.c login.h
	gcc -o login.cgi login.c

register: register.c register.h
	gcc -o register.cgi register.c

seeafriend: seeafriend.c seeafriend.h
	gcc -o seeafriend.cgi seeafriend.c

clean:
	-rm login register
