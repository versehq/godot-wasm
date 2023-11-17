#include "wasmShimNode3d.h"
#include "defs.h"
#include "godot-wasm.h"
#include "../godot-cpp/gen/include/godot_cpp/classes/node3d.hpp"

// NOTE - copy of defines in wasi-shim.cpp. Move this somewhere shareable.
// See https://github.com/WebAssembly/wasi-libc/blob/main/libc-bottom-half/headers/public/wasi/api.h
#define __WASI_CLOCKID_REALTIME (UINT32_C(0)) // The clock measuring real time
#define __WASI_CLOCKID_MONOTONIC (UINT32_C(1)) // The store-wide monotonic clock
#define __WASI_ERRNO_SUCCESS (UINT16_C(0)) // No error occurred
#define __WASI_ERRNO_ACCES (UINT16_C(2)) // [sic] Permission denied
#define __WASI_ERRNO_INVAL (UINT16_C(28)) // Invalid argument
#define __WASI_ERRNO_IO (UINT16_C(29)) // I/O error

///////////////////////////////////////////////////////////////////////////
#define SHIM_BEGIN(numArgs, numResults) \
        FAIL_IF(args->size != numArgs || results->size != numResults, "Invalid arguments " __FUNCTION__, wasi_result(results, __WASI_ERRNO_INVAL, "Invalid arguments\0"));\
        Wasm* wasm = (Wasm*) env;\
        wasm_memory_t* memory = wasm->get_memory().ptr()->get_memory();\
        if (memory == NULL) return wasi_result(results, __WASI_ERRNO_IO, "Invalid memory\0");\
        byte_t* data = wasm_memory_data(memory);\
        uint64_t nodeID = args->data[0].of.i64;\
        Node3D* node = (Node3D*) ObjectDB::get_instance(ObjectID(nodeID));\
        if (node != NULL)\
        {

///////////////////////////////////////////////////////////////////////////
#define SHIM_END() \
        }\
        return NULL;


namespace godot
{
    ///////////////////////////////////////////////////////////////////////////
    // NOTE - copy of function in wasi-shim.cpp. Move this somewhere shareable.
    wasm_trap_t* wasi_result(wasm_val_vec_t* results, int32_t value = __WASI_ERRNO_SUCCESS, const char* message = nullptr)
    {
        results->data[0].kind = WASM_I32;
        results->data[0].of.i32 = value;
        if (value == __WASI_ERRNO_SUCCESS) return NULL;
        wasm_message_t trap_message;
        wasm_name_new_from_string_nt(&trap_message, message);
        return wasm_trap_new(NULL, &trap_message);
    }

    ///////////////////////////////////////////////////////////////////////////
    // void set_transform(const Transform3D& local);
    // (nodeID, transformMemoryOffset) [I64, I64] -> []
    wasm_trap_t* WasmShimNode3D::set_transform(void* env, const wasm_val_vec_t* args, wasm_val_vec_t* results)
    {
        SHIM_BEGIN(2, 0)
        uint64_t transformOffset = args->data[1].of.i64;
        Transform3D local = *((Transform3D*) (data + transformOffset));
        node->set_transform(local);
        SHIM_END()
    }

    ///////////////////////////////////////////////////////////////////////////
    // Transform3D get_transform() const;
    // (nodeID, transformMemoryOffset) [I64, I64] -> []
    wasm_trap_t* WasmShimNode3D::get_transform(void* env, const wasm_val_vec_t* args, wasm_val_vec_t* results)
    {
        SHIM_BEGIN(2, 0)
        uint64_t transformOffset = args->data[1].of.i64;
        Transform3D transform = node->get_transform();
        memcpy(data + transformOffset, &transform, sizeof(Transform3D));
        SHIM_END()
    }

    ///////////////////////////////////////////////////////////////////////////
    // void set_position(const Vector3& position);
    // (nodeID, posMemoryOffset) [I64, I64] -> []
    wasm_trap_t* WasmShimNode3D::set_position(void* env, const wasm_val_vec_t* args, wasm_val_vec_t* results)
    {
        SHIM_BEGIN(2, 0)
        uint64_t vecOffset = args->data[1].of.i64;
        Vector3 pos = *((Vector3*) (data + vecOffset));
        node->set_position(pos);
        SHIM_END()
    }

    ///////////////////////////////////////////////////////////////////////////
    // Vector3 get_position() const;
    // (nodeID, posMemoryOffset) [I64, I64] -> []
    wasm_trap_t* WasmShimNode3D::get_position(void* env, const wasm_val_vec_t* args, wasm_val_vec_t* results)
    {
        SHIM_BEGIN(2, 0)
        uint64_t vec3Offset = args->data[1].of.i64;
        Vector3 val = node->get_position();
        memcpy(data + vec3Offset, &val, sizeof(Vector3));
        SHIM_END()
    }

    ///////////////////////////////////////////////////////////////////////////
    // void set_rotation(const Vector3& euler_radians);
    // (nodeID, rotationMemoryOffset) [I64, I64] -> []
    wasm_trap_t* WasmShimNode3D::set_rotation(void* env, const wasm_val_vec_t* args, wasm_val_vec_t* results)
    {
        SHIM_BEGIN(2, 0)
        uint64_t vecOffset = args->data[1].of.i64;
        Vector3 val = *((Vector3*) (data + vecOffset));
        node->set_rotation(val);
        SHIM_END()
    }

    ///////////////////////////////////////////////////////////////////////////
    // Vector3 get_rotation() const;
    // (nodeID, rotationMemoryOffset) [I64, I64] -> []
    wasm_trap_t* WasmShimNode3D::get_rotation(void* env, const wasm_val_vec_t* args, wasm_val_vec_t* results)
    {
        SHIM_BEGIN(2, 0)
        uint64_t vec3Offset = args->data[1].of.i64;
        Vector3 val = node->get_rotation();
        memcpy(data + vec3Offset, &val, sizeof(Vector3));
        SHIM_END()
    }

    ///////////////////////////////////////////////////////////////////////////
    // void set_rotation_degrees(const Vector3& euler_degrees);
    // (nodeID, rotationMemoryOffset) [I64, I64] -> []
    wasm_trap_t* WasmShimNode3D::set_rotation_degrees(void* env, const wasm_val_vec_t* args, wasm_val_vec_t* results)
    {
        SHIM_BEGIN(2, 0)
        uint64_t vecOffset = args->data[1].of.i64;
        Vector3 val = *((Vector3*) (data + vecOffset));
        node->set_rotation_degrees(val);
        SHIM_END()
    }

    ///////////////////////////////////////////////////////////////////////////
    // Vector3 get_rotation_degrees() const;
    // (nodeID, rotationMemoryOffset) [I64, I64] -> []
    wasm_trap_t* WasmShimNode3D::get_rotation_degrees(void* env, const wasm_val_vec_t* args, wasm_val_vec_t* results)
    {
        SHIM_BEGIN(2, 0)
        uint64_t vec3Offset = args->data[1].of.i64;
        Vector3 val = node->get_rotation_degrees();
        memcpy(data + vec3Offset, &val, sizeof(Vector3));
        SHIM_END()
    }

    ///////////////////////////////////////////////////////////////////////////
    // void set_rotation_order(EulerOrder order);
    // (nodeID, order) [I64, I64] -> []
    wasm_trap_t* WasmShimNode3D::set_rotation_order(void* env, const wasm_val_vec_t* args, wasm_val_vec_t* results)
    {
        SHIM_BEGIN(2, 0)
        uint64_t order = args->data[1].of.i64;
        node->set_rotation_order((EulerOrder) order);
        SHIM_END()
    }

    ///////////////////////////////////////////////////////////////////////////
    // EulerOrder get_rotation_order() const;
    // (nodeID) [I64] -> [I32]
    wasm_trap_t* WasmShimNode3D::get_rotation_order(void* env, const wasm_val_vec_t* args, wasm_val_vec_t* results)
    {
        SHIM_BEGIN(1, 1)
        EulerOrder order = node->get_rotation_order();
        results->data[0].kind = WASM_I32;
        results->data[0].of.i32 = (int32_t) order;
        SHIM_END()
    }

    ///////////////////////////////////////////////////////////////////////////
    // void set_rotation_edit_mode(Node3D::RotationEditMode edit_mode);
    // (nodeID, edit_mode) [I64, I64] -> []
    wasm_trap_t* WasmShimNode3D::set_rotation_edit_mode(void* env, const wasm_val_vec_t* args, wasm_val_vec_t* results)
    {
        SHIM_BEGIN(2, 0)
        uint64_t edit_mode = args->data[1].of.i64;
        node->set_rotation_edit_mode((Node3D::RotationEditMode) edit_mode);
        SHIM_END()
    }

    ///////////////////////////////////////////////////////////////////////////
    // Node3D::RotationEditMode get_rotation_edit_mode() const;
    // (nodeID) [I64] -> [I32]
    wasm_trap_t* WasmShimNode3D::get_rotation_edit_mode(void* env, const wasm_val_vec_t* args, wasm_val_vec_t* results)
    {
        SHIM_BEGIN(1, 1)
        Node3D::RotationEditMode edit_mode = node->get_rotation_edit_mode();
        results->data[0].kind = WASM_I32;
        results->data[0].of.i32 = (int32_t) edit_mode;
        SHIM_END()
    }

    ///////////////////////////////////////////////////////////////////////////
    // void set_scale(const Vector3& scale);
    // (nodeID, scaleMemoryOffset) [I64, I64] -> []
    wasm_trap_t* WasmShimNode3D::set_scale(void* env, const wasm_val_vec_t* args, wasm_val_vec_t* results)
    {
        SHIM_BEGIN(2, 0)
        uint64_t scaleVecOffset = args->data[1].of.i64;
        Vector3 scale = *((Vector3*) (data + scaleVecOffset));
        node->set_scale(scale);
        SHIM_END()
    }

    ///////////////////////////////////////////////////////////////////////////
    // Vector3 get_scale() const;
    // (nodeID, scaleMemoryOffset) [I64, I64] -> []
    wasm_trap_t* WasmShimNode3D::get_scale(void* env, const wasm_val_vec_t* args, wasm_val_vec_t* results)
    {
        SHIM_BEGIN(2, 0)
        uint64_t scaleVecOffset = args->data[1].of.i64;
        Vector3 scale = node->get_scale();
        memcpy(data + scaleVecOffset, &scale, sizeof(Vector3));
        SHIM_END()
    }

    ///////////////////////////////////////////////////////////////////////////
    // void set_quaternion(const Quaternion& quaternion);
    // (nodeID, quaternionMemoryOffset) [I64, I64] -> []
    wasm_trap_t* WasmShimNode3D::set_quaternion(void* env, const wasm_val_vec_t* args, wasm_val_vec_t* results)
    {
        SHIM_BEGIN(2, 0)
        uint64_t quatOffset = args->data[1].of.i64;
        Quaternion q = *((Quaternion*) (data + quatOffset));
        node->set_quaternion(q);
        SHIM_END()
    }

    ///////////////////////////////////////////////////////////////////////////
    // Quaternion get_quaternion() const;
    // (nodeID, quaternionMemoryOffset) [I64, I64] -> []
    wasm_trap_t* WasmShimNode3D::get_quaternion(void* env, const wasm_val_vec_t* args, wasm_val_vec_t* results)
    {
        SHIM_BEGIN(2, 0)
        uint64_t quatOffset = args->data[1].of.i64;
        Quaternion q = node->get_quaternion();
        memcpy(data + quatOffset, &q, sizeof(Quaternion));
        SHIM_END()
    }

    ///////////////////////////////////////////////////////////////////////////
    // void set_basis(const Basis& basis);
    // (nodeID, basisMemoryOffset) [I64, I64] -> []
    wasm_trap_t* WasmShimNode3D::set_basis(void* env, const wasm_val_vec_t* args, wasm_val_vec_t* results)
    {
        SHIM_BEGIN(2, 0)
        uint64_t basisOffset = args->data[1].of.i64;
        Basis b = *((Basis*) (data + basisOffset));
        node->set_basis(b);
        SHIM_END()
    }

    ///////////////////////////////////////////////////////////////////////////
    // Basis get_basis() const;
    // (nodeID, basisMemoryOffset) [I64, I64] -> []
    wasm_trap_t* WasmShimNode3D::get_basis(void* env, const wasm_val_vec_t* args, wasm_val_vec_t* results)
    {
        SHIM_BEGIN(2, 0)
        uint64_t basisOffset = args->data[1].of.i64;
        Basis b = node->get_basis();
        memcpy(data + basisOffset, &b, sizeof(Basis));
        SHIM_END()
    }

    ///////////////////////////////////////////////////////////////////////////
    // void set_global_transform(const Transform3D& global);
    // (nodeID, transformMemoryOffset) [I64, I64] -> []
    wasm_trap_t* WasmShimNode3D::set_global_transform(void* env, const wasm_val_vec_t* args, wasm_val_vec_t* results)
    {
        SHIM_BEGIN(2, 0)
        uint64_t offset = args->data[1].of.i64;
        Transform3D t = *((Transform3D*) (data + offset));
        node->set_global_transform(t);
        SHIM_END()
    }

    ///////////////////////////////////////////////////////////////////////////
    // Transform3D get_global_transform() const;
    // (nodeID, transformMemoryOffset) [I64, I64] -> []
    wasm_trap_t* WasmShimNode3D::get_global_transform(void* env, const wasm_val_vec_t* args, wasm_val_vec_t* results)
    {
        SHIM_BEGIN(2, 0)
        uint64_t offset = args->data[1].of.i64;
        Transform3D t = node->get_global_transform();
        memcpy(data + offset, &t, sizeof(Transform3D));
        SHIM_END()
    }

    ///////////////////////////////////////////////////////////////////////////
    // void set_global_position(const Vector3& position);
    // (nodeID, positionMemoryOffset) [I64, I64] -> []
    wasm_trap_t* WasmShimNode3D::set_global_position(void* env, const wasm_val_vec_t* args, wasm_val_vec_t* results)
    {
        SHIM_BEGIN(2, 0)
        uint64_t offset = args->data[1].of.i64;
        Vector3 p = *((Vector3*) (data + offset));
        node->set_global_position(p);
        SHIM_END()
    }

    ///////////////////////////////////////////////////////////////////////////
    // Vector3 get_global_position() const;
    // (nodeID, positionMemoryOffset) [I64, I64] -> []
    wasm_trap_t* WasmShimNode3D::get_global_position(void* env, const wasm_val_vec_t* args, wasm_val_vec_t* results)
    {
        SHIM_BEGIN(2, 0)
        uint64_t offset = args->data[1].of.i64;
        Vector3 p = node->get_global_position();
        memcpy(data + offset, &p, sizeof(Vector3));
        SHIM_END()
    }

    ///////////////////////////////////////////////////////////////////////////
    // void set_global_rotation(const Vector3& euler_radians);
    // (nodeID, rotationMemoryOffset) [I64, I64] -> []
    wasm_trap_t* WasmShimNode3D::set_global_rotation(void* env, const wasm_val_vec_t* args, wasm_val_vec_t* results)
    {
        SHIM_BEGIN(2, 0)
        uint64_t offset = args->data[1].of.i64;
        Vector3 v = *((Vector3*) (data + offset));
        node->set_global_rotation(v);
        SHIM_END()
    }

    ///////////////////////////////////////////////////////////////////////////
    // Vector3 get_global_rotation() const;
    // (nodeID, rotationMemoryOffset) [I64, I64] -> []
    wasm_trap_t* WasmShimNode3D::get_global_rotation(void* env, const wasm_val_vec_t* args, wasm_val_vec_t* results)
    {
        SHIM_BEGIN(2, 0)
        uint64_t offset = args->data[1].of.i64;
        Vector3 v = node->get_global_rotation();
        memcpy(data + offset, &v, sizeof(Vector3));
        SHIM_END()
    }

    ///////////////////////////////////////////////////////////////////////////
    // void set_global_rotation_degrees(const Vector3& euler_degrees);
    // (nodeID, rotationMemoryOffset) [I64, I64] -> []
    wasm_trap_t* WasmShimNode3D::set_global_rotation_degrees(void* env, const wasm_val_vec_t* args, wasm_val_vec_t* results)
    {
        SHIM_BEGIN(2, 0)
        uint64_t offset = args->data[1].of.i64;
        Vector3 v = *((Vector3*) (data + offset));
        node->set_global_rotation_degrees(v);
        SHIM_END()
    }

    ///////////////////////////////////////////////////////////////////////////
    // Vector3 get_global_rotation_degrees() const;
    // (nodeID, rotationMemoryOffset) [I64, I64] -> []
    wasm_trap_t* WasmShimNode3D::get_global_rotation_degrees(void* env, const wasm_val_vec_t* args, wasm_val_vec_t* results)
    {
        SHIM_BEGIN(2, 0)
        uint64_t offset = args->data[1].of.i64;
        Vector3 v = node->get_global_rotation_degrees();
        memcpy(data + offset, &v, sizeof(Vector3));
        SHIM_END()
    }

    ///////////////////////////////////////////////////////////////////////////
    // Node3D* get_parent_node_3d() const;
    // (nodeID) [I64] -> [I64]
    wasm_trap_t* WasmShimNode3D::get_parent_node_3d(void* env, const wasm_val_vec_t* args, wasm_val_vec_t* results)
    {
        SHIM_BEGIN(1, 1)
        Node3D* parent = node->get_parent_node_3d();
        results->data[0].kind = WASM_I64;
        // TODO - return instance id instead of pointer?
        results->data[0].of.i64 = (int64_t) parent;
        //results->data[0].of.i64 = parent->get_instance_id();
        SHIM_END()
    }

    ///////////////////////////////////////////////////////////////////////////
    // void set_ignore_transform_notification(bool enabled);
    // (nodeID, enabled) [I64, I64] -> []
    wasm_trap_t* WasmShimNode3D::set_ignore_transform_notification(void* env, const wasm_val_vec_t* args, wasm_val_vec_t* results)
    {
        SHIM_BEGIN(2, 0)
        bool enabled = (bool) args->data[1].of.i64;
        node->set_ignore_transform_notification(enabled);
        SHIM_END()
    }

    ///////////////////////////////////////////////////////////////////////////
    // void set_as_top_level(bool enable);
    // (nodeID, enable) [I64, I64] -> []
    wasm_trap_t* WasmShimNode3D::set_as_top_level(void* env, const wasm_val_vec_t* args, wasm_val_vec_t* results)
    {
        SHIM_BEGIN(2, 0)
        bool enable = (bool) args->data[1].of.i64;
        node->set_as_top_level(enable);
        SHIM_END()
    }

    ///////////////////////////////////////////////////////////////////////////
    // bool is_set_as_top_level() const;
    // (nodeID) [I64] -> [I32]
    wasm_trap_t* WasmShimNode3D::is_set_as_top_level(void* env, const wasm_val_vec_t* args, wasm_val_vec_t* results)
    {
        SHIM_BEGIN(1, 1)
        bool v = node->is_set_as_top_level();
        results->data[0].kind = WASM_I32;
        results->data[0].of.i32 = (int32_t) v;
        SHIM_END()
    }

    ///////////////////////////////////////////////////////////////////////////
    // void set_disable_scale(bool disable);
    // (nodeID, enable) [I64, I64] -> []
    wasm_trap_t* WasmShimNode3D::set_disable_scale(void* env, const wasm_val_vec_t* args, wasm_val_vec_t* results)
    {
        SHIM_BEGIN(2, 0)
        bool enable = (bool) args->data[1].of.i64;
        node->set_disable_scale(enable);
        SHIM_END()
    }

    ///////////////////////////////////////////////////////////////////////////
    // bool is_scale_disabled() const;
    // (nodeID) [I64] -> [I32]
    wasm_trap_t* WasmShimNode3D::is_scale_disabled(void* env, const wasm_val_vec_t* args, wasm_val_vec_t* results)
    {
        SHIM_BEGIN(1, 1)
        bool v = node->is_scale_disabled();
        results->data[0].kind = WASM_I32;
        results->data[0].of.i32 = (int32_t) v;
        SHIM_END()
    }

    /* TODO
    Ref<World3D> get_world_3d() const;
    */

    ///////////////////////////////////////////////////////////////////////////
    // void force_update_transform();
    // (nodeID) [I64] -> []
    wasm_trap_t* WasmShimNode3D::force_update_transform(void* env, const wasm_val_vec_t* args, wasm_val_vec_t* results)
    {
        SHIM_BEGIN(1, 0)
        node->force_update_transform();
        SHIM_END()
    }

    /* TODO
    void set_visibility_parent(const NodePath& path);
    NodePath get_visibility_parent() const;
    */
    
    ///////////////////////////////////////////////////////////////////////////
    // void update_gizmos();
    // (nodeID) [I64] -> []
    wasm_trap_t* WasmShimNode3D::update_gizmos(void* env, const wasm_val_vec_t* args, wasm_val_vec_t* results)
    {
        SHIM_BEGIN(1, 0)
        node->update_gizmos();
        SHIM_END()
    }

    /* TODO
    void add_gizmo(const Ref<Node3DGizmo>& gizmo);
    TypedArray<Node3DGizmo> get_gizmos() const;
    */

    ///////////////////////////////////////////////////////////////////////////
    // void clear_gizmos();
    // (nodeID) [I64] -> []
    wasm_trap_t* WasmShimNode3D::clear_gizmos(void* env, const wasm_val_vec_t* args, wasm_val_vec_t* results)
    {
        SHIM_BEGIN(1, 0)
        node->clear_gizmos();
        SHIM_END()
    }

    /* TODO
    void set_subgizmo_selection(const Ref<Node3DGizmo>& gizmo, int32_t id, const Transform3D& transform);
    */

    ///////////////////////////////////////////////////////////////////////////
    // void clear_subgizmo_selection();
    // (nodeID) [I64] -> []
    wasm_trap_t* WasmShimNode3D::clear_subgizmo_selection(void* env, const wasm_val_vec_t* args, wasm_val_vec_t* results)
    {
        SHIM_BEGIN(1, 0)
        node->clear_subgizmo_selection();
        SHIM_END()
    }

    ///////////////////////////////////////////////////////////////////////////
    // void set_visible(bool visible);
    // (nodeID, visible) [I64, I64] -> []
    wasm_trap_t* WasmShimNode3D::set_visible(void* env, const wasm_val_vec_t* args, wasm_val_vec_t* results)
    {
        SHIM_BEGIN(2, 0)
        bool visable = (bool) args->data[1].of.i64;
        node->set_visible(visable);
        SHIM_END()
    }

    ///////////////////////////////////////////////////////////////////////////
    // bool is_visible() const;
    // (nodeID) [I64] -> [I32]
    wasm_trap_t* WasmShimNode3D::is_visible(void* env, const wasm_val_vec_t* args, wasm_val_vec_t* results)
    {
        SHIM_BEGIN(1, 1)
        bool visible = node->is_visible();
        results->data[0].kind = WASM_I32;
        results->data[0].of.i32 = (int32_t) visible;
        SHIM_END()
    }

    ///////////////////////////////////////////////////////////////////////////
    // bool is_visible_in_tree() const;
    // (nodeID) [I64] -> [I32]
    wasm_trap_t* WasmShimNode3D::is_visible_in_tree(void* env, const wasm_val_vec_t* args, wasm_val_vec_t* results)
    {
        SHIM_BEGIN(1, 1)
        bool visible = node->is_visible_in_tree();
        results->data[0].kind = WASM_I32;
        results->data[0].of.i32 = (int32_t) visible;
        SHIM_END()
    }

    ///////////////////////////////////////////////////////////////////////////
    // void show();
    // (nodeID) [I64] -> []
    wasm_trap_t* WasmShimNode3D::show(void* env, const wasm_val_vec_t* args, wasm_val_vec_t* results)
    {
        SHIM_BEGIN(1, 0)
        node->show();
        SHIM_END()
    }

    ///////////////////////////////////////////////////////////////////////////
    // void hide();
    // (nodeID) [I64] -> []
    wasm_trap_t* WasmShimNode3D::hide(void* env, const wasm_val_vec_t* args, wasm_val_vec_t* results)
    {
        SHIM_BEGIN(1, 0)
        node->hide();
        SHIM_END()
    }

    ///////////////////////////////////////////////////////////////////////////
    // void set_notify_local_transform(bool enable);
    // (nodeID, enable) [I64, I64] -> []
    wasm_trap_t* WasmShimNode3D::set_notify_local_transform(void* env, const wasm_val_vec_t* args, wasm_val_vec_t* results)
    {
        SHIM_BEGIN(2, 0)
        bool enable = (bool) args->data[1].of.i64;
        node->set_notify_local_transform(enable);
        SHIM_END()
    }

    ///////////////////////////////////////////////////////////////////////////
    // bool is_local_transform_notification_enabled() const;
    // (nodeID) [I64] -> [I32]
    wasm_trap_t* WasmShimNode3D::is_local_transform_notification_enabled(void* env, const wasm_val_vec_t* args, wasm_val_vec_t* results)
    {
        SHIM_BEGIN(1, 1)
        bool v = node->is_local_transform_notification_enabled();
        results->data[0].kind = WASM_I32;
        results->data[0].of.i32 = (int32_t) v;
        SHIM_END()
    }

    ///////////////////////////////////////////////////////////////////////////
    // void set_notify_transform(bool enable);
    // (nodeID, enable) [I64, I64] -> []
    wasm_trap_t* WasmShimNode3D::set_notify_transform(void* env, const wasm_val_vec_t* args, wasm_val_vec_t* results)
    {
        SHIM_BEGIN(2, 0)
        bool enable = (bool) args->data[1].of.i64;
        node->set_notify_transform(enable);
        SHIM_END()
    }

    ///////////////////////////////////////////////////////////////////////////
    // bool is_transform_notification_enabled() const;
    // (nodeID) [I64] -> [I32]
    wasm_trap_t* WasmShimNode3D::is_transform_notification_enabled(void* env, const wasm_val_vec_t* args, wasm_val_vec_t* results)
    {
        SHIM_BEGIN(1, 1)
        bool v = node->is_transform_notification_enabled();
        results->data[0].kind = WASM_I32;
        results->data[0].of.i32 = (int32_t) v;
        SHIM_END()
    }

    ///////////////////////////////////////////////////////////////////////////
    // void rotate(const Vector3& axis, double angle);
    // (nodeID, axisMemoryOffset, angle) [I64, I64, F64] -> []
    wasm_trap_t* WasmShimNode3D::rotate(void* env, const wasm_val_vec_t* args, wasm_val_vec_t* results)
    {
        SHIM_BEGIN(3, 0)
        uint64_t vecOffset = args->data[1].of.i64;
        Vector3 axis = *((Vector3*) (data + vecOffset));
        double angle = args->data[2].of.f64;
        node->rotate(axis, angle);
        SHIM_END()
    }

    ///////////////////////////////////////////////////////////////////////////
    // void global_rotate(const Vector3& axis, double angle);
    // (nodeID, axisMemoryOffset, angle) [I64, I64, F64] -> []
    wasm_trap_t* WasmShimNode3D::global_rotate(void* env, const wasm_val_vec_t* args, wasm_val_vec_t* results)
    {
        SHIM_BEGIN(3, 0)
        uint64_t vecOffset = args->data[1].of.i64;
        Vector3 axis = *((Vector3*) (data + vecOffset));
        double angle = args->data[2].of.f64;
        node->global_rotate(axis, angle);
        SHIM_END()
    }

    ///////////////////////////////////////////////////////////////////////////
    // void global_scale(const Vector3& scale);
    // (nodeID, scaleMemoryOffset) [I64, I64] -> []
    wasm_trap_t* WasmShimNode3D::global_scale(void* env, const wasm_val_vec_t* args, wasm_val_vec_t* results)
    {
        SHIM_BEGIN(2, 0)
        uint64_t vecOffset = args->data[1].of.i64;
        Vector3 val = *((Vector3*) (data + vecOffset));
        node->global_scale(val);
        SHIM_END()
    }

    ///////////////////////////////////////////////////////////////////////////
    // void global_translate(const Vector3& offset);
    // (nodeID, offsetMemoryOffset) [I64, I64] -> []
    wasm_trap_t* WasmShimNode3D::global_translate(void* env, const wasm_val_vec_t* args, wasm_val_vec_t* results)
    {
        SHIM_BEGIN(2, 0)
        uint64_t vecOffset = args->data[1].of.i64;
        Vector3 val = *((Vector3*) (data + vecOffset));
        node->global_translate(val);
        SHIM_END()
    }

    ///////////////////////////////////////////////////////////////////////////
    // void rotate_object_local(const Vector3& axis, double angle);
    // (nodeID, axisMemoryOffset, angle) [I64, I64, F64] -> []
    wasm_trap_t* WasmShimNode3D::rotate_object_local(void* env, const wasm_val_vec_t* args, wasm_val_vec_t* results)
    {
        SHIM_BEGIN(3, 0)
        uint64_t axisVecOffset = args->data[1].of.i64;
        Vector3 axis = *((Vector3*) (data + axisVecOffset));
        double angle = args->data[2].of.f64;
        node->rotate_object_local(axis, angle);
        SHIM_END()
    }

    ///////////////////////////////////////////////////////////////////////////
    // void scale_object_local(const Vector3& scale);
    // (nodeID, scaleMemoryOffset) [I64, I64] -> []
    wasm_trap_t* WasmShimNode3D::scale_object_local(void* env, const wasm_val_vec_t* args, wasm_val_vec_t* results)
    {
        SHIM_BEGIN(2, 0)
        uint64_t vecOffset = args->data[1].of.i64;
        Vector3 scale = *((Vector3*) (data + vecOffset));
        node->scale_object_local(scale);
        SHIM_END()
    }

    ///////////////////////////////////////////////////////////////////////////
    // void translate_object_local(const Vector3& offset);
    // (nodeID, offsetMemoryOffset) [I64, I64] -> []
    wasm_trap_t* WasmShimNode3D::translate_object_local(void* env, const wasm_val_vec_t* args, wasm_val_vec_t* results)
    {
        SHIM_BEGIN(2, 0)
        uint64_t vecOffset = args->data[1].of.i64;
        Vector3 val = *((Vector3*) (data + vecOffset));
        node->translate_object_local(val);
        SHIM_END()
    }

    ///////////////////////////////////////////////////////////////////////////
    // void rotate_x(double angle);
    // (nodeID, angle) [I64, F64] -> []
    wasm_trap_t* WasmShimNode3D::rotate_x(void* env, const wasm_val_vec_t* args, wasm_val_vec_t* results)
    {
        SHIM_BEGIN(2, 0)
        double angle = args->data[1].of.f64;
        node->rotate_x(angle);
        SHIM_END()
    }

    ///////////////////////////////////////////////////////////////////////////
    // void rotate_y(double angle);
    // (nodeID, angle) [I64, F64] -> []
    wasm_trap_t* WasmShimNode3D::rotate_y(void* env, const wasm_val_vec_t* args, wasm_val_vec_t* results)
    {
        SHIM_BEGIN(2, 0)
        double angle = args->data[1].of.f64;
        node->rotate_y(angle);
        SHIM_END()
    }

    ///////////////////////////////////////////////////////////////////////////
    // void rotate_z(double angle);
    // (nodeID, angle) [I64, F64] -> []
    wasm_trap_t* WasmShimNode3D::rotate_z(void* env, const wasm_val_vec_t* args, wasm_val_vec_t* results)
    {
        SHIM_BEGIN(2, 0)
        double angle = args->data[1].of.f64;
        node->rotate_z(angle);
        SHIM_END()
    }

    ///////////////////////////////////////////////////////////////////////////
    // void translate(const Vector3& offset);
    // (nodeID, offsetMemoryOffset) [I64, I64] -> []
    wasm_trap_t* WasmShimNode3D::translate(void* env, const wasm_val_vec_t* args, wasm_val_vec_t* results)
    {
        SHIM_BEGIN(2, 0)
        uint64_t vecOffset = args->data[1].of.i64;
        Vector3 val = *((Vector3*) (data + vecOffset));
        node->translate(val);
        SHIM_END()
    }

    ///////////////////////////////////////////////////////////////////////////
    // void orthonormalize();
    // (nodeID) [I64] -> []
    wasm_trap_t* WasmShimNode3D::orthonormalize(void* env, const wasm_val_vec_t* args, wasm_val_vec_t* results)
    {
        SHIM_BEGIN(1, 0)
        node->orthonormalize();
        SHIM_END()
    }

    ///////////////////////////////////////////////////////////////////////////
    // void set_identity();
    // (nodeID) [I64] -> []
    wasm_trap_t* WasmShimNode3D::set_identity(void* env, const wasm_val_vec_t* args, wasm_val_vec_t* results)
    {
        SHIM_BEGIN(1, 0)
        node->set_identity();
        SHIM_END()
    }

    ///////////////////////////////////////////////////////////////////////////
    // void look_at(const Vector3& target, const Vector3& up = Vector3(0, 1, 0), bool use_model_front = false);
    // (nodeID, targetMemoryOffset, upMemoryOffset, use_model_front) [I64, I64, I64, I64] -> []
    wasm_trap_t* WasmShimNode3D::look_at(void* env, const wasm_val_vec_t* args, wasm_val_vec_t* results)
    {
        SHIM_BEGIN(4, 0)
        uint64_t targetVecOffset = args->data[1].of.i64;
        uint64_t upVecOffset = args->data[2].of.i64;
        uint64_t use_model_front = args->data[3].of.i64;
        Vector3 target = *((Vector3*) (data + targetVecOffset));
        Vector3 up = *((Vector3*) (data + upVecOffset));
        node->look_at(target, up, (bool) use_model_front);
        SHIM_END()
    }

    ///////////////////////////////////////////////////////////////////////////
    // void look_at_from_position(const Vector3& position, const Vector3& target, const Vector3& up = Vector3(0, 1, 0), bool use_model_front = false);
    // (nodeID, positionMemoryOffset, targetMemoryOffset, upMemoryOffset, use_model_front) [I64, I64, I64, I64, I64] -> []
    wasm_trap_t* WasmShimNode3D::look_at_from_position(void* env, const wasm_val_vec_t* args, wasm_val_vec_t* results)
    {
        SHIM_BEGIN(5, 0)
        uint64_t positionVecOffset = args->data[1].of.i64;
        uint64_t targetVecOffset = args->data[2].of.i64;
        uint64_t upVecOffset = args->data[3].of.i64;
        uint64_t use_model_front = args->data[4].of.i64;
        Vector3 pos = *((Vector3*) (data + positionVecOffset));
        Vector3 target = *((Vector3*) (data + targetVecOffset));
        Vector3 up = *((Vector3*) (data + upVecOffset));
        node->look_at_from_position(pos, target, up, (bool) use_model_front);
        SHIM_END()
    }

    ///////////////////////////////////////////////////////////////////////////
    // Vector3 to_local(const Vector3& global_point) const;
    // (nodeID, pointMemoryOffset, resultMemoryOffset) [I64, I64, I64] -> []
    wasm_trap_t* WasmShimNode3D::to_local(void* env, const wasm_val_vec_t* args, wasm_val_vec_t* results)
    {
        SHIM_BEGIN(3, 0)
        uint64_t pointVecOffset = args->data[1].of.i64;
        uint64_t resultVecOffset = args->data[2].of.i64;
        Vector3 val = *((Vector3*) (data + pointVecOffset));
        Vector3 result = node->to_local(val);
        memcpy(data + resultVecOffset, &result, sizeof(Vector3));
        SHIM_END()
    }

    ///////////////////////////////////////////////////////////////////////////
    // Vector3 to_global(const Vector3& local_point) const;
    // (nodeID, pointMemoryOffset) [I64, I64] -> []
    wasm_trap_t* WasmShimNode3D::to_global(void* env, const wasm_val_vec_t* args, wasm_val_vec_t* results)
    {
        SHIM_BEGIN(3, 0)
        uint64_t pointVecOffset = args->data[1].of.i64;
        uint64_t resultVecOffset = args->data[2].of.i64;
        Vector3 val = *((Vector3*) (data + pointVecOffset));
        Vector3 result = node->to_global(val);
        memcpy(data + resultVecOffset, &result, sizeof(Vector3));
        SHIM_END()
    }
}
