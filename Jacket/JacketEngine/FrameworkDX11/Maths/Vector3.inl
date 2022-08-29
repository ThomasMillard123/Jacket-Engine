#pragma once
#include"Vector3.h"

namespace Engine::Maths::Vector::Vec3 {
    template<typename T>
    inline Vector3<T>::Vector3():
        _X(0),
        _Y(0),
        _Z(0)
    {
    }

    template<typename T>
    inline Vector3<T>::Vector3(T x, T y, T z):
        _X(x),
        _Y(y),
        _Z(z)
    {
    }

    template<typename T>
    inline Vector3<T>::Vector3(const Vector3<T>& vec):
        _X(vec.GetX()),
        _Y(vec.GetY()),
        _Z(vec.GetZ())
    {
    }

    template<typename T>
    inline Vector3<T>::~Vector3()
    {
    }

    template<typename T>
    inline Vector3<T> Vector3<T>::operator+(const Vector3<T>& vec)
    {
        return Vector3<T>(_X + vec.GetX(), _Y + vec.GetY(), _Z + vec.GetZ());
    }

    template<typename T>
    inline Vector3<T>& Vector3<T>::operator+=(const Vector3<T>& vec)
    {
        _X += vec.GetX();
        _Y += vec.GetY();
        _Z += vec.GetZ();
        return *this;
    }

    template<typename T>
    inline Vector3<T> Vector3<T>::operator-(const Vector3<T>& vec)
    {
        return Vector3<T>(_X - vec.GetX(), _Y - vec.GetY(), _Z - vec.z);
    }

    template<typename T>
    inline Vector3<T>& Vector3<T>::operator-=(const Vector3<T>& vec)
    {
        _X -= vec.GetX();
        _Y -= vec.GetY();
        _Z -= vec.GetZ();
        return *this;
    }

    template<typename T>
    inline Vector3<T> Vector3<T>::operator*(float value)
    {
        return Vector3<T>(_X * value, _Y * value, _Z * value);
    }

    template<typename T>
    inline Vector3<T>& Vector3<T>::operator*=(float value)
    {
        _X *= value;
        _Y *= value;
        _Z *= value;
        return *this;
    }

    template<typename T>
    inline Vector3<T> Vector3<T>::operator/(float value)
    {
        assert(value != 0);
        return Vector3<T>(_X / value, _Y / value, _Z / value);
    }

    template<typename T>
    inline Vector3<T>& Vector3<T>::operator/=(float value) 
    {
        assert(value != 0);
        _X /= value;
        _Y /= value;
        _Z /= value;
        return *this;
    }

    template<typename T>
    inline Vector3<T>& Vector3<T>::operator=(const Vector3<T>& vec)
    {
        this->_X = vec.GetX();
        this->_Y = vec.GetY();
        this->_Z = vec.GetZ();
        return *this;
    }

    template<typename T>
    inline bool Vector3<T>::operator==(const Vector3<T>& vec)
    {
        if (this->Magnitude == vec.Magnitude() && this->Normalization().DotProduct(vec.Normalization)==1) {
            return true;
        }
        return false;
    }

    template<typename T>
    inline bool Vector3<T>::operator!=(const Vector3<T>& vec)
    {
        if (This.Magnitude() == vec.Magnitude() && this->Normalization().DotProduct(vec.Normalization) == 1) {
            return false;
        }
        return true;
    }

    template<typename T>
    inline float Vector3<T>::DotProduct(const Vector3<T>& vec)
    {
        return _X * vec.GetX() + _Y * vec.GetY() + _Z * vec.GetZ();
    }

    template<typename T>
    inline Vector3<T> Vector3<T>::CrossProduct(const Vector3<T>& vec)
    {
        float i = _Y * vec.GetZ() - _Z * vec.GetY();
        float j = _Z * vec.GetX() - _X * vec.GetZ();
        float k = _X * vec.GetY() - _Y * vec.GetX();

        return Vector3(i, j, k);
    }

    /// <summary>
    /// creates a nomalized vector of this
    /// </summary>
    /// <returns> New a Vec3</returns>
    template<typename T>
    inline Vector3<T> Vector3<T>::Normalization()
    { 
        Vector3<T> vecReturn;
        float Mag = Magnitude();
        if (Mag != 0) {
           
            vecReturn.GetX() = _X / Mag;
            vecReturn.GetY() = _Y / Mag;
            vecReturn.GetZ() = _Z / Mag;
    
        }   
        return vecReturn;
    }
    /// <summary>
    /// makes this a normalized vec
    /// </summary>
    /// <returns> this </returns>
    template<typename T>
    inline Vector3<T>& Vector3<T>::NormalizationThis()
    {
        float Mag = Magnitude();
        if (Mag != 0) {
            this /= Mag;
        }
        return *this;
    }
    /// <summary>
    /// Find distance between 2 vectors
    /// </summary>
    /// <typeparam name="T"></typeparam>
    /// <param name="vec"></param>
    /// <returns></returns>
    template<typename T>
    inline float Vector3<T>::Distance(const Vector3<T>& vec)
    {
        float X = _X - vec.GetX();
        float Y = _Y - vec.GetY();
        float Z = _Z - vec.GetZ();
        return sqrt(((X * X) + (Y * Y) + (Z * Z)));
    }

    template<typename T>
    inline float Vector3<T>::Magnitude()
    {
        return std::sqrt(_X * _X + _Y * _Y + _Z * _Z);
    }
    template<typename T>
    inline T Vector3<T>::GetX()
    {
        return _X;
    }
    template<typename T>
    inline T Vector3<T>::GetY()
    {
        return _Y;
    }
    template<typename T>
    inline T Vector3<T>::GetZ()
    {
        return _Z;
    }
}