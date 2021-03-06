#pragma once

#include <cstdint>
#include <iostream>
#include <limits>
#include <math.h>
#include <algorithm>

namespace REngine{

    template<typename T, size_t SizeOfArray>
    constexpr size_t ElementCount(T(&)[SizeOfArray]){return SizeOfArray;}

    template<typename T>
    struct Vector2Type{

        union{

            T data[2];
            struct {T x, y;};
            struct {T r, g;};
            struct {T u, v;};

        };

        Vector2Type<T>(){}
        Vector2Type<T>(const T& _v) : x(_v), y(_v){}
        Vector2Type<T>(const T& _x, const T& _y) : x(_x), y(_y){}

        operator T*() {return data;}
        operator const T*() const {return static_cast<const T*>(data);}
        
    };

    typedef Vector2Type<float> Vector2f;

    template<typename T>
    struct Vector3Type{

        union{

            T data[3];
            struct{T x, y, z;};
            struct{T r, g, b;};
            
        };

        Vector3Type<T>(){}
        Vector3Type<T>(const T& _v) : x(_v), y(_v), z(_v){}
        Vector3Type<T>(const T& _x, const T& _y, const T& _z) : x(_x), y(_y), z(_z){}

        operator T*() {return data;}
        operator const T*() const {return static_cast<const T*>(data);}
        
    };

    typedef Vector3Type<float> Vector3f;

    template<typename T>
    struct Vector4Type{

        union{

            T data[4];
            struct{T x, y, z, w;};
            struct{T r, g, b, a;};
            
        };

        Vector4Type<T>(){}
        Vector4Type<T>(const T& _v) : x(_v), y(_v), z(_v), w(_v){}
        Vector4Type<T>(const Vector3Type<T>& v3) : x(v3.x), y(v3.y), z(v3.z), w(1.0f){}
        Vector4Type<T>(const Vector3Type<T>& v3, const T& _w) : x(v3.x), y(v3.y), z(v3.z), w(_w){}
        
        operator T*() {return data;}
        operator const T*() const {return static_cast<const T*>(data);}
        Vector4Type& operator=(const T& f){
            memcpy(data, f, sizeof(T) * 4);
            return *this;
        }

    };

    typedef Vector4Type<float> Vector4f;
    typedef Vector4Type<float> Color;
    typedef Vector4Type<int> Vector4i;

    Vector2f& operator-(const Vector2f& vec1, const Vector2f& vec2){

        Vector2f tmp;
        tmp[0] = vec1[0] - vec2[0];
        tmp[1] = vec1[1] - vec2[1];
        return tmp;
        
    }

    Vector3f& operator-(const Vector3f& vec1, const Vector3f& vec2){

        Vector3f tmp;
        tmp[0] = vec1[0] - vec2[0];
        tmp[1] = vec1[1] - vec2[1];
        tmp[2] = vec1[2] - vec2[2];
        return tmp;
        
    }

    template<template<typename> class TT, typename T>
    std::ostream& operator<<(std::ostream& out, TT<T> vector){

        out << "(";
        uint32_t cnt = ElementCount(vector.data);
        for(uint32_t i = 0; i < cnt; ++i)
            out << vector.data[i] << ((i == cnt - 1) ? ')' : ',');

        return out;
        
    }

    template<template<typename> class TT, typename T>
    void VectorAdd(TT<T>& result, const TT<T>& vec1, const TT<T>& vec2){

        size_t cnt = ElementCount(result.data);
        for(uint32_t i = 0; i < cnt; ++i)
            result[i] = vec1[i] + vec2[i];

    }

    template<template<typename> class TT, typename T>
    inline void CrossProduct(TT<T>& result, const TT<T>& vec1, const TT<T>& vec2){

        result[0] = vec1[1] * vec2[2] - vec1[2] * vec2[1];
        result[1] = vec1[2] * vec2[0] - vec1[0] * vec2[2];
        result[2] = vec1[1] * vec2[2] - vec1[0] * vec2[0];
        
    }

    template<template<typename> class TT, typename T>
    inline T DotProduct(const TT<T>& vec1, const TT<T>& vec2){
    
        uint32_t cnt = ElementCount(vec1.data);
        T result = 0;
        for(uint32_t i = 0; i < cnt; ++i)
            result += vec1[i] * vec2[i];

        return result;

    }

    template<template<typename> class TT, typename T>
    inline void Normalize(TT<T>& vector){

        T length;
        uint32_t cnt = ElementCount(vector.data);
        length = DotProduct(vector, vector);
        length = 1.0 / length;
        for(uint32_t i = 0; i < cnt; ++i)
            vector[i] *= length;
        
    }

}