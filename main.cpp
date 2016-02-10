// main.cpp
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "ErrorContext.h"
#include "ClusteringTests.h"

using std::cout;
using std::endl;

using namespace Testing;

int main() {

    const int NumIters = 3;

    cout << endl << "Testing PA2!!" << endl << endl;

    cout << "NOTE:  If you see any memory errors, you MUST fix them!" << endl;
    cout << "       Tests intentionally invoke destructors after they complete,"
    << endl;
    cout << "       so if you see a seg-fault after a passed test, it is"
    << endl;
    cout << "       probably a bug in your destructor." << endl;

    cout << endl;

    ErrorContext ec(cout);

    // point tests
    test_point_smoketest(ec);
    test_point_id(ec, NumIters);
    test_point_getsetelem(ec, NumIters);
    test_point_copying(ec, NumIters);
    test_point_assignment(ec, NumIters);
    test_point_equality(ec, NumIters);
    test_point_comparison(ec, NumIters);
    test_point_CAO(ec, NumIters);
    test_point_SAO(ec, NumIters);
    test_point_distance(ec, NumIters);
    test_point_IO(ec, NumIters);

    // cluster tests
    test_cluster_smoketest(ec);
    test_cluster_subscript(ec, NumIters);
    test_cluster_equality(ec, NumIters);
    test_cluster_order(ec, NumIters);
    test_cluster_addremove(ec, NumIters);
    test_cluster_contain(ec, NumIters);
    test_cluster_copying(ec, NumIters);
    test_cluster_assignment(ec, NumIters);
    test_cluster_CAO(ec, NumIters);
    test_cluster_SAO(ec, NumIters);
    test_cluster_IO(ec, NumIters);

    return 0;
}
