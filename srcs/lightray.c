/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lightray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrasset <fgrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 14:19:12 by lfabbian          #+#    #+#             */
/*   Updated: 2023/07/24 14:25:54 by fgrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minirt.h"

// // Fonction pour calculer l'éclairage selon le modèle de réflexion de Phong
// t_color phong_lighting(t_inter intersection, t_v3d viewer_position, t_light light, double ambient_intensity, double diffuse_intensity, double specular_intensity, double shininess) {
//     // Direction du rayon vers la source lumineuse
//     t_v3d light_direction;
//     light_direction.x = light.position.x - intersection.point.x;
//     light_direction.y = light.position.y - intersection.point.y;
//     light_direction.z = light.position.z - intersection.point.z;
//     double light_distance = sqrt(light_direction.x * light_direction.x + light_direction.y * light_direction.y + light_direction.z * light_direction.z);
//     light_direction.x /= light_distance;
//     light_direction.y /= light_distance;
//     light_direction.z /= light_distance;

//     // Calcul de l'angle d'incidence entre la normale de surface et la direction de la lumière
//     double cos_theta = light_direction.x * intersection.normal.x + light_direction.y * intersection.normal.y + light_direction.z * intersection.normal.z;
//     if (cos_theta < 0.0) {
//         // Le point est dans l'ombre, retourner la couleur ambiante uniquement
//         return intersection.c;
//     }

//     // Calcul de la direction du rayon réfléchi (pour la composante spéculaire)
//     t_v3d reflection_direction;
//     reflection_direction.x = 2.0 * cos_theta * intersection.normal.x - light_direction.x;
//     reflection_direction.y = 2.0 * cos_theta * intersection.normal.y - light_direction.y;
//     reflection_direction.z = 2.0 * cos_theta * intersection.normal.z - light_direction.z;

//     // Direction du rayon du spectateur (vers la caméra)
//     t_v3d viewer_direction;
//     viewer_direction.x = viewer_position.x - intersection.point.x;
//     viewer_direction.y = viewer_position.y - intersection.point.y;
//     viewer_direction.z = viewer_position.z - intersection.point.z;
//     double viewer_distance = sqrt(viewer_direction.x * viewer_direction.x + viewer_direction.y * viewer_direction.y + viewer_direction.z * viewer_direction.z);
//     viewer_direction.x /= viewer_distance;
//     viewer_direction.y /= viewer_distance;
//     viewer_direction.z /= viewer_distance;

//     // Calcul de l'angle entre le rayon réfléchi et le rayon du spectateur (pour la composante spéculaire)
//     double cos_alpha = reflection_direction.x * viewer_direction.x + reflection_direction.y * viewer_direction.y + reflection_direction.z * viewer_direction.z;

//     // Calcul des composantes diffuse et spéculaire de l'éclairage
//     t_color diffuse_color, specular_color;
//     diffuse_color.r = intersection.c.r * light.color.r * diffuse_intensity * cos_theta;
//     diffuse_color.g = intersection.c.g * light.color.g * diffuse_intensity * cos_theta;
//     diffuse_color.b = intersection.c.b * light.color.b * diffuse_intensity * cos_theta;

//     double specular_factor = pow(cos_alpha, shininess);
//     specular_color.r = light.color.r * specular_intensity * specular_factor;
//     specular_color.g = light.color.g * specular_intensity * specular_factor;
//     specular_color.b = light.color.b * specular_intensity * specular_factor;

//     // Calcul de la couleur d'éclairage finale (somme de l'éclairage ambiant, diffus et spéculaire)
//     t_color result;
//     result.r = intersection.c.r * ambient_intensity + diffuse_color.r + specular_color.r;
//     result.g = intersection.c.g * ambient_intensity + diffuse_color.g + specular_color.g;
//     result.b = intersection.c.b * ambient_intensity + diffuse_color.b + specular_color.b;

//     // Assurer que les valeurs de couleur restent dans la plage [0, 1]
//     result.r = fmax(0.0, fmin(1.0, result.r));
//     result.g = fmax(0.0, fmin(1.0, result.g));
//     result.b = fmax(0.0, fmin(1.0, result.b));

//     return result;
// }
