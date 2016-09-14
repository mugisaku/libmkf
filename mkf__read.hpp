#ifndef MKF__READ_HPP_INCLUDED
#define MKF__READ_HPP_INCLUDED


#include"mkf_node.hpp"
#include"mkf_cursor.hpp"


namespace mkf{


unsigned int  read_decimal_integer(const Node&  src);
unsigned int  read_binary_integer( const Node&  src);
unsigned int  read_hex_integer(    const Node&  src);


}


#endif




