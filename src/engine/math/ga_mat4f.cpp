/*
** RPI Game Architecture Engine
**
** Portions adapted from:
** Viper Engine - Copyright (C) 2016 Velan Studios - All Rights Reserved
**
** This file is distributed under the MIT License. See LICENSE.txt.
*/

#include "math/ga_mat4f.h"

#include "math/ga_math.h"

#include <cmath>

// x is Col, Y = ROW
void ga_mat4f::make_identity()
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			data[i][j] = (i == j ? 1 : 0);
		}
	}
}

void ga_mat4f::make_translation(const ga_vec3f& __restrict t)
{
	data[0][3] = t.x;
	data[1][3] = t.y;
	data[2][3] = t.z;
}

void ga_mat4f::make_scaling(float s)
{
	for (int i = 0; i < 4; i++) {
		data[i][i] *= s;
	}
}

void ga_mat4f::make_rotation_x(float angle)
{
	data[1][1] *= cosf(angle * deg2Rad);
	data[1][2] *= sinf(angle * deg2Rad);
	data[2][1] *= -sinf(angle * deg2Rad);
	data[2][2] *= cosf(angle * deg2Rad);
}

void ga_mat4f::make_rotation_y(float angle)
{
	data[0][0] *= cosf(angle * deg2Rad);
	data[0][2] *= -sinf(angle * deg2Rad);
	data[2][0] *= sinf(angle * deg2Rad);
	data[2][2] *= cosf(angle * deg2Rad);
}

void ga_mat4f::make_rotation_z(float angle)
{
	data[0][0] *= cosf(angle * deg2Rad);
	data[0][1] *= -sinf(angle * deg2Rad);
	data[1][0] *= sinf(angle * deg2Rad);
	data[1][1] *= cosf(angle * deg2Rad);
}

void ga_mat4f::translate(const ga_vec3f& __restrict t)
{
	ga_mat4f tmp;
	tmp.make_translation(t);
	(*this) *= tmp;
}

void ga_mat4f::scale(float s)
{
	ga_mat4f tmp;
	tmp.make_scaling(s);
	(*this) *= tmp;
}

void ga_mat4f::rotate_x(float angle)
{
	ga_mat4f tmp;
	tmp.make_rotation_x(angle);
	(*this) *= tmp;
}

void ga_mat4f::rotate_y(float angle)
{
	ga_mat4f tmp;
	tmp.make_rotation_y(angle);
	(*this) *= tmp;
}

void ga_mat4f::rotate_z(float angle)
{
	ga_mat4f tmp;
	tmp.make_rotation_z(angle);
	(*this) *= tmp;
}

ga_mat4f ga_mat4f::operator*(const ga_mat4f& __restrict b) const
{
	ga_mat4f result;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			int res = 0;
			for (int k = 0; k < 4; k++) {
				res += this->data[i][k] * b.data[k][j];
			}
			result.data[i][j] = res;
		}
	}
	return result;
	
	
}

ga_mat4f& ga_mat4f::operator*=(const ga_mat4f& __restrict m)
{
	(*this) = (*this) * m;
	return (*this);
}

ga_vec4f ga_mat4f::transform(const ga_vec4f& __restrict in) const
{
	ga_vec4f result;

	result.x = (in.x * this->data[0][0]) + (in.y * this->data[0][1]) + (in.z * this->data[0][2]) + (in.w * this->data[0][3]);
	result.y = (in.x * this->data[1][0]) + (in.y * this->data[1][1]) + (in.z * this->data[1][2]) + (in.w * this->data[1][3]);
	result.z = (in.x * this->data[2][0]) + (in.y * this->data[2][1]) + (in.z * this->data[2][2]) + (in.w * this->data[2][3]);
	result.w = (in.x * this->data[3][0]) + (in.y * this->data[3][1]) + (in.z * this->data[3][2]) + (in.w * this->data[3][3]);

	return result;
}

ga_vec3f ga_mat4f::transform_vector(const ga_vec3f& __restrict in) const
{
	ga_vec3f result;
	result.x = (in.x * this->data[0][0]) + (in.y * this->data[0][1]) + (in.z * this->data[0][2]);
	result.y = (in.x * this->data[1][0]) + (in.y * this->data[1][1]) + (in.z * this->data[1][2]);
	result.z = (in.x * this->data[2][0]) + (in.y * this->data[2][1]) + (in.z * this->data[2][2]);
	return result;

}

ga_vec3f ga_mat4f::transform_point(const ga_vec3f& __restrict in) const
{
	// TODO: Homework 2

	return ga_vec3f::zero_vector();
}

void ga_mat4f::transpose()
{
	
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < i ; j++) {
			float temp = this->data[i][j];
			this->data[i][j] = this->data[j][i];
			this->data[j][i] = temp;
		}
	}
	
}

bool ga_mat4f::equal(const ga_mat4f& __restrict b)
{
	bool is_not_equal = false;
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			is_not_equal = is_not_equal || !ga_equalf(data[i][j], b.data[i][j]);
		}
	}
	return !is_not_equal;
}
