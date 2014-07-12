#ifndef UPLUS_H_
#define UPLUS_H_
#include <memory>
#include "node.h"
#include "unary_op.h"

namespace cs225
{
class uplus : public unary_op
{
    public:
	using unary_op::unary_op;
	double compute (double val) const override;
};
}
#endif
