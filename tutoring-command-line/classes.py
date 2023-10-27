""" Contains Tutor, Student, Booking and Lesson classes """
import datetime
import helpers

# Class declarations
class Tutor:
    pass
class Student:
    pass
class Booking:
    pass
class Lesson:
    pass


## brief: class used to maintain tutors 
## var name: string containing Tutors full name in the format "last_name, first_name"
## var age: integer containing Tutors current age
## var score: integer containing Tutors IB score
## list subjects: list of strings containing the subjects the Tutor is eligible to teach 
## list students: list of Booking Objects that the tutor has been assigned
## list applicants: contains Bookings of students who would like to have the tutor
## list bookings: countains Bookings that the tutor has already matched with
class Tutor:
    # Constructor
    def __init__(self, name, id, age, score, subjects):
        self._name: str = name
        self._age: int = age
        self._score: int = score
        self._subjects: list = subjects
        self._tutor_id: int = id
        self._bookings: Booking = []
        self._applicants: Booking = []
        self._summary = "I am a great tutor and have a lot of experience."
        print("--- New tutor created. ---")

    # Prints information about the tutor
    def out(self):
        # printing tutor info
        print("--------------------")
        print(f"| TUTOR ID: {self._tutor_id}\n| Name: {self.fullname}\n| Subjects: {', '.join(self._subjects)} \n| Booking IDs: ", end="")
        # printing active students
        if self._bookings:
            id_list = []
            for booking in self._bookings:
                id_list.append(str(booking._booking_id))
            print(', '.join(id_list))
        else: 
            print("This tutor has no active students.")
        print("--------------------")

    # Create full name 
    @property
    def fullname(self):
        first = self._name.split(",")[1].strip()
        last = self._name.split(",")[0].strip()
        return first + " " + last
    
    # Tutor profile that is presented to the student 
    def profile(self):
        print(f"Name: {self.fullname} | ID: {self._tutor_id}\nAge: {self._age}\nIB Score: {self._score}")
        print(f"Summary: {self._summary}")

    # Accept or reject all applications
    def manage_applicants(self):
        if not self._applicants:
            print("You don't have any applicants at the moment.")
            return
        for booking in self._applicants:
            booking.out()
            # User input
            while True:
                choice = input("Accept or Reject [Y/N]: ")
                # Accept
                if choice == "Y":
                    booking.match(self)
                    self._bookings.append(booking)
                    self._applicants.remove(booking)
                    break
                # Reject
                elif choice == "N":
                    print("--- We're new so you don't have a choice. ---")
                else:
                    print("--- Enter 'Y' or 'N' ---")

    # Print all active students to console
    def list_active_students(self):
        if self._bookings:
            for student in self._bookings:
                student.out()
        else:
            print("--- No active students. ---")

    # Print all bookings to console
    def list_all_bookings(self):
        for booking in self._bookings:
            booking.out()

    # Suggest a date for an upcoming lesson
    def suggest_lesson(self):
        lesson, booking = helpers.create_lesson(self)
        if lesson and booking:
            booking._lessons.append(lesson)
        else:
            print("--- Please try again. ---")

    # Print all upcoming lessons
    def print_all_lessons(self):
        for booking in self._bookings:
            booking.print_all_lessons()

    # Complete a lesson that has occured
    def complete_lesson(self):
        # list all bookings
        self.list_all_bookings()
        # choose booking
        booking = self.find_booking_byID()
        # confirm lessons
        for lesson in booking._lessons:
            if not lesson.completed:
                lesson.out()
                # User input
                while True:
                    choice = input("Lesson completed [Y/N]: ")
                    # Accept
                    if choice == "Y":
                        lesson._tutor_complete = True
                        # Update database
                        db, dbcursor = helpers.connect_to_database()
                        dbcursor.execute("UPDATE Lessons SET student_complete = TRUE WHERE lesson_id = (%s)", (lesson._lesson_id,))
                        db.commit()
                        helpers.close_db_connection(db, dbcursor)
                        lesson.complete()
                        break
                    # Reject
                    elif choice == "N":
                        print("--- Come back once the lesson has been completed. ---")
                        break
                    else:
                        print("--- Enter 'Y' or 'N' ---")

    ## Finds a Booking in a list of bookings by booking_id
    def find_booking_byID(self):
        while True:
            choice = int(input("Enter ID of booking: "))
            for booking in self._bookings: 
                if booking._booking_id == choice:
                    return booking
            else:
                print("--- Please enter an ID from your Bookings List. ---")
        
                    



## brief: class used to maintain students 
## var name: string containing Students full name in the format "last_name, first_name"
## var age: integer containing Students current age
## var grad_year: integer containing the year in which the Student will graduate
## list bookings: list containing all the students bookings
class Student:
    # constructor 
    def __init__(self, name, grad_year, id):
        self._name: str = name
        self._grad_year: int = grad_year
        self._bookings: Booking = []
        self._student_id: int = id
        print("--- New student created. ---")

    # print student information
    def out(self):
        # printing student info
        print("--------------------")
        print(f"| STUDENT ID: {self._student_id} \n| Name: {self.fullname}\n| Graduation Year: {self._grad_year}\n| Booking IDs: ", end="")
        # if already bought bookings
        if self._bookings:
            id_list = []
            for booking in self._bookings:
                id_list.append(str(booking._booking_id))
            print(', '.join(id_list))
        else: 
            print("No packages booked yet.")
        print("--------------------")

    # add lesson credits
    def add_booking(self, package, subject):
        # create new package and append to subjects 
        db, dbcursor = helpers.connect_to_database()
        booking_time = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        dbcursor.execute("INSERT INTO Bookings (student_id, subject, credits, booking_date) VALUES (%s, %s, %s, %s)", (self._student_id, subject, package, booking_time))
        db.commit()
        dbcursor.execute("SELECT booking_id FROM Bookings WHERE booking_date = (%s) AND student_id = (%s)", (booking_time, self._student_id))
        booking_id = dbcursor.fetchone()[0]
        new_booking = Booking(self, subject, package, booking_id, booking_time)
        if db and dbcursor:
            helpers.close_db_connection(db, dbcursor)
        self._bookings.append(new_booking)


    # Create full name 
    @property
    def fullname(self):
        first = self._name.split(",")[1].strip()
        last = self._name.split(",")[0].strip()
        return first + " " + last
    
    # Print all unmatched bookings to console
    def list_unmatched_bookings(self):
        if self._bookings:
            for booking in self._bookings:
                if booking._requested and not booking._matched:
                    print("----------------")
                    booking.out()
                    print(f"--- Waiting for confirmation by Tutor {booking._requested_tutor.fullname}")
                elif not booking._requested and not booking._matched:
                    print("----------------")
                    booking.out()
            print("----------------")
        else:
            print("--- You have no unmatched bookings. ---")

    # Print all unmatched bookings to console
    def list_matched_bookings(self):
        if self._bookings:
            booking_found = False
            for booking in self._bookings:
                if booking._matched:
                    booking_found = True
                    print("----------------")
                    booking.out()
            print("----------------")
            if not booking_found:
                print("--- You have no matched bookings. ---")
        else:
            print("--- You have no bookings. ---")

    # Print all bookings to console
    def list_all_bookings(self):
        if self._bookings:
            for booking in self._bookings:
                booking.out()
        else:
            print("--- No active bookings. ---")

    ## Finds a Booking in a list of bookings by booking_id
    def find_booking_byID(self):
        while True:
            choice = int(input("Enter ID of booking: "))
            for booking in self._bookings: 
                if booking._booking_id == choice:
                    return booking
            else:
                print("--- Please enter an ID from your Bookings List. ---")

    ## Requests to be matched with a tutor
    def request_tutor(self):
        # Check whether student has bought any packages
        if self._bookings:
            # list all bookings
            self.list_unmatched_bookings()
            # choose booking
            booking = self.find_booking_byID()
            if booking._requested:
                print("--- You already requested a tutor for this booking. ---")
                return
            # list available tutors
            tutors = helpers.available_tutors(booking._subject)
            # choose tutor and send request
            if tutors:
                helpers.apply_to_tutor(tutors, booking)
            else:
                print("--- Unfortunately there are no tutors available at the moment. We'll notify you as soon as a tutor is available. ---")
        else:
            print("--- No active bookings. ---")

    ## Buy a package 
    def buy_package(self):
        package = helpers.choose_package()
        subject = helpers.choose_subject()
        helpers.print_booking_summary(package, subject)
        if helpers.confirm_booking(package, subject):
            self.add_booking(package, subject)
            print("--- Credits bought. ---")
        else:
            print("--- Canceling... ---")

    # Print all lessons to console
    def print_all_lessons(self):
        for booking in self._bookings:
            booking.print_all_lessons()

    # Accept or reject suggested lesson
    def manage_lessons(self):
        # list all matched bookings
        self.list_matched_bookings()
        # choose booking
        booking = self.find_booking_byID()
        # confirm lessons
        for lesson in booking._lessons:
            if not lesson._date:
                lesson.out()
                # User input
                while True:
                    choice = input("Accept or Reject [Y/N]: ")
                    # Accept
                    if choice == "Y":
                        lesson.accept()
                        break
                    # Reject
                    elif choice == "N":
                        lesson.reject()
                        break
                    else:
                        print("--- Enter 'Y' or 'N' ---")

    # Complete a lesson that has occured
    def complete_lesson(self):
        # list all matched bookings
        self.list_matched_bookings()
        # choose booking
        booking = self.find_booking_byID()
        # confirm lessons
        for lesson in booking._lessons:
            if not lesson.completed:
                lesson.out()
                # User input
                while True:
                    choice = input("Lesson completed [Y/N]: ")
                    # Accept
                    if choice == "Y":
                        lesson._student_complete = True
                        # Update database
                        db, dbcursor = helpers.connect_to_database()
                        dbcursor.execute("UPDATE Lessons SET student_complete = TRUE WHERE lesson_id = (%s)", (lesson._lesson_id,))
                        db.commit()
                        helpers.close_db_connection(db, dbcursor)
                        lesson.complete()
                        break
                    # Reject
                    elif choice == "N":
                        print("--- Come back once the lesson has been completed. ---")
                        break
                    else:
                        print("--- Enter 'Y' or 'N' ---")



## brief: Booking objects encapsulate all required information pertaining to booking tutoring lessons
## Student student: the student who booked the package
## str subject: the subject that the student booked
## int credits: how many hours the student booked
class Booking:
    def __init__(self, student: Student, subject: str, credits: int, booking_id, booking_time: datetime,\
                 matched = False, requested = False, matched_time: datetime=None, lessons: Lesson=[],\
                 requested_time: datetime = None, requested_tutor:Tutor=None, current_tutor: Tutor=None,\
                 remaining_credits: int=None):
        self._student: Student = student
        self._subject: str = subject
        self._credits: int = int(credits)
        self._booking_date: datetime = booking_time
        self._matched: bool = matched
        self._requested: bool = requested
        self._booking_id: int = booking_id
        # These are unknown when the object is created
        self._matched_time: datetime = matched_time
        self._requested_time: datetime = requested_time
        self._requested_tutor: Tutor = requested_tutor
        self._current_tutor: Tutor = current_tutor
        self._lessons: Lesson = lessons
        self._remaining_credits: int = int(remaining_credits) if remaining_credits is not None else int(credits)
        print("--- New booking created. ---")

    # Match Booking with tutor 
    def match(self, tutor: Tutor):
        self._matched = True
        self._current_tutor = tutor
        self._matched_time = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        db, dbcursor = helpers.connect_to_database()
        dbcursor.execute("UPDATE Bookings SET matched = (%s), matched_date = (%s), tutor_id = (%s) WHERE booking_id = (%s)", (self._matched, self._matched_time, self._current_tutor._tutor_id, self._booking_id))
        db.commit()
        if db and dbcursor:
            helpers.close_db_connection(db, dbcursor)
        print(f"--- Student {self._student.fullname} | ID: {self._student._student_id} was matched with Tutor {self._current_tutor.fullname} | ID: {self._current_tutor._tutor_id} on {self._matched_time} ---")
        print("--- Booking summary:")
        self.out()
    
    # Print Booking information
    def out(self):
        print("--------------------")
        if not self._matched:
            print(f"| BOOKING ID: {self._booking_id} \n| Student: {self._student.fullname} \n| {self._subject}: {self._credits} Credits \n| Waiting for tutor... ---")
        else:
            print(f"| BOOKING ID: {self._booking_id} \n| Student: {self._student.fullname} \n| {self._subject}: {self._credits} Credits \n| Tutor: {self._current_tutor.fullname} ---")
        print("--------------------")

    # Update that student requested a tutor
    def requested(self, tutor: Tutor):
        self._requested = True
        self._requested_time = datetime.datetime.now()
        self._requested_tutor = tutor
        tutor._applicants.append(self)

    # Print all scheduled/suggested Lessons to concole
    def print_all_lessons(self):
        # Scheduled lessons first
        for lesson in self._lessons:
            if lesson._date:
                lesson.out()
        # Suggested Lessons
        for lesson in self._lessons:
            if not lesson._date:
                lesson.out()

    # Find lesson by ID
    def find_lesson_byID(self):
        while True:
            choice = int(input("Enter ID of lesson: "))
            for lesson in self._lessons: 
                if lesson._lesson_id == choice:
                    return lesson
            else:
                print("--- Please enter an ID from your Bookings List. ---")






class Lesson:
    def __init__(self, booking: Booking, suggested_date: datetime, length: int, comments: str, id: int, date: datetime=None, student_complete=False, tutor_complete=False):
        self._booking: Booking = booking
        self._suggested_date: datetime = suggested_date
        self._date: datetime = date
        self._length: int = length
        self._comments: str = comments
        self._lesson_id: int = id
        self._student_complete: bool = student_complete
        self._tutor_complete: bool = tutor_complete
        print("--- Lesson created. ---")

    @property
    def completed(self):
        return self._student_complete and self._tutor_complete

    # Print lesson information
    def out(self):
        print("--------------------")
        if self._date:
            print(f"| COMPLETED: {self.completed} \n| LESSON ID: {self._lesson_id} \n| BOOKING ID: {self._booking._booking_id} \n| STUDENT ID: {self._booking._student._student_id} \n| TUTOR ID: {self._booking._current_tutor._tutor_id} \n| SCHEDULED ON {self._date.strftime('%Y-%m-%d %H:%M')}")
        else:
            print(f"| COMPLETED: {self.completed} \n| LESSON ID: {self._lesson_id} \n| BOOKING ID: {self._booking._booking_id} \n| STUDENT ID: {self._booking._student._student_id} \n| TUTOR ID: {self._booking._current_tutor._tutor_id} \n| SUGGESTED FOR {self._suggested_date.strftime('%Y-%m-%d %H:%M')}")
        print("--------------------")

    # Accept a scheduled lesson
    def accept(self):
        self._date = self._suggested_date
        # update in database 
        db, dbcursor = helpers.connect_to_database()
        dbcursor.execute("UPDATE Lessons SET date = (%s) WHERE lesson_id = (%s)", (self._date, self._lesson_id))
        db.commit()
        helpers.close_db_connection(db, dbcursor)
        print("--- Lesson accept. ---")

    # Reject a suggested lesson
    def reject(self):
        self._suggested_date = None
        # update in database 
        db, dbcursor = helpers.connect_to_database()
        dbcursor.execute("DELETE FROM Lessons WHERE lesson_id = (%s)", (self._lesson_id,))
        self._booking._lessons.remove(self)
        db.commit()
        helpers.close_db_connection(db, dbcursor)
        print("--- Lesson rejected. ---")

    def complete(self):
        if self._student_complete and not self._tutor_complete:
            print("--- Waiting for tutor to complete lesson. ---")
        elif not self._student_complete and self._tutor_complete:
            print("--- Waiting for student to complete lesson. ---")
        else:
            # Update remainning credits
            self._booking._remaining_credits -= self._length
            # Update database entry
            db, dbcursor = helpers.connect_to_database()
            dbcursor.execute("UPDATE Bookings SET remaining_credits = (%s) WHERE booking_id = (%s)", (self._booking._remaining_credits, self._booking._booking_id))
            db.commit()
            # Check if booking has hours remaining
            if self._booking._remaining_credits == 0:
                print("--- Booking has been completed. Booking and all corresponding lessons will be deleted. ---")
                dbcursor.execute("DELETE FROM Bookings WHERE booking_id = (%s)", (self._booking._booking_id,))
                dbcursor.execute("DELETE FROM Lessons WHERE booking_id = (%s)", (self._booking._booking_id,))
                db.commit()
            helpers.close_db_connection(db, dbcursor)
            print("--- Lesson completed. ---")







## TO DO
""" class Subject:
    def __init__(self, level):
        self.level = level
        self.invis = False """

## TO DO
""" class Level(enum):
    HL = enum.auto()
    SL = enum.auto() """