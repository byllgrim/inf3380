n = 10

houses <- matrix(, nrow=n, ncol=2)
for (i in 1:n) {
	#houses <- c(houses, c(sample(1:n, 1), sample(1:n, 1)))
	houses[i,1] <- sample(1:n, 1)
	houses[i,2] <- sample(1:n, 1)
}
png(filename="records.png")
plot(houses, col="blue")

station <- matrix(c(sample(1:n, 1), sample(1:n, 1)), ncol=2)
points(station, col="red", pch=19)

distance.to.station <- function(house, station) {
	s = house - station
	sqrt(s[1]^2 + s[2]^2)
}
d = vector()
for (i in 1:n) {
	d <- c(d, distance.to.station(houses[i,], station))
}
d

# TODO find index of minimum displacement
