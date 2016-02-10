#ifndef CLUSTERING_POINT_H
#define CLUSTERING_POINT_H

#include <iostream>

namespace Clustering {

    class Point {
        unsigned int __id;
        int __dim;        // number of dimensions of the point
        double *__values; // values of the point's dimensions

        static unsigned int __idGen; // id generator

    public:
        Point(int);
        Point(int, double *);

        // Big three: cpy ctor, overloaded operator=, dtor
        Point(const Point &);
        Point &operator=(const Point &);
        ~Point();

        // Accessors & mutators
        int getId() const;
        int getDims() const;
        void setValue(int, double);
        double getValue(int) const;

        // Functions
        double distanceTo(const Point &) const;

        // Overloaded operators

        // Members
        Point &operator*=(double); // p *= 6; p.operator*=(6);
        Point &operator/=(double);
        const Point operator*(double) const; // prevent (p1 * 2) = p2;
        const Point operator/(double) const; // p3 = p2 / 2;

        double &operator[](int index);

        // Friends
        friend Point &operator+=(Point &, const Point &);
        friend Point &operator-=(Point &, const Point &);
        friend const Point operator+(const Point &, const Point &);
        friend const Point operator-(const Point &, const Point &);

        friend bool operator==(const Point &, const Point &);
        friend bool operator!=(const Point &, const Point &);

        friend bool operator<(const Point &, const Point &);
        friend bool operator>(const Point &, const Point &);
        friend bool operator<=(const Point &, const Point &);
        friend bool operator>=(const Point &, const Point &);

        friend std::ostream &operator<<(std::ostream &, const Point &);
        friend std::istream &operator>>(std::istream &, Point &);
    };

}
#endif //CLUSTERING_POINT_H
