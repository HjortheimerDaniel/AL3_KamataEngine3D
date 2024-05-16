#pragma once
#include "Matrix4x4.h"
#include "Vector3.h"
#include "math.h"
#include "cmath"
#include "iostream"

	Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);

	Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rot, const Vector3& translate);

	//Matrix4x4 Inverse(Matrix4x4& m1);

	Matrix4x4 MakeRotateMatrixX(float radian);

	Matrix4x4 MakeRotateMatrixY(float radian);

	Matrix4x4 MakeRotateMatrixZ(float radian);

	Vector3 Add(const Vector3& v1, const Vector3& v2);


