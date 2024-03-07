import numpy as np

# The file variable
csv_file = 'book1.csv'

# Importing the of the 2nd column, i.e the numbers into a numpy 1D- array 
# Skipping column 1 and row 1 of column 2 to access the require data  
data = np.loadtxt(csv_file, delimiter= '\t', usecols = 1, skiprows= 1)

# Sorting the array in ascending order
# We do not data.sort() so that the original data isn;t modified
sorted_data = np.sort(data)

# Printing the sorted data
print("The sorted data is :-\n", sorted_data )

