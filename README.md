# ThreadingExample

The goal of ThreadingExample is to demonstrate the use of threaded C++ code in an R package.

![](https://github.com/SchlossLab/CppThreadingExample/blob/main/inst/extdata/Threads.jpg?raw=true)

## Installation

You can install the development version of ThreadingExample from [GitHub](https://github.com/) with:

``` r
# install.packages("pak")
pak::pak("SchlossLab/CppThreadingExample")
```

## Example

The basic example below will calculate the sum of 'data' using 4 processors.

``` r
library(ThreadingExample)
data <- c(1:100)
calculate_sum(data, 4)
```
