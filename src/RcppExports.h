#include <Rcpp.h>

using namespace Rcpp;

// rcpp_hello_world
List rcpp_hello_world();

int get_nodes(SEXP); // get the number of samples in a node
void ED_Node(SEXP, SEXP, SEXP, SEXP, SEXP, int, int); // compute and set split point on each node
void set_nodeID(SEXP, int);
void ED_splitnode(SEXP, SEXP, SEXP, SEXP); // determine the split point

bool check_depth(SEXP, int); // is it so deep that we must stop?
bool check_nodes(SEXP, int); // is there too few samples to split?
bool get_nodeterminal(SEXP, SEXP); // I found it redunt at this time

SEXP get_leftnode(SEXP);
SEXP get_rightnode(SEXP);


RcppExport SEXP init_node(SEXP, SEXP, SEXP, SEXP);
void grow_tree(SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, int*, int);// the main function to do the 

RcppExport SEXP EDtree_Grow(SEXP, SEXP, SEXP, SEXP, SEXP);
