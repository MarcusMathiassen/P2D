
//-----------------------------------------|
//  AUTHOR: MARCUS MATHIASSEN          |
//  DATE: 03.05.2016               |
//-----------------------------------------|

#include "Process.h"

#include <thread>
#include <vector>

// Each node contains a list indexes of ints corresponding
//  to each objects index in the object_vec vector.
void Calc(const vec<vec<int> > &cont, size_t begin, const size_t end) {
  for (size_t k = begin; k < end; ++k) {
    for (size_t i = 0; i < cont[k].size(); ++i) {
      for (size_t j = i + 1; j < cont[k].size(); ++j) {
        if (object_vec[cont[k][i]]->collision_detection(
                *object_vec[cont[k][j]])) {
          object_vec[cont[k][i]]->collision_resolve(*object_vec[cont[k][j]]);
        }
      }
    }
  }
}

void process_segment(int begin, int end) {
  for (size_t i = begin; i < end; ++i) {
    for (size_t j = i + 1; j < object_vec.size(); ++j) {
      if (object_vec[i]->collision_detection(*object_vec[j])) {
        object_vec[i]->collision_resolve(*object_vec[j]);
      }
    }
  }
}

void update() {
  if (object_vec.size() > 0) {
    if (ballCol) {
      vec<vec<int> > cont;

      if (use_quadtree) {
        quadtree.update();
        quadtree.get(cont);
      } else if (use_fixedgrid) {
        fixedgrid.update();
        fixedgrid.get(cont);
      }

      // If we´re using collision optimizations
      if (use_quadtree || use_fixedgrid)
        Calc(cont, 0, cont.size());
      else if (numThreads > 0) {
        // Multithreading. DOESNT WORK.
        int total = object_vec.size();
        int parts = total / numThreads;

        std::vector<std::thread> thread_pool(numThreads);

        process_segment(parts * numThreads, total);

        for (int i = 0; i < numThreads; ++i) {
          thread_pool[i] =
              std::thread(process_segment, parts * i, parts * (i + 1));
        }
        for (auto &thread : thread_pool) thread.join();
      } else
        process_segment(0, object_vec.size());
    }

    // Update each objects position
    for (auto &object : object_vec) object->update();
  }
}
