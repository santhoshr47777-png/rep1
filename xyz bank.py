import mysql.connector as con
import random
mycon=con.connect(host="bcwmppuikrrxedoznhqj-mysql.services.clever-cloud.com",user="uryt7ugttcpdbq6q",password="KMV52k2jP9V1i71tUJfX" ,db="bcwmppuikrrxedoznhqj")
cursor=mycon.cursor()
qry1='''CREATE TABLE IF NOT EXISTS details (
    username   VARCHAR(30) UNIQUE,
    passwd     VARCHAR(255) NOT NULL,
    email      VARCHAR(50) NOT NULL UNIQUE,
    mobile_no  VARCHAR(15) NOT NULL UNIQUE,
    acc_no     BIGINT UNIQUE,
    balance    DECIMAL(15,2) NOT NULL DEFAULT 0.00,
    PRIMARY KEY (acc_no)
)'''
cursor.execute(qry1)
print("true")
def generate_acc_no():
    while True:
        acc_no = random.randint(1000000000, 9999999999)  # 10-digit random number
        cursor.execute("SELECT acc_no FROM details WHERE acc_no = %s", (acc_no,))
        if not cursor.fetchone():  # unique
            return acc_no
def create_user():
    username=input("Enter your username: ")
    passwd=input("Enter your password: ")
    email=input("Enter your email: ")
    mobile_no=input("Enter your mobile number: ")
    balance=0.00

    acc_no = generate_acc_no()  # ✅ random & unique

    qry2="INSERT INTO details (username, passwd, email, mobile_no, acc_no, balance) VALUES (%s, %s, %s, %s, %s, %s)"
    values=(username, passwd, email, mobile_no, acc_no, balance)

    try:
        cursor.execute(qry2, values)
        mycon.commit()
        print("User created successfully.")
        print(f"Your Account Number is: {acc_no}")
    except con.IntegrityError as e:
        print(f"Error: {e}")
    except Exception as e:
        print(f"An error occurred: {e}")

def login():
    username=input("Enter your username: ")
    passwd=input("Enter your password: ")
    qry3="SELECT * FROM details WHERE username=%s AND passwd=%s"
    values=(username, passwd)
    cursor.execute(qry3, values)
    result=cursor.fetchone()
    if result:
        print("Login successful.")
        return username
    else:
        print("Invalid username or password.")
        return None
def deposit(username):
    amount=float(input("Enter amount to deposit: "))
    if amount <= 0:
        print("Deposit amount must be positive.")
        return
    qry4="UPDATE details SET balance = balance + %s WHERE username = %s"
    values=(amount, username)
    cursor.execute(qry4, values)
    mycon.commit()
    print(f"Deposited {amount:.2f} successfully.")
def withdraw(username):
    amount=float(input("Enter amount to withdraw: "))
    if amount <= 0:
        print("Withdrawal amount must be positive.")
        return
    qry5="SELECT balance FROM details WHERE username = %s"
    values=(username,)
    cursor.execute(qry5, values)
    result=cursor.fetchone()
    if result and result[0] >= amount:
        qry6="UPDATE details SET balance = balance - %s WHERE username = %s"
        values=(amount, username)
        cursor.execute(qry6, values)
        mycon.commit()
        print(f"Withdrew {amount:.2f} successfully.")
    else:
        print("Insufficient balance.")
def check_balance(username):
    qry7="SELECT balance FROM details WHERE username = %s"
    values=(username,)
    cursor.execute(qry7, values)
    result=cursor.fetchone()
    if result:
        print(f"Your current balance is: {result[0]:.2f}")
    else:
        print("User not found.")
def main():
    while True:
        print("\n\t\tWelcome to XYZ Bank")
        print("\t\t\t1. Create User")
        print("\t\t\t2. Login")
        print("\t\t\t3. Exit")
        choice=input("Enter your choice: ")
        if choice=='1':
            create_user()
        elif choice=='2':
            username=login()
            if username:
                while True:
                    print("\n1. Deposit")
                    print("2. Withdraw")
                    print("3. Check Balance")
                    print("4. Logout")
                    sub_choice=input("Enter your choice: ")
                    if sub_choice=='1':
                        deposit(username)
                    elif sub_choice=='2':
                        withdraw(username)
                    elif sub_choice=='3':
                        check_balance(username)
                    elif sub_choice=='4':
                        print("Logged out successfully.")
                        break
                    else:
                        print("Invalid choice. Please try again.")
        elif choice=='3':
            print("Thank you for using XYZ Bank. Goodbye!")
            break
        else:
            print("Invalid choice. Please try again.")
if __name__=="__main__":
    main()