#include "KingSystem/Graphics/gfxUnk_710260af28.h"
#include <cmath>
#include <gsys/gsysModel.h>
#include <gsys/gsysModelNW.h>
#include <gsys/gsysModelUnit.h>
#include "Game/gameGraphics.h"

void Unk_710260af28::sub_7100F1D9B4(gsys::Model* model, f32 value, bool negate) {
    const f32 wrapped = std::fmod(value, Graphics::instance()->getSpecialEffectAWrapMaybe());
    const f32 effect = negate ? -wrapped : wrapped;
    for (s32 i = 0; i < model->getUnits().size(); ++i) {
        auto* unit = model->getUnits()[i]->mModelUnit;
        const s32 count = unit->getMaterialNum();
        for (s32 material = 0; material < count; ++material) {
            const sead::SafeString param_name("uk_special_effect_A");
            const s32 param = unit->searchMaterialParamIndex(material, param_name);
            if (param != -1)
                unit->setMaterialParamF32(material, param, effect);
        }
    }
}

void Unk_710260af28::sub_7100F1ED28(gsys::Model* model, int mode) {
    for (s32 i = 0; i < model->getUnits().size(); ++i)
        sub_7100F1ED8C(model->getUnits()[i]->mModelUnit, mode);
}

void Unk_710260af28::sub_7100F1D058(gsys::Model* model, u32 flags) {
    for (s32 i = 0; i < model->getUnits().size(); ++i)
        sub_7100F1D0BC(model->getUnits()[i]->mModelUnit, flags);
}

void Unk_710260af28::sub_7100F1C77C(gsys::Model* model, const void* user_data) {
    for (s32 i = 0; i < model->getUnits().size(); ++i) {
        auto* unit = model->getUnits()[i]->mModelUnit;
        const s32 count = unit->getMaterialNum();
        for (s32 material = 0; material < count; ++material)
            sub_7100F1C824(unit, material, user_data);
    }
}

u64 Unk_710260af28::sub_7100F1CD88(gsys::Model* model) {
    auto* unit = model->getUnits()[0]->mModelUnit;
    const s32 low_param = unit->searchMaterialParamIndex(0, "uk_user_data");
    const s32 high_param = unit->searchMaterialParamIndex(0, "uk_user_data1");
    if (low_param == -1 || high_param == -1)
        return 0;
    return unit->getMaterialParamU32(0, low_param) |
           (static_cast<u64>(unit->getMaterialParamU32(0, high_param)) << 32);
}

f32 Unk_710260af28::sub_7100F1CE68(gsys::Model* model) {
    auto* unit = model->getUnits()[0]->mModelUnit;
    const s32 param = unit->searchMaterialParamIndex(0, "uk_object_attribute");
    if (param == -1)
        return 0.0f;
    return unit->getMaterialParamF32(0, param);
}

// NON_MATCHING: temporary shader-name setup moves around the virtual call.
void Unk_710260af28::sub_7100F1CC38(gsys::Model* model, u64 value) {
    for (s32 i = 0; i < model->getUnits().size(); ++i) {
        auto* unit = model->getUnits()[i]->mModelUnit;
        const s32 count = unit->getMaterialNum();
        for (s32 material = 0; material < count; ++material) {
            const s32 low_param = unit->searchMaterialParamIndex(material, "uk_user_data");
            if (low_param != -1)
                unit->setMaterialParamU32(material, low_param, static_cast<u32>(value));
            const s32 high_param = unit->searchMaterialParamIndex(material, "uk_user_data1");
            if (high_param != -1)
                unit->setMaterialParamU32(material, high_param, static_cast<u32>(value >> 32));
        }
    }
}

// NON_MATCHING: temporary shader-name setup moves around the virtual call.
void Unk_710260af28::sub_7100F1CEF4(gsys::Model* model, f32 value) {
    for (s32 i = 0; i < model->getUnits().size(); ++i) {
        auto* unit = model->getUnits()[i]->mModelUnit;
        if (!sead::IsDerivedFrom<gsys::ModelNW>(unit))
            continue;
        for (s32 material = 0; material < unit->getMaterialNum(); ++material) {
            const s32 param = unit->searchMaterialParamIndex(material, "uk_object_attribute");
            if (param != -1)
                unit->setMaterialParamF32(material, param, value);
        }
    }
}


