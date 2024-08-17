
import sys
import random
from pyfiglet import Figlet
from cs50 import get_string


def main():

    figlet = Figlet()
    available_fonts = figlet.getFonts()

    if len(sys.argv) == 1:
        font = random.choice(available_fonts)
    elif len(sys.argv) == 3 and sys.argv[1] in ['-f', '--font']:
        font = sys.argv[2]
        if font not in available_fonts:
            sys.exit("Error: Font not found.")
    else:
        sys.exit("Usage: python script.py [-f FONT_NAME]")

    text = get_string("Input: ")
    figlet.setFont(font=font)
    print(figlet.renderText(text))


if __name__ == "__main__":
    main()
