#ifndef NODE_H_
#define NODE_H_
#include <memory>
#include <string>
#include <cmath>

namespace cs225
{

class node
{
    public:
	virtual double value() const = 0;
	virtual ~node() = default;
};

}
#endif
