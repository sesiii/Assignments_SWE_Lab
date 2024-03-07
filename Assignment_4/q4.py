import numpy as np

# Define the list of CSV files
csv_files = ['book1.csv', 'book2.csv', 'book3.csv']

# Initialize an empty list to store the data from each file
data_list = []

# Loop over each file in the list
for file in csv_files:
    # Load the second column from the CSV file into a numpy array, skipping the first row
    data_array = np.genfromtxt(file, delimiter='\t', usecols=1, skip_header=1)

    # Add the numpy array to the list
    data_list.append(data_array)

# Calculate the mean of each numpy array in the list using a for loop
mean_values = []
for array in data_list:
    mean_values.append(np.mean(array))

# Print the mean values
print("Mean values of all arrays:", mean_values)