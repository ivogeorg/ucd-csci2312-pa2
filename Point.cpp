//
// Created by HosZul on 4/30/2016.
// Resubmission: Due by 5/1/2016

#include "Point.h"

#include <iomanip>
#include <fstream>
#include <sstream>
#include <cmath>

using namespace Clustering;

namespace Clustering
{

    unsigned int Point::__idGen = 0;

    // Constructors
    Point::Point(int newNum)
    {
        __id = __idGen;
        __idGen++;
        __dim = newNum;
        __values = new double[__dim];

        for (int i = 0; i < __dim; ++i)
        {
            __values[i] = 0;
        }
    }

    // Dimensions of Points
    Point::Point(int dim, double *values)
    {
        __id = __idGen;
        __idGen++;
        __dim = dim;
        __values = values;
    }

    // Constructor: Copy
    Point::Point(const Point &newPoint)
    {
        __dim = newPoint.getDims();
        __id = newPoint.getId();
        __values = new double[__dim];

        for (int i = 0; i < __dim; ++i)
            __values[i] = newPoint.__values[i];
    }

    // Assignment stopped here
    Point &Point::operator=(const Point &rtpt)
    {
        if (this != &rtpt)
            return *this;

        else
        {
            __dim = rtpt.__dim;

            for (int count = 0; count < __dim; count++)
                __values[count] = rtpt.__values[count];

            __id = rtpt.__id;
        }

        return *this;
    }

    //  Copy Deconstructor
    Point::~Point()
    {
        delete[] __values;
    }

    // Mutator and Accessor
    int Point::getId() const
    {
        return __id;
    }

    int Point::getDims() const
    {
        return __dim;
    }

    void Point::setValue(int i, double nP)
    {
        __values[i] = nP;
    }

    double Point::getValue(int i) const
    {
        return __values[i];
    }

    // Corrected
    double Point::distanceTo(const Point &point) const
    {
        double arbitraryDistance = 0.0;

        for (int count = 0; count < __dim; ++count)
        {
            arbitraryDistance += pow((__values[count] - point.__values[count]), 2);
        }

        arbitraryDistance = sqrt(arbitraryDistance);

        return arbitraryDistance;
    }

    // Overloaded members
    Point &Point::operator*=(double rtpt)
    {
        for (int i = 0; i < __dim; ++i)
            __values[i] *= rtpt;

        return *this;
    }

    Point &Point::operator/=(double pt)
    {
        for (int count = 0; count < __dim; ++count)
            __values[count] /= pt;

        return *this;
    }

    const Point Point::operator*(double pt) const
    {
        return Point(*this) *= pt;
    }

    const Point Point::operator/(double rtpt) const
    {
        return Point(*this) /= rtpt;
    }

    double &Point::operator[](int i)
    {
        return __values[i];
    }

    Point &operator+=(Point &ltpt, const Point &rtpt)
    {
        for (int count = 0; count < ltpt.__dim; ++count)
            ltpt.__values[count] += rtpt.__values[count];

        return ltpt;
    }

    Point &operator-=(Point &ltpt, const Point &rtpt)
    {
        for (int count = 0; count < ltpt.__dim; ++count)
            ltpt.__values[count] -= rtpt.__values[count];

        return ltpt;
    }

    const Point operator+(const Point &ltpt, const Point &rtpt)
    {
        Point p(ltpt);

        p += rtpt;

        return p;
    }

    const Point operator-(const Point &ltpt, const Point &rtpt)
    {
        Point p(ltpt);
        p -= rtpt;

        return p;
    }

    // Bool
    // Correct
    bool operator==(const Point &ltpt, const Point &rtpt)
    {
        bool same = true;

        if(ltpt.__id != rtpt.__id)
            same = false;
        else
        {
            for (int count = 0; count < ltpt.__dim; ++count)
                if (ltpt.__values[count] != rtpt.__values[count])
                    same = false;
        }

        return same;
    }

    bool operator!=(const Point &ltpt, const Point &rtpt)
    {
        return(!(ltpt == rtpt));
    }

    bool operator<(const Point &ltpt, const Point &rtpt)
    {
        bool notSame = false;

        for (int count = 0; count < ltpt.__dim; ++count)
        {
            if (ltpt.__values[count] < rtpt.__values[count])
                return true;

            if (ltpt.__values[count] > rtpt.__values[count])
                return false;
        }
        return notSame;
    }

    // Correct
    bool operator>(const Point &ltpt, const Point &rtpt)
    {
        return operator<(rtpt, ltpt);
    }

    // Correct
    bool operator<=(const Point &ltpt, const Point &rtpt)
    {
        for (int count = 0; count < ltpt.__dim; ++count)

            if (ltpt.__values[count] <= rtpt.__values[count])
                return true;
        return false;
    }

    //Correct
    bool operator>=(const Point &ltpt, const Point &rtpt)
    {
        for (int count = 0; count < ltpt.__dim; ++count)

            if (ltpt.__values[count] >= rtpt.__values[count])
                return true;

        return false;
    }

    // Correct
    std::ostream &operator << (std::ostream &os, const Point &point)
    {
        int i;

        for (i = 0; i < point.__dim - 1; ++i)
            os << point.__values[i] << ", ";
        os << point.__values[i];

        os << std::endl;
        return os;
    }

    // COrrected
    std::istream &operator >> (std::istream &is, Clustering::Point &point)
    {
        int i = 0;

        std::string temp;

        double d;

        while(getline(is, temp, ','))
        {
            d = atof(temp.c_str());
            point.setValue(i++, d);
        }

        return is;
    }
}