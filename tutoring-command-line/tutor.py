""" Handles Tutor interface """
from helpers import * 


## brief: tutor account login, main tutor loop
def tutor_page(tutor_id: int):
    # Retrieving currently logged in student
    tutor: classes.Tutor = find_user(tutor_id, "tutor")
    print(f"--- Logged in as {tutor.fullname}, TUTOR ID: {tutor_id} ---")

    # Tutor account loop
    while True:
        choice = input("* Available students (1)\n* Active students (2)\n* Schedule a Lesson (3)\n* Upcoming Lessons (4)\n* Complete Lesson (5)\n* Sign out (0)\n")

        # Available students
        if choice == "1":
            tutor.manage_applicants()

        # Active students
        elif choice == "2":
            tutor.list_active_students()

        # Schedule a lesson
        elif choice == "3":
            tutor.suggest_lesson()

        # Upcoming Lessons
        elif choice == "4":
            tutor.print_all_lessons()

        # Complete Lesson
        elif choice == "5":
            tutor.complete_lesson()

        # Sign out 
        elif choice == "0":
            print("--------- Signing out from Tutor ---------")
            config.user_id = -1
            return