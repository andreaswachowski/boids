# Boids

I was interested in boids since I read an article on them in the mid 1980s[^1]. Finally, some time to dabble around. This is a pure hobby project, nothing in it will meet any production standards whatsoever (I also haven't worked with C++ for two decades), and progress (if one can speak of it at all) will be erratic.

[^1]: IIRC it was in the German magazine "P.M. Peter Moosleitners interessantes
    Magazin", and from the pictures I remember I assume they reported on
[Reynolds, Flocks, herds and schools: A distributed behavioral
model](https://dl.acm.org/doi/10.1145/37402.37406)

The goal is to experiment with a 2D simulation of people in crowded
environments. For example,

* a pedestrian road where people enter/leave stores, move alone or in small groups, stop randomly at
  shopping windows or gather in front of snack bars, etc.
* a train platform with people waiting to embark trains, crowds during
  entry/exit of a train, etc.

# Development Setup

The program has been tested on MacOS. The CMakefile depends on ncurses under the
HOMEBREW_PREFIX of /opt/homebrew.

```
cd build
cmake ..
cmake --build .
./boid_simulation
```


# References

* [Reynolds, Flocks, herds and schools: A distributed behavioral model](https://dl.acm.org/doi/11.1145/37402.37406)
