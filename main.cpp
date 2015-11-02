#include <iostream>
#include "obbbox.hpp"
#include "obbbox_creator.hpp"
#include "obbtree_navigator.hpp"

#include <omp.h>
#include <random>
#include <chrono>

int seeds[8] = {12345,45678,91011,12131,
		41516,17181,92021,22232};

int results[15] = {0,0,0,0,0,
		   0,0,0,0,0,
		   0,0,0,0,0};

int main(int argc, char* argv[]) {
  
  OBBBox *root = new OBBBox();
  root->set_centre(0.,0.,0.);
  root->set_widths(10.,10.,10.);

  OBBBoxCreator *crt = new OBBBoxCreator();
  crt->SplitBoxX(root);
  crt->SplitBoxX(root->leftChild);
  crt->SplitBoxX(root->rightChild);
  crt->SplitBoxX(root->leftChild->leftChild);
  crt->SplitBoxX(root->leftChild->rightChild);
  crt->SplitBoxX(root->rightChild->leftChild);
  crt->SplitBoxX(root->rightChild->rightChild);

  // start timing
  auto t1 = std::chrono::high_resolution_clock::now();

  // do point in vol checks
  int num = 100000000;
  # pragma omp parallel 
  {

  #ifdef _OPENMP 
    #ifdef DEBUG
    std::cout << "using " << omp_get_num_threads() << " threads" << std::endl;
    std::cout << "i am thread " << omp_get_thread_num() << std::endl;
    #endif
  #endif

  // each thread has its own navigator
  OBBTreeNavigator *trn = new OBBTreeNavigator(root);

  // each thread has own generator
  std::default_random_engine rd;
  #ifdef _OPENMP
    #ifdef DEBUG
    std::cout << "setting seed of thread " << omp_get_thread_num() << " to " << seeds[omp_get_thread_num()] << std::endl;
    #endif
  rd.seed(seeds[omp_get_thread_num()]);
  #else
  rd.seed(seeds[0]);
  #endif
  std::mt19937 e2(rd());
  std::uniform_real_distribution<> dist(0, 1);

  # pragma omp for
  for ( int i = 0 ; i < num ; i++ ) {
    // random point between -10 and 10
    double x =  (20*dist(e2))-10.;
    // intersect the point with the box
    int result = trn->point_intersect(x,0.0,0.0)->get_boxid();
    // openmp must be atomic
    #pragma omp atomic
    results[result] += 1;
  }
  } // end parallel section


  auto t2 = std::chrono::high_resolution_clock::now();
  std::cout << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count();
  std::cout << " milliseconds\n" << std::endl; 
  // we should find that the only hits are in the terminating leaves
  for ( int i = 0 ; i < 15 ; i++ ) {
    std::cout << i << " " << results[i] << std::endl;
  }
  
  return 0;
}
