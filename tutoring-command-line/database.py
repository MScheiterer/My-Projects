""" Contains Database Access and Database Helpers """
import config, classes, mysql.connector
import helpers


def connect_to_database() -> mysql.connector:
    """ 
    Open mysql connection and create database cursor 
    """
    try: 
        # Database connection
        db = mysql.connector.connect(
            host="localhost",
            user="asznee",
            password="!PmuYhc28T",
            database="tutoring"
        )
        dbcursor = db.cursor()
        return db, dbcursor

    except mysql.connector.Error as connection_failure:
        print("--- Couldn't connect to database. ---")
        return None, None
    

def close_db_connection(db: mysql.connector, dbcursor: mysql.connector) -> None:
    """ 
    Close database cursor and mysql connection 
    """
    if dbcursor:
        dbcursor.close()
    if db:
        db.close()


def clear_database() -> None:
    """ 
    Drop/Truncate Database for test purposes 
    """
    db, dbcursor = connect_to_database()
    if db and dbcursor:
        # Get the list of all tables in the database
        dbcursor.execute("SHOW TABLES")
        tables = [table[0] for table in dbcursor.fetchall()]

        dbcursor.execute("DROP TABLE IF EXISTS Lessons")
        # Truncate all tables to delete their data
        for table in tables:
            dbcursor.execute(f"DROP TABLE IF EXISTS {table}")
        print("Database cleared successfully!")

    else:
        print("--- Couldn't connect to database. ---")

    close_db_connection(db, dbcursor)


def load_database(clear: bool) -> None:
    """
    | Load Students, Tutors, Bookings, Lessons from database if they exist
    | Create Students, Tutors, Bookings, Lessons Tables if they dont exist
    | Clear allows to truncate all tables
    """
    if clear:
        clear_database()
    # Create table
    db, dbcursor = connect_to_database()
    # Students Table
    dbcursor.execute("""
                    CREATE TABLE IF NOT EXISTS Students (
                        student_id INT PRIMARY KEY AUTO_INCREMENT,
                        name VARCHAR(255) NOT NULL,
                        email VARCHAR(255) NOT NULL,
                        password VARCHAR(255) NOT NULL,
                        grad_year INT NOT NULL
                    )""")
    # Tutors Table
    dbcursor.execute("""
                    CREATE TABLE IF NOT EXISTS Tutors (
                        tutor_id INT PRIMARY KEY AUTO_INCREMENT,
                        name VARCHAR(255) NOT NULL, 
                        email VARCHAR(255) NOT NULL, 
                        password VARCHAR(255) NOT NULL, 
                        age INT NOT NULL,
                        score INT NOT NULL,
                        subjects TEXT NOT NULL
                    )""")
    # Bookings Table
    dbcursor.execute("""
                    CREATE TABLE IF NOT EXISTS Bookings (
                        booking_id INT PRIMARY KEY AUTO_INCREMENT,
                        student_id INT NOT NULL,
                        subject VARCHAR(100) NOT NULL,
                        credits INT NOT NULL, 
                        remaining_credits INT,
                        booking_date DATETIME NOT NULL, 
                        requested BOOL DEFAULT FALSE,
                        requested_date DATETIME,
                        requested_tutor INT,
                        matched BOOL DEFAULT FALSE,
                        matched_date DATETIME,
                        tutor_id INT,
                        FOREIGN KEY (student_id) REFERENCES Students(student_id), 
                        FOREIGN KEY (tutor_id) REFERENCES Tutors(tutor_id),
                        FOREIGN KEY (requested_tutor) REFERENCES Tutors(tutor_id)
                    )""")
    # Lessons Table 
    dbcursor.execute("""
                    CREATE TABLE IF NOT EXISTS Lessons (
                        lesson_id INT PRIMARY KEY AUTO_INCREMENT,
                        booking_id INT NOT NULL,
                        suggested_date DATETIME,
                        date DATETIME,
                        length INT NOT NULL,
                        comments TEXT,
                        student_complete BOOL DEFAULT FALSE,
                        tutor_complete BOOL DEFAULT FALSE,
                        FOREIGN KEY (booking_id) REFERENCES Bookings(booking_id)
                    )""")
    db.commit()

    # Load Students from database
    dbcursor.execute("SELECT name, grad_year, student_id FROM Students")
    result = dbcursor.fetchall()
    for row in result:
        name = row[0]
        grad_year = row[1]
        student_id = row[2]
        new_student = classes.Student(name, grad_year, student_id)
        config.all_students.append(new_student)

    # Load Tutors from database
    dbcursor.execute("SELECT name, tutor_id, age, score, subjects FROM Tutors")
    result = dbcursor.fetchall()
    for row in result:
        name = row[0]
        tutor_id = row[1]
        age = row[2]
        score = row[3]
        subjects = row[4].split(",")
        new_tutor = classes.Tutor(name, tutor_id, age, score, subjects)
        config.all_tutors.append(new_tutor)

    # Load Bookings and match to respective Tutors and Students
    dbcursor.execute("SELECT * FROM Bookings")
    result = dbcursor.fetchall()
    for row in result:
        booking_id = row[0]
        student = helpers.find_user(row[1], "student")
        subject = row[2]
        credits = row[3]
        remaining_credits = row[4]
        booking_date = row[5]
        requested = row[6]
        requested_time = row[7]
        requested_tutor = helpers.find_user(row[8], "tutor")
        matched = row[9]
        matched_time = row[10]
        current_tutor = helpers.find_user(row[11], "tutor")
        new_booking = classes.Booking(student, subject, credits, booking_id, booking_date,\
                                      matched_time=matched_time, requested_time=requested_time,\
                                      requested_tutor=requested_tutor, current_tutor=current_tutor,\
                                      matched=matched, requested=requested, remaining_credits=remaining_credits)
        student._bookings.append(new_booking)
        if matched:
            current_tutor._bookings.append(new_booking) 
        elif requested:
            requested_tutor._applicants.append(new_booking)

    # Load Lessons and match to bookings
    dbcursor.execute("SELECT * FROM Lessons")
    result = dbcursor.fetchall()
    for row in result:
        lesson_id = row[0]
        booking_id = row[1]
        lesson_booking = ""
        # Find booking 
        for student in config.all_students:
            for booking in student._bookings:
                if booking._booking_id == booking_id:
                    lesson_booking = booking
        suggested_date = row[2]
        date = row[3]
        length = row[4]
        comments = row[5]
        student_complete = row[6]
        tutor_complete = row[7]
        new_lesson = classes.Lesson(booking=lesson_booking, suggested_date=suggested_date, length=length, id=lesson_id, date=date, comments=comments, student_complete=student_complete, tutor_complete=tutor_complete)
        booking._lessons.append(new_lesson)

    # Close database connection   
    if db and dbcursor:
        dbcursor.close()
        db.close()

        
    



