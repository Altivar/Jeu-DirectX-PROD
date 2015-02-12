#pragma
struct Point2
{
	float x, y;
	
	Point2() {}
	Point2(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	inline bool operator==(Point2 pt)
	{
		if(x == pt.x && y == pt.y)
			return true;
		return false;
	}

	inline bool operator!=(Point2 pt)
	{
		return !((*this) == pt);
	}

	inline Point2 operator+(Point2 pt)
	{
		Point2 res;
		res.x = x + pt.x;
		res.y = y + pt.y;
		return (*this);
	}

	inline Point2 operator-(Point2 pt)
	{
		Point2 res;
		res.x = x - pt.x;
		res.y = y - pt.y;
		return (*this);
	}

	inline Point2 operator+=(Point2 pt)
	{
		x += pt.x;
		y += pt.y;
		return (*this);
	}

	inline Point2 operator-=(Point2 pt)
	{
		x -= pt.x;
		y -= pt.y;
		return (*this);
	}

	inline Point2 operator*(Point2 pt)
	{
		Point2 res;
		res.x = x * pt.x;
		res.y = y * pt.y;
		return res;
	}

	inline Point2 operator/(Point2 pt)
	{
		Point2 res;
		res.x = x / pt.x;
		res.y = y / pt.y;
		return res;
	}

	inline Point2 operator*=(Point2 pt)
	{
		x *= pt.x;
		y *= pt.y;
		return (*this);
	}

	inline Point2 operator/=(Point2 pt)
	{
		x /= pt.x;
		y /= pt.y;
		return (*this);
	}

	inline Point2 operator*(float f)
	{
		Point2 res;
		res.x = x * f;
		res.y = y * f;
		return res;
	}

	inline Point2 operator/(float f)
	{
		Point2 res;
		res.x = x / f;
		res.y = y / f;
		return res;
	}

	inline Point2 operator*=(float f)
	{
		x *= f;
		y *= f;
		return (*this);
	}

	inline Point2 operator/=(float f)
	{
		x /= f;
		y /= f;
		return (*this);
	}

	inline float Sca(Point2 pt)
	{
		return (x*pt.x + y*pt.y);
	}

	inline void Normalize()
	{
		operator*=(1 / sqrt(x*x + y*y));
	}

};