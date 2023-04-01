#ifndef __VEC_H__
#define __VEC_H__
#include<math.h>
template <typename T>
struct vec3
{
	union {
		struct { T x, y, z; };
		struct { T r, g, b; };
		T raw[3];
	};
	T& operator [] (int i) { return raw[i]; }
	const T& operator [] (int i) const { return raw[i]; }
	vec3() :x(0), y(0), z(0) {}
	vec3(T a, T b, T c) : x(a), y(b), z(c) {}
	vec3(T a) : x(a), y(a), z(a) {}
	inline vec3<T> operator + (const vec3<T>& temp) { return vec3<T>(temp.x + x, temp.y + y, temp.z + z); }
	inline vec3<T> operator + (const T& temp) { return vec3<T>(temp + x, temp + y, temp + z); }
	inline void operator += (const vec3<T>& temp) { x += temp.x; y += temp.y; z += temp.z; }

	inline vec3<T> operator - (const vec3<T>& temp) { return vec3<T>(x - temp.x, y - temp.y, z - temp.z); }
	inline void operator -= (const vec3<T>& temp) { x -= temp.x; y -= temp.y; z -= temp.z; }

	inline vec3<T> operator * (const vec3<T>& temp) { return vec3<T>(x * temp.x, y * temp.y, z * temp.z); }
	inline vec3<T> operator * (const T& temp) { return vec3<T>(x * temp, y * temp, z * temp); }
	inline void operator *= (const vec3<T>& temp) { x *= temp.x; y *= temp.y; z *= temp.z; }

	inline vec3<T> operator / (const vec3<T>& temp) { return vec3<T>(x / temp.x, y / temp.y, z / temp.z); }
	inline vec3<T> operator / (const T& temp) { return vec3<T>(x / temp, y / temp, z / temp); }
	inline void operator /= (const vec3<T>& temp) { x /= temp.x; y /= temp.y; z /= temp.z; }
	inline void operator /= (const T& temp) { x /= temp; y /= temp; z /= temp; }

	inline vec3<T> operator ^ (const vec3<T>& temp) { return vec3<T>(y * temp.z - z * temp.y, z * temp.x - x * temp.z, x * temp.y - y * temp.x); }

	inline T Length() { return sqrt(x * x + y * y + z * z); }


	inline T dot(const vec3<T>& temp) { return x * temp.x + y * temp.y + z * temp.z; }

};
template <typename T>
inline vec3<T> operator * (T a, vec3<T>& temp) { return temp * a; }
template <typename T>
inline vec3<T> operator / (T a, vec3<T>& temp) { return vec3f(a / temp.x, a / temp.y, a / temp.z); }
template <typename T>
inline vec3<T> Min(vec3<T>& temp, vec3<T>& temp_) { return vec3f(fminf(temp.x, temp_.x), fminf(temp.y, temp_.y), fminf(temp.z, temp_.z)); }
template <typename T>
inline vec3<T> Max(vec3<T>& temp, vec3<T>& temp_) { return vec3f(fmaxf(temp.x, temp_.x), fmaxf(temp.y, temp_.y), fmaxf(temp.z, temp_.z)); }


typedef vec3<int> vec3i;
typedef vec3<float> vec3f;
typedef vec3<double> vec3d;

inline vec3f normalize(vec3f v) { return v / v.Length(); }
inline float dot(vec3f v, vec3f u) { return u.dot(v); }


template <typename T>
struct vec2
{
	union {
		struct { T x, y; };
		T raw[2];
	};
	vec2() :x(0), y(0) {}
	vec2(T a, T b) : x(a), y(b) {}
	inline vec2<T> operator + (const vec2<T>& temp) { return vec2<T>(temp.x + x, temp.y + y); }
	inline vec2<T> operator + (const T& temp) { return vec2<T>(temp + x, temp + y); }
	inline vec2<T> operator - (const vec2<T>& temp) { return vec2<T>(x - temp.x, y - temp.y); }

	inline vec2<T> operator * (const vec2<T>& temp) { return vec2<T>(x * temp.x, y * temp.y); }
	inline vec2<T> operator * (const T& temp) { return vec2<T>(x * temp, y * temp); }

	inline vec2<T> operator / (const vec2<T>& temp) { return vec2<T>(x / temp.x, y / temp.y); }
	inline vec2<T> operator / (const T& temp) { return vec2<T>(x / temp, y / temp); }

	inline T Length() { return sqrt(x * x + y * y); }
	inline T dot(const vec2<T>& temp) { return x * temp.x + y * temp.y; }

};
template <typename T>
inline vec2<T> operator * (T a, vec2<T>& temp) { return temp * a; }

typedef vec2<int> vec2i;
typedef vec2<float> vec2f;


template <typename T>
struct vec4
{
	union {
		struct { T x, y, z, w; };
		struct { T r, g, b, a; };
		T raw[4];
	};
};
typedef vec4<int> vec4i;
typedef vec4<float> vec4f;

template <typename T>
inline T absolute_Value(T a) {
	if (a > 0) return a;
	else
	{
		return -a;
	}
}

template <typename T>
inline void SWAP(T& a, T& b) {
	T temp = b;
	b = a;
	a = temp;
}


#endif