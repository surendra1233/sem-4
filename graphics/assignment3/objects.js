class Shoes {
    constructor(center, width, height, depth, color, textureImage = WHITE_TEXTURE) {
        this.center = center;
        this.height = 0.3;
        this.width = 0.25;
        this.depth = 0.25;
        this.color = color;
        this.rotation = 0;

        this.texture = loadTexture(gl, textureImage);
        const vertex_buffer_data = [
            -0.25, -0.3, 0.25,
             0.25, -0.3, 0.25,
             0.25, 0.3, 0.25,
             -0.25, 0.3, 0.25,
             //Back Face
             -0.25, -0.3, -0.25,
             0.25, -0.3, -0.25,
             0.25, 0.3, -0.25,
             -0.25, 0.3, -0.25,
             //Top Face
             -0.25, 0.3, -0.25,
             0.25, 0.3, -0.25,
             0.25, 0.3, 0.25,
             -0.25, 0.3, 0.25,
             //Bottom Face
             -0.25, -0.3, -0.25,
             0.25, -0.3, -0.25,
             0.25, -0.3, 0.25,
             -0.25, -0.3, 0.25,
             //Left Face
             -0.25, -0.3, -0.25,
             -0.25, 0.3, -0.25,
             -0.25, 0.3, 0.25,
             -0.25, -0.3, 0.25,
             //Right Face
             0.25, -0.3, -0.25,
             0.25, 0.3, -0.25,
             0.25, 0.3, 0.25,
             0.25, -0.3, 0.25,
        ];

        
        const faceColors = [
            [1.0,  1.0,  1.0,  1.0],    // Front face: white
            [1.0,  0.0,  0.0,  1.0],    // Back face: red
            [0.0,  1.0,  0.0,  1.0],    // Top face: green
            [0.0,  0.0,  1.0,  1.0],    // Bottom face: blue
            [1.0,  1.0,  0.0,  1.0],    // Right face: yellow
            [1.0,  0.0,  1.0,  1.0],    // Left face: purple
        ];

        const textureCoordinates = [
            // Front
            0.9,  0.9,
            0.1,  0.9,
            0.1,  0.1,
            0.9,  0.1,
            // Back
            0.0,  0.0,
            1.0,  0.0,
            1.0,  1.0,
            0.0,  1.0,
            // Top
            0.0,  0.0,
            1.0,  0.0,
            1.0,  1.0,
            0.0,  1.0,
            // Bottom
            0.0,  0.0,
            1.0,  0.0,
            1.0,  1.0,
            0.0,  1.0,
            // Right
            0.0,  0.0,
            1.0,  0.0,
            1.0,  1.0,
            0.0,  1.0,
            // Left
            0.0,  0.0,
            1.0,  0.0,
            1.0,  1.0,
            0.0,  1.0,
        ];
        var colors = [];


        for (var j = 0; j < faceColors.length; ++j) {
            const c = faceColors[j];

            // Repeat each color four times for the four vertices of the face
            colors = colors.concat(c, c, c, c);
        }

        const indices = [
            0,  1,  2,      0,  2,  3,    // front
            4,  5,  6,      4,  6,  7,    // back
            8,  9,  10,     8,  10, 11,   // top
            12, 13, 14,     12, 14, 15,   // bottom
            16, 17, 18,     16, 18, 19,   // right
            20, 21, 22,     20, 22, 23,   // left
        ];


        this.vao = create3DObjectBoth(vertex_buffer_data, indices, textureCoordinates, colors, 36);
        this.modelMatrix = mat4.create();
    }
    
    draw(programInfo, VP) {
        var MVPMatrix = mat4.create();
        mat4.translate(MVPMatrix, this.modelMatrix, this.center);

        mat4.multiply(MVPMatrix, VP, MVPMatrix);
        gl.uniformMatrix4fv(
            programInfo.uniformLocations.MVPMatrix,
            false,
            MVPMatrix);
        draw3DObjectBoth(programInfo, this.vao, this.texture)
    }
}



class Jumping_rod{
    constructor(center, width, height, depth, color, textureImage = WHITE_TEXTURE) {
        this.center = center;
        this.height = 1;
        this.width = 0.5;
        this.depth = 0.5;
        this.color = color;


        this.texture = loadTexture(gl, textureImage);
        const vertex_buffer_data = [
            -0.5, -1, 0.5,
             0.5, -1, 0.5,
             0.5, 1, 0.5,
             -0.5, 1, 0.5,
             //Back Face
             -0.5, -1, -0.5,
             0.5, -1, -0.5,
             0.5, 1, -0.5,
             -0.5, 1, -0.5,
             //Top Face
             -0.5, 1, -0.5,
             0.5, 1, -0.5,
             0.5, 1, 0.5,
             -0.5, 1, 0.5,
             //Bottom Face
             -0.5, -1, -0.5,
             0.5, -1, -0.5,
             0.5, -1, 0.5,
             -0.5, -1, 0.5,
             //Left Face
             -0.5, -1, -0.5,
             -0.5, 1, -0.5,
             -0.5, 1, 0.5,
             -0.5, -1, 0.5,
             //Right Face
             0.5, -1, -0.5,
             0.5, 1, -0.5,
             0.5, 1, 0.5,
             0.5, -1, 0.5,
        ];

        
        const faceColors = [
            [1.0,  1.0,  1.0,  1.0],    // Front face: white
            [1.0,  1.0,  1.0,  1.0],    // Back face: red
            [1.0,  1.0,  1.0,  1.0],    // Top face: green
            [1.0,  1.0,  1.0,  1.0],    // Bottom face: blue
            [1.0,  1.0,  1.0,  1.0],    // Right face: yellow
            [1.0,  1.0,  1.0,  1.0],    // Left face: purple
        ];

        const textureCoordinates = [
            // Front
            1,  1.0,
            0,  1.0,
            0,  0.0,
            1,  0.0,
            // Back
            0,  1.0,
            0,  0.0,
            1.0,  0.0,
            1.0,  1.0,
            // Top
            0,  1.0,
            0,  0.0,
            1.0,  0.0,
            1.0,  1.0,
            // Bottom
            0,  1.0,
            0,  0.0,
            1.0,  0.0,
            1.0,  1.0,
            // Right
            0,  1.0,
            0,  0.0,
            1.0,  0.0,
            1.0,  1.0,
            // Left
            0,  1.0,
            0,  0.0,
            1.0,  0.0,
            1.0,  1.0,
        ];
        var colors = [];


        for (var j = 0; j < faceColors.length; ++j) {
            const c = faceColors[j];

            // Repeat each color four times for the four vertices of the face
            colors = colors.concat(c, c, c, c);
        }

        const indices = [
            0,  1,  2,      0,  2,  3,    // front
            4,  5,  6,      4,  6,  7,    // back
            8,  9,  10,     8,  10, 11,   // top
            12, 13, 14,     12, 14, 15,   // bottom
            16, 17, 18,     16, 18, 19,   // right
            20, 21, 22,     20, 22, 23,   // left
        ];

        // const ind = [
        //   0, 1, 2,   0, 2, 3,  //front
        //   4,5,6,     4,7,6, // back
        //    1,5,0,   0, 4, 5, //top
        //    2,3,6,    3,7,6, // bottom
        //    1,2,6,    1,5,6, //left
        //     0,3,7,  0,4,7
        // ];
        // this.vao = create3DObject(vertex_buffer_data, indices, 36, colors);

        this.vao = create3DObjectBoth(vertex_buffer_data, indices, textureCoordinates, colors, 36);
        this.modelMatrix = mat4.create();
    }
    
    draw(programInfo, VP) {
        var MVPMatrix = mat4.create();
        mat4.translate(MVPMatrix, this.modelMatrix, this.center);

        mat4.multiply(MVPMatrix, VP, MVPMatrix);
        gl.uniformMatrix4fv(
            programInfo.uniformLocations.MVPMatrix,
            false,
            MVPMatrix);
        draw3DObjectBoth(programInfo, this.vao, this.texture)
    }
}



class Train{
    constructor(center, width, height, depth, color, textureImage = WHITE_TEXTURE) {
        this.center = center;
        this.height = 1;
        this.width = 0.5;
        this.depth = 5;
        this.color = color;


        this.texture = loadTexture(gl, textureImage);
        const vertex_buffer_data = [
            -0.5, -1, 5,
             0.5, -1, 5,
             0.5, 1, 5,
             -0.5, 1, 5,
             //Back Face
             -0.5, -1, -5,
             0.5, -1, -5,
             0.5, 1, -5,
             -0.5, 1, -5,
             //Top Face
             -0.5, 1, -5,
             0.5, 1, -5,
             0.5, 1, 5,
             -0.5, 1, 5,
             //Bottom Face
             -0.5, -1, -5,
             0.5, -1, -5,
             0.5, -1, 5,
             -0.5, -1, 5,
             //Left Face
             -0.5, -1, -5,
             -0.5, 1, -5,
             -0.5, 1, 5,
             -0.5, -1, 5,
             //Right Face
             0.5, -1, -5,
             0.5, 1, -5,
             0.5, 1, 5,
             0.5, -1, 5,
        ];

        
        const faceColors = [
            [1.0,  1.0,  1.0,  1.0],    // Front face: white
            [1.0,  1.0,  1.0,  1.0],    // Back face: red
            [1.0,  1.0,  1.0,  1.0],    // Top face: green
            [1.0,  1.0,  1.0,  1.0],    // Bottom face: blue
            [1.0,  1.0,  1.0,  1.0],    // Right face: yellow
            [1.0,  1.0,  1.0,  1.0],    // Left face: purple
        ];

        const textureCoordinates = [
            // Front
            0.3,  0.0,
            1.0,  0.0,
            1.0,  1.0,
            0.3,  1.0,
            // Back
            0,  1.0,
            0,  0.0,
            1.0,  0.0,
            1.0,  1.0,
            // Top
            0,  1.0,
            0,  0.0,
            1.0,  0.0,
            1.0,  1.0,
            // Bottom
            0,  1.0,
            0,  0.0,
            1.0,  0.0,
            1.0,  1.0,
            // Right
            0,  1.0,
            0,  0.0,
            1.0,  0.0,
            1.0,  1.0,
            // Left
            0,  1.0,
            0,  0.0,
            1.0,  0.0,
            1.0,  1.0,
        ];
        var colors = [];


        for (var j = 0; j < faceColors.length; ++j) {
            const c = faceColors[j];

            // Repeat each color four times for the four vertices of the face
            colors = colors.concat(c, c, c, c);
        }

        const indices = [
            0,  1,  2,      0,  2,  3,    // front
            4,  5,  6,      4,  6,  7,    // back
            8,  9,  10,     8,  10, 11,   // top
            12, 13, 14,     12, 14, 15,   // bottom
            16, 17, 18,     16, 18, 19,   // right
            20, 21, 22,     20, 22, 23,   // left
        ];

        // const ind = [
        //   0, 1, 2,   0, 2, 3,  //front
        //   4,5,6,     4,7,6, // back
        //    1,5,0,   0, 4, 5, //top
        //    2,3,6,    3,7,6, // bottom
        //    1,2,6,    1,5,6, //left
        //     0,3,7,  0,4,7
        // ];
        // this.vao = create3DObject(vertex_buffer_data, indices, 36, colors);

        this.vao = create3DObjectBoth(vertex_buffer_data, indices, textureCoordinates, colors, 36);
        this.modelMatrix = mat4.create();
    }
    
    draw(programInfo, VP) {
        var MVPMatrix = mat4.create();
        mat4.translate(MVPMatrix, this.modelMatrix, this.center);

        mat4.multiply(MVPMatrix, VP, MVPMatrix);
        gl.uniformMatrix4fv(
            programInfo.uniformLocations.MVPMatrix,
            false,
            MVPMatrix);
        draw3DObjectBoth(programInfo, this.vao, this.texture);
    }
}

class Obstacle1 {
    constructor(center, width, height, depth, color, textureImage = WHITE_TEXTURE) {
        this.center = center;
        this.height = 0.25;
        this.width = 0.6;
        this.depth = 0.1;
        this.color = color;
        
        this.rotation = 0;


        this.texture = loadTexture(gl, textureImage);
        const vertex_buffer_data = [
            0.6, -0.25, 0.5-0.5,
            0.5, -0.25, 0.5-0.5,
            0.5, 0.25, 0.5-0.5,
            0.6, 0.25, 0.5-0.5,
            //Back Fac-0.5e
            0.6, -0.25, 0.6-0.5,
            0.5, -0.25, 0.6-0.5,
            0.5, 0.25, 0.6-0.5,
            0.6, 0.25, 0.6-0.5,
            //Top Fac-0.5e
            0.6, 0.25, 0.6-0.5,
            0.5, 0.25, 0.6-0.5,
            0.5, 0.25, 0.5-0.5,
            0.6, 0.25, 0.5-0.5,
            //Bottom Fac-0.5e
            0.6, -0.25, 0.6-0.5,
            0.5, -0.25, 0.6-0.5,
            0.5, -0.25, 0.5-0.5,
            0.6, -0.25, 0.5-0.5,
            //Left Fac-0.5e
            0.6, -0.25, 0.6-0.5,
            0.6, 0.25, 0.6-0.5,
            0.6, 0.25, 0.5-0.5,
            0.6, -0.25, 0.5-0.5,
            //Right Fac-0.5e
            0.5, -0.25, 0.6-0.5,
            0.5, 0.25, 0.6-0.5,
            0.5, 0.25, 0.5-0.5,
            0.5, -0.25, 0.5-0.5,

             -0.5, -0.25, -0.5+0.6,
             -0.6, -0.25, -0.5+0.6,
             -0.6, 0.25, -0.5+0.6,
             -0.5, 0.25, -0.5+0.6,
             //Back Fac+0.6e
             -0.5, -0.25, -0.6+0.6,
             -0.6, -0.25, -0.6+0.6,
             -0.6, 0.25, -0.6+0.6,
             -0.5, 0.25, -0.6+0.6,
             //Top Fac+0.6e
             -0.5, 0.25, -0.6+0.6,
             -0.6, 0.25, -0.6+0.6,
             -0.6, 0.25, -0.5+0.6,
             -0.5, 0.25, -0.5+0.6,
             //Bottom Fac+0.6e
             -0.5, -0.25, -0.6+0.6,
             -0.6, -0.25, -0.6+0.6,
             -0.6, -0.25, -0.5+0.6,
             -0.5, -0.25, -0.5+0.6,
             //Left Fac+0.6e
             -0.5, -0.25, -0.6+0.6,
             -0.5, 0.25, -0.6+0.6,
             -0.5, 0.25, -0.5+0.6,
             -0.5, -0.25, -0.5+0.6,
             //Right Fac+0.6e
             -0.6, -0.25, -0.6+0.6,
             -0.6, 0.25, -0.6+0.6,
             -0.6, 0.25, -0.5+0.6,
             -0.6, -0.25, -0.5+0.6,

             -0.6, 0.3, 0.1,
             0.6, 0.3, 0.1,
             0.6, 0.25, 0.1,
             -0.6, 0.25, 0.1,
             //Back Face
             -0.6, 0.3, 0,
             0.6, 0.3, 0,
             0.6, 0.25, 0,
             -0.6, 0.25, 0,
             //Top Face
             -0.6, 0.25, 0,
             0.6, 0.25, 0,
             0.6, 0.25, 0.1,
             -0.6, 0.25, 0.1,
             //Bottom Face
             -0.6, 0.3, 0,
             0.6, 0.3, 0,
             0.6, 0.3, 0.1,
             -0.6, 0.3, 0.1,
             //Left Face
             -0.6, 0.3, 0,
             -0.6, 0.25, 0,
             -0.6, 0.25, 0.1,
             -0.6, 0.3, 0.1,
             //Right Face
             0.6, 0.3, 0,
             0.6, 0.25, 0,
             0.6, 0.25, 0.1,
             0.6, 0.3, 0.1,
        ];

        
        const faceColors = [
            [1.0,  1.0,  1.0,  1.0],    // Front face: white
            [1.0,  0.0,  0.0,  1.0],    // Back face: red
            [0.0,  1.0,  0.0,  1.0],    // Top face: green
            [0.0,  0.0,  1.0,  1.0],    // Bottom face: blue
            [1.0,  1.0,  0.0,  1.0],    // Right face: yellow
            [1.0,  0.0,  1.0,  1.0],    // Left face: purple 
            [1.0,  1.0,  1.0,  1.0],    // Front face: white
            [1.0,  0.0,  0.0,  1.0],    // Back face: red
            [0.0,  1.0,  0.0,  1.0],    // Top face: green
            [0.0,  0.0,  1.0,  1.0],    // Bottom face: blue
            [1.0,  1.0,  0.0,  1.0],    // Right face: yellow
            [1.0,  0.0,  1.0,  1.0],    // Left face: purple
            [1.0,  1.0,  1.0,  1.0],    // Front face: white
            [1.0,  0.0,  0.0,  1.0],    // Back face: red
            [0.0,  1.0,  0.0,  1.0],    // Top face: green
            [0.0,  0.0,  1.0,  1.0],    // Bottom face: blue
            [1.0,  1.0,  0.0,  1.0],    // Right face: yellow
            [1.0,  0.0,  1.0,  1.0],    // Left face: purple
        ];

        const textureCoordinates = [
            // Front
            0.0,  0.0,
            1.0,  0.0,
            1.0,  1.0,
            0.0,  1.0,
            // Back
            0.0,  0.0,
            1.0,  0.0,
            1.0,  1.0,
            0.0,  1.0,
            // Top
            0.0,  0.0,
            1.0,  0.0,
            1.0,  1.0,
            0.0,  1.0,
            // Bottom
            0.0,  0.0,
            1.0,  0.0,
            1.0,  1.0,
            0.0,  1.0,
            // Right
            0.0,  0.0,
            1.0,  0.0,
            1.0,  1.0,
            0.0,  1.0,
            // Left
            0.0,  0.0,
            1.0,  0.0,
            1.0,  1.0,
            0.0,  1.0,
            0.0,  0.0,
            1.0,  0.0,
            1.0,  1.0,
            0.0,  1.0,
            // Back
            0.0,  0.0,
            1.0,  0.0,
            1.0,  1.0,
            0.0,  1.0,
            // Top
            0.0,  0.0,
            1.0,  0.0,
            1.0,  1.0,
            0.0,  1.0,
            // Bottom
            0.0,  0.0,
            1.0,  0.0,
            1.0,  1.0,
            0.0,  1.0,
            // Right
            0.0,  0.0,
            1.0,  0.0,
            1.0,  1.0,
            0.0,  1.0,
            // Left
            0.0,  0.0,
            1.0,  0.0,
            1.0,  1.0,
            0.0,  1.0,
            0.0,  0.0,
            1.0,  0.0,
            1.0,  1.0,
            0.0,  1.0,
            // Back
            0.0,  0.0,
            1.0,  0.0,
            1.0,  1.0,
            0.0,  1.0,
            // Top
            0.0,  0.0,
            1.0,  0.0,
            1.0,  1.0,
            0.0,  1.0,
            // Bottom
            0.0,  0.0,
            1.0,  0.0,
            1.0,  1.0,
            0.0,  1.0,
            // Right
            0.0,  0.0,
            1.0,  0.0,
            1.0,  1.0,
            0.0,  1.0,
            // Left
            0.0,  0.0,
            1.0,  0.0,
            1.0,  1.0,
            0.0,  1.0,
        ];
        var colors = [];


        for (var j = 0; j < faceColors.length; ++j) {
            const c = faceColors[j];

            // Repeat each color four times for the four vertices of the face
            colors = colors.concat(c, c, c, c);
        }

        const indices = [
            0,  1,  2,      0,  2,  3,    // front
            4,  5,  6,      4,  6,  7,    // back
            8,  9,  10,     8,  10, 11,   // top
            12, 13, 14,     12, 14, 15,   // bottom
            16, 17, 18,     16, 18, 19,   // right
            20, 21, 22,     20, 22, 23,   // left
            0+24,  1+24,  2+24,      0+24,  2+24,  3+24,    // front
            4+24,  5+24,  6+24,      4+24,  6+24,  7+24,    // back
            8+24,  9+24,  10+24,     8+24,  10+24, 11+24,   // top
            12+24, 13+24, 14+24,     12+24, 14+24, 15+24,   // bottom
            16+24, 17+24, 18+24,     16+24, 18+24, 19+24,   // right
            20+24, 21+24, 22+24,     20+24, 22+24, 23+24,   // left
            0+48,  1+48,  2+48,      0+48,  2+48,  3+48,    // front
            4+48,  5+48,  6+48,      4+48,  6+48,  7+48,    // back
            8+48,  9+48,  10+48,     8+48,  10+48, 11+48,   // top
            12+48, 13+48, 14+48,     12+48, 14+48, 15+48,   // bottom
            16+48, 17+48, 18+48,     16+48, 18+48, 19+48,   // right
            20+48, 21+48, 22+48,     20+48, 22+48, 23+48,   // left
        ];

        // const ind = [
        //   0, 1, 2,   0, 2, 3,  //front
        //   4,5,6,     4,7,6, // back
        //    1,5,0,   0, 4, 5, //top
        //    2,3,6,    3,7,6, // bottom
        //    1,2,6,    1,5,6, //left
        //     0,3,7,  0,4,7
        // ];
        // this.vao = create3DObject(vertex_buffer_data, indices, 36, colors);

        this.vao = create3DObjectBoth(vertex_buffer_data, indices, textureCoordinates, colors, 36*3);
        this.modelMatrix = mat4.create();
    }
    
    draw(programInfo, VP) {
        var MVPMatrix = mat4.create();
        mat4.translate(MVPMatrix, this.modelMatrix, this.center);
        mat4.rotate(MVPMatrix,MVPMatrix,this.rotation,[0, 1, 0]);

        mat4.multiply(MVPMatrix, VP, MVPMatrix);
        gl.uniformMatrix4fv(
            programInfo.uniformLocations.MVPMatrix,
            false,
            MVPMatrix);
        draw3DObjectBoth(programInfo, this.vao, this.texture)
    }
}

class Player {
    constructor(center, width, height, depth, color, textureImage = WHITE_TEXTURE) {
        this.center = center;
        this.height = 0.5;
        this.width = 0.36;
        this.depth = 0.1;
        this.color = color;
        this.score = 0;
        this.rotation = 0;
        this.jump = false;
        this.dodge = false;
        this.lane_index = 1;
        this.speedy = 0;
        this.jet = false;
        this.boots = false;
        this.ontrain = false;
        this.ontrain_jump = false;
        this.confused = 0;
        this.count = 0;
        this.texture = loadTexture(gl, textureImage);
        const vertex_buffer_data = [
            //head-------
            -0.075, 0.35,  0.1,
            0.075, 0.35,  0.1,
            0.075,  0.5,  0.1,
            -0.075,  0.5,  0.1,

            // Back face
            -0.075, 0.35, 0.0,
            -0.075,  0.5, 0.0,
            0.075,  0.5, 0.0,
            0.075, 0.35, 0.0,

            // Top face
            -0.075,  0.5, 0.0,
            -0.075,  0.5,  0.1,
            0.075,  0.5,  0.1,
            0.075,  0.5, 0.0,

            // Bottom face
            -0.075, 0.35, 0.0,
            0.075, 0.35, 0.0,
            0.075, 0.35,  0.1,
            -0.075, 0.35,  0.1,

            // Right face
            0.075, 0.35, 0.0,
            0.075,  0.5, 0.0,
            0.075,  0.5,  0.1,
            0.075, 0.35,  0.1,

            // Left face
            -0.075, 0.35, 0.0,
            -0.075, 0.35,  0.1,
            -0.075,  0.5,  0.1,
            -0.075,  0.5, 0.0,

            //neck------------------

            -0.035, 0.25,  0.1,
            0.035, 0.25,  0.1,
            0.035,  0.35,  0.1,
            -0.035,  0.35,  0.1,

            // Back face
            -0.035, 0.25, 0.0,
            -0.035,  0.35, 0.0,
            0.035,  0.35, 0.0,
            0.035, 0.25, 0.0,

            // Top face
            -0.035,  0.35, 0.0,
            -0.035,  0.35,  0.1,
            0.035,  0.35,  0.1,
            0.035,  0.35, 0.0,

            // Bottom face
            -0.035, 0.25, 0.0,
            0.035, 0.25, 0.0,
            0.035, 0.25,  0.1,
            -0.035, 0.25,  0.1,

            // Right face
            0.035, 0.25, 0.0,
            0.035,  0.35, 0.0,
            0.035,  0.35,  0.1,
            0.035, 0.25,  0.1,

            // Left face
            -0.035, 0.25, 0.0,
            -0.035, 0.25,  0.1,
            -0.035,  0.35,  0.1,
            -0.035,  0.35, 0.0,

            // body --

            -0.125, 0.0,  0.1,
            0.125, 0.0,  0.1,
            0.125,  0.25,  0.1,
            -0.125,  0.25,  0.1,

            // Back face
            -0.125, 0.0, 0.0,
            -0.125,  0.25, 0.0,
            0.125,  0.25, 0.0,
            0.125, 0.0, 0.0,

            // Top face
            -0.125,  0.25, 0.0,
            -0.125,  0.25,  0.1,
            0.125,  0.25,  0.1,
            0.125,  0.25, 0.0,

            // Bottom face
            -0.125, 0.0, 0.0,
            0.125, 0.0, 0.0,
            0.125, 0.0,  0.1,
            -0.125, 0.0,  0.1,

            // Right face
            0.125, 0.0, 0.0,
            0.125,  0.25, 0.0,
            0.125,  0.25,  0.1,
            0.125, 0.0,  0.1,

            // Left face
            -0.125, 0.0, 0.0,
            -0.125, 0.0,  0.1,
            -0.125,  0.25,  0.1,
            -0.125,  0.25, 0.0,

            // left leg

            -0.11, -0.25,  0.1,
            -0.05, -0.25,  0.1,
            -0.05,  0.0,  0.1,
            -0.11,  0.0,  0.1,

            // Back face
            -0.11, -0.25, 0.0,
            -0.11,  0.0, 0.0,
            -0.05,  0.0, 0.0,
            -0.05, -0.25, 0.0,

            // Top face
            -0.11,  0.0, 0.0,
            -0.11,  0.0,  0.1,
            -0.05,  0.0,  0.1,
            -0.05,  0.0, 0.0,

            // Bottom face
            -0.11, -0.25, 0.0,
            -0.05, -0.25, 0.0,
            -0.05, -0.25,  0.1,
            -0.11, -0.25,  0.1,

            // Right face
            -0.05, -0.25, 0.0,
            -0.05,  0.0, 0.0,
            -0.05,  0.0,  0.1,
            -0.05, -0.25,  0.1,

            // Left face
            -0.11, -0.25, 0.0,
            -0.11, -0.25,  0.1,
            -0.11,  0.0,  0.1,
            -0.11,  0.0, 0.0,

            // right leg

            0.11, -0.25,  0.1,
            0.05, -0.25,  0.1,
            0.05,  0.0,  0.1,
            0.11,  0.0,  0.1,

            // Back face
            0.11, -0.25, 0.0,
            0.11,  0.0, 0.0,
            0.05,  0.0, 0.0,
            0.05, -0.25, 0.0,

            // Top face
            0.11,  0.0, 0.0,
            0.11,  0.0,  0.1,
            0.05,  0.0,  0.1,
            0.05,  0.0, 0.0,

            // Bottom face
            0.11, -0.25, 0.0,
            0.05, -0.25, 0.0,
            0.05, -0.25,  0.1,
            0.11, -0.25,  0.1,

            // Right face
            0.05, -0.25, 0.0,
            0.05,  0.0, 0.0,
            0.05,  0.0,  0.1,
            0.05, -0.25,  0.1,

            // Left face
            0.11, -0.25, 0.0,
            0.11, -0.25,  0.1,
            0.11,  0.0,  0.1,
            0.11,  0.0, 0.0,

            //left hand-----
            -0.18, 0.0,  0.1,
            -0.14, 0.0,  0.1,
            -0.14,  0.25,  0.1,
            -0.18,  0.25,  0.1,

            // Back face
            -0.18, 0.0, 0.0,
            -0.18,  0.25, 0.0,
            -0.14,  0.25, 0.0,
            -0.14, 0.0, 0.0,

            // Top face
            -0.18,  0.25, 0.0,
            -0.18,  0.25,  0.1,
            -0.14,  0.25,  0.1,
            -0.14,  0.25, 0.0,

            // Bottom face
            
            -0.18, 0.0, 0.0,
            -0.14, 0.0, 0.0,
            -0.14, 0.0,  0.1,
            -0.18, 0.0,  0.1,

            // Right face
            -0.14, 0.0, 0.0,
            -0.14,  0.0, 0.0,
            -0.14,  0.0,  0.1,
            -0.14, 0.0,  0.1,

            // Left face
            -0.18, 0.0, 0.0,
            -0.18, 0.0,  0.1,
            -0.18,  0.25,  0.1,
            -0.18,  0.25, 0.0,

            //right hand
            0.18, 0.0,  0.1,
            0.14, 0.0,  0.1,
            0.14,  0.25,  0.1,
            0.18,  0.25,  0.1,

            // Back face
            0.18, 0.0, 0.0,
            0.18,  0.25, 0.0,
            0.14,  0.25, 0.0,
            0.14, 0.0, 0.0,

            // Top face
            0.18,  0.25, 0.0,
            0.18,  0.25,  0.1,
            0.14,  0.25,  0.1,
            0.14,  0.25, 0.0,

            // Bottom face
            
            0.18, 0.0, 0.0,
            0.14, 0.0, 0.0,
            0.14, 0.0,  0.1,
            0.18, 0.0,  0.1,

            // Right face
            0.14, 0.0, 0.0,
            0.14,  0.25, 0.0,
            0.14,  0.25,  0.1,
            0.14, 0.0,  0.1,

            // Left face
            0.18, 0.0, 0.0,
            0.18, 0.0,  0.1,
            0.18,  0.25,  0.1,
            0.18,  0.25, 0.0,

        ];

        
        var facecolors = [
            [1.0,  1.0,  1.0,  1.0],    // Front face: white
            [1.0,  0.0,  0.0,  1.0],    // Back face: red
            [0.0,  1.0,  0.0,  1.0],    // Top face: green
            [0.0,  0.0,  1.0,  1.0],    // Bottom face: blue
            [1.0,  1.0,  0.0,  1.0],    // Right face: yellow
            [1.0,  0.0,  1.0,  1.0],    // Left face: purple
        ];

        var faceColors = [];
        for(let i=0;i<7;i++){
            faceColors = faceColors.concat(facecolors);
        }

        var textureco= [
            // Front
            0.8,  0.3,
            0.2,  0.3,
            0.2,  0.1,
            0.8,  0.1,
            // Back
            0.0,  0.0,
            1.0,  0.0,
            1.0,  1.0,
            0.0,  1.0,
            // Top
            0.0,  0.0,
            1.0,  0.0,
            1.0,  1.0,
            0.0,  1.0,
            // Bottom
            0.0,  0.0,
            1.0,  0.0,
            1.0,  1.0,
            0.0,  1.0,
            // Right
            0.0,  0.0,
            1.0,  0.0,
            1.0,  1.0,
            0.0,  1.0,
            // Left
            0.0,  0.0,
            1.0,  0.0,
            1.0,  1.0,
            0.0,  1.0,
        ];
        var colors = [];
        var textureCoordinates = [];
        for(let i=0;i<7;i++)
            textureCoordinates = textureCoordinates.concat(textureco);
        for (var j = 0; j < faceColors.length; ++j) {
            const c = faceColors[j];

            // Repeat each color four times for the four vertices of the face
            colors = colors.concat(c, c, c, c);
        }

        var indices = [
            0,  1,  2,      0,  2,  3,    // front
            4,  5,  6,      4,  6,  7,    // back
            8,  9,  10,     8,  10, 11,   // top
            12, 13, 14,     12, 14, 15,   // bottom
            16, 17, 18,     16, 18, 19,   // right
            20, 21, 22,     20, 22, 23,   // left
        ];
        for(let i=0;i<36*6;i++)
            indices.push(indices[i]+24);

        // const ind = [
        //   0, 1, 2,   0, 2, 3,  //front
        //   4,5,6,     4,7,6, // back
        //    1,5,0,   0, 4, 5, //top
        //    2,3,6,    3,7,6, // bottom
        //    1,2,6,    1,5,6, //left
        //     0,3,7,  0,4,7
        // ];
        // this.vao = create3DObject(vertex_buffer_data, indices, 36, colors);

        this.vao = create3DObjectBoth(vertex_buffer_data, indices, textureCoordinates, colors, 36*7);
        this.modelMatrix = mat4.create();
    }
    
    draw(programInfo, VP) {
        var MVPMatrix = mat4.create();
        mat4.translate(MVPMatrix, this.modelMatrix, this.center);
        mat4.rotate(MVPMatrix,MVPMatrix,Math.PI*(this.rotation/180),[1, 0, 0]);

        mat4.multiply(MVPMatrix, VP, MVPMatrix);
        gl.uniformMatrix4fv(
            programInfo.uniformLocations.MVPMatrix,
            false,
            MVPMatrix);
        draw3DObjectBoth(programInfo, this.vao, this.texture)
    }
}

class Police {
    constructor(center, width, height, depth, color, textureImage = WHITE_TEXTURE) {
        this.center = center;
        this.height = 1;
        this.width = 0.72;
        this.depth = 0.2;
        this.color = color;
        this.score = 0;
        this.rotation = 0;
        this.jump = false;
        this.dodge = false;
        this.lane_index = 1;
        this.speedy = 0;
        this.jet = false;
        this.boots = false;
        this.ontrain = false;
        this.confused = 0;
        this.count = 0;
        this.texture = loadTexture(gl, textureImage);
        const vertex_buffer_data = [
            //head-------
            -0.075, 0.35,  0.1,
            0.075, 0.35,  0.1,
            0.075,  0.5,  0.1,
            -0.075,  0.5,  0.1,

            // Back face
            -0.075, 0.35, 0.0,
            -0.075,  0.5, 0.0,
            0.075,  0.5, 0.0,
            0.075, 0.35, 0.0,

            // Top face
            -0.075,  0.5, 0.0,
            -0.075,  0.5,  0.1,
            0.075,  0.5,  0.1,
            0.075,  0.5, 0.0,

            // Bottom face
            -0.075, 0.35, 0.0,
            0.075, 0.35, 0.0,
            0.075, 0.35,  0.1,
            -0.075, 0.35,  0.1,

            // Right face
            0.075, 0.35, 0.0,
            0.075,  0.5, 0.0,
            0.075,  0.5,  0.1,
            0.075, 0.35,  0.1,

            // Left face
            -0.075, 0.35, 0.0,
            -0.075, 0.35,  0.1,
            -0.075,  0.5,  0.1,
            -0.075,  0.5, 0.0,

            //neck------------------

            -0.035, 0.25,  0.1,
            0.035, 0.25,  0.1,
            0.035,  0.35,  0.1,
            -0.035,  0.35,  0.1,

            // Back face
            -0.035, 0.25, 0.0,
            -0.035,  0.35, 0.0,
            0.035,  0.35, 0.0,
            0.035, 0.25, 0.0,

            // Top face
            -0.035,  0.35, 0.0,
            -0.035,  0.35,  0.1,
            0.035,  0.35,  0.1,
            0.035,  0.35, 0.0,

            // Bottom face
            -0.035, 0.25, 0.0,
            0.035, 0.25, 0.0,
            0.035, 0.25,  0.1,
            -0.035, 0.25,  0.1,

            // Right face
            0.035, 0.25, 0.0,
            0.035,  0.35, 0.0,
            0.035,  0.35,  0.1,
            0.035, 0.25,  0.1,

            // Left face
            -0.035, 0.25, 0.0,
            -0.035, 0.25,  0.1,
            -0.035,  0.35,  0.1,
            -0.035,  0.35, 0.0,

            // body --

            -0.125, 0.0,  0.1,
            0.125, 0.0,  0.1,
            0.125,  0.25,  0.1,
            -0.125,  0.25,  0.1,

            // Back face
            -0.125, 0.0, 0.0,
            -0.125,  0.25, 0.0,
            0.125,  0.25, 0.0,
            0.125, 0.0, 0.0,

            // Top face
            -0.125,  0.25, 0.0,
            -0.125,  0.25,  0.1,
            0.125,  0.25,  0.1,
            0.125,  0.25, 0.0,

            // Bottom face
            -0.125, 0.0, 0.0,
            0.125, 0.0, 0.0,
            0.125, 0.0,  0.1,
            -0.125, 0.0,  0.1,

            // Right face
            0.125, 0.0, 0.0,
            0.125,  0.25, 0.0,
            0.125,  0.25,  0.1,
            0.125, 0.0,  0.1,

            // Left face
            -0.125, 0.0, 0.0,
            -0.125, 0.0,  0.1,
            -0.125,  0.25,  0.1,
            -0.125,  0.25, 0.0,

            // left leg

            -0.11, -0.25,  0.1,
            -0.05, -0.25,  0.1,
            -0.05,  0.0,  0.1,
            -0.11,  0.0,  0.1,

            // Back face
            -0.11, -0.25, 0.0,
            -0.11,  0.0, 0.0,
            -0.05,  0.0, 0.0,
            -0.05, -0.25, 0.0,

            // Top face
            -0.11,  0.0, 0.0,
            -0.11,  0.0,  0.1,
            -0.05,  0.0,  0.1,
            -0.05,  0.0, 0.0,

            // Bottom face
            -0.11, -0.25, 0.0,
            -0.05, -0.25, 0.0,
            -0.05, -0.25,  0.1,
            -0.11, -0.25,  0.1,

            // Right face
            -0.05, -0.25, 0.0,
            -0.05,  0.0, 0.0,
            -0.05,  0.0,  0.1,
            -0.05, -0.25,  0.1,

            // Left face
            -0.11, -0.25, 0.0,
            -0.11, -0.25,  0.1,
            -0.11,  0.0,  0.1,
            -0.11,  0.0, 0.0,

            // right leg

            0.11, -0.25,  0.1,
            0.05, -0.25,  0.1,
            0.05,  0.0,  0.1,
            0.11,  0.0,  0.1,

            // Back face
            0.11, -0.25, 0.0,
            0.11,  0.0, 0.0,
            0.05,  0.0, 0.0,
            0.05, -0.25, 0.0,

            // Top face
            0.11,  0.0, 0.0,
            0.11,  0.0,  0.1,
            0.05,  0.0,  0.1,
            0.05,  0.0, 0.0,

            // Bottom face
            0.11, -0.25, 0.0,
            0.05, -0.25, 0.0,
            0.05, -0.25,  0.1,
            0.11, -0.25,  0.1,

            // Right face
            0.05, -0.25, 0.0,
            0.05,  0.0, 0.0,
            0.05,  0.0,  0.1,
            0.05, -0.25,  0.1,

            // Left face
            0.11, -0.25, 0.0,
            0.11, -0.25,  0.1,
            0.11,  0.0,  0.1,
            0.11,  0.0, 0.0,

            //left hand-----
            -0.18, 0.0,  0.1,
            -0.14, 0.0,  0.1,
            -0.14,  0.25,  0.1,
            -0.18,  0.25,  0.1,

            // Back face
            -0.18, 0.0, 0.0,
            -0.18,  0.25, 0.0,
            -0.14,  0.25, 0.0,
            -0.14, 0.0, 0.0,

            // Top face
            -0.18,  0.25, 0.0,
            -0.18,  0.25,  0.1,
            -0.14,  0.25,  0.1,
            -0.14,  0.25, 0.0,

            // Bottom face
            
            -0.18, 0.0, 0.0,
            -0.14, 0.0, 0.0,
            -0.14, 0.0,  0.1,
            -0.18, 0.0,  0.1,

            // Right face
            -0.14, 0.0, 0.0,
            -0.14,  0.0, 0.0,
            -0.14,  0.0,  0.1,
            -0.14, 0.0,  0.1,

            // Left face
            -0.18, 0.0, 0.0,
            -0.18, 0.0,  0.1,
            -0.18,  0.25,  0.1,
            -0.18,  0.25, 0.0,

            //right hand
            0.18, 0.0,  0.1,
            0.14, 0.0,  0.1,
            0.14,  0.25,  0.1,
            0.18,  0.25,  0.1,

            // Back face
            0.18, 0.0, 0.0,
            0.18,  0.25, 0.0,
            0.14,  0.25, 0.0,
            0.14, 0.0, 0.0,

            // Top face
            0.18,  0.25, 0.0,
            0.18,  0.25,  0.1,
            0.14,  0.25,  0.1,
            0.14,  0.25, 0.0,

            // Bottom face
            
            0.18, 0.0, 0.0,
            0.14, 0.0, 0.0,
            0.14, 0.0,  0.1,
            0.18, 0.0,  0.1,

            // Right face
            0.14, 0.0, 0.0,
            0.14,  0.25, 0.0,
            0.14,  0.25,  0.1,
            0.14, 0.0,  0.1,

            // Left face
            0.18, 0.0, 0.0,
            0.18, 0.0,  0.1,
            0.18,  0.25,  0.1,
            0.18,  0.25, 0.0,

        ];

        for(let i =0;i<vertex_buffer_data.length;i++){
            vertex_buffer_data[i] *=2;
        }
        var facecolors = [
            [1.0,  1.0,  1.0,  1.0],    // Front face: white
            [1.0,  0.0,  0.0,  1.0],    // Back face: red
            [0.0,  1.0,  0.0,  1.0],    // Top face: green
            [0.0,  0.0,  1.0,  1.0],    // Bottom face: blue
            [1.0,  1.0,  0.0,  1.0],    // Right face: yellow
            [1.0,  0.0,  1.0,  1.0],    // Left face: purple
        ];

        var faceColors = [];
        for(let i=0;i<7;i++){
            faceColors = faceColors.concat(facecolors);
        }

        var textureco= [
            // Front
            0.2,  0.7,
            0.8,  0.7,
            0.8,  0.1,
            0.2,  0.1,
            // Back
            1.0,  1.0,
            0.0,  1.0,
            0.0,  0.0,
            1.0,  0.0,
            // Top
            0.0,  0.0,
            0.0,  0.0,
            0.0,  0.0,
            0.0,  0.0,
            // Bottom
            1.0,  1.0,
            0.0,  1.0,
            0.0,  0.0,
            1.0,  0.0,
            // Right
            1.0,  1.0,
            0.0,  1.0,
            0.0,  0.0,
            1.0,  0.0,
            // Left
            1.0,  1.0,
            0.0,  1.0,
            0.0,  0.0,
            1.0,  0.0,
        ];
        var colors = [];
        var textureCoordinates = [];
        
        
        for(let i=0;i<7;i++)
            textureCoordinates = textureCoordinates.concat(textureco);
        for (var j = 0; j < faceColors.length; ++j) {
            const c = faceColors[j];

            // Repeat each color four times for the four vertices of the face
            colors = colors.concat(c, c, c, c);
        }

        var indices = [
            0,  1,  2,      0,  2,  3,    // front
            4,  5,  6,      4,  6,  7,    // back
            8,  9,  10,     8,  10, 11,   // top
            12, 13, 14,     12, 14, 15,   // bottom
            16, 17, 18,     16, 18, 19,   // right
            20, 21, 22,     20, 22, 23,   // left
        ];
        for(let i=0;i<36*6;i++)
            indices.push(indices[i]+24);

        // const ind = [
        //   0, 1, 2,   0, 2, 3,  //front
        //   4,5,6,     4,7,6, // back
        //    1,5,0,   0, 4, 5, //top
        //    2,3,6,    3,7,6, // bottom
        //    1,2,6,    1,5,6, //left
        //     0,3,7,  0,4,7
        // ];
        // this.vao = create3DObject(vertex_buffer_data, indices, 36, colors);

        this.vao = create3DObjectBoth(vertex_buffer_data, indices, textureCoordinates, colors, 36*7);
        this.modelMatrix = mat4.create();
    }
    
    draw(programInfo, VP) {
        var MVPMatrix = mat4.create();
        mat4.translate(MVPMatrix, this.modelMatrix, this.center);
        // mat4.rotate(MVPMatrix,MVPMatrix,Math.PI*(this.rotation/180),[1, 0, 0]);

        mat4.multiply(MVPMatrix, VP, MVPMatrix);
        gl.uniformMatrix4fv(
            programInfo.uniformLocations.MVPMatrix,
            false,
            MVPMatrix);
        draw3DObjectBoth(programInfo, this.vao, this.texture)
    }
}
class Coin {
    constructor(center, width, height, depth, color, textureImage = WHITE_TEXTURE) {
        this.center = center;
        this.height = height;
        this.width = width;
        this.depth = depth;
        this.color = color;
        
        this.rotation = 0;

        this.texture = loadTexture(gl, textureImage);
        var vertex_buffer_data = []
        var vertexCount = 20;
        this.radius = 0.25;
        var indices = [];
        // vertex_buffer_data.push(0,0,0);
        for (var i = 0; i <9*vertexCount; i+=9)
        {
            vertex_buffer_data.push(0);
            vertex_buffer_data.push(0);
            vertex_buffer_data.push(0);
            vertex_buffer_data.push(this.radius * Math.cos((i / vertexCount) * 2.0 * Math.PI));
            vertex_buffer_data.push(this.radius * Math.sin((i / vertexCount) * 2.0 * Math.PI));
            vertex_buffer_data.push(0);
            vertex_buffer_data.push(this.radius * Math.cos(((i+1) / vertexCount) * 2.0 * Math.PI));
            vertex_buffer_data.push(this.radius * Math.sin(((i+1) / vertexCount) * 2.0 * Math.PI));
            vertex_buffer_data.push(0);
        }

        for(i=0;i<3*vertexCount;i++){
            indices.push(i);
        }

        var textureCoordinates = [];
        for(i=0;i<8*vertexCount;i++)
            textureCoordinates.push(0);


        var colors = [];
        var col = COLORS_0_1.GOLD;
        var c = [col[0],col[1],col[2],1];
        for (var j = 0; j <vertexCount;j++) {
            // Repeat each color four times for the four vertices of the face
            colors = colors.concat(c,c,c);
        }


        // const ind = [
        //   0, 1, 2,   0, 2, 3,  //front
        //   4,5,6,     4,7,6, // back
        //    1,5,0,   0, 4, 5, //top
        //    2,3,6,    3,7,6, // bottom
        //    1,2,6,    1,5,6, //left
        //     0,3,7,  0,4,7
        // ];
        // this.vao = create3DObject(vertex_buffer_data, indices, 36, colors);
        this.vao = create3DObjectBoth(vertex_buffer_data, indices, textureCoordinates, colors, 3*vertexCount);
        this.modelMatrix = mat4.create();
    }
    
    draw(programInfo, VP) {
        this.rotation += Math.PI / (((Math.random()) % 100) + 100);

        var MVPMatrix = mat4.create();
        mat4.translate(MVPMatrix, this.modelMatrix, this.center);

        mat4.rotate(MVPMatrix,MVPMatrix,this.rotation,[0, 1, 0]);
        mat4.multiply(MVPMatrix, VP, MVPMatrix);
        gl.uniformMatrix4fv(
            programInfo.uniformLocations.MVPMatrix,
            false,
            MVPMatrix);
        draw3DObjectBoth(programInfo, this.vao, this.texture)
    }
}