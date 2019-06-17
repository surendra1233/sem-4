

class Rectangle {
    constructor(height, width, position, textureImage) {
        this.height = height;
        this.width = width;
        const x = this.width / 2;
        const y = this.height / 2;
        this.position = position;
        let vertex_buffer_data = [
            x, y, 1,
            -x,y, 1,
            -x,-y, 1,
            x, -y, 1
        ];

        const faceColors2 = [
            [0.5,  0.5,  0.5,  1.0],    // Left face: purple
        ];
        const faceColors = [
            [1.0,  1.0,  1.0,  1.0],    // Left face: purple
        ];
        const textureCoordinates = [
            // Front
            0.0,  0.0,
            1.0,  0.0,
            1.0,  1.0,
            0.0,  1.0,
            // // Back
        ];


        let colors = [];
        for (var j = 0; j < faceColors.length; ++j) {
            const c = faceColors[j];

            // Repeat each color four times for the four vertices of the face
            colors = colors.concat(c, c, c, c);
        }
        const indices = [
            0,  1,  2,      0,  2,  3,    // front
        ];
        this.texture = loadTexture(gl,textureImage);
        this.modelMatrix = mat4.create();
        mat4.translate(this.modelMatrix, this.modelMatrix, this.position);
        this.vao = create3DObjectBoth(vertex_buffer_data, indices, textureCoordinates, colors, 6);
    }
    draw(programInfo, VP) {
        var MVPMatrix = mat4.create();
        mat4.multiply(MVPMatrix, VP, this.modelMatrix);
        gl.uniformMatrix4fv(
            programInfo.uniformLocations.MVPMatrix,
            false,
            MVPMatrix);
        draw3DObjectBoth(programInfo, this.vao, this.texture)
    }

    rotate(angle, axis, point) {
        angle = angle * (22/7) / 180;
        let pos= vec3.create();
        vec3.negate(pos, this.position);
        mat4.rotate(this.modelMatrix, this.modelMatrix, angle, axis);
    }
}