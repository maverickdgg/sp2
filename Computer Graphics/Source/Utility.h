#ifndef _UTILITU_H
#define _UTILITY_H

#include "Vertex.h"
#include "Mtx44.h"

Position operator*(const Mtx44& lhs, const Position&rhs);

#endif