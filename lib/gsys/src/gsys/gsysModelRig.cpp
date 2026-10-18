#include "gsys/gsysModelRig.h"
#include "gsys/gsysModel.h"
#include "gsys/gsysModelNW.h"
#include <nn/g3d/ResModel.h>

namespace gsys {

ModelRig::ModelRig()
    : mModelName(sead::FixedSafeString<64>("untitled"), "ModelName", "モデル名", this),
      mBonePrefix(sead::FixedSafeString<64>("untitled"), "BonePrefix", "ボーンプリフィックス", this),
      mMaterialPrefix(sead::FixedSafeString<64>("untitled"), "MaterialPrefix",
                      "マテリアルプリフィックス", this) {}

// NON_MATCHING: the natural wildcard-filter control flow produces a 2504-byte body.
void ModelRig::m23(Model* model) {
    const int bone_prefix_length = mBonePrefix->calcLength();
    const int material_prefix_length = mMaterialPrefix->calcLength();
    for (int unit_index = 0; unit_index < model->getUnits().size(); ++unit_index) {
        auto* unit = sead::DynamicCast<ModelNW>(model->getUnits()[unit_index]->mModelUnit);
        if (!unit || unit->getDrawArray())
            continue;

        // The per-unit callback runs before the name filter.
        m26(model, unit_index);
        bool selected = mModelName->isEqual(sead::SafeString::cEmptyString);
        if (!selected)
            selected = mModelName->isEqual(
                sead::SafeString(unit->getModelObj()->GetResource()->GetName()));
        if (mModelName->endsWith("*")) {
            const sead::SafeString model_name(unit->getModelObj()->GetResource()->GetName());
            bool prefix_matches = true;
            const int model_prefix_length = mModelName->calcLength() - 1;
            for (int i = 0; i < model_prefix_length; ++i) {
                // SafeString bounds/null-character behavior is intentional.
                if (model_name.at(i) != mModelName->at(i)) {
                    prefix_matches = false;
                    break;
                }
            }
            selected |= prefix_matches;
        }
        if (!selected)
            continue;

        for (int bone_index = 0; bone_index < unit->getBoneNum(); ++bone_index) {
            const sead::SafeString name = unit->getBoneName(bone_index);
            if (mBonePrefix->comparen(name, bone_prefix_length) == 0) {
                BoneAccessKey key;
                key.model_unit_index = unit_index;
                key.bone_index = bone_index;
                m24(model, key, name);
            }
        }
        for (int material_index = 0; material_index < unit->getMaterialNum(); ++material_index) {
            const sead::SafeString name = unit->getMaterialName(material_index);
            if (mMaterialPrefix->comparen(name, material_prefix_length) == 0) {
                MaterialAccessKey key;
                key.model_unit_index = unit_index;
                key.material_index = material_index;
                m25(model, key, name);
            }
        }
    }
}
}  // namespace gsys
