#!usr/bin/env/ python
from os import environ
import Cookie,os
import cgi, cgitb
import sys

def generateHeader():
	print "Content-type:text/html\r\n\r\n"
	head = '''
	<html>
	<head>
	<title> The Triangle</title>
	<link rel="stylesheet" href="/~tporta2/landing.css">
	</head>
	<body> 
	<center><h1 style="border:5px black solid">THE TRIANGLE:MAKE AN EDGE</h1> <br /></center>
	'''
	
	print(head)


def getFriendsList():
	with open("/~tporta2/cgi-bin/friends.txt") as friendsList:
		lineArray = friendsList.readlines()
		for line in lineArray:
			myFriends = line.split()
			if len(myFriends) > 0 and myFriends[0].rstrip() == thisusername.rstrip():
				for myfriend in  myFriends:
					friendArray.append(myfriend)

def getUsername();
	if environ.has_key('HTTP_COOKIE'):
   		for cookie in map(strip, split(environ['HTTP_COOKIE'], ';')):
      		(key, value ) = split(cookie, '=');
       			if key == "UserID":
         		user_id = value
	return user_id

def generateFooter():
	foot = '''
	<br />
	<center>Created by Thomas Porta,Berkehan Yanilmaz and Nehir Akdag</center>
	</body>
	</html>
	'''
	
	print(foot)


			


		
