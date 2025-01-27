#include <Rcpp.h>
#include "sum.h"


//' @title calculate_sum
//' @name calculate_sum
//' @rdname calculate_sum
//' @param data IntegerVector, containing numbers to add
//' @param processors Integer, number of cores to use. Default = all available
//' @description Calculate the sum of integers
//' @return Integer, containing sum of data
// [[Rcpp::export]]
std::int64_t calculateSum(Rcpp::IntegerVector data,
                           std::int64_t processors) {

    std::int64_t result = 0;

    // create instance of Sum class
    Sum* calc = new Sum(processors);
    // call accumulate function
    result = calc->accumulate(data);
    // delete instance of Sum class
    delete calc;
    return result;
}
