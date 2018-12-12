library(datasets)
library(cluster)
data("iris")
iris$Species<-NULL 
d <- scale(dist(iris,method = "euclidian"))
irisClusterKmeans <- kmeans(d, 3)
irisClusterH <- hkmeans(d, 3)
fviz_cluster(irisClusterKmeans, iris)
fviz_cluster(irisClusterH, iris)
