/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Rectangle.cpp
 * Author: dell
 * 
 * Created on December 5, 2017, 3:54 AM
 */
#include <iostream>
#include <cmath>
#include "easygl.h"
#include "Rectangle.h"
using namespace std;


//Constructor.Store the left upper point and right bottom point
Rectangle::Rectangle(string _name, string _colour,
        float _xcoords[], float _ycoords[],float _xcen, float _ycen)
          :Shape(_name,_colour,_xcen,_ycen){
    
    for(int i=0; i<2 ; i++){
        opposedVertex[i].x = _xcoords[i];
        opposedVertex[i].y = _ycoords[i];
    }
    
    
}
Rectangle::~Rectangle(){
    // No dynamic memory to delete
}

void Rectangle::print() const{
    Shape::print();
    float height = getheight();
    float width = getwidth();
    cout << "rectangle";
    cout << " width: " << width << " height: " << height<<endl;  
    
}

void Rectangle::scale(float scaleFac){
    //update new height and width, then compute new corner points 
   float newheight = getheight()*scaleFac;
   float newwidth = getwidth()*scaleFac;
     
        opposedVertex[0].x = getXcen() - newwidth/2;
        opposedVertex[0].y =  getYcen() + newheight/2;
        opposedVertex[1].x =  getXcen() + newwidth/2;
        opposedVertex[1].y =  getYcen() - newheight/2;
        
}

float Rectangle::computeArea() const{
    //area = width*height
    float height = getheight();
    float width = getwidth();
    
    float area ;
     area= height*width;
    return area;   
}

float Rectangle::computePerimeter() const{
    //perimeter = 2*(height + width)
    float perimeter = 0;
    float height = getheight();
    float width = getwidth();
    
    perimeter = 2*height+2*width;
    return (perimeter);
}



void Rectangle::draw(easygl* window) const{
      
    window->gl_setcolor(getColour());
    window->gl_fillrect(opposedVertex[0].x,opposedVertex[0].y,opposedVertex[1].x,opposedVertex[1].y);
}

bool Rectangle::pointInside(float x, float y) const{
    //points inside a width*height rectangle including those on the boundaries
    bool result = false;
    if( (x >= opposedVertex[0].x) && (x <= opposedVertex[1].x) ){
        if ( (y <= opposedVertex[0].y) && (y >= opposedVertex[1].y)){
            result = true;
        }
    }
    return (result);     
}


//Below are two helper function to get height and width of a rectangle 
float Rectangle::getwidth() const{
     float width = opposedVertex[1].x - opposedVertex[0].x;
     return(width);
}

float Rectangle::getheight() const{
     float height = opposedVertex[0].y - opposedVertex[1].y;
     return (height);  
}