#include "KingSystem/ActorSystem/AS/ASList.h"
#include <gsys/gsysModelUnit.h>

namespace ksys::as {

ASList::Unk5::Unk5() = default;

ASList::Unk5::~Unk5() {
    for (s32 i = 0; i < mBones.size(); ++i)
        mBones[i].freeBuffer();
    mBones.freeBuffer();
}

void ASList::Unk5::sub_7100D68104(gsys::Model* model, void*, const sead::Matrix34f* matrix,
                                const gsys::BoneAccessKey* key) {
    if (!model)
        return;
    for (s32 unit_index = 0; unit_index < model->getUnits().size(); ++unit_index) {
        auto* unit = model->getUnits().unsafeAt(unit_index)->mModelUnit;
        auto& bones = mBones[unit_index];
        const s32 num_bones = unit->getBoneNum();
        for (s32 bone_index = 0; bone_index < num_bones; ++bone_index) {
            Bone& bone = bones[bone_index];
            sead::Matrix34f local_matrix;
            if (key->model_unit_index == unit_index && key->bone_index == bone_index) {
                matrix->getTranslation(bone.translation);
                matrix->toQuat(bone.rotation);
            } else {
                unit->getBoneLocalMatrix(&local_matrix, &bone.scale, bone_index);
                local_matrix.getTranslation(bone.translation);
                local_matrix.toQuat(bone.rotation);
            }
        }
    }
    _21 = true;
}

void ASList::Unk5::sub_7100D68464(sead::Matrix34f* matrix, const gsys::BoneAccessKey* key) {
    const Bone& bone = mBones[key->model_unit_index][key->bone_index];
    matrix->fromQuat(bone.rotation);
    matrix->setTranslation(bone.translation);
}

void ASList::Unk5::sub_7100D68544(const sead::Matrix34f* matrix, const gsys::BoneAccessKey* key) {
    Bone& bone = mBones[key->model_unit_index][key->bone_index];
    matrix->getTranslation(bone.translation);
    matrix->toQuat(bone.rotation);
}

}  // namespace ksys::as
