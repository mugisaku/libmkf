#include"expression_node.hpp"
#include"expression_operator.hpp"
#include"cmplr_precontext.hpp"




namespace expression{




Node::
Node():
left(nullptr),
right(nullptr)
{
}


Node::
Node(const mkf::Node&  src, PreContext&  prectx):
left(nullptr),
right(nullptr)
{
  read(src,prectx);
}


Node::
Node(Element&&  el):
element(std::move(el)),
left(nullptr),
right(nullptr)
{
}


Node::
Node(const Element&  el):
element(el),
left(nullptr),
right(nullptr)
{
}


Node::
Node(Node&&  rhs) noexcept:
left(nullptr),
right(nullptr)
{
  *this = std::move(rhs);
}


Node::
Node(const Node&  rhs):
left(nullptr),
right(nullptr)
{
  *this = rhs;
}


Node::
~Node()
{
  clear();
}




Node&
Node::
operator=(const Node&  rhs)
{
  clear();

  element = rhs.element;

   left = rhs.left ? new Node(*rhs.left ):nullptr;
  right = rhs.right? new Node(*rhs.right):nullptr;

  return *this;
}


Node&
Node::
operator=(Node&&  rhs) noexcept
{
  clear();

  element = std::move(rhs.element);

  std::swap( left,rhs.left );
  std::swap(right,rhs.right);

  return *this;
}


void
Node::
clear()
{
  delete left          ;
         left = nullptr;

  delete right          ;
         right = nullptr;
}


namespace{
void
merge(std::list<Node*>&  buf, std::vector<Element>&  uols)
{
  auto  it = uols.rbegin();
  auto end = uols.rend();

    while(it != end)
    {
      buf.emplace_back(new Node(std::move(*it++)));
    }
}
}


std::list<Node*>
Node::
to_rpn(std::vector<Element>&&  src)
{
  std::list<Node*>  dst;

  std::vector<Element>   unary_operator_stack;
  std::vector<Element>  binary_operator_stack;

    for(auto&  el: src)
    {
        switch(static_cast<ElementKind>(el))
        {
          case(ElementKind::unary_operator):
            unary_operator_stack.emplace_back(el);
            break;
          case(ElementKind::binary_operator):
            {
              auto  cur_preced = static_cast<Precedence>(el).number;

                if(unary_operator_stack.size())
                {
                  auto  tail_preced = static_cast<Precedence>(unary_operator_stack.back()).number;

                    if(cur_preced >= tail_preced)
                    {
                        for(auto&  unop: unary_operator_stack)
                        {
                          binary_operator_stack.emplace_back(std::move(unop));
                        }
                    }

                  else
                    {
                      merge(dst,unary_operator_stack);
                    }


                  unary_operator_stack.clear();
                }


                while(binary_operator_stack.size())
                {
                  auto&  tail = binary_operator_stack.back();

                  auto  tail_preced = static_cast<Precedence>(tail).number;

                    if(cur_preced <= tail_preced)
                    {
                        if((cur_preced == tail_preced) &&
                           (static_cast<Associativity>(tail) == Associativity::right_to_left))
                        {
                          break;
                        }

                      else
                        {
                          dst.emplace_back(new Node(std::move(tail)));

                          binary_operator_stack.pop_back();
                        }
                    }

                  else
                    {
                      break;
                    }
                }


  	           binary_operator_stack.emplace_back(el);
            }
            break;
          case(ElementKind::operand):
            dst.emplace_back(new Node(std::move(el)));
            break;
        }
    }


  merge(dst, unary_operator_stack);
  merge(dst,binary_operator_stack);

  return std::move(dst);
}


Node*
Node::
create_tree(std::list<Node*>&&  ls)
{
  std::vector<Node*>  operand_buf;

    while(ls.size())
    {
      auto  nd = ls.front();
                 ls.pop_front();

        switch(static_cast<ElementKind>(nd->element))
        {
          case(ElementKind::operand):
            operand_buf.emplace_back(nd);
            break;
          case(ElementKind::unary_operator):
              if(operand_buf.size() < 1)
              {
                printf("単項演算オペランドの数が足りません\n");
                throw *nd;
              }


            nd->left = operand_buf.back();

            operand_buf.pop_back();
            operand_buf.emplace_back(nd);
            break;
          case(ElementKind::binary_operator):
              if(operand_buf.size() < 2)
              {
                printf("二項演算オペランドの数が足りません\n");
                throw *nd;
              }


            nd->right = operand_buf.back();

            operand_buf.pop_back();

            nd->left = operand_buf.back();

            operand_buf.pop_back();


            operand_buf.emplace_back(nd);
            break;
        }
    }


    if(operand_buf.size() != 1)
    {
      printf("結果が不正でした\n");

      throw operand_buf;
    }


  return operand_buf.front();
}




namespace{
Value
get_operand_value(const Value&  src, PreContext&  prectx)
{
  return src;
}
}


Constant
Node::
make_constant(PreContext&  prectx) const
{
    switch(element.kind)
    {
  case(ElementKind::null):
      return left->make_constant(prectx);
      break;
  case(ElementKind::operand):
      return element.data.operand.make_constant(prectx);
      break;
  case(ElementKind::unary_operator):
      {
        UnaryOperator  op(element.data.operator_);

        return expression::make_constant(*left,op,prectx);
      }
      break;
  case(ElementKind::binary_operator):
      {
        BinaryOperator  op(element.data.operator_);

        return expression::make_constant(*left,*right,op,prectx);
      }
      break;
    }


  throw Constant::Error();
}


Value
Node::
make_value(PreContext&  prectx) const
{
    switch(element.kind)
    {
  case(ElementKind::null):
      return left->make_value(prectx);
      break;
  case(ElementKind::operand):
      return element.data.operand.make_value(prectx);
      break;
  case(ElementKind::unary_operator):
      {
        UnaryOperator  op(element.data.operator_);

        return expression::make_value(*left,op,prectx);
      }
      break;
  case(ElementKind::binary_operator):
      {
        BinaryOperator  op(element.data.operator_);

        return expression::make_value(*left,*right,op,prectx);
      }
      break;
    }


  return Value();
}


Type
Node::
compile(Context&  ctx) const
{
    switch(element.kind)
    {
  case(ElementKind::null):
      return left->compile(ctx);
      break;
  case(ElementKind::operand):
//      return element.data.operand.compile(ctx);
      break;
  case(ElementKind::unary_operator):
      {
        UnaryOperator  op(element.data.operator_);

        return expression::compile(*left,op,ctx);
      }
      break;
  case(ElementKind::binary_operator):
      {
        BinaryOperator  op(element.data.operator_);

        return expression::compile(*left,*right,op,ctx);
      }
      break;
    }


  return Type();
}


void
Node::
print(FILE*  f) const
{
    switch(element.kind)
    {
      case(ElementKind::null):
        left->print(f);
        break;
      case(ElementKind::operand):
        element.print(f);
        break;
      case(ElementKind::unary_operator):
        fprintf(f,"(");

        element.print(f);

        left->print(f);

        fprintf(f,")");
        break;
      case(ElementKind::binary_operator):
        fprintf(f,"(");
 
        left->print(f);

        element.print(f);

        right->print(f);

        fprintf(f,")");
        break;
    }
}


namespace{


using ElementList = std::vector<Element>;


Subscript
read_subscript(const mkf::Node&  src, PreContext&  prectx)
{
  Literal*  lit = nullptr;

  mkf::Cursor  cur(src);

    while(!cur.test_ended())
    {
      auto&  nd = cur.get();

        if(nd == "literal_object")
        {
          lit = new Literal(nd,prectx);
        }

      else
        if(nd == "expression")
        {
          lit = new Literal(new expression::Node(nd,prectx));
        }


      cur.advance();
    }


  return Subscript(lit);
}


void
read_unary_operand(const mkf::Node&  base, PreContext&  prectx, ElementList&  ls)
{
  mkf::Cursor  cur(base);

    while(!cur.test_ended())
    {
      auto&  nd = cur.get();

        if(nd == "unary_operator")
        {
          ls.emplace_back(UnaryOperator(nd.children.front()->defname));
        }

      else
        if(nd == "literal_object")
        {
          ls.emplace_back(Literal(nd,prectx));
        }

      else
        if(nd == "argument_list")
        {
          auto  arr = new Array(Literal::read_list(nd,prectx));

          ls.emplace_back(BinaryOperator('(',')'));

          ls.emplace_back(ArgumentList(arr));
        }

      else
        if(nd == "subscript")
        {
          ls.emplace_back(BinaryOperator('[',']'));

          ls.emplace_back(read_subscript(nd,prectx));
        }


      cur.advance();
    }
}


}



void
Node::
read(const mkf::Node&  base, PreContext&  prectx)
{
  mkf::Cursor  cur(base);

  ElementList  ls;

    while(!cur.test_ended())
    {
      auto&  nd = cur.get();

        if(nd == "binary_operator")
        {
          ls.emplace_back(BinaryOperator(nd.children.front()->defname));
        }

      else
        if(nd == "unary_operand")
        {
          read_unary_operand(nd,prectx,ls);
        }


      cur.advance();
    }


  auto  rpn = to_rpn(std::move(ls));

  left = create_tree(std::move(rpn));
}


}




