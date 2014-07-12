#ifndef UMINUS_H_
#define UMINUS_H_
#include <memory>
#include "node.h"
#include "unary_op.h"

namespace cs225
{

class uminus : public unary_op
{
    public:
	using unary_op::unary_op;
	double compute(double val) const override;
};

}
#endif
