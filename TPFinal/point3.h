#pragma
struct Point3
{
	float x, y, z;
	
	Point3() {}
	Point3(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	inline bool operator==(Point3 pt)
	{
		if(x == pt.x && y == pt.y && z == pt.z)
			return true;
		return false;
	}

	inline bool operator!=(Point3 pt)
	{
		return !((*this) == pt);
	}

	inline Point3 operator+(Point3 pt)
	{
		Point3 res;
		res.x = x + pt.x;
		res.y = y + pt.y;
		res.z = z + pt.z;
		return (*this);
	}

	inline Point3 operator-(Point3 pt)
	{
		Point3 res;
		res.x = x - pt.x;
		res.y = y - pt.y;
		res.z = z - pt.z;
		return (*this);
	}

	inline Point3 operator+=(Point3 pt)
	{
		x += pt.x;
		y += pt.y;
		z += pt.z;
		return (*this);
	}

	inline Point3 operator-=(Point3 pt)
	{
		x -= pt.x;
		y -= pt.y;
		z -= pt.z;
		return (*this);
	}
	
	inline Point3 operator^(Point3 pt)
	{
		Point3 res;
		res.x = (y*pt.z) - (z*pt.y);
		res.y = -( (x*pt.z) - (z*pt.x) );
		res.z = (x*pt.y) - (y*pt.x);
		return res;
	}

	inline Point3 operator*(Point3 pt)
	{
		Point3 res;
		res.x = x * pt.x;
		res.y = y * pt.y;
		res.z = z * pt.z;
		return res;
	}

	inline Point3 operator/(Point3 pt)
	{
		Point3 res;
		res.x = x / pt.x;
		res.y = y / pt.y;
		res.z = z / pt.z;
		return res;
	}

	inline Point3 operator*=(Point3 pt)
	{
		x *= pt.x;
		y *= pt.y;
		z *= pt.z;
		return (*this);
	}

	inline Point3 operator/=(Point3 pt)
	{
		x /= pt.x;
		y /= pt.y;
		z /= pt.z;
		return (*this);
	}

	inline Point3 operator*(float f)
	{
		Point3 res;
		res.x = x * f;
		res.y = y * f;
		res.z = z * f;
		return res;
	}

	inline Point3 operator/(float f)
	{
		Point3 res;
		res.x = x / f;
		res.y = y / f;
		res.z = z / f;
		return res;
	}

	inline Point3 operator*=(float f)
	{
		x *= f;
		y *= f;
		z *= f;
		return (*this);
	}

	inline Point3 operator/=(float f)
	{
		x /= f;
		y /= f;
		z /= f;
		return (*this);
	}

	inline float Sca(Point3 pt)
	{
		return (x*pt.x + y*pt.y + z*pt.z);
	}

	inline void Normalize()
	{
		operator*=(1 / sqrt(x*x + y*y + z*z));
	}
};