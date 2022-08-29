#pragma once
#include <math.h>
namespace Engine::Maths::Vector::Vec3 {
	template<typename T>
	class Vector3
	{
	public:
		Vector3();
        Vector3(T x,T y,T z);
        Vector3(const Vector3<T>& vec);
		~Vector3();

        Vector3<T> operator+(const Vector3<T>& vec);
        Vector3<T>& operator+=(const Vector3<T>& vec);
        Vector3<T> operator-(const Vector3<T>& vec);
        Vector3<T>& operator-=(const Vector3<T>& vec);
        Vector3<T> operator*(float value);
        Vector3<T>& operator*=(float value);
        Vector3<T> operator/(float value);
        Vector3<T>& operator/=(float value);
        Vector3<T>& operator=(const Vector3<T>& vec);
        bool operator ==(const Vector3<T>& vec);
        bool operator !=(const Vector3<T>& vec);

        float DotProduct(const Vector3<T>& vec);
        Vector3<T> CrossProduct(const Vector3<T>& vec);
        Vector3<T> Normalization();
        Vector3<T>& NormalizationThis();
        float Distance(const Vector3<T>& vec);
        float Magnitude();



        T GetX();
        T GetY();
        T GetZ();
	private:
		T _X;
		T _Y;
		T _Z;
	};
}