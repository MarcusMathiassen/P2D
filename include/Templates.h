#ifndef TEMPLATES_H
#define TEMPLATES_H

#include <memory>
#include <vector>

template <class T>
using vec = std::vector<T>;
template <class T>
using uptr = std::unique_ptr<T>;

#endif
