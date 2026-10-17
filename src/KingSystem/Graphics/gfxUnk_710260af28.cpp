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

// 0x7100f1c774 / 0x7100f1ee98 / 0x7100f1eea0 (placeholder names): constant helpers of the model effect
// manager TU; the CSV rows are unnamed and nothing calls them directly.
s32 sub_7100F1C774() {
    return 0;
}

s32 sub_7100F1EE98() {
    return 22;
}

s32 sub_7100F1EEA0() {
    return 0;
}

s32 sub_7100F1C3E8() { return 1; }

s32 sub_7100F1FE1C() { return 2; }

s32 sub_7100F1FE24() { return -7; }

s32 sub_7100F1FE2C() { return -5; }

// Empty and delete-thunk virtuals in the graphics / framework address range (placeholder names).
void sub_7100F0071C() {}
void sub_7100F10BEC() {}
void sub_7100F14C64() {}
void sub_7100F159B4() {}
void sub_7100F159B8() {}
void sub_7100F159BC() {}
void sub_7100F159C0() {}
void sub_7100F159C4() {}
void sub_7100F159D0() {}
void sub_7100F159D4() {}
void sub_7100F159D8() {}
void sub_7100F159DC() {}
void sub_7100F159E0() {}
void sub_7100F159E4() {}
void sub_7100F159E8() {}
void sub_7100F159EC() {}
void sub_7100F159F0() {}
void sub_7100F159F4() {}
void sub_7100F159F8() {}
void sub_7100F159FC() {}
void sub_7100F176C4() {}
void sub_7100F1B9B0() {}
void sub_7100F1B9B4(void* p) { ::operator delete(p); }
void sub_7100F1F1F0() {}
void sub_7100F1F1F4() {}
void sub_7100F1FE40() {}
void sub_7100F1FE44() {}
void sub_7100F1FE48() {}
void sub_7100F1FE4C() {}
void sub_7100F1FE50() {}
void sub_7100F1FE54() {}
void sub_7100F1FE58() {}
void sub_7100F1FE5C() {}
void sub_7100F2DD98() {}
void sub_7100F2DD9C() {}
void sub_7100F2DFD8() {}
void sub_7100F2DFDC() {}
void sub_7100F2E07C() {}
void sub_7100F35F48() {}
void sub_7100F35F4C() {}
void sub_7100F36350() {}
void sub_7100F36354() {}
void sub_7100F36358() {}
void sub_7100F36428() {}
void sub_7100F3642C() {}
void sub_7100F36430() {}
void sub_7100F36434() {}
void sub_7100F36438() {}
void sub_7100F3643C() {}
void sub_7100F36440() {}
void sub_7100F36444() {}
void sub_7100F36448() {}
void sub_7100F3644C() {}
void sub_7100F36450() {}
void sub_7100F36454() {}
void sub_7100F36458() {}
void sub_7100F3645C() {}
void sub_7100F36460() {}
void sub_7100F36464() {}
void sub_7100F36468() {}
void sub_7100F3646C() {}
void sub_7100F36470() {}
void sub_7100F36474() {}
void sub_7100F36478() {}
void sub_7100F3704C() {}
void sub_7100F383DC() {}
void sub_7100F383E0() {}
void sub_7100F383E4() {}
void sub_7100F3D204() {}
void sub_7100F3D964() {}
