#include "main.h"

#ifndef BALL_H
#define BALL_H
class Missiles {
    public:
    Missiles() {}
    Missiles(float x, float y,float z,float rotation,glm::vec3 pos,bool play, color_t color);
    glm::vec3 position,cosin;
    int dam;
    bool play;
    double radius,speedx,speedy,speedz,rotation,rotationy,width;
    void draw(glm::mat4 VP);
    void coordinates_generator(GLfloat arr[]);
    void tick();
private:
    VAO *object;
};

class Bombs {
    public:
    Bombs() {}
    Bombs(float x, float y,float z,float rotation, color_t color);
    glm::vec3 position;
    int dam;
    double radius,speedx,speedy,speedz,rotation,width;
    void draw(glm::mat4 VP);
    void coordinates_generator(GLfloat arr[]);
    void tick();
private:
    VAO *object;
};

class Ball {
public:
    Ball() {}
    Ball(float x, float y, float z, color_t color);
    glm::vec3 position,check_position;
    int rotationx,rotationy,rotationz,rotation,score;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void coordinates_generator(GLfloat arr[]);
    std::vector <Missiles> bulls;
    std::vector <Bombs> bombs;
    void tick();
    // check_point checks[40];
    double radius,forward;
    int speedx,speedy,speedz,left,ind;
private:
    VAO *object, *object1, *object2;
};

class Enemy2{
public:
    Enemy2() {}
    Enemy2(float x,float y,float z, color_t color);
    glm::vec3 position;
    int del;
    std::vector <Missiles> bulls;
    void coordinates_generator(GLfloat arr[]);
    double width,height,radius;
    void draw(glm::mat4 VP);
private:
    VAO *object;
};
class Platform{
public:
    Platform() {}
    Platform(color_t color);
    glm::vec3 position;
    void draw(glm::mat4 VP);
private:
    VAO *object;
};

class Mountain{
public:
    Mountain() {}
    Mountain(float x, float y, float z,color_t color);
    void coordinates_generator(GLfloat arr[]);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    double radius,height;
private:
    VAO *object;
};

class Island{
public:
    Island() {}
    Island(float x, bool mountain, float z,color_t color);
    void coordinates_generator(GLfloat arr[]);
    glm::vec3 position;
    Mountain mount;
    Enemy2 ene;
    void draw(glm::mat4 VP);
    double radius,height;
    bool mountain;
private:
    VAO *object;
};

class Rings{
public:
    Rings() {}
    Rings(float x, float y, float z,color_t color);
    void coordinates_generator(GLfloat arr[]);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    double radius;
    int rotationy,rotationz;
private:
    VAO *object;
};

class Dashboard{
    public:
    Dashboard() {}
    Dashboard(color_t color);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    double speed,fuel,height;
    int rotation;
private:
    VAO *object3,*object,*object1,*object2,*object4,*object5;
};

class Enemy1{
public:
    Enemy1() {}
    Enemy1(float x,float y,float z, color_t color);
    glm::vec3 position;
    int health;
    void coordinates_generator(GLfloat arr[]);
    double width,height,radius,rotation;
    void tick();
    void draw(glm::mat4 VP);
private:
    VAO *object,*object1;
};

class Fuel{
public:
    Fuel() {}
    Fuel(float x,float y,float z, color_t color);
    glm::vec3 position;
    double width,height,radius;
    void draw(glm::mat4 VP);
private:
    VAO *object;
};

#endif // BALL_H
