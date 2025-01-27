#include <vector>
#include <string>

using namespace std;

/**********************************************************************/
struct pieceOfWork {
    double start;
    double end;
    pieceOfWork(double i, double j) : start(i), end(j) {}
    pieceOfWork() { start = 0; end = 0; }
    ~pieceOfWork() {}
};
/******************************************************************************/
// Template class - returns subset vector containing elements X to Y
template <typename T>
vector<T> slicing(vector<T> const& v, size_t X, size_t Y) {

    if (v.size() == 0) { return v; }

    // Begin and End iterator
    auto first = v.begin() + X;
    auto last = v.begin() + Y;

    // Copy the element
    vector<T> vector(first, last);

    // Return the results
    return vector;
}
/******************************************************************************/
template<typename T>
string toString(const T&x) {
    stringstream output;
    output << x;
    return output.str();
}
/******************************************************************************/

template<typename T>
void printVector(const vector<T>& x) {
    string result = "";
    char delim = ',';

    if (x.size() == 0) { return; }

    result = toString(x[0]);

    for (int i = 1; i < x.size(); i++) {
        result += delim + toString(x[i]);
    }

    cout << result << endl;
}
/******************************************************************************/
class Utils {
public:

    vector<pieceOfWork> divideWork(double numItems, int numProcessors) {
        // divide work between processors
        vector<pieceOfWork> work;

        if (numItems < numProcessors) { numProcessors = numItems; }
        size_t startIndex = 0;

        for (size_t remainingProcessors = numProcessors; remainingProcessors > 0;
        remainingProcessors--) {

            //case for last processor
            size_t numToProcess = numItems;
            if (remainingProcessors != 1) {
                numToProcess = ceil(numItems / remainingProcessors);
            }
            work.push_back(pieceOfWork(startIndex, (startIndex+numToProcess)));
            startIndex += numToProcess;
            numItems -= numToProcess;
        }
        return work;
    }
private:

};
/******************************************************************************/
