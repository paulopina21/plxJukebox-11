
/* Function management */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "Common.hpp"
#include "fatal.h"

#include "Func.hpp"
#include <map>

Func::Func (const std::string & _name, float (*_func_ptr)(float*), int _num_args):
	name(_name), func_ptr(_func_ptr), num_args(_num_args) {}

/* Frees a function type, real complicated... */
Func::~Func() {}
