#include "Game/gameGraphics.h"
#include <prim/seadScopedLock.h>
#include <effect/aglFxOfxBase.h>
#include <effect/aglFxOfxLensFlare.h>
#include <g3d/aglNW4FToNN.h>
#include <gsys/gsysModelNW.h>
#include <gsys/gsysModelRenderUnit.h>
#include <nn/g3d/ModelObj.h>
#include <nn/g3d/ResMaterial.h>
#include <layer/aglLayer.h>
#include <math/seadMathCalcCommon.h>
#include <postfx/aglDepthOfField.h>
#include "KingSystem/World/worldDofMgr.h"
#include "KingSystem/World/worldManager.h"

// 0x7100f00018: clears bit 3 of the object's flag word.
void sub_7100F00018(Unk_7100efd9b8Obj* object) {
    if (object->_638 & 8)
        object->_638 &= ~8;
}

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

// NON_MATCHING: the original's static object sits 12 bytes before its guard variable (a 12-byte static
// precedes it in its translation unit), so the guard and value offsets differ from ours.
const sead::Vector2i& Graphics::getScreenSize() {
    static const sead::Vector2i size(1920, 1080);
    return size;
}

// NON_MATCHING: same static block layout difference as getScreenSize.
const sead::Vector2i& Graphics::getReferenceScreenSize() {
    static const sead::Vector2i size(1280, 720);
    return size;
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

void Graphics::setRainRatio(f32 ratio, f32 rainfall) {
    const f32 rain = (1.0f - _398->_254) * ratio;
    setEnvMaterialParamF32("uking_dynamic_rain_ratio", rain);
    setEnvMaterialParamF32("uking_dynamic_rainfall", rainfall);
    const bool raining = rain > 0.0f;
    const s32 variation = mModelScenes.front()->_52e0->_230 ? 2 : raining;
    _e98->setShaderAssignVariation(static_cast<gsys::ModelEnum::ShaderAssignType>(0), variation);
}

// NON_MATCHING: register allocation (the hyperfocal distance / rate share d12 instead of d14, the -0.1 / 0.9
// constants take d13 / d14 instead of d12 / d13).
bool Graphics::sub_7100F309FC(const DofCameraArg& arg) {
    const f32 tan = std::tan(arg.fovy * 0.5f);
    if (tan <= sead::Mathf::epsilon())
        return false;

    const f32 focal = 17.5f / tan;
    const f32 hyperfocal = focal + focal * focal / (arg.f_number * 0.026f);
    const f32 distance = arg.focus_distance * 1000.0f;
    const f32 numerator = (distance - focal) * (distance - focal);

    const f32 near_denominator = (distance + hyperfocal - 2.0f * focal) * 1000.0f;
    const f32 near = near_denominator > 0.0f ? numerator / near_denominator : 100000.0f;
    const f32 near_pow = sead::Mathf::powTable(near, 1.4f);
    const f32 near_start = std::max(near + (near_pow - near) * -0.1f / 0.9f, 0.0f);

    f32 far_start;
    f32 far_end;
    f32 rate;
    const f32 far_denominator = (hyperfocal - distance) * 1000.0f;
    if (far_denominator > 0.0f) {
        const f32 far = numerator / far_denominator;
        far_end = std::min(sead::Mathf::powTable(far, 1.4f), 3000.0f);
        far_start = sead::Mathf::clamp(far + (far_end - far) * -0.1f / 0.9f, 0.0f, 1000.0f);
        rate = 0.0f;
    } else {
        far_start = 1000.0f;
        far_end = 3000.0f;
        rate = 1.0f;
    }

    if (auto* dof = mModelScenes.front()->mDepthOfField) {
        auto& param = dof->getParameter();
        far_start += (1000.0f - far_start) * rate;
        far_end += (3000.0f - far_end) * rate;
        param.setEnableDofFar(true);
        param.setStartEnd(far_start + arg.focus_distance, far_end + arg.focus_distance);
        if (ksys::world::Manager::instance()->getDofMgrUnchecked()->get_170())
            param.setEnableDofFarMax(true);
        else
            param.setEnableDofFarMax(false);
        param.setFarStartEnd(arg.focus_distance - near_pow, arg.focus_distance - near_start);
    }
    return true;
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
    const bool reset = _1b0b == 2 || mode == 2;
    _1b0b = mode;
    switch (_1b0b) {
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

// NON_MATCHING: the compiler computes the list address (add) before the index mask (and); the
// original computes the mask first. The body and every other instruction match.
bool Unk_71012a20e0::sub_71012A2768() {
    if (!(_498 & 1))
        return false;
    if (mCubeMapMgr->mUnits.size() < 2u)
        return false;
    const s32 index = _1b3 & 1;
    auto* unit = mCubeMapMgr->mUnits.nth(index);
    if (!mCubeMapMgr->isUnitRenderingFinished(unit))
        return false;
    mCubeMapMgr->setUnitPosition(unit, _198);
    mCubeMapMgr->setUnitBufferClear(unit, false);
    mCubeMapMgr->pushUpdateRequest(unit);
    const f32 next = _190 - 1.0f;
    _1b0 ^= 0x1000000;
    _190 = next > _194 ? next : _194;
    return true;
}









void Graphics::sub_7100F35DE8() {
    _ad8[0x508] = 1;
}

void Graphics::sub_7100F35DB0() {
    _284.set(0x10000);
}

// 0x7100c0a9b8: sead::PtrArrayImpl's out-of-line push (declaration only).
void sub_7100C0A9B8(sead::PtrArrayImpl* array, void* element);

void Graphics::sub_7100F2B3DC(sead::PtrArrayImpl* array) {
    if (_170 == 0)
        return;
    void** it = _178;
    void** end = it + _170;
    while (it != end)
        sub_7100C0A9B8(array, *it++);
}

namespace ksys::tera {
extern u8 sUnk_710260B184 KSYS_VISIBILITY_HIDDEN;
extern u8 sUnk_710260B188 KSYS_VISIBILITY_HIDDEN;
}  // namespace ksys::tera

u8 sub_7100F3A500() {
    return ksys::tera::sUnk_710260B184;
}

u8 sub_7100F3A51C() {
    return ksys::tera::sUnk_710260B188;
}

void sub_7100F3A528(u32 value) {
    ksys::tera::sUnk_710260B188 = value & 1;
}

void Graphics::sub_7100F2DDF0(s32 preset) {
    auto* lens_flare = mModelScenes[0]->mOfxManager->getOfx<agl::fx::OfxLensFlare>(0);
    if (!lens_flare)
        return;
    if (preset < 0) {
        _284.resetBit(10);
    } else {
        _284.setBit(10);
        if (mLensFlarePreset != preset) {
            mLensFlarePreset = preset;
            lens_flare->loadPresetByIndex(preset, false);
        }
    }
}
