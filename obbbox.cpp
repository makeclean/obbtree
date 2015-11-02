#include "obbbox.hpp"
#include <iostream>

// default constructor
OBBBox::OBBBox(double centre[3], double widths[3], int boxid, OBBBox *parent) {
  set_centre(centre[0],centre[1],centre[2]);
  set_widths(widths[0],widths[1],widths[2]);
  set_parent(parent);
  set_boxid(boxid);
}

// empty constructor
OBBBox::OBBBox() {
}

// destructor
OBBBox::~OBBBox() {
}

// set the box id
void OBBBox::set_boxid(int boxid) {
  boxId = boxid;
}

// set the centre of the box
void OBBBox::set_centre(double x, double y , double z) {
  double box_centre[3] = {x,y,z};
  std::copy(box_centre,box_centre+3,boxCentre);
}

// set the widths of the box
void OBBBox::set_widths(double x_width, double y_width, double z_width) {
  double box_widths[3] = {x_width,y_width,z_width};
  std::copy(box_widths,box_widths+3,boxWidths);
}

// set the parent of the box
void OBBBox::set_parent(OBBBox *parent) {
  boxParent = parent;
}

// set the children of the box
void OBBBox::set_children(OBBBox *left_child, OBBBox *right_child) {
  leftChild = left_child;
  rightChild = right_child;
}

// return the box id
int OBBBox::get_boxid() {
  return boxId;
}

// return the box widths
double * OBBBox::get_widths() {
  return boxWidths;
}

// return the box centre
double * OBBBox::get_centre() {
  return boxCentre;
}

// return the parent 
OBBBox * OBBBox::get_parent() {
  return boxParent;
}

// point in box test
bool OBBBox::point_in_box(double x, double y, double z) {

  if( ( x < boxCentre[0]-boxWidths[0] ) || ( x > boxCentre[0]+boxWidths[0] ) )
    return false;
  else {
    if( ( y < boxCentre[1]-boxWidths[1] ) || ( y > boxCentre[1]+boxWidths[1] ) )
      return false;
    else {
      if( ( z < boxCentre[2]-boxWidths[2] ) || ( z > boxCentre[2]+boxWidths[2] ) )
	return false;
    }
  }
  return true;
}

// point in box test
bool OBBBox::point_in_box(double point[3]) {
  bool rval = point_in_box(point[0], point[1], point[2]);
  return rval;
}
