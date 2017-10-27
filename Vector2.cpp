#include <Vector2.h>
#include <cmath>

template <class T> Vector2<T>::Vector2() : _x(0), _y(0) { }
template <class T> Vector2<T>::Vector2(T x, T y) : _x(x), _y(y) { }
template <class T> Vector2<T>::Vector2(const Vector2 &rhs) : _x(rhs._x), _y(rhs._y) { }
template <class T> Vector2<T> & Vector2<T>::operator=(const Vector2 &rhs) {
         _x = rhs._x;
         _y = rhs._y;
         return *this;
}

template <class T> Vector2<T> Vector2<T>::operator+(Vector2 &rhs)  const {
         return Vector2(_x + rhs._x, _y + rhs._y);
}

template <class T> Vector2<T> Vector2<T>::operator-(Vector2 &rhs)  const {
         return Vector2(_x - rhs._x, _y - rhs._y);
}

template <class T> Vector2<T> & Vector2<T>::operator+=(const Vector2 &rhs)
{
   _x += rhs._x;
   _y += rhs._y;
   return *this;
}

template <class T> Vector2<T> & Vector2<T>::operator-=(const Vector2 &rhs)
{
   _x -= rhs._x;
   _y -= rhs._y;
   return *this;
}

template <class T> Vector2<T> Vector2<T>::operator+(const T & rhs) const
{
   return Vector2(_x + rhs, _y + rhs);
}

template <class T> Vector2<T> Vector2<T>::operator-(const T & rhs) const
{
   return Vector2(_x - rhs, _y - rhs);
}

template <class T> Vector2<T> Vector2<T>::operator*(const T & rhs) const
{
   return Vector2(_x * rhs, _y * rhs);
}

template <class T> Vector2<T> Vector2<T>::operator/(const T & rhs) const
{
   return Vector2(_x / rhs, _y / rhs);
}

template <class T> Vector2<T> & Vector2<T>::operator*=(const T & rhs)
{
   _x *= rhs;
   _y *= rhs;
   return *this;
}

template <class T> Vector2<T> & Vector2<T>::operator/=(const T & rhs)
{
   _x /= rhs;
   _y /= rhs;
   return *this;
}

template <class T> T Vector2<T>::x() const { return _x; }

template <class T> T Vector2<T>::y() const { return _y; }

template <class T> Vector2<T> & Vector2<T>::setX(T x)
{
   _x = x;
   return *this;
}

template <class T> Vector2<T> & Vector2<T>::setY(T y)
{
   _y = y;
   return *this;
}

template <class T> Vector2<T> & Vector2<T>::set(T x, T y)
{
   _x = x;
   _y = y;
   return *this;
}

template <class T> Vector2<T> Vector2<T>::rotate(T deg) const
{
   double theta = deg / 180.0 * M_PI;
   double c = cos(theta);
   double s = sin(theta);
   double tx = _x * c - _y * s;
   double ty = _x * s + _y * c;
   return Vector2(tx, ty);
}

template <class T> Vector2<T> Vector2<T>::normalize() const
{
   if (length() == 0) return *this;
	return Vector2(*this * (1.0 / length()));
}

template <class T> Vector2<T> Vector2<T>::scale(const T & scale) const
{
   if (length() == 0) return *this;
	return Vector2(_x*scale, _y*scale);
}

template <class T> double Vector2<T>::distance(const Vector2 &rhs) const
{
   Vector2 d(rhs._x - _x, rhs._y - _y);
   return d.length();
}

template <class T> double Vector2<T>::length() const {
   return std::sqrt(_x * _x + _y * _y);
}

template <class T> double Vector2<T>::angle() const {
		double angle = atan(_y / _x) * 180 / M_PI;
		if(_x > 0) angle += 180;
		return angle;
}

//bstatic
template <class T> Vector2<T> Vector2<T>::midpoint(const Vector2 &a,
    const Vector2 &b)
{
   Vector2 c = a;
   double x = ((double) a._x + (double) b._x) / 2.0;
   double y = ((double) a._y + (double) b._y) / 2.0;
   T xt = x;
   T yt = y;
   return Vector2 (xt, yt);
}

template <class T> bool Vector2<T>::operator==(const Vector2 &rhs) const
{
   if(_x != rhs._x || _y != rhs._y) return false;
   return true;
}

template <class T> bool Vector2<T>::operator!=(const Vector2 &rhs) const
{
   return !(*this == rhs);
}

template <class T> Vector2<T> Vector2<T>::truncate(const T & length) const {
		double angle = atan2f(_y, _x);
		double x = length * cos(angle);
		double y = length * sin(angle);
      return Vector2(x,y);
}

template <class T> double Vector2<T>::dot(const Vector2 &rhs) const
{
   return (double) _x * (double) rhs._x + (double) rhs._y * (double) _y;
}

template <class T> double Vector2<T>::cross(const Vector2 &rhs) const
{
   return (_x * rhs._y) - (_y * rhs._x);
}
