""" Contains helper functions """
import config, bcrypt, classes
from datetime import datetime
from typing import Union
from database import *


def available_tutors(subject: str) -> list:
    """
    Returns a list containing all tutors that teach a given subject
    """
    available_tutors = []
    for tutor in config.all_tutors:
        if subject in tutor._subjects:
            available_tutors.append(tutor)
    # Print available tutors to console
    for tutor in available_tutors:
        print("----------------")
        tutor.profile()   
    print("----------------")
    return available_tutors


def validate_email(email: str) -> bool:
    """ 
    Validates if a given string is an email
    """
    return True
    #!TO DO


def confirm_password(pass1: str, pass2: str) -> bool:
    """
    Compares two given passwords for equality
    """
    return pass1 == pass2


def retrieve_email() -> str:
    """
    Retrieves user's email from user and checks for validity 
    """
    while True: 
        email = input("Email: ")
        if validate_email(email):
            return email
        print("--- Not a valid email address. ---")
        

def retrieve_password() -> str:
    """
    Retrieves a password from the user and returns the password hash
    """
    while True:
        # hash passwords using bcrypt
        salt = bcrypt.gensalt()
        password = input("Password: ").encode("utf-8")
        confirmation = input("Confirm password: ").encode("utf-8")
        hashed = bcrypt.hashpw(password, salt)
        hash_confirm = bcrypt.hashpw(confirmation, salt)
        # check if passwords match
        if confirm_password(hashed, hash_confirm):
            return hashed
        print("--- Passwords don't match. ---")


def email_in_database(email: str, type: str) -> bool:
    """
    Checks if a given email is already in the database
    Type differentiates between 'student' and 'tutor' account
    """
    db, dbcursor = connect_to_database()
    if type == "student":
        dbcursor.execute("SELECT COUNT(*) FROM Students WHERE email = (%s)", (email,))
    elif type == "tutor":
        dbcursor.execute("SELECT COUNT(*) FROM Tutors WHERE email = (%s)", (email,))
    count = dbcursor.fetchone()[0]
    # Close database connection
    if db and dbcursor:
        close_db_connection(db, dbcursor)
    return count > 0


def register_account(type: str) -> bool:
    """
    Creates an account and inserts it into the respective database
    Type differentiates between 'student' and 'tutor' account
    """
    print("--- REGISTER ---")
    email = retrieve_email()
    password = retrieve_password()
    if email_in_database(email, type):
        print("XX An account with this email already exists. XX")
        return False
    # All checks passed: account can be created
    else:
        if type == "student":
            return create_student_account(email, password)
        # Create tutor account [ADMIN ONLY]
        elif type == "tutor":
            return create_tutor_account(email, password)


def create_student_account(email: str, password: str) -> bool:
    """
    Creates a new student and adds it to the database 
    """
    print("--- Enter additional Information ---")
    name = input("Your name [last_name, first_name]: ")
    grad_year = input("Your graduation year: ")
    # Create new student in database
    db, dbcursor = connect_to_database()
    dbcursor.execute("INSERT INTO Students (name, email, password, grad_year) VALUES (%s, %s, %s, %s)", (name, email, password, grad_year))
    db.commit()
    dbcursor.execute("SELECT student_id FROM Students WHERE email = %s", (email,))
    id = dbcursor.fetchone()[0]
    new_student = classes.Student(name, grad_year, id)
    config.all_students.append(new_student)
    if db and dbcursor:
        close_db_connection(db, dbcursor)
    return True


def create_tutor_account(email: str, password: str) -> bool:
    """
    Creates a new tutor and adds it to the database 
    """
    print("--- Enter additional Information ---")
    name = str(input("Enter tutor name [last_name, first_name]: "))
    age = int(input("Enter tutor age: "))
    score = int(input("Enter tutor IB score: "))
    subjects = str(input("Enter eligible subjects: "))
    # Create new tutor in database
    db, dbcursor = connect_to_database()
    dbcursor.execute("INSERT INTO Tutors (name, email, password, age, score, subjects) VALUES (%s, %s, %s, %s, %s, %s)", (name, email, password, age, score, subjects))
    db.commit()
    dbcursor.execute("SELECT tutor_id FROM Tutors WHERE email = %s", (email,))
    id = dbcursor.fetchone()[0]
    new_tutor = classes.Tutor(name, id, age, score, subjects.split(","))
    config.all_tutors.append(new_tutor)
    if db and dbcursor:
        close_db_connection(db, dbcursor)
    return True


def login(type: str) -> bool:
    """
    Login function
    Type differentiates between student login and tutor login 
    True as return value denotes successful login
    """
    print("--- LOGIN ---")
    email = input("Email: ")
    password = input("Password: ").encode("utf-8")
    db, dbcursor = connect_to_database() # Open database connection
    # Differentiate between student and tutor
    if type == "student":   
        user_id = "student_id"
        table = "Students"
    elif type == "tutor":
        user_id = "tutor_id"
        table = "Tutors"
    # Execute login
    query_mail_count = f"SELECT COUNT(email) FROM {table} WHERE email = (%s)"
    dbcursor.execute(query_mail_count, (email,))
    if dbcursor.fetchone()[0] == 1:
        query_password = f"SELECT password, {user_id} FROM {table} WHERE email = (%s)"
        dbcursor.execute(query_password, (email,)) # Fetch stored password from database
        data = dbcursor.fetchone()
        if bcrypt.checkpw(password, data[0].encode("utf-8")):
            config.user_id = data[1]
            return True
    else: 
        print("--- No account has been registered at this email. ---")
        return False   
    if db and dbcursor:
        close_db_connection(db, dbcursor) # Close database connection


def choose_package() -> str:
    """
    Retrieves user input - what package they want to buy
    """
    while True:
        package = input("Choose package [5, 10, or 20 hours]: ")
        if package in config.packages:
            return package
        print("--- Please select a valid package. ---")


def choose_subject() -> str:
    """
    Retrieves user input - which subject the student wants to select
    """
    while True: 
        subject = input("Choose subject: ")
        if subject in config.subjects:
            return subject
        print("--- Please enter a valid subject. ---")


def print_booking_summary(package: str, subject: str) -> None:
    """
    Prints a summary of the booking for the student 
    """
    print("--- Booking summary: ---")
    print(f"|   Hours: {package}", end="")
    print(" "*(12-len(package))+"|")
    print(f"|   Subject: {subject}", end="")
    print(" "*(10-len(subject))+"|")
    print("------------------------")


def confirm_booking(package: str, subject: str) -> bool:
    """
    Retrieves user input - confirmation for booking
    """
    confirm = input("Please confirm [Y/N]: ")
    return True if confirm == "Y" else False


def find_user(user_id: int, type: str) -> Union[classes.Student, classes.Tutor]:
    """
    Finds a tutor/student in tutor/student lists based on user_id
    Type differentiates between student and tutor
    """
    if type == "student":
        for student in config.all_students:
            if student._student_id == user_id:
                return student
    elif type == "tutor":
        for tutor in config.all_tutors:
            if tutor._tutor_id == user_id:
                return tutor


def apply_to_tutor(tutors: list, booking: classes.Booking) -> None:
    """
    Add booking to tutor's applicants list  
    """
    while True:
        choice = int(input("Enter ID of tutor: "))
        for tutor in tutors:
            if tutor._tutor_id == choice:
                # Update Booking and add to tutors applicants list
                booking.requested(tutor)
                # Update Database
                db, dbcursor = connect_to_database()
                dbcursor.execute("UPDATE Bookings SET requested = (%s), requested_date = (%s), requested_tutor = (%s) WHERE booking_id = (%s)", (booking._requested, booking._requested_time, booking._requested_tutor._tutor_id, booking._booking_id))
                db.commit()
                # Close Database
                if db and dbcursor:
                    close_db_connection(db, dbcursor)
                print("--- Request has been sent. ---")
                return
        else:
            print("--- Please enter a valid ID from the List above. ---")
    

def retrieve_booking(tutor: classes.Tutor) -> classes.Booking:
    """
    Fetch booking from tutor's booking list
    """
    print("--- Choose booking. ---")
    tutor.list_all_bookings()
    while True:
        choice = int(input("Enter ID of booking: "))
        for booking in tutor._bookings:
            if booking._booking_id == choice:
                return booking
        else:
            print("--- Please enter a valid booking ID. ---")


def retrieve_date() -> None:
    """
    Retrieve user input - suggested lesson date 
    """
    print("--- Choose date. ---")
    while True:
        month = int(input("Which month [mm]: "))
        day = int(input("Which day [dd]: "))
        year = int(input("Which year [yyyy]: "))
        time = input("What time [hh:mm]: ")
        date = datetime(year, month, day, int(time.split(":")[0]), int(time.split(":")[1]))
        if date > datetime.now():
            return date
        else:
            print("--- Please enter a date in the future. ---")
        

def create_lesson(tutor: classes.Tutor) -> Union[classes.Lesson, classes.Booking]:
    """
    Retrieves user input - creates lesson object
    """
    # retrieve user input
    booking: classes.Booking = retrieve_booking(tutor)
    suggested_date: datetime = retrieve_date()
    length: int = int(input("Length: "))
    comments: str = input("Any comments for the student: ")
    if length > booking._remaining_credits:
        print("--- Student doesn't have enough credits left. --- ")
        return None, None
    # Insert lesson into database
    db, dbcursor = connect_to_database()
    dbcursor.execute("INSERT INTO Lessons (booking_id, suggested_date, length, comments) VALUES (%s, %s, %s, %s)", (booking._booking_id, suggested_date, length, comments))
    db.commit()
    print(suggested_date.strftime("%Y-%m-%d %H:%M:%S"))    # Retrieve id from database
    dbcursor.execute("SELECT lesson_id FROM Lessons WHERE suggested_date = (%s) AND booking_id = (%s)", (suggested_date.strftime("%Y-%m-%d %H:%M:%S"),booking._booking_id))
    id = dbcursor.fetchone()[0]
    # Close database connection
    if db and dbcursor:
        close_db_connection(db, dbcursor)
    # Return new lesson
    return classes.Lesson(booking, suggested_date, length, comments, id), booking

