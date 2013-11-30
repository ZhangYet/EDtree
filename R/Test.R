EDtreeTest <- function(){
    data(iris)
    data(cars)
    learnsample <- list("response"=iris[1:50,],
        "variable"=cars
        )
    weight <- rep(1,50)
    ditance <- 1
    controls <- list()
    test <- .Call("EDtree", learnsample, weight, ditance, controls)
}

