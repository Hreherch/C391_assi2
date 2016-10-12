# [(2,25),(5,23)]; [(3,20),(7,17)]; [(1,13),(4,15)]; [(1,3),(4,0)]; 
# [(6,24),(9,21)]; [(7,20),(9,15)]; [(6,8),(13,3)]; [(17,22),(20,9)]
# [(19,12),(24,9)]; [(19,8),(23,6)]; [(21,25),(26,21)];
# [(20,17),(30,15)]; [(28,16),(25,12)]; [(13,22),(17,19)]

import turtle
import random

def square ( turtle, topx, topy, botx, boty ):
    input();
    i = 16
    topx *= i
    topy *= i
    botx *= i
    boty *= i
    turtle.color( random.choice(["green", "blue", "red", "orange", "yellow", "black"]))
    turtle.penup()
    turtle.begin_fill()
    turtle.goto( topx, topy )
    turtle.pendown()
    turtle.goto( botx, topy )
    turtle.goto( botx, boty )
    turtle.goto( topx, boty )
    turtle.goto( topx, topy )
    turtle.end_fill()

def cartGrid( turtle ):
    i = 16
    top = 30
    turtle.penup()
    for x in range( 30 ):
        turtle.goto( x*i, 0 )
        turtle.pendown()
        turtle.goto( x*i, top*i )
        turtle.penup()
    for y in range( 30 ):
        turtle.goto( 0, y*i )
        turtle.pendown()
        turtle.goto( top*i, y*i )
        turtle.penup()

win = turtle.Screen()
turtt = turtle.Turtle()
turtt.speed( 0 )
cartGrid( turtt )
turtt.speed(1)
square( turtt, 2, 25, 5, 23 )
square( turtt, 3, 20, 7, 17 )
square( turtt, 1, 13, 4, 11 )
square( turtt, 1, 3, 4, 0 )
square( turtt, 6, 24, 9, 21 )
square( turtt, 7, 20, 9, 15 )
square( turtt, 6, 8, 13, 3 )
square( turtt, 17, 22, 20, 9 )
square( turtt, 19, 12, 24, 9 )
square( turtt, 19, 8, 23, 6 )
square( turtt, 21, 25, 26, 21 )
square( turtt, 20, 17, 30, 15 )
square( turtt, 25, 16, 28, 12 )
square( turtt, 13, 22, 17, 19 )
win.exitonclick()