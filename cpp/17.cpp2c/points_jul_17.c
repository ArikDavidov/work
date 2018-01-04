#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PHASE (2)

/***** Phase 1 *****{{ */
#if PHASE >= 1
/*class Point2D*/
/*{*/
/*private:*/
typedef struct Point2D
{
    double m_x;
    double m_y;
} Point2D;
/*public:*/
    
/*  Point2D();*/
    void Point2D_CTOR(Point2D* const _this);
/*  Point2D(double _x, double _y);*/
    void Point2D_CTOR_double_double(Point2D* const _this, double _x, double _y);
    void Point2D_CTOR_const_Point2D_ref(Point2D* const _this, const Point2D* const _other);
/*  double GetX() const;*/
/*  double GetY() const;*/
/*  double Distance(const Point2D& _other) const;*/
    double Point2D_Distance_const_Point2D_ref(const Point2D* const _this, const Point2D* const _other);

/*  Point2D &operator+=(const Point2D& _other);*/
Point2D* const Point2D_operator_plus_equl_const_Point2D_ref(Point2D* const _this, const Point2D* const _other);
/*  Point2D &operator*=(double _factor);*/
Point2D* const Point2D_operator_mult_equl_double(Point2D* const _this, double _factor);

/*Point2D::Point2D()*/
void Point2D_CTOR(Point2D* const _this)
/*: m_x(0), m_y(0)*/
{
    _this->m_x = 0;
    _this->m_y = 0;
}

/*Point2D::Point2D(double _x, double _y)*/
void Point2D_CTOR_double_double(Point2D* const _this, double _x, double _y)
/*: m_x(_x), m_y(_y)*/
{
    _this->m_x = _x;
    _this->m_y = _y;
}
void Point2D_CTOR_const_Point2D_ref(Point2D* const _this, const Point2D* const _point)
{
    _this->m_x = _point->m_x;
    _this->m_y = _point->m_y;
}

/*inline double Point2D::GetX() const*/
#define Point2D_GetX(T) (T)->m_x
/*{*/
/*  return m_x;*/
/*}*/

/*inline double Point2D::GetY() const*/
#define Point2D_GetY(T) (T)->m_y
/*{*/
/*  return m_y;*/
/*}*/

/*double Point2D::Distance(const Point2D& _other) const*/
double Point2D_Distance_const_Point2D_ref(const Point2D* const _this, const Point2D* const _other)
{
    double dx = _this->m_x - _other->m_x;
    double dy = _this->m_y - _other->m_y;
    return sqrt(dx * dx + dy * dy);
}

/*Point2D& Point2D::operator+=(const Point2D& _other)*/
Point2D* const Point2D_operator_plus_equl_const_Point2D_ref(Point2D* const _this, const Point2D* const _other)
{
    _this->m_x += _other->m_x;
    _this->m_y += _other->m_y;
    
    return _this;
}

/*Point2D& Point2D::operator*=(double _factor)*/
Point2D* const Point2D_operator_mult_equl_double(Point2D* const _this, double _factor)
{
    _this->m_x *= _factor;
    _this->m_y *= _factor;
    
    return _this;
}

void pointless()
{
    void Point2D_CTOR_double_double(Point2D* const _this, double _x, double _y);
    
/*  Point2D p0;*/
    Point2D p0;
    Point2D_CTOR(&p0);
/*  Point2D p1(0,10);*/
    Point2D p1;
    Point2D_CTOR_double_double(&p1, 0, 10);
/*  printf("distance p0 --> p1 == %f\n", p0.Distance(p1));*/
    printf("distance p0 --> p1 == %f\n", Point2D_Distance_const_Point2D_ref(&p0,&p1));
    
/*  Point2D dxy(+4, -7);*/
    Point2D dxy;
    Point2D_CTOR_double_double(&dxy, +4, -7);
/*  p1 += dxy;*/
    Point2D_operator_plus_equl_const_Point2D_ref(&p1, &dxy);
/*  printf("%f, %f\n", p1.GetX(), p1.GetY());*/
    printf("%f, %f\n", Point2D_GetX(&p1), Point2D_GetY(&p1));
/*  printf("now distance p0 --> p1 == %f\n", p0.Distance(p1));*/
    printf("now distance p0 --> p1 == %f\n", Point2D_Distance_const_Point2D_ref(&p0, &p1));
}

#endif

/* }} ***** Phase 1 *****/


/*----------------------------------------------------------------*/
/***** Phase 2 *****{{ */
#if PHASE >= 2

/*class NamedPoint2D : public Point2D*/
/*public:*/
/*private:*/
/*  const char *m_name; */
typedef struct NamedPoint2D
{
    double m_x;
    double m_y;
    const char *m_name;
} NamedPoint2D;


/*  NamedPoint2D(const char *_name = "origin");*/
void NamedPoint2D_CTOR_const_char_ptr(NamedPoint2D* const _this, const char *_name);
/*  NamedPoint2D(double _x, double _y, const char *_name = "anonymous Point");*/
void NamedPoint2D_CTOR_double_double_const_char_ptr(NamedPoint2D* const _this, double _x, double _y, const char *_name);
/*  NamedPoint2D(const Point2D& point, const char *_name = "anonymous Point");*/
void NamedPoint2D_CTOR_const_Point2D_ref_const_char_ptr(NamedPoint2D* const _this, const Point2D* const _point, const char *_name);
/*  const char *GetName() const;*/
const char *NamedPoint2D_const_GetName(NamedPoint2D* const _this);



/*NamedPoint2D::NamedPoint2D(const char *_name)*/
/*: m_name(_name)*/
void NamedPoint2D_CTOR_const_char_ptr(NamedPoint2D* const _this, const char *_name)
{
    Point2D_CTOR((Point2D* const)_this);
    _this->m_name = _name;
}

/*NamedPoint2D::NamedPoint2D(double _x, double _y, const char *_name)*/
void NamedPoint2D_CTOR_double_double_const_char_ptr(NamedPoint2D* const _this, double _x, double _y, const char *_name)
/*: m_name(_name), Point2D(_x, _y)*/
{
    Point2D_CTOR_double_double((Point2D* const)_this, _x, _y);
    _this->m_name = _name;
}

/*NamedPoint2D::NamedPoint2D(const Point2D& _point, const char *_name)*/
void NamedPoint2D_CTOR_const_Point2D_ref_const_char_ptr(NamedPoint2D* const _this, const Point2D* const _point, const char *_name)
/*: m_name(_name), Point2D(_point)*/
{
    Point2D_CTOR_const_Point2D_ref((Point2D* const)_this, _point);
    _this->m_name = _name;
}

/*const char *NamedPoint2D::GetName() const*/
const char *const_NamedPoint2D_GetName(NamedPoint2D* const _this)
{
    // return m_name;
    return _this->m_name;
}


/*----------------------------------------------------------------*/

const int Rectangle_static_s_curvature = 1;

// typedef class Rectangle
typedef struct Rectangle
{
// public:
// private:
    // static const int s_curvature = 1;
    NamedPoint2D m_a;
    Point2D m_b;
} Rectangle;


    
    // Rectangle(const Point2D& _a, const Point2D& _b, const char *_name = "anonymous Rectangle");
    void Rectangle_CTOR_const_Point2D_ref_const_Point2D_ref_const_char_ptr(Rectangle* const _this, const Point2D* const _a, const Point2D* const _b, const char *_name);
    // const char *GetName() const;
    const char *Rectangle_const_GetName(Rectangle* const _this);
    // double CalcArea() const;
    double Rectangle_const_CalcArea();



// Rectangle::Rectangle(const Point2D& _a, const Point2D& _b, const char *_name)
// : m_a(_a, _name), m_b(_b)
void Rectangle_CTOR_const_Point2D_ref_const_Point2D_ref_const_char_ptr(Rectangle* const _this, const Point2D* const _a, const Point2D* const _b, const char *_name)
{
    NamedPoint2D_CTOR_const_Point2D_ref_const_char_ptr(&_this->m_a, _a, _name);
    Point2D_CTOR_const_Point2D_ref(&_this->m_b, _b);
}

// const char *Rectangle::GetName() const
const char *Rectangle_const_GetName(Rectangle* const _this)
{
    // return m_a.GetName();
    return _this->m_a.m_name;
}

// double Rectangle::CalcArea() const
double Rectangle_const_CalcArea(Rectangle* const _this)
{
    // Point2D p1(m_a.GetX(), m_b.GetY());
    Point2D p1;
    Point2D_CTOR_double_double(&p1, _this->m_a.m_x, _this->m_b.m_y);
    
    // double sideA = m_a.Distance(p1);
    double sideA = Point2D_Distance_const_Point2D_ref((const Point2D* const)&_this->m_a, &p1);
    
    // double sideB = m_a.Distance(Point2D(m_b.GetX(), m_a.GetY()));
    Point2D tmp;
    Point2D_CTOR_double_double(&tmp, _this->m_b.m_x, _this->m_a.m_y);
    double sideB = Point2D_Distance_const_Point2D_ref((const Point2D* const)&_this->m_a, &tmp);
    
    // tmp DTOR
    // p1 DTOR    
    
    // return sideA * sideB * s_curvature;
    return sideA * sideB * Rectangle_static_s_curvature;
}

/*----------------------------------------------------------------*/

void dog()
{
    // NamedPoint2D home(5,7, "home");
    NamedPoint2D home;
    NamedPoint2D_CTOR_double_double_const_char_ptr(&home, 5, 7, "home");

    // Point2D point(home);
    Point2D point;
    Point2D_CTOR_const_Point2D_ref(&point, (const Point2D * const)&home);
    
    // NamedPoint2D dog(point);
    NamedPoint2D dog;
    NamedPoint2D_CTOR_const_Point2D_ref_const_char_ptr(&dog, &point, "anonymous Point");

    // dog *= 2;
    Point2D_operator_mult_equl_double((Point2D * const)&dog, 2);

    // printf("Distance from %s to %s is %f\n", home.m_name, dog.m_name, home.Distance(dog));
    printf("Distance from %s to %s is %f\n", home.m_name, dog.m_name,
            Point2D_Distance_const_Point2D_ref((const Point2D * const)&home, (const Point2D* const)&dog));

    // dog DTOR
    // point DTOR
    // home DTOR
}

void area()
{
    // Point2D p0;
    Point2D p0;
    Point2D_CTOR(&p0);

    // Point2D p1(12,12);
    Point2D p1;
    Point2D_CTOR_double_double(&p1, 12, 12);

    // Rectangle r(p0, p1);
    Rectangle r;
    Rectangle_CTOR_const_Point2D_ref_const_Point2D_ref_const_char_ptr(&r, &p0, &p1, "anonymous Rectangle");
    
    // printf("The area of %s is %f\n", r.GetName(), r.CalcArea());
    printf("The area of %s is %f\n", r.m_a.m_name, Rectangle_const_CalcArea(&r));
    // printf("rectangle size %zu", sizeof(r));
    printf("rectangle size %zu", sizeof(r));
}

#endif
 /* }} ***** Phase 2 *****/

/*----------------------------------------------------------------*/

int main()
{
#if PHASE >= 1
    pointless();
#endif

#if PHASE >= 2
    dog();
    area();
#endif

    return 0;
}

