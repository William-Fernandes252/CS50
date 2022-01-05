import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")

@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":
        name = request.form.get("name")
        month = request.form.get("month")
        day = request.form.get("day")
        if name not in next(person for person in db.execute("SELECT name FROM birthdays") if person["name"] == name)["name"]:
            db.execute("INSERT INTO birthdays (name, month, day) VALUES(?, ?, ?)", name, month, day)
        else:
            db.execute("UPDATE birthdays SET month = ?, day = ? WHERE name = ?", month, day, name)
        return redirect("/")
    else:
        birthdays = db.execute("SELECT id, name, month, day FROM birthdays")
        return render_template("index.html", birthdays = birthdays)

@app.route("/deregister", methods = ["GET", "POST"])
def deregister():
    id = request.form.get("id")
    if id:
        db.execute("DELETE FROM birthdays WHERE id = ?", id)
    birthdays = db.execute("SELECT name, month, day FROM birthdays")
    return render_template("index.html", birthdays = birthdays)