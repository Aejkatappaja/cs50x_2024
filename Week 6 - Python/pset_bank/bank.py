from cs50 import get_string

greeting = get_string("Greeting: ").lower().strip()

if greeting.startswith('hello'):
    print("$0")
elif greeting.startswith('h'):
    print("$20")
else:
    print('$100')
