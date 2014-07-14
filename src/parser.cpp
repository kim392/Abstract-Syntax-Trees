/**
 * @file parser.cpp
 * @author Chase Geigle
 * @date Summer 2014
 */

#include <cassert>
#include <iostream>
#include "parser.h"
#include "operation.h"
#include "number.h"
#include "terminal.h"
#include "binary_op.h"
#include "unary_op.h"

namespace cs225
{

/**
 * A "private class" for helping us parse expressions. Maintains all of the
 * state necessary to perform Dijkstra's shunting-yard algorithm.
 *
 * @see https://en.wikipedia.org/wiki/Shunting-yard_algorithm
 */
class parser
{
  public:
    /**
     * @param tokens The tokens to parse
     * @return the root of the parse tree for that expression
     */
    std::unique_ptr<node> parse(queue<std::unique_ptr<token>>& tokens);

  private:
    // add lots of other helper methods here!

    /**
     * The stack to hold the operator tokens encountered. This is the "side
     * rail" in the shunting yard algorithm.
     */
    stack<std::unique_ptr<token>> ops_;
    queue<std::unique_ptr<token>> qu_;
    /**
     * What is this for? It is a mystery (and a hint)!
     */
    stack<std::unique_ptr<node>> nodes_;
};

std::unique_ptr<node> parse(queue<std::unique_ptr<token>>& tokens)
{
    parser p;
    return p.parse(tokens);
}

std::unique_ptr<node> parser::parse(queue<std::unique_ptr<token>>& tokens)
{
    while (!tokens.empty())
    {
        auto& tok = tokens.front();
	if(tok->type() == token_type::OPERATION)
	{
		if(ops_.empty() || ops_.top()->as_operation()->precedence() <= tok->as_operation()->precedence())
		{
			ops_.push(std::move(tok));
		}
		else 
  		{
			qu_.push(std::move(ops_.top()));
			ops_.pop();
			ops_.push(std::move(tok));
		}
	}

	else if(tok->type() == token_type::TEXT) 
	{
		if(tok->text().front() == '(')
		{
			ops_.push(std::move(tok));
		}
		else
		{
			while(ops_.top()->text().front() != '(')
			{
				qu_.push(std::move(ops_.top()));
				ops_.pop();
				if(ops_.empty())
					throw std::runtime_error{"Missing ("};
			}
			ops_.pop();
		}
	}	

	else if(tok->type() == token_type::NUMBER)
	{
		qu_.push(std::move(tok));
	}
        tokens.pop();
    }
    while(!ops_.empty()) 
    {
//	if(ops_.top()->text().front() == '(' || ops_.top()->text().front() == ')')
//		throw std::runtime_error{"hahahha"};
	qu_.push(std::move(ops_.top()));
	ops_.pop();
    }
    while(!qu_.empty())
    {
	    auto& tok = qu_.front();
	    if(tok->type() == token_type::NUMBER)
	    {
		    double v = tok->as_number()->value();
		    std::unique_ptr<terminal> wow = make_term(v);
		    nodes_.push(std::move(wow));
		    qu_.pop();
	    }

	    else if(tok->type() == token_type::OPERATION)
	    {
		    uint32_t n = qu_.front()->as_operation()->args();
//		    if(qu_.size() < n)
//			    throw std::runtime_error{"insufficient value"};
//		    else
		    {
			    if(n==2)
			    {
				    std::unique_ptr<node> left = std::move(nodes_.top());
				    nodes_.pop();
				    std::unique_ptr<node> right = std::move(nodes_.top());
				    nodes_.pop();
				    std::string op = tok->text();
				    std::unique_ptr<node> binop = make_binary_op(op, std::move(left), std::move(right));
				    nodes_.push(std::move(binop));
			    }

			    else if(n==1)
			    {
				    std::unique_ptr<node> arg = std::move(nodes_.top());
				    nodes_.pop();
				    std::string op = tok->text();
				    std::unique_ptr<node> unop = make_unary_op(op, std::move(arg));
				nodes_.push(std::move(unop));
			    }
		    }
		    qu_.pop();
           }
    }

    return std::move(nodes_.top());
    /// @todo clean up remaining operators
    /// @todo return the root of your tree
    }
}
    
   
























