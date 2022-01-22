import pyrebase
from flask import Flask, request, jsonify, after_this_request


# create the Flask app
app = Flask(__name__)

firebase_config = {
        "apiKey": "AIzaSyCEQSxJPFbItS2GS6ClL0jHpzTzH3Fegcg",
        "authDomain": "smart-garbage-monitoring-iot.firebaseapp.com",
        "databaseURL": "https://smart-garbage-monitoring-iot-default-rtdb.firebaseio.com",
        "projectId": "smart-garbage-monitoring-iot",
        "storageBucket": "smart-garbage-monitoring-iot.appspot.com",
        "messagingSenderId": "489588431805",
        "appId": "1:489588431805:web:9f6c0f93d7a5f6a8c210d4",
        "measurementId": "G-0MYZ33N1C8"
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