### 1. `intersect_world`

This function becomes the heart of your ray–object intersection logic.

- **Step 1: Function signature**
  - In `main.c`, define:
    - `t_intersection_list	intersect_world(t_system *sys, t_ray *ray);`

- **Step 2: Loop through all objects**
  - Create a master `t_intersection_list all_intersections = {0};`
  - Loop from `i = 0` to `i < sys->object_count` and for each:
    - `t_object			*obj = &sys->obj_list[i];`
    - `t_intersection_list	obj_intersections;`

- **Step 3: Intersect each object**
  - Transform the ray into the object’s local space (as in `ray_to_object_space`).
  - Based on `obj->type`, call the appropriate function and fill `obj_intersections`:
    - `SPHERE` → `intersect_sphere(obj, ray);`
    - later: `PLANE`, `CYLINDER`, etc.
  - Append `obj_intersections` to `all_intersections` using a helper:
    - `append_intersections(&all_intersections, &obj_intersections);`

- **Step 4: Sort intersections**
  - After the loop, sort `all_intersections` by `t` ascending:
    - `sort_intersections(&all_intersections);`
  - Return `all_intersections`.

- **Step 5: Generalize sphere intersection**
  - Adapt `intersect_unit_sphere` into a general `intersect_sphere`:
    - Transform world ray to object space:
      - `object_ray = inverse(sphere_transform) * world_ray;` (reuse `ray_to_object_space`)
    - Call `intersect_unit_sphere(object_ray, ...)`.
    - Use resulting `t` values directly (no extra transform needed).

---

### 2. `color_at`

This now uses `intersect_world` and a helper `hit()` to determine the visible object.

- **Step 1: Call `intersect_world`**
  - Replace the old hardcoded sphere intersection with:
    - `t_intersection_list	intersections = intersect_world(sys, ray);`

- **Step 2: Implement `hit` helper**
  - Purpose: find the closest visible intersection (\(t > 0\)).
  - Logic (pseudocode-style):

```c
t_intersection	*hit(t_intersection_list *intersections)
{
	t_intersection	*closest_hit;
	int				i;

	closest_hit = NULL;
	i = 0;
	while (i < intersections->count)
	{
		if (intersections->intersections[i].t > 0)
		{
			if (closest_hit == NULL
				|| intersections->intersections[i].t < closest_hit->t)
				closest_hit = &intersections->intersections[i];
		}
		i++;
	}
	return (closest_hit);
}
```

- **Step 3: Shade or background**
  - In `color_at`:
    - `t_intersection	*the_hit = hit(&intersections);`
    - If `the_hit != NULL`:
      - Use `the_hit->object` and `the_hit->t` with `prepare_shading_computations` and `lighting`.
    - Else:
      - Return background color, e.g. `create_color(0, 0, 0, 1);`

---

### 3. Camera View Transformation (`view_transform`)

This positions and orients the camera.

- **Step 1: Extend camera struct**
  - In `minirt.h`, in `t_camera`, add:
    - `t_mat	transform;`
    - `t_mat	inverse;`

- **Step 2: Implement `view_transform(from, to, up)`**
  - Math:
    - `forward = normalize(to - from)`
    - `left = cross_product(forward, normalize(up))`
    - `true_up = cross_product(left, forward)`
  - Orientation matrix \(M\):

\[
\begin{bmatrix}
\text{left.x} & \text{left.y} & \text{left.z} & 0 \\
\text{true\_up.x} & \text{true\_up.y} & \text{true\_up.z} & 0 \\
-\text{forward.x} & -\text{forward.y} & -\text{forward.z} & 0 \\
0 & 0 & 0 & 1
\end{bmatrix}
\]

  - Final view matrix:
    - `view_matrix = M * translation(-from.x, -from.y, -from.z);`
  - Use existing helpers: `normalize_vector`, `subtract_tuple`, `cross_product_tuple`, `translation`, `multiply_matrices`.

- **Step 3: Hook into parser**
  - In `rt_parser.c`, after parsing camera location/rotation:
    - Compute `from`, `to`, and `up` tuples.
    - `sys->camera.transform = view_transform(from, to, up);`
    - Also compute and store `sys->camera.inverse`.

---

### 4. `ray_for_pixel` (new camera model)

Replaces your old `camera_ray_for_pixel`.

- **Step 1: Pixel geometry**
  - Given `camera->fov`, `WIDTH`, `HEIGHT`:
    - `half_view = tan(degrees_to_radians(camera->fov) / 2.0);`
    - `aspect_ratio = (float)WIDTH / (float)HEIGHT;`
    - If `aspect_ratio >= 1`:
      - `half_width = half_view;`
      - `half_height = half_view / aspect_ratio;`
    - Else:
      - `half_width = half_view * aspect_ratio;`
      - `half_height = half_view;`
    - `pixel_size = (half_width * 2) / WIDTH;`

- **Step 2: Pixel world coordinates for (px, py)**
  - `world_x = half_width - (px + 0.5) * pixel_size;`
  - `world_y = half_height - (py + 0.5) * pixel_size;`

- **Step 3: Transform and build ray**
  - Camera looks along \(-Z\):
    - `pixel_on_canvas = create_point(world_x, world_y, -1);`
  - Transform with camera inverse:
    - `pixel_in_world = camera->inverse * pixel_on_canvas;`
    - `origin_in_world = camera->inverse * create_point(0, 0, 0);`
  - Direction:
    - `direction = normalize(pixel_in_world - origin_in_world);`
  - Result:
    - `return (create_ray(origin_in_world, direction));`
  - Implementation details:
    - Use `multiply_matrix_and_tuple`, `subtract_tuple`, `normalize_vector`.
    - Call this `ray_for_pixel` from your main `render()` loop instead of the old `camera_ray_for_pixel`.