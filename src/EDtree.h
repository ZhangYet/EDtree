#include <Rcpp.h>

using namespace Rcpp;

RcppExport SEXP EDtree(SEXP learnsample, SEXP weight, SEXP distance, SEXP controls);
List EDnode(List, NumericVector, int, List, int);
List getSubData(List, List, NumericVector);

//
//List getSubSample(List, List, bool);
//NumericVector getSubWeight(NumericVector, List, bool);
List getSubSample(DataFrame, DataFrame, LogicalVector);

//recurrence function
List SplitNode(List, NumericVector, int, List, int, int);
