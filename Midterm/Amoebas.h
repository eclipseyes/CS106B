#pragma once

#include "vector.h"
#include "grid.h"

/* Given an initial configuration of the amoebas, simulates
 * the growth of the amoeba colony until it stops growing.
 */
Vector<Grid<bool>> simulateAmoebas(const Grid<bool>& world);
