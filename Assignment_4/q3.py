import numpy as np

# Define the path to the CSV file
file_path = 'book1.csv'

# Load the second column from the CSV file into a numpy array
# Skip the first row and the first column
dataset = np.loadtxt(file_path, delimiter='\t', usecols=1, skiprows=1)

# Create a sorted copy of the array
# The original array remains unmodified
sorted_dataset = np.sort(dataset)

# Reverse the sorted array to get it in descending order
desc_sorted_dataset = sorted_dataset[::-1]

# Print the sorted and reversed array
print("Data sorted in descending order:\n", desc_sorted_dataset)