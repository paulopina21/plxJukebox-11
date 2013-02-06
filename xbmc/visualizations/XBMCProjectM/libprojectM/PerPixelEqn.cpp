

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>

#include "fatal.h"
#include "Common.hpp"

#include "Expr.hpp"
#include "Eval.hpp"
#include "Param.hpp"
#include "PerPixelEqn.hpp"
#include <map>

#include "wipemalloc.h"
#include <cassert>
/* Evaluates a per pixel equation */
void PerPixelEqn::evaluate(int mesh_i, int mesh_j) {

  GenExpr * eqn_ptr = 0;
 

 eqn_ptr = this->gen_expr;

 float ** param_matrix = (float**)this->param->matrix;

 if (param_matrix == 0) {
	 assert(param->engine_val);
	 (*(float*)param->engine_val) = eqn_ptr->eval_gen_expr(mesh_i, mesh_j);

  } else {

  assert(!(eqn_ptr == NULL || param_matrix == NULL));

  param_matrix[mesh_i][mesh_j] = eqn_ptr->eval_gen_expr(mesh_i, mesh_j);

  /* Now that this parameter has been referenced with a per
     pixel equation, we let the evaluator know by setting
     this flag */
  /// @bug review and verify this behavior
  param->matrix_flag = true;
  param->flags |= P_FLAG_PER_PIXEL;
  }
}

PerPixelEqn::PerPixelEqn(int _index, Param * _param, GenExpr * _gen_expr):index(_index), param(_param), gen_expr(_gen_expr) {

	assert(index >= 0);
	assert(param != 0);
	assert(gen_expr != 0);
	
}

