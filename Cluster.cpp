//
// Created by HosZul on 2/26/2016.
// Resubmission: Due by 5/1/16
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

using namespace std;
using namespace Clustering;

namespace Clustering
{

    //Step 1
    // Typedef
    //typedef Point *PointPtr;

    // LNode in ascending order
    // Nodes
    //Correct
    LNode::LNode(const Point & p, LNodePtr n): point(p)
    {
        point= p;
        next= n;
    }

    // Step 2
    // Cluster
    // Correct
    Clustering::Cluster::Cluster()
    {
        __points = nullptr;
        __size = 0;
    }

    // Added
    int Clustering::Cluster::getSize() const
    {
        return __size;
    }

    Clustering::Cluster::Cluster(const Cluster & rtpt):Cluster()
    {
        for (int count = 0; count < rtpt.__size; count++)
            
            add(rtpt[count]);
    }


    // Assignment
    // Correct
    Cluster &Clustering::Cluster::operator=(const Cluster &rtpt)
    {
        LNodePtr currPtr;

        if(this == &rtpt)
            return *this;

        else
        {
            if(__points != nullptr)
            {
                LNodePtr currPtr = __points;
                LNodePtr nextPtr = nullptr;

                while(currPtr != nullptr)
                {
                    nextPtr = currPtr->next;
                    delete currPtr;
                    currPtr = nextPtr;
                }

                __points = nullptr;
                __size = 0;
            }

            for(int i = 0; i < rtpt.__size; ++i)
            {
                add(rtpt[i]);
            }
        }
        return *this;
    }

    // index and point
    const Point &Cluster::operator[](unsigned int index) const {
        if (__points != NULL)
        {
            LNodePtr cursor = __points;

            for (int i = 0; i < index; ++i)
            {
                cursor = cursor -> next;
            }
            return cursor->point;
        }
    }

    // Empties nodes
    Cluster::~Cluster()
    {
        if (__points != nullptr)
        {
            LNodePtr pPtr = __points;
            LNodePtr cPtr = nullptr;

            while (pPtr != nullptr)
            {
                cPtr = pPtr->next;
                delete cPtr;
                pPtr = cPtr;
            }
        }
        else
            assert(__size == 0);
    }

    // Added Postcondition
    // Correct
    void Clustering::Cluster::add(const Point &point)
    {
        LNodePtr insertPtr = new LNode(point, nullptr);
        LNodePtr cPtr=__points;
        LNodePtr pPtr=__points;

        if(__points==nullptr)
        {
            __points = insertPtr;
            __size++;

            return;
        }

        else if(__points->next==nullptr)
        {
            if(point<__points->point)
            {
                __points=insertPtr;
                insertPtr->next = pPtr;
                __size++;

                return;
            }

            else
            {
                __points->next=insertPtr;
                __size++;

                return;
            }
        }

        else
        {
            cPtr=cPtr->next;
            if(point < pPtr->point)
            {
                __points = insertPtr;
                insertPtr->next = pPtr;
                __size++;

                return;
            }

            while(cPtr!=nullptr)
            {
                if(point < cPtr->point)
                {
                    pPtr->next = insertPtr;
                    insertPtr->next = cPtr;
                    __size++;

                    return;
                }
                cPtr = cPtr->next;
                pPtr = pPtr->next;
            }

            pPtr->next = insertPtr;
            __size++;
        }
    }

    // Remove
    // Correct
    const Point &Clustering::Cluster::remove(const Point &point)
    {
        LNodePtr cPtr=__points;
        LNodePtr pPtr=__points;

        if(__points==nullptr)
            return point;

        else if(__points->point == point)
        {
            cPtr=__points;
            __points=__points->next;
            delete cPtr;

            __size--;
        }

        else
        {
            cPtr=cPtr->next;

            while (cPtr!= nullptr)
            {
                if (cPtr->point == point)
                {
                    pPtr->next = cPtr->next;
                    delete cPtr;

                    __size--;

                    break;
                }

                cPtr = cPtr->next;
                pPtr = pPtr->next;
            }
        }
        return point;
    }

    // For cluster
    //correct
    bool Cluster::contains(const Point &point)
    {
        LNodePtr next = __points;

        while (next != nullptr)
        {
            if (next->point == point)
                return true;

            next = next->next;
        }
        return false;
    }

    // Correct
    bool operator==(const Cluster &c1, const Cluster &c2)
    {
        LNodePtr cr1= c1.__points;
        LNodePtr cr2=c2.__points;

        bool same=true;
        if (c1.__size != c2.__size)
            same=false;

        while(cr1!=nullptr && cr2!=nullptr)
        {
            if(cr1->point!=cr2->point)
                same=false;
            cr1=cr1->next;
            cr2=cr2->next;
        }
        return same;
    }

    // COrrect
    bool operator!=(const Cluster &c1, const Cluster &c2)
    {
        return (!(c1==c2));
    }

    // Adds point
    // Correct
    Cluster &Clustering::Cluster::operator+=(const Point &point)
    {
        add(point);

        return *this;
    }

    // Removes Point
    // Correct
    Cluster &Clustering::Cluster::operator-=(const Point &point)
    {
        remove(point);

        return *this;
    }

    // New Cluster with add
    // Correct
    const Cluster operator+(const Cluster & c1, const Point &point)
    {
        Cluster c2(c1);
        c2+= point;

        return c2;
    }


    // New Cluster with Subtract
    // Correct
    const Cluster operator-(const Cluster & c1, const Point &point)
    {
        Cluster c2(c1);
        c2-= point;

        return c2;
    }

    // Unique points from Passed
    // Correct
    Cluster &Clustering::Cluster::operator+=(const Cluster & c1)
    {

        for (int count = 0; count < c1.__size; count++)
        {
            if (!contains(c1[count]))
                add(c1[count]);
        }
        return *this;
    }

    // Removes
    // Correct
    Cluster &Clustering::Cluster::operator-=(const Cluster &c1)
    {
        for (int count = 0; count < c1.__size; count++)
        {
            if (contains(c1[count]))
                remove(c1[count]);
        }
            return *this;
    }

    // New clusters fr Unique
    // Correct
    const Cluster operator+(const Cluster &c1, const Cluster &c2)
    {
        Cluster cr1(c1);
        cr1+=c2;
        
        return cr1;
    }
    
    // Similar
    // COrrect
    const Cluster operator-(const Cluster &c1, const Cluster &c2)
    {
        Cluster cr1(c1);
        cr1-=c2;
        
        return cr1;
    }
    
    
    // Ostream
    // COrrect
    std::ostream &operator<<(std::ostream &os, const Cluster &c1)
    {
        LNodePtr cursor = c1.__points;

        for(int index = 0; index < c1.__size; index++)
        {
            os << cursor->point;
            cursor = cursor->next;
        }
        return os;
    }

    // Istream
    // Correct
    std::istream &operator>>(std::istream &is, Cluster &c1)
    {
        std::string line;
       
        while (getline(is,line)) 
        {
            if (line.empty()) 
            {
                return is;
            }

            int count = std::count(line.begin(), line.end(), ',');

            Point *point = new Clustering::Point( count + 1);
            std::stringstream lineStream(line);

            lineStream >> *point;

            c1.add(*point);
        }
        return is;
    }

}