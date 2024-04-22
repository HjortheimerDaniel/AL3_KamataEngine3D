#include "OwnMath.h"

Matrix4x4 Multiply(Matrix4x4& m1, Matrix4x4& m2)
{
	Matrix4x4 result{
		m1.m[0][0] * m2.m[0][0] + m1.m[0][1] * m2.m[1][0] + m1.m[0][2] * m2.m[2][0] + m1.m[0][3] * m2.m[3][0], /*here*/ m1.m[0][0] * m2.m[0][1] + m1.m[0][1] * m2.m[1][1] + m1.m[0][2] * m2.m[2][1] + m1.m[0][3] * m2.m[3][1], /*here*/ m1.m[0][0] * m2.m[0][2] + m1.m[0][1] * m2.m[1][2] + m1.m[0][2] * m2.m[2][2] + m1.m[0][3] * m2.m[3][2], /*here*/ m1.m[0][0] * m2.m[0][3] + m1.m[0][1] * m2.m[1][3] + m1.m[0][2] * m2.m[2][3] + m1.m[0][3] * m2.m[3][3],
		m1.m[1][0] * m2.m[0][0] + m1.m[1][1] * m2.m[1][0] + m1.m[1][2] * m2.m[2][0] + m1.m[1][3] * m2.m[3][0], /*here*/ m1.m[1][0] * m2.m[0][1] + m1.m[1][1] * m2.m[1][1] + m1.m[1][2] * m2.m[2][1] + m1.m[1][3] * m2.m[3][1], /*here*/ m1.m[1][0] * m2.m[0][2] + m1.m[1][1] * m2.m[1][2] + m1.m[1][2] * m2.m[2][2] + m1.m[1][3] * m2.m[3][2], /*here*/ m1.m[1][0] * m2.m[0][3] + m1.m[1][1] * m2.m[1][3] + m1.m[1][2] * m2.m[2][3] + m1.m[1][3] * m2.m[3][3],
		m1.m[2][0] * m2.m[0][0] + m1.m[2][1] * m2.m[1][0] + m1.m[2][2] * m2.m[2][0] + m1.m[2][3] * m2.m[3][0], /*here*/ m1.m[2][0] * m2.m[0][1] + m1.m[2][1] * m2.m[1][1] + m1.m[2][2] * m2.m[2][1] + m1.m[2][3] * m2.m[3][1], /*here*/ m1.m[2][0] * m2.m[0][2] + m1.m[2][1] * m2.m[1][2] + m1.m[2][2] * m2.m[2][2] + m1.m[2][3] * m2.m[3][2], /*here*/ m1.m[2][0] * m2.m[0][3] + m1.m[2][1] * m2.m[1][3] + m1.m[2][2] * m2.m[2][3] + m1.m[2][3] * m2.m[3][3],
		m1.m[3][0] * m2.m[0][0] + m1.m[3][1] * m2.m[1][0] + m1.m[3][2] * m2.m[2][0] + m1.m[3][3] * m2.m[3][0], /*here*/ m1.m[3][0] * m2.m[0][1] + m1.m[3][1] * m2.m[1][1] + m1.m[3][2] * m2.m[2][1] + m1.m[3][3] * m2.m[3][1], /*here*/ m1.m[3][0] * m2.m[0][2] + m1.m[3][1] * m2.m[1][2] + m1.m[3][2] * m2.m[2][2] + m1.m[3][3] * m2.m[3][2], /*here*/ m1.m[3][0] * m2.m[0][3] + m1.m[3][1] * m2.m[1][3] + m1.m[3][2] * m2.m[2][3] + m1.m[3][3] * m2.m[3][3],

	};
	return result;
}

Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rot, const Vector3& translate)
{
	Matrix4x4 Scale{
		scale.x, 0, 0, 0,
		0, scale.y, 0, 0,
		0, 0, scale.z, 0,
		0, 0, 0, 1
	};

	Matrix4x4 Translate{
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		translate.x, translate.y, translate.z, 1
	};

	Matrix4x4 MakeRotateMatrixZ{
			cosf(rot.z), sinf(rot.z), 0, 0,
			-sinf(rot.z), cosf(rot.z), 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
	};

	Matrix4x4 MakeRotateMatrixX{
			1, 0, 0, 0,
			0, cosf(rot.x), sinf(rot.x), 0,
			0, -sinf(rot.x), cosf(rot.x), 0,
			0, 0, 0, 1
	};

	Matrix4x4 MakeRotateMatrixY{
			cosf(rot.y), 0, -sinf(rot.y), 0,
			0, 1, 0, 0,
			sinf(rot.y), 0, cosf(rot.y), 0,
			0, 0, 0, 1
	};

	Matrix4x4 RotateYZ = Multiply(MakeRotateMatrixY, MakeRotateMatrixZ);

	Matrix4x4 Rotate = Multiply(MakeRotateMatrixX, RotateYZ);
	Matrix4x4 ScaleRotate = Multiply(Scale, Rotate);
	Matrix4x4 result = Multiply(Translate, ScaleRotate);

	/*Matrix4x4 result{
		scale.x * Rotate.m[0][0], scale.x * Rotate.m[0][1], scale.x * Rotate.m[0][2], 0,
		scale.y * Rotate.m[1][0], scale.y * Rotate.m[1][1], scale.y * Rotate.m[1][2], 0,
		scale.z * Rotate.m[2][0], scale.z * Rotate.m[2][1], scale.z * Rotate.m[2][2], 0,
		translate.x, translate.y, translate.z, 1

	};*/

	return result;
}
