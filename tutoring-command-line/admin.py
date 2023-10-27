""" Handles Admin Interface """
from helpers import *


## brief: function that runs admin loop
def admin_page():
    print("------------------------------------------------------------------------------------")
    while True:
        choice = input("* Add new Tutor (1)\n* Add new Student (2)\n* Print Database (3)\n* Sign out (0)\n")

        # Create new Tutor
        if choice == "1":
            # Create Tutor account and object
            if register_account("tutor"):
                print("--- New tutor has been created by Admin ---")

        # Create new Student
        elif choice == "2":
            # Create student account and student object
            if register_account("student"):
                print("--- New Student has been created by Admin ---")

        # Print Database
        elif choice == "3":
            # tutors
            if config.all_tutors:
                print("Current tutors:")
                for tutor in config.all_tutors:
                    tutor.out()
            else:
                print("No active tutors.")
            # students
            if config.all_students:
                print("Current students:")
                for student in config.all_students:
                    student.out()
            else: 
                print("No active students.")

        # Sign out from Admin       
        elif choice == "0":
            print("--------- Signing out from Admin ---------")
            return