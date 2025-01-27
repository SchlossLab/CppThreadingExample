#ifndef ThreadingExample_sum_h
#define ThreadingExample_sum_h

//
//  sum.h
//  ThreadingExample
//
//  Created by Sarah Westcott on 12/16/24.
//  Copyright (c) 2024 Schloss Lab. All rights reserved.
//

#include <Rcpp.h>
#include <RcppThread.h>
#include "utils.h"

using namespace std;

// required by Rcpp and RcppThreads
// [[Rcpp::plugins(cpp11)]]
// [[Rcpp::depends(RcppThread)]]

/******************************************************************************/
class Sum {
 public:
     // constructor, proc = number of processors (default all available)
     Sum(const int proc);

     // default deconstuctor
    ~Sum() = default;

    // calculate the sum of data
    int accumulate(const Rcpp::IntegerVector& data);

    int getNumProcessors() { return processors; }

 private:

    // number of threads to use
    int processors;

    // function to create, execute and destroy threads.
    int createProcesses(const vector<int>& data);

};

/******************************************************************************/
#endif

