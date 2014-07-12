#include "unary_op.h"
#include "uminus.h"
#include "uplus.h"
namespace cs225
{

unary_op::unary_op(std::unique_ptr<node> arg)
{
    arg_ = std::move(arg);
}

double unary_op::value() const
{
    return compute(arg_->value());
}

std::unique_ptr<node> make_unary_op (const std::string& op, std::unique_ptr<node> arg)
{
    if(op.front() == '#')
	return std::move(std::unique_ptr<node> {new uplus{std::move(arg)}});
    else if(op.front() == '~')
	return std::move(std::unique_ptr<node> {new uminus{std::move(arg)}});
    else
	return std::move(std::unique_ptr<node> {});
}
}
