#include "KingSystem/ActorSystem/actModelBindInfo.h"
#include <gsys/gsysModel.h>
#include <gsys/gsysModelUnit.h>
#include <math/seadQuat.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"

namespace ksys::act {

ModelBindInfo::ModelBindInfo() = default;

// NON_MATCHING: branch hoisting, axis registers and quaternion temporary stores differ.
// The existing SEAD Matrix33 x Matrix34 multiply also emits a non-matching template.
void ModelBindInfo::sub_7100D3BDD8(Actor* actor, sead::Matrix34f* matrix,
                                const sead::Matrix34f& fallback) {
    if (_98 == 3) {
        matrix->setMul(*matrix, _68);
        const auto translation = matrix->getTranslation();
        actor->mMtx.setTranslation(translation);
        actor->nullsub_4648();
        if (_18)
            sub_7100EE57FC(actor, translation);
        return;
    }

    if (_98 == 4) {
        for (s32 i = 0; i < 3; ++i)
            matrix->setBase(i, fallback.getBase(i));
    } else {
        if (_98 != 2) {
            for (s32 i = 0; i < 3; ++i) {
                auto axis = matrix->getBase(i);
                axis.normalize();
                matrix->setBase(i, axis);
            }
        }
        if (_98 == 1) {
            sead::Quatf rotation;
            if (rotation.makeVectorRotation(matrix->getBase(1), sead::Vector3f::ey)) {
                sead::Matrix33f rotation_matrix;
                rotation_matrix.fromQuat(rotation);
                const auto translation = matrix->getTranslation();
                matrix->setMul(rotation_matrix, *matrix);
                matrix->setTranslation(translation);
            }
        }
    }

    matrix->setMul(*matrix, _68);
    actor->mMtx = *matrix;
    actor->nullsub_4648();
    if (_18)
        sub_7100EE58C0(actor, *matrix);
}

bool ModelBindInfo::m4(BaseProc* proc) {
    auto* bound_actor = sub_7100D3C5E0(proc);
    if (!bound_actor)
        return false;
    auto* model = bound_actor->getModel();
    if (!model) {
        sead::Matrix34f matrix = bound_actor->getMtx();
        sub_7100D3BDD8(static_cast<Actor*>(proc), &matrix, bound_actor->getMtx());
        return true;
    }
    if (!_28) {
        sead::Matrix34f matrix = model->getMatrix();
        sub_7100D3BDD8(static_cast<Actor*>(proc), &matrix, model->getMatrix());
        return false;
    }
    if (!_30.isValid())
        _30.search(model, _28);
    if (!_30.isValid())
        return false;
    sead::Matrix34f matrix;
    model->getUnits()(_30.getKey().model_unit_index)->mModelUnit->getBoneWorldMatrix(
        &matrix, _30.getKey().bone_index);
    sub_7100D3BDD8(static_cast<Actor*>(proc), &matrix, model->getMatrix());
    return true;
}

bool ModelBindInfo::m5(BaseProc* proc) {
    return false;
}

}  // namespace ksys::act
