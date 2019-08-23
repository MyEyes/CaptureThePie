from flask import Flask
import re
import os
import flask
app = Flask(__name__)

num_levels = 0

def get_challenge_flag(n):
    with open("../level{}/flag.h".format(n)) as file:
       for line in file:
          match = re.search("FLAG.*=.*\"(.*)\"", line)
          if match == None:
             continue
          return match.group(1)

def strip_challenge(n):
    flag = get_challenge_flag(n).encode()
    repl_flag = b"{NOT_a_real_flag}"
    f = open("../level{}/a.out".format(n), "rb")
    s = f.read()
    f.close()
    sn = s.replace(flag, repl_flag)
    f = open("download/level{}".format(n), "wb")
    f.write(sn)
    f.close()

def download_challenge(n):
    if not os.path.isfile("download/level{}".format(n)):
        strip_challenge(n)
    return flask.send_from_directory("download", "level{}".format(n), as_attachment=True)

def get_levels():
    global num_levels
    n = 0
    while os.path.isdir("../level{}".format(n)):
       n += 1
    num_levels = n

def get_description(n):
    file = "../level{}/desc".format(n)
    try:
       f = open(file,"r")
       s = str(f.read())
       f.close()
       return s
    except Exception:
       return "Error reading file {}".format(file)

def get_code(n):
    file = "../level{}/level{}.c".format(n,n)
    try:
       f = open(file,"r")
       s = str(f.read())
       f.close()
       return s
    except Exception:
       return "Error reading file {}".format(file)

#Just work out the number of levels once at the start
get_levels()

@app.route('/')
def home():
    global num_levels
    return flask.render_template('main.html', levels=range(0,num_levels))

@app.route('/challenge/<int:n>')
def challenge_page(n):
    challenge_info = {
        "title": "Level {}".format(n),
	"description": get_description(n),
	"code": get_code(n),
    }
    return flask.render_template('challenge.html', levels=range(0,num_levels), level=n, info=challenge_info)

#@app.route('/download/<int:n>', methods=['POST'])
#def download_chall(n):
#    download(n, "")

@app.route('/download/<int:n>/<file>', methods=['POST'])
def download(n, file):
    authorization = flask.request.form.get('auth')
    directory = "../level{}".format(n)
    if authorization == None or (n>0 and authorization != get_challenge_flag(n-1)):
        return "Unauthorized"
    if "flag" in file.lower():
        return "Nice try"
    if "a.out" in file.lower() or file == "":
        return download_challenge(n)
    return flask.send_from_directory(directory, file, as_attachment=True)
