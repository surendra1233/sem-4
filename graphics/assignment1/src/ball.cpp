#include "ball.h"
#include "main.h"



Ball::Ball(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->height = y;
    this->jump  = 0;
    this->health  = 3;
    this->rotation = 0;
    this->speedx = 0;
    this->speedy = 0;
    this->score = 0;
    this->width = 0.8;
    this->attract = 0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat vertex_buffer_data[] = {
        -0.4,0.4,0.0,
        -0.2,0.4,0.0,
        -0.2,-0.3,0.0,
        -0.4,-0.3,0.0,
        -0.2,-0.3,0.0,
        -0.4,0.4,0.0,

        
        -0.1,0.4,0.0,
        0.4,0.4,0.0,
        0.4,0.2,0.0,
        0.4,0.2,0.0,
        -0.1,0.4,0.0,
        -0.1,0.2,0.0,
        
        0.1,0.2,0.0,
        0.2,0.2,0.0,
        0.2,0.1,0.0,
        0.2,0.1,0.0,
        0.1,0.2,0.0,
        0.1,0.1,0.0,
        
        -0.1,0.1,0.0,
        0.4,0.1,0.0,
        0.4,-0.2,0.0,
        0.4,-0.2,0.0,
        -0.1,0.1,0.0,
        -0.1,-0.2,0.0,

        -0.05,-0.2,0.0,
        0.1,-0.2,0.0,
        -0.05,-0.4,0.0,
        -0.05,-0.4,0.0,
        0.1,-0.2,0.0,
        0.1,-0.4,0.0,

        0.2,-0.2,0.0,
        0.35,-0.2,0.0,
        0.2,-0.4,0.0,
        0.2,-0.4,0.0,
        0.35,-0.2,0.0,
        0.35,-0.4,0.0,

        /*0.5,0.5,0.0,
        0.5,-0.5,0.0,
        -0.5,0.5,0.0,
        -0.5,0.5,0.0,
        -0.5,-0.5,0.0,
        0.5,-0.5,0,*/
        }; 
    // points_generator(this->radius,vertex_buffer_data);
    this->object = create3DObject(GL_TRIANGLES, 36, vertex_buffer_data, color, GL_FILL);
}

void Ball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate );//* rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

/*void Ball::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}*/

void Ball::tick() {
    
    if(this->speedx>0.0){
        this->position.x += 0.1;
        this->speedx -= 0.1;
    }
    else if(this->speedx<0.0){
        this->position.x -= 0.1;
        this->speedx += 0.1;
    }
    else{
        this->position.x += scr_speed;
    }
    if(fabs(this->speedx)<0.1)
        this->speedx = 0;

    if(this->jump==1){
        this->speedy = 0;
        if(this->position.y<3.5)
           this->position.y += 0.1;
        // std::cout << this->jump << " 1\n";
    }

    this->position.y += this->attract*0.1;
    this->speedy -= this->attract*0.01;

    if(this->jump==0){
        if(this->position.y!=this->height)
            this->speedy += 0.01;
        
        if(this->position.y<=this->height){
            this->speedy = 0;
            this->position.y = this->height;
        }

        if(this->speedy>0){
            this->position.y -= this->speedy;
        }
    }

        // std::cout << this->jump << " 2\n";
}

Bubbles::Bubbles(float x,float y,float radius,float speedx,color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->radius = radius;
    this->width = 2*radius;
    this->dam = 20;
    this->speedx = speedx + 1.3;
    this->speedy =  0.6;
    GLfloat vertex_buffer_data[200];
    coordinates_generator(vertex_buffer_data);
    this->object = create3DObject(GL_TRIANGLES, 60, vertex_buffer_data, color, GL_FILL);
}


//bubbles
void Bubbles::coordinates_generator(GLfloat arr[]){
    double r = this->radius;
	int i,n=20;
    //since a n-sided polygon will have n triangles => n*3 vertices => 3*(n*3) co-ordinates
    for(i=0;i<n;i++){
		arr[9*i] = r*cos(((2*3.14*i)/n));
		arr[9*i+1] = r*sin(((2*3.14*i)/n));
		arr[9*i+2] = 0;
		
		arr[9*i+3] = r*cos(((2*3.14*(i+1))/n));
		arr[9*i+4] = r*sin(((2*3.14*(i+1))/n));
		arr[9*i+5] = 0;

		arr[9*i+6] = 0;
		arr[9*i+7] = 0;
		arr[9*i+8] = 0;
	}
	return;
}

void Bubbles::draw(glm::mat4 VP){

    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Bubbles::tick(){
    if(this->speedx>0){
        this->position.x += 0.1;
        this->speedx -=0.1;
    }
    else{
        this->position.x +=scr_speed;
    }
    if(this->speedy>0){
        this->position.y += 0.05;
        this->speedy -=0.05;
    }
    if(speedy<=0){
        this->position.y += this->speedy;        
        this->speedy -= 0.01;
    }
}

Platform::Platform(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat vertex_buffer_data[] = {
        20,-3.5,0.0,
        20,-5,0,
        -20,-3.5,0,
        -20,-3.5,0,
        -20,-5,0,
        20,-5,0,
        };
    // points_generator(this->radius,vertex_buffer_data);
    this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, color, GL_FILL);
}


void Platform::draw(glm::mat4 VP){

    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}


Coin::Coin(float x,float y,float radius,color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->radius = radius;
    if(color.r==COLOR_GOLD.r && color.g ==COLOR_GOLD.g && color.b==COLOR_GOLD.b){
        this->pts = 5;
    }
    else{
        this->pts = 1;
    }
    GLfloat vertex_buffer_data[200];
    coordinates_generator(vertex_buffer_data);
    this->object = create3DObject(GL_TRIANGLES, 60, vertex_buffer_data, color, GL_FILL);
}

void Coin::coordinates_generator(GLfloat arr[]){
    double r = this->radius;
	int i,n=20;
    //since a n-sided polygon will have n triangles => n*3 vertices => 3*(n*3) co-ordinates
    for(i=0;i<n;i++){
		arr[9*i] = r*cos(((2*3.14*i)/n));
		arr[9*i+1] = r*sin(((2*3.14*i)/n));
		arr[9*i+2] = 0;
		
		arr[9*i+3] = r*cos(((2*3.14*(i+1))/n));
		arr[9*i+4] = r*sin(((2*3.14*(i+1))/n));
		arr[9*i+5] = 0;

		arr[9*i+6] = 0;
		arr[9*i+7] = 0;
		arr[9*i+8] = 0;
	}
	return;
}

void Coin::draw(glm::mat4 VP){
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate );//* rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

// fire Lines
Enemy1::Enemy1(float x, float y,float rot, color_t color){
    this->position = glm::vec3(x, y, 0);
    this->rotation = rot;
    this->height = 0.2;
    this->width = 3;
    this->health = 100;
    GLfloat vertex_buffer_data[] = {
        1.2,0.1,0,
        -1.2,0.1,0,
        1.2,-0.1,0,
        -1.2,0.1,0,
        1.2,-0.1,0,
        -1.2,-0.1,0,
    };

    this->c1 = Coin(x+(this->width/2-0.3)*cos(this->rotation * M_PI / 180.0f),y + ((this->width-0.6)/2)*sin(this->rotation * M_PI / 180.0f),0.3,COLOR_END);
    this->c2 = Coin(x-(this->width/2-0.3)*cos(this->rotation * M_PI / 180.0f),y - ((this->width-0.6)/2)*sin(this->rotation * M_PI / 180.0f),0.3,COLOR_END);
    this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, color, GL_FILL);    
}


void Enemy1::draw(glm::mat4 VP) {
    this->c1.draw(VP);
    this->c2.draw(VP);
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);

}

Enemy2::Enemy2(float x, float y, color_t color){
    this->position = glm::vec3(x, y, 0);
    this->height = 0.2;
    this->health = 100;
    this->width = 3.0;
    this->speedy = 1;
    GLfloat vertex_buffer_data[] = {
        1.2,0.1,0,
        -1.2,0.1,0,
        1.2,-0.1,0,
        -1.2,0.1,0,
        1.2,-0.1,0,
        -1.2,-0.1,0,
    };

    this->c1 = Coin(x+(this->width/2-0.3),y,0.3,COLOR_END);
    this->c2 = Coin(x-(this->width/2-0.3),y,0.3,COLOR_END);
    this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, color, GL_FILL);    
}
void Enemy2::draw(glm::mat4 VP) {
    this->c1.draw(VP);
    this->c2.draw(VP);
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate );//* rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Enemy2::tick(){

    if(speedy>0 && this->position.y<=3.6){
        this->position.y+=0.1;
        this->c1.position.y+=0.1;
        this->c2.position.y+=0.1;
    }
    else if(this->speedy>0){
        this->speedy = 0;
    }
    
    if(this->speedy==0 && this->position.y>=-3){
        this->position.y-=0.1;
        this->c1.position.y-=0.1;
        this->c2.position.y-=0.1;
    }
    else{
        this->speedy = 1;
    }

}

Magnet::Magnet(float x,float y,color_t color){
    this->position = glm::vec3(x, y, 0);
    this->height = 1.5;
    this->width = 1.5;
    GLfloat vertex_buffer_data[] = {
        0.75,0.75,0,
        0.75,-0.55,0,
        0.65,0.75,0,
        0.75,-0.55,0,
        0.65,0.75,0,
        0.65,-0.55,0,
        -0.75,0.75,0,
        -0.75,-0.55,0,
        -0.65,0.75,0,
        -0.75,-0.55,0,
        -0.65,0.75,0,
        -0.65,-0.55,0,
        -0.75,-0.55,0,
        0.75,-0.55,0,
        0,-0.75,0,
    };
    this->object = create3DObject(GL_TRIANGLES, 15, vertex_buffer_data, color, GL_FILL);
}       

void Magnet::draw(glm::mat4 VP){

    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

Boomerang::Boomerang(float x,float y,color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->x1 = 14;
    this->y1 =  1;
    this->height = 0.2;
    this->width = 0.2;
    this->radius = 0.2;
    this->speedx = 14;
    this->speedy = 1;
    this->rotation +=3;
    this->a = 1;
    GLfloat vertex_buffer_data[] ={
        (this->width)*cos(45* M_PI / 180.0f),(this->width)*cos(45* M_PI / 180.0f),0,
        0,(this->width/2)*cos(45* M_PI / 180.0f),0,
        (this->width/2)*cos(45* M_PI / 180.0f),0,0,
        -(this->width)*cos(45* M_PI / 180.0f),(this->width)*cos(45* M_PI / 180.0f),0,
        0,(this->width/2)*cos(45* M_PI / 180.0f),0,
        -(this->width/2)*cos(45* M_PI / 180.0f),0,0,
        (this->width)*cos(45* M_PI / 180.0f),-(this->width)*cos(45* M_PI / 180.0f),0,
        0,-(this->width/2)*cos(45* M_PI / 180.0f),0,
        (this->width/2)*cos(45* M_PI / 180.0f),0,0,
        -(this->width)*cos(45* M_PI / 180.0f),-(this->width)*cos(45* M_PI / 180.0f),0,
        0,-(this->width/2)*cos(45* M_PI / 180.0f),0,
        -(this->width/2)*cos(45* M_PI / 180.0f),0,0,

        0,(this->width/2)*cos(45* M_PI / 180.0f),0,
        (this->width/2)*cos(45* M_PI / 180.0f),0,0,
        0,0,0,
        0,(this->width/2)*cos(45* M_PI / 180.0f),0,
        -(this->width/2)*cos(45* M_PI / 180.0f),0,0,
        0,0,0,
        0,-(this->width/2)*cos(45* M_PI / 180.0f),0,
        (this->width/2)*cos(45* M_PI / 180.0f),0,0,
        0,0,0,
        0,-(this->width/2)*cos(45* M_PI / 180.0f),0,
        -(this->width/2)*cos(45* M_PI / 180.0f),0,0,
        0,0,0,
    };
    this->object = create3DObject(GL_TRIANGLES, 24, vertex_buffer_data, color, GL_FILL);
}

void Boomerang::draw(glm::mat4 VP) {
    this->rotation +=10;
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}


void Boomerang::tick(){
    
    if(this->speedx>0)
        this->position.x -= a*0.07;
    this->speedx-=a*0.07;
    if(this->speedy>0)
        this->position.y -= a*0.05;
    this->speedy -= a*0.05;
    
    if(fabs(this->speedx)<0.1){
        a*=-1;
    }
    
    if(this->speedx == this->x1){
        a*=-1;
        this->speedy = this->y1;
    }
}


Special::Special(float x, float y, color_t color,int type){
    this->pts = type*(100);
    this->health = type;
    this->position = glm::vec3(x, y, 0);
    this->height = 1.0;
    this->width = 1.0;
    this->speedx = -0.02;
    this->speedy = 0.2;
    this->a = 0.001;
    GLfloat vertex_buffer_data[] ={
        -0.5,-0.5,0,
        -0.5,0.5,0,
        0.5,0.5,0,
        -0.5,-0.5,0,
        0.5,0.5,0,
        0.5,-0.5,0,
    };
    this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, color, GL_FILL);

}

void Special::draw(glm::mat4 VP) {

    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Special::tick(){

    this->position.x += this->speedx;    
    this->position.y += this->speedy - this->a;
    this->speedy -= this->a;
    
    if(this->position.y>3.0){
        this->speedy *= -1;
        this->position.y = 2.95;
    }
    else if(this->position.y < -3.0){
        this->position.y = -2.95;
        this->speedy *= -1;
    }
}