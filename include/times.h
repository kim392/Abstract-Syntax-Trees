#ifndef TIMES_H_
#define TIMES_H_
#include <memory>
#include "binary_op.h"

namespace cs225
{

class times : public binary_op
{
    public:
        using binary_op::binary_op;
        double combine (double left, double right) const override;
};

}
#endif
