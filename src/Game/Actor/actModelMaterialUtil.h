#pragma once

#include <gsys/gsysModel.h>
#include <gsys/gsysModelAccessKey.h>
#include <gsys/gsysModelUnit.h>

namespace uking::act {

// inline-only in the original; names are guesses: the model unit lookup is repeated for every query / change in
// ArmorBase::sub_7100E2A060 and HorseObject::m81 (the unit is reloaded after each call).
inline bool isMaterialVisible(gsys::Model* model, const gsys::MaterialAccessKey& key) {
    return model->getUnits().unsafeAt(key.model_unit_index)->mModelUnit->isMaterialVisible(
        key.material_index);
}

inline void setMaterialVisible(gsys::Model* model, const gsys::MaterialAccessKey& key, bool visible) {
    model->getUnits().unsafeAt(key.model_unit_index)->mModelUnit->setMaterialVisible(
        key.material_index, visible);
}

}  // namespace uking::act
