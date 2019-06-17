#include "main.h"
#include "timer.h"
#include "ball.h"

using namespace std;

GLMatrices Matrices;
GLMatrices Matrices1;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

Ball ball1;
Platform plat;
Dashboard dash;
vector <Island> islands;
vector <Enemy1> ene;
vector <Fuel> fuel_ups;
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
glm::vec3 camera_rotation;
float camera_rotation_angle = 0;
int cam = 0,heli = 0,mis = 0,bm = 0;
float rad = 7;
bool hov = false;
vector <Rings> rings;
Timer t60(1.0 / 60);
int counter = 0;
char output[100];
glm::vec3 eye,target,up;
glm::vec3 eye1,target1,up1;
/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;

    glUseProgram (programID);

    eye1 = glm::vec3 (0,0,10);
    target1 = glm::vec3 (0,0,0);
    up1 = glm::vec3(0,1,0);

    if(cam==0){
        // Follow-cam
        heli = 0;
        eye = glm::vec3 (-2*sin(ball1.rotationx* M_PI / 180.0f)+ball1.position.x,2+ball1.position.y,-2*cos(ball1.rotationx* M_PI / 180.0f)+ball1.position.z);
        target = ball1.position;
        up = glm::vec3(0,1,0);

        // dash.position = glm::vec23left,bottom);
    }
    else if(cam==1){
        // Plane view
        eye = glm::vec3 (1.5*sin(ball1.rotationx* M_PI / 180.0f)+ball1.position.x,ball1.position.y,1.5*cos(ball1.rotationx* M_PI / 180.0f)+ball1.position.z);        
        target = glm::vec3 (6*sin(ball1.rotationx* M_PI / 180.0f)+ball1.position.x,ball1.position.y,6*cos(ball1.rotationx* M_PI / 180.0f)+ball1.position.z);    
        up = glm::vec3(0,1,0);
    }
    else if(cam==2){
        // Top view
        eye = glm::vec3 (ball1.position.x,ball1.position.y+4,ball1.position.z);        
        target = ball1.position;    
        up = glm::vec3(sin(ball1.rotationx* M_PI / 180.0f),0,cos(ball1.rotationx* M_PI / 180.0f));
    }
    else if(cam==3){
        //Tower View
        eye = glm::vec3 (-1,2,-5);        
        target = ball1.position;    
        up = glm::vec3(0,1,0);
    }
    else if(cam==4){
        float alpha = glm::radians(camera_rotation.x);
        float theta = glm::radians(camera_rotation.y);
        float r = rad*std::sin(theta);
        glm::vec3 pos (0, rad*cos(theta), 0);
        glm::vec3 ro (r*std::cos(alpha), 0, r*std::sin(alpha));
        eye = ball1.position + pos + ro;
        target = ball1.position;
        up = glm::vec3(0, 1, 0);
    }
        // eye = glm::vec3 (-1+ball1.position.x,2+ball1.position.y,-5+ball1.position.z);
        // eye = glm::vec3 (0,10,0);
    
    // Eye - Location of camera. Don't change unless you are sure!!
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    
    

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    Matrices1.view = glm::lookAt( eye1, target1, up1 ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;
    glm::mat4 VP1 = Matrices1.projection * Matrices1.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    glViewport(0,500,200,400);
    dash.draw(VP1);

    glViewport(0,0,1000,1000); 
    plat.draw(VP);
    ball1.draw(VP);
    for(int i=0;i<rings.size();i++){
        rings[i].rotationz+=1;
        rings[i].rotationz%=360;
        rings[i].draw(VP);
    }
    for(int i=0;i<ene.size();i++){
        ene[i].draw(VP);
    }
    for(int i=0;i<ball1.bulls.size();i++){
        ball1.bulls[i].draw(VP);
    }
    for(int i=0;i<ball1.bombs.size();i++){
        ball1.bombs[i].draw(VP);
    }
    for(int i=0;i<islands.size();i++){
        islands[i].draw(VP);
    }

    for(int i=0;i<fuel_ups.size();i++){
        fuel_ups[i].draw(VP);
    }

}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_Q);
    int right = glfwGetKey(window, GLFW_KEY_E);
    int fwd = glfwGetKey(window, GLFW_KEY_W);
    int tilt_left = glfwGetKey(window, GLFW_KEY_A);
    int tilt_right = glfwGetKey(window, GLFW_KEY_D);
    int up = glfwGetKey(window, GLFW_KEY_SPACE);
    int down = glfwGetKey(window, GLFW_KEY_S);
    
    if (left==GLFW_PRESS) {
        ball1.speedx = 1;
    }
    else if(right==GLFW_PRESS){
        ball1.speedx = -1;
    }
    else{
        ball1.speedx = 0;
    }

    if(up==GLFW_PRESS){
        ball1.speedy = -1;
    }
    else if(down==GLFW_PRESS){
        ball1.speedy = 1;
    }
    else{
        ball1.speedy = 0;
    }

    if(tilt_left==GLFW_PRESS){
        ball1.speedz = -1;
    }
    else if(tilt_right == GLFW_PRESS){
        ball1.speedz = 1;
    }
    else{
        ball1.speedz = 0;
    }

    if(fwd==GLFW_PRESS){
        ball1.forward = 1;
        dash.speed = 1;
    }
    else{
        ball1.forward = 0;
        dash.speed = 0.4;
    }


    double xpos, ypos;

    glfwGetCursorPos(window, &xpos, &ypos);
    if (xpos > 600) {
        camera_rotation.x -= 1;
    }
    if (xpos < 400) {
        camera_rotation.x += 1;
    }
    if (ypos < 600) {
        camera_rotation.y -= 1;
    }
    if (ypos > 400) {
        camera_rotation.y += 1;
    }
}

void tick_elements() {

    dash.rotation = ball1.rotationx;
    counter++;
    if(counter%300 == 0){
        ball1.score += 5;
        counter = 0;
    }
    dash.fuel -= 0.0005;
    dash.height = (ball1.position.y)/(19.5 - 0);
    if(ball1.position.y<0.4){
        system("ffplay -nodisp -autoexit ../src/death_sound.mp3 >/dev/null 2>&1 &");
        quit(window);
    }
    ball1.tick();
    //fuel ups
    for(int i=0;i<fuel_ups.size();i++){
        if(dist(fuel_ups[i].position,ball1.position)<=1.75){
            system("ffplay -nodisp -autoexit ../src/power_sound.mp3 >/dev/null 2>&1 &");
            fuel_ups.erase(fuel_ups.begin() + i);
            dash.fuel = 1;
            i--;
            break;
        }
    }
    if(dash.fuel<=0){
        system("ffplay -nodisp -autoexit ../src/death_sound.mp3 >/dev/null 2>&1 &");
        quit(window);
    }
    //checkpoints
  /*  int i = ball1.ind;
    if(!(ball1.checks[i].reached) && ball1.position.x<=ball1.checks[i].x + 1.5 && ball1.position.x>=ball1.checks[i].x -1.5 && ball1.position.z <= 1.5+ ball1.checks[i].z && ball1.position.z >= -1.5+ ball1.checks[i].z){
        ball1.checks[i].reached = true;
        i++;
        ball1.check_position = glm::vec3(ball1.checks[i].x, ball1.checks[i].y, ball1.checks[i].z);
        ball1.ind = i;
    }*/


    // enemy1 update
    for(int i=0;i<ene.size();i++){
        if(dist(ene[i].position,ball1.position)<=1.75){
            ene.erase(ene.begin() + i);
            system("ffplay -nodisp -autoexit ../src/death_sound.mp3 >/dev/null 2>&1 &");
            quit(window);
        }
        if(dist(ene[i].position,ball1.position)<=30){
            ene[i].tick();
            if(ene[i].position.y<=0.75){
                ene.erase(ene.begin() + i);
            }
        }
    }
    //player missiles and its collisions
    if(mis==1 && ball1.bulls.size()<1){
        Missiles temp = Missiles(ball1.position.x,ball1.position.y,ball1.position.z,ball1.rotationx,glm::vec3(0,0,0),true,COLOR_FIRE);
        ball1.bulls.push_back(temp);
    }
    else{
        mis = 0;
    }

    for(int i=0;i<ball1.bulls.size();i++){
        ball1.bulls[i].tick();
        if(ball1.bulls[i].speedy<=0){
            ball1.bulls.erase(ball1.bulls.begin() + i);
            i--;
        }
        else{
            for(int j=0;j<islands.size();j++){
                if(!(islands[j].mountain) && islands[j].ene.del == 0 && dist(ball1.bulls[i].position,islands[j].position)<=1.5){
                    ball1.bulls.erase(ball1.bulls.begin() + i);
                    i--;
                    islands[j].ene.del = 1;
                    ball1.score += 10;
                    break;
                }
                else if(islands[j].mountain && dist(ball1.bulls[i].position,islands[j].position)<=5){
                    ball1.bulls.erase(ball1.bulls.begin() + i);
                    i--;
                    break;
                }
            }
            for(int j=0;j<ene.size();j++){
                if(dist(ball1.bulls[i].position,ene[j].position)<=1.25){
                    ball1.bulls.erase(ball1.bulls.begin() + i);
                    i--;
                    ene.erase(ene.begin() + j);
                    ball1.score += 5;
                    break;
                }
            }
        }
    }



    //player bombs and its collisions
    if(bm == 1 && ball1.bombs.size()<2){
        Bombs temp = Bombs(ball1.position.x,ball1.position.y,ball1.position.z,ball1.rotationx,COLOR_GOLD);
        ball1.bombs.push_back(temp);
        bm = 0;
    }
    else if(bm==1){
        bm = 0;
    }
    for(int i=0;i<ball1.bombs.size();i++){
        ball1.bombs[i].tick();
        if(ball1.bombs[i].speedy<=0){
            ball1.bombs.erase(ball1.bombs.begin() + i);
            i--;
        }
        else{
            for(int j=0;j<islands.size();j++){
                if(!(islands[j].mountain) && islands[j].ene.del == 0 && dist(ball1.bombs[i].position,islands[j].position)<=1.5){
                    ball1.bombs.erase(ball1.bombs.begin() + i);
                    i--;
                    islands[j].ene.del = 1;
                    ball1.score += 10;
                    break;
                }
                else if(islands[j].mountain && dist(ball1.bombs[i].position,islands[j].position)<=5){
                    ball1.bombs.erase(ball1.bombs.begin() + i);
                    i--;
                    break;
                }
            }
            for(int j=0;j<ene.size();j++){
                if(dist(ball1.bombs[i].position,ene[j].position)<=1.25){
                    ball1.bombs.erase(ball1.bombs.begin() + i);
                    i--;
                    ene.erase(ene.begin() + j);
                    ball1.score += 5;
                    break;
                }
            }
        }
    }
    camera_rotation_angle = ball1.rotationx;

    //collision for volcanoes
    for(int i=0;i<islands.size();i++){
        if(islands[i].mountain && dist(islands[i].position,ball1.position)<5){
            system("ffplay -nodisp -autoexit ../src/death_sound.mp3 >/dev/null 2>&1 &");
            quit(window);
        }
        else if(!islands[i].mountain && dist(islands[i].position,ball1.position)<=1.5){
            system("ffplay -nodisp -autoexit ../src/death_sound.mp3 >/dev/null 2>&1 &");
            quit(window);
        }
    }

    // collision for bombs


    //ene2 missiles
    for(int i=0;i<islands.size();i++){
        if(!(islands[i].mountain) && islands[i].ene.del == 0 &&  dist(islands[i].position,ball1.position)<=20){
            if(islands[i].ene.bulls.size()<3){
                double x,y,z,r= dist(islands[i].position,ball1.position);
                x = (ball1.position.x - islands[i].position.x)/r;
                y = (ball1.position.y - islands[i].position.y)/r;
                z = (ball1.position.z - islands[i].position.z)/r;
                islands[i].ene.bulls.push_back(Missiles(islands[i].ene.position.x,0,islands[i].ene.position.z,0,glm::vec3(x,y,z),false,COLOR_BLACK));
            }
            for(int j=0;j<islands[i].ene.bulls.size();j++){
                islands[i].ene.bulls[j].tick();
                if(islands[i].ene.bulls[j].speedy<=0){
                    islands[i].ene.bulls.erase(islands[i].ene.bulls.begin() + j);
                    j--;
                }
                else if(abs(ball1.position.x-islands[i].ene.bulls[j].position.x)<=abs(sin(ball1.rotationx*M_PI/180.0f)*cos(ball1.rotationy*M_PI/180.0f))+ball1.radius+islands[i].ene.bulls[j].radius){
                    if(abs(ball1.position.z-islands[i].ene.bulls[j].position.z)<=abs(cos(ball1.rotationx*M_PI/180.0f)*cos(ball1.rotationy*M_PI/180.0f))+ball1.radius+islands[i].ene.bulls[j].radius){
                        if(abs(ball1.position.y-islands[i].ene.bulls[j].position.y)<=abs(sin(ball1.rotationy*M_PI/180.0f))+ball1.radius+islands[i].ene.bulls[j].radius){
                            system("ffplay -nodisp -autoexit ../src/death_sound.mp3 >/dev/null 2>&1 &");
                            quit(window);
                        }
                    }
                }
            }
        }
        else if(!(islands[i].mountain) && islands[i].ene.del==0){
            for(int j=0;j<islands[i].ene.bulls.size();j++){
                islands[i].ene.bulls[j].tick();
                if(islands[i].ene.bulls[j].speedy<=0){
                        islands[i].ene.bulls.erase(islands[i].ene.bulls.begin() + j);
                        j--;
                }
                else{
                    if(abs(ball1.position.x-islands[i].ene.bulls[j].position.x)<=abs(sin(ball1.rotationx*M_PI/180.0f)*cos(ball1.rotationy*M_PI/180.0f))+ball1.radius+islands[i].ene.bulls[j].radius){
                        if(abs(ball1.position.z-islands[i].ene.bulls[j].position.z)<=abs(cos(ball1.rotationx*M_PI/180.0f)*cos(ball1.rotationy*M_PI/180.0f))+ball1.radius+islands[i].ene.bulls[j].radius){
                            if(abs(ball1.position.y-islands[i].ene.bulls[j].position.y)<=abs(sin(ball1.rotationy*M_PI/180.0f))+ball1.radius+islands[i].ene.bulls[j].radius){
                                system("ffplay -nodisp -autoexit ../src/death_sound.mp3 >/dev/null 2>&1 &");
                                quit(window);
                            }
                        }
                    }
                }
            }
        }
    }

    //rings
    for(int i=0;i<rings.size();i++){
       if(abs(ball1.position.z - rings[i].position.z)<=1){
           if(dist(ball1.position,rings[i].position)<=rings[i].radius){
               ball1.score+=5;
                rings.erase(rings.begin() + i);
                i--;
           }
       }
    }

    // check points
    int i=0;
    for(i=0;i<islands.size();i++){
        if(!(islands[i].mountain) && islands[i].ene.del==0){
            ball1.check_position = islands[i].ene.position;
            ball1.check_position.y = 6;
            break;
        }
    }
    if(i==islands.size()){
        
        quit(window);
    }

}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    ball1 = Ball(0, 3, 0,COLOR_PLAYER);
    for(int i=0;i<10;i++){
        ene.push_back(Enemy1(50*(i+1), 5, 50*(i+1)+10,COLOR_PLAYER));
    }
    dash = Dashboard(COLOR_WHITE);
    dash.fuel = 1;
    plat = Platform(COLOR_WATER);
    for(int i=0;i<30;i++){
        int temp = rand()%2,temp1 = rand()%2;
        Island a = Island(30*(i+1)+10*temp,temp,30*(i+1)+11*temp1,COLOR_BLACK);
        islands.push_back(a);
    }
    // for(i=0;i<)
    // Island a = Island(10+10,false,10+11,COLOR_BLACK);
    // islands.push_back(a);
    for(int i=0;i<6;i++){
        Fuel a = Fuel(100*(i+1),10,100*(i+1),COLOR_RED);
        fuel_ups.push_back(a);
    }
    for(int i=0;i<6;i++){
        Rings ring = Rings(100*(i+1),5,100*(i+1),COLOR_SILVER);
        rings.push_back(ring);
    }
    
    
    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL);
    camera_rotation = glm::vec3(0,0,0);

    srand(time(0));
    int width  = 1000;
    int height = 1000;

    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            if(ball1.ind>39){
                break;
            }
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);
            if(!hov){
                tick_elements();
                tick_input(window);
            }
            sprintf(output,"SCORE: %d",ball1.score);
            glfwSetWindowTitle(window,output);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    system("ffplay -nodisp -autoexit ../src/death_sound.mp3 >/dev/null 2>&1 &");
    quit(window);
}

double dist(glm::vec3 a, glm::vec3 b) {
    double x = (a.x - b.x)*(a.x - b.x);
    double y = (a.y - b.y)*(a.y - b.y);
    double z = (a.z - b.z)*(a.z - b.z);
    return sqrt(x+y+z);
}

double dist1(glm::vec3 a, glm::vec3 b) {
    double x = (a.x - b.x)*(a.x - b.x);
    double z = (a.z - b.z)*(a.z - b.z);
    return sqrt(x+z);
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    // Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}

void score_seven_segment(int score){
    //show score

}