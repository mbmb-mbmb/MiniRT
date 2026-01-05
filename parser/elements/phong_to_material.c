#include "../../minirt.h"

void	phong_to_material(t_material *material)
{
	material->ambient = MATERIAL_AMBIENT;
	material->diffuse = MATERIAL_DIFFUSE;
	material->specular = MATERIAL_SPECULAR;
	material->shininess = MATERIAL_SHININESS;
}
