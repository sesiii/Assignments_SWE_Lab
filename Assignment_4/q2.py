import numpy as np

# Specify the file
csv_file_path = 'book1.csv'

# Load the second column from the CSV file into a numpy array, skipping the first row
numeric_data = np.loadtxt(csv_file_path, delimiter='\t', usecols=1, skiprows=1)

# Create a sorted version of the array without modifying the original data
sorted_numeric_data = np.sort(numeric_data)

# Display the sorted data
print("Sorted data:\n", sorted_numeric_data)