
from asyncio import Event  # Importing Event from asyncio for handling events in asynchronous IO
import re  # Importing re for regular expression operations
import tkinter as tk  # Importing tkinter for GUI operations
from tkinter import ttk  # Importing ttk from tkinter for themed widgets
from tkinter import messagebox  # Importing messagebox from tkinter for displaying message boxes
from tkinter import simpledialog  # Importing simpledialog from tkinter for simple dialog boxes
import bcrypt  # Importing bcrypt for password hashing
import csv  # Importing csv for reading and writing CSV files
import secrets  # Importing secrets for generating cryptographically strong random numbers
import string  # Importing string for string operations

class Person:

    # Constructor for the Person class
    def __init__(self, username, email, password):
        self.username = username  # Assigning the username
        self.email = email  # Assigning the email
        self.password = password  # Assigning the password

    # Method to hash a password
    def hash_password(self, password):
        # Hashing the password with bcrypt and returning the hashed password
        return bcrypt.hashpw(password.encode('utf-8'), bcrypt.gensalt()).decode('utf-8')

    # Method to check if a password matches the hashed password
    def check_password(self, password):
        # Checking the password with bcrypt and returning the result
        return bcrypt.checkpw(password.encode('utf-8'), self.password.encode('utf-8'))

    # Method to convert the Person object to a dictionary
    def to_dict(self):
        # Returning a dictionary with the username, email, and password
        return {
            'username': self.username,
            'email': self.email,
            'password': self.password
        }

# The Student class inherits from the Person class
class Student(Person):
    # Constructor for the Student class
    def __init__(self, username, email, password, student_id):
        # Call the constructor of the Person class
        super().__init__(username, email, password)
        # Assign the student_id to the Student object
        self.student_id = student_id

# The Teacher class inherits from the Person class
class Teacher(Person):
    # Constructor for the Teacher class
    def __init__(self, username, email, password, teacher_id):
        # Call the constructor of the Person class
        super().__init__(username, email, password)
        # Assign the teacher_id to the Teacher object
        self.teacher_id = teacher_id

    # Method to convert the Teacher object to a dictionary
    def to_dict(self):
        # Call the to_dict method of the Person class
        data = super().to_dict()
        # Add the teacher_id to the dictionary
        data['teacher_id'] = self.teacher_id
        # Return the dictionary
        return data

# The UGStudent class inherits from the Student class
class UGStudent(Student):
    # Constructor for the UGStudent class
    def __init__(self, username, email, password, student_id, year_of_study):
        # Call the constructor of the Student class
        super().__init__(username, email, password, student_id)
        # Assign the year_of_study to the UGStudent object
        self.year_of_study = year_of_study

    # Method to convert the UGStudent object to a dictionary
    def to_dict(self):
        # Call the to_dict method of the Student class
        data = super().to_dict()
        # Add the year_of_study to the dictionary
        data['year_of_study'] = self.year_of_study
        # Return the dictionary
        return data

# The PGStudent class inherits from the Student class
class PGStudent(Student):
    # Constructor for the PGStudent class
    def __init__(self, username, email, password, student_id, program):
        # Call the constructor of the Student class
        super().__init__(username, email, password, student_id)
        # Assign the program to the PGStudent object
        self.program = program

    # Method to convert the PGStudent object to a dictionary
    def to_dict(self):
        # Call the to_dict method of the Student class
        data = super().to_dict()
        # Add the program to the dictionary
        data['program'] = self.program
        # Return the dictionary
        return data

# Function to validate a password
def is_valid_password(password):
    # Check if the length of the password is between 8 and 12 characters
    if len(password) < 8 or len(password) > 12:
        return False  # If not, return False
    # Check if the password contains a lowercase letter
    if not re.search('[a-z]', password):
        return False  # If not, return False
    # Check if the password contains an uppercase letter
    if not re.search('[A-Z]', password):
        return False  # If not, return False
    # Check if the password contains a number
    if not re.search('[0-9]', password):
        return False  # If not, return False
    # Check if the password contains a special character from the list
    if not re.search('[!@#$%&*]', password):
        return False  # If not, return False
    # Check if the password contains a blank space
    if ' ' in password:
        return False  # If it does, return False
    # If all checks pass, return True
    return True

# Function to load users from a CSV file
def load_users():
    try:
        # Try to open the CSV file
        with open('users.csv', 'r') as f:
            # Create a DictReader object
            reader = csv.DictReader(f)
            # Convert the reader object to a list and assign it to users
            users = list(reader)
    except FileNotFoundError:
        # If the file is not found, assign an empty list to users
        users = []
    # Return the list of users
    return users

# Function to generate a password
def generate_password(length):
    # Check if the length is between 8 and 12
    if length < 8 or length > 12:
        return None  # If not, return None

    # Define the alphabet for each requirement
    lowercase = string.ascii_lowercase  # All lowercase letters
    uppercase = string.ascii_uppercase  # All uppercase letters
    digits = string.digits  # All digits
    special = '!@#$%&*'  # All special characters

    # Ensure the password contains at least one character of each type
    password = [
        secrets.choice(lowercase),  # Choose a random lowercase letter
        secrets.choice(uppercase),  # Choose a random uppercase letter
        secrets.choice(digits),  # Choose a random digit
        secrets.choice(special)  # Choose a random special character
    ]

    # Fill the rest of the password length with random characters from the alphabet
    all_characters = lowercase + uppercase + digits + special  # All possible characters
    for i in range(length - 4):  # Subtract 4 because we already added 4 characters
        password.append(secrets.choice(all_characters))  # Add a random character

    # Shuffle the list to ensure the required characters aren't always at the start
    secrets.SystemRandom().shuffle(password)

    # Convert the list of characters into a string
    password = ''.join(password)

    # Return the generated password
    return password

# Function to validate an email
def is_valid_email(email):
    # Define the regular expression for a valid email
    email_regex = r'\b[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Z|a-z]{2,}\b'
    # Return True if the email matches the regex, False otherwise
    return re.match(email_regex, email) is not None

# Function to check a password against a hashed password
def check_password(hashed_password, user_password):
    # Use bcrypt to check if the hashed password matches the user password
    return bcrypt.checkpw(user_password.encode('utf-8'), hashed_password)

# Function to save users to a CSV file
def save_users(users):
    # Open the CSV file in write mode
    with open('users.csv', 'w', newline='') as file:
        # Define the fieldnames for the CSV file
        fieldnames = ['email', 'password', 'username', 'user_type', 'student_type']
        # Create a DictWriter object
        writer = csv.DictWriter(file, fieldnames=fieldnames)

        # Write the header to the CSV file
        writer.writeheader()
        # Loop through the users
        for user in users:
            # If 'student_type' is not in the user dict, set it to an empty string
            user.setdefault('student_type', '')
            # Write the user to the CSV file
            writer.writerow(user)

# Function to hash a password
def hash_password(password):
    # Generate a salt using bcrypt
    salt = bcrypt.gensalt()
    # Hash the password using the salt and return it
    return bcrypt.hashpw(password.encode('utf-8'), salt)

# Function to register a new user
def register(email, password, username, user_type, student_type=None):
    # Initialize the list of users
    users = []

    # Try to read the existing data
    try:
        # Open the CSV file in read mode
        with open('users.csv', 'r') as file:
            # Create a DictReader object
            reader = csv.DictReader(file)
            # Convert the reader object to a list and assign it to users
            users = list(reader)
    except FileNotFoundError:
        pass  # Do nothing if the file doesn't exist

    # Create a Person object
    person = Person(username, email, password)
    # Hash the password
    hashed_password = person.hash_password(password)

    # Create a dictionary for the new user
    user = {'email': email, 'password': hashed_password, 'username': username, 'user_type': user_type}
    # If the user is a student, add the student type to the dictionary
    if user_type == 'Student':
        user['student_type'] = student_type
    # Add the new user to the list of users
    users.append(user)

    # Save the updated list of users to the CSV file
    save_users(users)

    # Return a success message
    return "Registration successful"

# Function to check if an email exists in the user database
def email_exists(email):
    users = load_users()  # Load the existing users from the database
    for user in users:
        if user['email'] == email:  # If the email matches with any user's email in the database
            return True  # Return True indicating the email exists
    return False  # If no match is found after checking all users, return False indicating the email does not exist

# Function to retrieve a user's password based on their email
def get_user_password(email):
    # Open the 'users.csv' file in read mode
    with open('users.csv', 'r') as file:
        # Create a CSV reader for the file
        reader = csv.reader(file)
        # Convert the reader object to a list and assign it to data
        data = list(reader)

    # Iterate over each row in the data
    for row in data:
        # If the first element in the row (the email) matches the given email
        if row[0] == email:
            return row[1]  # Return the second element in the row (the password)

    # If no matching email is found in the data, return None
    return None

# Function to update a user's email
def update_user_email(current_email, new_email):
    # Open the 'users.csv' file in read mode
    with open('users.csv', 'r') as file:
        # Create a CSV reader for the file
        reader = csv.reader(file)
        # Convert the reader object to a list and assign it to data
        data = list(reader)

    # Iterate over each row in the data
    for row in data:
        # If the first element in the row (the email) matches the current email
        if row[0] == current_email:
            row[0] = new_email  # Update the email in the row to the new email
            break  # Exit the loop as we've found the user and updated the email
    else:
        # If no matching email is found in the data, return an error message
        return "User not found"

    # Open the 'users.csv' file in write mode
    with open('users.csv', 'w', newline='') as file:
        # Create a CSV writer for the file
        writer = csv.writer(file)
        # Write the updated data to the file
        writer.writerows(data)

    # Return a success message
    return "Email updated successfully"

# Function to update a user's password
def update_user_password(current_email, new_password):
    # Open the 'users.csv' file in read mode
    with open('users.csv', 'r') as file:
        # Create a CSV reader for the file
        reader = csv.reader(file)
        # Convert the reader object to a list and assign it to data
        data = list(reader)

    # Hash the new password using bcrypt
    new_hashed_password = bcrypt.hashpw(new_password.encode('utf-8'), bcrypt.gensalt())

    # Iterate over each row in the data
    for row in data:
        # If the first element in the row (the email) matches the current email
        if row[0] == current_email:
            # Update the password in the row to the hashed new password
            row[1] = new_hashed_password.decode('utf-8')
            break  # Exit the loop as we've found the user and updated the password
    else:
        # If no matching email is found in the data, return an error message
        return "User not found or incorrect password"

    # Open the 'users.csv' file in write mode
    with open('users.csv', 'w', newline='') as file:
        # Create a CSV writer for the file
        writer = csv.writer(file)
        # Write the updated data to the file
        writer.writerows(data)

    # Return a success message
    return "Password updated successfully"

# Function to update a user's username
def update_user_username(current_email, new_username):
    # Open the 'users.csv' file in read mode
    with open('users.csv', 'r') as file:
        # Create a CSV reader for the file
        reader = csv.reader(file)
        # Convert the reader object to a list and assign it to data
        data = list(reader)

    # Iterate over each row in the data
    for row in data:
        # If the first element in the row (the email) matches the current email
        if row[0] == current_email:
            row[2] = new_username  # Update the username in the row to the new username
            break  # Exit the loop as we've found the user and updated the username
    else:
        # If no matching email is found in the data, return an error message
        return "User not found"

    # Open the 'users.csv' file in write mode
    with open('users.csv', 'w', newline='') as file:
        # Create a CSV writer for the file
        writer = csv.writer(file)
        # Write the updated data to the file
        writer.writerows(data)

    # Return a success message
    return "Username updated successfully"

# Function to create a user menu GUI
def user_menu():
    # Function to open the update user GUI
    def open_update_user():
        root.destroy()  # Destroy the current GUI
        update_user_gui()  # Open the update user GUI

    # Function to open the deregister GUI
    def open_deregister():
        root.destroy()  # Destroy the current GUI
        deregister_gui()  # Open the deregister GUI

    # Create a new Tkinter window
    root = tk.Tk()
    root.title("User Menu")  # Set the title of the window
    bg = '#2d2d2d'  # Dark grey
    fg = '#ffffff'  # White
    button_color = '#5f5f5f'  # Light grey
    root.configure(bg=bg)  # Set the background color of the window

    # Create a label
    label = tk.Label(root, text="Welcome to the User Menu", font=("Arial", 14), bg=bg, fg=fg)
    label.grid(column=0, row=0, padx=10, pady=10)  # Add the label to the window

    # Create an "Update User" button
    update_user_button = tk.Button(root, text="Update User", command=open_update_user, font=("Arial", 14), bg=button_color, fg=fg)
    update_user_button.grid(column=0, row=1, padx=10, pady=10)  # Add the button to the window

    # Create a "Deregister" button
    deregister_button = tk.Button(root, text="Deregister", command=open_deregister, font=("Arial", 14), bg=button_color, fg=fg)
    deregister_button.grid(column=0, row=2, padx=10, pady=10)  # Add the button to the window

    root.mainloop()  # Start the Tkinter event loop

# Dictionary to keep track of unsuccessful login attempts
unsuccessful_attempts = {}

# Boolean to keep track of whether a user is signed in
is_signed_in = False  

# Variable to store the type of the current user
user_type = None

# Function to login a user
def login(identifier, password):
    # Load the existing users data
    users = load_users()

    # Iterate over the users to find the user with the given identifier
    for user in users:
        # Check if the user's email or username matches the identifier
        if ('email' in user and user['email'] == identifier) or ('username' in user and user['username'] == identifier):
            # Create a new Person instance with the identifier and password
            person = Person(identifier, user['email'], user['password'])
            # Check if the provided password is correct
            if person.check_password(password):
                # If the password is correct, reset the unsuccessful attempts count and return a success message
                unsuccessful_attempts[identifier] = 0
                return "Sign-in successful"
            else:
                # If the password is incorrect, increment the unsuccessful attempts count
                unsuccessful_attempts[identifier] = unsuccessful_attempts.get(identifier, 0) + 1
                # If there were 3 unsuccessful attempts, remove the user data and reset the unsuccessful attempts count, then return a message
                if unsuccessful_attempts[identifier] >= 3:
                    message = "User data removed after 3 failed attempts"
                    deregister('username', identifier)
                    unsuccessful_attempts[identifier] = 0
                    return message
                # If there were less than 3 unsuccessful attempts, return a message about the incorrect password
                return "Incorrect password"
    
    # If no user with the given identifier was found, print a message and return a failure message
    print(f"User {identifier} not found")
    return "User not found"

# Function to deregister a user
def deregister(identifier_type, identifier):
    # Load the existing users data
    users = load_users()
    user_found = False  # Flag to check if user is found

    # Iterate over the users to find the user with the given identifier
    for user in users.copy():  # Using copy to avoid modifying list during iteration
        if user[identifier_type] == identifier:  # Check if the user's identifier matches the given identifier
            users.remove(user)  # If found, remove the user from the users list
            user_found = True  # Set the flag to True

    # If the user was found and removed
    if user_found:
        save_users(users)  # Save the updated users data
        print(f"User with {identifier_type}: {identifier} deregistered successfully")  # Print a success message
        messagebox.showinfo("Success", "Deregistration was successful")  # Show a success message box
    else:  # If the user was not found
        print(f"User with {identifier_type}: {identifier} not found")  # Print an error message
        messagebox.showerror("Error", "User not found")  # Show an error message box

def register_gui():
    root = tk.Tk()
    root.title("User Registration")
    bg = '#2d2d2d'  # Dark grey
    fg = '#ffffff'  # White
    button_color = '#5f5f5f'  # Light grey
    root.configure(bg=bg)  # Set the background color of the window

    def suggest_password():
        suggested_password = generate_password(10)
        use_suggested = messagebox.askyesno("Suggested Password", f"Do you want to use this suggested password: {suggested_password}?")
        if use_suggested:
            password_entry.delete(0, tk.END)
            password_entry.insert(0, suggested_password)

    def submit():
        email = email_entry.get()
        password = password_entry.get()
        username = username_entry.get()
        user_type = user_type_var.get()
        student_type = student_type_var.get()

        if not is_valid_email(email):
            messagebox.showerror("Error", "Invalid email. Please enter a valid email.")
            return

        if email_exists(email):
            messagebox.showerror("Error", "Email already exists")
        else:
            # Pass student_type to the register function
            result = register(email, password, username, user_type, student_type)
            messagebox.showinfo("Registration", result)
            root.destroy()
            main_menu()

    def go_to_main_menu():
        root.destroy()
        main_menu()

    def user_type_changed(*args):
        if user_type_var.get() == 'Student':
            student_type_label.grid(column=0, row=5, padx=10, pady=10)  # Changed row to 5
            student_type_dropdown.grid(column=1, row=5, padx=10, pady=10)  # Changed row to 5
        else:
            student_type_label.grid_remove()
            student_type_dropdown.grid_remove()

    
    username_label = tk.Label(root, text="Username", font=("Arial", 14), bg=bg, fg=fg)
    username_label.grid(column=0, row=0, padx=10, pady=10)

    username_entry = tk.Entry(root, font=("Arial", 14), bg=bg, fg=fg)
    username_entry.grid(column=1, row=0, padx=10, pady=10)

    email_label = tk.Label(root, text="Email", font=("Arial", 14), bg=bg, fg=fg)
    email_label.grid(column=0, row=1, padx=10, pady=10)

    email_entry = tk.Entry(root, font=("Arial", 14), bg=bg, fg=fg)
    email_entry.grid(column=1, row=1, padx=10, pady=10)

    password_label = tk.Label(root, text="Password", font=("Arial", 14), bg=bg, fg=fg)
    password_label.grid(column=0, row=2, padx=10, pady=10)

    password_entry = tk.Entry(root, show="*", font=("Arial", 14), bg=bg, fg=fg)
    password_entry.grid(column=1, row=2, padx=10, pady=10)
    # Create a style object
    style = ttk.Style()

    # Configure the style
    style.configure('TButton', font=("Arial", 8), background=button_color, foreground=fg, borderwidth=1, relief="solid", bordercolor=button_color)

    # Create the button with the new style
    suggest_button = ttk.Button(root, text="Suggest Password", command=suggest_password, style='TButton')
    suggest_button.grid(column=1, row=3, padx=10, pady=10, sticky='e')  # 'e' for east or right alignment

    # Function to make the button blink
    def blink():
        current_color = suggest_button.cget("background")
        new_color = bg if current_color == button_color else button_color
        style.configure('TButton', background=new_color)
        root.after(1000, blink)  # Blink every 1000ms

        # Start the blinking
        blink()

    user_type_label = tk.Label(root, text="User Type", font=("Arial", 14), bg=bg, fg=fg)
    user_type_label.grid(column=0, row=4, padx=10, pady=10)

    user_type_var = tk.StringVar(root)
    user_type_var.trace('w', user_type_changed)
    user_type_dropdown = tk.OptionMenu(root, user_type_var, "", "Student", "Teacher")
    user_type_dropdown.grid(column=1, row=4, padx=10, pady=10)

    student_type_label = tk.Label(root, text="Student Type", font=("Arial", 14), bg=bg, fg=fg)
    student_type_label.grid(column=0, row=5, padx=10, pady=10)  # Removed width

    student_type_var = tk.StringVar(root)
    student_type_var.set("")  # default value

    student_type_dropdown = tk.OptionMenu(root, student_type_var, "", "UG", "PG")
    student_type_dropdown.grid(column=1, row=5, padx=10, pady=10)  # Removed width

    user_type_changed()  # Call the function to show/hide the student type dropdown

    submit_button = tk.Button(root, text="Sign up", command=submit, font=("Arial", 14), bg=button_color, fg=fg)
    submit_button.grid(column=0, row=6, columnspan=2, padx=10, pady=10)

    main_menu_button = tk.Button(root, text="Back to Main Menu", command=go_to_main_menu, font=("Arial", 14), bg=button_color, fg=fg)
    main_menu_button.grid(column=0, row=7, columnspan=2, padx=10, pady=10)
    
    # Start the tkinter event loop
    root.mainloop()
 
def signin_gui():
    # Function to handle the submit button click
    def submit():
        global is_signed_in  # Declare is_signed_in as global
        # Get the identifier and password from the entry fields
        identifier = identifier_entry.get()
        password = password_entry.get()
        # Call the login function with the entered identifier and password
        result = login(identifier, password)
        # Show a message box with the result of the login attempt
        messagebox.showinfo("Sign-in", result)
        # If the login was successful
        if result == "Sign-in successful":
            is_signed_in = True  # Update the global variable
            # Close the sign-in window and open the user menu
            root.destroy()
            user_menu()

    # Function to handle the main menu button click
    def go_to_main_menu():
        # Close the sign-in window and open the main menu
        root.destroy()
        main_menu()

    # Create a new tkinter window
    root = tk.Tk()
    # Set the title of the window
    root.title("Sign-in")
    # Define colors for the GUI
    bg = '#2d2d2d'  # Dark grey
    fg = '#ffffff'  # White
    button_color = '#5f5f5f'  # Light grey
    # Set the background color of the window
    root.configure(bg=bg)

    identifier_label = tk.Label(root, text="Username/Email", font=("Arial", 14), bg=bg, fg=fg)
    identifier_label.grid(column=0, row=0, padx=10, pady=10)

    identifier_entry = tk.Entry(root, font=("Arial", 14), bg=bg, fg=fg)
    identifier_entry.grid(column=1, row=0, padx=10, pady=10)

    password_label = tk.Label(root, text="Password", font=("Arial", 14), bg=bg, fg=fg)
    password_label.grid(column=0, row=1, padx=10, pady=10)

    password_entry = tk.Entry(root, show="*", font=("Arial", 14), bg=bg, fg=fg)
    password_entry.grid(column=1, row=1, padx=10, pady=10)

    submit_button = tk.Button(root, text="Sign-in", command=submit, font=("Arial", 14), bg=button_color, fg=fg)
    submit_button.grid(column=0, row=2, columnspan=2, padx=10, pady=10)

    main_menu_button = tk.Button(root, text="Back to Main Menu", command=go_to_main_menu, font=("Arial", 14), bg=button_color, fg=fg)
    main_menu_button.grid(column=0, row=3, columnspan=2, padx=10, pady=10)

    root.mainloop()

def update_user_gui():
    # Declare is_signed_in as global
    global is_signed_in

    # If the user is not signed in
    if not is_signed_in:
        # Show an error message
        messagebox.showinfo("Error", "You must be signed in to update user information.")
        return  # Exit the function

    # Create a new tkinter window
    root = tk.Tk()  
    # Set the title of the window
    root.title("Update User")

    # Define the font, colors for the GUI
    font = ("Helvetica", 14)
    bg = '#2d2d2d'  # Dark grey
    fg = '#ffffff'  # White
    button_color = '#5f5f5f'  # Light grey

    # Set the background color of the window
    root.configure(bg=bg)

    # Function to go back to the main menu
    def go_to_main_menu():
        # Close the current window
        root.destroy()
        # Open the main menu
        main_menu()  # Uncomment this line if you have a main_menu function

    # Function to handle the submit button click
    def submit():
        # Get the current email, field to update, and new value from the entry fields
        current_email = email_entry.get()
        field_to_update = field_var.get()
        new_value = new_value_entry.get()

        # Update the user information based on the field to update
        if field_to_update == "Email":
            update_user_email(current_email, new_value)
        elif field_to_update == "Password":
            update_user_password(current_email, new_value)
        elif field_to_update == "Username":
            update_user_username(current_email, new_value)

        # Show a message box indicating the user was updated successfully
        messagebox.showinfo("Update User", "User updated successfully. Returning to main menu.")
        # Close the current window
        root.destroy()        
        # Open the main menu
        main_menu()

    # Create and place the labels, entries, and buttons
    email_label = tk.Label(root, text="Current Email", font=font, bg=bg, fg=fg)
    email_label.grid(column=0, row=0, padx=10, pady=10)

    email_entry = tk.Entry(root, font=font, bg=bg, fg=fg)
    email_entry.grid(column=1, row=0, padx=10, pady=10)

    field_label = tk.Label(root, text="Field to update", font=font, bg=bg, fg=fg)
    field_label.grid(column=0, row=1, padx=10, pady=10)

    field_var = tk.StringVar()
    field_combobox = ttk.Combobox(root, textvariable=field_var, values=["Email", "Password", "Username"], font=font)
    field_combobox.grid(column=1, row=1, padx=10, pady=10)

    new_value_label = tk.Label(root, text="New Value", font=font, bg=bg, fg=fg)
    new_value_label.grid(column=0, row=2, padx=10, pady=10)

    new_value_entry = tk.Entry(root, font=font, bg=bg, fg=fg)
    new_value_entry.grid(column=1, row=2, padx=10, pady=10)

    submit_button = tk.Button(root, text="Update User", command=submit, font=font, bg=button_color, fg=fg)
    submit_button.grid(column=0, row=3, columnspan=2, padx=10, pady=10)

    main_menu_button = tk.Button(root, text="Back to Main Menu", command=go_to_main_menu, font=font, bg=button_color, fg=fg)
    main_menu_button.grid(column=0, row=4, columnspan=2, padx=10, pady=10)

    root.mainloop()

def deregister_gui():

    global is_signed_in

    if not is_signed_in:
        messagebox.showinfo("Error", "You must be signed in to deregister.")
        return
    

    # Create a new window
    root = tk.Tk()
    root.title("Deregister")
    bg = '#2d2d2d'  # Dark grey
    fg = '#ffffff'  # White
    button_color = '#5f5f5f'  # Light grey
    root.configure(bg=bg)  # Set the background color of the window

    def go_to_main_menu():
        root.destroy()
        main_menu()
    
    # Create a StringVar for the dropdown
    identifier_type = tk.StringVar()

    # Create a label for the dropdown
    dropdown_label = tk.Label(root, text="Identifier Type", font=("Arial", 14), bg=bg, fg=fg)
    dropdown_label.grid(column=0, row=0, padx=10, pady=10)

    # Create a dropdown menu
    dropdown = ttk.Combobox(root, textvariable=identifier_type, font=("Arial", 14))
    dropdown['values'] = ('username', 'email')
    dropdown.grid(column=1, row=0, padx=10, pady=10)

    # Create a StringVar for the entry field
    identifier = tk.StringVar()

    # Create a label for the entry field
    entry_label = tk.Label(root, text="Identifier", font=("Arial", 14), bg=bg, fg=fg)
    entry_label.grid(column=0, row=1, padx=10, pady=10)

    # Create an entry field
    entry = tk.Entry(root, textvariable=identifier, font=("Arial", 14), bg=bg, fg=fg)
    entry.grid(column=1, row=1, padx=10, pady=10)

    # Create a deregister button
    button = tk.Button(root, text="Deregister", command=lambda: (deregister(identifier_type.get(), identifier.get()), go_to_main_menu()), font=("Arial", 14), bg=button_color, fg=fg)
    button.grid(column=0, row=2, columnspan=2, padx=10, pady=10)  

    # Create a button to go back to the main menu
    main_menu_button = tk.Button(root, text="Back to Main Menu", command=go_to_main_menu, font=("Arial", 14), bg=button_color, fg=fg)
    main_menu_button.grid(column=0, row=3, columnspan=2, padx=10, pady=10)

    root.mainloop()
    
def main_menu():
    # Function to open the registration GUI
    def open_register():
        # Close the main menu
        root.destroy()
        # Open the registration GUI
        register_gui()
        
    def open_sign_in():
        root.destroy()
        signin_gui()

    root = tk.Tk()
    root.title("Main Menu")
    bg = '#2d2d2d'  # Dark grey
    fg = '#ffffff'  # White
    button_color = '#5f5f5f'  # Light grey
    root.configure(bg=bg)

    # Create a frame to hold the buttons
    frame = tk.Frame(root, bg=bg)
    frame.pack(fill=tk.BOTH, expand=True)

    # Add padding to the frame and space out the buttons
    frame.grid_columnconfigure(0, weight=1)
    frame.grid_rowconfigure([0, 1, 2, 3, 4], weight=1)

    welcome_label = tk.Label(frame, text="Welcome!", font=("Arial", 20), bg=bg, fg=fg)
    welcome_label.grid(column=0, row=0, padx=20, pady=20)

    sign_in_button = tk.Button(frame, text="Sign in", command=open_sign_in, font=("Arial", 14), bg=button_color, fg=fg)
    sign_in_button.grid(column=0, row=1, padx=20, pady=20)

    register_prompt_label = tk.Label(frame, text="Don't have an account?", font=("Arial", 14), bg=bg, fg=fg)
    register_prompt_label.grid(column=0, row=2, padx=20, pady=5)

    register_button = tk.Button(frame, text="Sign up", command=open_register, font=("Arial", 14), bg=button_color, fg=fg)
    register_button.grid(column=0, row=3, padx=20, pady=5)

    root.mainloop()

main_menu()