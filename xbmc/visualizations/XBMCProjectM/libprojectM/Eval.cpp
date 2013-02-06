
/* Evaluation Code */

#include <cstdio>
#include <cstdlib>

#include "Common.hpp"
#include "fatal.h"

#include "Eval.hpp"
#include "Expr.hpp"
#include "Param.hpp"
#include "Func.hpp"
#include "wipemalloc.h"

#include "BuiltinFuncs.hpp"

InfixOp *Eval::infix_add = NULL;
InfixOp *Eval::infix_minus = NULL;
InfixOp *Eval::infix_div = NULL;
InfixOp *Eval::infix_mult = NULL;
InfixOp *Eval::infix_or = NULL;
InfixOp *Eval::infix_and = NULL;
InfixOp *Eval::infix_mod = NULL;
InfixOp *Eval::infix_negative = NULL;
InfixOp *Eval::infix_positive = NULL;

/* Initializes all infix operators */
int Eval::init_infix_ops() {

	Eval::infix_add = new InfixOp(INFIX_ADD, 4);
	Eval::infix_minus = new InfixOp(INFIX_MINUS, 3);
	Eval::infix_div = new InfixOp(INFIX_DIV, 2);
	Eval::infix_or = new InfixOp(INFIX_OR, 5);
	Eval::infix_and = new InfixOp(INFIX_AND,4);
	Eval::infix_mod = new InfixOp(INFIX_MOD, 1);
	Eval::infix_mult = new InfixOp(INFIX_MULT, 2);
	
	/* Prefix operators */
	Eval::infix_positive = new InfixOp(INFIX_ADD, 0);
	Eval::infix_negative = new InfixOp(INFIX_MINUS, 0);

	return PROJECTM_SUCCESS;
}

/* Destroys the infix operator list. This should
   be done on program exit */
int Eval::destroy_infix_ops()
{

  delete(Eval::infix_add);
  delete(Eval::infix_minus);
  delete(Eval::infix_div);
  delete(Eval::infix_or);
  delete(Eval::infix_and);
  delete(Eval::infix_mod);
  delete(Eval::infix_mult);
  delete(Eval::infix_positive);
  delete(Eval::infix_negative);

  Eval::infix_add = NULL;
  Eval::infix_minus = NULL;
  Eval::infix_div = NULL;
  Eval::infix_or = NULL;
  Eval::infix_and = NULL;
  Eval::infix_mod = NULL;
  Eval::infix_mult = NULL;
  Eval::infix_positive = NULL;
  Eval::infix_negative = NULL;

  return PROJECTM_SUCCESS;
}
