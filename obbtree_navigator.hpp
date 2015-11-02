#include "obbbox.hpp"
#include <iostream>
#include <fstream>

class OBBTreeNavigator {
  public:
    OBBTreeNavigator(OBBBox *root_set);
   ~OBBTreeNavigator();

  void set_root(OBBBox *root_set);

  OBBBox* point_intersect(double x, double y, double z);
  OBBBox* point_intersect(double point[3]);

  void print_tree();
  void print_node(OBBBox *node, std::ostream &os);

  private:
    void print_node_attributes(OBBBox *node, std::ostream &os);

  private:
    OBBBox *rootBox;
};
