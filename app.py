from flask import Flask
from flask_restful import Api
from api import usage

app = Flask(__name__)
api = Api(app)

api.add_resource(usage.Usage, "/api/system")

if __name__ == "__main__":

    # FIXME: Using all hosts for now, should be IP of the ESP module.
    app.run(port=9795, host="0.0.0.0")