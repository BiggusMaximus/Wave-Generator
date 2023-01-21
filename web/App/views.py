from flask import Blueprint, render_template, Response, jsonify, send_file


views = Blueprint('views', __name__)                 

@views.route('/')
def home():
    return render_template('home.html')

