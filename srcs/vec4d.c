#include "../incs/minirt.h"

const t_v3d VEC3_UP = {0, 1, 0};

vec4 vec4_new(double x, double y, double z, double w) {
    vec4 v = {x, y, z, w};
    return v;
}

vec4 vec4_from_v3d(t_v3d v, double w) {
    return vec4_new(v.x, v.y, v.z, w);
}

t_v3d vec4_to_v3d(vec4 v) {
    t_v3d result = {v.x, v.y, v.z};
    return result;
}



mat4 mat4_identity(void) {
    mat4 m = {0};
    for (int i = 0; i < 4; ++i) {
        m.m[i][i] = 1;
    }
    return m;
}

mat4 mat4_translation(t_v3d t) {
    mat4 m = mat4_identity();
    m.m[0][3] = t.x;
    m.m[1][3] = t.y;
    m.m[2][3] = t.z;
    return m;
}

vec4 mat4_mul_vec4(mat4 m, vec4 v) {
    vec4 result = {0, 0, 0, 0};
    result.x = m.m[0][0] * v.x + m.m[0][1] * v.y + m.m[0][2] * v.z + m.m[0][3] * v.w;
    result.y = m.m[1][0] * v.x + m.m[1][1] * v.y + m.m[1][2] * v.z + m.m[1][3] * v.w;
    result.z = m.m[2][0] * v.x + m.m[2][1] * v.y + m.m[2][2] * v.z + m.m[2][3] * v.w;
    result.w = m.m[3][0] * v.x + m.m[3][1] * v.y + m.m[3][2] * v.z + m.m[3][3] * v.w;

    return result;
}


mat4 get_view_transform(t_camera cam)
{
    // Create the basis vectors of the camera
    t_v3d forward = normalize(cam.ori);  // Assuming the orientation is where camera is looking at
    t_v3d right = normalize(cross(forward, VEC3_UP));
    t_v3d up = cross(right, forward);

    // Create the view transformation matrix
    mat4 view;
    view.m[0][0] = right.x;
    view.m[0][1] = right.y;
    view.m[0][2] = right.z;
    view.m[0][3] = 0;
    view.m[1][0] = up.x;
    view.m[1][1] = up.y;
    view.m[1][2] = up.z;
    view.m[1][3] = 0;
    view.m[2][0] = -forward.x;
    view.m[2][1] = -forward.y;
    view.m[2][2] = -forward.z;
    view.m[2][3] = 0;
    view.m[3][0] = -dot_product(right, cam.coord);
    view.m[3][1] = -dot_product(up, cam.coord);
    view.m[3][2] = dot_product(forward, cam.coord);
    view.m[3][3] = 1;

    return view;
}


