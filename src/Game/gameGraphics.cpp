#include "Game/gameGraphics.h"
#include <prim/seadScopedLock.h>
#include <g3d/aglNW4FToNN.h>
#include <gsys/gsysModelNW.h>
#include <gsys/gsysModelRenderUnit.h>
#include <nn/g3d/ModelObj.h>
#include <nn/g3d/ResMaterial.h>
#include <layer/aglLayer.h>
#include <math/seadMathCalcCommon.h>

Unk_7100f35df8::Unk_7100f35df8() = default;

Unk_7100f35df8* Graphics::sub_7100F35E54() const {
    return _ae0;
}

void Graphics::sub_7100F35FA4(bool value, bool second) {
    if (second)
        _284.changeBit(12, value);
    else
        _284.changeBit(11, value);
    _280 |= 1;
}

void Graphics::sub_7100F2E06C() {
    _284.setBit(22);
}

void Graphics::sub_7100F35F50(agl::lyr::Layer* layer, bool value) {
    if (layer)
        layer->sub_7100B60DC4(value);
}

void Graphics::sub_7100F35F68(bool value) {
    _284.changeBit(14, value);
    if (_398) {
        if (value)
            _398->mFlags.setBit(0);
        else
            _398->mFlags.resetBit(0);
    }
}

void Graphics::sub_7100F2AF70(u8 map) {
    auto lock = sead::makeScopedLock(_f18);
    _f59 = map;
}

void Graphics::sub_7100F2AFAC(u8 value) {
    auto lock = sead::makeScopedLock(_f18);
    _f5b = value;
}

void Graphics::sub_7100F2AFE8(u8 value) {
    auto lock = sead::makeScopedLock(_f18);
    _f5d = value;
}

void Graphics::sub_7100F2B024(u8 value) {
    auto lock = sead::makeScopedLock(_f18);
    _f5f = value;
}

f32 Graphics::sub_7100F35F28() const {
    return _378->_18->_1520;
}

f32 Graphics::sub_7100F35F38() const {
    return _378->_18->_1524;
}

void Graphics::sub_7100F32AC8(sead::Camera* camera, void* unk) {
    _e08 = camera;
    _e10 = unk;
}

void Graphics::sub_7100F2FAAC(f32 exposure, bool force) {
    if (force || _f5a != 4)
        setEnvMaterialParamF32("uking_dynamic_exposure", exposure);
}

void Graphics::sub_7100F2FB6C(f32 ratio) {
    _e84 = ratio;
    setEnvMaterialParamF32("uking_dynamic_proj_shadow_off", 1.0f - ratio);
}

void Graphics::sub_7100F2FC24(f32 ratio) {
    _e80 = ratio;
    setEnvMaterialParamF32("uking_dynamic_base_light_change_ratio", 1.0f - ratio);
}

void Graphics::setDynamicCloudRatio(f32 ratio) {
    setEnvMaterialParamF32("uking_dynamic_cloud_ratio", sead::Mathf::clamp(1.0f - ratio, 0.0f, 1.0f));
}

// NON_MATCHING: the original loads _e8c and materialises 1.0f once before the first lock (kept across the calls).
void Graphics::sub_7100F2FF08(f32 ratio, f32 scale) {
    _e88 = ratio;
    if (_370)
        _370->sub_71012955AC(1.0f - scale, 0);
    const f32 shadowRatio = _e88;
    setEnvMaterialParamF32("uking_dynamic_depth_shadow_off", 1.0f - shadowRatio);
    setEnvMaterialParamF32("uking_dynamic_depth_shadow_scale", 1.0f - scale);
    setEnvMaterialParamF32("uking_dynamic_world_shadow_off", shadowRatio * ((1.0f - _e8c) - 1.0f) + 1.0f);
}

void Graphics::sub_7100F2E0F4(gsys::ModelNW* model, const nn::gfx::ResTexture* texture) {
    if (!texture) {
        model->setDisplayListDirty();
        return;
    }

    auto* model_obj = model->getModelObj();
    for (s32 i = 0; i < model_obj->GetNumMaterials(); ++i) {
        auto* material = model_obj->GetMaterial(i);
        for (s32 j = 0; j < material->GetResource()->_a9; ++j) {
            if (agl::g3d::MaterialObj::GetResTexture(material, j) != texture)
                continue;
            for (s32 k = 0; k < model_obj->GetNumShapes(); ++k) {
                if (model->getModelRenderUnit(k)->getMaterialIndex() == i)
                    model->setDisplayListDirty(k);
            }
        }
    }
}

void Graphics::sub_7100F2E2A4() {
    if (_b38 && _ae0 && (_b38->mRecords(0)._1f91 & 2)) {
        Unk_710129175c::Result result;
        _b38->sub_710129276C(0, &result);
        _ae0->_8 = result._0;
        _ae0->_10 = result.bounds;
        _ae0->_30 = result._18;
        _ae0->_4c = result._2c;
        _ae0->_20 = result._1c;
        _ae0->_0 = true;
    }
    if (_388)
        _388->sub_7100F1AC58();
    if (_3a0)
        _3a0->sub_710128F2A4();
    if (_3a8)
        _3a8->sub_7100EFE030();
}

void Graphics::sub_7100F2F1C8(Unk_7100f35df8* settings) {
    if (_ae0)
        return;
    _ae0 = settings;
    settings->_0 = false;
    _b38->sub_71012920C4(0);
}

void Graphics::sub_7100F2F1E8(Unk_7100f35df8* settings) {
    if (!_ae0 || _ae0 == settings) {
        _ae0 = nullptr;
        _b38->sub_71012920C4(0);
    }
}

// NON_MATCHING: the mode byte store is scheduled before the comparisons.
void Unk_71012a20e0::sub_71012A2268(u32 mode) {
    const bool reset = _1b0 == 2 || mode == 2;
    _1b0 = mode;
    switch (_1b0) {
    case 0:
        _194 = 0.2f;
        break;
    case 1:
        _194 = 0.4f;
        break;
    case 2:
        _194 = 0.0f;
        break;
    }
    if (reset)
        _190 = _194;
}
