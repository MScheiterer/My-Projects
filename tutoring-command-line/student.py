""" Handles Student Interface """
from helpers import *


## brief: student account login, main student loop
def student_page(student_id: int):
    # Retrieving currently logged in student
    student: classes.Student = find_user(student_id, "student")
    print(f"--- Logged in as {student.fullname}, STUDENT ID: {student_id} ---")

    # Student account loop 
    while True:
        choice = input("* Buy Package (1)\n* Active Bookings (2)\n* Confirm Lessons (3)\n* Complete Lesson (4)\n* Upcoming Lessons (5)\n* Get matched with a Tutor (6)\n* Sign out (0)\n")
        # Buy Lesson credits
        if choice == "1":
            student.buy_package()

        # Active Bookings
        elif choice == "2":
            student.list_all_bookings()

        # Confirm suggested Lesson
        elif choice == "3":
            student.manage_lessons()

        # Complete Lesson
        elif choice == "4":
            student.complete_lesson()
                
        # Upcoming Lessons
        elif choice == "5":
            student.print_all_lessons()

        # Get matched with a tutor
        elif choice == "6":
            student.request_tutor()

        # Sign out from Student
        elif choice == "0":
            print("--------- Signing out from Student ---------")
            config.user_id = -1
            return