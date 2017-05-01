Nikki Bregman

HOW TO RUN:
In the command line: navigate to the correct to-block directory
Enter: g++ -o main main.cpp `pkg-config opencv --cflags --libs`
Enter: ./main
Answer the prompts

input: filename of picture file
output: 3 .txt files and an image

This program takes an image and turns it into "blocks" by simplifying it into a grid of 23x14 to fit on the Gem board.  It outputs red.txt, green.txt, and blue.txt.  Each file has 298 comma seperated integers between 0 and 255.  These lists are used in the gemDisplay project to display the original image on the Gem hardware.

The build command is complex because of the use of openCV in this project.

Note that the filename of the picture is assumed to be in the images folder.

Learn more about the Gem at nbregman17.github.io
