#pragma once


namespace Engine::Maths::Vector::Vec2 {
    template <typename T>
    class Vector2
    {
    public:
        Vector2();
        Vector2(T x, T y);
        Vector2(const Vector2<T>& vec);

        Vector2<T> operator+(const Vector2<T>& vec);
        Vector2<T>& operator+=(const Vector2<T>& vec);
        Vector2<T> operator-(const Vector2<T>& vec);
        Vector2<T>& operator-=(const Vector2<T>& vec);
        Vector2<T> operator*(float value);
        Vector2<T>& operator*=(float value);
        Vector2<T> operator/(float value);
        Vector2<T>& operator/=(float value);
        Vector2<T>& operator=(const Vector2<T>& vec);
        bool operator !=(const Vector2<T>& vec);
        bool operator ==(const Vector2<T>& vec);

       float DotProduct(const Vector2<T>& vec);
        Vector2<T> CrossProduct(const Vector2<T>& vec);
        Vector2<T> Normalization();
        Vector2<T>& NormalizationThis();
        float Square(); 
        float Distance(const Vector2<T>& vec);
        float Magnitude();  


        T GetX();
        T GetY();
    private:
        T _X;
        T _Y;

    };

 

    

}