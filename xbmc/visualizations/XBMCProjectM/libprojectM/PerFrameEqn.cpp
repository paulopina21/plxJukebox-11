

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fatal.h"
#include "Common.hpp"

#include "Param.hpp"
#include "PerFrameEqn.hpp"

#include "Eval.hpp"
#include "Expr.hpp"

#include "wipemalloc.h"
#include <cassert>

/* Evaluate an equation */
void PerFrameEqn::evaluate() {

     if (PER_FRAME_EQN_DEBUG) { 
		 printf("per_frame_%d=%s= ", index, param->name.c_str());
		 fflush(stdout); 
     }
	 
    //*((float*)per_frame_eqn->param->engine_val) = eval_gen_expr(per_frame_eqn->gen_expr);
	assert(gen_expr);
	assert(param);
	param->set_param(gen_expr->eval_gen_expr(-1,-1));

     if (PER_FRAME_EQN_DEBUG) printf(" = %.4f\n", *((float*)param->engine_val)); 
		 
}


/* Frees perframe equation structure. Warning: assumes gen_expr pointer is not freed by anyone else! */
PerFrameEqn::~PerFrameEqn() {

  delete gen_expr;

  // param is freed in param_tree container of some other class

}

/* Create a new per frame equation */
PerFrameEqn::PerFrameEqn(int _index, Param * _param, GenExpr * _gen_expr) :
	index(_index), param(_param), gen_expr(_gen_expr) {}
