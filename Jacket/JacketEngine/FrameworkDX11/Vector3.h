#pragma once
#include<iostream>
#include<math.h>
#include<assert.h>
using namespace std;

/// <summary>
/// created from https://github.com/ThomasMillard123/FGAGC
/// </summary>
class Vector3A
{
public:
	Vector3A();
	Vector3A(float x, float y, float z);
	Vector3A(const Vector3A& Vec);

	Vector3A operator+(const Vector3A& vec);   //addition
	Vector3A& operator+=(const Vector3A& vec);//assign new result to vector
	Vector3A operator-(const Vector3A& vec); //substraction
	Vector3A& operator-=(const Vector3A& vec);//assign new result to vector
	Vector3A operator*(float value);    //multiplication
	Vector3A& operator*=(float value);  //assign new result to vector.
	Vector3A operator/(float value);    //division
	Vector3A& operator/=(float value);  //assign new result to vector
	Vector3A& operator=(const Vector3A& vec);



	float dot_product(const Vector3A& vec); //scalar dot_product
	Vector3A cross_product(const Vector3A& vec); //cross_product
	Vector3A normalization();   //normalized vector

	 //Scalar operations
	float square(); //gives square of the vector
	float distance(const Vector3A& vec); //distance between two vectors
	float magnitude();  //magnitude of the vector

	float x;
	float y;
	float z;

	bool operator !=(const Vector3A& vec);

};

