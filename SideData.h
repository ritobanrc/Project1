/* 
 * File:   SideData.h
 * Author: ritoban
 *
 * Created on October 27, 2020, 3:11 PM
 */

#ifndef SIDEDATA_H
#define SIDEDATA_H

#include <string>

enum Side { white, black };

/// A small wrpaper class that represents a piece of data that exists for both sides, and a convience method for accessing the corect one. 
template<typename T>
class SideData {
    public:
        SideData(T white, T black) : whiteData(white), blackData(black) {
        }
        T whiteData;
        T blackData;

        T& Get(Side s) {
            if (s == white) {
                return this->whiteData;
            } else {
                return this->blackData;
            }
        }
};


#endif /* SIDEDATA_H */

