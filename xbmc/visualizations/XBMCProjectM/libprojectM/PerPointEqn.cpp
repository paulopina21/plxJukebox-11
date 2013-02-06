

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <cassert>
#include "fatal.h"
#include "Common.hpp"

#include "CustomWave.hpp"
#include "Eval.hpp"
#include "Expr.hpp"
#include "Param.hpp"
#include "PerPixelEqn.hpp"
#include "PerPointEqn.hpp"
#include <map>
#include <iostream>
#include "wipemalloc.h"

/* Evaluates a per point equation for the current custom wave given by interface_wave ptr */
void PerPointEqn::evaluate(int i)
{

  float * param_matrix;
  GenExpr * eqn_ptr;

  //  samples = CustomWave::interface_wave->samples;

  eqn_ptr = gen_expr;

  if (param->matrix == NULL)
  {
    assert(param->matrix_flag == false);
    (*(float*)param->engine_val) = eqn_ptr->eval_gen_expr(i,-1);

  
    return;
  }

  else
  {
    param_matrix = (float*)param->matrix;
  
      // -1 is because per points only use one dimension
      param_matrix[i] = eqn_ptr->eval_gen_expr(i, -1);
    

    /* Now that this parameter has been referenced with a per
       point equation, we let the evaluator know by setting
       this flag */

    if (!param->matrix_flag)
      param->matrix_flag = true;

  }

}

PerPointEqn::PerPointEqn(int _index, Param * _param, GenExpr * _gen_expr, int _samples):
    index(_index),
    samples(_samples),
    param(_param),
    gen_expr(_gen_expr)

{}


PerPointEqn::~PerPointEqn()
{
  delete gen_expr;
}
