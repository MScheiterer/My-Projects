""" Contains global variables """

# Admin login
ADMIN = ADMIN_PASS = "admin"

# lists containing all active tutors/students
all_tutors: list = []
all_students: list = []

# list containing all subjects on offer
subjects: list = ["math", "physics", "computer science", "chemistry", "biology"]

# list containing all packages on offer
packages: list = ["5", "10", "20"]

# current user id, -1 considered invalid
user_id: int = -1