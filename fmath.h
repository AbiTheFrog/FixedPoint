/**
 *  Fixed Point Math Library
 *      Made by Abi The Frog
 *      Designed for use with TI84 calculators
 *          - ideally 24 bit value with 6 bits below point <24, 6>
 *          - should work on other platforms and with different bit layouts
 *      Change log  (d/m/y)
 *          Initial Code 3/3/2022
**/

#pragma once

#ifndef FixedPointMathLib
#define FixedPointMathLib

#include "fixedpoint.h"

#define FixedType GenericFixedPoint<bits, point, expand, integer>

/**
 *  Absolute value function
 *      @param x GenericFixedPoint<> value
**/
template<unsigned char bits, unsigned char point, typename expand = long, typename integer = int>
FixedType abs(FixedType x){
    x.value = (x.value < 0) ? -x.value : x.value;
    return x;
}

/**
 *  Sine function
 *      @param x radian angle in the domain [0, tau]
 *      ! limited accuracy
 *      Based of tailor series for cos (consider faster methods)
**/
template<unsigned char bits, unsigned char point, typename expand = long, typename integer = int>
FixedType sin_domain(FixedType x){
    constexpr FixedType pi = 3.141592f;
    constexpr FixedType hpi = 3.141592f / 2;

    x -= hpi;

    // confine between [0, pi]
    bool neg = false;
    if(x > pi){
        neg = true;
        x -= pi;
    }

    // evaluate cos tailor serios (good between -tau / 4 to tau / 4, or 0 - pi with shift)
    const FixedType x2 = x * x;
    const FixedType x4 = x2 * x2;

    x = 1 - (x2 / 2) + (x4 / 24) - (x4 * x2) / 720;

    return neg ? -x : x;
}

/**
 *  Cosine function
 *      @param x radian angle in the domain [0, tau]
 *      ! limited accuracy
 *      Based of tailor series for cos (consider faster methods)
 *      Presently almost the same as sin_domain
**/
template<unsigned char bits, unsigned char point, typename expand = long, typename integer = int>
FixedType cos_domain(FixedType x){
    constexpr FixedType pi = 3.141592f;

    bool neg = false;
    if(x > pi){
        neg = true;
        x -= pi;
    }

    const FixedType x2 = x * x;
    const FixedType x4 = x2 * x2;

    x = 1 - (x2 / 2) + (x4 / 24) - (x4 * x2) / 720;

    return neg ? -x : x;
}

/**
 *  Unrestricted sine function
 *      @param x radian angle (no domain restriction)
 *      ! limited accuracy
**/
template<unsigned char bits, unsigned char point, typename expand = long, typename integer = int>
FixedType sin(FixedType x){
    constexpr FixedType tau = 3.141592f * 2;
    
    // trim between [0, tau]
    if(x > tau){
        x.value %= tau.value;
    } else if(x < 0){
        x.value = tau.value - (-x.value % tau.value);
    }
    
    return sin_domain(x);
}

/**
 *  Unrestricted cosine function
 *      @param x radian angle (no domain restriction)
 *      ! limited accuracy
**/
template<unsigned char bits, unsigned char point, typename expand = long, typename integer = int>
FixedType cos(FixedType x){
    constexpr FixedType tau = 3.141592f * 2;

    // trim between [0, tau]
    if(x > tau){
        x.value %= tau.value;
    } else if(x < 0){
        x.value = tau.value - (-x.value % tau.value);
    }
    
    return cos_domain(x);
}

#undef FixedType

#endif