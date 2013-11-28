#include "EDtree.h"

SEXP EDtree(SEXP learnsample, SEXP weight, SEXP distance, SEXP controls)
{
  List node0;
  //convert data to different types from SEXP
  Rcpp::List LearnSample = Rcpp::as<List>(learnsample);
  Rcpp::NumericVector Weight = Rcpp::as<NumericVector>(weight);
  int Distance = as<int>(distance); 
  Rcpp::List Controls = as<List>(controls);

  //init node0, the root node
  node0 = EDnode(LearnSample, Weight, Distance, Controls, 0);
  
  
  return(wrap(node0));

}

List EDnode(List learnsample, NumericVector weight, int distance, List controls, int nodeID)
{
  List node = List::create(Named("nodeID"),
			   Named("weight"),
			   Named("statictics"),
			   Named("n_samples"),
			   Named("isTerminal"),
			   Named("split"),
			   Named("leftChild"),
			   Named("rightChild")
			   );

  node["nodeID"] = nodeID;

  double Weight = 0.0;
  for(int i=0; i<weight.size(); i++)
    Weight += weight[i];
  node["weight"] = Weight;

  //compute the statictics. We should implement a function to do so.
  //TODO
  node["statictics"] = 0;

  node["isTerminal"] = false; // default value

  Rcpp::DataFrame Variable = learnsample["variable"];
  Rcpp::DataFrame Response = learnsample["response"];
  node["n_samples"] = Response.nrows();
  
  node["split"] = NULL; 
  node["leftChild"] = NULL;
  node["rightChild"] = NULL;
 
  return node;
}
