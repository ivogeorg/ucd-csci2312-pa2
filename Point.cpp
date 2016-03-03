//
// Created by HosZul on 2/26/2016.
//

#include "Point.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cmath>



//fstream
using std::ifstream;

// sstream
using std::stringstream;
using std::string;

// Other
using std::cout;
using std::endl;
using std::setprecision;
using std::stringstream;
using std::string;

namespace Clustering {
    unsigned int Point::__idGen = 0;

    // Constructors
    Point::Point(int dim) {
        __id = __idGen;
        __idGen++;
        __dim = dim;

        __values = new double[__dim];

        for (int i = 0; i < __dim; ++i) {
            __values[i] = 0;
        }
    }

    // Dimensions of Points
    Point::Point(int dim, double *values) {
        __id = __idGen;
        __idGen++;
        __dim = dim;
        __values = values;
    }

    // Constructor: Copy
    Point::Point(const Point &point) {
        __dim = point.getDims();
        __id = point.getId();
        __values = new double[point.getDims()];

        for (int i = 0; i < point.getDims(); ++i)
            setValue(i, point.getValue(i));
    }

    // Assignment
    Point &Point::operator=(const Point &point) {
        for (int i = 0; i < __dim; i++) {
            this->__values[i] = point.getValue(i);
        }

        return *this;
    }

    //  Copy Deconstructor
    Point::~Point() {
        delete[] __values;
    }

    // Mutator and Accessor
    int Point::getId() const {
        return __id;
    }

    int Point::getDims() const {
        return __dim;
    }

    void Point::setValue(int i, double n) {
        __values[i] = n;
    }

    // Point functions
    double Point::getValue(int i) const {
        return __values[i];
    }

    double Point::distanceTo(const Point &point) const {
        double arbitraryDistance = 0;

        for (int i = 0; i < __dim; ++i) {
            arbitraryDistance += (__values[i] - point.__values[i]) * (__values[i] - point.__values[i]);
        }

        return sqrt(arbitraryDistance);
    }

    // Overloaded members
    Point &Point::operator*=(double a) {
        for (int i = 0; i < __dim; ++i)
            __values[i] *= a;

        return *this;
    }

    Point &Point::operator/=(double a) {
        for (int count = 0; count < __dim; ++count)
            __values[count] /= a;

        return *this;
    }

    const Point Point::operator*(double a) const {
        Point cp(*this);

        for (int count = 0; count < __dim; ++count)
            cp[count] *= a;

        return cp;
    }

    const Point Point::operator/(double a) const {
        Point cp(*this);

        for (int i = 0; i < __dim; ++i)
            cp[i] *= a;

        return cp;
    }

    double &Point::operator[](int index) {
        return __values[index];
    }

    Point &operator+=(Point &point, const Point &p1) {
        for (int i = 0; i < point.__dim; ++i)
            point.__values[i] += p1.__values[i];

        return point;
    }

    Point &operator-=(Point &point, const Point &p1) {
        for (int i = 0; i < point.__dim; ++i)
            point.__values[i] -= p1.__values[i];

        return point;
    }

    const Point operator+(const Point &p1, const Point &p2) {
        Point p0(p1.getDims());

        for (int i = 0; i < p1.__dim; ++i)
            p0.__values[i] = (p1.__values[i] + p2.__values[i]);

        return p0;
    }

    const Point operator-(const Point &p1, const Point &p2) {
        Point p0(p1.getDims());
        return p0;
    }

    bool operator==(const Point &p1, const Point &p2) {
        bool condition = true;

        if (p1.__id != p2.__id)
            condition = false;

        else {
            for (int i = 0; i < p1.__dim; ++i)
                if (p1.__values[i] != p2.__values[i])
                    condition = false;

        }
        return condition;
    }

    bool operator!=(const Point &p1, const Point &p2) {
        if (p1.__id != p2.__id) return true;
        if (p1.__dim == p2.__dim) {
            for (int i = 0; i < p1.__dim; ++i) {
                if (p1.__values[i] != p2.__values[i]) return true;
            }
            return false;
        }
        return true;
    }


    bool operator<(const Point &p1, const Point &p2) {
        if (p1.__dim == p2.__dim) {
            for (int i = 0; i < p1.__dim; ++i) {
                if (p1.__values[i] < p2.__values[i])
                    return true;
            }
        }
        return false;
    }

    bool operator>(const Point &p1, const Point &p2) {
        if (p1.__dim == p2.__dim) {
            for (int i = 0; i < p1.__dim; ++i) {
                if (p1.__values[i] > p2.__values[i])
                    return true;
            }
        }
        return false;
    }

    bool operator<=(const Point &p1, const Point &p2) {
        if (p1.__dim == p2.__dim) {
            for (int i = 0; i < p1.__dim; ++i) {
                if (p1.__values[i] >= p2.__values[i])
                    return true;
            }
        }
        return false;
    }

    std::ostream &operator<<(std::ostream &os, const Point &point) {
        int i;

        for (i = 0; i < point.__dim - 1; ++i)
            os << point.__values[i] << ", ";
        os << point.__values[i];

        os << endl;
        return os;
    }

    std::istream &operator>>(std::istream &is, const Point &p1) {
        int i = 0;

        std::string temp;

        double a;

        while(getline(is, temp, ','))
        {
            a = atof(temp.c_str());
            (i++, a);
        }
        return is;
    }
}