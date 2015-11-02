#include <iostream>
#include "obbbox_creator.hpp"

OBBBoxCreator::OBBBoxCreator() {
  boxCount = 0;
};

OBBBoxCreator::~OBBBoxCreator() {
};

// split box along midpoint of x
void OBBBoxCreator::SplitBoxX(OBBBox *box) {
  double *centre = box->get_centre();
  double *widths = box->get_widths();
  OBBBox *parent   = box->get_parent();

  // make the left child  
  double left_centre[3] = {centre[0] - widths[0]/2., centre[1] , centre[2]};
  double left_width[3] = {widths[0]/2., widths[1] , widths[2]};
  
  OBBBox *left_child = new OBBBox(left_centre,left_width,++boxCount,parent);
  left_child->set_parent(box);

  // make the right child
  double right_centre[3] = {centre[0] + widths[0]/2., centre[1] , centre[2]};
  double right_width[3] = {widths[0]/2., widths[1] , widths[2]};
  
  OBBBox *right_child = new OBBBox(right_centre,right_width,++boxCount,parent);
  right_child->set_parent(box);

  // set the box children
  box->set_children(left_child,right_child);
};

