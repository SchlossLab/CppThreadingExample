#' @title calculate_sum
#' @name calculate_sum
#'
#' @param data vector, containing Integers to add
#' @param processors Integer, number of cores to use. Default = all available
#' @description Calculate the sum of integers
#' @return Integer, containing sum of data
#'
#' @export
#' @author Sarah Westcott, \email{swestcot@@umich.edu}
#' @examples
#'
#' data <- 1:20
#' total <- calculate_sum(data)
#'
# Improvements to consider:
# 1. Remove Integer Limitation, allowing for decimals
# 2. Summing other R data objects, ie. data.table.
#     How do we store this in C++?
#     How should we divide work the differently to minimize overhead?
#     What about a column or row sums option?

calculate_sum <- function(data, processors = parallelly::availableCores()) {

    result <- 0

    # check user inputs: ie. correct data types, vector not NULL
    if(is.null(data) || !(class(data) %in% c("numeric", "integer"))) {
        cli::cli_abort("Unexpected data type, ensure 'data' is type 'numeric'.")
    }
    print(processors)
    # call rcpp exported function passing it data and processors
    result <- calculateSum(data, processors)
    return(result)
}
