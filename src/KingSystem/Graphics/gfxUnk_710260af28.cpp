#include "KingSystem/Graphics/gfxUnk_710260af28.h"
#include <cmath>
#include <gsys/gsysModel.h>
#include <gsys/gsysModelNW.h>
#include <gsys/gsysModelRenderUnit.h>
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

void Unk_710260af28::sub_7100F1ECE8(gsys::Model* model) {
    for (s32 i = 0; i < model->getUnits().size(); ++i)
        model->getUnits()[i]->mModelUnit->getAttributeFlags().reset(
            gsys::ModelUnit::Attribute::LodCalculation);
}

void Unk_710260af28::sub_7100F1C700(gsys::ModelUnit* unit) {
    unit->enableRenderViewOption(static_cast<gsys::ModelEnum::RenderViewOption>(0), false, -1);
    unit->enableRenderOption(static_cast<gsys::ModelEnum::RenderOption>(2), false);
    unit->sub_7100C3E898(1, false);
    unit->sub_7100C3ECF0(1, false);
    unit->sub_7100C3ECF0(0, false);
    unit->updateQueueInfo();
}

void Unk_710260af28::sub_7100F1DCA8(gsys::Model* model, f32 opacity, bool fade) {
    if ((_5c & 8) != 0)
        return;
    for (s32 i = 0; i < model->getUnits().size(); ++i)
        sub_7100F1DD24(model->getUnits()[i]->mModelUnit, opacity, fade);
}

void Unk_710260af28::sub_7100F1ED28(gsys::Model* model, int mode) {
    for (s32 i = 0; i < model->getUnits().size(); ++i)
        sub_7100F1ED8C(model->getUnits()[i]->mModelUnit, mode);
}

void Unk_710260af28::sub_7100F1E100(gsys::Model* model, f32 value) {
    for (s32 i = 0; i < model->getUnits().size(); ++i) {
        auto* unit = model->getUnits()[i]->mModelUnit;
        const s32 count = unit->getMaterialNum();
        for (s32 material = 0; material < count; ++material) {
            const sead::SafeString name("uk_shadow_alpha");
            const s32 param = unit->searchMaterialParamIndex(material, name);
            if (param != -1)
                unit->setMaterialParamF32(material, param, value);
        }
    }
}

void Unk_710260af28::sub_7100F1E1F8(gsys::Model* model, f32 value) {
    for (s32 i = 0; i < model->getUnits().size(); ++i) {
        auto* unit = model->getUnits()[i]->mModelUnit;
        const s32 count = unit->getMaterialNum();
        for (s32 material = 0; material < count; ++material) {
            const sead::SafeString name("uk_proc_discard");
            const s32 param = unit->searchMaterialParamIndex(material, name);
            if (param != -1)
                unit->setMaterialParamF32(material, param, 1.0f - value);
        }
    }
}

void Unk_710260af28::sub_7100F1E2F4(gsys::Model* model, const sead::Color4f& color) {
    for (s32 i = 0; i < model->getUnits().size(); ++i) {
        auto* unit = model->getUnits()[i]->mModelUnit;
        const s32 count = unit->getMaterialNum();
        for (s32 material = 0; material < count; ++material) {
            const sead::SafeString name("uk_damage_color");
            const s32 param = unit->searchMaterialParamIndex(material, name);
            if (param != -1)
                unit->setMaterialParamColor4f(material, param, color);
        }
    }
}

void Unk_710260af28::sub_7100F1E8A4(gsys::Model* model, f32 value) {
    for (s32 i = 0; i < model->getUnits().size(); ++i) {
        auto* unit = model->getUnits()[i]->mModelUnit;
        const s32 count = unit->getMaterialNum();
        for (s32 material = 0; material < count; ++material) {
            const sead::SafeString name("uk_cook_ratio");
            const s32 param = unit->searchMaterialParamIndex(material, name);
            if (param != -1)
                unit->setMaterialParamF32(material, param, value);
        }
    }
}

void Unk_710260af28::sub_7100F1EAF8(gsys::Model* model, f32 value) {
    for (s32 i = 0; i < model->getUnits().size(); ++i) {
        auto* unit = model->getUnits()[i]->mModelUnit;
        const s32 count = unit->getMaterialNum();
        for (s32 material = 0; material < count; ++material) {
            const sead::SafeString name("uk_kari_chemical_ice_ratio0");
            const s32 param = unit->searchMaterialParamIndex(material, name);
            if (param != -1)
                unit->setMaterialParamF32(material, param, value);
        }
    }
}

void Unk_710260af28::sub_7100F1EBF0(gsys::Model* model) {
    for (s32 i = 0; i < model->getUnits().size(); ++i) {
        auto* unit = model->getUnits()[i]->mModelUnit;
        const s32 count = unit->getMaterialNum();
        for (s32 material = 0; material < count; ++material) {
            const s32 param = unit->searchMaterialParamIndex(
                material, "uking_wind_vtx_transform_lie_intensity");
            if (param != -1)
                unit->setMaterialParamF32(material, param, 0.0f);
        }
    }
}

void Unk_710260af28::sub_7100F1E3E4(gsys::Model* model, f32 value) {
    for (s32 i = 0; i < model->getUnits().size(); ++i) {
        auto* unit = model->getUnits()[i]->mModelUnit;
        const s32 count = unit->getMaterialNum();
        for (s32 material = 0; material < count; ++material) {
            const sead::SafeString name("uk_special_effect_B");
            const s32 param = unit->searchMaterialParamIndex(material, name);
            if (param != -1)
                unit->setMaterialParamF32(material, param, value);
        }
    }
}

void Unk_710260af28::sub_7100F1E794(gsys::Model* model, f32 value, f32 step) {
    const f32 ratio = value + step * 0.99999;
    for (s32 i = 0; i < model->getUnits().size(); ++i) {
        auto* unit = model->getUnits()[i]->mModelUnit;
        const s32 count = unit->getMaterialNum();
        for (s32 material = 0; material < count; ++material) {
            const sead::SafeString name("uk_mimicly_ratio");
            const s32 param = unit->searchMaterialParamIndex(material, name);
            if (param != -1)
                unit->setMaterialParamF32(material, param, ratio);
        }
    }
}

void Unk_710260af28::sub_7100F1E99C(gsys::Model* model) {
    for (s32 i = 0; i < model->getUnits().size(); ++i)
        model->getUnits()[i]->mModelUnit->getMaterialNum();
}

s32 Unk_710260af28::sub_7100F1E9F0(gsys::ModelUnit* unit) {
    return unit->getMaterialNum();
}

void Unk_710260af28::sub_7100F1E4DC(gsys::Model* model, f32 value) {
    for (s32 i = 0; i < model->getUnits().size(); ++i)
        sub_7100F1E538(model->getUnits()[i]->mModelUnit, value);
}

void Unk_710260af28::sub_7100F1E538(gsys::ModelUnit* unit, f32 value) {
    const s32 count = unit->getMaterialNum();
    for (s32 material = 0; material < count; ++material) {
        const s32 p0 = unit->searchMaterialParamIndex(material, "texture_array_index0");
        if (p0 != -1)
            unit->setMaterialParamF32(material, p0, value);
        const s32 p1 = unit->searchMaterialParamIndex(material, "texture_array_index1");
        if (p1 != -1)
            unit->setMaterialParamF32(material, p1, value);
        const s32 p2 = unit->searchMaterialParamIndex(material, "texture_array_index2");
        if (p2 != -1)
            unit->setMaterialParamF32(material, p2, value);
        const s32 p3 = unit->searchMaterialParamIndex(material, "texture_array_index3");
        if (p3 != -1)
            unit->setMaterialParamF32(material, p3, value);
        const s32 p4 = unit->searchMaterialParamIndex(material, "texture_array_index4");
        if (p4 != -1)
            unit->setMaterialParamF32(material, p4, value);
        const s32 p5 = unit->searchMaterialParamIndex(material, "texture_array_index5");
        if (p5 != -1)
            unit->setMaterialParamF32(material, p5, value);
    }
}

void Unk_710260af28::sub_7100F1EA00(gsys::Model* model, f32 value) {
    for (s32 i = 0; i < model->getUnits().size(); ++i) {
        auto* unit = model->getUnits()[i]->mModelUnit;
        const s32 count = unit->getMaterialNum();
        for (s32 material = 0; material < count; ++material) {
            const s32 param = unit->searchMaterialParamIndex(material, "uk_model_tree_scale");
            if (param != -1)
                unit->setMaterialParamF32(material, param, value);
        }
    }
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



s32 Unk_710260af28::sub_7100F1EE98() {
    return 22;
}

s32 Unk_710260af28::sub_7100F1EEA0() {
    return 0;
}

s32 Unk_710260af28::sub_7100F1C3E8() {
    return 1;
}

s32 Unk_710260af28::sub_7100F1C774() {
    return 0;
}
