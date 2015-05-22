#version 330 core
// uniform mat4 MVP;
// uniform mat4 MODEL_MATRIX;
// uniform mat4 VIEW_MATRIX;
// uniform mat4 PROJECTION_MATRIX;
uniform float FOV;
uniform float WIN_WIDTH;
uniform float WIN_HEIGHT;
uniform float FAR_CLIPPING_PLANE;
uniform float NEAR_CLIPPING_PLANE;
uniform vec3 MODEL_POS;
uniform vec3 CAMERA_POS;
uniform vec3 CAMERA_LOOK_AT;
uniform vec3 CAMERA_HEAD_UP;
layout(location = 0) in vec3 vertex;

mat4 perspective(float fov, float ratio, float n, float f) {
    float cotfov = 1 / tan(fov / 2.0);
    mat4 result = mat4(
        cotfov / ratio,  0.0,    0.0,                     0.0,
        0.0,             cotfov, 0.0,                     0.0,
        0.0,             0.0,    -((f + n) / (f -n)),     -(1.0),
        0.0,             0.0,    -(2.0 * f * n) / (f -n), 0.0
    );
    return result;
}

mat4 look_at(const vec3 pos, vec3 look_at, vec3 up) {
    look_at = normalize(look_at - pos);
    up = normalize(up);
    vec3 right = normalize(cross(look_at, up));
    up = cross(right, look_at);

    mat4 result = mat4(
        right.x,          up.x,         -look_at.x,         0.0,
        right.y,          up.y,         -look_at.y,         0.0,
        right.z,          up.z,         -look_at.z,         0.0,
        -dot(right, pos), -dot(up, pos), dot(look_at, pos), 1.0
    );
    return result;
}

void main() {
    vec4 v = vec4(vertex, 1);
    mat4 model_matrix = mat4(
        1.0,         0.0,         0.0,         0.0,
        0.0,         1.0,         0.0,         0.0,
        0.0,         0.0,         1.0,         0.0,
        MODEL_POS.x, MODEL_POS.y, MODEL_POS.z, 1.0
    );
    mat4 view_matrix = look_at(CAMERA_POS, CAMERA_LOOK_AT, CAMERA_HEAD_UP);
    mat4 projection_matrix = perspective(
        FOV,
        WIN_WIDTH / WIN_HEIGHT,
        NEAR_CLIPPING_PLANE,
        FAR_CLIPPING_PLANE
    );
    gl_Position = projection_matrix * view_matrix * model_matrix * v;
}
