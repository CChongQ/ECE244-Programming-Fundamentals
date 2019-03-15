/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Polygon.h
 * Author: dell
 *
 * Created on December 5, 2017, 5:28 AM
 */

#ifndef POLYGON_H
#define POLYGON_H
#include "Shape.h"
#include "easygl.h"

class Polygon : public Shape {
private:
    int points;
    t_point relVertex[100];
    
    // Private helper function.
     t_point getVecBetweenPoints (t_point start, t_point end) const;
    
public:
    Polygon(string _name, string _colour,float _xcen, float _ycen,int _points,
            float _xcoords[100],float _ycoords[100]);
    virtual ~Polygon();
  
   virtual void print () const;
   virtual void scale (float scaleFac);
   virtual float computeArea () const;
   virtual float computePerimeter () const;
   virtual void draw (easygl* window) const;
   virtual bool pointInside (float x, float y) const;

};

#endif /* POLYGON_H */

