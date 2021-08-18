#pragma once

#include <cstdint>
#include <iostream>
#include <limits>
#include <math.h>
#include <algorithm>
#include "Vector.h"

namespace REngine{

    template<typename T, size_t RowSize, size_t ColSize>
    constexpr size_t ElementCount(T(&)[RowSize][ColSize]){return RowSize * ColSize;}

    template<typename T, int RowSize, int ColSize>
    struct Matrix{

        union{T data[RowSize][ColSize];};

        T* operator[](int rowIndex){
            return data[rowIndex];
        }

        const T* operator[](int rowIndex) const {
            return data[rowIndex];
        }

        operator T*(){
            return &data[0][0];
        }

        operator const T*() const {
            return static_cast<const T*>(&data[0][0]);
        }

        bool operator==(const Matrix& m){

            for(int r = 0; r < RowSize; ++r){
                for(int c = 0; c < ColSize; ++c){

                    if(data[r][c] != m[r][c])
                        return false;
                    
                }
            }
            
            return true;
        }
        
        bool operator!=(const Matrix& m){

            for(int r = 0; r < RowSize; ++r){
                for(int c = 0; c < ColSize; ++c){

                    if(data[r][c] != m[r][c])
                        return true;
                    
                }
            }
            
            return false;
        }

    };

    typedef Matrix<float, 4, 4> Matrix4x4f;

    std::ostream& operator<<(std::ostream& out, const Matrix4x4f& matrix){

        for(int r = 0; r < 4; ++r){
            for(int c = 0; c < 4; ++c){

                if(r != 3 || c != 3)
                    out<<matrix[r][c]<<",";
                else
                    out<<matrix[r][c];
                
            }
            out<<'\n';
        }

        return out;
        
    }

    template<typename T, int RowSize, int ColSize>
    inline void transpose(Matrix<T, RowSize, ColSize>& result, Matrix<T, RowSize, ColSize>& m){

        for(int r = 0; r < RowSize; ++r){
            for(int c = 0; c < ColSize; ++c){
                
                result[c][r] = m[r][c];

            }
        }

    }

    template<typename T, int RowSize, int ColSize>
    inline void TransposeInPlace(Matrix<T, RowSize, ColSize> m){

        Matrix<T, RowSize, ColSize> result;
        for(int r = 0; r < RowSize; ++r){
            for(int c = 0; c < ColSize; ++c){
                
                result[c][r] = m[r][c];

            }
        }

        m = result;

    }

    template<typename T, int RowSize, int ColSize>
    inline void MatrixAdd(Matrix<T, RowSize, ColSize>& result, const Matrix<T, RowSize, ColSize> m1, const Matrix<T, RowSize, ColSize> m2){

        for(int r = 0; r < RowSize; ++r){
            for(int c = 0; c < ColSize; ++c){

                result[r][c] = m1[r][c] + m2[r][c];
                
            }
        }
        
    }

    template<typename T, int RowSize, int ColSize>
    inline void MatrixSub(Matrix<T, RowSize, ColSize>& result, const Matrix<T, RowSize, ColSize> m1, const Matrix<T, RowSize, ColSize> m2){

        for(int r = 0; r < RowSize; ++r){
            for(int c = 0; c < ColSize; ++c){

                result[r][c] = m1[r][c] - m2[r][c];
                
            }
        }
        
    }

    template<typename T, int Da, int Db, int Dc>
    inline void MatrixMultiplyBy(Matrix<T, Da, Dc>& result, const Matrix<T, Da, Db>& m1, const Matrix<T, Db, Dc>& m2){

        Matrix<T, Da, Dc> tmp;
        for(int a = 0; a < Da; ++a){
            for(int c = 0; c < Dc; ++c){

                T sum = 0;
                for(int b = 0; b < Db; ++b){
                    sum += m1[a][b] * m2[b][c];
                }
                tmp[a][c] = sum;
                
            }
        }
        for(int a = 0; a < Da; ++a){
            for(int c = 0; c < Dc; ++c){
                result[a][c] = tmp[a][c];
            }
        }
        
    }

    template<typename T, int Da, int Db, int Dc>
    Matrix<T, Da, Dc> operator*(const Matrix<T, Da, Db>& m1, const Matrix<T, Db, Dc>& m2){

        Matrix<T, Da, Dc> result;
        MatrixMultiplyBy(result, m1, m2);
        return result;
        
    }

    template<typename T, int d>
    inline void MatrixSwapRows(Matrix<T, d, d> m, int row1, int row2){

        for(int c = 0; c < d; ++c){

            T t = m[row1][c];
            m[row1][c] = m[row2][c];
            m[row2][c] = t;
            
        }
        
    }
    
    template<typename T, int d>
    inline void MatrixSwapCols(Matrix<T, d, d> m, int col1, int col2){

        for(int r = 0; r < d; ++r){

            T t = m[col1][r];
            m[col1][r] = m[col2][r];
            m[col2][r] = t;
            
        }
        
    }

    //Inverse
    template <typename T, int d>
	inline float MatrixInverse(Matrix<T, d, d>& out, const Matrix<T, d, d>& in) {
		Matrix<T, d, d> m = in;
		float fDet = 1.0f;
		int f = 1;
		int is[d];
		int js[d];
		int k, i, j, l;
		int dd = d;

		for (k = 0; k < d; k++)
		{
			float fMax = 0.0f;
			for (i = k; i < d; i++)
			{
				for (j = k; j < d; j++)
				{
					const float f = abs(m[i][j]);
					if (f > fMax)
					{
						fMax = f;
						is[k] = i;
						js[k] = j;
					}
				}
			}
			if (abs(fMax) < 0.00000001f)
				return 0;
			if (is[k] != k)
			{
				f = -f;
				for (l = 0; l < d; ++l) {
					T temp = m[k][l];
					m[k][l] = m[is[k]][l];
					m[is[k]][l] = temp;
				}
			}
			if (js[k] != k)
			{
				f = -f;
				for (l = 0; l < d; ++l) {
					T temp = m[l][k];
					m[l][k] = m[l][js[k]];
					m[l][js[k]] = temp;
				}
			}
			fDet *= m[k][k];
			m[k][k] = 1.0f / m[k][k];

			for (j = 0; j < d; j++)
			{
				if (j != k)
					m[k][j] *= m[k][k];
			}

			for (i = 0; i < d; i++)
			{
				if (i != k)
				{
					for (j = 0; j < d; j++)
					{
						if (j != k)
							m[i][j] = m[i][j] - m[i][k] * m[k][j];
					}
				}
			}
			for (i = 0; i < d; i++)
			{
				if (i != k)
					m[i][k] *= -m[k][k];
			}
		}
		for (k = d - 1; k >= 0; k--)
		{
			if (js[k] != k)
			{
				for (l = 0; l < d; ++l) {
					T temp = m[k][l];
					m[k][l] = m[js[k]][l];
					m[js[k]][l] = temp;
				}
			}
			if (is[k] != k)
			{
				for (l = 0; l < d; ++l) {
					T temp = m[l][k];
					m[l][k] = m[l][is[k]];
					m[l][is[k]] = temp;
				}
			}
		}
		out = m;
		return fDet * f;
	}

    Vector4f operator*(const Matrix4x4f& matrix, const Vector4f& vector){

        Vector4f tmp;
        for(int r = 0; r < 4; ++r){
            for(int c = 0; c < 4; ++c){
                tmp[r] += vector[c] * matrix[r][c];
            }
        }
        
        return tmp;

    }

    Matrix4x4f GetIdentityMatrix(){
        Matrix4x4f matrix = {
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        };

        return matrix;
    }

    inline void Transform(Vector4f& vector, Matrix4x4f& matrix){

        vector = matrix * vector;
        
    }

    inline void Transform(Vector3f& vector, Matrix4x4f& matrix){

        Vector4f tmp(vector);
        tmp = matrix * tmp;
        vector[0] = tmp[0];
        vector[1] = tmp[1];
        vector[2] = tmp[2];

    }

    inline void Translate(Matrix4x4f& matrix, const Vector3f& pos){

        Matrix4x4f translate = {{{
            {1.0f, 0.0f, 0.0f, -pos.x},
            {0.0f, 1.0f, 0.0f, -pos.y},
            {0.0f, 0.0f, 1.0f, -pos.z},
            {0.0f, 0.0f, 0.0f, 1.0f}
        }}};

        matrix = translate * matrix;

    }

    inline void Rotation(Matrix4x4f& matrix, const float& tangle, Vector3f& axis){

        Normalize(axis);
        Matrix4x4f tmp;
        float nx = axis.x;
        float ny = axis.y;
        float nz = axis.z;
        float costheta = std::cos(tangle);
        float minus_costheta = 1.0 - costheta;
        float sintheta = std::sin(tangle);
        tmp[0][0] = nx * nx * minus_costheta + costheta;
        tmp[0][1] = nx * ny * minus_costheta - nz * sintheta;
        tmp[0][2] = nx * nz * minus_costheta + ny * sintheta;

        tmp[1][0] = nx * ny * minus_costheta + nz * sintheta;
        tmp[1][1] = ny * ny * minus_costheta + costheta;
        tmp[1][2] = ny * nz * minus_costheta - nx * sintheta;

        tmp[2][0] = nx * nz * minus_costheta - ny * sintheta;
        tmp[2][1] = ny * nz * minus_costheta + nx * sintheta;
        tmp[2][2] = nz * nz * minus_costheta + costheta;

        matrix = tmp * matrix;

    }

    inline void LookAt(Matrix4x4f& matrix, const Vector3f pos, const Vector3f& goal, const Vector3f& WorldUp){

        Matrix4x4f translate = GetIdentityMatrix();
        Translate(translate, pos);

        Vector3f front = goal - pos;
        Vector3f right(1.0f);
        CrossProduct(right, front, WorldUp);
        Vector3f up(1.0f);
        CrossProduct(up, right, front);
        Matrix4x4f cameraSpaceMatrix = {
            right.x, right.y, right.z, 0.0f,
            up.x, up.y, up.z, 0.0f,
            front.x, front.y, front.z, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        };

        matrix = cameraSpaceMatrix * translate * matrix;
        
    }

    inline void OrthoProjection(Matrix4x4f& matrix, const float width, const float height, const float zn, const float zf){

        Matrix4x4f projection = {
            2 / width,       0.0f,             0.0f,           0.0f,
                 0.0f, 2 / height,             0.0f,           0.0f,
                 0.0f,       0.0f, 1.0f / (zn - zf), zn / (zn - zf),
                 0.0f,       0.0f,             0.0f,           1.0f
        };

        matrix = projection * matrix;
        
    }

    inline void PerspectiveProjection(Matrix4x4f& matrix, const float fov, const float aspect, const float zn, const float zf){

        auto yscale = 1.0f / tanf(fov * 0.5f);
		auto xscale = yscale / aspect;

		Matrix4x4f projection = {
		xscale,	  0.0f,           0.0f,                  0.0f,
		  0.0f,	yscale,	          0.0f,                  0.0f,
		  0.0f,   0.0f, zf / (zn - zf), (zn * zf) / (zn - zf),
		  0.0f,	  0.0f,          -1.0f,	                 0.0f
		};
		matrix = projection * matrix;
        
    }

}