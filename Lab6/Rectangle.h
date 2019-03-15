/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Rectangle.h
 * Author: dell
 *
 * Created on December 5, 2017, 3:54 AM
 */

#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Shape.h"
#include "easygl.h"


class Rectangle : public Shape{
    private:
        t_point opposedVertex[2];//two opposite points along diagonal 
        
        //private helper function
        float getheight() const;
        float getwidth() const;
    public:
        Rectangle(string _name, string _colour, float _xcoords[2], float _ycoords[2],float _xcen,float _ycen);
        virtual ~Rectangle();
        
         virtual void print () const;
         virtual void scale (float scaleFac);
         virtual float computeArea () const;
         virtual float computePerimeter () const;
         virtual void draw (easygl* window) const;
         virtual bool pointInside (float x, float y) const;           

};

#endif /* RECTANGLE_H */

