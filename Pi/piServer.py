from flask import Flask, send_from_directory, request

app = Flask(__name__)

def replace_line(file_name, line_num, text):
    lines = open(file_name, 'r').readlines()
    lines[line_num] = str(text) + '\n'
    with open('base.txt', 'w') as file:
        file.writelines(lines)
    file.close()

@app.route('/userInput', methods=['POST'])
def userInput():
    return send_from_directory("", "index.html")

@app.route('/destination', methods=['POST'])
def destination():
    destinationAddress = request.args.get('address')
    replace_line('base.txt',6,destinationAddress)
    return send_from_directory("", "index.html")

@app.route('/origin', methods=['POST'])
def origin():
    originAddress=request.args.get('address')
    replace_line('base.txt',0,originAddress)
    return send_from_directory("", "index.html")

@app.route('/timeToArrive', methods=['POST'])
def arrive():
    ttaHours = request.args.get('hour')
    ttaMin = request.args.get('min')
    replace_line('base.txt', 12, ttaHours)
    replace_line('base.txt', 13, ttaMin)
    return send_from_directory("", "index.html")

@app.route('/prep', methods=['POST'])
def prep():
    prepTime = request.args.get('time')
    replace_line('base.txt', 5, prepTime)
    return send_from_directory("", "index.html")

@app.route('/dataInputFromScript', methods=['POST'])
def dataInputFromScript():
    for key in request.args:
        with open('base.txt','w') as file:
            file.writeline
    return 'this is working'

@app.route('/')
@app.route('/<path:filepath>')
def index(filepath='index.html'):
    return 'send_from_directory('', filepath)'

# @app.route('/')
# @app.route('/<path:filepath>')
# def index(filepath='index.html'):
#     return send_from_directory('views', filepath)

if __name__ == '__main__':
    app.run(host='0.0.0.0', port="8000")
