#include "obbtree_navigator.hpp"  

// constructor
OBBTreeNavigator::OBBTreeNavigator(OBBBox *root_set) {
  set_root(root_set);
}

// destructor
OBBTreeNavigator::~OBBTreeNavigator() {
}

void OBBTreeNavigator::set_root(OBBBox *root_set) {
  rootBox = root_set;
}

// intersect the point in the tree
OBBBox* OBBTreeNavigator::point_intersect(double x, double y, double z) {
  OBBBox *entity = rootBox;
  bool inside;
  while ( true ) {
    // only the terminating leaves have null left and right children
    if(entity->leftChild == NULL && entity->rightChild == NULL)
      return entity;

    // check the left child, then the right child
    if (entity->leftChild->point_in_box(x,y,z))
      entity = entity->leftChild;
    else if (entity->rightChild->point_in_box(x,y,z))
      entity = entity->rightChild;
    else
      return NULL;
  }
}

// intersect the point in the tree
OBBBox* OBBTreeNavigator::point_intersect(double point[3]) {
  return point_intersect(point[0], point[1], point[2]);
}

// print the tree
void OBBTreeNavigator::print_tree() {
  // output file
  std::ofstream dotfile ("graph.dot");
  dotfile << "digraph graphname { " << std::endl;
  print_node(rootBox,dotfile);
  // navigate around the tree printing each node and its children
  dotfile << "} " << std::endl;
}

void OBBTreeNavigator::print_node(OBBBox *node, std::ostream &os) {
  if(node != NULL ) {

    if(node->get_parent() != NULL ) {
      os << node->get_parent()->get_boxid() << "->" << node->get_boxid() << std::endl;
      print_node_attributes(node->get_parent(),os);
      print_node_attributes(node,os);
    }
    print_node(node->leftChild,os);
    print_node(node->rightChild,os);
  }
}

// print the attribtues for the node
void OBBTreeNavigator::print_node_attributes(OBBBox *node, std::ostream &os) {
  os << node->get_boxid() << "[shape=box,label = \"" << node->get_boxid();
  double *widths =  node->get_widths();
  double *origin =  node->get_centre();
  os << " | xrange = " << origin[0] - widths[0] << " to " << origin[0] + widths[0] << "\"];" << std::endl;
}
