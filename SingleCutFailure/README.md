# PROBLEM

The problem consists on finding the minimal number of cuts to make in order to cut all wires on the door as described on file [ICPC 2018](https://github.com/gabrielmsantos/acmicpc/blob/master/icpc2018.pdf)

# SOLUTION

The trick here is that in worst case scenarios we can make 2 cuts (DIAGONALS) to cut all wires turning the security system off. So, the problem changes to finding a solution consisting of only one cut.
In order to find the solution, we need to take these steps:
```
    1- Polar sorting all points in the cartesian plan (using the arc tangent) # O(nlogn)
```
```
    2- Iterating through all sorted points to find a cut for each one: you must cross only one point of the segment. # O(2n)
```
```
    3-  Check if the solution found is on the same side of the door. If so, move it to the next point of a different side. # O(1)
```
```
    4- If there is no single cut solution the DIAGONALS
```

