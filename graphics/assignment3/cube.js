
var game_speed = -0.1;
var track = [];
var rect_track = [];
var brick_wall = [];
var change = 3;
cam_pos = 0;
var grayscale = false;
var rect;
var rect2;
var ply;
var coins = [];
var wedges = [];
var trains = [];
var jumping_rods = [];
var jumping_boots = [];
var count = 0;
var gameover = false;
var setup = true;
var success = false;
var count1 = 0;
var shaderProgram;
var scorecanvas = document.getElementById("score");
var ctx = scorecanvas.getContext("2d");
ctx.font= "10px Arial";
main();



//
// Start here
//
function main() {

    document.onkeydown = checkKey;

    // If we don't have a GL context, give up now

    if (!gl) {
        alert('Unable to initialize WebGL. Your browser or machine may not support it.');
        return;
    }

    // window.addEventListener('keydown', function(event) { Key.onKeydown(event); }, false);

    // Vertex shader program

    const vsSource = `
    attribute vec4 aVertexPosition;
    attribute vec4 aVertexColor;

    uniform mat4 uMVPMatrix;

    varying lowp vec4 vColor;

    void main(void) {
      gl_Position = uMVPMatrix * aVertexPosition;
      vColor = aVertexColor;
    }
  `;

    const vsSrc2 = `
        attribute vec4 aVertexPosition;
        attribute vec2 aTextureCoord;
        
        uniform mat4 uMVPMatrix;
        
        varying highp vec2 vTextureCoord;
        
        void main(void) {
            gl_Position = uMVPMatrix * aVertexPosition;
            vTextureCoord = aTextureCoord;
        }
    `;

    const vsSrcBoth = `
        attribute vec4 aVertexPosition;
        attribute vec2 aTextureCoord;
        attribute vec4 aVertexColor;
        
        uniform mat4 uMVPMatrix;
        
        varying lowp vec4 vColor;
        varying highp vec2 vTextureCoord;
        
        void main(void) {
            gl_Position = uMVPMatrix * aVertexPosition;
            vTextureCoord = aTextureCoord;
            vColor = aVertexColor;
            }
    `;

    // Fragment shader program

    const fsSource = `
    varying lowp vec4 vColor;

    void main(void) {
      gl_FragColor = vColor;
    }
  `;

    const gsSource = `
    precision mediump float;
    varying vec2 vTextureCoord;
    varying lowp vec4 vColor;
    uniform sampler2D u_texture;
    void main(void) {
      lowp vec4 Color = vec4(128.0/256.0,128.0/256.0,128.0/256.0,1.0);
      gl_FragColor =   Color * vColor * texture2D(u_texture, vTextureCoord);
    }
    `;  

    const fsSrc2 = `
        varying highp vec2 vTextureCoord;
        
        uniform sampler2D uSampler;
        void main(void) {
            gl_FragColor = texture2D(uSampler, vTextureCoord);
        }
    `;

    const fsSrcboth = `
        varying highp vec2 vTextureCoord;
        varying lowp vec4 vColor;
        uniform sampler2D uSampler;
        
    void main(void) {
      gl_FragColor = texture2D(uSampler, vTextureCoord) * vColor;
    }
    `;

    const fsSrcgray = `
        varying highp vec2 vTextureCoord;
        varying lowp vec4 vColor;
        uniform sampler2D uSampler;
        
    void main(void) {
        highp vec4 texturecolor = texture2D(uSampler, vTextureCoord) * vColor;
        highp float grey = dot(texturecolor.rgb,vec3(0.299,0.587,0.114));
        gl_FragColor =  vec4(vec3(grey),1);
    }
    `;
    // Initialize a shader program; this is where all the lighting
    // for the vertices and so forth is established.
    var shaderProgram = initShaderProgram(gl, vsSrcBoth, fsSrcboth);
    const shaderProgramColors = initShaderProgram(gl, vsSource, fsSource);

    // Collect all the info needed to use the shader program.
    // Look up which attributes our shader program is using
    // for aVertexPosition, aVevrtexColor and also
    // look up uniform locations.


    var programInfo1 = {
        program: shaderProgram,
        attribLocations: {
            vertexPosition: gl.getAttribLocation(shaderProgram, 'aVertexPosition'),
            vertexColor: gl.getAttribLocation(shaderProgram, 'aVertexColor'),
            textureCoord: gl.getAttribLocation(shaderProgram, 'aTextureCoord'),
        },
        uniformLocations: {
            MVPMatrix: gl.getUniformLocation(shaderProgram, 'uMVPMatrix'),
            uSampler: gl.getUniformLocation(shaderProgram, 'uSampler')
        },
    };

    var programInfo2 = {
        program: shaderProgram,
        attribLocations: {
            vertexPosition: gl.getAttribLocation(shaderProgram, 'aVertexPosition'),
            vertexColor: gl.getAttribLocation(shaderProgram, 'aVertexColor'),
            textureCoord: gl.getAttribLocation(shaderProgram, 'aTextureCoord'),
        },
        uniformLocations: {
            MVPMatrix: gl.getUniformLocation(shaderProgram, 'uMVPMatrix'),
            uSampler: gl.getUniformLocation(shaderProgram, 'uSampler')
        },
    };

    // Here's where we call the routine that builds all the
    // objects we'll be drawing.
    const buffers = initBuffers(gl);

    var then = 0;

    // Draw the scene repeatedly
    function render(now) {
        now *= 0.001;  // convert to seconds
        const deltaTime = now - then;
        then = now;

        if(success==true){
            succes();
        }
        else{
            drawScene(gl, programInfo1,programInfo2, buffers, deltaTime);
            if(gameover==false){
                flashing();
                tick();
            }
            else{
                over();
            }
        }
        
        requestAnimationFrame(render);
    }
    requestAnimationFrame(render);

    function change_gray(){
        if(grayscale){
            shaderProgram = initShaderProgram(gl, vsSrcBoth, fsSrcgray);
        }
        else{
            shaderProgram = initShaderProgram(gl, vsSrcBoth, fsSrcboth);
        }

        programInfo1 = {
            program: shaderProgram,
            attribLocations: {
                vertexPosition: gl.getAttribLocation(shaderProgram, 'aVertexPosition'),
                vertexColor: gl.getAttribLocation(shaderProgram, 'aVertexColor'),
                textureCoord: gl.getAttribLocation(shaderProgram, 'aTextureCoord'),
            },
            uniformLocations: {
                MVPMatrix: gl.getUniformLocation(shaderProgram, 'uMVPMatrix'),
                uSampler: gl.getUniformLocation(shaderProgram, 'uSampler')
            },
        };

    }

    function flashing(){
        if(count%2){
            shaderProgram = initShaderProgram(gl, vsSrcBoth, gsSource);
        }
        else{
            shaderProgram = initShaderProgram(gl, vsSrcBoth, fsSrcboth);
        }

        programInfo2 = {
            program: shaderProgram,
            attribLocations: {
                vertexPosition: gl.getAttribLocation(shaderProgram, 'aVertexPosition'),
                vertexColor: gl.getAttribLocation(shaderProgram, 'aVertexColor'),
                textureCoord: gl.getAttribLocation(shaderProgram, 'aTextureCoord'),
            },
            uniformLocations: {
                MVPMatrix: gl.getUniformLocation(shaderProgram, 'uMVPMatrix'),
                uSampler: gl.getUniformLocation(shaderProgram, 'uSampler')
            },
        };

    }
    function checkKey(e) {

        e = e || window.event;
      
        if (e.key == ' ') {
            // up arrow
            ply.jump = true;
            if(ply.ontrain){
                ply.ontrain_jump = true;
            }
            
        }
        else if (e.keyCode == '40') {
            // down arrow
            ply.dodge = true;
        }
        else if (e.keyCode == '37') {
           // left arrow
           if(ply.lane_index>0)
            ply.lane_index-=1;
        }
        else if (e.keyCode == '39') {
           // right arrow
           if(ply.lane_index<2)
               ply.lane_index+=1;
        }
        else if (e.key == 'g') {
            // right arrow
            grayscale = !grayscale;
            change_gray();
         }
        // console.log(e.keyCode);
    }
    
    function over(){
        if(setup){
            pol.center[2] = ply.center[2] + 10;
            pol.center[0] = ply.center[0];
        }
        setup = false;
        if(pol.center[2]>ply.center[2])
            pol.center[2] -=0.1;
    }
    
}

function succes(){
    // if(count1 < 320){
        // ply.score += 1;
        // count1++;
    // }
    ctx.clearRect(0,0,ctx.canvas.width,ctx.canvas.height);
    ctx.fillText("You WON::Score:: " + String(ply.score),0,20);

    // document.write("<body><h1>You Won. Your score :: " + toString(ply.score) + "</h1></body>");
}
function tick() {
    count += 1;
    cam_pos += game_speed;
    ply.center[2] +=game_speed;
    
    if(ply.center[2]<=-160){
        success = true;
    }
    if(ply.center[0]<-2.3+ply.lane_index*(2.4))
        ply.center[0]+=0.1;

    if(ply.center[0]>-2.3+ply.lane_index*(2.4))
        ply.center[0]-=0.1;
    
    
    if(ply.jump && !ply.jets){
        if(count - ply.count >= 300){
            ply.boots = false;
        }

        if(!ply.boots){
            if(ply.speedy==0 && ply.center[1]==0 && !ply.ontrain){
                ply.speedy = 2;
            }
            else if(ply.ontrain_jump){
                ply.speedy = 2;
                ply.ontrain_jump = false;
            }
        }
        else if(ply.boots){
            if(ply.speedy==0 && ply.center[1]==0){
                ply.speedy = 4;
            }
            else if(ply.ontrain_jump){
                ply.speedy = 4;
                ply.ontrain_jump = false;
            }
            

        }

        if(ply.speedy>0){
            ply.center[1]+=0.1;
            ply.speedy-=0.1;
        }
        else if(ply.center[1]>=0 && !ply.ontrain){
            ply.center[1]-=0.1;
        }

        if(ply.center[1]<=0){
            ply.jump = false;
            ply.center[1] = 0;
            ply.speedy = 0;
        }
        
    }
    else if(ply.jets){
        if(ply.center[1]<=5){
            ply.center[1] +=0.1;
        }
        if(ply.center[1]>=5){
            ply.center[1] = 5;
        }
        if(count - ply.count >=300){
            ply.jets = false;
            ply.jump = true;
            ply.speedy = 0;
        }
    }
    
    if(ply.dodge){
        if(ply.jump){
            ply.speedy = 0;
        }
        if(ply.center[1]==0 || ply.ontrain){
            if(ply.rotation>=90){
                change*=-1;
            } 
            ply.rotation+=change;
        }
        if(ply.rotation<=0){
            ply.dodge = false;
            change = 3;
            ply.rotaiton = 0;
        }
    }

    ctx.clearRect(0,0,ctx.canvas.width,ctx.canvas.height);

    for(let i=0;i<coins.length;i++){
        if(Math.abs(coins[i].center[2]-ply.center[2])<= coins[i].radius+ ply.depth){
            if(Math.abs(coins[i].center[1]-ply.center[1])<= coins[i].radius+ ply.height){
                if(Math.abs(coins[i].center[0]-ply.center[0])<= coins[i].radius+ ply.width){
                    ply.score += 1;
                    console.log(ply.score);
                    coins.splice(i,1);
                    i--;
                    break;
                }
            }
        }
    }


    for(i=0;i<jumping_rods.length;i++){
        if(Math.abs(jumping_rods[i].center[2]-ply.center[2])<= jumping_rods[i].depth+ ply.depth){
            if(Math.abs(jumping_rods[i].center[1]-ply.center[1])<= jumping_rods[i].height+ ply.height){
                if(Math.abs(jumping_rods[i].center[0]-ply.center[0])<= jumping_rods[i].width+ ply.width){
                    ply.jets = true;
                    ply.confused = 0;
                    game_speed = -0.1;
                    ply.count = count;
                    ply.score +=1;
                    console.log(ply.score);
                   jumping_rods.splice(i,1);
                    i--;
                    break;
                }
            }
        }        
    }

    for(i=0;i<jumping_boots.length;i++){
        if(Math.abs(jumping_boots[i].center[2]-ply.center[2])<= jumping_boots[i].depth+ ply.depth){
            if(Math.abs(jumping_boots[i].center[1]-ply.center[1])<= jumping_boots[i].height+ ply.height){
                if(Math.abs(jumping_boots[i].center[0]-ply.center[0])<= jumping_boots[i].width+ ply.width){
                    ply.boots = true;
                    ply.count = count;
                    ply.score +=1;
                    console.log(ply.score);
                   jumping_boots.splice(i,1);
                    i--;
                    break;
                }
            }
        }        
    }

    if(!ply.jets){
        for(i=0;i<wedges.length;i++){
            if(Math.abs(wedges[i].center[2]-ply.center[2])<= wedges[i].depth + ply.depth){
                if(Math.abs(wedges[i].center[1]-ply.center[1])<=wedges[i].height + ply.height){
                    if(Math.abs(wedges[i].center[0]-ply.center[0])<= wedges[i].width + ply.width){
                        if(ply.rotation<=45){
                            console.log("game over");
                            gameover = true;
                        }
                        break;
                    }
                    else if(Math.abs(Math.abs(wedges[i].center[0]-ply.center[0])-wedges[i].width - ply.width)<=0.1){
                        ply.confused +=1;
                        if(ply.confused==1){
                            ply.count = count;
                            game_speed /=2;
                        }
                        ply.lane_index -=1*((wedges[i].center[0]-ply.center[0])/Math.abs(wedges[i].center[0]-ply.center[0]));
                        break;
                    }
                }
            }        
        }
    

    
        ply.ontrain = false;
        for(let i=0;i<trains.length;i++){
            if(Math.abs(trains[i].center[2]-ply.center[2])<= trains[i].depth+ ply.depth){
                if(Math.abs(trains[i].center[1]-ply.center[1])< trains[i].height+ ply.height){
                    if(Math.abs(trains[i].center[0]-ply.center[0])<= trains[i].width+ ply.width){
                        console.log("game over");
                            gameover = true;
                        // trains.splice(i,1);
                        // i--;
                        break;
                    }
                    else if(Math.abs(Math.abs(trains[i].center[0]-ply.center[0])-trains[i].width - ply.width)<=0.1){
                        ply.confused +=1;
                        if(ply.confused==1){
                            ply.count = count;
                            game_speed /=2;
                        }
                        ply.lane_index -=1*((trains[i].center[0]-ply.center[0])/Math.abs(trains[i].center[0]-ply.center[0]));
                        break;
                    }
                }
                else if(Math.abs(Math.abs(trains[i].center[1]-ply.center[1]) - (trains[i].height+ ply.height))<=0.1){
                    if(Math.abs(trains[i].center[0]-ply.center[0])<= trains[i].width+ ply.width){
                        ply.ontrain = true;
                        console.log("true");
                        break;
                    }
                }
            }
        }
    }

    if(ply.confused>=2){
        gameover = true;
    }

    if(count - ply.count >=600){
        game_speed = -0.1;
        ply.confused = 0;
    }
    if(gameover){
        ctx.fillText("GAME OVER::SCORE:: " + String(ply.score),0,20);
    }
    else{
        ctx.fillText("Score:: " + String(ply.score),0,20);
    }
}

//
// initBuffers
//
function initBuffers(gl) {

    
    let img = 'rail.jpg';
    for (let i=0;i<200;i++) {
        rect_track.push(new Rectangle(2,2, new vec3.fromValues(0, -2.5, 4-2*i), img));
        rect_track[rect_track.length - 1].rotate(-90, X_AXIS, ORIGIN);
        rect_track.push(new Rectangle(2,2, new vec3.fromValues(-3, -2.5, 4-2*i), img));
        rect_track[rect_track.length-1].rotate(-90, X_AXIS, ORIGIN);
        rect_track.push(new Rectangle(2,2, new vec3.fromValues(3, -2.5, 4-2*i), img));
        rect_track[rect_track.length-1].rotate(-90, X_AXIS, ORIGIN);
    }

    img = 'wall.png';
    for (let i=0;i<200;i++) {
        brick_wall.push(new Cuboid(vec3.fromValues(6,-0.7,4-2*i), 1,1,1, '', img));
        brick_wall.push(new Cuboid(vec3.fromValues(-6,-0.7,4-2*i),1,1, 1, '',img));
    }
    img = 'runner.jpeg';
    ply = new Player(vec3.fromValues(1,0,-6),2,2,1, '', img);
    img = 'police.png';
    pol= new Police(vec3.fromValues(0.1,0,-1),2,2,1,'', img);

    img = 'coin.jpg';
    for(i=0;i<30;i++){
        ind = i%3;
        coins.push(new Coin(new vec3.fromValues(-2.3+ind*(2.4),1,-5*i),2,2,2, '', img));
        coins.push(new Coin(new vec3.fromValues(-2.3+ind*(2.4),0,-5*i+1),2,2,2, '', img));
        coins.push(new Coin(new vec3.fromValues(-2.3+ind*(2.4),1,-5*i+2),2,2,2, '', img));
        coins.push(new Coin(new vec3.fromValues(-2.3+ind*(2.4),2,-5*i+2),2,2,2, '', img));

    }
    for(i=0;i<30;i++){
        ind = (i)%3;
        wedges.push(new Obstacle1(new vec3.fromValues(-2.3+ind*(2.4),0,-5*i+1),2,2,2, 'sd'));
    }

    img = 'train-front.jpg';
    for(i=0;i<8;i++){
        ind = (i+2)%3;
        trains.push(new Train(new vec3.fromValues(-2.3+ind*(2.4),0,-20*i),2,2,2,'', img));
    }

    img = 'jumping_rod.webp';
    for(i=0;i<3;i++){
        ind = (i+1)%3;
        jumping_rods.push(new Jumping_rod(new vec3.fromValues(-2.3+ind*(2.4),0,-30*(i+1)-20),2,2,2,'', img));
    }

    img = 'jumping_boots.jpg';
    for(i=0;i<3;i++){
        ind = (i)%3;
        jumping_boots.push(new Shoes(new vec3.fromValues(-2.3+ind*(2.4),0,-30*(i+1)-20),2,2,2,'', img));
    }

}

//
// Draw the scene.
//
function drawScene(gl, programInfo1,programInfo2, buffers, deltaTime) {
    resize();
    let backgroundColor = COLORS_0_1.SKY_BLUE;
    gl.clearColor(backgroundColor[0], backgroundColor[1], backgroundColor[2], 1.0);  // Clear to black, fully opaque
    gl.clearDepth(1.0);                 // Clear everything
    gl.enable(gl.DEPTH_TEST);           // Enable depth testing
    gl.depthFunc(gl.LEQUAL);            // Near things obscure far things

    // Clear the canvas before we start drawing on it.

    gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);

    // and 100 units away from the camera.

    const fieldOfView = 45 * Math.PI / 180;   // in radians
    const aspect = gl.canvas.clientWidth / gl.canvas.clientHeight;
    const zNear = 0.1;
    const zFar = 50.0;
    const projectionMatrix = mat4.create();

    // note: glmatrix.js always has the first argument
    // as the destination to receive the result.
    mat4.perspective(projectionMatrix,
        fieldOfView,
        aspect,
        zNear,
        zFar);

    // Set the drawing position to the "identity" point, which is
    // the center of the scene.
    const modelViewMatrix = mat4.create();
    const viewMatrix = mat4.create();
    // temp_vector = vec3.create();

    // Now move the drawing position a bit to where we want to
    // start drawing the square.

    mat4.lookAt(viewMatrix, vec3.fromValues(0, 4, 5+cam_pos), vec3.fromValues(0,0,cam_pos-10), vec3.fromValues(0,1,0));

    const VP = mat4.create();
    mat4.multiply(VP, projectionMatrix, viewMatrix);
    //Write your code to Rotate the cube here//

    gl.useProgram(programInfo1.program);

    for (let i=0;i<track.length;i++) {
        // track[i].draw(programInfo1, VP);
    }
    for (let i=0;i<rect_track.length;i++) {
        rect_track[i].draw(programInfo1, VP);
    }

    // cuboid.draw(programInfo1, VP);
    ply.draw(programInfo1, VP);
    pol.draw(programInfo1, VP);
    // c1.draw(programInfo1, VP);
    for(i=0;i<coins.length;i++){
        coins[i].draw(programInfo1,VP);
    }
    for(i=0;i<wedges.length;i++){
        wedges[i].draw(programInfo1,VP);
    }

    for(i=0;i<trains.length;i++){
        trains[i].draw(programInfo1,VP);
    }
    for(i=0;i<jumping_rods.length;i++){
        jumping_rods[i].draw(programInfo1,VP);
    }

    for(i=0;i<jumping_boots.length;i++){
        jumping_boots[i].draw(programInfo1,VP);
    }

    gl.useProgram(programInfo2.program);

    for (let i=0;i<brick_wall.length; i++) {
        // console.log('came');
        brick_wall[i].draw(programInfo2, VP);
    }
}

//
// Initialize a shader program, so WebGL knows how to draw our data
//
function initShaderProgram(gl, vsSource, fsSource) {
    const vertexShader = loadShader(gl, gl.VERTEX_SHADER, vsSource);
    const fragmentShader = loadShader(gl, gl.FRAGMENT_SHADER, fsSource);

    // Create the shader program

    const shaderProgram = gl.createProgram();
    gl.attachShader(shaderProgram, vertexShader);
    gl.attachShader(shaderProgram, fragmentShader);
    gl.linkProgram(shaderProgram);

    // If creating the shader program failed, alert

    if (!gl.getProgramParameter(shaderProgram, gl.LINK_STATUS)) {
        alert('Unable to initialize the shader program: ' + gl.getProgramInfoLog(shaderProgram));
        return null;
    }

    return shaderProgram;
}

//
// creates a shader of the given type, uploads the source and
// compiles it.
//
function loadShader(gl, type, source) {
    const shader = gl.createShader(type);

    // Send the source to the shader object

    gl.shaderSource(shader, source);

    // Compile the shader program

    gl.compileShader(shader);

    // See if it compiled successfully

    if (!gl.getShaderParameter(shader, gl.COMPILE_STATUS)) {
        alert('An error occurred compiling the shaders: ' + gl.getShaderInfoLog(shader));
        gl.deleteShader(shader);
        return null;
    }

    return shader;
}
