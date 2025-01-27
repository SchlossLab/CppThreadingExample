#include <testthat.h>
#include <iostream>

#include "sum.h"

context("Sum C++ unit tests") {

    test_that("test constructor") {

        Sum mySum(4);

        expect_true(mySum.getNumProcessors() == 4);
    }

    test_that("test accumulate function") {

        Sum mySum(4);
        Rcpp::IntegerVector v(5, 10);

        expect_true(mySum.accumulate(v) == 50);
    }
}
