/*
 * Kodowanie Windows-1250, koniec wiersza CR+LF, test: Za???? g??l? ja??
 * Math - Modu? matematyczny
 * Dokumentacja: Patrz plik doc/Math.txt
 * Copyleft (C) 2007 Adam Sawicki
 * Licencja: GNU LGPL
 * Kontakt: mailto:sawickiap@poczta.onet.pl , http://regedit.gamedev.pl/
 */
#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif
#ifndef COMMON_MATH_H_
#define COMMON_MATH_H_

#ifdef USE_DIRECTX
	#include <windows.h> // bo bez tego w d3d9types.h s? b??dy bo nie zna DWORD itp.
	#include <d3d9types.h>
	#include <d3dx9math.h>
#endif

namespace common
{

// Szablon bazowy - nie dzia?a, specjalizacje b?d? dzia?a?
template <typename DestT, typename SrcT>
DestT & math_cast(const SrcT &x)
{
	assert(0 && "Unsupported type in math_cast.");
}


//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// PUNKT 2D Z LICZB CA?KOWITYCH

/*
Kompatybilny ze struktur? POINT z Win32API.
Nazywa si? tak dziwnie, bo POINT to w Windows API marko i robi problem z nazw?.
Konwersja do i ze stringa: "x,y", np. "10,1".
*/

struct POINT_
{
	union
	{
		struct
		{
			int x, y;
		};
		int v[2];
	};

	static const POINT_ ZERO;

	POINT_() { }
	POINT_(int x, int y) : x(x), y(y) { }

	bool operator == (const POINT_ &v) const { return x == v.x && y == v.y; }
	bool operator != (const POINT_ &v) const { return x != v.x || y != v.y; }

	POINT_ operator - () const { return POINT_(-x, -y); }
	POINT_ operator + (const POINT_ &v) const { return POINT_(x+v.x, y+v.y); }
	POINT_ operator - (const POINT_ &v) const { return POINT_(x-v.x, y-v.y); }
	POINT_ & operator += (const POINT_ &v) { x += v.x; y += v.y; return *this; }
	POINT_ & operator -= (const POINT_ &v) { x -= v.x; y -= v.y; return *this; }
	POINT_ & operator *= (int v) { x *= v; y *= v; return *this; }
	POINT_ & operator /= (int v) { x /= v; y /= v; return *this; }

	int & operator [] (uint4 Index) { return v[Index]; }
	const int & operator [] (uint4 Index) const { return v[Index]; }

	int * GetArray() { return &x; }
	const int * GetArray() const { return &x; }
};

inline POINT_ operator * (const POINT_ pt, int v) { return POINT_(pt.x*v, pt.y*v); }
inline POINT_ operator / (const POINT_ pt, int v) { return POINT_(pt.x/v, pt.y/v); }
inline POINT_ operator * (int v, const POINT_ pt) { return POINT_(pt.x*v, pt.y*v); }
inline POINT_ operator / (int v, const POINT_ pt) { return POINT_(pt.x/v, pt.y/v); }

// Konwersja do i z POINT z Win32API
#ifdef WIN32
	template <> inline ::POINT & math_cast<::POINT, POINT_>(const POINT_ &x) { return (::POINT&)(x); }
	template <> inline POINT_ & math_cast<POINT_, ::POINT>(const ::POINT &x) { return (POINT_&)(x); }
#endif

inline void swap(POINT_ &v1, POINT_ &v2)
{
	std::swap(v1.x, v2.x);
	std::swap(v1.y, v2.y);
}


//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// WEKTOR 2D, 3D i 4D Z FLOAT?W

/* Kompatybilny ze struktur? odpowiednio D3DXVECTOR2, D3DXVECTOR3 i D3DXVECTOR4
z D3DX. Konwersja do i ze stringa: "x,y,z", np. "10,-1,2.5".
*/

struct VEC2
{
	union
	{
		struct
		{
			float x, y;
		};
		float v[2];
	};

	static const VEC2 ZERO;
	static const VEC2 ONE;
	static const VEC2 POSITIVE_X;
	static const VEC2 POSITIVE_Y;
	static const VEC2 NEGATIVE_X;
	static const VEC2 NEGATIVE_Y;

	VEC2() { }
	VEC2(float x, float y) : x(x), y(y) { }
	VEC2(float *Array) : x(Array[0]), y(Array[1]) { }

	bool operator == (const VEC2 &v) const { return x == v.x && y == v.y; }
	bool operator != (const VEC2 &v) const { return x != v.x || y != v.y; }

	VEC2 operator - () const { return VEC2(-x, -y); }
	VEC2 operator + (const VEC2 &v) const { return VEC2(x+v.x, y+v.y); }
	VEC2 operator - (const VEC2 &v) const { return VEC2(x-v.x, y-v.y); }
	VEC2 & operator += (const VEC2 &v) { x += v.x; y += v.y; return *this; }
	VEC2 & operator -= (const VEC2 &v) { x -= v.x; y -= v.y; return *this; }
	VEC2 & operator *= (float v) { x *= v; y *= v; return *this; }
	VEC2 & operator /= (float v) { x /= v; y /= v; return *this; }

	float & operator [] (uint4 Index) { return v[Index]; }
	const float & operator [] (uint4 Index) const { return v[Index]; }

	float * GetArray() { return &x; }
	const float * GetArray() const { return &x; }
};

inline VEC2 operator * (const VEC2 pt, float v) { return VEC2(pt.x*v, pt.y*v); }
inline VEC2 operator / (const VEC2 pt, float v) { return VEC2(pt.x/v, pt.y/v); }
inline VEC2 operator * (float v, const VEC2 pt) { return VEC2(pt.x*v, pt.y*v); }
inline VEC2 operator / (float v, const VEC2 pt) { return VEC2(pt.x/v, pt.y/v); }

#ifdef USE_DIRECTX
	template <> inline ::D3DXVECTOR2 & math_cast<::D3DXVECTOR2, VEC2>(const VEC2 &x) { return (::D3DXVECTOR2&)(x); }
	template <> inline VEC2 & math_cast<VEC2, ::D3DXVECTOR2>(const ::D3DXVECTOR2 &x) { return (VEC2&)(x); }
#endif

inline void swap(VEC2 &v1, VEC2 &v2)
{
	std::swap(v1.x, v2.x);
	std::swap(v1.y, v2.y);
}

struct VEC3
{
	union
	{
		struct
		{
			float x, y, z;
		};
		float v[3];
	};

	static const VEC3 ZERO;
	static const VEC3 ONE;
	static const VEC3 POSITIVE_X;
	static const VEC3 POSITIVE_Y;
	static const VEC3 POSITIVE_Z;
	static const VEC3 NEGATIVE_X;
	static const VEC3 NEGATIVE_Y;
	static const VEC3 NEGATIVE_Z;

	VEC3() { }
	VEC3(float x, float y, float z) : x(x), y(y), z(z) { }
	VEC3(float *Array) : x(Array[0]), y(Array[1]), z(Array[2]) { }

	bool operator == (const VEC3 &v) const { return x == v.x && y == v.y && z == v.z; }
	bool operator != (const VEC3 &v) const { return x != v.x || y != v.y || z != v.z; }

	VEC3 operator - () const { return VEC3(-x, -y, -z); }
	VEC3 operator + (const VEC3 &v) const { return VEC3(x+v.x, y+v.y, z+v.z); }
	VEC3 operator - (const VEC3 &v) const { return VEC3(x-v.x, y-v.y, z-v.z); }
	VEC3 & operator += (const VEC3 &v) { x += v.x; y += v.y; z += v.z; return *this; }
	VEC3 & operator -= (const VEC3 &v) { x -= v.x; y -= v.y; z -= v.z; return *this; }
	VEC3 & operator *= (float v) { x *= v; y *= v; z *= v; return *this; }
	VEC3 & operator /= (float v) { x /= v; y /= v; z /= v; return *this; }

	float & operator [] (uint4 Index) { return v[Index]; }
	const float & operator [] (uint4 Index) const { return v[Index]; }

	float * GetArray() { return &x; }
	const float * GetArray() const { return &x; }
};

inline VEC3 operator * (const VEC3 pt, float v) { return VEC3(pt.x*v, pt.y*v, pt.z*v); }
inline VEC3 operator / (const VEC3 pt, float v) { return VEC3(pt.x/v, pt.y/v, pt.z/v); }
inline VEC3 operator * (float v, const VEC3 pt) { return VEC3(pt.x*v, pt.y*v, pt.z*v); }
inline VEC3 operator / (float v, const VEC3 pt) { return VEC3(pt.x/v, pt.y/v, pt.z/v); }

#ifdef USE_DIRECTX
	template <> inline ::D3DXVECTOR3 & math_cast<::D3DXVECTOR3, VEC3>(const VEC3 &x) { return (::D3DXVECTOR3&)(x); }
	template <> inline VEC3 & math_cast<VEC3, ::D3DXVECTOR3>(const ::D3DXVECTOR3 &x) { return (VEC3&)(x); }
#endif

inline void swap(VEC3 &v1, VEC3 &v2)
{
	std::swap(v1.x, v2.x);
	std::swap(v1.y, v2.y);
	std::swap(v1.z, v2.z);
}

struct VEC4
{
	union
	{
		struct
		{
			float x, y, z, w;
		};
		float v[4];
	};

	static const VEC4 ZERO;
	static const VEC4 ONE;
	static const VEC4 POSITIVE_X;
	static const VEC4 POSITIVE_Y;
	static const VEC4 POSITIVE_Z;
	static const VEC4 POSITIVE_W;
	static const VEC4 NEGATIVE_X;
	static const VEC4 NEGATIVE_Y;
	static const VEC4 NEGATIVE_Z;
	static const VEC4 NEGATIVE_W;

	VEC4() { }
	VEC4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) { }
	VEC4(float *Array) : x(Array[0]), y(Array[1]), z(Array[2]), w(Array[3]) { }

	bool operator == (const VEC4 &v) const { return x == v.x && y == v.y && z == v.z && w == v.w; }
	bool operator != (const VEC4 &v) const { return x != v.x || y != v.y || z != v.z || w != v.w; }

	VEC4 operator - () const { return VEC4(-x, -y, -z, -w); }
	VEC4 operator + (const VEC4 &v) const { return VEC4(x+v.x, y+v.y, z+v.z, w+v.w); }
	VEC4 operator - (const VEC4 &v) const { return VEC4(x-v.x, y-v.y, z-v.z, w-v.w); }
	VEC4 & operator += (const VEC4 &v) { x += v.x; y += v.y; z += v.z; w += v.w; return *this; }
	VEC4 & operator -= (const VEC4 &v) { x -= v.x; y -= v.y; z -= v.z; w -= v.w; return *this; }
	VEC4 & operator *= (float v) { x *= v; y *= v; z *= v; w *= v; return *this; }
	VEC4 & operator /= (float v) { x /= v; y /= v; z /= v; w /= v; return *this; }

	float & operator [] (uint4 Index) { return v[Index]; }
	const float & operator [] (uint4 Index) const { return v[Index]; }

	float * GetArray() { return &x; }
	const float * GetArray() const { return &x; }
};

inline VEC4 operator * (const VEC4 pt, float v) { return VEC4(pt.x*v, pt.y*v, pt.z*v, pt.w*v); }
inline VEC4 operator / (const VEC4 pt, float v) { return VEC4(pt.x/v, pt.y/v, pt.z/v, pt.w/v); }
inline VEC4 operator * (float v, const VEC4 pt) { return VEC4(pt.x*v, pt.y*v, pt.z*v, pt.w*v); }
inline VEC4 operator / (float v, const VEC4 pt) { return VEC4(pt.x/v, pt.y/v, pt.z/v, pt.w/v); }

#ifdef USE_DIRECTX
	template <> inline ::D3DXVECTOR4 & math_cast<::D3DXVECTOR4, VEC4>(const VEC4 &x) { return (::D3DXVECTOR4&)(x); }
	template <> inline VEC4 & math_cast<VEC4, ::D3DXVECTOR4>(const ::D3DXVECTOR4 &x) { return (VEC4&)(x); }
#endif

inline void swap(VEC4 &v1, VEC4 &v2)
{
	std::swap(v1.x, v2.x);
	std::swap(v1.y, v2.y);
	std::swap(v1.z, v2.z);
	std::swap(v1.w, v2.w);
}

// Zwraca kwadrat d?ugo?ci wektora
inline float LengthSq(const VEC2 &v)
{
	return v.x*v.x + v.y*v.y;
}
inline float LengthSq(const VEC3 &v)
{
	return v.x*v.x + v.y*v.y + v.z*v.z;
}
inline float LengthSq(const VEC4 &v)
{
	return v.x*v.x + v.y*v.y + v.z*v.z + v.w*v.w;
}

// Zwraca d?ugo?? wektora
inline float Length(const VEC2 &v)
{
	return sqrtf(LengthSq(v));
}
inline float Length(const VEC3 &v)
{
	return sqrtf(LengthSq(v));
}
inline float Length(const VEC4 &v)
{
	return sqrtf(LengthSq(v));
}

// Zwraca wektor z?o?ony z mniejszych sk?adowych podanych wektor?w
inline void Min(VEC2 *Out, const VEC2 &v1, const VEC2 &v2)
{
	Out->x = std::min(v1.x, v2.x);
	Out->y = std::min(v1.y, v2.y);
}
inline void Min(VEC3 *Out, const VEC3 &v1, const VEC3 &v2)
{
	Out->x = std::min(v1.x, v2.x);
	Out->y = std::min(v1.y, v2.y);
	Out->z = std::min(v1.z, v2.z);
}
inline void Min(VEC4 *Out, const VEC4 &v1, const VEC4 &v2)
{
	Out->x = std::min(v1.x, v2.x);
	Out->y = std::min(v1.y, v2.y);
	Out->z = std::min(v1.z, v2.z);
	Out->w = std::min(v1.w, v2.w);
}

// Zwraca wektor z?o?ony z wi?kszych sk?adowych podanych wektor?w
inline void Max(VEC2 *Out, const VEC2 &v1, const VEC2 &v2)
{
	Out->x = std::max(v1.x, v2.x);
	Out->y = std::max(v1.y, v2.y);
}
inline void Max(VEC3 *Out, const VEC3 &v1, const VEC3 &v2)
{
	Out->x = std::max(v1.x, v2.x);
	Out->y = std::max(v1.y, v2.y);
	Out->z = std::max(v1.z, v2.z);
}
inline void Max(VEC4 *Out, const VEC4 &v1, const VEC4 &v2)
{
	Out->x = std::max(v1.x, v2.x);
	Out->y = std::max(v1.y, v2.y);
	Out->z = std::max(v1.z, v2.z);
	Out->w = std::max(v1.w, v2.w);
}

// Operacje na poszczeg?lnych sk?adowych wektor?w

inline void Mul(VEC2 *Out, const VEC2 &v, float f)
{
	Out->x = v.x * f;
	Out->y = v.y * f;
}
inline void Mul(VEC3 *Out, const VEC3 &v, float f)
{
	Out->x = v.x * f;
	Out->y = v.y * f;
	Out->z = v.z * f;
}
inline void Mul(VEC4 *Out, const VEC4 &v, float f)
{
	Out->x = v.x * f;
	Out->y = v.y * f;
	Out->z = v.z * f;
	Out->w = v.w * f;
}

inline void Add(VEC2 *Out, const VEC2 &v1, const VEC2 &v2)
{
	Out->x = v1.x + v2.x;
	Out->y = v1.y + v2.y;
}
inline void Add(VEC3 *Out, const VEC3 &v1, const VEC3 &v2)
{
	Out->x = v1.x + v2.x;
	Out->y = v1.y + v2.y;
	Out->z = v1.z + v2.z;
}
inline void Add(VEC4 *Out, const VEC4 &v1, const VEC4 &v2)
{
	Out->x = v1.x + v2.x;
	Out->y = v1.y + v2.y;
	Out->z = v1.z + v2.z;
	Out->w = v1.w + v2.w;
}

inline void Sub(VEC2 *Out, const VEC2 &v1, const VEC2 &v2)
{
	Out->x = v1.x - v2.x;
	Out->y = v1.y - v2.y;
}
inline void Sub(VEC3 *Out, const VEC3 &v1, const VEC3 &v2)
{
	Out->x = v1.x - v2.x;
	Out->y = v1.y - v2.y;
	Out->z = v1.z - v2.z;
}
inline void Sub(VEC4 *Out, const VEC4 &v1, const VEC4 &v2)
{
	Out->x = v1.x - v2.x;
	Out->y = v1.y - v2.y;
	Out->z = v1.z - v2.z;
	Out->w = v1.w - v2.w;
}

inline void Mul(VEC2 *Out, const VEC2 &v1, const VEC2 &v2)
{
	Out->x = v1.x * v2.x;
	Out->y = v1.y * v2.y;
}
inline void Mul(VEC3 *Out, const VEC3 &v1, const VEC3 &v2)
{
	Out->x = v1.x * v2.x;
	Out->y = v1.y * v2.y;
	Out->z = v1.z * v2.z;
}
inline void Mul(VEC4 *Out, const VEC4 &v1, const VEC4 &v2)
{
	Out->x = v1.x * v2.x;
	Out->y = v1.y * v2.y;
	Out->z = v1.z * v2.z;
	Out->w = v1.w * v2.w;
}

inline void Div(VEC2 *Out, const VEC2 &v1, const VEC2 &v2)
{
	Out->x = v1.x / v2.x;
	Out->y = v1.y / v2.y;
}
inline void Div(VEC3 *Out, const VEC3 &v1, const VEC3 &v2)
{
	Out->x = v1.x / v2.x;
	Out->y = v1.y / v2.y;
	Out->z = v1.z / v2.z;
}
inline void Div(VEC4 *Out, const VEC4 &v1, const VEC4 &v2)
{
	Out->x = v1.x / v2.x;
	Out->y = v1.y / v2.y;
	Out->z = v1.z / v2.z;
	Out->w = v1.w / v2.w;
}

// Iloczyn skalarny wektor?w
inline float Dot(const VEC2 &v1, const VEC2 &v2)
{
	return v1.x*v2.x + v1.y*v2.y;
}
inline float Dot(const VEC3 &v1, const VEC3 &v2)
{
	return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}
inline float Dot(const VEC4 &v1, const VEC4 &v2)
{
	return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z + v1.w*v2.w;
}

// Odwraca znak sk?adowych wektora
inline void Minus(VEC2 *Out, VEC2 &v) { Out->x = -v.x; Out->y = -v.y; }
inline void Minus(VEC3 *Out, VEC3 &v) { Out->x = -v.x; Out->y = -v.y; Out->z = -v.z; }
inline void Minus(VEC4 *Out, VEC4 &v) { Out->x = -v.x; Out->y = -v.y; Out->z = -v.z; Out->w = -v.w; }
inline void Minus(VEC2 *InOut) { InOut->x = -InOut->x; InOut->y = -InOut->y; }
inline void Minus(VEC3 *InOut) { InOut->x = -InOut->x; InOut->y = -InOut->y; InOut->z = -InOut->z; }
inline void Minus(VEC4 *InOut) { InOut->x = -InOut->x; InOut->y = -InOut->y; InOut->z = -InOut->z; InOut->w = -InOut->w; }

// Iloczyn wektorowy dw?ch wektor?w daj?cy liczb? m?wi?c? czy drugi wskazuje
// na lewo, czy na prawo wzgl?dem pierwszego
// W uk?adzie gdzie X jest w prawo a Y do g?ry, > 0 znaczy na lewo
// W uk?adzie gdzie X jest w prawo a Y w d??, > 0 znaczy na prawo
inline float Cross(const VEC2 &v1, const VEC2 &v2)
{
	return v1.x*v2.y - v1.y*v2.x;
}

// Iloczyn wektorowy dw?ch wektor?w 3D
inline void Cross(VEC3 *Out, const VEC3 &v1, const VEC3 &v2)
{
	Out->x = v1.y * v2.z - v1.z * v2.y;
	Out->y = v1.z * v2.x - v1.x * v2.z;
	Out->z = v1.x * v2.y - v1.y * v2.x;
}

// Kwadrat odleg?o?ci mi?dzy dwoma punktami
inline float DistanceSq(const VEC2 &p1, const VEC2 &p2)
{
	return LengthSq(p2-p1);
}
inline float DistanceSq(const VEC3 &p1, const VEC3 &p2)
{
	return LengthSq(p2-p1);
}
inline float DistanceSq(const VEC4 &p1, const VEC4 &p2)
{
	return LengthSq(p2-p1);
}

// Odleg?o?? mi?dzy dwoma punktami
inline float Distance(const VEC2 &p1, const VEC2 &p2)
{
	return Length(p2-p1);
}
inline float Distance(const VEC3 &p1, const VEC3 &p2)
{
	return Length(p2-p1);
}
inline float Distance(const VEC4 &p1, const VEC4 &p2)
{
	return Length(p2-p1);
}

// Liniowa interpolacja wektor?w
inline void Lerp(VEC2 *Out, const VEC2 &v1, const VEC2 &v2, float t)
{
	Out->x = v1.x + t*(v2.x-v1.x);
	Out->y = v1.y + t*(v2.y-v1.y);
}
inline void Lerp(VEC3 *Out, const VEC3 &v1, const VEC3 &v2, float t)
{
	Out->x = v1.x + t*(v2.x-v1.x);
	Out->y = v1.y + t*(v2.y-v1.y);
	Out->z = v1.z + t*(v2.z-v1.z);
}
inline void Lerp(VEC4 *Out, const VEC4 &v1, const VEC4 &v2, float t)
{
	Out->x = v1.x + t*(v2.x-v1.x);
	Out->y = v1.y + t*(v2.y-v1.y);
	Out->z = v1.z + t*(v2.z-v1.z);
	Out->w = v1.w + t*(v2.w-v1.w);
}

// Normalizuje wektor, czyli zmienia mu d?ugo?? na 1
inline void Normalize(VEC2 *Out, const VEC2 &v)
{
	float l = 1.0f / Length(v);
	Out->x = v.x * l;
	Out->y = v.y * l;
}
inline void Normalize(VEC3 *Out, const VEC3 &v)
{
	float l = 1.0f / Length(v);
	Out->x = v.x * l;
	Out->y = v.y * l;
	Out->z = v.z * l;
}
inline void Normalize(VEC4 *Out, const VEC4 &v)
{
	float l = 1.0f / Length(v);
	Out->x = v.x * l;
	Out->y = v.y * l;
	Out->z = v.z * l;
	Out->w = v.w * l;
}

// Normalizuje wektor w miejscu
inline void Normalize(VEC2 *v)
{
	float rcl = 1.0f / Length(*v);
	v->x *= rcl;
	v->y *= rcl;
}
inline void Normalize(VEC3 *v)
{
	float rcl = 1.0f / Length(*v);
	v->x *= rcl;
	v->y *= rcl;
	v->z *= rcl;
}
inline void Normalize(VEC4 *v)
{
	float rcl = 1.0f / Length(*v);
	v->x *= rcl;
	v->y *= rcl;
	v->z *= rcl;
	v->w *= rcl;
}

// Konwersja z wektora 3D na 4D dopisuj?ca W=1
inline void Vec3ToVec4(VEC4 *Out, const VEC3 &v)
{
	Out->x = v.x;
	Out->y = v.y;
	Out->z = v.z;
	Out->w = 1.0f;
}

// Konwersja z wektora 4D na 3D ze zignorowaniem sk?adowej W
inline void Vec4ToVec3_Ignore(VEC3 *Out, const VEC4 &v)
{
	Out->x = v.x;
	Out->y = v.y;
	Out->z = v.z;
}
// Konwersja z wektora 4D na 3D ze podzieleniem sk?adowych przez W
inline void Vec4ToVec3_Div(VEC3 *Out, const VEC4 &v)
{
	float rcw = 1.0f / v.w;
	Out->x = v.x * rcw;
	Out->y = v.y * rcw;
	Out->z = v.z * rcw;
}

// Zwraca punkt w po?owie drogi mi?dzy podanymi punktami
inline void MidPoint(VEC2 *Out, const VEC2 &p1, const VEC2 &p2)
{
	Out->x = (p1.x+p2.x) * 0.5f;
	Out->y = (p1.y+p2.y) * 0.5f;
}
inline void MidPoint(VEC3 *Out, const VEC3 &p1, const VEC3 &p2)
{
	Out->x = (p1.x+p2.x) * 0.5f;
	Out->y = (p1.y+p2.y) * 0.5f;
	Out->z = (p1.z+p2.z) * 0.5f;
}
inline void MidPoint(VEC4 *Out, const VEC4 &p1, const VEC4 &p2)
{
	Out->x = (p1.x+p2.x) * 0.5f;
	Out->y = (p1.y+p2.y) * 0.5f;
	Out->z = (p1.z+p2.z) * 0.5f;
	Out->w = (p1.w+p2.w) * 0.5f;
}

// Zwraca true, je?li podane wektory/punkty s? sobie mniej wi?cej r?wne
inline bool VecEqual(const VEC2 &v1, const VEC2 &v2) {
	return float_equal(v1.x, v2.x) && float_equal(v1.y, v2.y);
}
inline bool VecEqual(const VEC3 &v1, const VEC3 &v2) {
	return float_equal(v1.x, v2.x) && float_equal(v1.y, v2.y) && float_equal(v1.z, v2.z);
}
inline bool VecEqual(const VEC4 &v1, const VEC4 &v2) {
	return float_equal(v1.x, v2.x) && float_equal(v1.y, v2.y) && float_equal(v1.z, v2.z) && float_equal(v1.w, v2.w);
}

// Zwraca true, je?li wszystkie sk?adowe podanego wektora s? odpowiednio
// mniejsze / wi?ksze / mniejsze lub r?wne / wi?ksze lub r?wne od drugiego

inline bool Less(const VEC2 &v1, const VEC2 &v2)
{
	return v1.x < v2.x && v1.y < v2.y;
}
inline bool Less(const VEC3 &v1, const VEC3 &v2)
{
	return v1.x < v2.x && v1.y < v2.y && v1.z < v2.z;
}
inline bool Less(const VEC4 &v1, const VEC4 &v2)
{
	return v1.x < v2.x && v1.y < v2.y && v1.z < v2.z && v1.w < v2.w;
}

inline bool LessOrEqual(const VEC2 &v1, const VEC2 &v2)
{
	return v1.x <= v2.x && v1.y <= v2.y;
}
inline bool LessOrEqual(const VEC3 &v1, const VEC3 &v2)
{
	return v1.x <= v2.x && v1.y <= v2.y && v1.z <= v2.z;
}
inline bool LessOrEqual(const VEC4 &v1, const VEC4 &v2)
{
	return v1.x <= v2.x && v1.y <= v2.y && v1.z <= v2.z && v1.w <= v2.w;
}

inline bool Greater(const VEC2 &v1, const VEC2 &v2)
{
	return v1.x > v2.x && v1.y > v2.y;
}
inline bool Greater(const VEC3 &v1, const VEC3 &v2)
{
	return v1.x > v2.x && v1.y > v2.y && v1.z > v2.z;
}
inline bool Greater(const VEC4 &v1, const VEC4 &v2)
{
	return v1.x > v2.x && v1.y > v2.y && v1.z > v2.z && v1.w > v2.w;
}

inline bool GreaterOrEqual(const VEC2 &v1, const VEC2 &v2)
{
	return v1.x >= v2.x && v1.y >= v2.y;
}
inline bool GreaterOrEqual(const VEC3 &v1, const VEC3 &v2)
{
	return v1.x >= v2.x && v1.y >= v2.y && v1.z >= v2.z;
}
inline bool GreaterOrEqual(const VEC4 &v1, const VEC4 &v2)
{
	return v1.x >= v2.x && v1.y >= v2.y && v1.z >= v2.z && v1.w >= v2.w;
}

inline bool around(const VEC2 &v1, const VEC2 &v2, float Epsilon) {
	return around(v1.x, v2.x, Epsilon) && around(v1.y, v2.y, Epsilon);
}
inline bool around(const VEC3 &v1, const VEC3 &v2, float Epsilon) {
	return around(v1.x, v2.x, Epsilon) && around(v1.y, v2.y, Epsilon) && around(v1.z, v2.z, Epsilon);
}
inline bool around(const VEC4 &v1, const VEC4 &v2, float Epsilon) {
	return around(v1.x, v2.x, Epsilon) && around(v1.y, v2.y, Epsilon) && around(v1.z, v2.z, Epsilon) && around(v1.w, v2.w, Epsilon);
}

// Zwraca wektor prostopad?y do podanego wektora 2D
// W uk?adzie w kt?rym X jest w prawo a Y do g?ry wektor le?y na lewo od danego.
// W uk?adzie w kt?rym X jest w prawo a Y w d??, le?y na prawo.
inline void Perpedicular(VEC2 *Out, const VEC2 &v)
{
	Out->x = -v.y;
	Out->y = v.x;
}

// Oblicza wektor kierunku odbicia od p?aszczyzny o podanej normalnej
// v wskazuje na kierunek *do* tej p?aszczyzny.
// PlaneNormal musi by? znormalizowany.
inline void Reflect(VEC2 *Out, const VEC2 &v, const VEC2 &PlaneNormal)
{
	// Wz?r: *Out = v - ( 2.0f * Dot(v, PlaneNormal) * PlaneNormal );
	float f = 2.0f * Dot(v, PlaneNormal);
	Out->x = v.x - f * PlaneNormal.x;
	Out->y = v.y - f * PlaneNormal.y;
}
inline void Reflect(VEC3 *Out, const VEC3 &v, const VEC3 &PlaneNormal)
{
	// Wz?r: *Out = v - ( 2.0f * Dot(v, PlaneNormal) * PlaneNormal );
	float f = 2.0f * Dot(v, PlaneNormal);
	Out->x = v.x - f * PlaneNormal.x;
	Out->y = v.y - f * PlaneNormal.y;
	Out->z = v.z - f * PlaneNormal.z;
}

// Rzutowanie wektora V na wektor N
// Wektor wyj?ciowy Out b?dzie r?wnoleg?y do N.
// Je?li chcemy roz?o?y? wektor V na wektor prostopad?y i r?wnoleg?y do N,
// to wektorem r?wnoleg?ym jest Out, a prostopad?y obliczamy jako V - Out.
inline void Project(VEC2 *Out, const VEC2 &V, const VEC2 &N)
{
	// Oryginalnie:
	// *Out = N * ( Dot(V, N) / LengthSq(N) );
	// Wersja szybsza:
	float T = (V.x*N.x + V.y*N.y) / (N.x*N.x + N.y*N.y);
	Out->x = N.x * T;
	Out->y = N.y * T;
}
inline void Project(VEC3 *Out, const VEC3 &V, const VEC3 &N)
{
	float T = (V.x*N.x + V.y*N.y + V.z*N.z) / (N.x*N.x + N.y*N.y + N.z*N.z);
	Out->x = N.x * T;
	Out->y = N.y * T;
	Out->z = N.z * T;
}
// Wersja kiedy wektor N jest ju? na pewno znormalizowany.
inline void Project_N(VEC2 *Out, const VEC2 &V, const VEC2 &N)
{
	// Oryginalnie:
	// *Out = N * Dot(V, N);
	// Wersja szybsza:
	float T = V.x*N.x + V.y*N.y;
	Out->x = N.x * T;
	Out->y = N.y * T;
}
inline void Project_N(VEC3 *Out, const VEC3 &V, const VEC3 &N)
{
	float T = V.x*N.x + V.y*N.y + V.z*N.z;
	Out->x = N.x * T;
	Out->y = N.y * T;
	Out->z = N.z * T;
}

// Ortogonalizacja trzech wektor?w
// - Po tym przekszta?ceniu b?d? do siebie prostopad?e.
// - Wektory wej?ciowe nie musz? by? znormalizowane.
// - Wektory wyj?ciowe niekoniecznie b?d? znormalizowane (nawet je?li wej?ciowe by?y).
// > Metoda szybka
void Orthogonalize_Fast(VEC3 *OutR1, VEC3 *OutR2, VEC3 *OutR3, const VEC3 &R1, const VEC3 &R2, const VEC3 &R3);
// > Metoda dok?adna
void Orthogonalize(VEC3 *OutR1, VEC3 *OutR2, VEC3 *OutR3, const VEC3 &R1, const VEC3 &R2, const VEC3 &R3);

// Wyznacza dwa dowolne wektory prostopad?e do podanego
// - v nie musi by? znormalizowany.
// - Zwr?cone wektory nie s? znormalizowane.
void PerpedicularVectors(VEC3 *Out1, VEC3 *Out2, const VEC3 &v);


//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// TR?JK?T

// Oblicza signed pole powierzchni tr?jk?ta
// Wychodzi dodanie, kiedy wierzcho?ki s? w kierunku wskaz?wek zegara.
float TriangleArea(const VEC2 &p1, const VEC2 &p2, const VEC2 &p3);
float TriangleArea(const VEC3 &p1, const VEC3 &p2, const VEC3 &p3);

// Znajduje obw?d tr?jk?ta
float TrianglePerimeter(const VEC2 &p1, const VEC2 &p2, const VEC2 &p3);
float TrianglePerimeter(const VEC3 &p1, const VEC3 &p2, const VEC3 &p3);

// Oblicza punkt na powierzhchni tr?jk?ta we wsp. barycentrycznych
// f to waga punktu p2, g to waga punktu p3.
// Wz?r: *Out = p1 + f*(p2-p1) + g*(p3-p1)
// Inny wz?r: *Out = p1*(1-f-g) + p2*f + p3*g
inline void Barycentric(VEC2 *Out, const VEC2 &p1, const VEC2 &p2, const VEC2 &p3, float f, float g)
{
	float e = 1.0f-f-g;
	Out->x = e*p1.x + f*p2.x + g*p3.x;
	Out->y = e*p1.y + f*p2.y + g*p3.y;
}
inline void Barycentric(VEC3 *Out, const VEC3 &p1, const VEC3 &p2, const VEC3 &p3, float f, float g)
{
	// Stara wersja, na podstawie DX SDK, du?o wolniejsza:
	//VEC3 Diff2 = p2-p1;
	//VEC3 Diff3 = p3-p1;
	//Out->x = p1.x + f*Diff2.x + g*Diff3.x;
	//Out->y = p1.y + f*Diff2.y + g*Diff3.y;
	//Out->z = p1.z + f*Diff2.z + g*Diff3.z;

	float e = 1.0f-f-g;
	Out->x = e*p1.x + f*p2.x + g*p3.x;
	Out->y = e*p1.y + f*p2.y + g*p3.y;
	Out->z = e*p1.z + f*p2.z + g*p3.z;
}
inline void Barycentric(VEC4 *Out, const VEC4 &p1, const VEC4 &p2, const VEC4 &p3, float f, float g)
{
	float e = 1.0f-f-g;
	Out->x = e*p1.x + f*p2.x + g*p3.x;
	Out->y = e*p1.y + f*p2.y + g*p3.y;
	Out->z = e*p1.z + f*p2.z + g*p3.z;
	Out->w = e*p1.w + f*p2.w + g*p3.w;
}

// Oblicz wsp??rz?dne barycentryczne podanego punktu p w ramach tr?jk?ta
// p1-p2-p3. Punkt musi na pewno le?e? na p?aszczy?nie tego tr?jk?ta.
// Normal mo?na poda? je?li mamy ju? obliczony jako Cross(v[1]-v[0], v[2]-v[1]) (nie musi by? znormalizowany) - ale nie trzeba.
void CalculateBarycentric(const VEC3 &p, const VEC3 &p1, const VEC3 &p2, const VEC3 &p3, const VEC3 *Normal, float *e, float *f, float *g);

// Znajduje okr?g wpisany w tr?jk?t
void TriangleInscribedCircle(VEC2 *OutCenter, float *OutRadius, const VEC2 &v1, const VEC2 &v2, const VEC2 &v3);
void TriangleInscribedCircle(VEC3 *OutCenter, float *OutRadius, const VEC3 &v1, const VEC3 &v2, const VEC3 &v3);
// Znajduje okr?g opisany na tr?jk?cie
void TriangleCircumscribedCircle(VEC2 *OutCenter, float *OutRadius, const VEC2 &v1, const VEC2 &v2, const VEC2 &v3);
void TriangleCircumscribedCircle(VEC3 *OutCenter, float *OutRadius, const VEC3 &v1, const VEC3 &v2, const VEC3 &v3);


//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// PROMIE?

// Zwraca punkt na promieniu
inline void PointOnRay(VEC2 *Out, const VEC2 &Origin, const VEC2 &Direction, float t)
{
	Out->x = Origin.x + t * Direction.x;
	Out->y = Origin.y + t * Direction.y;
}
inline void PointOnRay(VEC3 *Out, const VEC3 &Origin, const VEC3 &Direction, float t)
{
	Out->x = Origin.x + t * Direction.x;
	Out->y = Origin.y + t * Direction.y;
	Out->z = Origin.z + t * Direction.z;
}


//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// PROSTOK?T

/*
RECTI jest kompatybilny ze struktur? RECT z Win32API.
Konwersja do i ze stringa: "left,top,right,bottom", np. "1,2,3,4".
Niezale?nie od uk?adu wsp??rz?dnych, prawid?owy prostok?t jest wtedy, kiedy top
jest mniejsze co do warto?ci od bottom, a left od right.
*/

struct RECTI
{
	union
	{
		struct
		{
			int left;
			int top;
			int right;
			int bottom;
		};
		int v[4];
	};

	static const RECTI ZERO;

	RECTI() { }
	RECTI(int left, int top, int right, int bottom) : left(left), top(top), right(right), bottom(bottom) { }

	bool operator == (const RECTI &r) const { return left == r.left && top == r.top && right == r.right && bottom == r.bottom; }
	bool operator != (const RECTI &r) const { return left != r.left || top != r.top || right != r.right || bottom != r.bottom; }

	RECTI operator - () const { return RECTI(-right, -bottom, -left, -top); }
	RECTI operator + (const POINT_ &p) const { return RECTI(left+p.x, top+p.y, right+p.x, bottom+p.y); }
	RECTI operator - (const POINT_ &p) const { return RECTI(left-p.x, top-p.y, right-p.x, bottom-p.y); }
	RECTI operator * (int s) const { return RECTI(left*s, top*s, right*s, bottom*s); }
	RECTI operator * (const POINT_ &s) const { return RECTI(left*s.x, top*s.y, right*s.x, bottom*s.y); }
	RECTI & operator += (const POINT_ &p) { left += p.x; top += p.y; right += p.x; bottom += p.y; return *this; }
	RECTI & operator -= (const POINT_ &p) { left -= p.x; top -= p.y; right -= p.x; bottom -= p.y; return *this; }
	RECTI & operator *= (int s) { left *= s; top *= s; right *= s; bottom *= s; return *this; }
	RECTI & operator *= (const POINT_ &s) { left *= s.x; top *= s.y; right *= s.x; bottom *= s.y; return *this; }

	bool IsValid() const { return left < right && top < bottom; }
	void Repair() { if (right < left) std::swap(left, right); if (bottom < top) std::swap(top, bottom); }

	void LeftTop(POINT_ *Out) const { Out->x = left; Out->y = top; }
	void RightBottom(POINT_ *Out) const { Out->x = right; Out->y = bottom; }

	int & operator [] (uint4 Index) { return v[Index]; }
	const int & operator [] (uint4 Index) const { return v[Index]; }

	int * GetArray() { return &left; }
	const int * GetArray() const { return &left; }

	// Powi?ksza prostok?t z ka?dej strony o podan? warto??
	void Extend(int d) { left -= d; top -= d; right += d; bottom += d; }
	// Oblicza i zwraca szeroko??
	int Width() const { return right - left; }
	// Oblicza i zwraca wysoko??
	int Height() const { return bottom - top; }
	// Oblicza i zwraca d?ugo?? przek?tnej
	float Diagonal() const { return sqrtf( (float)((right-left)*(right-left)) + (float)((bottom-top)*(bottom-top)) ); }
	// Oblicza i zwraca pole powierzchni
	int Field() const { return (right-left)*(bottom-top); }
	// Zmienia szeroko?? na podan?
	void SetWidth(int NewWidth) { right = left + NewWidth; }
	// Zmienia wysoko?? na podan?
	void SetHeight(int NewHeight) { bottom = top + NewHeight; }
	// Zmienia szeroko?? i wysoko?? na podan?
	void SetSize(int NewWidth, int NewHeight) { right = left + NewWidth; bottom = top + NewHeight; }
	// Oblicza i zwraca pozycj? ?rodka
	void GetCenter(POINT_ *Out) const { Out->x = (left+right)/2; Out->y = (top+bottom)/2; }
	int GetCenterX() const { return (left+right)/2; }
	int GetCenterY() const { return (top+bottom)/2; }
	// Zwraca true, je?li prostok?t jest zerowy
	bool Empty() const { return left == 0 && top == 0 && right == 0 && bottom == 0; }
	// Czy?ci prostok?t na zerowy
	void Clear() { left = top = right = bottom = 0; }
};

struct RECTF
{
	union
	{
		struct
		{
			float left;
			float top;
			float right;
			float bottom;
		};
		float v[4];
	};

	static const RECTF ZERO;

	RECTF() { }
	RECTF(float left, float top, float right, float bottom) : left(left), top(top), right(right), bottom(bottom) { }

	bool operator == (const RECTF &r) const { return left == r.left && top == r.top && right == r.right && bottom == r.bottom; }
	bool operator != (const RECTF &r) const { return left != r.left || top != r.top || right != r.right || bottom != r.bottom; }

	RECTF operator - () const { return RECTF(-right, -bottom, -left, -top); }
	RECTF operator + (const VEC2 &p) const { return RECTF(left+p.x, top+p.y, right+p.x, bottom+p.y); }
	RECTF operator - (const VEC2 &p) const { return RECTF(left-p.x, top-p.y, right-p.x, bottom-p.y); }
	RECTF operator * (float s) const { return RECTF(left*s, top*s, right*s, bottom*s); }
	RECTF operator * (const VEC2 &s) const { return RECTF(left*s.x, top*s.y, right*s.x, bottom*s.y); }
	RECTF & operator += (const VEC2 &p) { left += p.x; top += p.y; right += p.x; bottom += p.y; return *this; }
	RECTF & operator -= (const VEC2 &p) { left -= p.x; top -= p.y; right -= p.x; bottom -= p.y; return *this; }
	RECTF & operator *= (float s) { left *= s; top *= s; right *= s; bottom *= s; return *this; }
	RECTF & operator *= (const VEC2 &s) { left *= s.x; top *= s.y; right *= s.x; bottom *= s.y; return *this; }

	bool IsValid() const { return left < right && top < bottom; }
	void Repair() { if (right < left) std::swap(left, right); if (bottom < top) std::swap(top, bottom); }

	void LeftTop(VEC2 *Out) const { Out->x = left; Out->y = top; }
	void RightBottom(VEC2 *Out) const { Out->x = right; Out->y = bottom; }

	float & operator [] (uint4 Index) { return v[Index]; }
	const float & operator [] (uint4 Index) const { return v[Index]; }

	float * GetArray() { return &left; }
	const float * GetArray() const { return &left; }

	// Powi?ksza prostok?t z ka?dej strony o podan? warto??
	void Extend(float d) { left -= d; top -= d; right += d; bottom += d; }
	// Oblicza i zwraca szeroko??
	float Width() const { return right - left; }
	// Oblicza i zwraca wysoko??
	float Height() const { return bottom - top; }
	// Oblicza i zwraca d?ugo?? przek?tnej
	float Diagonal() const { return sqrtf( (right-left)*(right-left) + (bottom-top)*(bottom-top) ); }
	// Oblicza i zwraca pole powierzchni
	float Field() const { return (right-left)*(bottom-top); }
	// Zmienia szeroko?? na podan?
	void SetWidth(float NewWidth) { right = left + NewWidth; }
	// Zmienia wysoko?? na podan?
	void SetHeight(float NewHeight) { bottom = top + NewHeight; }
	// Zmienia szeroko?? i wysoko?? na podan?
	void SetSize(float NewWidth, float NewHeight) { right = left + NewWidth; bottom = top + NewHeight; }
	// Oblicza i zwraca pozycj? ?rodka
	void GetCenter(VEC2 *Out) const { Out->x = (left+right)*0.5f; Out->y = (top+bottom)*0.5f; }
	float GetCenterX() const { return (left+right)*0.5f; }
	float GetCenterY() const { return (top+bottom)*0.5f; }
	// Zwraca true, je?li prostok?t jest zerowy
	bool Empty() const { return left == 0.0f && top == 0.0f && right == 0.0f && bottom == 0.0f; }
	// Czy?ci prostok?t na zerowy
	void Clear() { left = top = right = bottom = 0.0f; }
};

// Konwersja do i z RECT z Win32API
#ifdef WIN32
	template <> inline ::RECT & math_cast<::RECT, RECTI>(const RECTI &x) { return (::RECT&)(x); }
	template <> inline RECTI & math_cast<RECTI, ::RECT>(const ::RECT &x) { return (RECTI&)(x); }
#endif

inline void swap(RECTI &r1, RECTI &r2)
{
	std::swap(r1.left, r2.left); std::swap(r1.top, r2.top);
	std::swap(r1.right, r2.right); std::swap(r1.bottom, r2.bottom);
}

inline void swap(RECTF &r1, RECTF &r2)
{
	std::swap(r1.left, r2.left); std::swap(r1.top, r2.top);
	std::swap(r1.right, r2.right); std::swap(r1.bottom, r2.bottom);
}

// Zwraca true, je?li punkt nale?y do prostok?ta
inline bool PointInRect(const POINT_ &p, const RECTI &r)
{
	return
		(p.x >= r.left) &&
		(p.x <= r.right) &&
		(p.y >= r.top) &&
		(p.y <= r.bottom);
}
inline bool PointInRect(const VEC2 &p, const RECTF &r)
{
	return
		(p.x >= r.left) &&
		(p.x <= r.right) &&
		(p.y >= r.top) &&
		(p.y <= r.bottom);
}

// Zwraca true, je?li prostok?t sr zawiera si? w ca?o?ci wewn?trz r
inline bool RectInRect(const RECTI &sr, const RECTI &r)
{
	return
		(sr.left >= r.left) &&
		(sr.right <= r.right) &&
		(sr.top >= r.top) &&
		(sr.bottom <= r.bottom);
}
inline bool RectInRect(const RECTF &sr, const RECTF &r)
{
	return
		(sr.left >= r.left) &&
		(sr.right <= r.right) &&
		(sr.top >= r.top) &&
		(sr.bottom <= r.bottom);
}

// Zwraca true, je?li podane prostok?ty zachodz? na siebie
inline bool OverlapRect(const RECTI &r1, const RECTI &r2)
{
	return
		(r1.left <= r2.right) &&
		(r1.right >= r2.left) &&
		(r1.top <= r2.bottom) &&
		(r1.bottom >= r2.top);
}
inline bool OverlapRect(const RECTF &r1, const RECTF &r2)
{
	return
		(r1.left <= r2.right) &&
		(r1.right >= r2.left) &&
		(r1.top <= r2.bottom) &&
		(r1.bottom >= r2.top);
}

// Je?li prostok?ty posiadaj? cz??? wsp?ln?, zwraca j? przez Out i zwraca true
inline bool Intersection(RECTI *Out, const RECTI &r1, const RECTI &r2)
{
	*Out = RECTI(
		std::max(r1.left, r2.left),
		std::max(r1.top, r2.top),
		std::min(r1.right, r2.right),
		std::min(r1.bottom, r2.bottom));
	return Out->IsValid();
}
inline bool Intersection(RECTF *Out, const RECTF &r1, const RECTF &r2)
{
	*Out = RECTF(
		std::max(r1.left, r2.left),
		std::max(r1.top, r2.top),
		std::min(r1.right, r2.right),
		std::min(r1.bottom, r2.bottom));
	return Out->IsValid();
}

// Zwraca prostok?t opisany na podanych dw?ch prostok?tach
inline void Union(RECTI *Out, const RECTI &r1, const RECTI &r2)
{
	Out->left = std::min(r1.left, r2.left);
	Out->top = std::min(r1.top, r2.top);
	Out->right = std::max(r1.right, r2.right);
	Out->bottom = std::max(r1.bottom, r2.bottom);
}
inline void Union(RECTF *Out, const RECTF &r1, const RECTF &r2)
{
	Out->left = std::min(r1.left, r2.left);
	Out->top = std::min(r1.top, r2.top);
	Out->right = std::max(r1.right, r2.right);
	Out->bottom = std::max(r1.bottom, r2.bottom);
}


//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// AXIS ALIGNED BOUNDING BOX

/*
Sk?adnia do konwersji na i z ?a?cuch: p1x,p1y,p1z;p2x,p2y,p2z, np.:
"1,2,3;4,5,6"
*/

struct BOX
{
	VEC3 p1;
	VEC3 p2;

	static const BOX ZERO;

	BOX() { }
	BOX(const VEC3 &p1, const VEC3 &p2) : p1(p1), p2(p2) { }
	BOX(float p1x, float p1y, float p1z, float p2x, float p2y, float p2z) : p1(p1x, p1y, p1z), p2(p2x, p2y, p2z) { }

	bool operator == (const BOX &p) const { return p1 == p.p1 && p2 == p.p2; }
	bool operator != (const BOX &p) const { return p1 != p.p1 || p2 != p.p2; }

	BOX operator - () const { return BOX(-p2, -p1); }
	BOX operator + (const VEC3 &v) const { return BOX(p1+v, p2+v); }
	BOX operator - (const VEC3 &v) const { return BOX(p1-v, p2-v); }
	BOX operator * (float f) const { return BOX(p1*f, p2*f); }
	BOX operator * (const VEC3 &s) const { return BOX(VEC3(p1.x*s.x, p1.y*s.y, p1.z*s.z), VEC3(p2.x*s.x, p2.y*s.y, p2.z*s.z)); }
	BOX & operator += (const VEC3 &v) { p1 += v; p2 += v; return *this; }
	BOX & operator -= (const VEC3 &v) { p1 -= v; p2 -= v; return *this; }
	BOX & operator *= (float f) { p1 *= f; p2 *= f; return *this; }
	BOX & operator *= (const VEC3 &s) { p1.x *= s.x; p1.y *= s.y; p1.z *= s.z; p2.x *= s.x; p2.y *= s.y; p2.z *= s.z; return *this; }

	bool IsValid() { return Less(p1, p2); }
	void Repair() { if (p2.x < p1.x) std::swap(p1.x, p2.x); if (p2.y < p1.y) std::swap(p1.y, p2.y); if (p2.z < p1.z) std::swap(p1.z, p2.z); }

	float * GetArray() { return &p1.x; }
	const float * GetArray() const { return &p1.x; }

	float & operator [] (uint4 Index) { return GetArray()[Index]; }
	const float & operator [] (uint4 Index) const { return GetArray()[Index]; }

	// Powi?ksza boks z ka?dej strony o podan? warto??
	void Extend(float d) { p1.x -= d; p1.y -= d; p1.z -= d; p2.x += d; p2.y += d; p2.z += d; }
	// Oblicza i zwraca rozmiary boksa w trzech wymiarach
	void GetSize(VEC3 *Out) const { Out->x = p2.x-p1.x; Out->y = p2.y-p1.y; Out->z = p2.z-p1.z; }
	// Oblicza szeroko??, wysoko?? lub g??boko??
	float GetCX() const { return p2.x - p1.x; }
	float GetCY() const { return p2.y - p1.y; }
	float GetCZ() const { return p2.z - p1.z; }
	// Zmienia wielko?? na podan?
	void SetSize(const VEC3 &NewSize) { p2.x = p1.x + NewSize.x; p2.y = p1.y + NewSize.y; p2.z = p1.z + NewSize.z; }
	// Oblicza i zwraca d?ugo?? przek?tnej
	float Diagonal() const { return sqrtf( (p2.x-p1.x)*(p2.x-p1.x) + (p2.y-p1.y)*(p2.y-p1.y) + (p2.z-p1.z)*(p2.z-p1.z) ); }
	// Oblicza i zwraca obj?to??
	float Volume() const { return (p2.x-p1.x)*(p2.y-p1.y)*(p2.z-p1.z); }
	// Oblicza i zwraca pozycj? ?rodka
	void CalcCenter(VEC3 *Out) const { Out->x = (p1.x+p2.x)*0.5f; Out->y = (p1.y+p2.y)*0.5f; Out->z = (p1.z+p2.z)*0.5f; }
	// Zwraca true, je?li prostok?t jest zerowy
	bool Empty() const { return *this == ZERO; }
	// Czy?ci prostok?t na zerowy
	void Clear() { *this = ZERO; }
	// Zwraca wybrany wierzcho?ek
	void GetCorner(VEC3 *Out, int i) const
	{
		Out->x = (i & 1) ? p2.x : p1.x;
		Out->y = (i & 2) ? p2.y : p1.y;
		Out->z = (i & 4) ? p2.z : p1.z;
	}
	// Zwraca wszystkie 6 wierzcho?k?w w kolejno?ci:
	// p1x, p1y, p1z; p2x, p1y, p1z; p1x, p2y, p1z; p2x, p2y, p1z
	// p1x, p1y, p2z; p2x, p1y, p2z; p1x, p2y, p2z; p2x, p2y, p2z
	// Trzeba poda? wska?nik do tablicy.
	void GetAllCorners(VEC3 *Out) const
	{
		Out[0] = VEC3(p1.x, p1.y, p1.z); Out[1] = VEC3(p2.x, p1.y, p1.z); Out[2] = VEC3(p1.x, p2.y, p1.z); Out[3] = VEC3(p2.x, p2.y, p1.z);
		Out[4] = VEC3(p1.x, p1.y, p2.z); Out[5] = VEC3(p2.x, p1.y, p2.z); Out[6] = VEC3(p1.x, p2.y, p2.z); Out[7] = VEC3(p2.x, p2.y, p2.z);
	}
	// Powi?ksza tak ?eby na pewno zawiera? podany punkt
	void AddInternalPoint(const VEC3 &p)
	{
		p1.x = std::min(p1.x, p.x); p1.y = std::min(p1.y, p.y); p1.z = std::min(p1.z, p.z);
		p2.x = std::max(p2.x, p.x); p2.y = std::max(p2.y, p.y); p2.z = std::max(p2.z, p.z);
	}
	// Powi?ksza tak ?eby na pewno zawiera? podany boks
	// Podany boks musi by? prawid?owy.
	void AddInternalBox(const BOX &b)
	{
		p1.x = std::min(p1.x, b.p1.x); p1.y = std::min(p1.y, b.p1.y); p1.z = std::min(p1.z, b.p1.z);
		p2.x = std::max(p2.x, b.p2.x); p2.y = std::max(p2.y, b.p2.y); p2.z = std::max(p2.z, b.p2.z);
	}
};

// Skaluje boks o podan? liczb?
inline void Scale(BOX *Out, const BOX &b, float s)
{
	Out->p1.x = b.p1.x * s; Out->p1.y = b.p1.y * s; Out->p1.z = b.p1.z * s;
	Out->p2.x = b.p2.x * s; Out->p2.y = b.p2.y * s; Out->p2.z = b.p2.z * s;
}

// Skaluje boks o podane 3 wymiary
inline void Scale(BOX *Out, const BOX &b, const VEC3 &s)
{
	Out->p1.x = b.p1.x * s.x; Out->p1.y = b.p1.y * s.y; Out->p1.z = b.p1.z * s.z;
	Out->p2.x = b.p2.x * s.x; Out->p2.y = b.p2.y * s.y; Out->p2.z = b.p2.z * s.z;
}


inline void swap(BOX &b1, BOX &b2)
{
	std::swap(b1.p1, b2.p1);
	std::swap(b1.p2, b2.p2);
}

// Zwraca true, je?li punkt nale?y do boksa
inline bool PointInBox(const VEC3 &p, const BOX &b)
{
	return
		(p.x >= b.p1.x) && (p.x <= b.p2.x) &&
		(p.y >= b.p1.y) && (p.y <= b.p2.y) &&
		(p.z >= b.p1.z) && (p.z <= b.p2.z);
}

// Zwraca true, je?li boks sb zawiera si? w ca?o?ci wewn?trz b
inline bool BoxInBox(const BOX &sb, const BOX &b)
{
	return
		(sb.p1.x >= b.p1.x) && (sb.p2.x <= b.p2.x) &&
		(sb.p1.y >= b.p1.y) && (sb.p2.y <= b.p2.y) &&
		(sb.p1.z >= b.p1.z) && (sb.p2.z <= b.p2.z);
}

// Zwraca true, je?li podane boksy zachodz? na siebie
inline bool OverlapBox(const BOX &b1, const BOX &b2)
{
	return
		(b1.p1.x <= b2.p2.x) && (b1.p2.x >= b2.p1.x) &&
		(b1.p1.y <= b2.p2.y) && (b1.p2.y >= b2.p1.y) &&
		(b1.p1.z <= b2.p2.z) && (b1.p2.z >= b2.p1.z);
}

// Je?li boksy posiadaj? cz??? wsp?ln?, zwraca j? przez Out i zwraca true
inline bool Intersection(BOX *Out, const BOX &b1, const BOX &b2)
{
	*Out = BOX(
		VEC3(
			std::max(b1.p1.x, b2.p1.x),
			std::max(b1.p1.y, b2.p1.y),
			std::max(b1.p1.z, b2.p1.z)),
		VEC3(
			std::min(b1.p2.x, b2.p2.x),
			std::min(b1.p2.y, b2.p2.y),
			std::min(b1.p2.z, b2.p2.z)));
	return Out->IsValid();
}

// Zwraca boks opisany na podanych dw?ch boksach
inline void Union(BOX *Out, const BOX &b1, const BOX &b2)
{
	*Out = BOX(
		VEC3(
			std::min(b1.p1.x, b2.p1.x),
			std::min(b1.p1.y, b2.p1.y),
			std::min(b1.p1.z, b2.p1.z)),
		VEC3(
			std::max(b1.p2.x, b2.p2.x),
			std::max(b1.p2.y, b2.p2.y),
			std::max(b1.p2.z, b2.p2.z)));
}


//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// KOLORY

/*
Sta?e z kolorami, operacje generuj?ce kolory itp. wype?niaj? kana? alfa jedynk?.
*/

/*
Reprezentuje kolor w formacie A8R8G8B8
Operacje dodawania i odejmowania kolor?w, a tak?e dodawania, odejmowania,
mno?enia i dzielenia przez liczb? pilnuj? zakresu i w razie czego obcinaj?,
nie zawijaj?.
*/
struct COLOR
{
	union
	{
		// Ca?y kolor razem
		uint4 ARGB;
		// Osobno poszczeg?lne sk?adowe
		PACKED struct
		{
			uint1 B, G, R, A;
		};
	};

	static const COLOR TRANSPARENT_;
	static const COLOR BLACK;
	static const COLOR GRAY;
	static const COLOR SILVER;
	static const COLOR WHITE;
	static const COLOR FUCHSIA;
	static const COLOR RED;
	static const COLOR ORANGE;
	static const COLOR YELLOW;
	static const COLOR LIME;
	static const COLOR AQUA;
	static const COLOR BLUE;
	static const COLOR PURPLE;
	static const COLOR MAROON;
	static const COLOR OLIVE;
	static const COLOR GREEN;
	static const COLOR TEAL;

	COLOR() { }
	COLOR(uint4 c) : ARGB(c) { }
	COLOR(unsigned long c) : ARGB((uint4)c) { }
	COLOR(uint1 R, uint1 G, uint1 B) : B(B), G(G), R(R), A(0xFF) { }
	COLOR(uint1 A, uint1 R, uint1 G, uint1 B) : B(B), G(G), R(R), A(A) { }

	bool operator == (COLOR c) const { return ARGB == c.ARGB; }
	bool operator != (COLOR c) const { return ARGB != c.ARGB; }

	// Operatory unarne - dany kolor i negatyw koloru
	COLOR operator - () const { return COLOR(~ARGB); }
	// Dodawanie i odejmowanie kolor?w
	COLOR operator + (const COLOR &c) const { return COLOR(safe_add(A, c.A), safe_add(R, c.R), safe_add(G, c.G), safe_add(B, c.B)); }
	COLOR operator - (const COLOR &c) const { return COLOR(safe_sub(A, c.A), safe_sub(R, c.R), safe_sub(G, c.G), safe_sub(B, c.B)); }
	COLOR & operator += (const COLOR &c) { A = safe_add(A, c.A); R = safe_add(R, c.R); G = safe_add(G, c.G); B = safe_add(B, c.B); return *this; }
	COLOR & operator -= (const COLOR &c) { A = safe_sub(A, c.A); R = safe_sub(R, c.R); G = safe_sub(G, c.G); B = safe_sub(B, c.B); return *this; }
	// Mno?enie i dzielenie koloru przez liczb?
	// Autor: Tarlandil
	COLOR operator * (float s) const { return COLOR( (uint1)(minmax(0, (int)(A*s), 255)), (uint1)(minmax(0, (int)(R*s), 255)), (uint1)(minmax(0, (int)(G*s), 255)), (uint1)(minmax(0, (int)(B*s), 255)) ); }
	COLOR operator / (float s) const { return COLOR( (uint1)(minmax(0, (int)(A/s), 255)), (uint1)(minmax(0, (int)(R/s), 255)), (uint1)(minmax(0, (int)(G/s), 255)), (uint1)(minmax(0, (int)(B/s), 255)) ); }
	COLOR & operator *= (float s) { A = (uint1)(minmax(0, (int)(A*s), 255)); R = (uint1)(minmax(0, (int)(R*s), 255)); G = (uint1)(minmax(0, (int)(G*s), 255)); B = (uint1)(minmax(0, (int)(B*s), 255)); return *this; }
	COLOR & operator /= (float s) { A = (uint1)(minmax(0, (int)(A/s), 255)); R = (uint1)(minmax(0, (int)(R/s), 255)); G = (uint1)(minmax(0, (int)(G/s), 255)); B = (uint1)(minmax(0, (int)(B/s), 255));  return *this; }
	// Mno?enie dw?ch kolor?w, czyli modulacja
	COLOR operator * (const COLOR &c) const { return COLOR( (uint1)(((int)A*(int)c.A)/255), (uint1)(((int)R*(int)c.R)/255), (uint1)(((int)G*(int)c.G)/255), (uint1)(((int)B*(int)c.B)/255) ); }
	COLOR & operator *= (const COLOR &c) { A = (uint1)(((int)A*(int)c.A)/255); R = (uint1)(((int)R*(int)c.R)/255); G = (uint1)(((int)G*(int)c.G)/255); B = (uint1)(((int)B*(int)c.B)/255); return *this; }
};

/*
Reprezentacja koloru z czterech float?w
Operacje dodawania i odejmowania kolor?w, a tak?e dodawania, odejmowania,
mno?enia i dzielenia przez liczb? nie pilnuj? zakresu i warto?ci sk?adowych
mog? urosn?? powy?ej 1.0 albo zmale? poni?ej 0.0.
*/

struct COLORF
{
	float R, G, B, A;

	static const COLORF TRANSPARENT_;
	static const COLORF BLACK;
	static const COLORF GRAY;
	static const COLORF SILVER;
	static const COLORF WHITE;
	static const COLORF FUCHSIA;
	static const COLORF RED;
	static const COLORF ORANGE;
	static const COLORF YELLOW;
	static const COLORF LIME;
	static const COLORF AQUA;
	static const COLORF BLUE;
	static const COLORF PURPLE;
	static const COLORF MAROON;
	static const COLORF OLIVE;
	static const COLORF GREEN;
	static const COLORF TEAL;

	COLORF() { }
	COLORF(float R, float G, float B) : R(R), G(G), B(B), A(1.0f) { }
	COLORF(float A, float R, float G, float B) : R(R), G(G), B(B), A(A) { }

	bool operator == (const COLORF &c) const { return A == c.A && R == c.R && G == c.G && B == c.B; }
	bool operator != (const COLORF &c) const { return A != c.A || R != c.R || G != c.G || B != c.B; }

	// Operatory unarne - dany kolor i negatyw koloru
	COLORF operator - () const { return COLORF(1.0f-A, 1.0f-R, 1.0f-G, 1.0f-B); }
	// Dodawanie i odejmowanie kolor?w
	COLORF operator + (const COLORF &c) const { return COLORF(A+c.A, R+c.R, G+c.G, B+c.B); }
	COLORF operator - (const COLORF &c) const { return COLORF(A-c.A, R-c.R, G-c.G, B-c.B); }
	COLORF & operator += (const COLORF &c) { A += c.A; R += c.R; G += c.G; B += c.B; return *this; }
	COLORF & operator -= (const COLORF &c) { A -= c.A; R -= c.R; G -= c.G; B -= c.B; return *this; }
	// Mno?enie i dzielenie koloru przez liczb?
	COLORF operator * (float s) const { return COLORF(A*s, R*s, G*s, B*s); }
	COLORF operator / (float s) const { return COLORF(A/s, R/s, G/s, B/s); }
	COLORF & operator *= (float s) { A *= s; R *= s; G *= s; B *= s; return *this; }
	COLORF & operator /= (float s) { A /= s; R /= s; G /= s; B /= s; return *this; }
	// Mno?enie dw?ch kolor?w, czyli modulacja
	COLORF operator * (const COLORF &c) const { return COLORF(A*c.A, R*c.R, G*c.G, B*c.B); }
	COLORF & operator *= (const COLORF &c) { A *= c.A; R *= c.R; G *= c.G; B *= c.B; return *this; }

	float * GetArray() { return &R; }
	const float * GetArray() const { return &R; }

	// Sprawdza, czy sk?adowe mieszcz? si? w zakresie 0.0 .. 1.0
	bool IsValid() const { return (A >= 0.0f && A <= 1.0f) && (R >= 0.0f && R <= 1.0f) && (G >= 0.0f && G <= 1.0f) && (B >= 0.0f && B <= 1.0f); }
	// Sprowadza sk?adowe do zakresu 0.0 .. 1.0
	void Repair()
	{
		A = minmax(0.0f, A, 1.0f); R = minmax(0.0f, R, 1.0f);
		G = minmax(0.0f, G, 1.0f); B = minmax(0.0f, B, 1.0f);
	}
};

// Mno?enie i dzielenie koloru przez liczb?
inline COLORF operator * (float s, const COLORF &c) { return COLORF(c.A*s, c.R*s, c.G*s, c.B*s); }
inline COLORF operator / (float s, const COLORF &c) { return COLORF(c.A/s, c.R/s, c.G/s, c.B/s); }

inline COLOR operator * (float s, const COLOR &c) { return COLOR( (uint1)(minmax(0, (int)(c.A*s), 255)), (uint1)(minmax(0, (int)(c.R*s), 255)), (uint1)(minmax(0, (int)(c.G*s), 255)), (uint1)(minmax(0, (int)(c.B*s), 255)) ); }
inline COLOR operator / (float s, const COLOR &c) { return COLOR( (uint1)(minmax(0, (int)(c.A/s), 255)), (uint1)(minmax(0, (int)(c.R/s), 255)), (uint1)(minmax(0, (int)(c.G/s), 255)), (uint1)(minmax(0, (int)(c.B/s), 255)) ); }

template <> inline uint4 & math_cast<uint4, COLOR>(const COLOR &x) { return (uint4&)(x); }
template <> inline unsigned long & math_cast<unsigned long, COLOR>(const COLOR &x) { return (unsigned long&)(x); }
template <> inline COLOR & math_cast<COLOR, uint4>(const uint4 &x) { return (COLOR&)(x); }
template <> inline COLOR & math_cast<COLOR, unsigned long>(const unsigned long &x) { return (COLOR&)(x); }

#ifdef USE_DIRECTX
	template <> inline D3DXCOLOR & math_cast<D3DXCOLOR, COLORF>(const COLORF &x) { return (D3DXCOLOR&)(x); }
	template <> inline COLORF & math_cast<COLORF, D3DXCOLOR>(const D3DXCOLOR &x) { return (COLORF&)(x); }
#endif

// Konwersje mi?dzy tymi dwoma reprezentacjami kolor?w
inline void ColorToColorf(COLORF *Out, COLOR c)
{
	Out->R = c.R / 255.0f;
	Out->G = c.G / 255.0f;
	Out->B = c.B / 255.0f;
	Out->A = c.A / 255.0f;
}
// Tu musi by? valid, inaczej wyjdzie zawini?te.
inline COLOR ColorfToColor(const COLORF &c)
{
	return COLOR(
		(uint1)(minmax(0.0f, c.A, 1.0f)*255.0f+0.5f),
		(uint1)(minmax(0.0f, c.R, 1.0f)*255.0f+0.5f),
		(uint1)(minmax(0.0f, c.G, 1.0f)*255.0f+0.5f),
		(uint1)(minmax(0.0f, c.B, 1.0f)*255.0f+0.5f));
}

// Konwersja koloru na ?a?cuch
// Formatem mo?e by?:
// - 'x' = RRGGBB szesnastkowo
// - 'X' = AARRGGBB szesnastkowo
// - 'f' = R,G,B floaty
// - 'F' = A,R,G,B floaty
void ColorToStr(string *Out, COLOR Color, char Format = 'X');
void ColorToStr(string *Out, const COLORF &Color, char Format = 'F');
// Konwersja ?a?cucha na kolor
// ?a?cuchem mo?e by?:
// - jedna z 16 nazw standardowych kolor?w (wielko?? liter dowolna)
// - warto?? szesnastkowa RRGGBB
// - warto?? szesnastkowa AARRGGBB
// - liczby float R,G,B
// - liczby float A,R,G,B
// Je?li kana? alfa nie podany, zostaje wype?niony warto?ci? maksymaln?.
bool StrToColor(COLOR *Out, const string &Str);
bool StrToColor(COLORF *Out, const string &Str);

inline void swap(COLORF &c1, COLORF &c2)
{
	std::swap(c1.A, c2.A); std::swap(c1.R, c2.R);
	std::swap(c1.G, c2.G); std::swap(c1.B, c2.B);
}

inline void Add(COLORF *Out, const COLORF &c1, const COLORF &c2)
{
	Out->A = c1.A + c2.A; Out->R = c1.R + c2.R;
	Out->G = c1.G + c2.G; Out->B = c1.B + c2.B;
}
inline void Sub(COLORF *Out, const COLORF &c1, const COLORF &c2)
{
	Out->A = c1.A - c2.A; Out->R = c1.R - c2.R;
	Out->G = c1.G - c2.G; Out->B = c1.B - c2.B;
}
inline void Mul(COLORF *Out, const COLORF &c1, const COLORF &c2)
{
	Out->A = c1.A * c2.A; Out->R = c1.R * c2.R;
	Out->G = c1.G * c2.G; Out->B = c1.B * c2.B;
}
inline void Mul(COLORF *Out, const COLORF &c, float s)
{
	Out->A = c.A * s; Out->R = c.R * s;
	Out->G = c.G * s; Out->B = c.B * s;
}
inline void Div(COLORF *Out, const COLORF &c, float s)
{
	Out->A = c.A / s; Out->R = c.R / s;
	Out->G = c.G / s; Out->B = c.B / s;
}
inline void Negative(COLORF *Out, const COLORF &c)
{
	Out->A = 1.0f - c.A; Out->R = 1.0f - c.R;
	Out->G = 1.0f - c.G; Out->B = 1.0f - c.B;
}

// Konwertuje kolor mi?dzy systemami ARGB i ABGR
inline COLOR ARGB_ABGR(COLOR color)
{
	return COLOR(
		(color.ARGB & 0xFF00FF00) |
		((color.ARGB >> 16) & 0x000000FF) |
		((color.ARGB & 0x000000FF) << 16)
		);
}

inline void Lerp(COLORF *Out, const COLORF &c1, const COLORF &c2, float t)
{
	Out->A = Lerp(c1.A, c2.A, t);
	Out->R = Lerp(c1.R, c2.R, t);
	Out->G = Lerp(c1.G, c2.G, t);
	Out->B = Lerp(c1.B, c2.B, t);
}
inline COLOR Lerp(COLOR c1, COLOR c2, float t)
{
	return COLOR(
		(uint1)(minmax(0, (int)(c1.A + t*((float)c2.A-(float)c1.A)), 255)),
		(uint1)(minmax(0, (int)(c1.R + t*((float)c2.R-(float)c1.R)), 255)),
		(uint1)(minmax(0, (int)(c1.G + t*((float)c2.G-(float)c1.G)), 255)),
		(uint1)(minmax(0, (int)(c1.B + t*((float)c2.B-(float)c1.B)), 255)) );
}

// Konwertuje kolor mi?dzy HSB a RGB
// - Hue, Saturation, Brightness = 0..1
// - Kana? alfa zwraca 1.
void HsbToRgb(COLORF *Out, float hue, float saturation, float brightness);
// Konwertuje kolor RGB na HSB
void RgbToHsb(float *OutHue, float *OutSaturation, float *OutBrightness, const COLORF &Color);

// Zwraca kolor t?czy od czerwonego (odpowiada mu t = 0) do niebieskiego (t = 1)
// Kana? alfa zwraca 0.
inline void ColorRainbow(COLORF *Out, float t)
{
	HsbToRgb(Out, t*0.75f, 1.0f, 1.0f);
}

// Zwraca jasno?? podanego koloru (odcie? szaro?ci) z zakresu 0..1
inline float ColorToGrayscale(const COLORF &c)
{
	return 0.299f * c.R + 0.587f * c.G + 0.114f * c.B;
}
inline float ColorToGrayscale(COLOR &c)
{
	return 0.299f * (c.R/255.0f) + 0.587f * (c.G/255.0f) + 0.114f * (c.B/255.0f);
}

// Zwraca kolor szary o podanej jasno?ci t = 0..1
inline void GrayscaleToColor(COLORF *Out, float t)
{
	Out->A = 1.0f;
	Out->R = Out->G = Out->B = t;
}
inline void GrayscaleToColor(COLOR *Out, float t)
{
	Out->A = 255;
	Out->R = Out->G = Out->B = (uint1)(t*255.0f);
}

// Zmienia kolorowi kontrast na miejscu
// Dla t = 0 wychodzi idealnie po??wkowy szary.
// Dla t = 1 wychodzi kolor oryginalny.
// t mo?e te? by? wi?ksze ni? 1.
// Alfa zostaje bez zmian
inline void AdjustContrast(COLORF *Color, float t)
{
	Color->R = 0.5f + t * (Color->R - 0.5f);
	Color->G = 0.5f + t * (Color->G - 0.5f);
	Color->B = 0.5f + t * (Color->B - 0.5f);
}

// Zmienia kolorowi nasycenie na miejscu
// Dla t = 0 wychodzi dany kolor skonwertowany do odcienia szaro?ci.
// Dla t = 1 wychodzi kolor oryginalny.
// t < 0 zmniejsza nasycenie, t > 0 zwi?ksza nasycenie
// Alfa zostaje bez zmian
inline void AdjustSaturation(COLORF *Color, float t)
{
	float gray = ColorToGrayscale(*Color);
	Color->R = gray + t * (Color->R - gray);
	Color->G = gray + t * (Color->G - gray);
	Color->B = gray + t * (Color->B - gray);
}

// Przetwarza znormalizowany wektor na kolor XRGB
// A zwraca 0
inline COLOR VectorToColor(const VEC3 &v)
{
	int R = minmax(0, (int)(127.0f * v.x + 128.0f), 255);
	int G = minmax(0, (int)(127.0f * v.y + 128.0f), 255);
	int B = minmax(0, (int)(127.0f * v.z + 128.0f), 255);
	return COLOR((uint4)((R << 16) | (G << 8) | B));
}

// Przetwarza kolor na wektor
inline void ColorToVector(VEC3 *Out, COLOR color)
{
	const float o = 1.0f / 127.0f;
	Out->x = (((color.ARGB >> 16) & 0xFF) - 128.0f) * o;
	Out->y = (((color.ARGB >>  8) & 0xFF) - 128.0f) * o;
	Out->z = (((color.ARGB      ) & 0xFF) - 128.0f) * o;
}

// Zwraca "odleg?o??" dw?ch kolor?w wg jakiej?tam byle jakiej metryki.
// Uwzgl?dnia sk?adowe R, G, B.
inline uint ColorDistance(COLOR Color1, COLOR Color2)
{
	int rd = (int)Color1.R - (int)Color2.R;
	int gd = (int)Color1.G - (int)Color2.G;
	int bd = (int)Color1.B - (int)Color2.B;
	return (uint)(rd*rd + gd*gd + bd*bd);
}


//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// P?ASZCZYZNA

/*
Reprezentuje p?aszczyzn? w przestrzeni 3D z jedn? stron? dodatni?, a drug?
ujemn?. Opisana jest r?wnaniem A x + B y + C z + D = 0. Wektor [A,B,C] to wektor
normalny wskazuj?cy w kierunku dodatniej p??przestrzeni. Je?li p?aszczyzna jest
znormalizowana, wektor normalny jest znormalizowany, a D to odleg?o??
p?aszczyzny od ?rodka uk?adu wsp??rz?dnych.
Reprezentacja jako string to A,R,G,B np. "1,2,3,0.2".
Je?li u?ywasz D3DX, jest kompatybilna przez math_cast z D3DXPLANE.
P?aszczyzna maj?ca a=b=c=0 (czyli sta?a ZERO) jest niepoprawna, zdegenerowana.
*/

struct PLANE
{
	float a, b, c, d;

	static const PLANE ZERO;
	static const PLANE POSITIVE_X; // P?aszczyzna pionowa, r?wnoleg?a do Y i Z, wskazuj?ca na prawo na X
	static const PLANE POSITIVE_Y; // P?aszczyzna pozioma, r?wnoleg?a do X i Z, wskazuj?ca do g?ry na Y
	static const PLANE POSITIVE_Z; // P?aszczyzna pionowa, r?wnoleg?a do X i Y, wskazuj?ca w g??b na Z
	static const PLANE NEGATIVE_X; // P?aszczyzna pionowa, r?wnoleg?a do Y i Z, wskazuj?ca na lewo na X
	static const PLANE NEGATIVE_Y; // P?aszczyzna pozioma, r?wnoleg?a do X i Z, wskazuj?ca w d?? na Y
	static const PLANE NEGATIVE_Z; // P?aszczyzna pionowa, r?wnoleg?a do X i Y, wskazuj?ca do gracza na Z

	PLANE() { }
	PLANE(float a, float b, float c, float d) : a(a), b(b), c(c), d(d) { }
	PLANE(const VEC3 &n, float d) : a(n.x), b(n.y), c(n.z), d(d) { }

	VEC3 & GetNormal() { return (VEC3&)a; }
	const VEC3 & GetNormal() const { return (VEC3&)a; }

	bool operator == (const PLANE &p) const { return a == p.a && b == p.b && c == p.c && d == p.d; }
	bool operator != (const PLANE &p) const { return a != p.a || b != p.b || c != p.c || d != p.d; }

	// Zwraca p?aszczyzn? zwr?con? w przeciwn? stron?
	PLANE operator - () const { return PLANE(-a, -b, -c, -d); }

	// Skalowanie
	PLANE operator * (float s) const { return PLANE(a*s, b*s, c*s, d*s); }
	PLANE operator / (float s) const { return PLANE(a/s, b/s, c/s, d/s); }
	PLANE & operator *= (float s) { a *= s; b *= s; c *= s; d *= s; return *this; }
	PLANE & operator /= (float s) { a /= s; b /= s; c /= s; d /= s; return *this; }

	float * GetArray() { return &a; }
	const float * GetArray() const { return &a; }

	float & operator [] (uint4 Index) { return GetArray()[Index]; }
	const float & operator [] (uint4 Index) const { return GetArray()[Index]; }

	// Zwraca jaki? punkt le??cy na tej p?aszczy?nie
	// Musi by? znormalizowana.
	void GetMemberPoint(VEC3 *Out)
	{
		*Out = GetNormal() * -d;
	}

	// Zmienia odleg?o?? od pocz?tku uk?adu wsp??rz?dnych tak, ?eby ta p?aszczyzna pozostaj?c tak samo
	// zorientowana zosta?a przesuni?ta tak, ?eby zawiera? w sobie podany punkt
	// Musi by? znormalizowana (?)
	void RecalculateD(const VEC3 &p)
	{
		d = -Dot(GetNormal(), p);
	}
};

inline PLANE operator * (float s, const PLANE &p) { return PLANE(p.a*s, p.b*s, p.c*s, p.d*s); }
inline PLANE operator / (float s, const PLANE &p) { return PLANE(p.a/s, p.b/s, p.c/s, p.d/s); }

#ifdef USE_DIRECTX
	template <> inline ::D3DXPLANE & math_cast<::D3DXPLANE, PLANE>(const PLANE &x) { return (::D3DXPLANE&)(x); }
	template <> inline PLANE & math_cast<PLANE, ::D3DXPLANE>(const ::D3DXPLANE &x) { return (PLANE&)(x); }
#endif

inline void swap(PLANE &p1, PLANE &p2)
{
	std::swap(p1.a, p2.a); std::swap(p1.b, p2.b);
	std::swap(p1.c, p2.c); std::swap(p1.d, p2.d);
}

// Zwraca true, je?li podane p?aszczyzny s? sobie mniej wi?cej r?wne
inline bool PlaneEqual(const PLANE &p1, const PLANE &p2) {
	return float_equal(p1.a, p2.a) && float_equal(p1.b, p2.b) && float_equal(p1.c, p2.c) && float_equal(p1.d, p2.d);
}

// Tworzy p?aszczyzn? na podstawie trzech punkt?w
// P?aszczyzna b?dzie zorientowana dodatnio w kierunku tej p??przestrzeni,
// z kt?rej wierzcho?ki tr?jk?ta s? widoczne jako zorientowane zgodnie z ruchem
// wskaz?wek zegara w uk?adzie LH.
inline void PointsToPlane(PLANE *Out, const VEC3 &p1, const VEC3 &p2, const VEC3 &p3) {
	Cross(&Out->GetNormal(), p2-p1, p3-p1);
	Normalize(&Out->GetNormal());
	Out->d = -Dot(p1, Out->GetNormal());
}
// Tworzy p?aszczyzn? z wektora normalnego i punktu le??cego na tej p?aszczy?nie
// - Czy Normal musi by? znormalizowany? Nie wiem.
inline void PointNormalToPlane(PLANE *Out, const VEC3 &Point, const VEC3 &Normal) {
	Out->a = Normal.x; Out->b = Normal.y; Out->c = Normal.z;
	Out->d = -Dot(Normal, Point);
}

// Skalowanie p?aszczyzny
inline void Mul(PLANE *Out, const PLANE &p, float s)
{
	Out->a = p.a * s; Out->b = p.b * s;
	Out->c = p.c * s; Out->d = p.d * s;
}
inline void Div(PLANE *Out, const PLANE &p, float s)
{
	Out->a = p.a / s; Out->b = p.b / s;
	Out->c = p.c / s; Out->d = p.d / s;
}

// Iloczyn skalarny p?aszczyzny i punktu we wsp??rz?dnych jednorodnych
// Mo?na u?y? do wyznaczenia czy tak zapisany punkt le?y na p?aszczy?nie,
// po kt?rej stronie i jak daleko.
inline float Dot(const PLANE &p, const VEC4 &pt)
{
	return p.a*pt.x + p.b*pt.y + p.c*pt.z + p.d*pt.w;
}

// Iloczyn skalarny p?aszczyzny z punktem 3D: a*x+b*y+c*z+d*1
// Mo?na u?y? do wyznaczenia czy punkt le?y na p?aszczy?nie, po kt?rej stronie
// i jak daleko.
inline float DotCoord(const PLANE &p, const VEC3 &pt)
{
	return p.a*pt.x + p.b*pt.y + p.c*pt.z + p.d;
}

// Iloczyn skalarny p?aszczyzny z wektorem 3D: a*x+b*y+c*z+d*0
// Przydatny do wyznaczania k?ta mi?dzy p?aszczyzn? (jej normaln?) a wektorem.
inline float DotNormal(const PLANE &p, const VEC3 &v)
{
	return p.a*v.x + p.b*v.y + p.c*v.z;
}

// Normalizacja p?aszczyzny
// Po tej operacji wektor normalny p?aszczyzny jest znormalizowany.
// P?aszczyzna pozostaje po?o?ona i zorientowana tam gdzie by?a.
inline void Normalize(PLANE *Out, const PLANE &p)
{
	float nlsq = 1.0f / Length(p.GetNormal());
	Out->a = p.a * nlsq; Out->b = p.b * nlsq;
	Out->c = p.c * nlsq; Out->d = p.d * nlsq;
}
// Normalizacja p?aszczyzny w miejscu
inline void Normalize(PLANE *p)
{
	float nlsq = 1.0f / Length(p->GetNormal());
	p->a *= nlsq; p->b *= nlsq;
	p->c *= nlsq; p->d *= nlsq;
}


//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// PROSTA 2D

/*
Reprezentuje prost? w przestrzeni 2D z jedn? stron? dodatni?, a drug?
ujemn?. Opisana jest r?wnaniem A x + B y + C = 0. Wektor [A,B] to wektor
normalny wskazuj?cy w kierunku dodatniej p??p?aszczyzny. Je?li prosta jest
znormalizowana, wektor normalny jest znormalizowany, a C to odleg?o?? prostej
od ?rodka uk?adu wsp??rz?dnych.
Reprezentacja jako string to A,B,C, np. "2,0,2.1"
Prosta maj?ca a = b = 0 (czyli np. sta?a ZERO) jest niepoprawna, zdegenerowana.
*/

struct LINE2D
{
	float a, b, c;

	static const LINE2D ZERO;
	static const LINE2D POSITIVE_X;
	static const LINE2D NEGATIVE_X;
	static const LINE2D POSITIVE_Y;
	static const LINE2D NEGATIVE_Y;

	LINE2D() { }
	LINE2D(float a, float b, float c) : a(a), b(b), c(c) { }
	LINE2D(const VEC2 &Normal, float c) : a(Normal.x), b(Normal.y), c(c) { }

	VEC2 & GetNormal() { return (VEC2&)a; }
	const VEC2 & GetNormal() const { return (VEC2&)a; }

	bool operator == (const LINE2D &L) const { return a == L.a && b == L.b && c == L.c; }
	bool operator != (const LINE2D &L) const { return a != L.a || b != L.b || c != L.c; }

	// Zwraca prost? zwr?con? w przeciwn? stron?
	LINE2D operator - () const { return LINE2D(-a, -b, -c); }

	// Skalowanie
	LINE2D operator * (float s) const { return LINE2D(a*s, b*s, c*s); }
	LINE2D operator / (float s) const { return LINE2D(a/s, b/s, c/s); }
	LINE2D & operator *= (float s) { a *= s; b *= s; c *= s; return *this; }
	LINE2D & operator /= (float s) { a /= s; b /= s; c /= s; return *this; }

	float * GetArray() { return &a; }
	const float * GetArray() const { return &a; }

	float & operator [] (uint4 Index) { return GetArray()[Index]; }
	const float & operator [] (uint4 Index) const { return GetArray()[Index]; }

	// Zwraca wektor wskazuj?cy w kierunku prostej
	void GetTangent(VEC2 *Out) { Out->x = b; Out->y = -a; }

	// Zwraca jaki? punkt le??cy na tej prostej
	// Musi by? znormalizowana.
	void GetMemberPoint(VEC2 *Out)
	{
		*Out = GetNormal() * -c;
	}

	// Zmienia odleg?o?? od pocz?tku uk?adu wsp??rz?dnych tak, ?eby ta prosta pozostaj?c tak samo
	// zorientowana zosta?a przesuni?ta tak, ?eby zawiera? w sobie podany punkt
	// Musi by? znormalizowana (?)
	void RecalculateD(const VEC2 &p)
	{
		c = -Dot(GetNormal(), p);
	}
};

inline LINE2D operator * (float s, const LINE2D &p) { return LINE2D(p.a*s, p.b*s, p.c*s); }
inline LINE2D operator / (float s, const LINE2D &p) { return LINE2D(p.a/s, p.b/s, p.c/s); }

// Zwraca true, je?li podane proste s? sobie mniej wi?cej r?wne
inline bool LineEqual(const LINE2D &p1, const LINE2D &p2) {
	return float_equal(p1.a, p2.a) && float_equal(p1.b, p2.b) && float_equal(p1.c, p2.c);
}

inline void swap(LINE2D &p1, LINE2D &p2)
{
	std::swap(p1.a, p2.a); std::swap(p1.b, p2.b); std::swap(p1.c, p2.c);
}

// Tworzy prost? na podstwie dw?ch punkt?w
// Wynikowa prosta nie jest znormalizowana.
inline void PointsToLine(LINE2D *Out, const VEC2 &p1, const VEC2 &p2) {
	Out->a = p1.y - p2.y;
	Out->b = p2.x - p1.x;
	Out->c = - Out->a * p1.x - Out->b * p1.y;
}

// Tworzy prost? z wektora normalnego i punktu le??cego na tej prostej
inline void PointNormalToLine(LINE2D *Out, const VEC2 &Point, const VEC2 &Normal) {
	Out->a = Normal.x; Out->b = Normal.y;
	Out->c = -Dot(Normal, Point);
}

// Zwraca true, je?li podane proste s? r?wnoleg?e
inline bool LinesParallel(const LINE2D &L1, const LINE2D &L2) {
	return FLOAT_ALMOST_ZERO(L1.a*L2.b - L2.a*L1.b);
}

// Zwraca true, je?li podane proste s? prostopad?e
inline bool LinesPerpedicular(const LINE2D &L1, const LINE2D &L2) {
	return FLOAT_ALMOST_ZERO(L1.a*L2.a + L1.b*L2.b);
}

// Zwraca dot z wektor?w normalnych dw?ch prostych
// Je?li te proste s? znormalizowane, wynikiem jest cos k?ta mi?dzy tymi prostymi.
inline float Dot(const LINE2D &L1, const LINE2D &L2) {
	return L1.a*L2.a + L1.b*L2.b;
}

// Zwraca signed odleg?o?? dw?ch prostych na p?aszczy?nie
// Proste musz? by? znormalizowane.
inline float LineDistance(const LINE2D &L1, const LINE2D &L2) {
	return L1.c - L2.c;
}

// Oblicza punkt przeciecia dw?ch prostych
// Je?li proste nie przecinaj? si?, tylko s? r?wnoleg?e lub si? pokrywan?, to nie oblicza tylko zwraca false.
bool LinesIntersection(VEC2 *Out, const LINE2D &L1, const LINE2D &L2);

// Zwraca true, je?li podane trzy punkty le?? na jednej prostej
bool PointsColinear(const VEC2 &p1, const VEC2 &p2, const VEC2 &p3);

// Skalowanie prostej
inline void Mul(LINE2D *Out, const LINE2D &p, float s) {
	Out->a = p.a * s; Out->b = p.b * s; Out->c = p.c * s;
}
inline void Div(LINE2D *Out, const LINE2D &p, float s) {
	Out->a = p.a / s; Out->b = p.b / s; Out->c = p.c / s;
}

// Iloczyn skalarny p?aszczyzny i punktu we wsp??rz?dnych jednorodnych 2D
// Mo?na u?y? do wyznaczenia czy tak zapisany punkt le?y na p?aszczy?nie,
// po kt?rej stronie i jak daleko.
inline float Dot(const LINE2D &p, const VEC3 &pt) {
	return p.a*pt.x + p.b*pt.y + p.c*pt.z;
}

// Iloczyn skalarny prostej 2D z punktem 2D: a*x + b*y + c*1
// Mo?na u?y? do wyznaczenia czy punkt le?y na prostej 2D, po kt?rej stronie i jak daleko.
inline float DotCoord(const LINE2D &p, const VEC2 &pt) {
	return p.a*pt.x + p.b*pt.y + p.c;
}

// Iloczyn skalarny prostej 2D z wektorem 2D: a*x + b*y + c*z + d*0
// Przydatny do wyznaczania k?ta mi?dzy prost? 2D (jej normaln?) a wektorem.
inline float DotNormal(const LINE2D &p, const VEC2 &v) {
	return p.a*v.x + p.b*v.y;
}

// Normalizacja prostej 2D
// Po tej operacji wektor normalny prostej jest znormalizowany.
// Prosta pozostaje po?o?ona i zorientowana tam gdzie by?a.
inline void Normalize(LINE2D *Out, const LINE2D &p) {
	float nlsq = 1.f / Length(p.GetNormal());
	Out->a = p.a * nlsq; Out->b = p.b * nlsq; Out->c = p.c * nlsq;
}
// Normalizacja p?aszczyzny w miejscu
inline void Normalize(LINE2D *p) {
	float nlsq = 1.f / Length(p->GetNormal());
	p->a *= nlsq; p->b *= nlsq; p->c *= nlsq;
}


//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// MACIERZ 4 x 4

/*
Elementy s? indeksowane [wiersz,kolumna].
Reprezentacja tekstowa to:
	a11,a12,a13,a14;a21,a22,a23,a24;a31,a32,a33,a34;a41,a42,a43,a44
*/

struct MATRIX
{
	union
	{
		struct
		{
			float _11, _12, _13, _14;
			float _21, _22, _23, _24;
			float _31, _32, _33, _34;
			float _41, _42, _43, _44;
		};
        struct {
            float a00, a01, a02, a03;
            float a10, a11, a12, a13;
            float a20, a21, a22, a23;
            float a30, a31, a32, a33;
        };
		float m[4][4]; // [wiersz][kolumna]
	};

	static const MATRIX ZERO;
	static const MATRIX IDENTITY;

	MATRIX() { }
	MATRIX(float _11, float _12, float _13, float _14, float _21, float _22, float _23, float _24, float _31, float _32, float _33, float _34, float _41, float _42, float _43, float _44) : _11(_11), _12(_12), _13(_13), _14(_14), _21(_21), _22(_22), _23(_23), _24(_24), _31(_31), _32(_32), _33(_33), _34(_34), _41(_41), _42(_42), _43(_43), _44(_44) { }
	MATRIX(float *Array) : _11(Array[0]), _12(Array[1]), _13(Array[2]), _14(Array[3]), _21(Array[4]), _22(Array[5]), _23(Array[6]), _24(Array[7]), _31(Array[8]), _32(Array[9]), _33(Array[10]), _34(Array[11]), _41(Array[12]), _42(Array[13]), _43(Array[14]), _44(Array[15]) { }

	bool operator == (const MATRIX &m) const { return _11 == m._11 && _12 == m._12 && _13 == m._13 && _14 == m._14 && _21 == m._21 && _22 == m._22 && _23 == m._23 && _24 == m._24 && _31 == m._31 && _32 == m._32 && _33 == m._33 && _34 == m._34 && _41 == m._41 && _42 == m._42 && _43 == m._43 && _44 == m._44; }
	bool operator != (const MATRIX &m) const { return _11 != m._11 || _12 != m._12 || _13 != m._13 || _14 != m._14 || _21 != m._21 || _22 != m._22 || _23 != m._23 || _24 != m._24 || _31 != m._31 || _32 != m._32 || _33 != m._33 || _34 != m._34 || _41 != m._41 || _42 != m._42 || _43 != m._43 || _44 != m._44; }

	float & operator () (unsigned Row, unsigned Col) { return m[Row][Col]; }
	float operator () (unsigned Row, unsigned Col) const { return m[Row][Col]; }

	MATRIX operator - () const;
	MATRIX operator + (const MATRIX &m) const;
	MATRIX operator - (const MATRIX &m) const;
	MATRIX operator * (const MATRIX &m) const
	{
		return MATRIX(
			_11 * m._11 + _12 * m._21 + _13 * m._31 + _14 * m._41,
			_11 * m._12 + _12 * m._22 + _13 * m._32 + _14 * m._42,
			_11 * m._13 + _12 * m._23 + _13 * m._33 + _14 * m._43,
			_11 * m._14 + _12 * m._24 + _13 * m._34 + _14 * m._44,

			_21 * m._11 + _22 * m._21 + _23 * m._31 + _24 * m._41,
			_21 * m._12 + _22 * m._22 + _23 * m._32 + _24 * m._42,
			_21 * m._13 + _22 * m._23 + _23 * m._33 + _24 * m._43,
			_21 * m._14 + _22 * m._24 + _23 * m._34 + _24 * m._44,

			_31 * m._11 + _32 * m._21 + _33 * m._31 + _34 * m._41,
			_31 * m._12 + _32 * m._22 + _33 * m._32 + _34 * m._42,
			_31 * m._13 + _32 * m._23 + _33 * m._33 + _34 * m._43,
			_31 * m._14 + _32 * m._24 + _33 * m._34 + _34 * m._44,

			_41 * m._11 + _42 * m._21 + _43 * m._31 + _44 * m._41,
			_41 * m._12 + _42 * m._22 + _43 * m._32 + _44 * m._42,
			_41 * m._13 + _42 * m._23 + _43 * m._33 + _44 * m._43,
			_41 * m._14 + _42 * m._24 + _43 * m._34 + _44 * m._44);
	}
	MATRIX & operator += (const MATRIX &m);
	MATRIX & operator -= (const MATRIX &m);
	MATRIX & operator *= (const MATRIX &m);

	MATRIX operator * (float s) const;
	MATRIX operator / (float s) const;
	MATRIX & operator *= (float s);
	MATRIX & operator /= (float s);

	float * GetArray() { return &m[0][0]; }
	float GetArray() const { return m[0][0]; }
};

#ifdef USE_DIRECTX
	template <> inline ::D3DXMATRIX & math_cast<::D3DXMATRIX, MATRIX>(const MATRIX &x) { return (::D3DXMATRIX&)(x); }
	template <> inline MATRIX & math_cast<MATRIX, ::D3DXMATRIX>(const ::D3DXMATRIX &x) { return (MATRIX&)(x); }
#endif

void MatrixToStr(string *Out, const MATRIX &m);
bool StrToMatrix(MATRIX *Out, const string &Str);

inline void swap(MATRIX &m1, MATRIX &m2)
{
	std::swap(m1._11, m2._11); std::swap(m1._12, m2._12); std::swap(m1._13, m2._13); std::swap(m1._14, m2._14);
	std::swap(m1._21, m2._21); std::swap(m1._22, m2._22); std::swap(m1._23, m2._23); std::swap(m1._24, m2._24);
	std::swap(m1._31, m2._31); std::swap(m1._32, m2._32); std::swap(m1._33, m2._33); std::swap(m1._34, m2._34);
	std::swap(m1._41, m2._41); std::swap(m1._42, m2._42); std::swap(m1._43, m2._43); std::swap(m1._44, m2._44);
}

// Zwraca true, je?li podane macierze s? sobie mniej wi?cej r?wne
bool MatrixEqual(const MATRIX &m1, const MATRIX &m2);
// Negacja macierzy w miejscu
void Minus(MATRIX *m);
// Dodawanie, odejmowanie, mno?enie macierzy
void Add(MATRIX *Out, const MATRIX &m1, const MATRIX &m2);
void Sub(MATRIX *Out, const MATRIX &m1, const MATRIX &m2);
void Mul(MATRIX *Out, const MATRIX &m1, const MATRIX &m2);
// Mno?enie i dzielenie macierzy przez skalar w miejscu
void Mul(MATRIX *m, float s);
void Div(MATRIX *m, float s);

// Mno?enie wektora 2D jako [x,y,0,1] przez macierz, wychodzi wektor 4D
void Transform(VEC4 *Out, const VEC2 &v, const MATRIX &m);
// Mno?enie wektora 2D jako [x,y,0,1] przez macierz z olaniem wyj?ciowego W
void Transform(VEC2 *Out, const VEC2 &v, const MATRIX &m);
// Mno?enie wektora 2D jako [x,y,0,1] przez macierz i sprowadzenie z powrotem do 2D przez podzielenie przez W
void TransformCoord(VEC2 *Out, const VEC2 &v, const MATRIX &m);
// Mno?enie wektora 2D jako [x,y,0,0] przez macierz
void TransformNormal(VEC2 *Out, const VEC2 &v, const MATRIX &m);

// Mno?enie wektora 3D jako [X,Y,Z,1] przez macierz, wychodzi wektor 4D
void Transform(VEC4 *Out, const VEC3 &v, const MATRIX &m);
// Mno?enie wektora 3D jako [X,Y,Z,1] przez macierz z olaniem wyj?ciowego W
// Dobre do przekszta?cania wektor?w 3D je?li macierz reprezentuje przekszta?cenie liniowe.
void Transform(VEC3 *Out, const VEC3 &v, const MATRIX &m);
// Mno?enie wektora 3D jako [X,Y,Z,1] przez macierz i sprowadzenie z powrotem do 3D przez podzielenie przez W
// Dobre do niezawodnego przekszta?cania wektor?w 3D przez dowoln? macierz np. rzutowania.
void TransformCoord(VEC3 *Out, const VEC3 &v, const MATRIX &m);
// Mno?enie wektora 3D jako [X,Y,Z,0] przez macierz
// Dobre do przekszta?cania wektor?w (np. normalnych), nie punkt?w, bo nie robi translacji.
void TransformNormal(VEC3 *Out, const VEC3 &v, const MATRIX &m);

// Przekszta?ca na raz ca?? tablic? wektor?w - w miejscu lub z tablicy wej?ciowej do wyj?ciowej
void TransformArray(VEC3 OutPoints[], const VEC3 InPoints[], size_t PointCount, const MATRIX &M);
void TransformArray(VEC3 InOutPoints[], size_t PointCount, const MATRIX &M);
void TransformNormalArray(VEC3 OutPoints[], const VEC3 InPoints[], size_t PointCount, const MATRIX &M);
void TransformNormalArray(VEC3 InOutPoints[], size_t PointCount, const MATRIX &M);
void TransformCoordArray(VEC3 OutPoints[], const VEC3 InPoints[], size_t PointCount, const MATRIX &M);
void TransformCoordArray(VEC3 InOutPoints[], size_t PointCount, const MATRIX &M);

// Mno?enie wektora 4D przez macierz
// Czyli przekszta?cenie wektora we wsp??rz?dnych jednorodnych przez t? macierz.
void Transform(VEC4 *Out, const VEC4 &v, const MATRIX &m);

// Przekszta?ca p?aszczyzn? przez macierz
// P?aszczyzna ma by? znormalizowana.
// Macierz ma by? odwrotna i transponowana wzgl?dem normalnej macierzy.
void Transform(PLANE *Out, const PLANE &p, const MATRIX &m);
// Przekszta?ca promie? przez macierz
void TransformRay(VEC3 *OutOrigin, VEC3 *OutDir, const VEC3 &RayOrigin, const VEC3 &RayDir, const MATRIX &m);

// Przekszta?ca AABB przez podan? macierz i wylicza AABB tego co wysz?o po przekszta?ceniu
void TransformBox(BOX *Out, const BOX &In, const MATRIX &M);
// Przekszta?ca AABB przez podan? macierz i wylicza AABB tego co wysz?o po przekszta?ceniu
// Wersja dziel?ca przez W - mo?na stosowa? te? do macierzy projekcji.
void TransformBoxCoord(BOX *Out, const BOX &In, const MATRIX &M);

// Tworzy macierz przekszta?caj?c? do lokalnego uk?adu wsp??rz?dnych wyznaczonego przez podane 3 osie
// Nast?pi obr?t, a je?li nie s? znormalizowane to i skalowanie.
void AxesToMatrix(MATRIX *Out, const VEC3 &AxisX, const VEC3 &AxisY, const VEC3 &AxisZ);
// Tworzy macierz przekszta?caj?c? do lokalnego uk?adu wsp??rz?dnych wyznaczonego przez podane 3 osie
// i pozycj? pocz?tku tego uk?adu.
// Nast?pi obr?t, a je?li osie s? znormalizowane to i skalowanie.
void AxesToMatrixTranslation(MATRIX *Out, const VEC3 &Origin, const VEC3 &AxisX, const VEC3 &AxisY, const VEC3 &AxisZ);

// Macierz kamery
// Eye to punkt, Forward i Up to wektory.
void LookAtLH(MATRIX *Out, const VEC3 &Eye, const VEC3 &Forward, const VEC3 &Up);
void LookAtRH(MATRIX *Out, const VEC3 &Eye, const VEC3 &Forward, const VEC3 &Up);

// Tworzy macierz identyczno?ciow?
void Identity(MATRIX *Out);
// Tworzy macierz translacji (przesuwania)
void Translation(MATRIX *Out, float x, float y, float z);
void Translation(MATRIX *Out, const VEC3 &v);
// Tworzy macierz skalowania (powi?kszania, pomniejszania, rozci?gania)
void Scaling(MATRIX *Out, float sx, float sy, float sz);
void Scaling(MATRIX *Out, const VEC3 &sv);
void Scaling(MATRIX *Out, float s);
// Tworzy macierz skalowania wzd?u? podanego kierunku
// k - wsp??czynnik skalowania
// n - wektor kierunku, musi by? znormalizowany
void ScalingAxis(MATRIX *Out, const VEC3 &n, float k);

// Macierz obrotu wok?? danej osi
void RotationX(MATRIX *Out, float Angle);
void RotationY(MATRIX *Out, float Angle);
void RotationZ(MATRIX *Out, float Angle);
// Axis musi by? znormalizowany.
void RotationAxisLH(MATRIX *Out, const VEC3 &Axis, float Angle);
inline void RotationAxisRH(MATRIX *Out, const VEC3 &Axis, float Angle) { RotationAxisLH(Out, Axis, -Angle); }

// Macierz obrotu wok?? trzech osi w kolejno?ci Yaw-Pitch-Roll (ZXY) - tzw. k?ty Eulera
// Yaw jest wok?? osi Y. Pitch jest wok?? osi X. Roll jest wok?? osi Z.
// W przypadku wektora sk?adowe odpowiadaj? obrotom wok?? poszczeg?lnych osi, czyli:
//   X = Pitch, Y = Yaw, Z = Roll
// Przekszta?ca ze wsp. obiektu do ?wiata (object -> interial space). [a mo?e odwrotnie?]
// Czyli tak naprawd? robi ZXY.
void RotationYawPitchRoll(MATRIX *Out, float Yaw, float Pitch, float Roll);
void RotationYawPitchRoll(MATRIX *Out, const VEC3 &EulerAngles);
// Przekszta?ca ze wsp. ?wiata do obiektu (interial -> object space). [a mo?e odwrotnie?]
// Czyli tworzy macierz dok?adnie odwrotn? do tej z RotationYawPitchRoll.
void RotationYawPitchRollInv(MATRIX *Out, float Yaw, float Pitch, float Roll);
void RotationYawPitchRollInv(MATRIX *Out, const VEC3 &EulerAngles);

// Przetwarza macierz obeotu (to musi by? czysta macierz obrotu) na k?ty Eulera
//void RotationMatrixToEulerAngles(const MATRIX &m, float *Yaw, float *Pitch, float *Roll);

// Tworzy macierz rzutowania ortogonalnego
// Dane s? w uk?adzie kamery.
void OrthoLH(MATRIX *Out, float Width, float Height, float ZNear, float ZFar);
void OrthoRH(MATRIX *Out, float Width, float Height, float ZNear, float ZFar);
void OrthoOffCenterLH(MATRIX *Out, float Left, float Right, float Bottom, float Top, float ZNear, float ZFar);
void OrthoOffCenterRH(MATRIX *Out, float Left, float Right, float Bottom, float Top, float ZNear, float ZFar);
// Tworzy macierz rzutowania perspektywicznego
// Width i Height s? wymiarami na p?aszczy?nie bliskiej (near).
// Left, Top, Right, Bottom prawdopodobnie te?.
// Tworzone macierze s? "W-Friendly" - wektor przemno?ony przez tak? macierz ma w sk?adowej W komponent Z.
void PerspectiveLH(MATRIX *Out, float Width, float Height, float ZNear, float ZFar);
void PerspectiveRH(MATRIX *Out, float Width, float Height, float ZNear, float ZFar);
void PerspectiveFovLH(MATRIX *Out, float FovY, float Aspect, float ZNear, float ZFar);
void PerspectiveFovRH(MATRIX *Out, float FovY, float Aspect, float ZNear, float ZFar);
void PerspectiveOffCenterLH(MATRIX *Out, float Left, float Right, float Bottom, float Top, float ZNear, float ZFar);
void PerspectiveOffCenterRH(MATRIX *Out, float Left, float Right, float Bottom, float Top, float ZNear, float ZFar);
// Wersja tworz?ca macierz z Z-Far = INFINITY
void PerspectiveFovLH_Inf(MATRIX *Out, float FovY, float Aspect, float ZNear);
// Tworzy macierz sp?aszczaj?c? geometri? na podan? p?aszczyzn? w podanym kierunku padania ?wiat?a
// P?aszczyzna musi by? znormalizowana.
void MatrixShadow(MATRIX *Out, const VEC4 &Light, const PLANE &Plane);
// Tworzy macierz odbijaj?c? geometri? wzgl?dem podanej p?aszczyzny
// P?aszczyzna musi by? znormalizowana.
void MatrixReflect(MATRIX *Out, const PLANE &p);

// Transpozycja macierzy na miejscu
void Transpose(MATRIX *m);
// Interpolacja liniowa macierzy
void Lerp(MATRIX *Out, const MATRIX &m1, const MATRIX &m2, float t);
// Wyznacznik macierzy
float Det(const MATRIX &m);
// Odwrotno?? macierzy
bool Inverse(MATRIX *Out, const MATRIX &m);


//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// KWATERNION

/*
Reprezentacja jako ?a?cuch to: "x,y,z,w", np.: "1,2,3.5,-10".
Kwaterniony s? mno?one od drugiej strony ni? matematycznie, dzi?ki czemu mo?na
??czy? obroty kt?re reprezentuj? w porz?dku naturalnym, tak jak macierze.
*/

struct QUATERNION
{
	union
	{
		struct
		{
			float x, y, z, w;
		};
		float v[4];
	};

	static const QUATERNION ZERO;
	static const QUATERNION IDENTITY;

	QUATERNION() { }
	QUATERNION(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) { }
	QUATERNION(float *Array) : x(Array[0]), y(Array[1]), z(Array[2]), w(Array[3]) { }

	bool operator == (const QUATERNION &v) const { return x == v.x && y == v.y && z == v.z && w == v.w; }
	bool operator != (const QUATERNION &v) const { return x != v.x || y != v.y || z != v.z || w != v.w; }

	QUATERNION operator - () const { return QUATERNION(-x, -y, -z, -w); }
	QUATERNION operator + (const QUATERNION &q) const { return QUATERNION(x+q.x, y+q.y, z+q.z, w+q.w); }
	QUATERNION operator - (const QUATERNION &q) const { return QUATERNION(x-q.x, y-q.y, z-q.z, w-q.w); }
	QUATERNION operator * (const QUATERNION &q) const { return QUATERNION(w*q.x + x*q.w + y*q.z - z*q.y, w*q.y + y*q.w + z*q.x - x*q.z, w*q.z + z*q.w + x*q.y - y*q.x, w*q.w - x*q.x - y*q.y - z*q.z); }
	QUATERNION & operator += (const QUATERNION &q) { x += q.x; y += q.y; z += q.z; w += q.w; return *this; }
	QUATERNION & operator -= (const QUATERNION &q) { x -= q.x; y -= q.y; z -= q.z; w -= q.w; return *this; }
	QUATERNION & operator *= (const QUATERNION &q) { QUATERNION R; R.x = w*q.x + x*q.w + y*q.z - z*q.y; R.y = w*q.y + y*q.w + z*q.x - x*q.z; R.z = w*q.z + z*q.w + x*q.y - y*q.x; R.w = w*q.w - x*q.x - y*q.y - z*q.z; *this = R; return *this; }
	QUATERNION & operator *= (float v) { x *= v; y *= v; z *= v; w *= v; return *this; }
	QUATERNION & operator /= (float v) { x /= v; y /= v; z /= v; w /= v; return *this; }

	float & operator [] (uint4 Index) { return v[Index]; }
	const float & operator [] (uint4 Index) const { return v[Index]; }

	float * GetArray() { return &x; }
	const float * GetArray() const { return &x; }

	// Zwraca k?t obrotu jaki reprezentuje ten kwaternion
	float CalcAngle() const { return safe_acos(w) * 2.0f; }
	// Zwraca o? obrotu jak? reprezentuje ten kwaternion
	void CalcAxis(VEC3 *Out) const;
};

inline QUATERNION operator * (const QUATERNION pt, float v) { return QUATERNION(pt.x*v, pt.y*v, pt.z*v, pt.w*v); }
inline QUATERNION operator / (const QUATERNION pt, float v) { return QUATERNION(pt.x/v, pt.y/v, pt.z/v, pt.w/v); }
inline QUATERNION operator * (float v, const QUATERNION pt) { return QUATERNION(pt.x*v, pt.y*v, pt.z*v, pt.w*v); }
inline QUATERNION operator / (float v, const QUATERNION pt) { return QUATERNION(pt.x/v, pt.y/v, pt.z/v, pt.w/v); }

#ifdef USE_DIRECTX
	template <> inline ::D3DXQUATERNION & math_cast<::D3DXQUATERNION, QUATERNION>(const QUATERNION &x) { return (::D3DXQUATERNION&)(x); }
	template <> inline QUATERNION & math_cast<QUATERNION, ::D3DXQUATERNION>(const ::D3DXQUATERNION &x) { return (QUATERNION&)(x); }
#endif

inline void swap(QUATERNION &v1, QUATERNION &v2)
{
	std::swap(v1.x, v2.x);
	std::swap(v1.y, v2.y);
	std::swap(v1.z, v2.z);
	std::swap(v1.w, v2.w);
}

// Zwraca true, je?li podane kwaterniony s? sobie mniej wi?cej r?wne
inline bool QuaternionEqual(const QUATERNION &q1, const QUATERNION &q2) {
	return float_equal(q1.x, q2.x) && float_equal(q1.y, q2.y) && float_equal(q1.z, q2.z) && float_equal(q1.w, q2.w);
}

// Ujemny kwaternion
void Minus(QUATERNION *q);
inline void Minus(QUATERNION *Out, const QUATERNION &q) { *Out = q; Minus(Out); }
// Dodawanie, odejmowanie, mno?enie kwaternion?w
void Add(QUATERNION *Out, const QUATERNION &q1, const QUATERNION &q2);
void Sub(QUATERNION *Out, const QUATERNION &q1, const QUATERNION &q2);
void Mul(QUATERNION *Out, const QUATERNION &q1, const QUATERNION &q2);
// Mno?enie i dzielenie kwaterniona przez skalar
void Mul(QUATERNION *q, float v);
void Div(QUATERNION *q, float v);
inline void Mul(QUATERNION *Out, const QUATERNION &q, float v) { *Out = q; Mul(Out, v); }
inline void Div(QUATERNION *Out, const QUATERNION &q, float v) { *Out = q; Div(Out, v); }

// Tworzy kwaternion na podstawie macierzy obrotu
void RotationMatrixToQuaternion(QUATERNION *Out, const MATRIX &RotationMatrix);
// Przekszta?ca kwaternion w macierz obrotu
void QuaternionToRotationMatrix(MATRIX *Out, const QUATERNION &q);
// Przekszta?ca punkt/wektor przez kwaternion obracaj?c go o ten kwaternion
// > To nie jest wcale super szybkie i nie przydaje si? a? tak cz?sto.
//   Lepiej sobie przekszta?ci? kwaternion na macierz.
// > Out = q * p * q^-1
void QuaternionTransform(VEC3 *Out, const VEC3 &p, const QUATERNION &q);
// Konwersja k?t?w Eulera na kwaternion (kt?ry obraca ze wsp. obiektu do ?wiata, czyli object -> interial space) [a mo?e odwrotnie?]
void EulerAnglesToQuaternionO2I(QUATERNION *Out, float Yaw, float Pitch, float Roll);
// Konwersja k?t?w Eulera na kwaternion (kt?ry obraca ze wsp. ?wiata do obiektu, czyli interial -> object space) [a mo?e odwrotnie?]
void EulerAnglesToQuaternionI2O(QUATERNION *Out, float Yaw, float Pitch, float Roll);
// Konwersja kwaterniona kt?ry obraca ze wsp. obiektu do ?wiata, czyli object -> interial space, na k?ty Eulera
void QuaternionO2IToEulerAngles(float *Yaw, float *Pitch, float *Roll, const QUATERNION &q);
// Konwersja kwaterniona kt?ry obraca ze wsp. ?wiata do obiektu, czyli interial -> object space, na k?ty Eulera
void QuaternionI2OToEulerAngles(float *Yaw, float *Pitch, float *Roll, const QUATERNION &q);

// Tworzy kwaternion obracaj?cy wok?? osi X
void QuaternionRotationX(QUATERNION *Out, float a);
// Tworzy kwaternion obracaj?cy wok?? osi Y
void QuaternionRotationY(QUATERNION *Out, float a);
// Tworzy kwaternion obracaj?cy wok?? osi Z
void QuaternionRotationZ(QUATERNION *Out, float a);
// Tworzy kwaternion na podstawie osi obrotu i k?ta
void AxisToQuaternion(QUATERNION *Out, const VEC3 &Axis, float Angle);

// Oblica "r??nic?" dw?ch kwaternion?w reprezentuj?c? taki obr?t ?e a*Out = b
// To jest obliczane tak: Out = a^-1 * b, wi?c je?li masz ju? a^-1 to nie u?ywaj.
void QuaternionDiff(QUATERNION *Out, const QUATERNION &a, const QUATERNION &b);
// Kwaternion sprz??ony do danego
void Conjugate(QUATERNION *q);
inline void Conjugate(QUATERNION *Out, const QUATERNION &q) { *Out = q; Conjugate(Out); }
// Odwrotno?? kwaterniona
void Inverse(QUATERNION *Out, const QUATERNION &q);
// Normalizacja kwaternion
void Normalize(QUATERNION *Out, const QUATERNION &q);
void Normalize(QUATERNION *InOut);
// Iloczyn skalarny dw?ch kwaternion?w
float Dot(const QUATERNION &q1, const QUATERNION &q2);
// Kwadrat d?ugo?ci kwaterniona
float LengthSq(const QUATERNION &q);
// D?ugo?? kwaterniona
float Length(const QUATERNION &q);
void Log(QUATERNION *Out, const QUATERNION &q);
void Exp(QUATERNION *Out, const QUATERNION &q);
// Podnie? kwaternion do pot?gi.
// Wyk?adnik 0..1 daje interpolacje kwaterniona od identyczno?ciowego do q.
void Pow(QUATERNION *InOut, float t);
inline void Pow(QUATERNION *Out, const QUATERNION &q, float t) { *Out = q; Pow(Out, t); }
// Interpolacja normalna kwaternion?w
void Lerp(QUATERNION *Out, const QUATERNION &q1, const QUATERNION &q2, float t);
// Interpolacja sferyczna kwaternion?w
// - Sprawdzona, daje wyniki dok?adnie tekie same jak D3DXQuaternionSlerp.
void Slerp(QUATERNION *Out, const QUATERNION &q0, const QUATERNION &q1, float t);
// NIE TESTOWANA
void Squad(QUATERNION *Out, const QUATERNION &Q1, const QUATERNION &A, const QUATERNION &B, const QUATERNION &C, float t);
// NIE TESTOWANA
void SquadSetup(QUATERNION *OutA, QUATERNION *OutB, QUATERNION *OutC, const QUATERNION &Q0, const QUATERNION &Q1, const QUATERNION &Q2, const QUATERNION &Q3);


//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// FRUSTUM

struct FRUSTUM_PLANES;
struct FRUSTUM_POINTS;

/*
Frustum opisany 6 p?aszczyznami z wektorami normalnymi zwr?conymi do wewn?trz.
- Je?li WorldViewProj jest macierz? Proj, otrzymane p?aszczyzny s? we wsp. widoku.
  Je?li WorldViewProj jest macierz? View*Proj, otrzymane p?aszczyzny s? we wsp. ?wiata.
  Je?li WorldViewProj jest macierz? World*View*Proj, otrzymane p?aszczyzny s? we wsp. lokalnych obiektu.
*/
struct FRUSTUM_PLANES
{
	// Indeksy do tej tablicy
	// Przedrostek PLANE_ jest, bo NEAR zosta?o gdzie? zdefiniowane jako makro - grrrrr!
	static const size_t PLANE_LEFT   = 0;
	static const size_t PLANE_RIGHT  = 1;
	static const size_t PLANE_TOP    = 2;
	static const size_t PLANE_BOTTOM = 3;
	static const size_t PLANE_NEAR   = 4;
	static const size_t PLANE_FAR    = 5;

	PLANE Planes[6];

	// Tworzy niezainicjalizowany
	FRUSTUM_PLANES() { }
	// Inicjalizuje na podstawie macierzy
	FRUSTUM_PLANES(const MATRIX &WorldViewProj) { Set(WorldViewProj); }
	// Inicjalizuje na podstawie reprezentacji punktowej
	FRUSTUM_PLANES(const FRUSTUM_POINTS &FrustumPoints) { Set(FrustumPoints); }
	// Wype?nia
	void Set(const MATRIX &WorldViewProj);
	void Set(const FRUSTUM_POINTS &FrustumPoints);
	// Normalizuje p?aszczyzny
	void Normalize();

	PLANE & operator [] (size_t Index) { return Planes[Index]; }
	const PLANE & operator [] (size_t Index) const { return Planes[Index]; }
};

/*
Frustum zapisany jako 8 wierzcho?k?w
- Uzyskiwanie przez konwersj? macierzy ViewProj do FRUSTUM_PLANES i z niego
  do FRUSTUM_POINTS jest du?o szybsze ni? budowanie FRUSTUM_POINTS z macierzy
  ViewProjInv - 2 (Release) - 8 (Debug) razy szybsze!
*/
struct FRUSTUM_POINTS
{
	// indeksy do tej tablicy
	// kolejno na przeci?ciu p?aszczyzn:
	static const size_t NEAR_LEFT_BOTTOM  = 0;
	static const size_t NEAR_RIGHT_BOTTOM = 1;
	static const size_t NEAR_LEFT_TOP     = 2;
	static const size_t NEAR_RIGHT_TOP    = 3;
	static const size_t FAR_LEFT_BOTTOM   = 4;
	static const size_t FAR_RIGHT_BOTTOM  = 5;
	static const size_t FAR_LEFT_TOP      = 6;
	static const size_t FAR_RIGHT_TOP     = 7;

	VEC3 Points[8];

	// Tworzy niezainicjalizowany
	FRUSTUM_POINTS() { }
	// Inicjalizuje na podstawie p?aszczyzn
	FRUSTUM_POINTS(const FRUSTUM_PLANES &FrustumPlanes) { Set(FrustumPlanes); }
	// Inicjalizuje na podstawie ODWROTNO?CI macierzy View*Projection
	FRUSTUM_POINTS(const MATRIX &WorldViewProjInv) { Set(WorldViewProjInv); }
	// Wype?nia
	void Set(const FRUSTUM_PLANES &FrustumPlanes);
	void Set(const MATRIX &WorldViewProjInv);

	VEC3 & operator [] (size_t Index) { return Points[Index]; }
	const VEC3 & operator [] (size_t Index) const { return Points[Index]; }

	// Wylicza i zwraca ?rodek frustuma
	void CalcCenter(VEC3 *Out) const;
	// Oblicza najmniejszy AABB otaczaj?cy frustum dany tymi punktami
	void CalcBoundingBox(BOX *Box) const;
	// Oblicza sfer? otaczaj?c? frustum
	// Mo?e nie najlepsz?, ale jak??tam... (a mo?e to jest najlepsza? nie wiem :P)
	void CalcBoundingSphere(VEC3 *SphereCenter, float *SphereRadius) const;
};

/*
Frustum - reprezentacja radarowa.
- Bardzo szybki jest test kolizji z punktem i ze sfer? (PointInFrustum,
  SphereToFrustum).
- UWAGA! Jako wektor Up podawa? prawdziwy wektor kamery do g?ry, tzw. RealUp,
  kt?ry jest naprawd? wzajemnie prostopad?y do Forward i Right, a nie ten kt?ry
  zawsze wynosi (0,1,0) - to by? b??d kt?rego si? naszuka?em.
*/
class FRUSTUM_RADAR
{
private:
	VEC3 m_Eye;
	VEC3 m_Forward;
	VEC3 m_Up;
	VEC3 m_Right;
	float m_RFactor;
	float m_UFactor;
	float m_RSphereFactor;
	float m_USphereFactor;
	float m_ZNear;
	float m_ZFar;

public:
	// Tworzy niezainicjalizowany
	FRUSTUM_RADAR() { }
	// Tworzy w pe?ni zainicjalizowany
	FRUSTUM_RADAR(const VEC3 &Eye, const VEC3 &Forward, const VEC3 &Up, const VEC3 &Right, float FovY, float Aspect, float ZNear, float ZFar) { Set(Eye, Forward, Up, Right, FovY, Aspect, ZNear, ZFar); }

	// Zwraca poszczeg?lne pami?tane pola (FovY i Aspect nie pami?ta bezpo?rednio)
	const VEC3 & GetEye() const     { return m_Eye; }
	const VEC3 & GetForward() const { return m_Forward; }
	const VEC3 & GetUp() const      { return m_Up; }
	const VEC3 & GetRight() const   { return m_Right; }
	float GetZNear() const   { return m_ZNear; }
	float GetZFar() const    { return m_ZFar; }

	// Zwraca dane pomocnicze
	float GetRFactor() const { return m_RFactor; }
	float GetUFactor() const { return m_UFactor; }
	float GetRSphereFactor() const { return m_RSphereFactor; }
	float GetUSphereFactor() const { return m_USphereFactor; }

	// Ustawia poszczeg?lne pola
	void SetEye    (const VEC3 &Eye)     { m_Eye = Eye; }
	void SetForward(const VEC3 &Forward) { m_Forward = Forward; }
	void SetUp     (const VEC3 &Up)      { m_Up = Up; }
	void SetRight  (const VEC3 &Right)   { m_Right = Right; }
	void SetZNear(float ZNear) { m_ZNear = ZNear; }
	void SetZFor (float ZFar)  { m_ZFar = ZFar; }
	void SetFovAndAspect(float FovY, float Aspect);
	
	// Kompletnie wype?nia
	void Set(const VEC3 &Eye, const VEC3 &Forward, const VEC3 &Up, const VEC3 &Right, float FovY, float Aspect, float ZNear, float ZFar) { SetProjection(FovY, Aspect, ZNear, ZFar); SetView(Eye, Forward, Up, Right); }
	// Wype?nia jedn? po??wk? danych
	void SetProjection(float FovY, float Aspect, float ZNear, float ZFar);
	// Wype?nia drug? po??wk? danych
	void SetView(const VEC3 &Eye, const VEC3 &Forward, const VEC3 &Up, const VEC3 &Right);
};


//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// KAPSU?A

// Obj?to?? kapsu?y
float CapsuleVolume(const VEC3 &p1, const VEC3 &p2, float R);


//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// INNE

// Funkcja wyg?adzaj?ca zmian? zmiennej w czasie - SmoothCD.
// Nak?adki na t? funkcj? - szablon specjalizowany dla: float, VEC2, VEC3.
// Klasa szablonowa enkapsuluj?ca pami?tanie parametr?w wyg?adzania.

template <typename T>
inline void SmoothCD_T(T *InOutPos, const T &Dest, T *InOutVel, float SmoothTime, float TimeDelta)
{
	assert(0 && "SmoothCD_T for invalid template type.");
}

template <>
inline void SmoothCD_T<float>(float *InOutPos, const float &Dest, float *InOutVel, float SmoothTime, float TimeDelta)
{
	SmoothCD(InOutPos, Dest, InOutVel, SmoothTime, TimeDelta);
}

template <>
inline void SmoothCD_T<VEC2>(VEC2 *InOutPos, const VEC2 &Dest, VEC2 *InOutVel, float SmoothTime, float TimeDelta)
{
	SmoothCD(&InOutPos->x, Dest.x, &InOutVel->x, SmoothTime, TimeDelta);
	SmoothCD(&InOutPos->y, Dest.y, &InOutVel->y, SmoothTime, TimeDelta);
}

template <>
inline void SmoothCD_T<VEC3>(VEC3 *InOutPos, const VEC3 &Dest, VEC3 *InOutVel, float SmoothTime, float TimeDelta)
{
	SmoothCD(&InOutPos->x, Dest.x, &InOutVel->x, SmoothTime, TimeDelta);
	SmoothCD(&InOutPos->y, Dest.y, &InOutVel->y, SmoothTime, TimeDelta);
	SmoothCD(&InOutPos->z, Dest.z, &InOutVel->z, SmoothTime, TimeDelta);
}

template <typename T>
class SmoothCD_obj
{
public:
	T Pos;
	T Dest; // Zapami?tana ostatnia warto?? docelowa - mo?e si? przyda?.
	T Vel;
	float SmoothTime;

	// Tworzy niezainicjalizowany
	SmoothCD_obj() { }
	// Tworzy zainicjalizowany
	SmoothCD_obj(const T &Pos, float SmoothTime, const T &Vel) : Pos(Pos), Dest(Pos), Vel(Vel), SmoothTime(SmoothTime) { }
	// Ustawia parametry
	void Set(const T &Pos, const T &Vel) { this->Pos = Pos; this->Dest = Pos; this->Vel = Vel; }

	// Wykonuje krok czasowy
	void Update(const T &Dest, float TimeDelta) {
		this->Dest = Dest;
		SmoothCD_T<T>(&Pos, Dest, &Vel, SmoothTime, TimeDelta);
	}
};

// Zamiana mi?dzy uk?adem wsp??rz?dnych:
// - Kartezja?skim DirectX: X w prawo, Y w g?r?, Z w g??b
// - Sferycznym: Yaw to d?ugo?? geograficzna, Pitch to szeroko?? geograficzna, R to promie? wodz?cy

// Tu mo?na podawa? co si? chce.
void SphericalToCartesian(VEC3 *Out, float Yaw, float Pitch, float R);

// Jako OutYaw, OutPitch, OutR mo?na podawa? NULL je?li akurat nas nie interesuje - wtedy liczy szybciej.
// Nie podawa? wektora zerowego bo wyjd? buraki.
// Yaw wychodzi -PI..PI
// Pitch wychodzi -PI/2..PI/2
// R wychodzi > 0
void CartesianToSpherical(float *OutYaw, float *OutPitch, float *OutR, const VEC3 &Pos);

// Zwraca wypuk?? otoczk? zbioru punkt?w 2D.
// - Na wej?ciu musi by? co najmniej jeden punkt.
// - Punkty b?d? u?o?one zgodnie z ruchem wskaz?wek zegara, je?li uk?ad jest X w prawo a Y w d??.
// - Punkty powtarzaj?ce si? s? chyba usuwane, tzn. wynik jest bez powt?rze?.
// - Punkty le??ce na prostej kraw?dzi raz pojawiaj? si? w wyniku a raz nie.
void ConvexHull2D(std::vector<VEC2> *OutPoints, const VEC2 InPoints[], size_t InPointCount);


//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// KOLIZJE

// Dany punkt p i promie? (RayOrig, RayDir).
// Oblicza parametr t dla punktu na tym promieniu b?d?cego rzutem tego punktu na ten promie?.
// W ten spos?b mo?na obliczy? rzut punktu na promie? (punkt z promienia najbli?szy danemu punktowi) jako RayOrig + RayDir*t.
// Mo?na te? policzy? najbli?szy punkt na p??prostej lub odcinku limituj?c najpierw t od 0 do 1 czy od 0 do dlugo?ci odcinka.
// UWAGA! Je?li RayDir nie jest jednostkowy, wynik trzeba podzieli? przez LengthSq(RayDir).
float ClosestPointOnLine(const VEC3 &p, const VEC3 &RayOrig, const VEC3 &RayDir);
// Zwraca odleg?o?? punktu od prostej
// LineDir musi by? znormalizowane!
float PointToLineDistance(const VEC3 &P, const VEC3 &LineOrig, const VEC3 &LineDir);
// Zwraca true, je?li punkt le?y na prostej
// LineDir musi by? znormalizowane!
bool PointOnLine(const VEC3 &P, const VEC3 &LineOrig, const VEC3 &LineDir);
// Zwraca parametr T punktu le??cego na prostej
// Punkt P musi naprawd? le?e? na tej prostej!
float PointToLine(const VEC3 &P, const VEC3 &LineOrig, const VEC3 &LineDir);
// Zwraca true, je?li punkt le?y na odcinku.
// Punkt P musi le?e? na prostej przechodz?cej przez ten odcinek!
bool PointInLineSegment(const VEC3 &P, const VEC3 &SegmentBeg, const VEC3 &SegmentEnd);
// Wyznacza najbli?szy punkt le??cy na odcinku P1-P2 wzgl?dem punktu P
void ClosestPointOnLineSegment(VEC3 *Out, const VEC3 &P, const VEC3 &P1, const VEC3 &P2);
// Wyznacza najbli?szy punkt wewn?trz prostopad?o?cianu wzgl?dem punktu p.
// Je?li p le?y wewn?trz tego prostopad?o?cianu, zwr?cone zostaje dok?adnie p.
void ClosestPointInBox(VEC3 *Out, const BOX &Box, const VEC3 &p);
// Odleg?o?? punktu od prostopad?o?cianu
// Je?li p le?y wewn?trz tego prostopad?o?cianu, zwraca 0.
float PointToBoxDistance(const VEC3 &p, const BOX &box);
// Zwraca true, je?li podany punkt nale?y do sfery
bool PointInSphere(const VEC3 &p, const VEC3 &SphereCenter, float SphereRadius);
// Zwraca odleg?o?? punktu od powierzchni sfery
// Je?li punkt le?y wewn?trz sfery, zwr?ci odleg?o?? ujemn?.
float PointToSphereDistance(const VEC3 &p, const VEC3 &SphereCenter, float SphereRadius);
// Wyznacza najbli?szy punkt na powierzchni sfery wzgl?dem punktu p.
// Punkt mo?e by? wewn?trz sfery - te? jest OK, zwr?ci z powierzchni sfery.
// Punkt nie mo?e by? dok?adnie na ?rodku sfery - wtedy jest dzielenie przez zero.
void ClosestPointOnSphere(VEC3 *Out, const VEC3 &SphereCenter, float SphereRadius, const VEC3 &p);
// Zwraca true, je?li podany punkt nale?y do p?aszczyzny
// P?aszczyzna nie musi by? znormalizowana.
bool PointOnPlane(const VEC3 &p, const PLANE &plane);
// Wyznacza najbli?szy punkt na p?aszczy?nie wzgl?dem punktu p.
void ClosestPointOnPlane(VEC3 *Out, const PLANE &Plane, const VEC3 &p);
// Zwraca true, je?li punkt nale?y do tr?jk?ta
bool PointOnTriangle(const VEC3 &point, const VEC3 &pa, const VEC3 &pb, const VEC3 &pc);
// Zwraca true, je?li punkt nale?y do wn?trza podanego frustuma
bool PointInFrustum(const VEC3 &p, const FRUSTUM_PLANES &Frustum);
bool PointInFrustum(const VEC3 &p, const FRUSTUM_RADAR &Frustum);
// Dane s? dwie proste (RayOrig1, RayDir1) i (RayOrig2, RayDir2).
// Funkcja wyznacza parametry t1 i t2 dla punkt?w na tych prostych, w kt?rych te proste s? najbli?ej siebie.
// Je?li nie da si? takich znale?? (proste s? r?wnoleg?e), funkcja zwraca false.
// Te punkty mo?na policzy? ze wzor?w p1=RayOrig1+t1*RayDir1 i p2=RayOrig2+t2*RayDir2.
// Proste faktycznie przecinaj? si? je?li odleg?o?? mi?dzy tymi punktami wynosi ok. 0.
bool ClosestPointsOnLines(float *OutT1, float *OutT2, const VEC3 &RayOrig1, const VEC3 &RayDir1, const VEC3 &RayOrig2, const VEC3 &RayDir2);
// Kolizja promienia z prostopad?o?cianem
// Je?li promie? nie przecina prostopad?o?cianu, zwraca false.
// Je?li promie? przecina prostopad?o?cian, zwraca true i przez OutT zwraca odleg?o?? w wielokrotno?ciach d?ugo?ci RayDir.
// Je?li promie? przecina prostopad?o?cian od ty?u, funkcja te? zwraca true i zwraca OutT ujemne.
// Je?li RayOrig jest wewn?trz prostopad?o?cianu, funkcja zwraca true i OutT = 0.
bool RayToBox(float *OutT, const VEC3 &RayOrig, const VEC3 &RayDir, const BOX &Box);
// Wylicza kolizj? promienia ze sfer?
// Je?li nie ma kolizji, zwraca false.
// Je?li jest kolizja, zwraca true i parametr T.
// Je?li kolizja jest z ty?u promienia - wcze?niej ni? jego pocz?tek - zwraca true i T ujemne.
// Je?li pocz?tek promienia jest wewn?trz sfery, zwraca true i T=0
bool RayToSphere(const VEC3 &RayOrig, const VEC3 &RayDir, const VEC3 &SphereCenter, float SphereRadius, float *OutT);
// Przeci?cie promienia z p?aszczyzn?
// OutT - zwr?cony parametr dla promienia (NIE mo?na poda? 0)
// OutVD - zwr?cona liczba m?wi?ca o zwrocie p?aszczyzny (NIE mo?na poda? 0)
//   OutVD > 0 oznacza, ?e p?aszczyzna jest ty?em do promienia
// Warto?? zwracana - false je?li promie? by? r?wnoleg?y do p?aszczyzny i nie uda?o si? nic policzy?.
bool RayToPlane(const VEC3 &RayOrig, const VEC3 &RayDir, const PLANE &Plane, float *OutT, float *OutVD);
// Kolizja promienia z tr?jk?tem
// t - mo?na poda? NULL je?li nie interesuje nas odleg?o?? kolizji.
// BackfaceCulling - je?li true, funkcja zawsze uwzgl?dnia wy??cznie kolizj? z tr?jk?tem zwr?conym w stron? CW (jak w DirectX).
bool RayToTriangle(
	const VEC3 &RayOrig, const VEC3 &RayDir,
	const VEC3 &p0, const VEC3 &p1, const VEC3 &p2,
	bool BackfaceCulling,
	float *OutT);
// Kolizja promienia z frustumem
bool RayToFrustum(const VEC3 &RayOrig, const VEC3 &RayDir, const FRUSTUM_PLANES &Frustum, float *t_near, float *t_far);
// Zwraca true je?li kula koliduje z prostopad?o?cianem (tak?e je?li jest w jego ?rodku)
bool SphereToBox(const VEC3 &SphereCenter, float SphereRadius, const BOX &Box);
// Zwraca true, je?li sfera zawiera si? w ca?o?ci w prostopad?o?cianie
bool SphereInBox(const VEC3 &SphereCenter, float SphereRadius, const BOX &Box);
// Zwraca true, je?li prostopad?o?cian zawiera si? w ca?o?ci w sferze
bool BoxInSphere(const BOX &Box, const VEC3 &SphereCenter, float SphereRadius);
// Kolizja p?aszczyzny z prostopad?o?cianem
bool PlaneToBox(const PLANE &plane, const BOX &box);
// Klasyfikuje po?o?enie prostopad?o?cianu wzgl?dem p?aszczyzny
// -1 = prostopad?o?cian w ca?o?ci po ujemnej stronie p?aszczyzny
//  0 = prostopad?o?cian przecina p?aszczyzn?
// +1 = prostopad?o?cian w ca?o?ci po dodatniej stronie p?aszczyzny
int ClassifyBoxToPlane(const PLANE &plane, const BOX &box);
// Zwraca true, je?li tr?jk?t zawiera si? w prostopad?o?cianie
bool TriangleInBox(const VEC3 &p1, const VEC3 &p2, const VEC3 &p3, const BOX &Box);
// Zwraca true, je?li tr?jk?t przecina prostopad?o?cian lub si? w nim zawiera
// OptTrianglePlane mo?na poda? je?li si? ju? ma wyliczone, ?eby przyspieszy?. Nie musi by? znormalizowane.
bool TriangleToBox(const VEC3 &p1, const VEC3 &p2, const VEC3 &p3, const BOX &Box, const PLANE *OptTrianglePlane = NULL);
// Zwraca true, je?li podany prostopad?o?cian jest widoczny cho? troch? w bryle widzenia
// - Uwaga! W rzadkich przypadkach mo?e stwierdzi? kolizj? chocia? jej nie ma.
bool BoxToFrustum_Fast(const BOX &Box, const FRUSTUM_PLANES &Frustum);
// Zwraca true, je?li podany prostopad?o?cian jest widoczny cho? troch? w bryle widzenia
// - Test dok?adny, ale wolniejszy i wymaga te? reprezentacji punktowej frustuma
// - OptFrustumPoints to parametr opcjonalny - podaj je?li masz ju? wyliczony
bool BoxToFrustum(const BOX &Box, const FRUSTUM_PLANES &FrustumPlanes, const FRUSTUM_POINTS *OptFrustumPoints);
bool BoxToFrustum(const BOX &Box, const FRUSTUM_RADAR &Frustum);
// Zwraca true, je?li AABB jest w ca?o?ci wewn?trz frustuma
bool BoxInFrustum(const BOX &Box, const FRUSTUM_PLANES &Frustum);
// Zwraca true je?li podane dwie sfery koliduj? ze sob?
bool SphereToSphere(const VEC3 &Center1, float Radius1, const VEC3 &Center2, float Radius2);
// Zwraca true, je?li sfera koliduje z p?aszczyzn?
// P?aszczyzna chyba musi by? znormalizowana.
bool SphereToPlane(const VEC3 &SphereCenter, float SphereRadius, const PLANE &Plane);
// Klasyfikuje po?o?enie sfery wzgl?dem p?aszczyzny
// -1 = sfera w ca?o?ci po ujemnej stronie p?aszczyzny
//  0 = sfera przecina p?aszczyzn?
// +1 = sfera w ca?o?ci po dodatniej stronie p?aszczyzny
int ClassifySphereToPlane(const VEC3 &SphereCenter, float SphereRadius, const PLANE &Plane);
// Zwraca true, je?li sfera koliduje z frustumem
// - Uwaga! W rzadkich przypadkach mo?e stwierdzi? kolizj? chocia? jej nie ma.
bool SphereToFrustum_Fast(const VEC3 &SphereCenter, float SphereRadius, const FRUSTUM_PLANES &Frustum);
// Zwraca true, je?li sfera koliduje z frustumem
// - Test dok?adny, ale wolniejszy i wymaga te? reprezentacji punktowej frustuma
// - OptFrustumPoints to parametr opcjonalny - podaj je?li masz ju? wyliczony
bool SphereToFrustum(
	const VEC3 &SphereCenter, float SphereRadius,
	const FRUSTUM_PLANES &FrustumPlanes, const FRUSTUM_POINTS *OptFrustumPoints);
// - Uwaga! Wygl?da na to, ?e z nienznaych przyczyn ta funkcja nie zwraca true
//   tak?e dla sfery kt?ra nie jest ?ci?le koliduj?ca z frustumem, ale z pewnym
//   niewielkim marginesem b??du w kierunku +/- Right.
bool SphereToFrustum(const VEC3 &SphereCenter, float SphereRadius, const FRUSTUM_RADAR &Frustum);
// Zwraca true, je?li sfera zawiera si? w ca?o?ci wewn?trz frustuma
bool SphereInFrustum(const VEC3 &SphereCenter, float SphereRadius, const FRUSTUM_PLANES &Frustum);
// Wylicza kolizj? dw?ch p?aszczyzn zwracaj?c parametry prostej tworz?cej ich przeci?cie
// Jesli nie ma kolizji, zwraca false.
// Zwr?cony kierunek promienia nie jest znormalizowany.
bool Intersect2Planes(const PLANE &Plane1, const PLANE &Plane2, VEC3 *LineOrig, VEC3 *LineDir);
// Zwraca punkt przeci?cia trzech p?aszczyzn lub false, je?li taki punkt nie istnieje
bool Intersect3Planes(const PLANE &P1, const PLANE &P2, const PLANE &P3, VEC3 *OutP);
// Kolizja p?aszczyzny z tr?jk?tem
bool PlaneToTriangle(const PLANE &Plane, const VEC3 &p0, const VEC3 &p1, const VEC3 &p2);
// Klasyfikuje po?o?enie tr?jk?ta wzgl?dem p?aszczyzny
// -1 = tr?jk?t w ca?o?ci po ujemnej stronie p?aszczyzny
//  0 = tr?jk?t przecina p?aszczyzn?
// +1 = tr?jk?t w ca?o?ci po dodatniej stronie p?aszczyzny
int ClassifyPlaneToTriangle(const PLANE &Plane, const VEC3 &p0, const VEC3 &p1, const VEC3 &p2);
// Kolizja p?aszczyzny z frustumem (klasyfikacja)
int ClassifyFrustumToPlane(const FRUSTUM_POINTS &Frustum, const PLANE &Plane);
// Zwraca true, je?li dwa odcinki 2D: p1-p2 i p3-p4 zachodz? na siebie
bool IntersectLines(const VEC2 &p1, const VEC2 &p2, const VEC2 &p3, const VEC2 &p4);
// Testuje kolizj? dw?ch tr?jk?t?w 3D
// - Nie wiem co si? dzieje je?li tr?jk?ty s? zdegenerowane.
bool TriangleToTriangle(
	const VEC3 &V0,const VEC3 &V1,const VEC3 &V2,
	const VEC3 &U0,const VEC3 &U1,const VEC3 &U2);
// Testuje, czy tr?jk?t le?y w ca?o?ci wewn?trz frustuma
bool TriangleInFrustum(const VEC3 &t1, const VEC3 &t2, const VEC3 &t3, const FRUSTUM_PLANES &Frustum);
// Testuje kolizj? tr?jk?ta z frustumem
// - Parametry OptTrianglePlane i OptFrustumPoints s? opcjonalne - podaj je?li masz ju? wyliczone, aby przyspieszy?.
bool TriangleToFrustum(
	const VEC3 &t1, const VEC3 &t2, const VEC3 &t3, const PLANE *OptTrianglePlane,
	const FRUSTUM_PLANES &FrustumPlanes, const FRUSTUM_POINTS *OptFrustumPoints);
// Testuje kolizj? mi?dzy dwoma frustumami
bool FrustumToFrustum(
	const FRUSTUM_PLANES &Frustum1_Planes, const FRUSTUM_POINTS &Frustum1_Points,
	const FRUSTUM_PLANES &Frustum2_Planes, const FRUSTUM_POINTS &Frustum2_Points);
// [2D] Zwraca true, je?li podany punkt le?y wewn?trz podanego wielok?ta.
// Wielok?t mo?e mie? dowolny kszta?t, tak?e niewypuk?y, a nawet sam si? przecina?.
// Jego wierzcho?ki mog? biec w dowolnym kierunku.
bool PointInPolygon(const VEC2 &Point, const VEC2 PolygonPoints[], uint PolygonPointCount);
// [3D] Zwraca true, je?li promie? przecina wielok?t i wtedy przez OutT zwraca parametr dla promienia.
// Wierzcho?ki wielok?ta musz? le?e? w jednej p?aszczy?nie.
// Je?li BackfaceCulling = true, promie? trafia tylko je?li wchodzi z jednej strony, z tej z kt?rej
// wierzcho?ki wielok?ta s? widoczne jako zorientowane w kierunku zgodnym ze wskaz?wkami zeraga.
bool RayToPolygon(const VEC3 &RayOrig, const VEC3 &RayDir, const VEC3 PolygonPoints[], uint PolygonPointCount, bool BackfaceCulling, float *OutT);

// Znajduje sfer? otaczaj?c? podany zbi?r punkt?w
// - Nie jest to mo?e najmniejsza sfera, ale przynajmniej ten algorytm jest prosty i szybki.
void SphereBoundingPoints(VEC3 *OutSphereCenter, float *OutSphereRadius, const VEC3 Points[], size_t PointCount);
// Liczy kolizj? poruszaj?cej si? sfery z p?aszczyzn?
// - P?aszczyzna musi by? znormalizowana.
// - Jako OutT0 i OutT1 mo?na podawa? NULL, je?li nas akurat nie interesuje.
// - Je?li sfera porusza si? w drug? stron?, te? wychodzi true i T wychodz? ujemne.
// - Je?li sfera koliduje z p?aszczyzn? i porusza si? w kierunku do niej r?wnoleg?ym, jest T0=0, T1=MAXFLOAT i return true.
bool SweptSphereToPlane(const VEC3 &SphereCenter, float SphereRadius, const VEC3 &SphereSweepDir, const PLANE &Plane, float *OutT0, float *OutT1);
// Oblicza kolizj? poruszaj?cej si? sfery z frustumem
// - Frustum musi by? znormalizowany.
// - Je?li sfera le?y w ?rodku, te? oczywi?cie zwraca true.
bool SweptSphereToFrustum(const VEC3 &SphereCenter, float SphereRadius, const VEC3 &SphereSweepDir, const FRUSTUM_PLANES &Frustum);
// Analityczna kolizja dw?ch poruszaj?cych si? sfer.
// SphereSweepDir1 to kierunek ruchu sfery 1 w stosunku do sfery 2. Nie musi by? znormalizowany.
// Je?li nie ma kolizji, zwraca false. T1 i T2 niezdefiniowane.
// Je?li jest kolizja, zwraca true. W?wczas przez T1 i T2 zwraca czas pocz?tku i ko?ca kolizji wyra?ony we wielokrotno?ciach d?ugo?ci SphereSweepDir1 (T1 <= T2).
// Je?li kolizja nast?puje z ty?u, te? zwraca true, a T1 i/lub T2 b?d? ujemne.
bool SweptSphereToSphere(
	const VEC3 &SphereCenter1, float SphereRadius1,
	const VEC3 &SphereCenter2, float SphereRadius2,
	const VEC3 &SphereSweepDir1,
	float *OutT1, float *OutT2);
// Kolizja poruszaj?cego si? AABB z drugim AABB.
// SweepDirBox1 nie musi by? znormalizowany. T b?dzie wyra?one we wielokrotno?ciach jego d?ugo?ci.
// Je?li nie zachodzi, zwraca false.
// Je?li zachodzi, zwraca true i T jako czas pocz?tkowy kontaktu.
// Je?li zachodzi z ty?u, zwraca true i T ujemne.
// Je?li zachodzi w chwili pocz?tkowej, zwraca true i T=0.
bool SweptBoxToBox(const BOX &Box1, const BOX &Box2, const VEC3 &SweepDirBox1, float *OutT);

// Tworzy najmniejszy boks otaczaj?cy podany zbi?r punkt?w
void BoxBoundingPoints(BOX *box, const VEC3 points[], size_t PointCount);
// Oblicza sfer? otaczaj?c? box
void BoxBoundingSphere(VEC3 *SphereCenter, float *SphereRadius, const BOX &Box);
// Oblicza box otaczaj?cy sfer?
void SphereBoundingBox(BOX *Out, const VEC3 &SphereCenter, float SphereRadius);
// Wylicza AABB otaczaj?cy podany zbi?r sfer
// - SphereCount musi by? wi?ksze od 0.
void BoxBoundingSpheres(BOX *OutBox, const VEC3 SpheresCenter[], const float SpheresRadius[], size_t SphereCount);

// Losuje punkt wewn?trz kuli o ?rodku w (0,0,0) i promieniu 1. Rozk?ad r?wnomierny.
void RandomPointInUnitSphere(VEC3 *Out, RandomGenerator &Rand);
void RandomPointInUnitSphere(VEC3 *Out);
// Losuje punkt wewn?trz ko?a o ?rodku w (0,0) i promieniu 1. Rozk?ad r?wnomierny.
void RandomPointInUnitCircle(VEC2 *Out, RandomGenerator &Rand);
void RandomPointInUnitCircle(VEC2 *Out);
// Losuje punkt z wn?trza kapsu?y. Rozk?ad r?wnomierny.
void RandomPointInCapsule(VEC3 *Out, const VEC3 &p1, const VEC3 &p2, float R, RandomGenerator &Rand);
void RandomPointInCapsule(VEC3 *Out, const VEC3 &p1, const VEC3 &p2, float R);


//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Poisson Disc

extern const float POISSON_DISC_1D[];
const uint4 POISSON_DISC_1D_COUNT = 100;

extern const VEC2 POISSON_DISC_2D[];
const uint4 POISSON_DISC_2D_COUNT = 100;

extern const VEC3 POISSON_DISC_3D[];
const uint4 POISSON_DISC_3D_COUNT = 100;


} // namespace common


//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Konwersje

template <>
struct SthToStr_obj<common::POINT_>
{
	void operator () (string *Str, const common::POINT_ &Sth)
	{
		*Str = common::Format("#,#") % Sth.x % Sth.y;
	}
	static inline bool IsSupported() { return true; }
};

template <>
struct StrToSth_obj<common::POINT_>
{
	bool operator () (common::POINT_ *Sth, const string &Str)
	{
		size_t CommaPos = Str.find(',');
		if (CommaPos == string::npos) return false;
		if (!StrToSth<int>(&Sth->x, Str.substr(0, CommaPos))) return false;
		if (!StrToSth<int>(&Sth->y, Str.substr(CommaPos+1))) return false;
		return true;
	}
	static inline bool IsSupported() { return true; }
};

template <>
struct SthToStr_obj<common::VEC2>
{
	void operator () (string *Str, const common::VEC2 &Sth)
	{
		*Str = common::Format("#,#") % Sth.x % Sth.y;
	}
	static inline bool IsSupported() { return true; }
};

template <>
struct StrToSth_obj<common::VEC2>
{
	bool operator () (common::VEC2 *Sth, const string &Str)
	{
		size_t CommaPos = Str.find(',');
		if (CommaPos == string::npos) return false;
		if (!StrToSth<float>(&Sth->x, Str.substr(0, CommaPos))) return false;
		if (!StrToSth<float>(&Sth->y, Str.substr(CommaPos+1))) return false;
		return true;
	}
	static inline bool IsSupported() { return true; }
};

template <>
struct SthToStr_obj<common::VEC3>
{
	void operator () (string *Str, const common::VEC3 &Sth)
	{
		*Str = common::Format("#,#,#") % Sth.x % Sth.y % Sth.z;
	}
	static inline bool IsSupported() { return true; }
};

template <>
struct StrToSth_obj<common::VEC3>
{
	bool operator () (common::VEC3 *Sth, const string &Str)
	{
		size_t CommaPos1 = Str.find(',');
		if (CommaPos1 == string::npos) return false;
		size_t CommaPos2 = Str.find(',', CommaPos1+1);
		if (CommaPos2 == string::npos) return false;
		if (!StrToSth<float>(&Sth->x, Str.substr(0, CommaPos1))) return false;
		if (!StrToSth<float>(&Sth->y, Str.substr(CommaPos1+1, CommaPos2-(CommaPos1+1)))) return false;
		if (!StrToSth<float>(&Sth->z, Str.substr(CommaPos2+1))) return false;
		return true;
	}
	static inline bool IsSupported() { return true; }
};

template <>
struct SthToStr_obj<common::VEC4>
{
	void operator () (string *Str, const common::VEC4 &Sth)
	{
		*Str = common::Format("#,#,#,#") % Sth.x % Sth.y % Sth.z % Sth.w;
	}
	static inline bool IsSupported() { return true; }
};

template <>
struct StrToSth_obj<common::VEC4>
{
	bool operator () (common::VEC4 *Sth, const string &Str)
	{
		size_t CommaPos1 = Str.find(',');
		if (CommaPos1 == string::npos) return false;
		size_t CommaPos2 = Str.find(',', CommaPos1+1);
		if (CommaPos2 == string::npos) return false;
		size_t CommaPos3 = Str.find(',', CommaPos2+1);
		if (CommaPos3 == string::npos) return false;
		if (!StrToSth<float>(&Sth->x, Str.substr(0, CommaPos1))) return false;
		if (!StrToSth<float>(&Sth->y, Str.substr(CommaPos1+1, CommaPos2-(CommaPos1+1)))) return false;
		if (!StrToSth<float>(&Sth->z, Str.substr(CommaPos2+1, CommaPos3-(CommaPos2+1)))) return false;
		if (!StrToSth<float>(&Sth->w, Str.substr(CommaPos3+1))) return false;
		return true;
	}
	static inline bool IsSupported() { return true; }
};

template <>
struct SthToStr_obj<common::RECTI>
{
	void operator () (string *Str, const common::RECTI &Sth)
	{
		*Str = common::Format("#,#,#,#") % Sth.left % Sth.top % Sth.right % Sth.bottom;
	}
	static inline bool IsSupported() { return true; }
};

template <>
struct StrToSth_obj<common::RECTI>
{
	bool operator () (common::RECTI *Sth, const string &Str)
	{
		size_t CommaPos1 = Str.find(',');
		if (CommaPos1 == string::npos) return false;
		size_t CommaPos2 = Str.find(',', CommaPos1+1);
		if (CommaPos2 == string::npos) return false;
		size_t CommaPos3 = Str.find(',', CommaPos2+1);
		if (CommaPos3 == string::npos) return false;
		if (!StrToSth<int>(&Sth->left,   Str.substr(0, CommaPos1))) return false;
		if (!StrToSth<int>(&Sth->top,    Str.substr(CommaPos1+1, CommaPos2-(CommaPos1+1)))) return false;
		if (!StrToSth<int>(&Sth->right,  Str.substr(CommaPos2+1, CommaPos3-(CommaPos2+1)))) return false;
		if (!StrToSth<int>(&Sth->bottom, Str.substr(CommaPos3+1))) return false;
		return true;
	}
	static inline bool IsSupported() { return true; }
};

template <>
struct SthToStr_obj<common::RECTF>
{
	void operator () (string *Str, const common::RECTF &Sth)
	{
		*Str = common::Format("#,#,#,#") % Sth.left % Sth.top % Sth.right % Sth.bottom;
	}
	static inline bool IsSupported() { return true; }
};

template <>
struct StrToSth_obj<common::RECTF>
{
	bool operator () (common::RECTF *Sth, const string &Str)
	{
		size_t CommaPos1 = Str.find(',');
		if (CommaPos1 == string::npos) return false;
		size_t CommaPos2 = Str.find(',', CommaPos1+1);
		if (CommaPos2 == string::npos) return false;
		size_t CommaPos3 = Str.find(',', CommaPos2+1);
		if (CommaPos3 == string::npos) return false;
		if (!StrToSth<float>(&Sth->left,   Str.substr(0, CommaPos1))) return false;
		if (!StrToSth<float>(&Sth->top,    Str.substr(CommaPos1+1, CommaPos2-(CommaPos1+1)))) return false;
		if (!StrToSth<float>(&Sth->right,  Str.substr(CommaPos2+1, CommaPos3-(CommaPos2+1)))) return false;
		if (!StrToSth<float>(&Sth->bottom, Str.substr(CommaPos3+1))) return false;
		return true;
	}
	static inline bool IsSupported() { return true; }
};

template <>
struct SthToStr_obj<common::BOX>
{
	void operator () (string *Str, const common::BOX &Sth)
	{
		*Str = common::Format("#;#") % Sth.p1 % Sth.p2;
	}
	static inline bool IsSupported() { return true; }
};

template <>
struct StrToSth_obj<common::BOX>
{
	bool operator () (common::BOX *Sth, const string &Str)
	{
		size_t SemicolonPos = Str.find(';');
		if (SemicolonPos == string::npos) return false;
		if (!StrToSth<common::VEC3>(&Sth->p1, Str.substr(0, SemicolonPos))) return false;
		if (!StrToSth<common::VEC3>(&Sth->p2, Str.substr(SemicolonPos+1))) return false;
		return true;
	}
	static inline bool IsSupported() { return true; }
};

template <> struct SthToStr_obj<common::COLOR> {
	void operator () (string *Str, const common::COLOR &Sth) { common::ColorToStr(Str, Sth); }
	static inline bool IsSupported() { return true; }
};
template <> struct StrToSth_obj<common::COLOR> {
	bool operator () (common::COLOR *Sth, const string &Str) { return common::StrToColor(Sth, Str); }
	static inline bool IsSupported() { return true; }
};

template <> struct SthToStr_obj<common::COLORF> {
	void operator () (string *Str, const common::COLORF &Sth) { common::ColorToStr(Str, Sth); }
	static inline bool IsSupported() { return true; }
};
template <> struct StrToSth_obj<common::COLORF> {
	bool operator () (common::COLORF *Sth, const string &Str) { return common::StrToColor(Sth, Str); }
	static inline bool IsSupported() { return true; }
};

template <>
struct SthToStr_obj<common::PLANE>
{
	void operator () (string *Str, const common::PLANE &Sth)
	{
		*Str = common::Format("#,#,#,#") % Sth.a % Sth.b % Sth.c % Sth.d;
	}
	static inline bool IsSupported() { return true; }
};

template <>
struct StrToSth_obj<common::PLANE>
{
	bool operator () (common::PLANE *Sth, const string &Str)
	{
		size_t CommaPos1 = Str.find(',');
		if (CommaPos1 == string::npos) return false;
		size_t CommaPos2 = Str.find(',', CommaPos1+1);
		if (CommaPos2 == string::npos) return false;
		size_t CommaPos3 = Str.find(',', CommaPos2+1);
		if (CommaPos3 == string::npos) return false;
		if (!StrToSth<float>(&Sth->a, Str.substr(0, CommaPos1))) return false;
		if (!StrToSth<float>(&Sth->b, Str.substr(CommaPos1+1, CommaPos2-(CommaPos1+1)))) return false;
		if (!StrToSth<float>(&Sth->c, Str.substr(CommaPos2+1, CommaPos3-(CommaPos2+1)))) return false;
		if (!StrToSth<float>(&Sth->d, Str.substr(CommaPos3+1))) return false;
		return true;
	}
	static inline bool IsSupported() { return true; }
};

template <>
struct SthToStr_obj<common::LINE2D>
{
	void operator () (string *Str, const common::LINE2D &Sth)
	{
		*Str = common::Format("#,#,#") % Sth.a % Sth.b % Sth.c;
	}
	static inline bool IsSupported() { return true; }
};

template <>
struct StrToSth_obj<common::LINE2D>
{
	bool operator () (common::LINE2D *Sth, const string &Str)
	{
		size_t CommaPos1 = Str.find(',');
		if (CommaPos1 == string::npos) return false;
		size_t CommaPos2 = Str.find(',', CommaPos1+1);
		if (CommaPos2 == string::npos) return false;
		if (!StrToSth<float>(&Sth->a, Str.substr(0, CommaPos1))) return false;
		if (!StrToSth<float>(&Sth->b, Str.substr(CommaPos1+1, CommaPos2-(CommaPos1+1)))) return false;
		if (!StrToSth<float>(&Sth->c, Str.substr(CommaPos2+1))) return false;
		return true;
	}
	static inline bool IsSupported() { return true; }
};

template <> struct SthToStr_obj<common::MATRIX> {
	void operator () (string *Str, const common::MATRIX &Sth) { common::MatrixToStr(Str, Sth); }
	static inline bool IsSupported() { return true; }
};
template <> struct StrToSth_obj<common::MATRIX> {
	bool operator () (common::MATRIX *Sth, const string &Str) { return common::StrToMatrix(Sth, Str); }
	static inline bool IsSupported() { return true; }
};

template <>
struct SthToStr_obj<common::QUATERNION>
{
	void operator () (string *Str, const common::QUATERNION &Sth)
	{
		*Str = common::Format("#,#,#,#") % Sth.x % Sth.y % Sth.z % Sth.w;
	}
	static inline bool IsSupported() { return true; }
};

template <>
struct StrToSth_obj<common::QUATERNION>
{
	bool operator () (common::QUATERNION *Sth, const string &Str)
	{
		size_t CommaPos1 = Str.find(',');
		if (CommaPos1 == string::npos) return false;
		size_t CommaPos2 = Str.find(',', CommaPos1+1);
		if (CommaPos2 == string::npos) return false;
		size_t CommaPos3 = Str.find(',', CommaPos2+1);
		if (CommaPos3 == string::npos) return false;
		if (!StrToSth<float>(&Sth->x, Str.substr(0, CommaPos1))) return false;
		if (!StrToSth<float>(&Sth->y, Str.substr(CommaPos1+1, CommaPos2-(CommaPos1+1)))) return false;
		if (!StrToSth<float>(&Sth->z, Str.substr(CommaPos2+1, CommaPos3-(CommaPos2+1)))) return false;
		if (!StrToSth<float>(&Sth->w, Str.substr(CommaPos3+1))) return false;
		return true;
	}
	static inline bool IsSupported() { return true; }
};

#endif
