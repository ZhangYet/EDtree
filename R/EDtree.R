setClass(Class="EDTREE",
         representation=representation(
             tree="list",
             split="list"
             ),
         )

#learnsample: a list containing response, variables, the type of variables, etc.
#weight: a vector.
#distance: a string, determine which measure to be used. We implement the method for e-distance first.
#control: a list containing min_nodes (if number of samples in one node less than min_nodes, this node is a leaf.), max_depth ( if the depth for one node is greater or equal to max_depth, this node is a leaf)
#EDtree: this function return an object name EDTREE, which contain the nodes and the splits
EDtree <- function(learnsample, weight, distance, controls){
    #init and check the parameters
    #TODO

    #grow tree
    #tree: a list containing the nodes.
    tree <- .Call("EDtree", learnsample, weight, distance, controls)
    
    #prune tree and set up S4 class
    prune_tree <- pruneTree(tree)
    edtree <- new("edtree")
    edtree@tree <- prune_tree
    #TODO
}

pruneTree <- function(tree){
}

    
