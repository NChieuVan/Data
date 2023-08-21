import pgzrun
import pygame

WIDTH = 800
HEIGHT =600

ship = Actor('phithuyen.jpg')

ship.x= 370
ship.y= 70

def draw():
    ship.draw()
    
pgzrun.go()

