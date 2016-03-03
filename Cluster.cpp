//
// Created by HosZul on 2/26/2016.
//

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
#include <sstream>
#include <assert.h>
#include <algorithm>

// .h files
#include "Cluster.h"

using namespace Clustering;
using Clustering::Point;

namespace Clustering {

    //Step 1
    // Typedef
    typedef Point *PointPtr;

    // LNode in ascending order
    // Nodes
    LNode::LNode(const Point &p, LNodePtr n = nullptr) : point(p) {
        next = n;
        point = p;
    }

    // Step 2
    // Cluster
    Cluster::Cluster() {
        __points = nullptr;
        __size = 0;
    }

    // Gone over in class
    Cluster::Cluster(const Cluster &cluster1) : Cluster() {
        if (cluster1.__points == NULL) {
            __size = 0;
            __points = NULL;
        }

        else {
            __size = 0;

            // LNode and points
            LNodePtr prevptr = cluster1.__points;

            // New Point
            PointPtr createPoint;
            createPoint = new Point(cluster1.__points->point);
            __points = new LNode(*createPoint, NULL);
            ++__size;

            // Pointer lists
            LNodePtr currptr = __points;
            LNodePtr lastptr = currptr;
            prevptr = prevptr->next;

            for (; prevptr != NULL; prevptr = prevptr->next) {
                createPoint = new Point(prevptr->point);
                currptr = new LNode(*createPoint, NULL);
                lastptr->next = currptr;
                ++__size;
                lastptr = currptr;
            }
        }
    }

    // Assignment
    Cluster &Cluster::operator=(const Cluster &c) {
        if (this == &c)
            return *this;

        else {
            if (__points != nullptr) {
                LNodePtr currptr = __points;
                LNodePtr nextptr = currptr->next;

                while (currptr != nullptr) {
                    nextptr = currptr->next;
                    delete currptr;
                    currptr = nextptr;
                }
                __size = 0;
                __points = nullptr;
            }
            for (int count = 0; count < c.__size; ++count) {
                add(c[count]);

            }
        }
        return *this;
    }

    // Empties nodes
    Cluster::~Cluster() {
        if (__points != nullptr) {
            LNodePtr prevptr = __points;
            LNodePtr currptr = nullptr;

            while (prevptr != nullptr) {
                currptr = prevptr->next;
                delete prevptr;
                prevptr = currptr;
            }
        }
        else
            assert(__size == 0);
    }

    int Cluster::getSize() const {
        return __size;
    }

    // Step 5
    // Helper
    bool operator==(const Cluster &c1, const Cluster &c2) {
        if (c1.__size != c2.__size)
            return false;

        LNodePtr cr1 = c1.__points;
        LNodePtr cr2 = c2.__points;

        bool condition = true;

        while (cr1 != nullptr && cr2 != nullptr) {
            if (cr1->point != cr2->point) condition = false;

            cr1 = cr1->next;
            cr2 = cr2->next;
        }
        return condition;
    }

    //Add post
    // Step 6
    void Cluster::add(const Point &point) {
        Point pp(point);

        LNodePtr addptr = new LNode(pp, nullptr);
        LNodePtr prev = __points;
        LNodePtr next = __points;

        if (__points == nullptr) {
            __points = nullptr;
            __points = addptr;
            __size++;
        }

        else if (__points->next == nullptr) {
            if (point < __points->point) {
                __points = addptr;
                addptr->next = prev;
                __size++;
            }
            else {
                __points->next = addptr;
                __size++;
            }
        }

        else {
            next = next->next;

            if (point < prev->point) {
                __points = addptr;
                addptr->next = next;
                __size++;
                return;
            }
            next = next->next;
            prev = prev->next;
        }
        prev->next = addptr;
        __size++;
    }

    const Point &Cluster::remove(const Point &point) {
        LNodePtr currptr = __points;
        LNodePtr addptr = __points;

        if (__points->point == point) {
            __points = __points->next;
            delete addptr;
            __size--;
        }


        else {
            currptr = __points;
            addptr = __points->next;

            while (addptr != nullptr) {
                if (addptr->point == point) {
                    addptr->next = addptr->next;
                    delete addptr;
                    __size--;

                    break;
                }
                addptr = addptr;
                addptr = addptr->next;
            }
        }
        return point;
    }

    // For cluster
    bool Cluster::contains(const Point &point) {
        LNodePtr next = __points;

        while (next != nullptr) {
            if (next->point == point)
                return true;

            next = next->next;
        }
        return false;
    }

    // index and point
    const Point &Cluster::operator[](unsigned int index) const {
        if (__points != NULL) {
            LNodePtr cursor = __points;

            for (int i = 0; i < index; ++i) {
                cursor = cursor->next;
            }
            return cursor->point;
        }
    }

    bool operator!=(const Cluster &cluster, const Cluster &cluster1) {
        return (!(cluster == cluster1));
    }

    // Adds cluster point
    Cluster &Cluster::operator+=(const Point &point) {
        add(point);

        return *this;
    }

    // Removes cluster point
    Cluster &Cluster::operator-=(const Point &point) {
        remove(point);

        return *this;
    }

    // For Unique points: addition
    Cluster &Cluster::operator+=(const Cluster &arg_Cluster) {
        LNodePtr cr1 = arg_Cluster.__points;

        for (; cr1 != NULL; cr1 = cr1->next) {
            if (!(this->contains(cr1->point)))
                add(cr1->point);
        }

        return *this;
    }

    // For Unique points; subtraction
    Cluster &Cluster::operator-=(const Cluster &cr1) {
        for (int i = 0; i < cr1.getSize(); ++i) {
            remove(cr1[i]);
        }

        return *this;
    }

    // ostream
    std::ostream &operator<<(std::ostream &os, const Cluster &cluster1) {
        LNodePtr cursor = cluster1.__points;

        for (int count = 0; count < cluster1.__size; ++count) {
            os << cursor->point;
            cursor = cursor->next;
        }
        return os;
    }

    // istream
    std::istream &operator>>(std::istream &istream, Clustering::Cluster &cluster)
    {
        std::string line;

        while (getline(istream, line)) {

            int a = std::count(line.begin(), line.end(), ',');

            Point *ptPtr = new Clustering::Point(a + 1);

            std::stringstream lineStream(line);

            lineStream >> *ptPtr;

            cluster.add(*ptPtr);
        }
    }
}
