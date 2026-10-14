#include "Game/Actor/Action/actionUnk_71024512e8.h"

#include <gsys/gsysModel.h>
#include <gsys/gsysModelNW.h>
#include <nn/g3d/SkeletonObj.h>

Unk_71024512e8::Unk_71024512e8() = default;

Unk_71024512e8::~Unk_71024512e8() = default;

void Unk_71024512e8::setName(const sead::SafeString& name) {
    if (_8)
        return;
    _50 = name;
    _60.getKey().reset();
}

// NON_MATCHING: matrix register allocation and temporary stack placement differ.
void Unk_71024512e8::m2(gsys::Model* model) {
    const auto& key = _60.getKey();
    if (!key.isValid())
        return;
    auto* unit = sead::DynamicCast<gsys::ModelNW>(
        model->getUnits()[key.model_unit_index]->mModelUnit);
    if (!unit)
        return;
    const auto* skeleton = unit->getSkeletonObj()->GetRes();
    if (!skeleton)
        return;
    sead::Matrix34f bone_matrix;
    sead::Vector3f scale;
    const s32 bone_index = key.bone_index;
    unit->getBoneLocalMatrix(&bone_matrix, &scale, bone_index);
    u32 parent = skeleton->GetBone(bone_index)->GetParentIndex();
    sead::Matrix34f parent_matrix(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0);
    if (parent != 0 || !_98) {
        do {
            sead::Matrix34f local;
            sead::Vector3f local_scale;
            unit->getBoneLocalMatrix(&local, &local_scale, parent);
            parent_matrix.setMul(local, parent_matrix);
            if (parent == 0)
                break;
            parent = skeleton->GetBone(parent)->GetParentIndex();
        } while (parent != 0 || !_98);
    }
    parent_matrix.setMul(model->getMatrix(), parent_matrix);
    sead::Matrix34f inverse;
    inverse.setInverse(parent_matrix);
    sead::Matrix34f local;
    local.setMul(inverse, _20);
    model->setBoneLocalMatrix(key, local, scale);
}

bool Unk_71024512e8::m3(gsys::Model* model, bool sorted) {
    _60.search(model, _50);
    return _60.isValid();
}
