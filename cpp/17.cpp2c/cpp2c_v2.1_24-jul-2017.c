#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


/*struct Color {*/
/*  enum ColorEnum { RED, GREEN, DEFAULT };*/
/*  static void setColor(ColorEnum color){*/
/*      static const char * pallete[] = { "\x1B[31m", "\x1B[32m", "\033[0m" };*/
/*      puts(pallete[color]);*/
/*  }*/
/*};*/
typedef struct Color {
} Color;

typedef enum Color_ColorEnum{
    Color_RED, 
    Color_GREEN, 
    Color_DEFAULT
} Color_ColorEnum;

void Color_setColor_Color_ColorEnum(Color_ColorEnum color){
    const char * pallete[] = { "\x1B[31m", "\x1B[32m", "\033[0m" };
    puts(pallete[color]);
}

/*class Scaleable {*/
/*public:*/
/*  virtual ~Scaleable() { }    */
/*  virtual void scale(double) = 0;*/
/*};*/
typedef struct Scaleable {
    void (***m_vPtr)(void*);
} Scaleable;

void Scaleable_DTOR();
void Scaleable_scale_double(Scaleable* const _this, double _f);

void (*vtable_Scaleable[])(void*) = { (void (*)(void*))Scaleable_DTOR,
                                      (void (*)(void*))Scaleable_scale_double };

void Scaleable_DTOR() { }
void Scaleable_scale_double(Scaleable* const _this, double _f){
    fprintf(stderr, "Error: pure virtual function called\n");
    assert(0);
}

/*class Shape : public Scaleable {*/
/*public:*/
typedef struct Shape {
    Scaleable m_scaleable;
    int       m_id;
} Shape;

int Shape_NumOfShapes = 0;

void   Shape_DTOR(Shape* const _this);
void   Shape_scale_double(Shape* const _this, double _f);
void   Shape_const_draw(const Shape* const _this);
void   Shape_const_draw_Color_ColorEnum(const Shape* const _this, Color_ColorEnum _c);
double Shape_const_area();

void (*vtable_Shape[])(void*) = { (void (*)(void*))Shape_DTOR,
                                  (void (*)(void*))Shape_scale_double,
                                  (void (*)(void*))Shape_const_draw,
                                  (void (*)(void*))Shape_const_draw_Color_ColorEnum,
                                  (void (*)(void*))Shape_const_area  };
                          
/*  Shape() : m_id(++NumOfShapes) {*/
/*      printf("Shape::Shape() - %d\n", m_id); */
/*  }*/
    void Shape_CTOR(Shape* const _this)
    {
        // Scaleable CTOR
        
        *((void (***)(void*))_this) = vtable_Shape;
        
        _this->m_id = ++Shape_NumOfShapes;
        printf("Shape::Shape() - %d\n", _this->m_id); 
    }

/*  ~Shape() {*/
/*      draw();*/
/*      --NumOfShapes; */
/*      printf("Shape::~Shape - %d\n", m_id);*/
/*  }*/
    void Shape_DTOR(Shape* const _this) {
        
        Shape_const_draw(_this);
        --Shape_NumOfShapes;
        printf("Shape::~Shape - %d\n", _this->m_id);

        *((void (***)(void*))_this) = vtable_Scaleable;
        // Scaleable DTOR
    }

/*    Shape(const Shape& other) : m_id(++NumOfShapes) {*/
/*      printf("Shape::Shape(Shape&) - %d from - %d\n", m_id, other.m_id);*/
/*    }*/
    void Shape_CTOR_const_Shape_ref(Shape* const _this, const Shape* const _other)
    {
        // Scaleable CTOR
        *((void (***)(void*))_this) = vtable_Shape;
        
        _this->m_id = ++Shape_NumOfShapes;
        printf("Shape::Shape(Shape&) - %d from - %d\n", _this->m_id, _other->m_id);
    }

/*    virtual void draw() const {*/
/*      printf("Shape::draw() - %d\n", m_id);       */
/*    }*/
    void Shape_const_draw(const Shape* const _this){
        printf("Shape::draw() - %d\n", _this->m_id);
    }
    
/*    virtual void draw(Color::ColorEnum c) const {*/
/*      printf("Shape::draw(c) - %d\n", m_id);*/
/*      Color::setColor(c);*/
/*      draw();*/
/*      Color::setColor(Color::DEFAULT);*/
/*    }*/
    void Shape_const_draw_Color_ColorEnum(const Shape* const _this, Color_ColorEnum _c) {
        printf("Shape::draw(c) - %d\n", _this->m_id);
        Color_setColor_Color_ColorEnum(_c);
        Shape_const_draw(_this);
        Color_setColor_Color_ColorEnum(Color_DEFAULT);
    }
    
/*    virtual void scale(double f = 1) { */
/*      printf("Shape::scale(%f)\n", f);*/
/*    }*/
    void Shape_scale_double(Shape* const _this, double _f) { 
        printf("Shape::scale(%f)\n", _f);
    }

/*    virtual double area() const { return -1; }*/
    double Shape_const_area(Shape* const _this)  { return -1; }
    
/*    static void printInventory() {*/
/*      printf("Shape::printInventory - %d\n", NumOfShapes);*/
/*    }*/    
    void Shape_static_printInventory() {
        printf("Shape::printInventory - %d\n", Shape_NumOfShapes);
    }
    
/*private:*/
/*  static int NumOfShapes;*/
/*  Shape& operator=(const Shape &); // disabled, no implementation provided*/

/*protected:*/
/*   int m_id;*/


/*int Shape_NumOfShapes = 0;*/



/*class Circle : public Shape { */
/*public:*/
/*private:*/
/*  double m_radius;*/
/*};*/
typedef struct Circle{
    Shape  m_shape;
    double m_radius;
} Circle;

void   Circle_DTOR(Circle* const _this);
void   Circle_scale_double(Circle* const _this, double _f);
void   Circle_const_draw(Circle* const _this);
double Circle_const_area(Circle* const _this);
double Circle_const_radius(Circle* const _this);

void (*vtable_Circle[])(void*) = { (void (*)(void*))Circle_DTOR,
                                   (void (*)(void*))Circle_scale_double,
                                   (void (*)(void*))Circle_const_draw,
                                   (void (*)(void*))Shape_const_draw_Color_ColorEnum,
                                   (void (*)(void*))Circle_const_area,
                                   (void (*)(void*))Circle_const_radius  };


/*  Circle() : m_radius(1) { */
/*      printf("Circle::Circle() - %d, r:%f\n", m_id, m_radius); */
/*  }*/
    void Circle_CTOR(Circle* const _this)
    { 
        Shape_CTOR((Shape*)_this);
        *((void (***)(void*))_this) = vtable_Circle;
        _this->m_radius = 1;
        printf("Circle::Circle() - %d, r:%f\n", ((Shape*)_this)->m_id, _this->m_radius);
    }

/*  Circle(double r) : m_radius(r) { */
/*      printf("Circle::Circle(double) - %d, r:%f\n", m_id, m_radius); */
/*  }*/
    void Circle_CTOR_double(Circle* const _this, double _r)
    { 
        Shape_CTOR((Shape*)_this);
        *((void (***)(void*))_this) = vtable_Circle;
        
        _this->m_radius = _r;
        printf("Circle::Circle(double) - %d, r:%f\n", ((Shape*)_this)->m_id, _this->m_radius);
    }

/*  Circle(const Circle& other)*/
/*  : Shape(other), m_radius(other.m_radius) { */
/*      printf("Circle::Circle(Circle&) - %d, r:%f\n", m_id, m_radius);*/
/*  }*/
    void Circle_CTOR_const_Circle_ref(Circle* const _this, const Circle* const _other)
    {
        Shape_CTOR_const_Shape_ref((Shape*)_this, (const Shape* const) _other);
        *((void (***)(void*))_this) = vtable_Circle;
        
        _this->m_radius = _other->m_radius;
        
        printf("Circle::Circle(Circle&) - %d, r:%f\n", ((Shape*)_this)->m_id, _this->m_radius);
    }

/*  ~Circle() { */
/*      printf("Circle::~Circle() - %d, r:%f\n", m_id, m_radius); */
/*  }*/
    void Circle_DTOR(Circle* const _this) {
        
        printf("Circle::~Circle() - %d, r:%f\n", ((Shape*)_this)->m_id, _this->m_radius);

        *((void (***)(void*))_this) = vtable_Shape;
        Shape_DTOR((Shape*)_this);
    }
    
/*  void draw() const { */
/*      printf("Circle::draw()  - %d, r:%f\n", m_id, m_radius);*/
/*  }*/
    void Circle_const_draw(Circle* const _this)  { 
        printf("Circle::draw()  - %d, r:%f\n", ((Shape*)_this)->m_id, _this->m_radius);
    }
    
/*  void scale(double f = 2) {*/
/*      printf("Circle::scale(%f)\n", f);*/
/*      m_radius *= f;*/
/*  }*/
    void Circle_scale_double(Circle* const _this, double _f) {
        printf("Circle::scale(%f)\n", _f);
        _this->m_radius *= _f;
    }

/*  double area() const {*/
/*      return m_radius * m_radius * 3.1415;    */
/*  }*/
    double Circle_const_area(Circle* const _this) {
        return _this->m_radius * _this->m_radius * 3.1415;
    }

/*  double radius() const { */
/*      printf("Circle::draw()  - %d, r:%f\n", m_id, m_radius);*/
/*      return m_radius;*/
/*  }*/
    double Circle_const_radius(Circle* const _this)  {
        return _this->m_radius;
    }


/*class Rectangle: public Shape {*/
/*public:*/
/*private:*/
/*  int m_a, m_b;*/
/*};*/
typedef struct Rectangle{
    Shape m_shape;
    int m_a;
    int m_b;
} Rectangle;

void   Rectangle_DTOR(Rectangle* const _this);
void   Rectangle_scale_double(Rectangle* const _this, double _f);
void   Rectangle_const_draw(Rectangle* const _this);
void   Rectangle_const_draw_Color_ColorEnum(Rectangle* const _this, Color_ColorEnum _c);
double Rectangle_const_area(Rectangle* const _this);

void (*vtable_Rectangle[])(void*) = { (void (*)(void*))Rectangle_DTOR,
                                      (void (*)(void*))Rectangle_scale_double,
                                      (void (*)(void*))Rectangle_const_draw,
                                      (void (*)(void*))Rectangle_const_draw_Color_ColorEnum,
                                      (void (*)(void*))Rectangle_const_area  };

/*  Rectangle() : m_a(1), m_b(1) { */
/*      printf("Rectangle::Rectangle() - %d, [%d, %d]\n", m_id, m_a, m_b);*/
/*  }*/
    void Rectangle_CTOR(Rectangle* const _this) {
        Shape_CTOR((Shape*)_this);
        *((void (***)(void*))_this) = vtable_Rectangle;
                
        _this->m_a = 1;
        _this->m_b = 1;
        printf("Rectangle::Rectangle() - %d, [%d, %d]\n", ((Shape*)_this)->m_id, _this->m_a, _this->m_b);
    }

/*  Rectangle(int a) : m_a(a), m_b(a) { */
/*      printf("Rectangle::Rectangle(int) - %d, [%d, %d]\n", m_id, m_a, m_b);*/
/*  }*/
    void Rectangle_CTOR_int(Rectangle* const _this, int _a)
    { 
        Shape_CTOR((Shape*)_this);
        *((void (***)(void*))_this) = vtable_Rectangle;
        
        _this->m_a = _a;
        _this->m_b = _a;
        printf("Rectangle::Rectangle(int) - %d, [%d, %d]\n", ((Shape*)_this)->m_id, _this->m_a, _this->m_b);
    }

/*  Rectangle(int a, int b) : m_a(a), m_b(b) { */
/*      printf("Rectangle::Rectangle(int, int) - %d, [%d, %d]\n", m_id, m_a, m_b);*/
/*  }*/
    void Rectangle_CTOR_int_int(Rectangle* const _this, int _a, int _b)
    {
        Shape_CTOR((Shape*)_this);
        *((void (***)(void*))_this) = vtable_Rectangle;
        
        _this->m_a = _a;
        _this->m_b = _b;
        printf("Rectangle::Rectangle(int, int) - %d, [%d, %d]\n", ((Shape*)_this)->m_id, _this->m_a, _this->m_b);
    }

/*  Rectangle(const Rectangle &other ) */
/*  : m_a(other.m_a), m_b(other.m_b), Shape(other) { */
/*      printf("Rectangle::Rectangle(Rectangle&) - %d, a:%d/%d\n", m_id, m_a, m_b);*/
/*  }*/
    void Rectangle_CTOR_const_Rectangle_ref(Rectangle* const _this, const Rectangle* const _other)
    { 
        Shape_CTOR_const_Shape_ref((Shape*)_this, (const Shape* const)_other);
        _this->m_a = _other->m_a;
        _this->m_b = _other->m_b;
        printf("Rectangle::Rectangle(Rectangle&) - %d, a:%d/%d\n", ((Shape*)_this)->m_id, _this->m_a, _this->m_b);
    }

/*  ~Rectangle() { */
/*      printf("Rectangle::~Rectangle() - %d, [%d, %d]\n", m_id, m_a, m_b);*/
/*  }*/
    void Rectangle_DTOR(Rectangle* const _this) { 
        printf("Rectangle::~Rectangle() - %d, [%d, %d]\n", ((Shape*)_this)->m_id, _this->m_a, _this->m_b);
        
        *((void (***)(void*))_this) = vtable_Shape;
        Shape_DTOR((Shape*)_this);
    }

/*  void draw() const { */
/*      printf("Rectangle::draw()  - %d, [%d, %d]\n", m_id, m_a, m_b);*/
/*  }*/
    void Rectangle_const_draw(Rectangle* const _this) { 
        printf("Rectangle::draw()  - %d, [%d, %d]\n", ((Shape*)_this)->m_id, _this->m_a, _this->m_b);
    }

/*    void draw(Color::ColorEnum c) const {*/
/*      printf("Rectangle::draw(%d)  - %d, [%d, %d]\n", c, m_id, m_a, m_b);*/
/*  }*/
    void Rectangle_const_draw_Color_ColorEnum(Rectangle* const _this, Color_ColorEnum _c)  {
        printf("Rectangle::draw(%d)  - %d, [%d, %d]\n", _c, ((Shape*)_this)->m_id, _this->m_a, _this->m_b);
    }

/*  void scale(double f = 4){*/
/*      printf("Rectangle::scale(%f)\n", f);*/
/*      m_a *= f;*/
/*      m_b *= f;*/
/*  }*/
    void Rectangle_scale_double(Rectangle* const _this, double _f){
        printf("Rectangle::scale(%f)\n", _f);
        _this->m_a *= _f;
        _this->m_b *= _f;
    }
    
/*  double area() const {*/
/*      return m_a * m_b;*/
/*  }*/
    double Rectangle_const_area(Rectangle* const _this)  {
        return _this->m_a * _this->m_b;
    }


/*void report(const Shape& s) {*/
/*  puts("-----report-----");*/
/*  s.draw(); */
/*  Shape::printInventory();*/
/*  puts("-----report-----");*/
/*}*/
void report_const_Shape_ref(const Shape* const _s) {
    puts("-----report-----");
    ((*((void (***)(const Shape* const))_s))[2])(_s);
    Shape_static_printInventory();
    puts("-----report-----");
}

/*inline void draw(Shape& obj) { */
/*  puts("-----draw(Shape&)-----");*/
/*  obj.scale();*/
/*  obj.draw();*/
/*  puts("-----draw(Shape&)-----");*/
/*}*/
void draw_Shape_ref(Shape* const _obj) { 
    puts("-----draw(Shape&)-----");
    
    // default value is of static type --> Shape and cannot be changed!!!! --> 1
    ((*((void (***)(Shape* const, double))_obj))[1])(_obj, 1);  
    ((*((void (***)(Shape* const))_obj))[2])(_obj);
    puts("-----draw(Shape&)-----");
}


    int draw_Circle_constructed = 0;
    Circle draw_Circle_unit;

// void draw(Circle c) { 
//     puts("-----draw(Circle)-----");

//     static Circle unit(1);
    
//     unit.draw();
//     unit.scale(3);
//     c.draw(); 
//     puts("-----draw(Circle)-----");
// }
void draw_Circle(const Circle* const _c) {
    Circle tmpCircle;
    Circle_CTOR_const_Circle_ref(&tmpCircle, _c);

    puts("-----draw(Circle)-----");

/*    static int constructed = 0;*/
/*    static Circle unit;*/
    if (!draw_Circle_constructed)
    {
        Circle_CTOR_double(&draw_Circle_unit, 1);
        draw_Circle_constructed = 1;
    }

    Circle_const_draw(&draw_Circle_unit);
    Circle_scale_double(&draw_Circle_unit, 3);
    Circle_const_draw(&tmpCircle);
    puts("-----draw(Circle)-----");
    
    Circle_DTOR(&tmpCircle);
}

// void doObjArray(){
//     Shape objects[] = {
//         Circle(),
//         Rectangle(4),
//         Circle(9)
//     };

//     for(int i = 0; i < 3; ++i) 
//         objects[i].draw();
// }
void doObjArray(){
    Shape objects[3];
    
    union Shape {
        Circle    circle;
        Rectangle rectangle;
    };
    
    union Shape tmp;
    
    Circle_CTOR(&tmp.circle);
    Shape_CTOR_const_Shape_ref(&objects[0], (const Shape* const)&tmp.circle);       // slicing
    Circle_DTOR(&tmp.circle);

    Rectangle_CTOR_int(&tmp.rectangle, 4);
    Shape_CTOR_const_Shape_ref(&objects[1], (const Shape* const)&tmp.rectangle);    // slicing
    Rectangle_DTOR(&tmp.rectangle);
    
    Circle_CTOR_double(&tmp.circle, 9);
    Shape_CTOR_const_Shape_ref(&objects[2], (const Shape* const)&tmp.circle);       // slicing
    Circle_DTOR(&tmp.circle);

    int i;
    for(i = 0; i < 3; ++i)
        Shape_const_draw(objects + i);

    Shape_DTOR(&objects[2]);
    Shape_DTOR(&objects[1]);
    Shape_DTOR(&objects[0]);
}

void disappear() {
    puts("-----disappear-----");

    Circle defaultCircle();

    puts("-----disappear-----");
}

/*template <class T>*/
/*double diffWhenDoubled(T& shape){*/
/*    double a0 = shape.area();*/
/*    shape.scale(2);*/
/*    double a1 = shape.area();*/
/*    return a1 - a0;*/
/*}*/
double diffWhenDoubled_Shape(Shape* const _shape){
    double a0 = ((*((double (***)(Shape* const))_shape))[4])(_shape);   // double Shape_const_area(Shape* const _this);
    ((*((double (***)(Shape* const, double))_shape))[1])(_shape, 2);    // void   Shape_scale_double(Shape* const _this, double _f);
    double a1 = ((*((double (***)(Shape* const))_shape))[4])(_shape);   // double Shape_const_area(Shape* const _this);
    return a1 - a0;
}
double diffWhenDoubled_Circle(Circle* const _circle){
    double a0 = ((*((double (***)(Circle* const))_circle))[4])(_circle);   // double Circle_const_area(Circle* const _this);
    ((*((void (***)(Circle* const, double))_circle))[1])(_circle, 2);      // void   Circle_scale_double(Circle* const _this, double _f);
    double a1 = ((*((double (***)(Circle* const))_circle))[4])(_circle);   // double Circle_const_area(Circle* const _this);
    return a1 - a0;
}

void doPointerArray(){
    puts("-----doPointerArray-----");
    // Shape *array[] =  {
    //     new Circle(),
    //     new Rectangle(3),
    //     new Circle(4)
    // };
    Shape* array[3];

    array[0] = malloc(sizeof(Circle));
    Circle_CTOR((Circle*)array[0]);
    
    array[1] = malloc(sizeof(Rectangle));
    Rectangle_CTOR_int((Rectangle*)array[1], 3);
    
    array[2] = malloc(sizeof(Circle));
    Circle_CTOR_double((Circle*)array[2], 4);
    

    // for(int i = 0; i < 3; ++i){ 
    //     array[i]->scale();
    //     array[i]->draw();
    // }
    int i;
    for(i = 0; i < 3; ++i){
        ((*((void (***)(Shape* const, double))array[i]))[1])(array[i], 1);  // void Shape_scale_double(Shape* const, double);
        ((*((void (***)(Shape* const))array[i]))[2])(array[i]);             // void Shape_const_draw(const Shape* const);
    }

    printf("area: %f\n", diffWhenDoubled_Shape(array[2]));

    // for(int i = 0; i < 3; ++i) { 
    //     delete array[i]; 
    //     array[i] = 0; 
    // }
    for(i = 0; i < 3; ++i) { 
        ((*((void (***)(Shape* const))array[i]))[0])(array[i]);  // void Shape_DTOR(Shape* const);
        free(array[i]);
        array[i] = 0;
    }

    puts("-----doPointerArray-----");
}

/*void dispose(Rectangle* p){*/
/*  delete[] p;*/
/*}*/
void dispose(Rectangle* _p)
{
    _p = (Rectangle*)((char*)_p - sizeof(size_t));
    size_t noe = *(size_t*)_p;
    _p = (Rectangle*)((char*)_p + sizeof(size_t));
    
    int i;
    for (i = noe - 1; i >= 0; --i)
    {
        Rectangle_DTOR(&_p[i]);
    }

    free((char*)_p - sizeof(size_t));
}

/*class Empty {*/
/*public:*/
/*    Empty(int id = 0) { printf("Empty::Empty(%d)\n", id); }*/
/*   ~Empty() { puts("Empty::~Empty()");} */
/*};*/
typedef struct Empty {
    char m_emptyChar;
} Empty;

void Empty_CTOR_int(Empty* const _this, int _id)
{
    printf("Empty::Empty(%d)\n", _id);
}

void Empty_DTOR(Empty* const _this) { puts("Empty::~Empty()");}


/*class EmptyEmpty  : public Empty{*/
/*  int m_i;*/
/*public:*/
/*  EmptyEmpty(int id) : m_i(id){*/
/*       std::printf("EmptyEmpty::EmptyEmpty(%d)\n", m_i); */
/*  }*/
/*};*/
typedef struct EmptyEmpty {
    int m_i;
} EmptyEmpty;

void EmptyEmpty_CTOR_int(EmptyEmpty* const _this, int _id){
    Empty_CTOR_int((Empty* const)_this, 0);
    _this->m_i = _id;
    printf("EmptyEmpty::EmptyEmpty(%d)\n", _this->m_i);
}

void EmptyEmpty_DTOR(EmptyEmpty* const _this){
    Empty_DTOR((Empty* const)_this);
}

/*class EmptyBag {*/
/*    Empty e1;*/
/*    Empty e2;*/
/*    EmptyEmpty ee;*/
/*public: */
/*    EmptyBag() : e2(2), e1(1), ee(2) {*/
/*        puts("EmptyBag::EmptyBag()");*/
/*    }*/
/*    ~EmptyBag(){*/
/*        puts("EmptyBag::~EmptyBag");*/
/*    }   */
/*};*/
typedef struct EmptyBag {
    Empty e1;
    Empty e2;
    EmptyEmpty ee;
} EmptyBag;

void EmptyBag_CTOR(EmptyBag* const _this)
{
    Empty_CTOR_int(&_this->e1, 1);
    Empty_CTOR_int(&_this->e2, 2);
    EmptyEmpty_CTOR_int(&_this->ee, 2);

    puts("EmptyBag::EmptyBag()");
}

void EmptyBag_DTOR(EmptyBag* const _this){
    puts("EmptyBag::~EmptyBag");

    EmptyEmpty_DTOR(&_this->ee);
    Empty_DTOR(&_this->e2);
    Empty_DTOR(&_this->e1);
}   


int main(int argc, char **argv, char **envp)
{   
    Circle c;
    Rectangle s;
    Circle c2;
    Circle olympics[5];
    int i;
    EmptyBag eb;
    printf("---------------Start----------------\n");
    Circle_CTOR(&c);
    Rectangle_CTOR_int(&s, 4);

    printf("0.-------------------------------\n");      
    draw_Circle(&c);

    printf("+..............\n");        
    draw_Circle(&c);

    printf("+..............\n");        
    draw_Shape_ref((Shape* const)&s);

    printf("+..............\n");        
    report_const_Shape_ref((const Shape* const)&c);

    printf("1.-------------------------------\n");  
    
    doPointerArray();

    printf("2.-------------------------------\n");

    doObjArray();

    printf("3.-------------------------------\n");
    
/*    Shape::printInventory();*/
/*    Circle c2 = c;*/
/*    c2.printInventory();*/
    Shape_static_printInventory();
    Circle_CTOR_const_Circle_ref(&c2, &c);
    Shape_static_printInventory();

    printf("4.-------------------------------\n");

/*    Circle olympics[5];*/
/*    printf("olympic diff %f\n", diffWhenDoubled(olympics[1]));*/
    for(i = 0; i < 5; ++i){
        Circle_CTOR(&olympics[i]);
    }

    printf("olympic diff %f\n", diffWhenDoubled_Circle(&olympics[1]));

    printf("5.-------------------------------\n");

/*    Rectangle *fourRectangles = new Rectangle[4];*/
/*    dispose(fourRectangles);*/
    Rectangle *fourRectangles = malloc(sizeof(size_t) + 4 * sizeof(Rectangle));
    *(size_t*)fourRectangles = 4;
    fourRectangles = (Rectangle*)((char*)fourRectangles + sizeof(size_t));
    
    for (i = 0; i < 4; ++i)
    {
        Rectangle_CTOR(&fourRectangles[i]);
    }
    
    dispose(fourRectangles);

    printf("6.-------------------------------\n");
    EmptyBag_CTOR(&eb);
    printf("Empty things are: %zu %zu %zu", sizeof(Empty), sizeof(EmptyEmpty), sizeof(EmptyBag) );
    
    printf("7.-------------------------------\n");
    disappear();

    printf("---------------END----------------\n");


    EmptyBag_DTOR(&eb);
    for(i = 4; i >= 0; --i){
        Circle_DTOR(&olympics[i]);
    }
    Circle_DTOR(&c2);
    Rectangle_DTOR(&s);
    Circle_DTOR(&c);
    Circle_DTOR(&draw_Circle_unit);

    return 0;
}

