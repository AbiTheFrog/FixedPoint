/**
 *  Fixed Point Math Library
 *      Made by Abi The Frog
 *      Designed for use with TI84 calculators
 *          - ideally 24 bit value with 6 bits below point <24, 6>
 *          - should work on other platforms and with different bit layouts
 *      Change log  (d/m/y)
 *          Initial Code 2/3/2022
**/

#pragma once

#ifndef FixedPointLib
#define FixedPointLib

#define SCALE_FACTOR (bits * point)

/**
 *  Generic Fixed Point
 *      Used for generating fixed point types that can later be used
 *      @tparam bits number of bits for base type 'value'
 *      @tparam point number of bits in point (must be less than bits)
 *      @tparam expand is used as the type when doing operations to prevent overflows (default long)
**/
template<unsigned char bits, unsigned char point, typename expand = long>
struct GenericFixedPoint {
    long value : bits;

    /**
     *  Default Constructor
     *      ! Leaves value uninitialized
    **/
    GenericFixedPoint(){}

    /**
     *  Copy Constructor
     *      @param n a fixed point number of THE SAME TYPE (template-wise)
    **/
    GenericFixedPoint(const GenericFixedPoint<bits, point> n){
        value = n.value;
    }

    /**
     *  Floating Point Constructor
     *      @param n floating point number to convert
    **/
    GenericFixedPoint(float n){
        value = n * SCALE_FACTOR;
    }

    /**
     *  Integer Type Constructors
     *      ! May cause type problems
    **/
    GenericFixedPoint(char n){
        value = n;
        value << point;
    }

    GenericFixedPoint(int n){
        value = n;
        value << point;
    }

    GenericFixedPoint(long n){
        value = n;
        value << point;
    }

    /**
     *  Fixed <-> Fixed -> Fixed Operations
     *      ! only works on fixed point operations with the same type
    **/
    GenericFixedPoint<bits, point> operator +(const GenericFixedPoint<bits, point> n) const {
        GenericFixedPoint<bits, point> ret;
        ret.value = value + n.value;
        return ret;
    }

    GenericFixedPoint<bits, point> operator -(const GenericFixedPoint<bits, point> n) const {
        GenericFixedPoint<bits, point> ret;
        ret.value = value - n.value;
        return ret;
    }

    GenericFixedPoint<bits, point> operator *(const GenericFixedPoint<bits, point> n) const {
        GenericFixedPoint<bits, point> ret;
        ret.value = ((expand)value * n.value) / (1 << point);
        return ret;
    }

    GenericFixedPoint<bits, point> operator /(const GenericFixedPoint<bits, point> n) const {
        GenericFixedPoint<bits, point> ret;
        ret.value = ((expand)value << point) / n.value;
        return ret;
    }

    GenericFixedPoint<bits, point>& operator +=(const GenericFixedPoint<bits, point> n) {
        value += n.value;
        return *this;
    }

    GenericFixedPoint<bits, point>& operator -=(const GenericFixedPoint<bits, point> n) {
        value -= n.value;
        return *this;
    }

    GenericFixedPoint<bits, point>& operator *=(const GenericFixedPoint<bits, point> n){
        value = ((expand)value * n.value) / (1 << point);
        return *this;
    }

    GenericFixedPoint<bits, point>& operator /=(const GenericFixedPoint<bits, point> n){
        value = ((expand)value << point) / n.value;
        return *this;
    }

    /**
     *  Fixed <-> Fixed -> Boolean Operations
     *      ! only works on fixed point operations with the same type
    **/
    bool operator <(const GenericFixedPoint<bits, point> n){
        return value < n.value;
    }

    bool operator >(const GenericFixedPoint<bits, point> n){
        return value > n.value;
    }

    bool operator <=(const GenericFixedPoint<bits, point> n){
        return value <= n.value;
    }

    bool operator >(const GenericFixedPoint<bits, point> n){
        return value >= n.value;
    }

    bool operator ==(const GenericFixedPoint<bits, point> n){
        return value == n.value;
    }
};

#undef SCALE_FACTOR

#endif