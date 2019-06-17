#include "main.h"

#ifndef BALL_H
#define BALL_H

class Bubbles {
    public:
    Bubbles() {}
    Bubbles(float x, float y,float radius,float speedx, color_t color);
    glm::vec3 position;
    int dam;
    double radius,speedx,speedy,width;
    void draw(glm::mat4 VP);
    void coordinates_generator(GLfloat arr[]);
    void tick();
private:
    VAO *object;
};

class Ball {
public:
    Ball() {}
    Ball(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void tick();
    std::vector <Bubbles> bubs;
    double speedx,speedy;
    double height,jump,attract,width;
    int score,health;
private:
    VAO *object;
};



class Platform{
public:
    Platform() {}
    Platform(float x, float y, color_t color);
    glm::vec3 position;
    void draw(glm::mat4 VP);
private:
    VAO *object;
};

class Coin{
public:
    Coin() {}
    Coin(float x, float y,float radius, color_t color);
    glm::vec3 position;
    int pts;
    double radius,rotation;
    void draw(glm::mat4 VP);
    void coordinates_generator(GLfloat arr[]);
private:
    VAO *object;
};

class Enemy1{
public:
    Enemy1() {}
    Enemy1(float x,float y,float rot, color_t color);
    glm::vec3 position;
    float rotation;
    int health;
    double width,height;
    void draw(glm::mat4 VP);
    Coin c1,c2;
private:
    VAO *object;
};

class Enemy2{
public:
    Enemy2() {}
    Enemy2(float x,float y, color_t color);
    glm::vec3 position;
    float rotation;
    double width,height;
    double speedy;
    int health;
    void draw(glm::mat4 VP);
    void tick();
    Coin c1,c2;
private:
    VAO *object;
};

class Magnet{
public:
    Magnet() {}
    Magnet(float x,float y, color_t color);
    glm::vec3 position;
    float rotation;
    double width,height;
    void draw(glm::mat4 VP);
    private:
    VAO *object;
};
class Boomerang{
public:
    Boomerang() {}
    Boomerang(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void tick();
    double speedx,speedy,radius,a,x1,y1,height,width;
    void draw(glm::mat4 VP);
private:
    VAO *object; 
};

class Special{
public:
    Special() {}
    Special(float x, float y, color_t color,int type);
    glm::vec3 position;
    float rotation;
    void tick();
    int pts,health;
    double speedx,speedy,height,width,a;
    void draw(glm::mat4 VP);
private:
    VAO *object; 
};

#endif // BALL_H