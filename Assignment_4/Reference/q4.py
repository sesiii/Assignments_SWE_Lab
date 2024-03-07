import numpy as np

# The list of all file names
csv_file = ['book1.csv', 'book2.csv', 'book3.csv']

# List to store the numpy arrays 
all_data = []

# Iterating through all the files
for x in csv_file:
    # Importing the of the 2nd column, i.e the numbers into a numpy 1D- array 
    # Skipping column 1 and row 1 of column 2 to access the require data  
    data = np.loadtxt(x, delimiter='\t', usecols= 1, skiprows= 1)

    # Appending the numpy array into the (global) list
    all_data.append(data)

# Creating a list of means for each numpy array in all_data 
mean = [np.mean(np.array(x)) for x in all_data]

# Printing the means
print("The mean of all arrays is:-", mean, sep= ' ')
