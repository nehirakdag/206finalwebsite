#!/usr/bin/env python
# -*- coding: UTF-8 -*-

from __future__ import print_function
from os import environ
import Cookie
import os
import cgi, cgitb
import urllib
import urlparse
import sys


# Generate HTML Header
def generateheader():
	head = '''
	<html>
	<head>
	<title>The Triangle</title>
	<link rel="stylesheet" href="/~tporta2/landing.css">
	</head>
	<body>
	<center style="border:5px black solid"><h1>THE TRIANGLE</h1></center><br />
	<center><img src="https://onoitsmyworld.files.wordpress.com/2013/03/full-black-triangle-white-background.jpg" width="700" height="400"/></center><br />
	<center><h2>Dashboard</h2></center><br />
	<center><form action="./cgi-bin/seefriends.cgi" method = "get">
	<input type="hidden" name="USERNAME" value="%s”><br />
	<input type="submit" value="See Friends!">
	</form></center><br />
	'''%(theUsername)

	print (head)


def statusUpdateForm():
	form_html = '''
	<center><h2>Publish a subtriangle</h2></center><br />
	<center><form action="/~tporta2/cgi-bin/status.py" method="GET">
	<textarea placeholder="Update Your Status..." name="mystatusupdate" cols="50" rows="2"></textarea><br />
	<input id="updatebutton" type="submit" value="Update Status">
	<input type="hidden" name="userID" value=%s>
	</form></center><br/>
	<center><h2>News Feed</h2></center>
	'''%(theUsername)
	print (form_html)

def generatefooter():
	foot = '''
	<br />
	<center><b>Created by Thomas Porta,Berkehan Yanilmaz,Nehir Akdag</b></center>
	</body>
	</html>
	'''
	print (foot)



def printLatestStatus():
	if len(ArrayOfFriends) == 0:
		print ("<center>Connect with other edges of the triangle to succeed</center><br />")
	else:
		with open("status.txt", "r") as statuses:
			statusList = statuses.readlines()
			numStatus = len(statusList)
			m = numStatus-1
			n = numStatus-1
			print ("\t<p>")
			while (n>=0 and m>(numStatus-20)):
				if checkFriendshipStatus(getStatusUser(statusList[n])):
					print("<center><strong>%s</strong></center><br />" %(statusList[m].rstrip()))
					m -= 1
				n -= 1
			print ("\t</p>")


def getStatusUser(status):
	parsed = status.split()
	if len(parsed):
		return parsed[0]
	else:
		return 'null'


def getFriendsList():
	with open("friends.txt", "r") as friends:
		lines = friends.readlines()
		for line in lines:
			myFriends = line.split()
			if len(myFriends) > 0 and myFriends[0].rstrip()==theUsername.rstrip():
				for myfriend in  myFriends:
					ArrayOfFriends.append(myfriend)
			
def checkFriendshipStatus(possibleFriend):
	result = False
	for elements in ArrayOfFriends:
		if elements.rstrip() == possibleFriend.rstrip():
			result = True
			break
	return result				


def main():
	getFriendsList()
	print ("Content-Type:text/html\n\n")	
	generateheader()
	statusUpdateForm()
	printLatestStatus()
	generatefooter()


cgitb.enable()

form=cgi.FieldStorage()
global theUsername
theUsername=form.getvalue('USERNAME')
ArrayOfFriends = []


main()
