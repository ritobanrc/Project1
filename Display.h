/* 
 * File:   Display.h
 * Author: ritoban
 *
 * Created on October 25, 2020, 7:10 PM
 */

#ifndef DISPLAY_H
#define DISPLAY_H

#include <iostream>
#include "Color.h"

class Display {
    public:
      static void BeginBold() { std::cout << "\033[1m"; }

      static void BeginUnderline() { std::cout << "\033[4m"; }

      static void BeginColor(std::uint8_t col) { std::cout << "\033[" << unsigned(col) << "m"; }

      static void NewLine() { std::cout << std::endl; }

      static void EndFormat() { std::cout << "\033[0m"; }


      template <typename T> static void Print(T x) {
        std::cout << x;
      }

      template <typename T> static void PrintBold(T x) {
        Display::BeginBold();
        std::cout << x;
        Display::EndFormat();
      }

      template <typename T> static void PrintUnderlined(T x) {
        Display::BeginUnderline();
        std::cout << x;
        Display::EndFormat();
      }
};

#endif /* DISPLAY_H */

