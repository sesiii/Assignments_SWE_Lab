import numpy as np

# The file variable
csv_file = 'book1.csv'

# Importing the of the 2nd column, i.e the numbers into a numpy 1D- array 
# Skipping column 1 and row 1 of column 2 to access the require data  
data = np.loadtxt(csv_file, delimiter = '\t', usecols = 1, skiprows=1)

# Maximum element
maximum = np.max(data)

# Minimum element
minimum = np.min(data)

# Printing the maximum and minimum elements
print("The maximum element is :- {}\nThe minimum element is :- {}".format(maximum, minimum))

