#ifndef MINUS_H_
#define MINUS_H_
#include <memory>
#include "binary_op.h"

namespace cs225
{

class minus : public binary_op
{
    public:
	using binary_op::binary_op;
	double combine(double left, double right) const override;
};

}
#endif
