#ifndef PLUS_H_
#define PLUS_H_
#include <memory>
#include "binary_op.h"

namespace cs225
{

class plus : public binary_op
{
    public:
        using binary_op::binary_op;
        double combine (double left, double right) const override;
};

}
#endif
