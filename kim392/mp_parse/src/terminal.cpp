#include "terminal.h"

namespace cs225
{

terminal::terminal(double arg)
{
    val_ = std::unique_ptr<double> (new double{arg});
}

double terminal::value() const
{
    return *val_.get();
}

std::unique_ptr<terminal> make_term(double arg)
{
    std::unique_ptr<terminal> ret(new terminal(arg));
    return ret;
}

}
