#pragma once

template <class T>
class Vector2
{
   public:
      Vector2();
      Vector2(T x, T y);
      Vector2(const Vector2 &rhs);
      Vector2 & operator=(const Vector2 &rhs);
      Vector2 & operator+=(const Vector2 &rhs);
      Vector2 & operator-=(const Vector2 &rhs);
      bool operator==(const Vector2 &rhs) const;
      bool operator!=(const Vector2 &rhs) const;
      Vector2 operator+(Vector2 &rhs) const;
      Vector2 operator-(Vector2 &rhs) const;
      Vector2 operator+(const T & rhs) const;
      Vector2 operator-(const T & rhs) const;
      Vector2 operator*(const T & rhs) const;
      Vector2 operator/(const T & rhs) const;
      Vector2 & operator*=(const T & rhs);
   	Vector2 & operator/=(const T & rhs);
      T x() const;
      T y() const;
      Vector2 & setX(T x);
      Vector2 & setY(T y);
      Vector2 & set(T x, T y);
      Vector2 rotate(T deg) const;
      Vector2 normalize() const;
      Vector2 scale(const T & scale) const;
      double distance(const Vector2 &v) const;
      double length() const;
      double angle() const;
      Vector2 truncate(const T & length) const;
      double dot(const Vector2 &rhs) const;
      double cross(const Vector2 &rhs) const;
      static Vector2 midpoint(const Vector2 &a, const Vector2 &b);

   protected:
      T _x, _y;
};

typedef Vector2<float> Vector2f;
typedef Vector2<double> Vector2d;
typedef Vector2<int> Vector2i;

#include <Vector2.cpp>


/* For debugging vectors
*/
#include <iostream>
std::ostream & operator<<(std::ostream & out, const Vector2d & v); 

