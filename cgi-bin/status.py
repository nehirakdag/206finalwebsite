#!/usr/bin/env python

from __future__ import print_function
from os import environ
import Cookie
import os
import cgi, cgitb
import urllib
import urlparse
import sys

url = cgi.FieldStorage()
statusupdate= url.getvalue('mystatusupdate')
user_id = url.getvalue('userID')

with open("./status.txt", "r+") as status:
	content = status.read()
	status.seek(0,0)
	info = user_id+" "+statusupdate
        status.write(info.rstrip('\r\n')+ '\n' + content)
	status.close()

print('Content-Type:text/html\n\n')
print('<html>')
print('<head>')
print('<title>Status posted</title>')
print('</head>')
print('<body>')
print('<center><form action="/~tporta2/cgi-bin/dashboard.py" method="get">')
print('<input type="hidden" name="USERNAME" value=%s>'%(user_id))
print('<input type="image" src="https://onoitsmyworld.files.wordpress.com/2013/03/full-black-triangle-white-background.jpg">')
print('</form></center></body></html>')

