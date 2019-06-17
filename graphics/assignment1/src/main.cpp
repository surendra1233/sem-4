#include "main.h"
#include "timer.h"
#include "ball.h"

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/
Magnet mg;
Ball ball1;
Platform plat;
Boomerang boom;
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;
int level = 1;
vector <Coin> coins;
vector <Coin> jet;
vector <Enemy1> ene1;
vector <Enemy2> ene2;
vector <Boomerang> booms;
vector <pair<int,int> > ene_arr;
vector <Special> specials;
Timer t60(1.0 / 60);
float scr_speed = 0.03*level;
char output[100];
bool comparecoins(Coin c1, Coin c2) 
{ 
    return (c1.position.x < c2.position.x); 
}
bool compareenemies(Enemy1 c1, Enemy1 c2) 
{ 
    return (c1.position.x < c2.position.x); 
}
bool compareenemies2(Enemy2 c1, Enemy2 c2) 
{ 
    return (c1.position.x < c2.position.x); 
}
/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw(glm::vec3 eye,glm::vec3 target) {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    // glm::vec3 eye ( 0, 0, 5 );
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    // glm::vec3 target (0, 0, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    mg.draw(VP);
    plat.draw(VP);
    for(int i=0;i<jet.size();i++){
        jet[i].draw(VP);
    }
    jet.clear();
    for(int i=0;i<coins.size();i++)
        coins[i].draw(VP);
    
    for(int i=0;i<ball1.bubs.size();i++){
        if(ball1.bubs[i].position.y<=plat.position.y-4){
            ball1.bubs.erase(ball1.bubs.begin() + i);
            i--;
            continue;
        }
        ball1.bubs[i].draw(VP);
    }
    for(int i=0;i<ene1.size();i++){
        ene1[i].draw(VP);
    }   
    for(int i=0;i<ene2.size();i++){
        ene2[i].draw(VP);
    }
    for(int i=0;i<specials.size();i++){
        specials[i].draw(VP);
    }
    for(int i=0;i<booms.size();i++){
        booms[i].draw(VP);
    }
    ball1.draw(VP);

}


void tick_input(GLFWwindow *window) {
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int right_down = glfwGetKey(window, GLFW_KEY_RIGHT);
    int left = glfwGetKey(window, GLFW_KEY_LEFT);
    int up = glfwGetKey(window, GLFW_KEY_SPACE);
    int bub = glfwGetKey(window, GLFW_KEY_LEFT_CONTROL);

    if(right==GLFW_PRESS){
        if(ball1.position.x<=plat.position.x + 3.3 + 4*(1/screen_zoom - 1)){
            ball1.speedx+=0.2;        
        }
        else{
            ball1.speedx=0;
        }
    }
    else if(right == GLFW_RELEASE){
        ball1.speedx = 0;
        
        if(left==GLFW_PRESS){
            if(ball1.position.x>=plat.position.x -3.5 - 4*(1/screen_zoom - 1)){
                ball1.speedx-=0.2;        
            }
            else{
                ball1.speedx=0;
            }
        }
        else if(left == GLFW_RELEASE){
            ball1.speedx = 0;
        }
    }
    
    if(bub==GLFW_PRESS){
        Bubbles tem = Bubbles(ball1.position.x+0.3,ball1.position.y+0.3,0.04,ball1.speedx,COLOR_WATER);
        ball1.bubs.push_back(tem);
    }

    if(up== GLFW_PRESS){
        ball1.jump = 1;
        for(int i=0;i<5;i++){
            Coin a = Coin(ball1.position.x-0.2+(i)*0.04,ball1.position.y-0.3-i*0.1,0.04,COLOR_FIRE);
            jet.push_back(a);
        }
        for(int i=0;i<5;i++){
            Coin a = Coin(ball1.position.x-0.2-(i)*0.04,ball1.position.y-0.3-i*0.1,0.04,COLOR_FIRE);
            jet.push_back(a);
        }
        for(int i=0;i<5;i++){
            Coin a = Coin(ball1.position.x-0.2,ball1.position.y-0.3-i*0.1,0.04,COLOR_FIRE);
            jet.push_back(a);
        }    
    }
    else if(up == GLFW_RELEASE){
        ball1.jump = 0;
    }
}

void tick_elements() {
    level = 1 + plat.position.x/400;
    mg.position.x += (level-1)*400;
    //enemy2 collision
    if(ball1.health==0){
        system("ffplay -nodisp -autoexit src/death_sound.mp3 >/dev/null 2>&1 &");
        quit(window);
    }
    if(screen_zoom <=1){
        screen_center_x = 0;screen_center_y = 0;
    }
    else{
        screen_center_x = ball1.position.x;
        screen_center_y = ball1.position.y;
        reset_screen();
    }
    for(int i=0;i<ene2.size();i++){
        if(ball1.width/2 + (ene2[i].width)/2 > abs(ball1.position.x - ene2[i].position.x) && ball1.width/2 + ene2[i].height > abs(ball1.position.y - ene2[i].position.y)){
            ene2.erase(ene2.begin() + i);
            ball1.health--;
            break;
        }
        else{
            // if(ene2[i].position.x<= plat.position.x - 6 && ene2[i].position.x<=plat.position.x + 6)
                ene2[i].tick();
        } 
    }
    //collision for enemy1
    for(int i=0;i<ene1.size();i++){
        if(abs(ball1.position.x - ene1[i].position.x) <= ball1.width/2 +(ene1[i].width/2)*abs(cos(ene1[i].rotation* M_PI / 180.0f)) && abs(ball1.position.y - ene1[i].position.y) <= ball1.width/2 + (ene1[i].width/2)*abs(sin(ene1[i].rotation* M_PI / 180.0f))){
            double x5 = ball1.position.x , y5 = (ball1.position.y),dis = sqrt(1+tan(ene1[i].rotation * M_PI / 180.0f)*tan(ene1[i].rotation * M_PI / 180.0f)+(tan(ene1[i].rotation * M_PI / 180.0f)*ene1[i].position.x- ene1[i].position.y)*(tan(ene1[i].rotation * M_PI / 180.0f)*ene1[i].position.x- ene1[i].position.y));
            double val5 = abs(y5 - ene1[i].position.y - tan(ene1[i].rotation * M_PI / 180.0f)*(x5 - ene1[i].position.x));
            if(val5/dis<=ball1.width/2){
                ene1.erase(ene1.begin() + i);
                ball1.health--;
                break;  
            }
        }
    }
    //collision for bubbles(water)
    std::vector<Enemy2>::iterator low1,high1;
    Enemy2 temy = Enemy2(ball1.position.x-4,2,COLOR_FIRE);
    Enemy2 temy1 = Enemy2(ball1.position.x+4,2,COLOR_FIRE);
    high1 = std::upper_bound(ene2.begin(),ene2.end(),temy1,compareenemies2);
    low1 = std::lower_bound(ene2.begin(),ene2.end(),temy,compareenemies2);
   
    for(int j=(low1-ene2.begin());j<=(high1 - low1);j++){
        for(int i=0;i<ball1.bubs.size();i++){
            if(ball1.bubs[i].width/2 + (ene2[j].width)/2 > abs(ball1.bubs[i].position.x - ene2[j].position.x) && ball1.bubs[i].width/2 + ene2[j].height > abs(ball1.bubs[i].position.y - ene2[j].position.y)){
                ene2[j].health -= ball1.bubs[i].dam/level;
                if(ene2[j].health==0){
                    ene2.erase(ene2.begin() + j);
                    ball1.score+=10*level;
                }
                ball1.bubs.erase(ball1.bubs.begin() + i);
                i--;
            } 
        }
    }
    std::vector<Enemy1>::iterator low,high;
    Enemy1 tem = Enemy1(ball1.position.x-4,2,0,COLOR_FIRE);
    Enemy1 tem1 = Enemy1(ball1.position.x+4,2,0,COLOR_FIRE);
    high = std::upper_bound(ene1.begin(),ene1.end(),tem1,compareenemies);
    low = std::lower_bound(ene1.begin(),ene1.end(),tem,compareenemies);

    for(int j=(low-ene1.begin());j<=(high - low);j++){
        for(int i=0;i<ball1.bubs.size();i++){
            if(abs(ball1.bubs[i].position.x - ene1[j].position.x) <= ball1.bubs[i].width/2 +(ene1[j].width/2)*abs(cos(ene1[j].rotation* M_PI / 180.0f)) && abs(ball1.bubs[i].position.y - ene1[j].position.y) <= ball1.bubs[i].width/2 + (ene1[j].width/2)*abs(sin(ene1[j].rotation* M_PI / 180.0f))){
                double x5 = ball1.bubs[i].position.x , y5 = (ball1.bubs[i].position.y),dis = sqrt(1+tan(ene1[j].rotation * M_PI / 180.0f)*tan(ene1[j].rotation * M_PI / 180.0f)+(tan(ene1[j].rotation * M_PI / 180.0f)*ene1[j].position.x- ene1[j].position.y)*(tan(ene1[j].rotation * M_PI / 180.0f)*ene1[j].position.x- ene1[j].position.y));
                double val5 = abs(y5 - ene1[j].position.y - tan(ene1[j].rotation * M_PI / 180.0f)*(x5 - ene1[j].position.x));
                if(val5/dis<=ball1.bubs[i].width/2){
                    ene1[j].health -= ball1.bubs[i].dam/level;
                    if(ene1[j].health==0){
                        ene1.erase(ene1.begin() + j);
                        ball1.score+=10*level;
                    }
                    ball1.bubs.erase(ball1.bubs.begin() + i);
                    i--;
                }
            } 
        }
    }

    //collision for specials and also update
    for(int i=0;i<specials.size();i++){
        double x = ball1.position.x - specials[i].position.x , y = (ball1.position.y - specials[i].position.y);
        double dis = sqrt(x*x + y*y);
        if(dis<(ball1.width/2 + specials[i].width/2)*cos(M_PI/4) -0.05){
            ball1.health += specials[i].health;
            ball1.score += specials[i].pts;
            specials.erase(specials.begin() + i);
            i--;
            continue;
        }
        specials[i].tick();
    }
   //collision detection for coins.
    
    for(int i=0;i<=coins.size();i++){
        if(ball1.width/2 + coins[i].radius> abs(ball1.position.x - coins[i].position.x) && ball1.width/2 + coins[i].radius> abs(ball1.position.y - coins[i].position.y)){
            ball1.score += coins[i].pts*level;
            system("ffplay -nodisp -autoexit src/coin_sound.mp3 >/dev/null 2>&1 &");
            coins.erase(coins.begin() + i);
            i--;
        }
    }
    plat.position.x +=scr_speed;

    //bubbles
    for(int i=0;i<ball1.bubs.size();i++){
        ball1.bubs[i].tick();
    }
    //camera_rotation_angle += 1;
    double x = ball1.position.x - mg.position.x,y = ball1.position.y-mg.position.y,dist = sqrt(x*x + y*y);
    if(abs(mg.position.x -plat.position.x)<=3 && dist<=8){
        ball1.speedx += -0.01*(x/abs(x));
        ball1.attract = -1*(y/abs(y));    
    }
    else{
        ball1.attract = 0;
    }
    //collision detection for boomerang
    for(int i=0;i<=booms.size();i++){
        if(ball1.width/2 + booms[i].radius> abs(ball1.position.x - booms[i].position.x) && ball1.width/2 + booms[i].radius> abs(ball1.position.y - booms[i].position.y)){
            ball1.health --;
            booms.erase(booms.begin() + i);
            i--;
            std::cout << ball1.score << "\n";
        }
    }
    for(int i=0;i<=booms.size();i++){
        booms[i].tick();
    }    
    ball1.tick();

}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models
    
    ene_arr.push_back(make_pair(1,2));
    ene_arr.push_back(make_pair(18,2));
    ene_arr.push_back(make_pair(22,-1));
    ene_arr.push_back(make_pair(35,2));
    mg = Magnet(6,2,COLOR_FIRE);
    ball1 = Ball(-3, -3, COLOR_PLAYER);
    plat  = Platform(0,0,COLOR_PLATFORM);
    Special a = Special(500,0,COLOR_SPECIAL,1);
    specials.push_back(a);
    a = Special(50,-1,COLOR_SPECIAL,0);
    specials.push_back(a);
    a = Special(300,0,COLOR_SPECIAL,2);
    specials.push_back(a);
    for(int i=0;i<100;i++){
        int rot = rand()%91,temp = rand()%2;
        Enemy1 e = Enemy1((i/2)*40 + ene_arr[i%2].first,ene_arr[i%2].second,-2*temp*rot +rot,COLOR_FIRE);
        ene1.push_back(e);
    }
    for(int i=0;i<100;i++){
        Enemy2 e = Enemy2((i/2)*40 + ene_arr[2+i%2].first,ene_arr[2+i%2].second,COLOR_FIRE);
        ene2.push_back(e);
    }

    for(int i=0;i<100;i++){
        Boomerang e = Boomerang(i*30 +15,-1 + i%3,COLOR_SILVER);
        booms.push_back(e);
    }
    for(int i=0;i<2000;i++){
        int x = rand()%2000,y = rand()%6 - 2,temp = rand()%2;
        Coin a;
        if(temp==1)
            a = Coin(x,y,0.3,COLOR_GOLD);
        else
            a = Coin(x,y,0.3,COLOR_SILVER);

        coins.push_back(a);
    }
    std::sort(coins.begin(),coins.end(),comparecoins);
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

   /* cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;*/
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 600;
    int height = 600;
    
    bool coll = false;
    window = initGLFW(width, height);

    initGL (window, width, height);
    
    glm::vec3 eye(0,0,5),target(0,0,0);
    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            
            // 60 fps
            // OpenGL Draw commands
            
            draw(eye,target);
            // Swap Frame Buffer in double buffering

            glfwSwapBuffers(window);

            tick_input(window);
            
            eye = glm::vec3(plat.position.x,0,5);
            target = glm::vec3(plat.position.x,0,0);
            tick_elements();
            sprintf(output,"SCORE: %d, LIVES: %d,LEVEL: %d",ball1.score,ball1.health,level);
            glfwSetWindowTitle(window,output);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width));
}


void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}

