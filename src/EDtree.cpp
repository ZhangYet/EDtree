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
  
  if(!node0["isTerminal"])
    {
      //begin the recurrence
      List subdata = getSubData(node0["split"], LearnSample, Weight); //split the data into two part.

    }
  
  return(wrap(node0));

}

List SplitNode(List learnsample, NumericVector weight, int distance, List controls, int depth, int nodeID)
{
  List NewNode;
  NewNode = EDnode(learnsample, weight, distance, controls, nodeID);
  bool stop = (depth>=4 || NewNode["isTerminal"]); //in fact stop will be determined by controls not 4.
  if(stop)
    {
      //compute and return the node
      //Computation is left to be done
      return NewNode;
    }
  else
    {
      List subdata = getSubData(NewNode["split"], learnsample, weight);
      NewNode["leftchild"] = SplitNode(subdata["leftsample"], subdata["leftweight"], distance, controls, depth+1, 2*nodeID+1);
      NewNode["rightchild"] = SplitNode(subdata["rightsample"], subdata["rightweight"], distance, controls, depth+1, 2*nodeID+2);
      return NewNode;
    }
  return NewNode;
}

List getSubData(List split, List learnsample, NumericVector weight)
{
  List res = List::create(Named("leftsample"),
			  Named("leftweight"),
			  Named("rightsample"),
			  Named("rightweight")
			  );
  
  DataFrame VarDF = learnsample["variable"];
  DataFrame ResDF = learnsample["response"];
  NumericVector flagVec = VarDF[as<std::string>(split["spvar"])];
  LogicalVector flag = flagVec < as<double>(split["spvalue"]);

  //split sample and weight
  NumericVector ltemp;
  NumericVector rtemp;
  for(int i=0; i<flag.size(); i++)
    {
      if(flag[i])
	{
	  ltemp.push_back(weight[i]);
	}
      else
	{
	  rtemp.push_back(weight[i]);
	}
    }// end of for int i=0; i<flag.size(); i++
  res["leftweight"] = ltemp;
  res["rightweight"] = rtemp;

  List subsample = getSubSample(VarDF, ResDF, flag);
  List leftsample = List::create(Named("variable")=subsample["leftvariable"], 
				 Named("response")=subsample["leftresponse"]);
  List rightsample = List::create(Named("variable")=subsample["rightvariable"],
				  Named("response")=subsample["rightresponse"]);

  res["leftsample"] = leftsample;
  res["rightsample"] = rightsample;
  return res;
  
}

List getSubSample(DataFrame varDF, DataFrame resDF, LogicalVector flag)
{
  List res;
  
  List VarNames = varDF.attr("name");
  List ResNames = resDF.attr("name");

  DataFrame ltemp;
  DataFrame rtemp;
  for(int i=0; i<VarNames.size(); i++)
    {
      NumericVector vltemp;
      NumericVector vrtemp;
      NumericVector dtemp = varDF[as<std::string>(VarNames[i])];
      for(int j=0; j<flag.size(); j++)
	{
	  if(flag[j]) vltemp.push_back(dtemp[j]);
	  else vrtemp.push_back(dtemp[j]);
	}
      ltemp[as<std::string>(VarNames[i])] = vltemp;
      rtemp[as<std::string>(VarNames[i])] = vrtemp;
    }
  res["leftvariable"] = ltemp;
  res["rightvariable"] = rtemp;

  DataFrame ltemp1;
  DataFrame rtemp1;
  for(int i=0; i<ResNames.size(); i++)
    {
      NumericVector vltemp;
      NumericVector vrtemp;
      NumericVector dtemp = resDF[as<std::string>(VarNames[i])];
      for(int j=0; j<flag.size(); j++)
	{
	  if(flag[j]) vltemp.push_back(dtemp[j]);
	  else vrtemp.push_back(dtemp[j]);
	}
      ltemp1[as<std::string>(VarNames[i])] = vltemp;
      rtemp1[as<std::string>(VarNames[i])] = vrtemp;
    }
  res["leftresponse"] = ltemp1;
  res["rightresponse"] = rtemp1;

  return res;
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
  
  

  Rcpp::DataFrame Variable = learnsample["variable"];
  Rcpp::DataFrame Response = learnsample["response"];
  node["n_samples"] = Response.nrows();

  if(as<int>(node["n_samples"]) < controls["min_samples"])
    node["isTerminal"] = true;
  else
    node["isTerminal"] = false; 
  
  node["split"] = NULL; 
  node["leftChild"] = NULL;
  node["rightChild"] = NULL;
 
  return node;
}
