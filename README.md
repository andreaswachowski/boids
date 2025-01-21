# Boids

I was interested in boids since I read an article on them in the mid 1980s[^1]. Finally, some time to dabble around. This is a pure hobby project, nothing in it will meet any production standards whatsoever. I haven't worked with C++ for two decades. Progress will be erratic at best.

[^1]: IIRC it was in the German magazine "P.M. Peter Moosleitners interessantes
    Magazin", and from the pictures I remember I assume they reported on
[Reynolds, Flocks, herds and schools: A distributed behavioral
model](https://dl.acm.org/doi/10.1145/37401.37406)

The goal is to experiment with a 2D simulation of people in crowded
environments. For example,

* a pedestrian road where people enter/leave stores, move alone or in small groups, stop randomly at
  shopping windows or gather in front of snack bars, etc.
* a train platform with people waiting to embark trains, crowds during
  entry/exit of a train, etc.

# Development Setup

The program is being developed on MacOS. The pipeline also compiles on Ubuntu.

```
mkdir Debug
cd Debug
cmake -D CMAKE_BUILD_TYPE=Debug ..
cmake --build .
./boid_simulation
```

Alternatively, use `Release` instead of `Debug`.

To test, execute `./Debug/tests/tests` or call `ctest` inside the `Debug` directory.

## cmake-format

```
python3 -m venv venv
source venv/bin/activate
python3 -m pip install cmakelang
```

## Logging

Logs go to `logs/development.txt`. To specify the log level:

```
./boid_simulation SPDLOG_LEVEL=debug
```

# References

* [Reynolds, "Flocks, herds and schools: A distributed behavioral model"](https://dl.acm.org/doi/10.1145/37401.37406)
* [Kim, Sujeong et al, "Interactive simulation of dynamic crowd behaviors using general adaptation syndrome theory", 2012](https://dl.acm.org/doi/10.1145/2159616.2159626)
