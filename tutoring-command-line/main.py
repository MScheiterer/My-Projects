""" command line based tutoring platform """
from admin import admin_page
from student import student_page 
from tutor import tutor_page
from helpers import config, login, register_account
from database import load_database

load_database(clear = False)


# video link: https://youtu.be/xqYH7lbW7wk


def main():
    # menu loop
    while True:   
        print("------------------------------------------------------------------------------------")     
        choice = input("* Log in as Admin (1)\n* Register as student (2)\n* Login as student (3)\n* Login as tutor (4)\n* Exit (0)\n")
        # Log in as admin [user: asznee, password: asznee]
        if choice == "1":
            username = input("username: ")
            password = input("password: ")
            if username == config.ADMIN and password == config.ADMIN_PASS:
                print("--------- Logged in as Admin ---------")
                admin_page()
            else: 
                print("Username or password incorrect.")

        # Registering as student
        elif choice == "2":
            if not register_account("student"):
                print("--- Canceling... ---")
            else:
                print("--- Registered Successfully ---")

        # Login as student
        elif choice == "3":
            if login("student"):
                student_page(config.user_id)
            else: 
                print("Login unsuccessful. Try again.")

        # Login as tutor
        elif choice == "4":
            if login("tutor"):
                tutor_page(config.user_id)
            else:
                print("Login unsuccessful. Try again.")

        # Exit
        else: 
            print("Goodbye")
            break

main()









