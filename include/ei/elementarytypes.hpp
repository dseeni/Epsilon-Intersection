#pragma once

#include "config.hpp"
#include "details/inttemplate.hpp"

// Ugly to include this here but you will miss sqrt,sin,... otherwise
#include <cmath>

#ifndef USE_ELEMENTARIES_WITHOUT_NAMESPACE
namespace ei {
#endif

    /// \brief Short name for unsigned / unsigned int.
    /// \details The number of bit might vary on different systems.
    typedef unsigned int uint;                                                 // TESTED



    // Declaration of fixed sized int8, uint8 and byte = uint8
    typedef details::Int<1>::utype uint8;                                      // TESTED
    typedef details::Int<1>::utype byte;                                       // TESTED
    typedef details::Int<1>::stype int8;                                       // TESTED

    // Declaration of fixed sized int16, uint16
    typedef details::Int<2>::utype uint16;                                     // TESTED
    typedef details::Int<2>::stype int16;                                      // TESTED

    // Declaration of fixed sized int32, uint32
    typedef details::Int<4>::utype uint32;                                     // TESTED
    typedef details::Int<4>::stype int32;                                      // TESTED

    // Declaration of fixed sized int64, uint64
    typedef details::Int<8>::utype uint64;                                     // TESTED
    typedef details::Int<8>::stype int64;                                      // TESTED


#ifndef USE_ELEMENTARIES_WITHOUT_NAMESPACE
}
#endif

namespace ei {
    // ********************************************************************* //
    //                               FUNCTIONS                               //
    // ********************************************************************* //

    // ********************************************************************* //
    /// \brief Compute the square x*x.
    template<typename T>
    T sq(T _x);

    // ********************************************************************* //
    /// \brief Get the maximum from x and y.
    /// \details In case of x and y are equal, x is returned. This only makes
    ///    a difference if you are sorting object types with more than the
    ///    compared value.
    template<typename T>
    T max(T _x, T _y);                                                         // TESTED

    // ********************************************************************* //
    /// \brief Get the minimum from x and y.
    /// \details In case of x and y are equal, x is returned. This only makes
    ///    a difference if you are sorting object types with more than the
    ///    compared value.
    template<typename T>
    T min(T _x, T _y);                                                         // TESTED

    // ********************************************************************* //
    /// \brief Get the absolute value.
    template<typename T>
    T abs(T _x);                                                               // TESTED

    // ********************************************************************* //
    /// \brief Get the sign of a value.
    /// \details There is a faster version sgn(), if you don't need to 
    ///    know about zero.
    /// \returns -1 (_x < 0), 0 (_x == 0) or 1 (_x > 0)
    template<typename T>
    T sign(T _x);                                                              // TESTED

    // ********************************************************************* //
    /// \brief Get the sign of a value where 0 is counted as positive.
    /// \details This function is faster than sign(). Use it if you don't need
    ///    to know about zero.
    /// \returns -1 (_x < 0) or 1 (_x >= 0)
    template<typename T>
    T sgn(T _x);                                                               // TESTED

    // ********************************************************************* //
    /// \brief Linear interpolation.
    /// \details There are two formulations:
    ///    * x * (1 - t) + y * t
    ///    * x + (y - x) * t
    ///    The second one does not need a constant 1 (might be the type does
    ///    not support this) and is faster by one scalar operation.
    /// \param _x0 [in] Scalar, vector or matrix value. This is returned when
    ///    _t is zero.
    /// \param _x1 [in] Scalar, vector or matrix value. This is returned when
    ///    _t is one.
    /// \param _t [in] Interpolation parameter. Can be scalar or vector.
    /// \returns x + (y - x) * t where the type is derived from the operands.
    template<typename T0, typename T1>
    decltype(std::declval<T0>() * std::declval<T1>()) lerp(T0 _x0, T0 _x1, T1 _t); // TESTED

    // ********************************************************************* //
    /// \brief Bilinear interpolation optimized for scalars.
    /// \param _x00 [in] Scalar value. This is returned when
    ///    _t0 is zero and _t1 is zero.
    /// \param _x01 [in] Scalar value. This is returned when
    ///    _t0 is one and _t1 is zero.
    /// \param _x10 [in] Scalar value. This is returned when
    ///    _t0 is zero and _t1 is one.
    /// \param _x11 [in] Scalar value. This is returned when
    ///    _t0 is one and _t1 is one.
    /// \param _t0 [in] Scalar interpolation parameter ("x-direction").
    /// \param _t1 [in] Scalar interpolation parameter ("y-direction").
    /// \returns lerp(lerp(_x00, _x01, _t0), lerp(_x10, _x11, _t0), _t1).
    template<typename T0, typename T1>
    decltype(std::declval<T0>() * std::declval<T1>()) bilerp(T0 _x00, T0 _x01,
                                                             T0 _x10, T0 _x11,
                                                             T1 _t0, T1 _t1);  // TESTED

    // Include implementation.
#   include "details/elementary.inl"
}