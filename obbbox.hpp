#include <cstddef>
#include <algorithm>

#ifndef OBBBOX_HPP
#define OBBBOX_HPP

class OBBBox {
  public:
    OBBBox(double centre[3], double widths[3], int boxid = 0, OBBBox *parent = NULL);
    OBBBox();
   ~OBBBox();
  
    // setters
    void set_boxid(int boxid);
    void set_centre(double x, double y, double z);
    void set_widths(double x_width, double y_width, double z_width);
    void set_parent(OBBBox *parent);
    void set_children(OBBBox *left_child, OBBBox *right_child);

    // getters
    int get_boxid();
    double * get_widths();
    double * get_centre();
    OBBBox*  get_parent();

    // point in box test
    bool point_in_box(double x, double y, double z);
    bool point_in_box(double point[3]);

  OBBBox *leftChild;
  OBBBox *rightChild;

  private:
  int boxId;
  double boxCentre[3];
  double boxWidths[3];
  OBBBox *boxParent;
};

#endif
