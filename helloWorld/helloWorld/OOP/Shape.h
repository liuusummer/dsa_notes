#ifndef Shape_h_
#define Shape_h_
#include <utility>
#include <tuple>
class Shape_base {
public:
	using value_type = double;
	virtual ~Shape_base() = default;
};

class Shape2D_base :public Shape_base {
public:
	using value_type = Shape_base::value_type;
	// 二维坐标
	using Coordinate = std::pair<value_type, value_type>;
	// 周长
	virtual value_type perimeter() const = 0;
	// 面积
	virtual value_type area()const = 0;    
};

class Shape3D_base : public Shape_base {
public:
	using value_type = Shape_base::value_type;
	// 三维坐标
	using Coordinate = std::tuple<value_type, value_type, value_type>;
	// 面积
	virtual value_type area() const = 0;
	// 体积
	virtual value_type volumn() const = 0;
};

class Circle : public Shape2D_base {};
class Ellipse : public Shape2D_base {};
class Square : public Shape2D_base {};
class Rectangle : public Shape2D_base {};
class Sphere : public Shape3D_base {};
class Cube : public Shape3D_base {};
class Box : public Shape3D_base {};
class Cone : public Shape3D_base {};
#endif