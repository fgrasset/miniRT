#include "../../incs/minirt.h"

t_mat4	mat4_identity(void) {
	int		i;
	t_mat4	m;

	i = 0;
	// m = {0};
	while (i < 4)
	{
		m.m[i][i] = 1;
		i++;
	}
	return (m);
}

t_mat4	mat4_translation(t_v3d t) {
	t_mat4 m;

	m = mat4_identity();
	m.m[0][3] = t.x;
	m.m[1][3] = t.y;
	m.m[2][3] = t.z;
	return (m);
}

t_mat4	get_view_transform(t_camera cam)
{
	// Create the basis vectors of the camera
	t_v3d	forward;
	t_v3d	right;
	t_v3d	up;
	t_v3d	constant;
	t_mat4	view;

	constant = new_v3d(0, 1, 0);
	forward = normalize(cam.ori);  // Assuming the orientation is where camera is looking at
	right = normalize(cross(forward, constant));
	up = cross(right, forward);
	// Create the view transformation matrix
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

	return (view);
}

t_v3d	mat4_mul_v3d(t_mat4 m, t_v3d v)
{
	t_v3d	result;
	double	w;

	result.x = m.m[0][0] * v.x + m.m[0][1] * v.y + m.m[0][2] * v.z + m.m[0][3];
	result.y = m.m[1][0] * v.x + m.m[1][1] * v.y + m.m[1][2] * v.z + m.m[1][3];
	result.z = m.m[2][0] * v.x + m.m[2][1] * v.y + m.m[2][2] * v.z + m.m[2][3];
	w = m.m[3][0] * v.x + m.m[3][1] * v.y + m.m[3][2] * v.z + m.m[3][3];

	if (w != 1.0 && w != 0.0){
		result.x /= w;
		result.y /= w;
		result.z /= w;
	}

	return (result);
}

