#include"Vector2.h"
namespace Engine::Maths::Vector::Vec2{
    template<typename T>
    inline Vector2<T>::Vector2():
        _X(0),
        _Y(0)
    {
    }
    template<typename T>
    inline Vector2<T>::Vector2(T x, T y):
        _X(x),
        _Y(y)
    {
    }
    template<typename T>
    inline Vector2<T>::Vector2(const Vector2<T>& vec):
        _X(vec.GetX()),
        _Y(vec.GetY())
    {
    }
    template<typename T>
    inline Vector2<T> Vector2<T>::operator+(const Vector2<T>& vec)
    {
        return Vector2<T>(_X + vec.GetX(), _Y + vec.GetY());
    }
    template<typename T>
    inline Vector2<T>& Vector2<T>::operator+=(const Vector2<T>& vec)
    {
        _X += vec.GetX();
        _Y += vec.GetY();
      
        return *this;
    }

    template<typename T>
    inline Vector2<T> Vector2<T>::operator-(const Vector2<T>& vec)
    {
        return Vector2<T>(_X - vec.GetX(), _Y - vec.GetY());
    }

    template<typename T>
    inline Vector2<T>& Vector2<T>::operator-=(const Vector2<T>& vec)
    {
        _X -= vec.GetX();
        _Y -= vec.GetY();
        return *this;
    }

    template<typename T>
    inline Vector2<T> Vector2<T>::operator*(float value)
    {
        return Vector2<T>(_X * value, _Y * value);
    }

    template<typename T>
    inline Vector2<T>& Vector2<T>::operator*=(float value)
    {
        _X *= value;
        _Y *= value;
        return *this;
    }

    template<typename T>
    inline Vector2<T> Vector2<T>::operator/(float value)
    {
        assert(value != 0);
        return Vector2<T>(_X / value, _Y / value);
    }

    template<typename T>
    inline Vector2<T>& Vector2<T>::operator/=(float value)
    {
        assert(value != 0);
        _X /= value;
        _Y /= value;
        return *this;
    }

    template<typename T>
    inline Vector2<T>& Vector2<T>::operator=(const Vector2<T>& vec)
    {
        this->_X = vec.GetX();
        this->_Y = vec.GetY();
        return *this;
    }

    template<typename T>
    inline bool Vector2<T>::operator!=(const Vector2<T>& vec)
    {
        if (this->Magnitude == vec.Magnitude() && this->Normalization().DotProduct(vec.Normalization) == 1) {
            return true;
        }
        return false;
    }
    template<typename T>
    inline bool Vector2<T>::operator==(const Vector2<T>& vec)
    {

        if (This.Magnitude() == vec.Magnitude() && this->Normalization().DotProduct(vec.Normalization) == 1) {
            return false;
        }
        return true;
    }
    template<typename T>
    inline float Vector2<T>::DotProduct(const Vector2<T>& vec)
    {
        return _X * vec.GetX() + _Y * vec.GetY();
    }
    template<typename T>
    inline Vector2<T> Vector2<T>::CrossProduct(const Vector2<T>& vec)
    {
        float i = _X * vec.GetY() - _Y * vec.GetX();
        return Vector2<T>(i, i);
    }
    template<typename T>
    inline Vector2<T> Vector2<T>::Normalization()
    {
        Vector2<T> vecReturn;
        float Mag = Magnitude();
        if (Mag != 0) {

            vecReturn.GetX() = _X / Mag;
            vecReturn.GetY() = _Y / Mag;
            

        }
        return vecReturn;
    }
    template<typename T>
    inline Vector2<T>& Vector2<T>::NormalizationThis()
    {
        float Mag = Magnitude();
        if (Mag != 0) {
            this /= Mag;
        }
        return *this;
    }
    template<typename T>
    inline float Vector2<T>::Distance(const Vector2<T>& vec)
    {
        float X = _X - vec.GetX();
        float Y = _Y - vec.GetY();
        return sqrt(((X * X) + (Y * Y)));
    }
    template<typename T>
    inline float Vector2<T>::Magnitude()
    {
        return std::sqrt(_X * _X + _Y * _Y);
    }
    template<typename T>
    inline T Vector2<T>::GetX()
    {
        return _X;
    }
    template<typename T>
    inline T Vector2<T>::GetY()
    {
        return _Y;
    }
}