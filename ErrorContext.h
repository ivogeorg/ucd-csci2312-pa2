//
// Created by Ivo Georgiev on 11/13/15.
//

#ifndef CLUSTERING_ERRORCONTEXT_H
#define CLUSTERING_ERRORCONTEXT_H


/**
 * Acknowledgement: Donnie Pinkston, CALTECH
 */

#include <iostream>
#include <set>
#include <sstream>

namespace Testing {

    using std::set;
    using std::ostream;
    using std::string;

    class ErrorContext              // displays test results
    {
    public:
        ErrorContext(ostream &os);              // write header to stream
        void desc(const char *msg, int line);   // write line/description
        void desc(string msg, int line);

        void result(bool good);                 // write test result
        ~ErrorContext();                        // write summary info
        bool ok() const;                        // true iff all tests passed

    private:
        ostream &os;                            // output stream to use
        int passed;                             // # of tests which passed
        int total;                              // total # of tests
        int lastline;                           // line # of most recent test
        set<int> badlines;                      // line #'s of failed tests
        bool skip;                              // skip a line before title?
    };

}


#endif //CLUSTERING_ERRORCONTEXT_H
