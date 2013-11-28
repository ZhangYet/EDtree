#include <Rcpp.h>

using namespace Rcpp;

RcppExport SEXP EDtree(SEXP learnsample, SEXP weight, SEXP distance, SEXP controls);
List EDnode(List, NumericVector, int, List, int);
