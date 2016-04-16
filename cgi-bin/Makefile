
all: login register seefriends

login: login.c login.h
	gcc -o login.cgi login.c

register: register.c register.h
	gcc -o register.cgi register.c

seefriends: seefriends.c seefriends.h
	gcc -o seefriends.cgi seefriends.c

clean:
	-rm login register seefriends
