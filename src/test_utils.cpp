#include <testthat.h>
#include <iostream>
#include <numeric>

#include "utils.h"

context("Utils C++ unit tests") {

    test_that("test slicing") {
        // 5,5,5,5,5,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10
        vector<int> vec(5, 5);
        vec.resize(20, 10);
        expect_true(vec.size() == 20);

        // subset a vector
        vector<int> firstHalf = slicing(vec, 0, 10);
        expect_true(firstHalf.size() == 10);
        expect_true(firstHalf[0] == 5);
        expect_true(accumulate(firstHalf.begin(), firstHalf.end(), 0) == 75);

        // subset a vector
        vector<int> secondHalf = slicing(vec, 10, 20);
        expect_true(secondHalf.size() == 10);
        expect_true(secondHalf[0] == 10);
        expect_true(accumulate(secondHalf.begin(), secondHalf.end(), 0) == 100);
    }

    test_that("test divideWork") {

        // 95 pieces of work, 4 processors, 3 = 24, 1 = 27
        Utils util;
        vector<pieceOfWork> startEnds = util.divideWork(95, 4);

        expect_true(startEnds[0].start == 0);
        expect_true(startEnds[0].end == 24);
        expect_true(startEnds[1].start == 24);
        expect_true(startEnds[1].end == 48);
        expect_true(startEnds[2].start == 48);
        expect_true(startEnds[2].end == 72);
        expect_true(startEnds[3].start == 72);
        expect_true(startEnds[3].end == 95);
    }

}
