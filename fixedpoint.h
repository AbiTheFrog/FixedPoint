/**
 *  Fixed Point Library
 *      Made by Abi The Frog
 *      Designed for use with TI84 calculators
 *          - ideally 24 bit value with 6 bits below point <24, 6>
 *          - should work on other platforms and with different bit layouts
 *      Change log  (d/m/y)
 *          Initial Code 2/3/2022
 *          Version 1.0 3/3/2022
**/

#pragma once

#ifndef FixedPointLib
#define FixedPointLib

#define SCALE_FACTOR (1 << point)

/**
 *  Generic Fixed Point
 *      Used for generating fixed point types that can later be used
 *      @tparam bits number of bits for base type 'value' (must be <= to number of bits in expand type)
 *      @tparam point number of bits in point (must be less than bits)
 *      @tparam expand is used as the type when doing operations to prevent overflows (default long)
 *      @tparam integer defines the type used in all integer operations and conversions
**/
template<unsigned char bits, unsigned char point, typename expand = long, typename integer = int>
struct GenericFixedPoint {
    expand value : bits;

    /**
     *  Improves code readability
    **/
    typedef GenericFixedPoint<bits, point, expand, integer> FixedType;

    /**
     *  Default Constructor
     *      ! Leaves value uninitialized
    **/
    GenericFixedPoint(){}

    /**
     *  Copy Constructor
     *      @param n a fixed point number of THE SAME TYPE (template-wise)
    **/
    GenericFixedPoint(const FixedType& n){
        value = n.value;
    }

    /**
     *  Floating Point Constructor
     *      @param n floating point number to convert
    **/
    constexpr GenericFixedPoint(float n) : value(n * SCALE_FACTOR) {}

    /**
     *  Integer Type Constructors
     *      ! May cause type problems
     *      ! Can overflow
    **/
    GenericFixedPoint(integer n){
        value = n;
        value <<= point;
    }

    /**
     *  Fixed <-> Fixed -> Fixed Operations
     *      ! only works on fixed point operations with the same type
    **/
    FixedType operator +(const FixedType n) const {
        FixedType ret;
        ret.value = value + n.value;
        return ret;
    }

    FixedType operator -(const FixedType n) const {
        FixedType ret;
        ret.value = value - n.value;
        return ret;
    }

    FixedType operator *(const FixedType n) const {
        FixedType ret;
        ret.value = ((expand)value * n.value) / SCALE_FACTOR;
        return ret;
    }

    FixedType operator /(const FixedType n) const {
        FixedType ret;
        ret.value = ((expand)value << point) / n.value;
        return ret;
    }

    FixedType& operator +=(const FixedType n) {
        value += n.value;
        return *this;
    }

    FixedType& operator -=(const FixedType n) {
        value -= n.value;
        return *this;
    }

    FixedType& operator *=(const FixedType n){
        value = ((expand)value * n.value) / SCALE_FACTOR;
        return *this;
    }

    FixedType& operator /=(const FixedType n){
        value = ((expand)value << point) / n.value;
        return *this;
    }

    /**
     *  Fixed <-> Fixed -> Boolean Operations
     *      ! only works on fixed point operations with the same type
    **/
    bool operator <(const FixedType n) const {
        return value < n.value;
    }

    bool operator >(const FixedType n) const {
        return value > n.value;
    }

    bool operator <=(const FixedType n) const {
        return value <= n.value;
    }

    bool operator >=(const FixedType n) const {
        return value >= n.value;
    }

    bool operator ==(const FixedType n) const {
        return value == n.value;
    }

    /**
     *  Negation Fixed -> Fixed
     **/
    FixedType operator -() const {
        FixedType ret;
        ret.value = -value;
        return ret;
    }

    /**
     *  Conversions
    **/
    operator float() const {
        return (float)value / SCALE_FACTOR;
    }

    operator integer() const {
        return (integer)(value / SCALE_FACTOR);
    }

    /**
     *  Integer operations on fixed point numbers
    **/
    FixedType operator +(integer n) const {
        FixedType ret;
        ret.value = value + ((expand)n << point);
        return ret;
    }

    FixedType operator -(integer n) const {
        FixedType ret;
        ret.value = value - ((expand)n << point);
        return ret;
    }
    
    FixedType operator *(integer n) const {
        FixedType ret;
        ret.value = value * n;  // ((extend)value * (n * SCALE_FACTOR)) / SCALE_FACTOR;
        return ret;
    }

    FixedType operator /(integer n) const {
        FixedType ret;
        ret.value = value / n; // ((extend)value * SCALE_FACTOR) / (n * SCALE_FACTOR);
        return ret;
    }

    FixedType& operator +=(integer n){
        value += (expand)n << point;
        return *this;
    }

    FixedType& operator -=(integer n){
        value += (expand)n << point;
        return *this;
    }

    FixedType& operator *=(integer n){
        value *= n;
        return *this;
    }

    FixedType& operator /=(integer n){
        value /= n;
        return *this;
    }

    bool operator <(integer n) const {
        return value < ((expand)n << point);
    }

    bool operator >(integer n) const {
        return value > ((expand)n << point);
    }

    bool operator <=(integer n) const {
        return value <= ((expand)n << point);
    }

    bool operator >=(integer n) const {
        return value >= ((expand)n << point);
    }

    bool operator ==(integer n) const {
        return value == ((expand)n << point);
    }

    /**
     *  Floating point operations
    **/
    FixedType operator +(float n) const {
        FixedType ret;
        ret.value = value + n * SCALE_FACTOR;
        return ret;
    }

    FixedType operator -(float n) const {
        FixedType ret;
        ret.value = value - n * SCALE_FACTOR;
        return ret;
    }

    FixedType operator *(float n) const {
        FixedType ret;
        ret.value = value * n;
        return ret;
    }

    FixedType operator /(float n) const {
        FixedType ret;
        ret.value = value / n;
        return ret;
    }

    FixedType& operator +=(float n){
        value += n * SCALE_FACTOR;
        return *this;
    }

    FixedType& operator -=(float n){
        value -= n * SCALE_FACTOR;
        return *this;
    }

    FixedType& operator *=(float n){
        value *= n;
        return *this;
    }

    FixedType& operator /=(float n){
        value /= n;
        return *this;
    }

    bool operator <(float n) const {
        return value < n * SCALE_FACTOR;
    }

    bool operator >(float n) const {
        return value > n * SCALE_FACTOR;
    }

    bool operator <=(float n) const {
        return value <= n * SCALE_FACTOR;
    }

    bool operator >=(float n) const {
        return value >= n * SCALE_FACTOR;
    }

    bool operator ==(float n) const {
        return value == n * SCALE_FACTOR;
    }
};

#define FixedType GenericFixedPoint<bits, point, expand, integer>

/**
 *  Integer <-> Fixed -> Fixed Operations
**/
template<unsigned char bits, unsigned char point, typename expand = long, typename integer = int>
FixedType operator +(integer n, const FixedType f){
    FixedType ret;
    ret.value = ((expand)n << point) + f.value;
    return ret;
}

template<unsigned char bits, unsigned char point, typename expand = long, typename integer = int>
FixedType operator -(integer n, const FixedType f){
    FixedType ret;
    ret.value = ((expand)n << point) - f.value;
    return ret;
}

template<unsigned char bits, unsigned char point, typename expand = long, typename integer = int>
FixedType operator *(integer n, const FixedType f){
    FixedType ret;
    ret.value = f.value * n;
    return ret;
}

template<unsigned char bits, unsigned char point, typename expand = long, typename integer = int>
FixedType operator /(integer n, const FixedType f){
    FixedType ret;
    ret.value = ((expand)n << (point * 2)) / f.value;
    return ret;
}

/**
 *  Float <-> Fixed -> Fixed
**/
template<unsigned char bits, unsigned char point, typename expand = long, typename integer = int>
FixedType operator +(float n, const FixedType f){
    FixedType ret;
    ret.value = n * SCALE_FACTOR + f.value;
    return ret;
}

template<unsigned char bits, unsigned char point, typename expand = long, typename integer = int>
FixedType operator -(float n, const FixedType f){
    FixedType ret;
    ret.value = n * SCALE_FACTOR - f.value;
    return ret;
}

template<unsigned char bits, unsigned char point, typename expand = long, typename integer = int>
FixedType operator *(float n, const FixedType f){
    FixedType ret;
    ret.value = f.value * n;
    return ret;
}

template<unsigned char bits, unsigned char point, typename expand = long, typename integer = int>
FixedType operator /(float n, const FixedType f){
    FixedType ret;
    ret.value = (n / f.value) * SCALE_FACTOR * SCALE_FACTOR;
    return ret;
}

#undef FixedType

#undef SCALE_FACTOR

#endif
