/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Circle.cpp
 * Author: dell
 * 
 * Created on December 5, 2017, 5:28 AM
 */
#include <iostream>
#include <cmath>
#include "easygl.h"
#include "Circle.h"
using namespace std;

//Constructor
//store center and radius of a circle
Circle::Circle(string _name, string _colour, float _xcen, float _ycen, 
        float _radius) : Shape (_name, _colour, _xcen, _ycen){
    
    center.x = _xcen;
    center.y = _ycen;
    radius = _radius;   
}

Circle::~Circle(){
    // No dynamic memory to delete
}

void Circle::print() const{
    Shape::print();
    cout << "circle radius: " << radius <<endl;
}

void Circle::scale(float scaleFac){    
    radius *= scaleFac;
}

float Circle::computeArea() const{
    //area = pi*(radius^2)
    const double pi= acos(-1);
    
    float area;
    area = pi*radius*radius;
    
    return (area);   
}

float Circle::computePerimeter() const{
    //perimeter = 2*pi*radius
    float perimeter = 0;
    const double pi = acos(-1);
    
    perimeter = 2*pi*radius;
    
    return (perimeter);   
}

void Circle::draw(easygl* window) const{
    
    window->gl_setcolor(getColour());
    window->gl_fillarc(center.x,center.y,radius,0,360);
}

bool Circle::pointInside(float x, float y) const{
    
    t_point click;
    click.x = x -center.x;
    click.y = y-center.y;
    
    float distance = sqrt(click.x*click.x + click.y*click.y);
    //distance represent the distance between a point and the center
    //if distance is smaller than radius, this point lies inside the circle
    if(distance <=radius) return (true);
    else return(false);   
}





