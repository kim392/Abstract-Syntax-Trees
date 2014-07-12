#ifndef TERMINAL_H_
#define TERMINAL_H_
#include <memory>
#include "node.h"

namespace cs225
{

class terminal : public node
{
    public: 
	terminal(double arg);
	double value() const override;
    private:
	std::unique_ptr<double> val_;
};

std::unique_ptr<terminal> make_term (double arg);

}
#endif
