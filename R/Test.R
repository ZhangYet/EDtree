

test <- function(){
    data(iris)
    data(cars)

    sample <- list("response"=iris[1:50,], "variable"=cars)
    show(nrow(sample$response))
    weight <- rep(1, 50)
    distance <- "Edistance"
    contrls <- list(max_depth=5, min_node=5)

    init_test(sample, weight, controls)
}

init_test <- function(sample, weight, controls){
    node <- list()
    where <- rep(0, length(weight))
    .Call("init_node", node=node, learnsample=sample, weights=weight, where=where)
    return(node)

}

recurrencTest <- function(){
    tree <- .Call("grow_tree_test", 5)
}
