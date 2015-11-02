#include "obbbox.hpp"

class OBBBoxCreator {
  public:
    OBBBoxCreator();
   ~OBBBoxCreator();
    void SplitBoxX(OBBBox *box);

  private:
    int boxCount;
};
