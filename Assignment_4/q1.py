import numpy as np

# Define the path to the CSV file
file_path = 'book1.csv'

# Load the second column from the CSV file into a numpy array
# Skip the first row and the first column
numbers = np.loadtxt(file_path, delimiter='\t', usecols=1, skiprows=1)

# Find the highest value
max_value = np.amax(numbers)

# Find the lowest value
min_value = np.amin(numbers)

# Output the highest and lowest values
print(f"Maximum value: {max_value}\nMinimum value: {min_value}")