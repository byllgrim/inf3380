inf3380
=======
notes and shit for inf3380

pensum
======
introduction to parallel computing 2nd ed
-----------------------------------------
introduction: 3 design, 4 communication, 5 modeling.

paradigms: 6 message passing, 7 shared memory.

algorithms: 8 matrices, 9 sorting, 10 graphs.

* ch3 parallel algorithm design
  * 3.1 preliminaries
  * 3.2 decomposition
  * 3.3 tasks and interactions
  * 3.4 mapping for load balancing
  * 3.5 interaction overhead
  * 3.6 parallel algorithm models
* ch4 communication operations
  * 4.1 one-to-all broadcast and all-to-one reduction
  * 4.2 all-to-all broadcast and reduction
  * 4.3 all-reduce and prefix-sum
  * 4.4 scatter and gather
  * 4.5 all-to-all personalized communication
  * 4.6 circular shift
  * 4.7 improving communication speed
* ch5 analytical modeling
  * 5.1 sources of overhead
  * 5.2 performance metrics
  * 5.3 granularity
  * 5.4 scalability
  * 5.5 cost-optimal execution time
  * 5.6 asymptotic analysis
  * 5.7 other scalability metrics
* ch6 the message-passing paradigm
  * 6.1 message-passing
  * 6.2 send and receive
  * 6.3 mpi
  * 6.4 topologies and embedding
  * 6.5 overlapping communication with computation? TODO
  * 6.6 collective communication and computation
  * 6.7 groups and communicators
* ch7 shared address space
  * 7.10 openmp
* ch8 dense matrix algorithms
  * 8.1 matrix-vector multiplication
  * 8.2 matrix-matrix multiplication
  * 8.3 linear equations
* ch9 sorting
  * 9.1 issues
  * 9.3 bubble sort
  * 9.4 quicksort
* ch10 graph algorithms
  * 10.1 definitions and representations
  * 10.2 minimum spanning tree: prim's TODO
  * 10.3 single-source shortest paths: dijkstra's TODO
  * 10.4 all-pairs shortest paths
