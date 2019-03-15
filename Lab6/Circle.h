/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Circle.h
 * Author: dell
 *
 * Created on December 5, 2017, 5:28 AM
 */

#ifndef CIRCLE_H
#define CIRCLE_H

#include "Shape.h"
#include "easygl.h"

class Circle : public Shape {
private:
       t_point center;
       float radius;
        
public:
    Circle(string _name, string _colour, float _xcen,float _ycen,float _radius);
    
    virtual ~Circle();
    
    
    virtual void print () const;
    virtual void scale (float scaleFac);
    virtual float computeArea () const;
    virtual float computePerimeter () const;
    virtual void draw (easygl* window) const;
    virtual bool pointInside (float x, float y) const;
            
};

#endif /* CIRCLE_H */

