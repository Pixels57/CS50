import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    rows = db.execute("SELECT * FROM user_purchases WHERE userid = ?", session["user_id"])
    symbols = []
    totalPrices = []
    for row in rows:
        symbols.append(usd(lookup((row["symbol"]))["price"]))
        totalPrices.append(usd(float((lookup(row["symbol"]))["price"]) * row["shares"]))
    cash = usd(db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])[0]['cash'])
    return render_template("homepage.html", data=rows, money=cash, livevalue=symbols, livetotal=totalPrices)


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    rows = db.execute(
        "SELECT * FROM Purchases WHERE userid = ? ORDER BY TIME DESC", session["user_id"])
    return render_template("history.html", data=rows)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("Must provide symbol", 400)
        result = lookup(request.form.get("symbol"))
        if not result:
            return apology("Symbol does not exist", 400)
        print(result)
        result["price"] = usd(result["price"])
        return render_template("quoted.html", data=result)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        if not request.form.get("username"):
            return apology("Must provide username", 400)
        if len(db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))) == 1:
            return apology("Username already taken", 400)
        if not request.form.get("password"):
            return apology("Must provide password", 400)
        if request.form.get("password") != request.form.get("confirmation"):
            return apology("Password does not match", 400)
        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", request.form.get(
            "username"), generate_password_hash(request.form.get("password")))
        return redirect("/")
    else:
        return render_template("register.html")


@app.route("/change_password", methods=["GET", "POST"])
@login_required
def change_password():
    if request.method == "POST":
        if not request.form.get("oldpassword"):
            return apology("Must provide old password", 403)
        if not request.form.get("password"):
            return apology("Must provide password", 403)
        if not request.form.get("confirmation"):
            return apology("Must provide password confirmation", 403)
        if not check_password_hash(db.execute("SELECT hash FROM users WHERE id = ?", session["user_id"])[0]["hash"],  request.form.get("oldpassword")):
            return apology("Old Password is not correct", 403)
        if request.form.get("password") != request.form.get("confirmation"):
            return apology("Password does not match", 403)
        db.execute("UPDATE users set hash = ? WHERE id = ?", generate_password_hash(
            request.form.get("password")), session["user_id"])
        return logout()
    else:
        return render_template("changePassword.html")


@app.route("/add_cash", methods=["GET", "POST"])
@login_required
def add_cash():
    if request.method == "POST":
        if not request.form.get("amount"):
            return apology("Must provide amount", 403)
        intamount = int(request.form.get("amount"))
        if intamount < 1:
            return apology("Amount must be positive number", 403)
        db.execute("UPDATE users set cash = ? WHERE id = ?", db.execute(
            "SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"] + intamount, session["user_id"])
        return index()
    else:
        return render_template("add_cash.html")


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("Must provide a symbol", 403)
        if not lookup(request.form.get("symbol")):
            return apology("Symbol does not exist", 400)
        if not request.form.get("shares"):
            return apology("Must provide number of shares", 403)

        shares = request.form.get("shares")

        # Check if the shares value is a valid integer
        try:
            intShares = int(shares)
            if intShares < 1:
                return apology("Shares must be a positive number", 400)
        except ValueError:
            return apology("Shares must be an integer", 400)

        stock = lookup(request.form.get("symbol"))
        total_price = float(stock["price"]) * intShares
        user_cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]

        if total_price > user_cash:
            return apology("You don't have enough money! Transaction failed", 400)

        db.execute("UPDATE users SET cash = ? WHERE id = ?",
                   user_cash - total_price, session["user_id"])
        current_time = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        db.execute("INSERT INTO Purchases (userid, type, symbol, price, shares, time) VALUES (?, ?, ?, ?, ?, ?)",
                   session["user_id"], "Purchase", stock["symbol"], usd(stock["price"]), intShares, current_time)

        rows = db.execute("SELECT * FROM user_purchases WHERE userid = ? AND symbol = ?",
                          session["user_id"], stock["symbol"])
        if len(rows) == 0:
            db.execute("INSERT INTO user_purchases (userid, symbol, shares, unit_price, total_price) VALUES (?, ?, ?, ?, ?)",
                       session["user_id"], stock["symbol"], intShares, usd(stock["price"]), usd(total_price))
        else:
            currentShare = rows[0]["shares"]
            new_total_shares = intShares + currentShare
            new_total_price = usd(new_total_shares * float(stock["price"]))
            db.execute("UPDATE user_purchases SET shares = ?, total_price = ? WHERE userid = ? AND symbol = ?",
                       new_total_shares, new_total_price, session["user_id"], stock["symbol"])

        return redirect("/")
    else:
        return render_template("buy.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("Must provide item to sell", 403)
        stock = db.execute("SELECT * FROM user_purchases WHERE userid = ? AND symbol = ?",
                           int(session["user_id"]), request.form.get("symbol"))
        if len(stock) == 0:
            return apology("You don't own stock of this company", 404)
        if not request.form.get("shares"):
            return apology("Must provide number to sell", 403)
        intShares = int(request.form.get("shares"))
        if intShares < 1:
            return apology("Shares must be a positive number", 400)
        currShares = stock[0]["shares"]
        if intShares > stock[0]["shares"]:
            return apology("You don't own that much stock to sell", 400)
        currStock = lookup(stock[0]["symbol"])
        stockPrice = float(currStock["price"])
        totalPrice = stockPrice * intShares
        user_cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]
        db.execute("UPDATE users SET cash = ? WHERE id = ?",
                   user_cash + totalPrice, session["user_id"])
        current_time = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        db.execute("INSERT INTO Purchases (userid, type, symbol, price, shares, time) VALUES (?, ?, ?, ?, ?, ?)", int(
            session["user_id"]), "Sale", currStock["symbol"], usd(totalPrice), intShares, current_time)
        if stock[0]["shares"] == intShares:
            db.execute("DELETE FROM user_purchases WHERE userid = ? AND symbol = ?",
                       int(session["user_id"]), currStock["symbol"])
            return index()
        else:
            cuurentShare = stock[0]["shares"]
            db.execute("UPDATE user_purchases SET shares = ?, total_price = ? WHERE userid = ? AND symbol = ?", cuurentShare -
                       intShares, usd((cuurentShare - intShares) * float(currStock["price"])), int(session["user_id"]), currStock["symbol"])
            return index()
    else:
        stocks = db.execute("SELECT symbol FROM user_purchases WHERE userid = ?",
                            int(session["user_id"]))
        return render_template("sell.html", data=stocks)


@app.route("/trade", methods=["POST"])
@login_required
def trade():
    realstock = db.execute("SELECT * FROM user_purchases WHERE userid = ? AND symbol = ?",
                           int(session["user_id"]), request.form.get("symbol"))
    intShares = int(request.form.get("shares"))
    if request.form.get("action") == "buy":
        stock = lookup(request.form.get("symbol"))
        total_price = float(stock["price"]) * intShares
        user_cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]
        if total_price > user_cash:
            return apology("You don't have enough money! Transaction failed", 400)
        db.execute("UPDATE users SET cash = ? WHERE id = ?",
                   user_cash - total_price, session["user_id"])
        current_time = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        db.execute("INSERT INTO Purchases (userid, type, symbol, price, shares, time) VALUES (?, ?, ?, ?, ?, ?)", int(
            session["user_id"]), "Purchase", stock["symbol"], usd(int(stock["price"]) * intShares), intShares, current_time)
        rows = db.execute("SELECT * FROM user_purchases WHERE userid = ? AND symbol = ?",
                          int(session["user_id"]), stock["symbol"])
        if len(rows) == 0:
            db.execute("INSERT INTO user_purchases (userid, symbol, shares, unit_price, total_price) VALUES (?, ?, ?, ?, ?)", int(
                session["user_id"]), stock["symbol"], intShares, usd(stock["price"]), usd(total_price))
        else:
            cuurentShare = rows[0]["shares"]
            db.execute("UPDATE user_purchases SET shares = ?, total_price = ? WHERE userid = ? AND symbol = ?", intShares +
                       cuurentShare, usd((cuurentShare + intShares) * float(stock["price"])), int(session["user_id"]), stock["symbol"])
        return index()
    elif request.form.get("action") == "sell":
        currShares = realstock[0]["shares"]
        if intShares > realstock[0]["shares"]:
            return apology("You don't own that much stock to sell", 403)
        currStock = lookup(realstock[0]["symbol"])
        stockPrice = float(currStock["price"])
        totalPrice = stockPrice * intShares
        user_cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]
        db.execute("UPDATE users SET cash = ? WHERE id = ?",
                   user_cash + totalPrice, session["user_id"])
        current_time = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        db.execute("INSERT INTO Purchases (userid, type, symbol, price, shares, time) VALUES (?, ?, ?, ?, ?, ?)", int(
            session["user_id"]), "Sale", currStock["symbol"], usd(totalPrice), intShares, current_time)
        if realstock[0]["shares"] == intShares:
            db.execute("DELETE FROM user_purchases WHERE userid = ? AND symbol = ?",
                       int(session["user_id"]), currStock["symbol"])
            return index()
        else:
            cuurentShare = realstock[0]["shares"]
            db.execute("UPDATE user_purchases SET shares = ?, total_price = ? WHERE userid = ? AND symbol = ?", cuurentShare -
                       intShares, usd((cuurentShare - intShares) * float(currStock["price"])), int(session["user_id"]), currStock["symbol"])
            return index()
