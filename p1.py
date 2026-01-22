#problerm 1
x1=8
x2=8.4
x3=3+1j
x4="sahil katara"
print("type of x1 is",type(x1))
print("type of x2 is",type(x2))
print("type of x3 is",type(x3))
print("type of x4 is",type(x4))

 #problem 2
print("")
print(5+2*3)
print((5+2)*3)
print(6%2)
print(2*3**2)
print(4-5+2*4/2)
print(-2**3)
print((-2)**3)
print(2**3**2)
print((2**3)**2)
print(6/2*3+4%2-2)

# #problem 3
import cmath

def solve_quadratic(a, b, c):
Calculate the discriminant     
discriminant = cmath.sqrt(b**2 - 4*a*c)
Calculate two solutions
sol1 = (-b + discriminant) / (2*a)
sol2 = (-b - discriminant) / (2*a)
return sol1, sol2

 # Example usage
a = float(input("Enter coefficient a: "))
b = float(input("Enter coefficient b: "))
c = float(input("Enter coefficient c: "))

solution1, solution2 = solve_quadratic(a, b, c)

print(f"The solutions are {solution1} and {solution2}")

#problem4
def calculate_simple_interest(principal, rate, time):
    simple_interest = (principal * rate * time) / 100
    return simple_interest


principal = float(input("Enter the principal amount: "))
rate = float(input("Enter the rate of interest per year: "))
time = float(input("Enter the time in years: "))

simple_interest = calculate_simple_interest(principal, rate, time)

print(f"The simple interest is: {simple_interest}")
