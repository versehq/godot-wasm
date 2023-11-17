#include "wasm.h"

#define SHIMDECL(funcName) static wasm_trap_t* funcName(void* env, const wasm_val_vec_t* args, wasm_val_vec_t* results);

namespace godot
{
    class WasmShimNode3D
    {
        public:
            
            // void set_transform(const Transform3D& local);
            SHIMDECL(set_transform)

            // Transform3D get_transform() const;
            SHIMDECL(get_transform)

            // void set_position(const Vector3& position);
            SHIMDECL(set_position)

            // Vector3 get_position() const;
            SHIMDECL(get_position)

            // void set_rotation(const Vector3& euler_radians);
            SHIMDECL(set_rotation)

            // Vector3 get_rotation() const;
            SHIMDECL(get_rotation)

            // void set_rotation_degrees(const Vector3& euler_degrees);
            SHIMDECL(set_rotation_degrees)

            // Vector3 get_rotation_degrees() const;
            SHIMDECL(get_rotation_degrees)

            // void set_rotation_order(EulerOrder order);
            SHIMDECL(set_rotation_order)

            // EulerOrder get_rotation_order() const;
            SHIMDECL(get_rotation_order)

            // void set_rotation_edit_mode(Node3D::RotationEditMode edit_mode);
            SHIMDECL(set_rotation_edit_mode)
            
            // Node3D::RotationEditMode get_rotation_edit_mode() const;
            SHIMDECL(get_rotation_edit_mode)

            // void set_scale(const Vector3& scale);
            SHIMDECL(set_scale)

            // Vector3 get_scale() const;
            SHIMDECL(get_scale)

            // void set_quaternion(const Quaternion& quaternion);
            SHIMDECL(set_quaternion)

            // Quaternion get_quaternion() const;
            SHIMDECL(get_quaternion)

            // void set_basis(const Basis& basis);
            SHIMDECL(set_basis)
            
            // Basis get_basis() const;
            SHIMDECL(get_basis)
            
            // void set_global_transform(const Transform3D& global);
            SHIMDECL(set_global_transform)

            // Transform3D get_global_transform() const;
            SHIMDECL(get_global_transform)

            // void set_global_position(const Vector3& position);
            SHIMDECL(set_global_position)

            // Vector3 get_global_position() const;
            SHIMDECL(get_global_position)

            // void set_global_rotation(const Vector3& euler_radians);
            SHIMDECL(set_global_rotation)

            // Vector3 get_global_rotation() const;
            SHIMDECL(get_global_rotation)

            // void set_global_rotation_degrees(const Vector3& euler_degrees);
            SHIMDECL(set_global_rotation_degrees)

            // Vector3 get_global_rotation_degrees() const;
            SHIMDECL(get_global_rotation_degrees)

            // Node3D* get_parent_node_3d() const;
            SHIMDECL(get_parent_node_3d)

            // void set_ignore_transform_notification(bool enabled);
            SHIMDECL(set_ignore_transform_notification)
            
            // void set_as_top_level(bool enable);
            SHIMDECL(set_as_top_level)

            // bool is_set_as_top_level() const;
            SHIMDECL(is_set_as_top_level)

            // void set_disable_scale(bool disable);
            SHIMDECL(set_disable_scale)

            // bool is_scale_disabled() const;
            SHIMDECL(is_scale_disabled)

            // TODO
            // Ref<World3D> get_world_3d() const;

            // void force_update_transform();
            SHIMDECL(force_update_transform)

            // TODO
            // void set_visibility_parent(const NodePath& path);
            // NodePath get_visibility_parent() const;

            // void update_gizmos();
            SHIMDECL(update_gizmos)

            // TODO
            // void add_gizmo(const Ref<Node3DGizmo>& gizmo);
            // TypedArray<Node3DGizmo> get_gizmos() const;

            // void clear_gizmos();
            SHIMDECL(clear_gizmos)

            // TODO
            // void set_subgizmo_selection(const Ref<Node3DGizmo>& gizmo, int32_t id, const Transform3D& transform);
            
            // void clear_subgizmo_selection();
            SHIMDECL(clear_subgizmo_selection)

            // void set_visible(bool visible);
            SHIMDECL(set_visible)

            // bool is_visible() const;
            SHIMDECL(is_visible)

            // bool is_visible_in_tree() const;
            SHIMDECL(is_visible_in_tree)

            // void show();
            SHIMDECL(show)

            // void hide();
            SHIMDECL(hide)

            // void set_notify_local_transform(bool enable);
            SHIMDECL(set_notify_local_transform)

            // bool is_local_transform_notification_enabled() const;
            SHIMDECL(is_local_transform_notification_enabled)

            // void set_notify_transform(bool enable);
            SHIMDECL(set_notify_transform)

            // bool is_transform_notification_enabled() const;
            SHIMDECL(is_transform_notification_enabled)

            // void rotate(const Vector3& axis, double angle);
            SHIMDECL(rotate)
            
            // void global_rotate(const Vector3& axis, double angle);
            SHIMDECL(global_rotate)
            
            // void global_scale(const Vector3& scale);
            SHIMDECL(global_scale)

            // void global_translate(const Vector3& offset);
            SHIMDECL(global_translate)

            // void rotate_object_local(const Vector3& axis, double angle);
            SHIMDECL(rotate_object_local)

            // void scale_object_local(const Vector3& scale);
            SHIMDECL(scale_object_local)

            // void translate_object_local(const Vector3& offset);
            SHIMDECL(translate_object_local)

            // void rotate_x(double angle);
            SHIMDECL(rotate_x)
            
            // void rotate_y(double angle);
            SHIMDECL(rotate_y)
            
            // void rotate_z(double angle);
            SHIMDECL(rotate_z)

            // void translate(const Vector3& offset);
            SHIMDECL(translate)
            
            // void orthonormalize();
            SHIMDECL(orthonormalize)
            
            // void set_identity();
            SHIMDECL(set_identity)

            // void look_at(const Vector3& target, const Vector3& up = Vector3(0, 1, 0), bool use_model_front = false);
            SHIMDECL(look_at)

            // void look_at_from_position(const Vector3& position, const Vector3& target, const Vector3& up = Vector3(0, 1, 0), bool use_model_front = false);
            SHIMDECL(look_at_from_position)

            // Vector3 to_local(const Vector3& global_point) const;
            SHIMDECL(to_local)

            // Vector3 to_global(const Vector3& local_point) const;
            SHIMDECL(to_global)
    };
}
