from flask import request
from flask import Flask, send_from_directory

app = Flask(__name__)


@app.route("/download")
def index():
    version = request.values.get('version')
    return send_from_directory(r"/home/lvsj/study/testCode/shell", filename=version, as_attachment=True)


if __name__ == '__main__':
    print(app.url_map)
    app.run(host="0.0.0.0", port=5000)
