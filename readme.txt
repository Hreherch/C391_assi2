= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
= = = = = = = = = = = = = = =  README = = = = = = = = = = = = = = = = = = = = =
= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
Assignment:          1
Due Date:            October 31, 2016
Name 1:              Bennett Hreherchuk
Unix ID 1:           hreherch
Name 2:              Kieter Balisnomo 
Unix ID 2:           balisnom
Instructor:          Denilson Barbosa
Lab Section:         D03
Teaching Assistant:  Michael Strobl
= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
= = = Compilation & Execution Instructuions
= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

WARNING:
    Ensure our copy of sqlite3.c is contained within this .zip folder. q7 and
    q8 are not garunteed to work without it. 

To compile all q files type:
    make
    
To run q4:
    ./q4 x1, y1, x2, y2 class
    
    x1 is the minimum x value bounding the square
    y1 is the maximum y value bounding the square 
    x2 is the maximum x value bounding the square
    y2 is the minimum y value bounding the square
    class is a type of objects you want to see (i.e. "hotel")
    
To run q5:
    ./q5 L
    
    where L is a decimal/integer representing a side length one wants to check
    while comparing speeds of r-Trees relative to indexes.
    
To run q7:
    ./q7 x y
    
    where x and y are float or integer values depicting a representing a point
    you wish to check for the nearest neighbours of. 
    
To run q8:
    ./q8 x y k
    
    The same as q7, but this one returns the specified k nearest neighbours 
    instead of the first one.

    
= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
= = = File Information
= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

q0.txt
    contains SQL commands to create a database with the the tables poi and
    poi_tag. Also contains the commands in q1.txt to ease the creation of
    A2.db, the database we use for thsi project.
    
q1.txt 
    contains the SQL commands to create an rTree on the data given in the poi
    table (created in q0.txt).
    
q2.pdf
    A pdf file with a cartesian-grid representation of Q2's squares and a
    r-Tree of the same squares. 
    
q3.txt
    Contains SQL commands to list inner node MBRs. There is only one MBR node
    created. 
    
q4.c
    prints a list of objects of a certian class and within a containing square.
    
q5.c 
    prints the average query speed of r-Trees vs. indexes given a side length 
    of a square to randomly generate and query
    
q6.c 
    The results of running q5 with L = {25, 50, 75, 100, 125} and the 
    conclusion thereof
    
q7.c
    returns the nearest neighbour in the r-Tree to a given point
    
q8.c
    returns the k nearest neighbours of a given point
    
NearestNeighbour.c and NearestNeighbour.h
    Files to aid q7 and q8. These are what you should look at to see the implementation
    It generalizes the k-nearest neighbours so that q7 can call it with k=1.
