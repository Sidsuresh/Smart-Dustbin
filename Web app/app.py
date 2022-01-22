import pyrebase
from flask import Flask, request, jsonify, after_this_request


# create the Flask app
app = Flask(__name__)

firebase_config = {
        "apiKey": "",
        "authDomain": "",
        "databaseURL": "",
        "projectId": "",
        "storageBucket": "",
        "messagingSenderId": "",
        "appId": "",
        "measurementId": ""
}

firebase = pyrebase.initialize_app(firebase_config)
db = firebase.database()

@app.route('/getLvl', methods=['GET'])
def returnVal():
    @after_this_request
    def add_header(response):
        response.headers.add('Access-Control-Allow-Origin', '*')
        return response
    lvl = db.child('garbageLvl').child('Level').get()
    l = lvl.val()
    loc = db.child('garbageLvl').child('Loc').get()
    lctn = loc.val()
    return jsonify({'level' : l, 'location': lctn})

if __name__ == '__main__':
    app.run(debug=True, port=8000)
