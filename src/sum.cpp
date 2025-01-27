//
//  sum.cpp
//  ThreadingExample
//
//  Created by Sarah Westcott on 12/16/24.
//  Copyright (c) 2024 Schloss Lab. All rights reserved.
//

#include "sum.h"

/******************************************************************************/
//custom data structure for threads to use.
// This is passed by void pointer so it can be any data type
// that can be passed using a single void pointer (LPVOID).

struct sumData {

    // variable containing portion of the data to sum
    vector<int> partialData;

    // variable containing subtotal to return to main process
    int partialSum;

    // sumData default constructor
    sumData() {
       partialSum = 0;
    }

    // sumData custom constructor
    sumData(const vector<int>& d) {
        partialData = d;
        partialSum = 0;
    }

    // sumData deconstructor
    ~sumData() = default;

};
/******************************************************************************/
// class constructor
Sum::Sum(const int proc) {

    processors = proc;

}
/******************************************************************************/
// class function for calculating the sum of data
int Sum::accumulate(const Rcpp::IntegerVector& data) {
    int result = 0;

    // convert data
    vector<int> my_data = Rcpp::as<std::vector<int> >(data);

    result = createProcesses(my_data);

    return result;
}
/******************************************************************************/
// Important notes:
// 1. non class function that will be run in parallel
//         - this is the where the work is done
// 2. must be defined (appear in the file) before function calling it
// 3. must return void, all inputs and results are passed in the sumData struct
// 4. can call other globally defined functions, and use any classes
// 5. All functions called / data structures used must be thread safe
//       - https://en.wikipedia.org/wiki/Thread_safety
// sumData - partialSum, partialData
void driverAccumulate(sumData* params){

    // loop over partialData adding to partialSum
    for(int i = 0; i < params->partialData.size(); i++) {

        RcppThread::checkUserInterrupt();

        params->partialSum += params->partialData[i];
    }

}
/******************************************************************************/
// class function for dividing work, creating and destroying threads
int Sum::createProcesses(const vector<int>& data) {

    // use divideWork function (numItems, numProcessors)
    Utils util;
    vector<pieceOfWork> startEnds = util.divideWork(data.size(), processors);

    vector<RcppThread::Thread*> workerThreads;
    vector<sumData*> threadData;

    //Launch worker threads
    for (int i = 0; i < processors-1; i++) {

        // create sumData* containing this thread's piece of work
            sumData* threadSum = new sumData(slicing(data, startEnds[i+1].start, startEnds[i+1].end));

        // save sumData* for later access
            threadData.emplace_back(threadSum);
        // create thread and save for join
        workerThreads.push_back(new RcppThread::Thread(driverAccumulate, threadSum));
    }


    // create sumData* containing main thread's piece of work
    sumData* firstSum = new sumData(slicing(data, startEnds[0].start, startEnds[0].end));
    // run worker function with main thread
    driverAccumulate(firstSum);
    // collect main thread's results
    int total = firstSum->partialSum;
    // delete main thread's sumData*
    delete firstSum;

    for (int i = 0; i < processors-1; i++) {

        // join threads
        workerThreads[i]->join();

        // collect worker thread's results
        total+=threadData[i]->partialSum;
        // delete worker thread's sumData* and delete thread
        delete threadData[i], workerThreads[i];
        // delete thread
    }

    return total;
}
/******************************************************************************/


