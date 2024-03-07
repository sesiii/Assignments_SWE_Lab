def greet(name):
    print(f"Hello, {name}!")

def add_numbers(a, b):
    return a + b

def main():
    name = input("Enter your name: ")
    greet(name)
    
    num1 = int(input("Enter the first number: "))
    num2 = int(input("Enter the second number: "))
    result = add_numbers(num1, num2)
    print(f"The sum of {num1} and {num2} is {result}.")

if __name__ == "__main__":
    main()