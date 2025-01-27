# test calc_sum function

test_that("test calc_sum ", {
    data <- seq(1,100, 1)
    # test standard functions
    result <- calculate_sum(data, 1)
    # test that results with 1 processor == results with multiple processors
    result_processors_4 <- calculate_sum(data, 4)
    expect_equal(result, result_processors_4)
    expect_equal(result, sum(data))
    expect_equal(result_processors_4, sum(data))
})

test_that("test calc_sum errors", {

    # test inputs that will cause errors
    expect_error(calculate_sum())
    expect_error(calculate_sum(c("a", "b")))
})
