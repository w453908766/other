from math import *
acc=4
wid=4
theta00=0
axis=6
def theta0(ax):
    return theta00+2*ax*PI/axis

def Ln(n):
    return n*acc

def thetan(n):
    return sqrt(2*Ln(n)+theta00*theta00)

def thetanax(n,ax):
    return thetan(n)+theta0(ax)

def xnax(n,ax):
    theta=thetanax(n,ax)
    return theta*cos(theta)

def ynax(n,ax):
    theta=thetanax(n,ax)
    return theta*sin(theta)

bits=[[0,1,0,1,0,1,0,1,1,0,1,0,1,0,1,0,0,1,0,1,0],
      [1,0,1,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0],
      [0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,1],
      [0,1,0,1,0,1,0,0,0,1,0,1,1,0,0,1,0,1,1,0,1],
      [1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1],
      [1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0]]
