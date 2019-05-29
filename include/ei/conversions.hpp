#pragma once

#include "vector.hpp"
#include "quaternion.hpp"

/// \brief Utility functions for conversions of colors and vector representations.

namespace ei {

    // Conversion of sRGB to linear RGB (single component)
    EIAPI constexpr inline float sRgbToRgb(float _c)  // TESTED
    {
        if(_c <= 0.04045f)
            return _c / 12.92f;
        return pow((_c + 0.055f) / 1.055f, 2.4f);
    }

    // Conversion of sRGB to linear RGB (two components)
    EIAPI constexpr inline Vec2 sRgbToRgb(const Vec2 & _sRg)
    {
        return Vec2{sRgbToRgb(_sRg.r), sRgbToRgb(_sRg.g)};
    }

    // Conversion of sRGB to linear RGB
    EIAPI constexpr inline Vec3 sRgbToRgb(const Vec3 & _sRgb)  // TESTED
    {
        return Vec3{sRgbToRgb(_sRgb.r), sRgbToRgb(_sRgb.g), sRgbToRgb(_sRgb.b)};
    }

    // Conversion of linear RGB to sRGB (single component)
    EIAPI constexpr inline float rgbToSRgb(float _c)  // TESTED
    {
        if(_c <= 0.0031308f)
            return _c * 12.92f;
        return 1.055f * pow(_c, 1.0f/2.4f) - 0.055f;;
    }

    // Conversion of linear RGB to sRGB (two components)
    EIAPI constexpr inline Vec2 rgbToSRgb(const Vec2 & _rg)
    {
        return Vec2{rgbToSRgb(_rg.r), rgbToSRgb(_rg.g)};
    }

    // Conversion of linear RGB to sRGB
    EIAPI constexpr inline Vec3 rgbToSRgb(const Vec3 & _rgb)  // TESTED
    {
        return Vec3{rgbToSRgb(_rgb.r), rgbToSRgb(_rgb.g), rgbToSRgb(_rgb.b)};
    }


    // Conversion of CIE XYZ to linear RGB
    // D65 reference white.
    // Linear RGB means ITU-R BT.709 without the gamma correction part.
    // Color spectrum 35.9% of visible spectrum.
    // http://brucelindbloom.com/index.html?Eqn_RGB_XYZ_Matrix.html
    EIAPI constexpr inline Vec3 xyzToRgb(const Vec3 & _xyz)  // TESTED
    {
        constexpr Mat3x3 XYZ_TO_RGB {
             3.2404542f, -1.5371385f, -0.4985314f,
            -0.9692660f,  1.8760108f,  0.0415560f,
             0.0556434f, -0.2040259f,  1.0572252f
        };
        return XYZ_TO_RGB * _xyz;
    }

    // Conversion of linear RGB to CIE XYZ
    EIAPI constexpr inline Vec3 rgbToXyz(const Vec3 & _rgb)  // TESTED
    {
        constexpr Mat3x3 RGB_TO_XYZ {
            0.4124564f, 0.3575761f, 0.1804375f,
            0.2126729f, 0.7151522f, 0.0721750f,
            0.0193339f, 0.1191920f, 0.9503041f
        };
        return RGB_TO_XYZ * _rgb;
    }

    // Conversion of CIE XYZ to Adobe RGB (1998)
    // D65 reference white.
    // Color spectrum 52.1% of visible spectrum.
    EIAPI constexpr inline Vec3 xyzToAdobeRgb(const Vec3 & _xyz)
    {
        constexpr Mat3x3 XYZ_TO_ADOBE_RGB {
             2.0413690, -0.5649464, -0.3446944,
            -0.9692660,  1.8760108,  0.0415560,
             0.0134474, -0.1183897,  1.0154096
        };
        return XYZ_TO_ADOBE_RGB * _xyz;
    }

    // Conversion of Adobe RGB to CIE XYZ
    EIAPI constexpr inline Vec3 adobeRgbToXyz(const Vec3 & _rgb)
    {
        constexpr Mat3x3 ADOBE_RGB_TO_XYZ {
            0.5767309, 0.1855540, 0.1881852,
            0.2973769, 0.6273491, 0.0752741,
            0.0270343, 0.0706872, 0.9911085
        };
        return ADOBE_RGB_TO_XYZ * _rgb;
    }

    // Conversion of CIE XYZ to ITU-R BT.2020 RGB
    // D65 reference white.
    // Color spectrum 75.8% of visible spectrum.
    EIAPI constexpr inline Vec3 xyzToRec2020Rgb(const Vec3 & _xyz)
    {
        constexpr Mat3x3 XYZ_TO_REC2020RGB {
             1.7166512, -0.3556708, -0.2533663,
            -0.6666844,  1.6164812,  0.0157685,
             0.0176399, -0.0427706,  0.9421031
        };
        return XYZ_TO_REC2020RGB * _xyz;
    }

    // Conversion of ITU-R BT.2020 RGB to CIE XYZ
    EIAPI constexpr inline Vec3 rec2020RgbToXyz(const Vec3 & _rgb)
    {
        constexpr Mat3x3 REC2020RGB_TO_XYZ {
            0.6369580, 0.1446169, 0.1688810,
            0.2627002, 0.6779981, 0.0593017,
            0.0f,      0.0280727, 1.0609851
        };
        return REC2020RGB_TO_XYZ * _rgb;
    }


    // Conversion of YCgCo color space to linear RGB
    EIAPI constexpr inline Vec3 yCgCoToRgb(const Vec3 & _yCgCo)
    {
        float tmp = _yCgCo.x - _yCgCo.y;
        return Vec3(tmp + _yCgCo.z, _yCgCo.x + _yCgCo.y, tmp - _yCgCo.z);
    }

    // Conversion of linear RGB to YCgCo color space
    EIAPI constexpr inline Vec3 rgbToYCgCo(const Vec3 & _rgb)
    {
        return Vec3{(_rgb.r + _rgb.b) * 0.25f + _rgb.g * 0.5f,
                    (_rgb.r + _rgb.b) * -0.25f + _rgb.g * 0.5f,
                    (_rgb.r - _rgb.b) * 0.5f};
    }

    // Conversion of YCbCr color space to linear RGB.
    // Colorspace used by JPEG, MPEG, ...
    // This conversion does not include the offset (0,128,128 or similar).
    EIAPI constexpr inline Vec3 yCbCrToRgb(const Vec3 & _yCbCr)
    {
        return Vec3{_yCbCr.x                       + 1.402 * _yCbCr.z,
                    _yCbCr.x - 0.344136 * _yCbCr.y - 0.714136 * _yCbCr.z,
                    _yCbCr.x + 1.772 * _yCbCr.y};
    }

    // Conversion of linear RGB to YCbCr.
    EIAPI constexpr inline Vec3 rgbToYCbCr(const Vec3 & _rgb)
    {
        constexpr Mat3x3 RGB_TO_YCBCR {
             0.299,     0.587,     0.114,
            -0.168736, -0.331264,  0.5,
             0.5,      -0.418688, -0.081312
        };
        return RGB_TO_YCBCR * _rgb;
    }



    // Converts an RGB value in [0,1]^2x[0,x] to HSV in [0,x]^3
    // Yes, HSV is capable of HDR colors with greater values.
    EIAPI constexpr inline Vec3 rgbToHsv(const Vec3 & _rgb) // TESTED
    {
        eiAssert(_rgb >= 0.0f, "Negative color value not allowed.");
        if(_rgb.r == _rgb.g && _rgb.r == _rgb.b)        // R=G=B
            return Vec3 { 0.0f, 0.0f, _rgb.r };

        if(_rgb.r >= _rgb.g && _rgb.r >= _rgb.b)          // R max
        {
            float m = min(_rgb.g, _rgb.b);
            float h = (_rgb.g - _rgb.b) / (_rgb.r - m);
            if(h < 0.0f) h += 6.0f;
            float s = (_rgb.r - m) / _rgb.r;
            return Vec3 { h / 6.0f, s, _rgb.r };
        }
        
        if(_rgb.g >= _rgb.r && _rgb.g >= _rgb.b)        // G max
        {
            float m = min(_rgb.r, _rgb.b);
            float h = 2.0f + (_rgb.b - _rgb.r) / (_rgb.g - m);
            float s = (_rgb.g - m) / _rgb.g;
            return Vec3 { h / 6.0f, s, _rgb.g };
        }

        // B max
        float m = min(_rgb.r, _rgb.g);
        float h = 4.0f + (_rgb.r - _rgb.g) / (_rgb.b - m);
        float s = (_rgb.b - m) / _rgb.b;
        return Vec3 { h / 6.0f, s, _rgb.b };
    }

    // Converts an HSV value in [0,1]^2x[0,x] to RGB [0,x]^3
    // Yes, HSV is capable of HDR colors with greater values.
    EIAPI constexpr inline Vec3 hsvToRgb(const Vec3 & _hsv) // TESTED
    {
        eiAssert(_hsv.x >= 0.0f && _hsv.x <= 1.0f, "Hue out of range");
        eiAssert(_hsv.y >= 0.0f && _hsv.y <= 1.0f, "Saturation out of range");
        eiAssert(_hsv.z >= 0.0f, "Value out of range");
        float chroma = _hsv.y * _hsv.z;
        float h = _hsv.x * 3.0f; // instead mod(2) use half the factor and frac
        float x = chroma * (1.0f - ei::abs(frac(h) * 2.0f - 1.0f));
        float m = _hsv.z - chroma;
        chroma += m;
        x += m;
        if(h <= 0.5f) return Vec3 { chroma, x, m };
        if(h <= 1.0f) return Vec3 { x, chroma, m };
        if(h <= 1.5f) return Vec3 { m, chroma, x };
        if(h <= 2.0f) return Vec3 { m, x, chroma };
        if(h <= 2.5f) return Vec3 { x, m, chroma };
        return Vec3 { chroma, m, x };
    }


    // Conversion from CIE XYZ to L*a*b* (CIELAB).
    // Other than the standardization this methods expects [0,1] normalized colors
    // and not [0,100].
    // Output value are within [0,1] x [-1.7,1] x [-1,1.5] for LDR colors.
    // White point D65.
    EIAPI constexpr inline Vec3 xyzToLab(const Vec3 & _xyz) // TESTED
    {
        //constexpr Vec3 XYZn {95.047f, 100.0f, 108.883f}; // D65 2�
        constexpr Vec3 XYZn {0.950470030f, 1.00000012f, 1.08882999f}; // D65 2�
        const Vec3 ratio = _xyz / XYZn;
        const float xCurt = ratio.x <= 0.008856452f ? 7.787037037f * ratio.x + 0.137931034f : pow(ratio.x, 1.0f/3.0f);
        const float yCurt = ratio.y <= 0.008856452f ? 7.787037037f * ratio.y + 0.137931034f : pow(ratio.y, 1.0f/3.0f);
        const float zCurt = ratio.z <= 0.008856452f ? 7.787037037f * ratio.z + 0.137931034f : pow(ratio.z, 1.0f/3.0f);
        return Vec3 {1.16f * yCurt - 0.16f, 5.0f * (xCurt - yCurt), 2.0f * (yCurt - zCurt)};
    }

    EIAPI constexpr inline Vec3 labToXyz(const Vec3 & _lab) // TESTED
    {
        constexpr Vec3 XYZn {0.950470030f, 1.00000012f, 1.08882999f}; // D65 2�
        const float yCurt = (_lab.x + 0.16f) / 1.16f;
        const float xCurt = _lab.y / 5.0f + yCurt;
        const float zCurt = yCurt - _lab.z / 2.0f;
        const Vec3 ratio {
            xCurt <= 0.206896554f ? (xCurt - 0.137931034f) / 7.787037037f : xCurt * xCurt * xCurt,
            yCurt <= 0.206896554f ? (yCurt - 0.137931034f) / 7.787037037f : yCurt * yCurt * yCurt,
            zCurt <= 0.206896554f ? (zCurt - 0.137931034f) / 7.787037037f : zCurt * zCurt * zCurt
        };
        return ratio * XYZn;
    }

    // Conversion from CIE XYZ to IPT (Intensity - Protan - Tritan).
    // This colorspace is more uniform than L*a*b* and has a better decorrelation.
    // Output value are within [0,1] x [-1,1]� for LDR colors.
    // White point D65.
    EIAPI constexpr inline Vec3 xyzToIpt(const Vec3 & _xyz)
    {
        constexpr Mat3x3 XYZ_TO_LMS {
             0.4002f, 0.7075f, -0.0807f,
            -0.2280f, 1.1500f,  0.0612f,
             0.0000f, 0.0000f,  0.9184f
        };
        const Vec3 lms = XYZ_TO_LMS * _xyz;
        const Vec3 lmsp = ei::sgn(lms) * pow(ei::abs(lms), 0.43f);
        constexpr Mat3x3 LMSP_TO_IPT {
            0.4000f,  0.4000f,  0.2000f,
            4.4550f, -4.8510f,  0.3960f,
            0.8056f,  0.3572f, -1.1628f
        };
        return LMSP_TO_IPT * lmsp;
    }

    EIAPI constexpr inline Vec3 iptToXyz(const Vec3 & _ipt)
    {
        constexpr Mat3x3 IPT_TO_LMSP {
            1.8502f, -1.1383f,  0.2384f,
            0.3668f,  0.6439f, -0.0107f,
            0.0000f,  0.0000f,  1.0889f
        };
        const Vec3 lmsp = IPT_TO_LMSP * _ipt;
        const Vec3 lms = ei::sgn(lms) * pow(ei::abs(lms), 1.0f/0.43f);
        constexpr Mat3x3 LMS_TO_XYZ {
            1.0000f,  0.0976f,  0.2052f,
            1.0000f, -1.1139f,  0.1332f,
            1.0000f,  0.0326f, -0.6769f
        };
        return LMS_TO_XYZ * lms;
    }




    // Discretize a [0,1]^3 vector into a single integer with 11.11.10 bits
    // for the components.
    // Note: This is not the R11G11B10F (float) format from textures!
    EIAPI constexpr inline uint32 packR11G11B10(Vec3 _v)  // TESTED
    {
        eiAssertWeak(all(greatereq(_v, 0.0f)) && all(lesseq(_v, 1.0f)), "Unclamped color cannot be converted into R11G11B10 format!");
        _v *= Vec3{2047.0, 2047.0, 1023.0};
        return (uint32(_v.r) << 21) | (uint32(_v.g) << 10) | uint32(_v.b);
    }

    // Unpack a 11.11.10 bit descretized vector into a full Vec3
    // Note: This is not the R11G11B10F (float) format from textures!
    EIAPI constexpr inline Vec3 unpackR11G11B10(uint32 _code)  // TESTED
    {
        return Vec3 {
            float(_code >> 21) / 2047.0,
            float((_code >> 10) & 0x7ff) / 2047.0,
            float(_code & 0x3ff) / 1023.0
        };
    }


    // Pack an HDR color value into RGB9E5 shared exponent format
    // See https://www.khronos.org/registry/OpenGL/extensions/EXT/EXT_texture_shared_exponent.txt
    EIAPI constexpr inline uint32 packRGB9E5(const Vec3 & _v)
    {
        eiAssertWeak(all(greatereq(_v, 0.0f)), "Vector must be positive to be packed into RGB9E5");
        float maxComp = ei::max(_v);
        if(maxComp <= 6e-8f) return 0;
        // Code from spec:
        //int e = ei::max(0, ei::floor(log2f(maxComp)) + 1); // Without bias
        //float norm = exp2f(-(e - 9));	// - #MantissaBits
        //if(maxComp * norm >= 511.5f) {	// <=> floor(maxComp * norm + 0.5f) == 512
        //    ++e;
        //    norm *= 0.5f;
        //}
        // Equivalent, faster code?:
        int e = 0;
        float norm = frexpf(maxComp, &e) * 511.5f / maxComp;
        e += 15;
        if(e < 0) { norm *= exp2f(float(e)); e = 0; }	// Denormalized values
        return floor(_v.r * norm + 0.5f)
            | (floor(_v.g * norm + 0.5f) << 9)
            | (floor(_v.b * norm + 0.5f) << 18)
            | (ei::min(e, 31) << 27); // Clamp the number if value range of RGB9E5 is exceeded
    }

    // Unpack a RGB9E5 value into a full Vec3
    EIAPI inline Vec3 unpackRGB9E5(uint32 _code) noexcept
    {
        float e = exp2f(float(_code>>27) - 15 - 9); // - ExponentBias - #MantissaBits
        return Vec3 {
            (_code & 0x1ff) * e,
            ((_code>>9) & 0x1ff) * e,
            ((_code>>18) & 0x1ff) * e
        };
    }

    // Pack an HDR color value into RGB8E8 shared exponent format.
    // This is used for example by the *.hdr file format
    EIAPI constexpr inline uint32 packRGB8E8(const Vec3 & _v) noexcept
    {
        eiAssertWeak(all(greatereq(_v, 0.0f)), "Vector must be positive to be packed into RGB8E8");
        float maxComp = ei::max(_v);
        if(maxComp <= 2e-41f) return 0;
        int e = 0;
        float norm = frexpf(maxComp, &e) * 255.5f / maxComp;
        e += 128;
        if(e < 0) { norm *= exp2f(float(e)); e = 0; }	// Denormalized values
        return floor(_v.r * norm + 0.5f)
            | (floor(_v.g * norm + 0.5f) << 8)
            | (floor(_v.b * norm + 0.5f) << 16)
            | (ei::min(e, 255) << 24); // Clamp the number if value range of RGB8E8 is exceeded
    }

    // Unpack a RGB8E8 value into a full Vec3
    EIAPI inline Vec3 unpackRGB8E8(uint32 _code)
    {
        float e = exp2f(float(_code>>24) - 128 - 8); // - ExponentBias - #MantissaBits
        return Vec3 {
            (_code & 0xff) * e,
            ((_code>>8) & 0xff) * e,
            ((_code>>16) & 0xff) * e
        };
    }

    // Pack a direction vector into a 32 bit integer using octahedral mapping
    EIAPI constexpr inline uint32 packOctahedral32(const Vec3 & _d)  // TESTED
    {
        eiAssertWeak(approx(len(_d), 1.0f), "Can only pack direction vectors using octahedral mapping");
        float l1norm = abs(_d.x) + abs(_d.y) + abs(_d.z);
        float u = (_d.z >= 0) ? _d.x / l1norm
                              : (1 - abs(_d.y) / l1norm) * (_d.x >= 0 ? 1 : -1);    // warp lower hemisphere
        float v = (_d.z >= 0) ? _d.y / l1norm
                              : (1 - abs(_d.x) / l1norm) * (_d.y >= 0 ? 1 : -1);    // warp lower hemisphere
        return uint16(floor(u * 32767.0f + 0.5f))
            | (uint32(floor(v * 32767.0f + 0.5f)) << 16);
    }

    // Unpack a direction vector from octahedral mapping
    EIAPI constexpr inline Vec3 unpackOctahedral32(uint32 _code)  // TESTED
    {
        float u = int16(_code & 0xffff) / 32767.0f;
        float v = int16(_code >> 16) / 32767.0f;
        //u = u * 2 - 1;
        //v = v * 2 - 1;
        float z = 1 - abs(u) - abs(v);
        if(z >= 0) {
            float x = u;
            float y = v;
            return normalize(Vec3{x,y,z});
        } else {
            float x = (1 - abs(v)) * (u >= 0 ? 1 : -1);
            float y = (1 - abs(u)) * (v >= 0 ? 1 : -1);
            return normalize(Vec3{x,y,z});
        }
    }

    // Use fixed point discretization to pack an already packed tangent space further.
    EIAPI constexpr uint64 packOrthoSpace64(const OrthoSpace& _space) noexcept
    {
        // Pack only ijk with 21 bits each, r can be reconstructed if its
        // sign is known (bit 64).
        NormalizedInt<int32, 21> i(_space.data().i);
        NormalizedInt<int32, 21> j(_space.data().j);
        NormalizedInt<int32, 21> k(_space.data().k);
        uint64 rSign = sgn(_space.data().r) > 0.0f ? 0 : (1ull << 63);
        return rSign | (uint64(k) << 42) | (uint64(j) << 21) | uint64(i);
    }

    EIAPI inline OrthoSpace unpackOrthoSpace64(uint64 _code) noexcept
    {
        float i { NormalizedInt<int32, 21>(_code) };
        float j { NormalizedInt<int32, 21>(_code >> 21) };
        float k { NormalizedInt<int32, 21>(_code >> 42) };
        float r = sqrt(1.0f - (i*i + j*j + k*k));
        OrthoSpace res;
        res.data().i = i; res.data().j = j; res.data().k = k;
        res.data().r = (_code & (1ull<<63)) ? -r : r;
        return res;
    }


    // ********************************************************************* //
    // Alias types to convert from and to the different models above         //
    // ********************************************************************* //
    struct R11G11B10 : public details::NonScalarType
    {
        uint32 code;

        R11G11B10() = default;

        EIAPI constexpr explicit R11G11B10(const Vec3 & _v) :
            code(packR11G11B10(_v))
        {}

        EIAPI constexpr explicit operator Vec3 () const {
            return unpackR11G11B10(code);
        }
    };

    struct RGB9E5 : public details::NonScalarType
    {
        uint32 code;

        RGB9E5() = default;

        EIAPI constexpr explicit RGB9E5(const Vec3 & _v) :
            code(packRGB9E5(_v))
        {}

        EIAPI explicit operator Vec3 () const {
            return unpackRGB9E5(code);
        }
    };

    struct RGB8E8 : public details::NonScalarType
    {
        uint32 code;

        RGB8E8() = default;

        EIAPI constexpr explicit RGB8E8(const Vec3 & _v) :
            code(packRGB8E8(_v))
        {}

        EIAPI explicit operator Vec3 () const {
            return unpackRGB8E8(code);
        }
    };


    struct OctahedralDir32 : public details::NonScalarType
    {
        uint32 code;

        OctahedralDir32() = default;

        EIAPI constexpr explicit OctahedralDir32(const Vec3 & _v) :
            code(packOctahedral32(_v))
        {}

        EIAPI constexpr explicit operator Vec3 () const {
            return unpackOctahedral32(code);
        }
    };

} // namespace ei