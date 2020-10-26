/* 
 * File:   Color.h
 * Author: ritoban
 *
 * Created on October 25, 2020, 7:26 PM
 */

#include <map>
#include <string>
#include <cinttypes>

#ifndef COLOR_H
#define COLOR_H


/* This class represents a Color -- specicially a 4 bit color based on ANSI escape sequences. See https://stackoverflow.com/questions/4842424/list-of-ansi-color-escape-sequences for more info */
class Color {
public:
    Color() { };
    //Color(std::string);
    Color(uint8_t);
    Color(const Color& orig);

    virtual ~Color();

    uint8_t AsFG() { return inner + 30; }
    uint8_t AsBG() { return inner + 40; }
    static std::map<std::string, Color> CreateColorMap();


    uint8_t inner;
};

extern std::map<std::string, Color> COLOR;


#endif /* COLOR_H */

