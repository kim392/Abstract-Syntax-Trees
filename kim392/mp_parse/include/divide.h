#ifndef DIVIDE_H_
#define DIVIDE_H_
#include <memory>
#include "binary_op.h"

namespace cs225
{

class divide : public binary_op
{
    public:
	using binary_op::binary_op;
	double combine(double left, double right) const override;
};

}
#endif
