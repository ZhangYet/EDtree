
data(iris)
data(cars)

sample <- list(reponse=iris[1:50,], variable=cars)
weight <- rep(1, 50)
distance <- "Edistance"
contrls <- list(max_depth=5, min_node=5)

test <- function(){
    EDtree(sample, weight, distance, contrls)
}
