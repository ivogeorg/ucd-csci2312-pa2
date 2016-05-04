// ClusteringTests.cpp
//
// Created by Ivo Georgiev on 10/29/15.
//

#include <iostream>
#include <cassert>
#include <iomanip>
#include <fstream>

#include "ClusteringTests.h"
#include "Point.h"
#include "Cluster.h"

using namespace Clustering;
using namespace Testing;

#define DESC(x) desc(x, __LINE__)  // ugly hack, but saves some time




// - - - - - - - - - - helper functions - - - - - - - - - -
const Point point_in_and_out(const Point p) { return Point(p); }



// - - - - - - - - - - T E S T S - - - - - - - - - -

// - - - - - - - - - - P O I N T - - - - - - - - - -

// Smoketest: constructor, copy constructor, destructor
void test_point_smoketest(ErrorContext &ec) {
    bool pass;

    ec.DESC("--- Test - Point - Smoketest ---");

    ec.DESC("constructor, dimensionality, destructor");
    pass = true;
    for (int i = 0; i < 10; i ++) {

        // Construct a Point
        // At the end of the block, destructor will be called
        Point p(10);

        pass = (p.getDims() == 10);
        if (!pass) break;
    }
    ec.result(pass);


    ec.DESC("constructor, large size");
    pass = true;
    for (int i = 0; i < 10; i ++) {

        // Construct a Point
        // At the end of the block, destructor will be called
        Point p(1000000);

        pass = (p.getDims() == 1000000);
        if (!pass) break;
    }
    ec.result(pass);


    ec.DESC("copy constructor");
    pass = true;
    for (int i = 0; i < 10; i ++) {

        // Construct a Point
        // At the end of the block, destructor will be called
        Point p1(10);
        Point p2(p1);

        pass = (p1.getDims() == 10 && p2.getDims() == 10);
        if (!pass) break;
    }
    ec.result(pass);
}

// id
void test_point_id(ErrorContext &ec, unsigned int numRuns) {
    bool pass;

    // Run at least once!!
    assert(numRuns > 0);

    ec.DESC("--- Test - Point - Point ID ---");

    for (int run = 0; run < numRuns; run ++)
    {
        ec.DESC("get a point's id");

        {
            Point p(15);

            pass = (p.getId() >= 0);

            ec.result(pass);
        }

        ec.DESC("sequential id-s");

        {
            Point **points = new Point*[100];
            for (int i=0; i<100; i++)
                points[i] = new Point(15);

            pass = true;
            int firstId = points[0]->getId();
            for (int i=0; i<100; i++)
                pass = pass && (points[i]->getId() == (firstId + i));

            for (int i=0; i<100; i++)
                delete points[i];
            delete [] points;

            ec.result(pass);
        }
    }
}

// setValue, getValue, operator[]
void test_point_getsetelem(ErrorContext &ec, unsigned int numRuns) {
    bool pass;

    // Run at least once!!
    assert(numRuns > 0);

    ec.DESC("--- Test - Point - Get/set element ---");

    for (int run = 0; run < numRuns; run ++)
    {
        ec.DESC("values default to zero");

        {
            Point p(50);

            // Check zeros
            pass = true;
            for (int i = 0; i < 50; i ++) {
                pass = pass &&
                        (p.getValue(i) == 0.0) &&
                        (p[i] == 0.0);
            }
            ec.result(pass);
        }

        ec.DESC("setValue, getValue (0-indexed)");

        {
            Point p(20);

            // Set values
            for (int i = 0; i < 20; i ++)
                p.setValue(i, 13.43 * i * i + 4.567 * i + 1.234567);

            // Check values
            pass = true;
            for (int i = 0; i < 20; i ++)
                pass = pass &&
                        (p.getValue(i) == (13.43 * i * i + 4.567 * i + 1.234567)) &&
                        (p[i] == (13.43 * i * i + 4.567 * i + 1.234567));
            ec.result(pass);
        }

        ec.DESC("operator[] (0-indexed)");

        {
            Point p(5);

            // Set values
            for (int i = 0; i < 5; i ++)
                p[i] = 1000000.43 * i * i + 400000.567 * i + 10000.234567;

            // Check values
            pass = true;
            for (int i = 0; i < 5; i ++)
                pass = pass &&
                       (p.getValue(i) == (1000000.43 * i * i + 400000.567 * i + 10000.234567)) &&
                       (p[i] == (1000000.43 * i * i + 400000.567 * i + 10000.234567));
            ec.result(pass);
        }
    }
}

// Copy constructor
void test_point_copying(ErrorContext &ec, unsigned int numRuns) {
    bool pass;

    // Run at least once!!
    assert(numRuns > 0);

    ec.DESC("--- Test - Point - Copy ---");

    for (int run = 0; run < numRuns; run ++) {

        ec.DESC("simple copy");

        {
            Point p1(50);

            for (int i = 0; i < 50; i ++)
                p1[i] = 44.56 * i * i + 23.45 * i + 12.34;

            Point p2(p1);

            pass = true;
            for (int i = 0; i < 50; i ++)
                pass = pass && (p1[i] == p2[i]);
            ec.result(pass);
        }

        ec.DESC("pass and return by value");

        {
            Point p1(50);

            for (int i = 0; i < 50; i ++)
                p1[i] = 44.56 * i * i + 23.45 * i + 12.34;

            Point p2 = point_in_and_out(p1);

            pass = true;
            for (int i = 0; i < 50; i ++)
                pass = pass && (p1[i] == p2[i]);
            ec.result(pass);
        }
    }
}

// operator=
void test_point_assignment(ErrorContext &ec, unsigned int numRuns) {
    bool pass;

    // Run at least once!!
    assert(numRuns > 0);

    ec.DESC("--- Test - Point - Assign ---");

    for (int run = 0; run < numRuns; run++) {

        ec.DESC("simple assignment");

        {
            Point p1(50);

            for (int i = 0; i < 50; i++)
                p1[i] = 44.56 * i * i + 23.45 * i + 12.34;

            Point p2 = p1;

            pass = true;
            for (int i = 0; i < 50; i++)
                pass = pass && (p1[i] == p2[i]);
            ec.result(pass);
        }

        ec.DESC("chained assignment");

        {
            Point p1(50);

            for (int i = 0; i < 50; i++)
                p1[i] = 44.56 * i * i + 23.45 * i + 12.34;

            Point p2(50), p3(50), p4(50), p5(50);

            p2 = p3 = p4 = p5 = p1;

            pass = true;
            for (int i = 0; i < 50; i++)
                pass = pass && (p1[i] == p2[i]);
            ec.result(pass);
        }
    }
}

// operator==, operator!=
void test_point_equality(ErrorContext &ec, unsigned int numRuns) {
    bool pass;

    // Run at least once!!
    assert(numRuns > 0);

    ec.DESC("--- Test - Point - Equal ---");

    for (int run = 0; run < numRuns; run++) {

        ec.DESC("compare equal");

        {
            Point p1(50);

            for (int i = 0; i < 50; i++)
                p1[i] = 44.56 * i * i + 23.45 * i + 12.34;

            Point p2(p1);

            pass = (p2 == p1);
            ec.result(pass);
        }


        ec.DESC("ensure operator== is not a dummy");

        {
            Point p1(50);

            for (int i = 0; i < 50; i++)
                p1[i] = 44.56 * i * i + 23.45 * i + 12.34;

            Point p2(p1);
            p2[1] = p2[1] + 1.0;

            pass = !(p2 == p1);
            ec.result(pass);
        }

        ec.DESC("compare not equal");

        {
            Point p1(50);

            for (int i = 0; i < 50; i++)
                p1[i] = 44.56 * i * i + 23.45 * i + 12.34;

            Point p2(p1);
            p1[49] = p1[49] + 100.0;

            pass = (p2 != p1);
            ec.result(pass);
        }
    }
}

// operator<, operator<=, operator>, operator>=
// (pseudo-lexicographic comparison)
void test_point_comparison(ErrorContext &ec, unsigned int numRuns) {
    bool pass;

    // Run at least once!!
    assert(numRuns > 0);

    ec.DESC("--- Test - Point - Compare ---");

    for (int run = 0; run < numRuns; run++) {

        ec.DESC("compare pseudo-lexicographic order");

        {
            Point p1(50), p2(50), p3(50);

            for (int i = 0; i < 50; i ++) {
                p1[i] = i;
                p2[i] = i + 1.0;
                p3[i] = i + 2.0;
            }

            pass = (p1 < p2) &&
                   (p2 < p3) &&
                   (p1 < p3);
            ec.result(pass);
        }

        ec.DESC("less than, one different value, leading");

        {
            Point p1(50), p2(50), p3(50);

            for (int i = 0; i < 50; i ++) {
                p1[i] = p2[i] = p3[i] = i;
            }
            p2[1] = p1[1] + std::numeric_limits<double>::epsilon();
            p3[1] = p2[1] + std::numeric_limits<double>::epsilon();

            pass = (p1 < p2) &&
                   (p2 < p3) &&
                   (p1 < p3);
            ec.result(pass);
        }

        ec.DESC("less than, one different value, middle");

        {
            Point p1(50), p2(50), p3(50);

            for (int i = 0; i < 50; i ++) {
                p1[i] = p2[i] = p3[i] = i;
            }
            p2[30] = p1[30] + 0.00000001;
            p3[30] = p2[30] + 0.00000001;

            pass = (p1 < p2) &&
                   (p2 < p3) &&
                   (p1 < p3);
            ec.result(pass);
        }

        ec.DESC("less than, one different value, trailing");

        {
            Point p1(50), p2(50), p3(50);

            for (int i = 0; i < 50; i ++) {
                p1[i] = p2[i] = p3[i] = i;
            }
            p2[49] = p1[49] + 0.00000001;
            p3[49] = p2[49] + 0.00000001;

            pass = (p1 < p2) &&
                   (p2 < p3) &&
                   (p1 < p3);
            ec.result(pass);
        }

        ec.DESC("less than or equal, equal values");

        {
            Point p1(50), p2(50), p3(50);

            for (int i = 0; i < 50; i ++) {
                p1[i] = p2[i] = p3[i] = i;
            }

            pass = (p1 <= p2) &&
                   (p2 <= p3) &&
                   (p1 <= p3);
            ec.result(pass);
        }

        ec.DESC("less than or equal, one different value, trailing");

        {
            Point p1(50), p2(50), p3(50);

            for (int i = 0; i < 50; i ++) {
                p1[i] = p2[i] = p3[i] = i;
            }
            p2[49] = p1[49] + 0.00000001;
            p3[49] = p2[49] + 0.00000001;

            pass = (p1 <= p2) &&
                   (p2 <= p3) &&
                   (p1 <= p3);
            ec.result(pass);
        }

        ec.DESC("more than or equal, equal values");

        {
            Point p1(50), p2(50), p3(50);

            for (int i = 0; i < 50; i ++) {
                p1[i] = p2[i] = p3[i] = i;
            }

            pass = (p1 >= p2) &&
                   (p2 >= p3) &&
                   (p1 >= p3);
            ec.result(pass);
        }

        ec.DESC("more than or equal, one different value, middle");

        {
            Point p1(50), p2(50), p3(50);

            for (int i = 0; i < 50; i ++) {
                p1[i] = p2[i] = p3[i] = i;
            }

            p2[30] = p3[30] + 0.00000001;
            p1[30] = p2[30] + 0.00000001;

            pass = (p1 >= p2) &&
                   (p2 >= p3) &&
                   (p1 >= p3);
            ec.result(pass);
        }

        ec.DESC("more than, one different value, middle");

        {
            Point p1(50), p2(50), p3(50);

            for (int i = 0; i < 50; i ++) {
                p1[i] = p2[i] = p3[i] = i;
            }

            p2[30] = p3[30] + 0.00000001;
            p1[30] = p2[30] + 0.00000001;

            pass = (p1 > p2) &&
                   (p2 > p3) &&
                   (p1 > p3);
            ec.result(pass);
        }
    }
}

// operator+=, operator-=, operator*=, operator/=
void test_point_CAO(ErrorContext &ec, unsigned int numRuns) {
    bool pass;

    // Run at least once!!
    assert(numRuns > 0);

    ec.DESC("--- Test - Point - Compound arithmetic ---");

    for (int run = 0; run < numRuns; run++) {

        ec.DESC("plus equals (two points)");

        {
            Point p1(50), p2(50);

            for (int i = 0; i < 50; i++) {
                p1[i] = i;
                p2[i] = i + 1;
            }

            Point p3(50);
            p3 += p1 += p2;
            pass = true;
            for (int i = 0; i < 50; i++) {
                pass = pass && (p3[i] == 2 * i + 1);
            }
            ec.result(pass);
        }

        ec.DESC("minus equals (two points)");

        {
            Point p1(50), p2(50), p3(50);

            for (int i = 0; i < 50; i++) {
                p1[i] = i;
                p2[i] = i + 1;
                p3[i] = 3 * i + 1;
            }

            p3 -= p2 -= p1;
            pass = true;
            for (int i = 0; i < 50; i++) {
                pass = pass && (p3[i] == 3 * i);
            }
            ec.result(pass);
        }

        ec.DESC("times equals (point and double)");

        {
            Point p1(50);

            for (int i = 0; i < 50; i++) {
                p1[i] = i;
            }

            p1 *= 3.14;

            pass = true;
            for (int i = 0; i < 50; i++) {
                pass = pass && (p1[i] == 3.14 * i);
            }
            ec.result(pass);
        }

        ec.DESC("divide equals (point and double)");

        {
            Point p1(50);

            for (int i = 0; i < 50; i++) {
                p1[i] = 100.0 * i;
            }

            p1 /= 3.14;

            pass = true;
            for (int i = 0; i < 50; i++) {
                pass = pass && (p1[i] == 100.0 * i / 3.14);
            }
            ec.result(pass);
        }
    }
}

// operator+, operator-, operator*, operator/
void test_point_SAO(ErrorContext &ec, unsigned int numRuns) {
    bool pass;

    // Run at least once!!
    assert(numRuns > 0);

    ec.DESC("--- Test - Point - Simple arithmetic ---");

    for (int run = 0; run < numRuns; run++) {

        ec.DESC("plus (two points)");

        {
            Point p1(50), p2(50);

            for (int i = 0; i < 50; i++) {
                p1[i] = i;
                p2[i] = i + 1;
            }

            Point p3 = p1 + p2;
            pass = true;
            for (int i = 0; i < 50; i++) {
                pass = pass && (p3[i] == 2 * i + 1);
            }
            ec.result(pass);
        }

        ec.DESC("minus (two points)");

        {
            Point p1(50), p2(50);

            for (int i = 0; i < 50; i++) {
                p1[i] = i + 1;
                p2[i] = 2 * i - 1;
            }

            Point p3 = p2 - p1;
            pass = true;
            for (int i = 0; i < 50; i++) {
                pass = pass && (p3[i] == i - 2);
            }
            ec.result(pass);
        }

        ec.DESC("times (point and double)");

        {
            Point p1(50);

            for (int i = 0; i < 50; i++) {
                p1[i] = i;
            }

            Point p2 = p1 * 3.14;

            pass = true;
            for (int i = 0; i < 50; i++) {
                pass = pass && (p2[i] == 3.14 * i);
            }
            ec.result(pass);
        }

        ec.DESC("divide (point and double)");

        {
            Point p1(50);

            for (int i = 0; i < 50; i++) {
                p1[i] = 100.0 * i;
            }

            Point p2 = p1 / 3.14;

            pass = true;
            for (int i = 0; i < 50; i++) {
                pass = pass && (p2[i] == 100.0 * i / 3.14);
            }
            ec.result(pass);
        }
    }
}

// distanceTo
void test_point_distance(ErrorContext &ec, unsigned int numRuns) {
    bool pass;

    // Run at least once!!
    assert(numRuns > 0);

    ec.DESC("--- Test - Point - Distance ---");

    for (int run = 0; run < numRuns; run++) {

        ec.DESC("same point");

        {
            Point p1(50);

            for (int i = 0; i < 50; i++)
                p1[i] = 2.4 * i * i + 1.3 * i + 6.7;

            Point p2(p1);

            pass = (p1.distanceTo(p2) == 0);
            ec.result(pass);
        }

        ec.DESC("5 units away");

        {
            Point p1(50);

            for (int i = 0; i < 50; i++)
                p1[i] = i;

            Point p2(p1);
            p2[1] += 5;

            pass = (p1.distanceTo(p2) == 5);
            if (!pass) std::cout << p1.distanceTo(p2) << " ";
            ec.result(pass);
        }

        // Integer sequence A180442

        ec.DESC("distance 1612 from origin");

        {
            Point p1(169); // 198 - 29

            unsigned int start = 30;
            for (int i = 0; i < 169; i++) {
                p1[i] = start;
                start++;
            }

            Point origin(169); // relies on initialization to zeros

            pass = (p1.distanceTo(origin) == 1612);
            if (!pass) std::cout << p1.distanceTo(origin) << " ";
            ec.result(pass);
        }
    }
}

// operator>>, operator<< (incl. exceptions)
void test_point_IO(ErrorContext &ec, unsigned int numRuns) {
    bool pass;

    // Run at least once!!
    assert(numRuns > 0);

    ec.DESC("--- Test - Point - Stream IO ---");

    for (int run = 0; run < numRuns; run++) {

        ec.DESC("stream between two points");

        {
            Point p1(50);

            for (int i = 0; i < 50; i++)
                p1[i] = 6.12 * i * i + 5.17 * i + 4.19;

            Point p2(50);
            std::stringstream iostr;
            iostr << std::setprecision(20) << p1; // Avoid truncation
            iostr >> p2;

            pass = true;
            for (int i = 0; i < 50; i++)
                pass = pass && (p2[i] == p1[i]);
            if (!pass) {
                std::cout << p1 << std::endl;
                std::cout << p2 << std::endl;
            }
            ec.result(pass);

        }
    }
}


// - - - - - - - - - - C L U S T E R - - - - - - - - - -

// Smoketest: constructor, copy constructor, destructor
void test_cluster_smoketest(ErrorContext &ec) {
    bool pass;

    ec.DESC("--- Test - Cluster - Smoketest ---");

    ec.DESC("constructor, destructor");
    pass = true;
    for (int i = 0; i < 10; i ++) {

        Cluster c;
    }
    ec.result(pass);


    ec.DESC("size getter - implement if you haven't");
    pass = true;
    for (int i = 0; i < 10; i ++) {

        // Construct a Point
        // At the end of the block, destructor will be called
        Cluster c;

        pass = (c.getSize() == 0);
        if (!pass) break;
    }
    ec.result(pass);


    ec.DESC("copy constructor");
    pass = true;
    for (int i = 0; i < 10; i ++) {

        Cluster c1, c2(c1);

        pass = (c1 == c2);
        if (!pass) break;
    }
    ec.result(pass);
}

// add, remove
void test_cluster_addremove(ErrorContext &ec, unsigned int numRuns) {
    bool pass;

    // Run at least once!!
    assert(numRuns > 0);

    ec.DESC("--- Test - Cluster - Add/remove points ---");

    for (int run = 0; run < numRuns; run++) {

        ec.DESC("add and check with size getter");

        {
            Cluster c1;
            c1.add(Point(50));
            c1.add(Point(50));
            c1.add(Point(50));

            pass = (c1.getSize() == 3);

            ec.result(pass);
        } // by default, points will get released here


        ec.DESC("add, remove, and check with size getter");

        {
            Point   p1(10),
                    p2(10),
                    p3(10);
            Cluster c1;
            c1.add(p1); c1.add(p2); c1.add(p3);
            c1.remove(p1); c1.remove(p2); c1.remove(p3);

            pass = (c1.getSize() == 0);
            if (!pass) {
                std::cout << std::endl;
                std::cout << c1 << std::endl;
                std::cout << std::endl;
            }

            ec.result(pass);
        } // by default, points will get released here

        ec.DESC("add, check with cluster equality, remove");

        {
            Point   p1(10),
                    p2(10),
                    p3(10);

            Cluster c1, c2;
            c1.add(p1); c1.add(p2); c1.add(p3);
            c2.add(p1); c2.add(p2); c2.add(p3);

            pass = (c1 == c2);
            // don't forget to remove the points from one
            // of the clusters to avoid the "double delete"
            c2.remove(p1); c2.remove(p2); c2.remove(p3);

            ec.result(pass);
        }

        ec.DESC("check point after add and remove");

        {
            Point   p1(10);

            for (int i = 0; i < 10; i++)
                p1[i] = 5.4 * i * i + 3.4 * i + 1.6;

            Cluster c1;
            c1.add(p1);
            Point p2 = c1.remove(p1);

            pass = (p1 == p2);

            ec.result(pass);
        }
    }
}

// Containment
void test_cluster_contain(ErrorContext &ec, unsigned int numRuns) {
    bool pass;

    // Run at least once!!
    assert(numRuns > 0);

    ec.DESC("--- Test - Cluster - Containment ---");

    for (int run = 0; run < numRuns; run++) {

        ec.DESC("cluster with one point");

        {
            Point p(10);
            p[0] = p[2] = p[4] = p[8] = 6.705;
            Cluster c;
            c.add(p);

            pass = c.contains(p);

            ec.result(pass);
        }

        ec.DESC("cluster with several points");

        {
            Point p(10);
            p[0] = p[2] = p[4] = p[8] = 6.705;
            Cluster c;

            for (int i = 0; i < 10; i ++) {
                Point pp(10);
                for (int j = 0; j < 10; j ++) {
                    pp[i] = 3.4 + i * 2.1 + i * i;
                }
                c.add(pp);
            }
            c.add(p);

            pass = c.contains(p);

            ec.result(pass);
        }
    }
}

// Copy constructor
void test_cluster_copying(ErrorContext &ec, unsigned int numRuns) {
    bool pass;

    // Run at least once!!
    assert(numRuns > 0);

    ec.DESC("--- Test - Cluster - Copy ---");

    for (int run = 0; run < numRuns; run++) {

        ec.DESC("simple copy");

        {
            Point   p1(10),
                    p2(10),
                    p3(10);
            Cluster c1;
            c1.add(p1); c1.add(p2); c1.add(p3);
            Cluster c2(c1);

            pass = (c1 == c2);

            ec.result(pass);
        }

        ec.DESC("chained copy");

        {
            Point   p1(10),
                    p2(10),
                    p3(10);
            Cluster c1;
            c1.add(p1); c1.add(p2); c1.add(p3);
            Cluster c2(c1), c3(c2), c4(c3);

            pass = (c1 == c4);

            ec.result(pass);
        }
    }
}

// operator=
void test_cluster_assignment(ErrorContext &ec, unsigned int numRuns) {
    bool pass;

    // Run at least once!!
    assert(numRuns > 0);

    ec.DESC("--- Test - Cluster - Assign ---");

    for (int run = 0; run < numRuns; run++) {

        ec.DESC("simple assignment");

        {
            Point   p1(10),
                    p2(10),
                    p3(10);

            Cluster c1;
            c1.add(p1); c1.add(p2); c1.add(p3);
            Cluster c2 = c1;

            pass = (c1 == c2);

            ec.result(pass);
        }


        ec.DESC("assignment causing deletion");

        {
            Point   p1(10),
                    p2(10),
                    p3(10);

            Cluster c1;
            c1.add(p1); c1.add(p2); c1.add(p3);
            Cluster c2;
            // add some other points
            c2.add(Point(10));
            c2.add(Point(10));
            c2.add(Point(10));

            c2 = c1;

            pass = (c1 == c2);

            ec.result(pass);
        }

        ec.DESC("chained assignment");

        {
            Point   p1(10),
                    p2(10),
                    p3(10);

            Cluster c1;
            c1.add(p1); c1.add(p2); c1.add(p3);
            Cluster c2 = c1;
            Cluster c3 = c2;
            Cluster c4 = c3;

            pass = (c1 == c4);

            ec.result(pass);
        }
    }
}

// subscript (operator[])
void test_cluster_subscript(ErrorContext &ec, unsigned int numRuns) {
    bool pass;

    // Run at least once!!
    assert(numRuns > 0);

    ec.DESC("--- Test - Cluster - Subscript ---");

    for (int run = 0; run < numRuns; run++) {

        ec.DESC("cluster with one point");

        {
            Cluster c;
            Point p(10);
            p[5] = 3.14;

            c.add(p);
            Point p1 = c[0];

            pass = p1[5] == 3.14;

            ec.result(pass);
        }

        ec.DESC("cluster with several points");

        {
            Cluster c;
            for (int i = 0; i < 10; i ++) {
                Point p(10);
                p[5] = 3.14;
                c.add(p);
            }

            pass = true;
            for (int i = 0; i < 10; i ++) {
                Point p1 = c[i];
                pass = pass && (p1[5] == 3.14);
            }

            ec.result(pass);
        }
    }
}

// operator==, operator!=
void test_cluster_equality(ErrorContext &ec, unsigned int numRuns) {
    bool pass;

    // Run at least once!!
    assert(numRuns > 0);

    ec.DESC("--- Test - Cluster - Equal ---");

    for (int run = 0; run < numRuns; run++) {

        ec.DESC("check operator== is not a dummy");

        {
            // The requirements don't provide for many other methods that
            // can be used for testing, so operator== is checked first
            Cluster c1, c2;
            c1.add(Point(100));

            pass = !(c1 == c2);

            ec.result(pass);
        }

        ec.DESC("check inequality");

        {
            // The requirements don't provide for many other methods that
            // can be used for testing, so operator== is checked first
            Cluster c1, c2;
            c1.add(Point(100));

            pass = (c1 != c2);

            ec.result(pass);
        }
    }
}

// ascending pseudo-lexicographic order
void test_cluster_order(ErrorContext &ec, unsigned int numRuns) {
    bool pass;

    // Run at least once!!
    assert(numRuns > 0);

    ec.DESC("--- Test - Cluster - Order ---");

    for (int run = 0; run < numRuns; run++) {

        ec.DESC("points in a cluster are sorted");

        {
            Point p1(5), p2(5), p3(5), p4(5), p5(5);
            p1[0] = 1;
            p2[1] = 1;
            p3[2] = 1;
            p4[3] = 1;
            p5[4] = 1;

            Cluster c;
            c.add(p1);
            c.add(p2);
            c.add(p4);
            c.add(p3);
            c.add(p5);

            pass = (c[0] == p5)
                   && (c[1] == p4)
                   && (c[2] == p3)
                   && (c[3] == p2)
                   && (c[4] == p1);

            if (!pass) {
                std::cout << std::endl;
                std::cout << c << std::endl;
                std::cout << std::endl;
            }

            ec.result(pass);
        }

        ec.DESC("ascending pseudo-lexicographic order");

        {
            Point p1(5), p2(5), p3(5), p4(5), p5(5);
            p1[0] = 1;
            p2[1] = 1;
            p3[2] = -1;
            p4[3] = 1;
            p5[4] = -1;

            Cluster c;
            c.add(p1);
            c.add(p2);
            c.add(p4);
            c.add(p3);
            c.add(p5);

            pass = (c[0] == p3)
                   && (c[1] == p5)
                   && (c[2] == p4)
                   && (c[3] == p2)
                   && (c[4] == p1);

            if (!pass) {
                std::cout << std::endl;
                std::cout << c << std::endl;
                std::cout << std::endl;
            }

            ec.result(pass);
        }
    }
}

// operator+=, operator-=, different rhs
void test_cluster_CAO(ErrorContext &ec, unsigned int numRuns) {
    bool pass;

    // Run at least once!!
    assert(numRuns > 0);

    ec.DESC("--- Test - Cluster - Compound arithmetic ---");

    for (int run = 0; run < numRuns; run++) {

        ec.DESC("plus equals (Cluster and Point) check with non-equality");

        {
            Cluster c1, c2;
            Point p1(50);

            for (int i = 0; i < 50; i++)
                p1[i] = 6.75 * i * i + 5.45 * i + 1.15;

            c1 += p1;

            pass = !(c1 == c2);

            ec.result(pass);
        }

        ec.DESC("plus equals (Cluster and Point) check with size getter");

        {
            Cluster c1;
            Point p1(50);

            for (int i = 0; i < 50; i++)
                p1[i] = 6.75 * i * i + 5.45 * i + 1.15;

            c1 += p1;

            pass = (c1.getSize() == 1);

            ec.result(pass);
        }

        ec.DESC("minus equals (Cluster and Point) check with non-equality");

        {
            Cluster c1, c2;
            Point p1(50);

            for (int i = 0; i < 50; i++)
                p1[i] = 6.75 * i * i + 5.45 * i + 1.15;

            c1 += p1;
            pass = !(c1 == c2);

            c1 -= p1;
            pass = (c1 == c2);

            ec.result(pass);
        }

        ec.DESC("minus equals (Cluster and Point) check with size getter");

        {
            Cluster c1;
            Point p1(50);

            for (int i = 0; i < 50; i++)
                p1[i] = 6.75 * i * i + 5.45 * i + 1.15;

            c1 += p1;
            pass = (c1.getSize() == 1);

            c1 -= p1;
            pass = (c1.getSize() == 0);

            ec.result(pass);
        }

        ec.DESC("plus equals (Cluster union) no common points");

        {
            Cluster c1, c2, c3;
            Point   p1(50),
                    p2(50),
                    p3(50),
                    p4(50),
                    p5(50);
            c1.add(p1); c1.add(p2); c1.add(p3);
            c2.add(p4); c2.add(p5);

            // create a union to compare to
            c3.add(p1); c3.add(p2); c3.add(p3);
            c3.add(p4); c3.add(p5);

            c1 += c2;

            pass = (c1 == c3);

            ec.result(pass);
        }

        ec.DESC("plus equals (Cluster union) one common point");

        {
            Cluster c1, c2, c3;
            Point   p1(50),
                    p2(50),
                    p3(50),
                    p4(50),
                    p5(50);
            c1.add(p1); c1.add(p2); c1.add(p3);
            c2.add(p3); c2.add(p4); c2.add(p5);

            // create a union to compare to
            c3.add(p1); c3.add(p2); c3.add(p3);
            c3.add(p4); c3.add(p5);

            c1 += c2;

            pass = (c1 == c3);

            ec.result(pass);
        }

        ec.DESC("plus equals (Cluster union) two equal clusters");

        {
            Cluster c1, c2;
            Point   p1(50),
                    p2(50),
                    p3(50),
                    p4(50),
                    p5(50);
            c1.add(p1); c1.add(p2); c1.add(p3); c1.add(p4); c1.add(p5);
            c2.add(p1); c2.add(p2); c2.add(p3); c2.add(p4); c2.add(p5);

            c1 += c2;

            pass = (c1 == c2);

            ec.result(pass);
        }

        ec.DESC("minus equals (asymmetric Cluster difference) no common points");

        {
            Cluster c1, c2, c3;
            Point   p1(50),
                    p2(50),
                    p3(50),
                    p4(50),
                    p5(50);
            c1.add(p1); c1.add(p2); c1.add(p3);
            c2.add(p4); c2.add(p5);

            c3 = c1;
            c1 -= c2;

            pass = (c1 == c3);

            ec.result(pass);
        }

        ec.DESC("minus equals (asymmetric Cluster difference) one common point");

        {
            Cluster c1, c2, c3;
            Point   p1(50),
                    p2(50),
                    p3(50),
                    p4(50),
                    p5(50);
            c1.add(p1); c1.add(p2); c1.add(p3);
            c2.add(p3); c2.add(p4); c2.add(p5);

            // Prepare a difference to compare to
            c3.add(p1); c3.add(p2);
            c1 -= c2;

            pass = (c1 == c3);

            ec.result(pass);
        }

        ec.DESC("minus equals (asymmetric Cluster difference) two equal clusters");

        {
            Cluster c1, c2, c3;
            Point   p1(50),
                    p2(50),
                    p3(50),
                    p4(50),
                    p5(50);
            c1.add(p1); c1.add(p2); c1.add(p3); c1.add(p4); c1.add(p5);
            c2.add(p1); c2.add(p2); c2.add(p3); c2.add(p4); c2.add(p5);

            c1 -= c2;

            pass = (c1 == c3); // c1 should be empty

            ec.result(pass);
        }
    }
}

// operator+, operator-, different rhs
void test_cluster_SAO(ErrorContext &ec, unsigned int numRuns) {
    bool pass;

    // Run at least once!!
    assert(numRuns > 0);

    ec.DESC("--- Test - Cluster - Simple arithmetic ---");

    for (int run = 0; run < numRuns; run++) {

        ec.DESC("plus (Cluster and Point)");

        {
            Cluster c1, c2;
            Point   p1(50),
                    p2(50),
                    p3(50),
                    p4(50);
            c1.add(p1); c1.add(p2); c1.add(p3);

            c2 = c1; c2.add(p4);
            Cluster c3 = c1 + p4;

            pass = (c3 == c2);

            ec.result(pass);

        }

        ec.DESC("minus (Cluster and Point)");

        {
            Cluster c1, c2;
            Point   p1(50),
                    p2(50),
                    p3(50),
                    p4(50);
            c1.add(p1); c1.add(p2); c1.add(p3); c1.add(p4);

            c2 = c1; c2.remove(p4);
            Cluster c3 = c1 - p4;

            pass = (c3 == c2);

            ec.result(pass);
        }

        ec.DESC("plus (Cluster union)");

        {
            Cluster c1, c2;
            Point   p1(50),
                    p2(50),
                    p3(50),
                    p4(50),
                    p5(50);
            c1.add(p1); c1.add(p2); c1.add(p3);
            c2.add(p4); c2.add(p5);

            Cluster c3;
            c3.add(p1); c3.add(p2); c3.add(p3); c3.add(p4); c3.add(p5);

            Cluster c4 = c1 + c2;

            pass = (c4 == c3);

            ec.result(pass);
        }

        ec.DESC("minus (Cluster difference)");

        {
            Cluster c1, c2;
            Point   p1(50),
                    p2(50),
                    p3(50),
                    p4(50),
                    p5(50);
            c1.add(p1); c1.add(p2); c1.add(p3);
            c2.add(p3); c2.add(p4); c2.add(p5);

            Cluster c3;
            c3.add(p1); c3.add(p2);

            Cluster c4 = c1 - c2;

            pass = (c4 == c3);

            ec.result(pass);
        }
    }
}

// operator>>, operator<<
void test_cluster_IO(ErrorContext &ec, unsigned int numRuns) {
    bool pass;

    // Run at least once!!
    assert(numRuns > 0);

    ec.DESC("--- Test - Cluster - Stream IO ---");

    for (int run = 0; run < numRuns; run++) {

        ec.DESC("read from a file");

        {
            std::ifstream csv("points.csv");
            Cluster c;
            if (csv.is_open()) {
                csv >> c;
                csv.close();
            }
            pass = (c.getSize() == 4);

            ec.result(pass);
        }

        ec.DESC("read, write, and read again");

        {
            std::ifstream csv("points.csv");
            Cluster c;
            if (csv.is_open()) {
                csv >> c;
                csv.close();
            }
            pass = (c.getSize() == 4);

            // add a point
            c.add(Point(5));

            std::ofstream csv1("points1.csv", std::ofstream::out);

            csv1 << c;
            csv1.close();

            std::ifstream csv2("points1.csv");
            Cluster c2;
            if (csv2.is_open()) {
                csv2 >> c2;
                csv2.close();
            }
            pass = pass && (c2.getSize() == 5);

            ec.result(pass);
        }
    }
}
