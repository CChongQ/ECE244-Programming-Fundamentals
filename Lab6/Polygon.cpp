/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Polygon.cpp
 * Author: dell
 * 
 * Created on December 5, 2017, 5:28 AM
 */
#include <iostream>
#include <cmath>
#include "easygl.h"
#include "Polygon.h"
using namespace std;

// Constructor. First set up base class (Shape), then store the 
// vertices, which are nPoint (x,y) points giving offsets from the Shape center 
// to each polygon vertex.
Polygon::Polygon(string _name, string _colour, float _xcen, float _ycen, 
             int _points, float _xcoords[100], float _ycoords[100]) : Shape(_name,_colour,_xcen,_ycen){
    points = _points;
   for (int i=0; i< _points; i++){
       relVertex[i].x= _xcoords[i];
       relVertex[i].y = _ycoords[i];     
   }   
}

Polygon::~Polygon(){
   // No dynamic memory to delete
}

void Polygon::print() const{
    Shape::print();
    cout<<"polygon ";
    for (int i = 0; i< points;i++){
        cout << " (" << getXcen()+relVertex[i].x <<"," 
                << getYcen()+relVertex[i].y << ")";
    }
    cout <<endl;
    
}

void Polygon::scale(float scaleFac){
   for (int i = 0; i < points; i++) {
      relVertex[i].x *= scaleFac;
      relVertex[i].y *= scaleFac;
   }
}

float Polygon::computeArea() const{
    //area = 0.5*[(X1Y2-X2Y1)+(X2Y3-X3Y2)+....(Xn-1*Yn-Xn*Yn-1)+(Xn*Y1-YnX1)]
    float area = 0;
    int j=points-1; //last vertex is the 'previous' one of the first vertex
    
    for(int i = 0; i<points; i++){ 
        area = area +  (relVertex[j].x+relVertex[i].x)*(relVertex[j].y-relVertex[i].y);
        j=i;
    }
  
    area = area/2;
    return area;   
}

float Polygon::computePerimeter() const{
    float perimeter = 0;
    float sideLength=0;
    int endIndex;
    t_point dist;
    
    for(int i=0; i< points ; i++){
        endIndex = (i+1)%points;
        dist = getVecBetweenPoints (relVertex[i], relVertex[endIndex]);
         sideLength = sqrt (dist.x * dist.x + dist.y * dist.y); //distance = sqrt(x^2+y^2)
         perimeter += sideLength;       
    }
    
    return perimeter;   
}

void Polygon::draw(easygl* window) const{
    
   t_point coords[points];  // This data type is in easygl_constants.h
   for (int i = 0; i < points; i++) {
      coords[i].x = getXcen() + relVertex[i].x;
      coords[i].y = getYcen() + relVertex[i].y;
   }
   window->gl_setcolor(getColour());
   window->gl_fillpoly(coords, points);
}

bool Polygon::pointInside(float x, float y) const{
  
    //All vertices are relative to the polygon center
    //click point is an offset from polygon center
    t_point click;
   click.x = x - getXcen();
   click.y = y - getYcen();
   
   t_point vecOfSide;
   float distanceAlongVector, yDistance;
   int endIndex;
   int sidesToLeft = 0;
   
   //logic here is similar to the triangular part
   //the only difference is that istart should iterate "points" times
   for (int istart = 0; istart < points; istart++) {
      endIndex = (istart + 1) % points; // Next vertex after istart
      vecOfSide = getVecBetweenPoints (relVertex[istart], relVertex[endIndex]);
      yDistance = (click.y - relVertex[istart].y);
      if (vecOfSide.y != 0) {
          distanceAlongVector = yDistance / vecOfSide.y;
      }
      else if (yDistance == 0) {
          distanceAlongVector = 0;
      }
      else {
          distanceAlongVector = 1e10; // Really infinity, but this is big enough
      }
      
      if (distanceAlongVector >= 0 && distanceAlongVector < 1) {
         float xIntersection = relVertex[istart].x + vecOfSide.x * distanceAlongVector;
         if (xIntersection <= click.x ) 
             sidesToLeft++;
      }
   } 
   
   return (sidesToLeft == 1);
}

//This is a helper function to return a vector between two points
t_point Polygon::getVecBetweenPoints (t_point start, t_point end) const {
   t_point vec;
   vec.x = end.x - start.x;
   vec.y = end.y - start.y;
   return (vec);
}


