#include "KingSystem/Resource/Actor/resResourceAttPos.h"
#include <gsys/gsysModel.h>
#include <gsys/gsysModelAccessKey.h>
#include <gsys/gsysModelUnit.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace ksys::res {

AttPos::AttPos() = default;

void AttPos::init(agl::utl::IParameterObj* obj, const char* node_key, const char* offset_key,
                  const char* rotate_key, const char* y_rot_only_key) {
    node.init("", node_key, "ノード", "", obj);
    offset.init(sead::Vector3f::zero, offset_key, "オフセット", "Min=-100.f,Max=100.f", obj);
    rotate.init(sead::Vector3f::zero, rotate_key, "回転", "Min=-3.1415f,Max=3.1415f", obj);
    y_rot_only.init(false, y_rot_only_key, "Ｙ軸回転のみ有効", "", obj);
}

// NON_MATCHING: scheduling only (the original loads the three components of `ey` into integer registers in one
// go before storing the new Y axis and reloads y / z as floats for the second cross product)
void AttPos::x(sead::Matrix34f* mtx) const {
    if (!y_rot_only.ref())
        return;

    sead::Vector3f x_axis;
    mtx->getBase(x_axis, 0);
    if (x_axis.x != 0.0f || x_axis.z != 0.0f) {
        sead::Vector3f z_axis = x_axis.cross(sead::Vector3f::ey);
        z_axis.normalize();
        mtx->setBase(2, z_axis);
    }

    mtx->setBase(1, sead::Vector3f::ey);

    sead::Vector3f z_axis;
    mtx->getBase(z_axis, 2);
    if (z_axis.x != 0.0f || z_axis.z != 0.0f) {
        x_axis = sead::Vector3f::ey.cross(z_axis);
        x_axis.normalize();
        mtx->setBase(0, x_axis);
    }
}

void AttPos::edit(sead::Matrix34f* mtx, act::Actor* actor, const gsys::BoneAccessKey* key) const {
    const f32 scale = actor->getScale().x;
    const sead::Vector3f translation = offset.ref() * scale;
    sead::Matrix34f local;
    local.makeRT(rotate.ref(), translation);

    if (!key || key->model_unit_index == -1 || key->bone_index == -1 || !actor->getModel()) {
        *mtx = actor->getMtx();
    } else {
        actor->getModel()
            ->getUnits()
            .unsafeAt(key->model_unit_index)
            ->mModelUnit->getBoneWorldMatrix(mtx, key->bone_index);
    }

    x(mtx);
    mtx->setMul(*mtx, local);
}

// NON_MATCHING: the original tests the node name with an inlined `cstr()` + length loop + empty-string fallback
// instead of `isEmpty()`, and schedules the rotation matrix differently
void AttPos::x_1(sead::Matrix34f* mtx, act::ActorConstDataAccess& accessor) const {
    const f32 scale = accessor.getField418().x;
    const sead::Vector3f translation = offset.ref() * scale;
    sead::Matrix34f local;
    local.makeRT(rotate.ref(), translation);

    if (node.ref().isEmpty() || !accessor.sub_7100D12944(mtx, node.ref()))
        *mtx = accessor.getActorMtx();

    x(mtx);
    mtx->setMul(*mtx, local);
}

// NON_MATCHING: scheduling only (the loads of the node name test are interleaved with the rotation matrix)
void AttPos::x_2(sead::Matrix34f* mtx, act::Actor* actor) const {
    const f32 scale = actor->getScale().x;
    const sead::Vector3f translation = offset.ref() * scale;
    sead::Matrix34f local;
    local.makeRT(rotate.ref(), translation);

    bool found = false;
    if (!node.ref().isEmpty()) {
        if (auto* model = actor->getModel()) {
            const auto key = model->searchBone(node.ref());
            if (key.isValid()) {
                model->getUnits()
                    .unsafeAt(key.model_unit_index)
                    ->mModelUnit->getBoneWorldMatrix(mtx, key.bone_index);
                found = true;
            }
        }
    }
    if (!found)
        *mtx = actor->getMtx();

    x(mtx);
    mtx->setMul(*mtx, local);
}

}  // namespace ksys::res
