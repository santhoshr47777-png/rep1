import sys
import random
import re
import hashlib
import mysql.connector as con
from PyQt5.QtWidgets import (
    QApplication, QWidget, QVBoxLayout, QHBoxLayout, QPushButton,
    QLabel, QLineEdit, QTextEdit, QMessageBox, QStackedWidget, QFormLayout
)

# === DB Connection ===
mycon = con.connect(
    host="bcwmppuikrrxedoznhqj-mysql.services.clever-cloud.com",
    user="uryt7ugttcpdbq6q",
    password="KMV52k2jP9V1i71tUJfX",
    db="bcwmppuikrrxedoznhqj"
)
cursor = mycon.cursor()

# === Utility functions ===
def generate_acc_no():
    while True:
        acc_no = random.randint(1000000000, 9999999999)
        cursor.execute("SELECT acc_no FROM details WHERE acc_no=%s", (acc_no,))
        if not cursor.fetchone():
            return acc_no

def hash_password(password):
    return hashlib.sha256(password.encode()).hexdigest()

def validate_email(email):
    return re.match(r"[^@]+@[^@]+\.[^@]+", email)

def validate_mobile(mobile):
    return mobile.isdigit() and 10 <= len(mobile) <= 15


# === Main Banking App ===
class BankApp(QWidget):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("🏦 XYZ Bank")
        self.setGeometry(200, 100, 800, 500)

        # Layout
        main_layout = QHBoxLayout(self)

        # Sidebar (Navigation)
        sidebar = QVBoxLayout()
        self.btn_create = QPushButton("Create Account")
        self.btn_login = QPushButton("Login")
        self.btn_dashboard = QPushButton("Dashboard")
        self.btn_txn = QPushButton("Transactions")
        self.btn_logout = QPushButton("Logout")

        for btn in [self.btn_create, self.btn_login, self.btn_dashboard, self.btn_txn, self.btn_logout]:
            sidebar.addWidget(btn)

        # Pages (Stacked)
        self.stack = QStackedWidget(self)
        self.page_create = self.create_account_page()
        self.page_login = self.login_page()
        self.page_dashboard = self.dashboard_page()
        self.page_txn = self.transactions_page()

        self.stack.addWidget(self.page_create)     # index 0
        self.stack.addWidget(self.page_login)      # index 1
        self.stack.addWidget(self.page_dashboard)  # index 2
        self.stack.addWidget(self.page_txn)        # index 3

        # Add layouts
        main_layout.addLayout(sidebar, 1)
        main_layout.addWidget(self.stack, 3)

        # Button actions
        self.btn_create.clicked.connect(lambda: self.stack.setCurrentIndex(0))
        self.btn_login.clicked.connect(lambda: self.stack.setCurrentIndex(1))
        self.btn_dashboard.clicked.connect(lambda: self.stack.setCurrentIndex(2))
        self.btn_txn.clicked.connect(lambda: self.stack.setCurrentIndex(3))
        self.btn_logout.clicked.connect(self.logout)

        self.acc_no = None  # Track logged in user

    # === Create Account Page ===
    def create_account_page(self):
        page = QWidget()
        layout = QFormLayout(page)

        self.in_user = QLineEdit()
        self.in_pass = QLineEdit(); self.in_pass.setEchoMode(QLineEdit.Password)
        self.in_email = QLineEdit()
        self.in_mobile = QLineEdit()

        btn_submit = QPushButton("Submit")
        btn_submit.clicked.connect(self.create_account)

        layout.addRow("Username:", self.in_user)
        layout.addRow("Password:", self.in_pass)
        layout.addRow("Email:", self.in_email)
        layout.addRow("Mobile:", self.in_mobile)
        layout.addRow(btn_submit)

        return page

    def create_account(self):
        u, p, e, m = self.in_user.text(), self.in_pass.text(), self.in_email.text(), self.in_mobile.text()
        if not validate_email(e):
            QMessageBox.warning(self, "Error", "Invalid email")
            return
        if not validate_mobile(m):
            QMessageBox.warning(self, "Error", "Invalid mobile")
            return

        acc_no = generate_acc_no()
        hp = hash_password(p)

        try:
            cursor.execute("INSERT INTO details VALUES (%s,%s,%s,%s,%s,%s)",
                           (acc_no, u, hp, e, m, 0.00))
            mycon.commit()
            QMessageBox.information(self, "Success", f"Account created!\nYour Account No: {acc_no}")
            self.in_user.clear(); self.in_pass.clear(); self.in_email.clear(); self.in_mobile.clear()
        except Exception as ex:
            QMessageBox.warning(self, "Error", str(ex))

    # === Login Page ===
    def login_page(self):
        page = QWidget()
        layout = QFormLayout(page)

        self.in_acc = QLineEdit()
        self.in_login_pass = QLineEdit(); self.in_login_pass.setEchoMode(QLineEdit.Password)
        btn_login = QPushButton("Login")
        btn_login.clicked.connect(self.login_user)

        layout.addRow("Account No:", self.in_acc)
        layout.addRow("Password:", self.in_login_pass)
        layout.addRow(btn_login)

        return page

    def login_user(self):
        acc = self.in_acc.text().strip()
        hp = hash_password(self.in_login_pass.text().strip())

        cursor.execute("SELECT * FROM details WHERE acc_no=%s AND passwd=%s", (acc, hp))
        if cursor.fetchone():
            self.acc_no = acc
            QMessageBox.information(self, "Login", "Login successful")
            self.stack.setCurrentIndex(2)  # Go to dashboard
        else:
            QMessageBox.warning(self, "Error", "Invalid credentials")

    # === Dashboard Page ===
    def dashboard_page(self):
        page = QWidget()
        layout = QVBoxLayout(page)

        self.lbl_balance = QLabel("Balance: -")
        btn_deposit = QPushButton("Deposit")
        btn_withdraw = QPushButton("Withdraw")
        btn_refresh = QPushButton("Refresh Balance")

        btn_deposit.clicked.connect(self.deposit_money)
        btn_withdraw.clicked.connect(self.withdraw_money)
        btn_refresh.clicked.connect(self.check_balance)

        layout.addWidget(self.lbl_balance)
        layout.addWidget(btn_deposit)
        layout.addWidget(btn_withdraw)
        layout.addWidget(btn_refresh)

        return page

    def check_balance(self):
        if not self.acc_no: return
        cursor.execute("SELECT balance FROM details WHERE acc_no=%s", (self.acc_no,))
        bal = cursor.fetchone()[0]
        self.lbl_balance.setText(f"Balance: {bal:.2f}")

    def deposit_money(self):
        if not self.acc_no: return
        amt, ok = QInputDialog.getDouble(self, "Deposit", "Amount:")
        if ok and amt > 0:
            cursor.execute("UPDATE details SET balance=balance+%s WHERE acc_no=%s", (amt, self.acc_no))
            cursor.execute("INSERT INTO transactions(acc_no,txn_type,amount) VALUES (%s,%s,%s)",
                           (self.acc_no, "DEPOSIT", amt))
            mycon.commit()
            QMessageBox.information(self, "Success", f"Deposited {amt:.2f}")
            self.check_balance()

    def withdraw_money(self):
        if not self.acc_no: return
        amt, ok = QInputDialog.getDouble(self, "Withdraw", "Amount:")
        if ok and amt > 0:
            cursor.execute("SELECT balance FROM details WHERE acc_no=%s", (self.acc_no,))
            bal = cursor.fetchone()[0]
            if bal >= amt:
                cursor.execute("UPDATE details SET balance=balance-%s WHERE acc_no=%s", (amt, self.acc_no))
                cursor.execute("INSERT INTO transactions(acc_no,txn_type,amount) VALUES (%s,%s,%s)",
                               (self.acc_no, "WITHDRAW", amt))
                mycon.commit()
                QMessageBox.information(self, "Success", f"Withdrew {amt:.2f}")
                self.check_balance()
            else:
                QMessageBox.warning(self, "Error", "Insufficient balance")

    # === Transactions Page ===
    def transactions_page(self):
        page = QWidget()
        layout = QVBoxLayout(page)
        self.txn_list = QTextEdit()
        self.txn_list.setReadOnly(True)
        btn_load = QPushButton("Load Transactions")
        btn_load.clicked.connect(self.load_txn)
        layout.addWidget(self.txn_list)
        layout.addWidget(btn_load)
        return page

    def load_txn(self):
        if not self.acc_no: return
        cursor.execute("SELECT txn_type,amount,txn_time FROM transactions WHERE acc_no=%s ORDER BY txn_time DESC", (self.acc_no,))
        rows = cursor.fetchall()
        if rows:
            text = "\n".join([f"{r[0]}: {r[1]} at {r[2]}" for r in rows])
        else:
            text = "No transactions"
        self.txn_list.setText(text)

    # === Logout ===
    def logout(self):
        self.acc_no = None
        QMessageBox.information(self, "Logout", "Logged out successfully")
        self.stack.setCurrentIndex(1)


# === Run App ===
if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = BankApp()
    window.show()
    sys.exit(app.exec_())
