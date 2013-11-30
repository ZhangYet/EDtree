#include "test.h"

SEXP grow_tree_test(SEXP max_depth)
{
  Rcpp::List node0;
  node0["ID"] = 0;
  node0["left_child"] = recurrence(1, 1, max_depth);
  node0["right_child"] = recurrence(2, 1, max_depth);
  return(Rcpp::wrap(node0));
}

SEXP recurrence(int ID, int depth, SEXP max_depth)
{
  int i_max_depth = as<int>(max_depth);
  List new_node;
  if(depth >= i_max_depth){
    new_node["ID"] = ID;
    new_node["left_child"] = NULL;
    new_node["right_child"] = NULL;
    return(Rcpp::wrap(new_node));
  }
  else{
    new_node["ID"] = ID;
    new_node["left_child"] = recurrence(ID*2+1, depth+1, max_depth);
    new_node["right_child"] = recurrence(ID*2+2, depth+1, max_depth);
    return(Rcpp::wrap(new_node));
  }
}


