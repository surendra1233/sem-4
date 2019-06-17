#include "ball.h"
#include "main.h"

Ball::Ball(float x, float y,float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotationx = 0;
    this->rotationy = 0;
    this->rotationz = 0;
    this->rotation = 0;
    this->radius = 0.2;
    this->ind =0;
    this->speedx = 0;
    this->speedy = 0;
    this->speedz = 0;
    this->score = 0;
    // this->axes = 
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat vertex_buffer_data[800];
    GLfloat vertex_buffer_data1[] = {
        0,0,0.3,
        0,0,0,
        -1,0,-0.1,
        -1,0,-0.1,
        -1,0,0.1,
        0,0,0.3,
        0,0,0.3,
        0,0,0,
        1,0,-0.1,
        1,0,-0.1,
        1,0,0.1,
        0,0,0.3,

        0,0.2,0,
        0,-0.2,0,
        -1,0,0,

        0,0.2,0,
        0,-0.2,0,
        1,0,0,

        0,0,-0.5,
        0,0,-0.8,
        -0.5,0,-0.9,
        -0.5,0,-0.9,
        -0.5,0,-0.7,
        0,0,-0.5,
        0,0,-0.5,
        0,0,-0.8,
        0.5,0,-0.9,
        0.5,0,-0.9,
        0.5,0,-0.7,
        0,0,-0.5,
        
        0,0.2,-0.65,
        0,-0.2,-0.65,
        0.5,0,-0.65,

        0,0.2,-0.65,
        0,-0.2,-0.65,
        -0.5,0,-0.65,

        0,0,-0.8,
        0,0,-1,
        0,0.5,-1.1,

    }; 
     GLfloat vertex_buffer_data2[] = {
        1,2.0,0,
        1,-2.0,0,
        -1,-2,0,
        1,2.0,0,
        -1,2,0,
        -1,-2,0,
        -1,-2,0,
        1,-2.0,0,
        0,-3,0,
    };
    this->object1 = create3DObject(GL_TRIANGLES, 39, vertex_buffer_data1, COLOR_BLACK, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 9, vertex_buffer_data2, COLOR_RED, GL_FILL);
    this->coordinates_generator(vertex_buffer_data);
    this->object = create3DObject(GL_TRIANGLES, 20*12, vertex_buffer_data, COLOR_SPECIAL, GL_FILL);

}

void Ball::coordinates_generator(GLfloat arr[]){
    double r = this->radius;
	int i,n=20;
    //since a n-sided polygon will have n triangles => n*3 vertices => 3*(n*3) co-ordinates
    for(i=0;i<n;i++){
		arr[36*i] = r*cos(((2*M_PI*i)/n));
		arr[36*i+1] = r*sin(((2*M_PI*i)/n));
		arr[36*i+2] = -1;
		
		arr[36*i+3] = r*cos(((2*M_PI*(i+1))/n));
		arr[36*i+4] = r*sin(((2*M_PI*(i+1))/n));
		arr[36*i+5] = -1;

        arr[36*i+6] = r*cos(((2*M_PI*i)/n));
		arr[36*i+7] = r*sin(((2*M_PI*i)/n));
		arr[36*i+8] = 0.75;

		arr[36*i+9] = r*cos(((2*M_PI*(i+1))/n));
		arr[36*i+10] = r*sin(((2*M_PI*(i+1))/n));
		arr[36*i+11] = -1;

		arr[36*i+12] = 0;
		arr[36*i+13] = 0;
		arr[36*i+14] = -1;        

		arr[36*i+15] = r*cos(((2*M_PI*i)/n));
		arr[36*i+16] = r*sin(((2*M_PI*i)/n));
		arr[36*i+17] = -1;

		arr[36*i+18] = r*cos(((2*M_PI*i)/n));
		arr[36*i+19] = r*sin(((2*M_PI*i)/n));
		arr[36*i+20] = 0.75;
		
		arr[36*i+21] = r*cos(((2*M_PI*(i+1))/n));
		arr[36*i+22] = r*sin(((2*M_PI*(i+1))/n));
		arr[36*i+23] = 0.75;
		
		arr[36*i+24] = r*cos(((2*M_PI*(i+1))/n));
		arr[36*i+25] = r*sin(((2*M_PI*(i+1))/n));
		arr[36*i+26] = -1;
		
        arr[36*i+27] = r*cos(((2*M_PI*i)/n));
		arr[36*i+28] = r*sin(((2*M_PI*i)/n));
		arr[36*i+29] = 0.75;
		
		arr[36*i+30] = r*cos(((2*M_PI*(i+1))/n));
		arr[36*i+31] = r*sin(((2*M_PI*(i+1))/n));
		arr[36*i+32] = 0.75;

        arr[36*i+33] = 0;
		arr[36*i+34] = 0;
		arr[36*i+35] = 1;

    }
return;
}


void Ball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 rotate = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    
    rotate *= glm::rotate((float) ((float)this->rotationx* M_PI / 180.0f), glm::vec3(0, 1, 0));
    rotate *= glm::rotate((float) ((float)this->rotationy* M_PI / 180.0f), glm::vec3(1, 0, 0));
    rotate *= glm::rotate((float) ((float)this->rotationz* M_PI / 180.0f), glm::vec3(0, 0, 1));
    

    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object1);
   
    translate = glm::translate (this->check_position);    // glTranslatef
    rotate = glm::rotate((float) ((float)this->rotation* M_PI / 180.0f), glm::vec3(0, 1, 0));
    Matrices.model = (translate * rotate);
    MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object2);
}

void Ball::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Ball::tick() {
    if(this->speedz!=0){
        this->rotationz += 3*this->speedz;
    }
    if(this->speedy!=0){
        this->rotationy += this->speedy;
    }
    if(this->speedx!=0){
        this->rotationx += this->speedx;
    }

    if(this->speedy==0 && this->rotationy!=0){
        this->rotationy -= this->rotationy/(abs(this->rotationy));
    }
    if(this->speedz==0 && this->rotationz!=0){
        if(abs(this->rotationz)<=180)
            this->rotationz -= 3*this->rotationz/(abs(this->rotationz));
        else
            this->rotationz += 3*this->rotationz/(abs(this->rotationz));
    }
    this->rotationx %= 360;
    this->rotationy %= 360;
    this->rotationz %= 360;
    this->rotation %= 360;
    if(this->forward==1){
        this->position.z += 0.2*cos(this->rotationx* M_PI / 180.0f)*cos(this->rotationy* M_PI / 180.0f);
        this->position.x += 0.2*sin(this->rotationx* M_PI / 180.0f)*cos(this->rotationy* M_PI / 180.0f);
        this->position.y -= 0.2*sin(this->rotationy* M_PI / 180.0f);
        if(this->position.y>=19.4)
            this->position.y = 19.4;
    }
    
    if(this->forward!=1 && this->speedx==0){
        this->position.z += 0.1*cos(this->rotationx* M_PI / 180.0f)*cos(this->rotationy* M_PI / 180.0f);
        this->position.x += 0.1*sin(this->rotationx* M_PI / 180.0f)*cos(this->rotationy* M_PI / 180.0f);
        if(this->position.y>=19.4)
            this->position.y -= 0.1*sin(this->rotationy* M_PI / 180.0f);
    }

    this->rotation++;
}

Missiles::Missiles(float x,float y,float z,float rotation,glm::vec3 pos,bool play,color_t color) {
    this->position = glm::vec3(x, y, z);
    this->play = play;
    this->radius = 0.2;
    this->width = 2*radius;
    this->rotationy = rotationy;
    this->cosin = pos;
    this->dam = 20;
    this->rotation = rotation;
    this->speedx = 0.3*sin(rotation*M_PI / 180.0f);
    this->speedz = 0.3*cos(rotation*M_PI / 180.0f);
    this->speedy = y;
    if(!play)
        this->speedy = 23;

    GLfloat vertex_buffer_data[800];
    coordinates_generator(vertex_buffer_data);
    this->object = create3DObject(GL_TRIANGLES, 20*9, vertex_buffer_data, color, GL_FILL);
}


//Missiles
void Missiles::coordinates_generator(GLfloat arr[]){
    double r = this->radius;
	int i,n=20;
    //since a n-sided polygon will have n triangles => n*3 vertices => 3*(n*3) co-ordinates
    for(i=0;i<n;i++){
		arr[27*i] = r*cos(((2*M_PI*i)/n));
		arr[27*i+1] = r*sin(((2*M_PI*i)/n));
		arr[27*i+2] = -0.2;
		
		arr[27*i+3] = r*cos(((2*M_PI*(i+1))/n));
		arr[27*i+4] = r*sin(((2*M_PI*(i+1))/n));
		arr[27*i+5] = -0.2;

        arr[27*i+6] = r*cos(((2*M_PI*i)/n));
		arr[27*i+7] = r*sin(((2*M_PI*i)/n));
		arr[27*i+8] = 0.2;

		arr[27*i+9] = r*cos(((2*M_PI*(i+1))/n));
		arr[27*i+10] = r*sin(((2*M_PI*(i+1))/n));
		arr[27*i+11] = -0.2;

		arr[27*i+12] = 0;
		arr[27*i+13] = 0;
		arr[27*i+14] = -0.2;        

		arr[27*i+15] = r*cos(((2*M_PI*i)/n));
		arr[27*i+16] = r*sin(((2*M_PI*i)/n));
		arr[27*i+17] = -0.2;

		arr[27*i+18] = r*cos(((2*M_PI*i)/n));
		arr[27*i+19] = r*sin(((2*M_PI*i)/n));
		arr[27*i+20] = 0.2;
		
		arr[27*i+21] = r*cos(((2*M_PI*(i+1))/n));
		arr[27*i+22] = r*sin(((2*M_PI*(i+1))/n));
		arr[27*i+23] = 0.2;
		
		arr[27*i+24] = r*cos(((2*M_PI*(i+1))/n));
		arr[27*i+25] = r*sin(((2*M_PI*(i+1))/n));
		arr[27*i+26] = -0.3;

	}
	return;
}

void Missiles::draw(glm::mat4 VP){

    Matrices.model = glm::mat4(1.0f);
    glm::mat4 rotate = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    if(this->play)
        rotate *= glm::rotate((float) ((float)this->rotation* M_PI / 180.0f), glm::vec3(0, 1, 0));
    else{
        rotate *= glm::rotate((float) ((float)acos(this->cosin.x)* M_PI / 180.0f), glm::vec3(0, 1, 0));
        rotate *= glm::rotate((float) ((float)acos(this->cosin.y)* M_PI / 180.0f), glm::vec3(0, 0, -1));
    }
    Matrices.model *= (translate* rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Missiles::tick(){

    if(this->play && this->speedy>0){
        this->speedy -=0.05;
        this->position.x += this->speedx;
        this->position.y -= 0.05;
        this->position.z += this->speedz;
    }
    else if(!this->play && this->speedy > 0){
        this->position.x += 0.3*this->cosin.x;
        this->position.y += 0.3*this->cosin.y;
        this->position.z += 0.3*this->cosin.z;
        this->speedy -= 0.3;
    }
}


Bombs::Bombs(float x,float y,float z,float rotation,color_t color) {
    this->position = glm::vec3(x, y, z);
    this->radius = 0.2;
    this->width = 2*radius;
    this->dam = 20;
    this->rotation = rotation;
    this->speedx = 0.1*sin(rotation*M_PI / 180.0f);
    this->speedz = 0.1*cos(rotation*M_PI / 180.0f);
    this->speedy = y+1;
    GLfloat vertex_buffer_data[600];
    coordinates_generator(vertex_buffer_data);
    this->object = create3DObject(GL_TRIANGLES, 20*9, vertex_buffer_data, color, GL_FILL);
}


//Bombs
void Bombs::coordinates_generator(GLfloat arr[]){
    double r = this->radius;
	int i,n=20;
    //since a n-sided polygon will have n triangles => n*3 vertices => 3*(n*3) co-ordinates
    for(i=0;i<n;i++){
		arr[27*i] = r*cos(((2*M_PI*i)/n));
		arr[27*i+1] = r*sin(((2*M_PI*i)/n));
		arr[27*i+2] = -0.4;
		
		arr[27*i+3] = r*cos(((2*M_PI*(i+1))/n));
		arr[27*i+4] = r*sin(((2*M_PI*(i+1))/n));
		arr[27*i+5] = -0.4;

        arr[27*i+6] = r*cos(((2*M_PI*i)/n));
		arr[27*i+7] = r*sin(((2*M_PI*i)/n));
		arr[27*i+8] = 0.4;

		arr[27*i+9] = r*cos(((2*M_PI*(i+1))/n));
		arr[27*i+10] = r*sin(((2*M_PI*(i+1))/n));
		arr[27*i+11] = -0.4;

		arr[27*i+12] = 0;
		arr[27*i+13] = 0;
		arr[27*i+14] = -0.4;        

		arr[27*i+15] = r*cos(((2*M_PI*i)/n));
		arr[27*i+16] = r*sin(((2*M_PI*i)/n));
		arr[27*i+17] = -0.4;

		arr[27*i+18] = r*cos(((2*M_PI*i)/n));
		arr[27*i+19] = r*sin(((2*M_PI*i)/n));
		arr[27*i+20] = 0.4;
		
		arr[27*i+21] = r*cos(((2*M_PI*(i+1))/n));
		arr[27*i+22] = r*sin(((2*M_PI*(i+1))/n));
		arr[27*i+23] = 0.4;
		
		arr[27*i+24] = r*cos(((2*M_PI*(i+1))/n));
		arr[27*i+25] = r*sin(((2*M_PI*(i+1))/n));
		arr[27*i+26] = -0.4;
		
	}
	return;
}

void Bombs::draw(glm::mat4 VP){

    Matrices.model = glm::mat4(1.0f);
    glm::mat4 rotate = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    rotate *= glm::rotate((float) ((float)this->rotation* M_PI / 180.0f), glm::vec3(0, 1, 0));
    Matrices.model *= (translate* rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Bombs::tick(){

    if(this->speedy>0){
        this->position.y -= 0.1;
        this->speedy -=0.1;
        this->position.x += this->speedx;
        this->position.z += this->speedz;
    }
}

Platform::Platform(color_t color) {
    this->position = glm::vec3(0, 0, 0);
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat vertex_buffer_data[] = {
        1000,-0.01,-1000,
        1000,-0.01,1000,
        -1000,-0.01,1000,
        -1000,-0.01,1000,
        1000,-0.01,-1000,
        -1000,-0.01,-1000,
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

Mountain::Mountain(float x, float y, float z,color_t color) {
    this->position = glm::vec3(x, y, z);
    this->radius = 4;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat vertex_buffer_data[600];
    this->coordinates_generator(vertex_buffer_data);
    this->object = create3DObject(GL_TRIANGLES, 180, vertex_buffer_data, color, GL_FILL);
}


void Mountain::draw(glm::mat4 VP){

    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Mountain::coordinates_generator(GLfloat arr[]){
    double r1 = this->radius,r2 = this->radius/3;
	int i,n=20;
    //since a n-sided polygon will have n triangles => n*3 vertices => 3*(n*3) co-ordinates
    for(i=0;i<n;i++){
        arr[27*i] = r1*cos(((2*M_PI*i)/n));
		arr[27*i+1] = 0;
		arr[27*i+2] = r1*sin(((2*M_PI*i)/n));
		
		arr[27*i+3] = r1*cos(((2*M_PI*(i+1))/n));
		arr[27*i+4] = 0;
		arr[27*i+5] = r1*sin(((2*M_PI*(i+1))/n));

        arr[27*i+6] = r2*cos(((2*M_PI*i)/n));
		arr[27*i+7] = 4;
		arr[27*i+8] = r2*sin(((2*M_PI*i)/n));

		arr[27*i+9] = r1*cos(((2*M_PI*(i+1))/n));
		arr[27*i+10] = 0;
		arr[27*i+11] = r1*sin(((2*M_PI*(i+1))/n));

		arr[27*i+12] = 0;
		arr[27*i+13] = 0;
		arr[27*i+14] = 0;        

		arr[27*i+15] = r1*cos(((2*M_PI*i)/n));
		arr[27*i+16] = 0;
		arr[27*i+17] = r1*sin(((2*M_PI*i)/n));

		arr[27*i+18] = r2*cos(((2*M_PI*i)/n));
		arr[27*i+19] = 4;
		arr[27*i+20] = r2*sin(((2*M_PI*i)/n));
		
		arr[27*i+21] = r2*cos(((2*M_PI*(i+1))/n));
		arr[27*i+22] = 4;
		arr[27*i+23] = r2*sin(((2*M_PI*(i+1))/n));
		
		arr[27*i+24] = r1*cos(((2*M_PI*(i+1))/n));
		arr[27*i+25] = 0;
		arr[27*i+26] = r1*sin(((2*M_PI*(i+1))/n));
    }
return;
}

Island::Island(float x, bool mountain, float z,color_t color) {
    this->position = glm::vec3(x, 0 , z);
    this->radius = 9;
    this->mountain = mountain;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat vertex_buffer_data[200];
    this->coordinates_generator(vertex_buffer_data);
    this->object = create3DObject(GL_TRIANGLES, 60, vertex_buffer_data, color, GL_FILL);
    if(mountain){
        this->mount = Mountain(x,0,z,COLOR_FIRE);
    }
    else{
        this->ene = Enemy2(x,0,z,COLOR_PLAYER);
    }
}


void Island::draw(glm::mat4 VP){

    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    if(this->mountain){
        this->mount.draw(VP);
    }
    else{
        this->ene.draw(VP);
    }
}

void Island::coordinates_generator(GLfloat arr[]){
    double r1= this->radius,r2= this->radius/2;
	int i,n=20;
    //since a n-sided polygon will have n triangles => n*3 vertices => 3*(n*3) co-ordinates
    for(i=0;i<n;i++){
		
        arr[9*i] = r2*cos(((2*M_PI*i)/n));
		arr[9*i+1] = 0;
		arr[9*i+2] = r1*sin(((2*M_PI*i)/n));
		
		arr[9*i+3] = r2*cos(((2*M_PI*(i+1))/n));
		arr[9*i+4] = 0;
		arr[9*i+5] = r1*sin(((2*M_PI*(i+1))/n));

        arr[9*i+6] = 0;
		arr[9*i+7] = 0;
		arr[9*i+8] = 0;

    }
return;
}

Rings::Rings(float x, float y, float z,color_t color) {
    this->position = glm::vec3(x, y, z);
    this->radius = 4;
    this->rotationz = 0;
    this->rotationy = 0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat vertex_buffer_data[600];
    this->coordinates_generator(vertex_buffer_data);
    this->object = create3DObject(GL_TRIANGLES, 60, vertex_buffer_data, color, GL_FILL);
}

void Rings::draw(glm::mat4 VP){

   Matrices.model = glm::mat4(1.0f);
    glm::mat4 rotate = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    rotate *= glm::rotate((float) ((float)this->rotationy* M_PI / 180.0f), glm::vec3(0, 1, 0));
    rotate *= glm::rotate((float) ((float)this->rotationz* M_PI / 180.0f), glm::vec3(0, 0, 1));
    Matrices.model *= (translate* rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}


void Rings::coordinates_generator(GLfloat arr[]){
    double r1 = this->radius,r2 = this->radius+0.3;
	int i,n=20;
    //since a n-sided polygon will have n triangles => n*3 vertices => 3*(n*3) co-ordinates
    for(i=0;i<n;i++){
		arr[9*i] = r1*cos(((2*M_PI*i)/n));
		arr[9*i+1] = r1*sin(((2*M_PI*i)/n));
		arr[9*i+2] = 0;
		
		arr[9*i+3] = r1*cos(((2*M_PI*(i+1))/n));
		arr[9*i+4] = r1*sin(((2*M_PI*(i+1))/n));
		arr[9*i+5] = 0;

        arr[9*i+6] = r2*cos(((2*M_PI*i)/n));
		arr[9*i+7] = r2*sin(((2*M_PI*i)/n));
		arr[9*i+8] = 0;
    }
return;
}

Enemy1::Enemy1(float x, float y,float z, color_t color){
    this->position = glm::vec3(x, y, z);
    this->radius = 1;
    this->height = 0.2;
    this->width = 3;
    this->health = 100;
    GLfloat vertex_buffer_data[600];
    GLfloat vertex_buffer_data1[] = {
        0.5 , - 0.5 ,  0.5,
        - 0.5 , - 0.5 , - 0.5,
        0.5 , - 0.5 , - 0.5,

        0.5 ,  0.5 , - 0.5,
        0.5 , - 0.5 , - 0.5,
        - 0.5 , - 0.5 , - 0.5,

        - 0.5 , - 0.5 , - 0.5,
        - 0.5 , - 0.5 ,  0.5,
        - 0.5 ,  0.5 ,  0.5,

        0.5 ,  0.5 , - 0.5,
        - 0.5 , - 0.5 , - 0.5,
        - 0.5 ,  0.5 , - 0.5,

        - 0.5 ,  0.5 ,  0.5,
        - 0.5 , - 0.5 ,  0.5,
        0.5 , - 0.5 ,  0.5,

        0.5 ,  0.5 ,  0.5,
        0.5 , - 0.5 , - 0.5,
        0.5 ,  0.5 , - 0.5,

        - 0.5 , - 0.5 , - 0.5,
        - 0.5 ,  0.5 ,  0.5,
        - 0.5 ,  0.5 , - 0.5,

        0.5 , - 0.5 ,  0.5,
        - 0.5 , - 0.5 ,  0.5,
        - 0.5 , - 0.5 , - 0.5,

        0.5 , - 0.5 , - 0.5,
        0.5 ,  0.5 ,  0.5,
        0.5 , - 0.5 ,  0.5,

        0.5 ,  0.5 ,  0.5,
        0.5 ,  0.5 , - 0.5,
        - 0.5 ,  0.5 , - 0.5,

        0.5 ,  0.5 ,  0.5,
        - 0.5 ,  0.5 , - 0.5,
        - 0.5 ,  0.5 ,  0.5,

        0.5 ,  0.5 ,  0.5,
        - 0.5 ,  0.5 ,  0.5,
        0.5 , - 0.5 ,  0.5
};
    this->coordinates_generator(vertex_buffer_data);
    this->object = create3DObject(GL_TRIANGLES, (20/2)*3+6, vertex_buffer_data, color, GL_FILL);    
    this->object1 = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data1, color, GL_FILL);    
}


void Enemy1::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    glm::mat4 rotate = glm::mat4(1.0f);
    rotate *= glm::rotate((float) ((float)this->rotation* M_PI / 180.0f), glm::vec3(0, 1, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);

    translate = glm::translate (glm::vec3(0,-0.75,0));
    Matrices.model *= (translate);// * rotate);
    MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
}

void Enemy1::tick(){
    this->rotation+=1;
    this->position.y -= 0.01;
}

void Enemy1::coordinates_generator(GLfloat arr[]){
    double r = this->radius;
	int i,n=20;
    //since a n-sided polygon will have n triangles => n*3 vertices => 3*(n*3) co-ordinates
    for(i=0;i<n/2;i++){
		arr[9*i] = r*cos(((2*M_PI*i)/n));
		arr[9*i+1] = r*sin(((2*M_PI*i)/n));
		arr[9*i+2] = 0;
		
		arr[9*i+3] = r*cos(((2*M_PI*(i+1))/n));
		arr[9*i+4] = r*sin(((2*M_PI*(i+1))/n));
		arr[9*i+5] = 0;

        arr[9*i+6] = 0;
		arr[9*i+7] = 0;
		arr[9*i+8] = 0;
    }
    arr[9*i] = r;
	arr[9*i+1] = 0;
	arr[9*i+2] = 0;

    arr[9*i+3] = r - 0.2;
	arr[9*i+4] = 0;
	arr[9*i+5] = 0;

    arr[9*i+6] = 0;
	arr[9*i+7] = -1*r;
	arr[9*i+8] = 0;

    i++;
    arr[9*i] = -1*r;
	arr[9*i+1] = 0;
	arr[9*i+2] = 0;

    arr[9*i+3] = -1*(r - 0.2);
	arr[9*i+4] = 0;
	arr[9*i+5] = 0;

    arr[9*i+6] = 0;
	arr[9*i+7] = -1*r;
	arr[9*i+8] = 0;


return;
}

Enemy2::Enemy2(float x, float y,float z, color_t color){
    this->position = glm::vec3(x, y, z);
    this->radius = 1;
    this->height = 0.2;
    this->width = 3;
    this->del = 0;
    GLfloat vertex_buffer_data1[] = {
        1 , - 1 ,  1,
        - 1 , - 1 , - 1,
        1 , - 1 , - 1,

        1 ,  1 , - 1,
        1 , - 1 , - 1,
        - 1 , - 1 , - 1,

        - 1 , - 1 , - 1,
        - 1 , - 1 ,  1,
        - 1 ,  1 ,  1,

        1 ,  1 , - 1,
        - 1 , - 1 , - 1,
        - 1 ,  1 , - 1,

        - 1 ,  1 ,  1,
        - 1 , - 1 ,  1,
        1 , - 1 ,  1,

        1 ,  1 ,  1,
        1 , - 1 , - 1,
        1 ,  1 , - 1,

        - 1 , - 1 , - 1,
        - 1 ,  1 ,  1,
        - 1 ,  1 , - 1,

        1 , - 1 ,  1,
        - 1 , - 1 ,  1,
        - 1 , - 1 , - 1,

        1 , - 1 , - 1,
        1 ,  1 ,  1,
        1 , - 1 ,  1,

        1 ,  1 ,  1,
        1 ,  1 , - 1,
        - 1 ,  1 , - 1,

        1 ,  1 ,  1,
        - 1 ,  1 , - 1,
        - 1 ,  1 ,  1,

        1 ,  1 ,  1,
        - 1 ,  1 ,  1,
        1 , - 1 ,  1
};
    this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data1, color, GL_FILL);    
}

void Enemy2::draw(glm::mat4 VP) {
    if(this->del==0){
        Matrices.model = glm::mat4(1.0f);
        glm::mat4 translate = glm::translate (this->position);    // glTranslatef
        // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
        // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
        Matrices.model *= (translate);// * rotate);
        glm::mat4 MVP = VP * Matrices.model;
        glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
        draw3DObject(this->object);
        for(int i=0;i<this->bulls.size();i++){
            this->bulls[i].draw(VP);
        }
    }
}

Dashboard::Dashboard(color_t color) {
    this->rotation = 0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices

}

void Dashboard::draw(glm::mat4 VP){

    GLfloat vertex_buffer_data[] = {
        5,20*this->speed,0,
        0,20*this->speed,0,
        5,0,0,
        5,0,0,
        0,0,0,
        0,20*this->speed,0,
    };
    GLfloat vertex_buffer_data1[] = {
        5,20*this->fuel,0,
        0,20*this->fuel,0,
        5,0,0,
        5,0,0,
        0,0,0,
        0,20*this->fuel,0,
    };
    GLfloat vertex_buffer_data2[] = {
        5,20*this->height,0,
        0,20*this->height,0,
        5,0,0,
        5,0,0,
        0,0,0,
        0,20*this->height,0,
    };

    GLfloat vertex_buffer_data4[] = {
        5,0,0,
        -5,0,0,
        0,5,0,
    };
    GLfloat vertex_buffer_data5[] = {
        5,0,0,
        -5,0,0,
        0,-5,0,
    };

    GLfloat vertex_buffer_data3[] = {
        30,25,0,
        -30,25,0,
        30,-25,0,
        30,-25,0,
        -30,-25,0,
        -30,25,0,
    };
    this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, COLOR_DARK_BLACK, GL_FILL);
    this->object1 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data1, COLOR_GOLD, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data2, COLOR_YELLOW, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data3, COLOR_WHITE, GL_FILL);
    this->object4 = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data4, COLOR_RED, GL_FILL);
    this->object5 = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data5, COLOR_DARK_BLACK, GL_FILL);

    Matrices.model = glm::mat4(1.0f);
    // glm::mat4 rotate = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // rotate *= glm::rotate((float) ((float)this->rotationy* M_PI / 180.0f), glm::vec3(0, 1, 0));
    // rotate *= glm::rotate((float) ((float)this->rotationz* M_PI / 180.0f), glm::vec3(0, 0, 1));
    Matrices.model *= (translate);//* rotate);
    glm::mat4 MVP = VP * Matrices.model;
    // glm::mat4 MVP = Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object3);
    
    //speed

    translate = glm::translate (this->position + glm::vec3(2.5,2.5,0));    // glTranslatef
    Matrices.model = (translate);//* rotate);
    MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);

    // fuel
    translate = glm::translate (this->position + glm::vec3(10,2.5,0));    // glTranslatef
    Matrices.model = translate;//* rotate;
    MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);

    // height
    translate = glm::translate (this->position + glm::vec3(-10,2.5,0));    // glTranslatef
    Matrices.model = (translate);//* rotate);
    MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object2);

    translate = glm::translate (this->position + glm::vec3(0,-4,0));    // glTranslatef
    glm::mat4 rotate = glm::mat4(1.0f);
    rotate *= glm::rotate((float) ((float)this->rotation* M_PI / 180.0f), glm::vec3(0, 0, 1));
    Matrices.model = (translate* rotate);
    MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object4);

    draw3DObject(this->object5);
}


Fuel::Fuel(float x, float y,float z, color_t color){
    this->position = glm::vec3(x, y, z);
    GLfloat vertex_buffer_data1[] = {
        1 , - 1 ,  1,
        - 1 , - 1 , - 1,
        1 , - 1 , - 1,

        1 ,  1 , - 1,
        1 , - 1 , - 1,
        - 1 , - 1 , - 1,

        - 1 , - 1 , - 1,
        - 1 , - 1 ,  1,
        - 1 ,  1 ,  1,

        1 ,  1 , - 1,
        - 1 , - 1 , - 1,
        - 1 ,  1 , - 1,

        - 1 ,  1 ,  1,
        - 1 , - 1 ,  1,
        1 , - 1 ,  1,

        1 ,  1 ,  1,
        1 , - 1 , - 1,
        1 ,  1 , - 1,

        - 1 , - 1 , - 1,
        - 1 ,  1 ,  1,
        - 1 ,  1 , - 1,

        1 , - 1 ,  1,
        - 1 , - 1 ,  1,
        - 1 , - 1 , - 1,

        1 , - 1 , - 1,
        1 ,  1 ,  1,
        1 , - 1 ,  1,

        1 ,  1 ,  1,
        1 ,  1 , - 1,
        - 1 ,  1 , - 1,

        1 ,  1 ,  1,
        - 1 ,  1 , - 1,
        - 1 ,  1 ,  1,

        1 ,  1 ,  1,
        - 1 ,  1 ,  1,
        1 , - 1 ,  1
};
    this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data1, color, GL_FILL);    

}

void Fuel::draw(glm::mat4 VP) {
        /*float a;
        if(this->position.y==15){
            a = -0.05;
        }
        else if(this->position.y==7){
            a = 0.05;
        }
        this->position.y += a;*/
        Matrices.model = glm::mat4(1.0f);
        glm::mat4 translate = glm::translate (this->position);    // glTranslatef
        // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
        // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
        Matrices.model *= (translate);// * rotate);
        glm::mat4 MVP = VP * Matrices.model;
        glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
        draw3DObject(this->object);
}