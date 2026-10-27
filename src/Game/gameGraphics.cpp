#include "Game/gameGraphics.h"
#include <prim/seadScopedLock.h>
#include <common/aglShaderProgramArchive.h>
#include <effect/aglFxOfxBase.h>
#include <effect/aglFxOfxLensFlare.h>
#include <effect/aglFxCloud.h>
#include <g3d/aglNW4FToNN.h>
#include <gsys/gsysModelNW.h>
#include <gsys/gsysModelRenderUnit.h>
#include <gsys/gsysGBuffer.h>
#include <gsys/gsysRenderBufferContext.h>
#include <nn/g3d/ModelObj.h>
#include <nn/g3d/ResMaterial.h>
#include <layer/aglLayer.h>
#include <layer/aglRenderer.h>
#include <math/seadMathCalcCommon.h>
#include <random/seadGlobalRandom.h>
#include <postfx/aglDepthOfField.h>
#include "KingSystem/World/worldDofMgr.h"
#include "KingSystem/World/worldManager.h"
#include "KingSystem/Graphics/gfxUnk_710260af28.h"
#include "KingSystem/System/VFR.h"
#include "KingSystem/Sound/sndSound.h"
#include <utility/aglDynamicTextureAllocator.h>
#include <utility/aglPrimitiveTexture.h>
#include <common/aglShaderProgram.h>
#include <driver/aglGraphicsDriverMgr.h>
#include <gfx/seadGraphicsContext.h>
#include <nvn/nvn_FuncPtrInline.h>

namespace gsys {

// 0x7100f36350 / 0x7100f36354 / 0x7100f36428 - 0x7100f36444: the interface's ten out-of-line virtual
// defaults, each a single return. Graphics overrides eight of them and inherits editorCallback4 / 9.
void IResourceEditorCallback::editorCallback0(const Arg& arg) {}
void IResourceEditorCallback::editorCallback1(const Arg& arg) {}
void IResourceEditorCallback::getModelFmdbPath(const char** path, const Arg& arg) {}
void IResourceEditorCallback::editorCallback3(const Arg& arg) {}
void IResourceEditorCallback::editorCallback4(const Arg& arg) {}
void IResourceEditorCallback::editorCallback5(const Arg& arg) {}
void IResourceEditorCallback::editorCallback6(const Arg& arg) {}
void IResourceEditorCallback::editorCallback7(const Arg& arg) {}
void IResourceEditorCallback::editorCallback8(const Arg& arg) {}
void IResourceEditorCallback::editorCallback9(const Arg& arg) {}

}  // namespace gsys

// 0x7100f2a1d0 and the disposer vtables 0x71024f45a0 / 0x7100f2a100 / 0x7100f2a164: the source is
// SEAD_SINGLETON_DISPOSER(Graphics) (written out here because sInstance is hand-declared in the header).
// NON_MATCHING (the destructor pair): the original calls Graphics::~Graphics() through vtable slot 0x50;
// the rest of the Graphics vtable is not modelled, so ours has the destructor in slot 0.
Graphics::SingletonDisposer_::~SingletonDisposer_() {
    if (this == sStaticDisposer) {
        sStaticDisposer = nullptr;
        Graphics::sInstance->~Graphics();
        Graphics::sInstance = nullptr;
    }
}

Graphics* Graphics::createInstance(sead::Heap* heap) {
    if (!sInstance) {
        auto* buffer = new (heap, alignof(Graphics)) u8[sizeof(Graphics)];
        auto* disposer_buffer = buffer + offsetof(Graphics, mSingletonDisposerBuf_);
        SingletonDisposer_::sStaticDisposer = new (disposer_buffer) SingletonDisposer_(heap);
        sInstance = new (buffer) Graphics;
    }
    return sInstance;
}

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

void Graphics::editorCallback0(const gsys::IResourceEditorCallback::Arg& arg) {
    if (arg._0)
        _284.setBit(22);
}

void Graphics::editorCallback1(const gsys::IResourceEditorCallback::Arg& arg) {}

void Graphics::editorCallback3(const gsys::IResourceEditorCallback::Arg& arg) {
    if (_3a0)
        _3a0->sub_710128F9E0(arg._0);
}

void Graphics::editorCallback5(const gsys::IResourceEditorCallback::Arg& arg) {}

void Graphics::editorCallback6(const gsys::IResourceEditorCallback::Arg& arg) {
    _284.setBit(22);
}

void Graphics::editorCallback7(const gsys::IResourceEditorCallback::Arg& arg) {}

void Graphics::editorCallback8(const gsys::IResourceEditorCallback::Arg& arg) {
    if (arg._8)
        if (_284.isOnBit(22))
            Unk_710260af28::instance()->sub_7100F1B9D0(arg._8);
}

void Graphics::initializeModelSceneEnvObj(gsys::ModelScene* scene,
                                          agl::env::EnvObjBuffer::AllocateArg* arg) {
    _aa0->sub_7100F0B5B8(scene, arg);
}

void Graphics::bindModelScene(gsys::ModelScene* scene) {
    _aa0->sub_7100F13060(scene);
}

void Graphics::unbindModelScene(gsys::ModelScene* scene) {
    _aa0->sub_7100F131C0(scene);
}

void Graphics::clearModelSceneQueue() {
    if (_3b0)
        _3b0->clear();
}

// NON_MATCHING: one extra `mov x3, scene`; the original's call to sub_7100F34848 leaves the
// unused third argument register undefined.
void Graphics::drawModelSceneXlu(agl::DrawContext* draw_context, s32 pass,
                                 gsys::ModelScene* scene,
                                 gsys::ModelRenderContext* context) {
    if (_a88)
        _a88->sub_710129F728(pass, context);
    if (pass != 1)
        return;
    if (context->getViewIndex() == 0) {
        sub_7100F34848(draw_context, 1, scene, context);
        if (_398)
            _398->sub_71012940CC(draw_context, scene, context);
        auto* render_buffer_context = scene->mBuffer.getRenderBufferContext();
        auto* gbuffer = render_buffer_context->getContext(context->getViewIndex())->mGBuffer;
        gbuffer->invalidate(gsys::GBuffer::Resolution(0), gsys::GBuffer::BufferType(2));
        gbuffer->invalidate(gsys::GBuffer::Resolution(0), gsys::GBuffer::BufferType(1));
        gbuffer->invalidate(gsys::GBuffer::Resolution(1), gsys::GBuffer::BufferType(1));
        render_buffer_context->release(context->getViewIndex(), 0x200000);
        gbuffer->setMaterialIdMask(gsys::GBuffer::MaterialIdMask(0), 0xf);
        gbuffer->setMaterialIdMask(gsys::GBuffer::MaterialIdMask(1), 0xe);
        gbuffer->setMaterialIdMask(gsys::GBuffer::MaterialIdMask(2), 0x1f);
    }
    if (_aa0 && (agl::lyr::Renderer::instance()->get_1b8() & 2) == 0)
        _aa0->sub_7100F12828(draw_context, context);
}

void Graphics::drawModelSceneFinalImage(agl::DrawContext* draw_context, s32 pass,
                                        gsys::ModelScene* scene,
                                        gsys::ModelRenderContext* context) {
    if (pass != 0)
        return;
    if (_3b0)
        _3b0->drawDebug(draw_context, context->getViewIndex());
    if (_3a0)
        _3a0->sub_710128F888(draw_context, context);
    if (_3a8)
        _3a8->sub_7100EFF5E8(draw_context, context);
    if (_378)
        _378->sub_710128A988(draw_context, context->getViewIndex());
    if (_668)
        _668->sub_710128CF08(draw_context, context->getViewIndex());
}

void Graphics::resetModelSceneHostIO(gsys::ModelRenderContext* context) {}

void Graphics::calcModelSceneViewGPU(gsys::ModelRenderContext* context) {
    if (_378)
        _378->sub_71012890FC(context->getViewIndex());
    if (_b38)
        _b38->sub_71012920EC(context->getViewIndex());
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

// 0x7100f2b424 (placeholder name): whether any material of the unit has render view option 4
// enabled in view 0. Called by the world camera-frustum pass 0x71010b84f0 for each model unit.
bool Graphics::sub_7100F2B424(gsys::ModelUnit* unit) {
    bool all_disabled = true;
    for (s32 i = 0; i < unit->getMaterialNum(); ++i)
        all_disabled &= !unit->isRenderViewOptionEnabled(i, gsys::ModelEnum::RenderViewOption(4), 0);
    return !all_disabled;
}

// NON_MATCHING: clang folds the first target-pointer load into a pre-indexed load (`ldr x9,[x1,#0x10]!`)
// and then reloads the remaining stores through the advanced base; the original reloads [x1,#0x10] every
// time. Same stores and branches otherwise.
void Graphics::sub_7100F2DF04(Unk_7100F2DF04Arg* arg) {
    switch (arg->_4) {
    case 0xd:
        if (arg->_0 != 1)
            return;
        arg->_10->_4 = 0xff;
        arg->_10->_28 = 0x02020202;
        arg->_10->_2c = 3;
        arg->_10->_2d = 3;
        break;
    case 0xe:
        if (arg->_0 != 1)
            return;
        arg->_10->_4 = 0xff;
        arg->_10->_28 = 0x02020202;
        break;
    default:
        return;
    }
    arg->_10->_64 = 5;
}

// NON_MATCHING: the switch form reproduces the original's branch layout (2..7 range test as
// `cmp #6; b.hs`, pass 0 / 1 arm before the pass-8 arm) and the shared setPassViewProjIndex
// tail-call epilogue after the 2..7 arm. The first scene's Context lookup still differs in one
// instruction: clang selects `madd` (and loads the Buffer size before its pointer) where the
// original has `umaddl` / base first. The same accessor in the other Graphics and
// ModelSceneBuffer functions is `madd` too, so this is local to the original's expression here.
// 0x7100f34f1c: the procedural-model pass hook. For pass 2..7 it stores this object's
// pass-view-projection byte in `cache`; pass 0 / 1 invalidates the first scene's GBuffer write
// cache first (the map states 3 / 6 / 7 are the ones drawn procedurally); pass 8 takes the value
// from the particle editor singleton.
void Graphics::drawProceduralPassMaybe(s32 pass, gsys::ModelRenderCache* cache) const {
    switch (pass) {
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
        if (!usesPassViewProjMaybe())
            return;
        cache->setPassViewProjIndex(_19);
        return;
    case 0:
    case 1: {
        gsys::RenderBufferContext* buffer =
            mModelScenes.unsafeAt(0)->mBuffer.getRenderBufferContext();
        gsys::RenderBufferContext::Context* context = buffer->getContext(cache->getViewIndex());
        context->mGBuffer->invalidateGPUWriteCache(cache->getDrawContext(), "gfx::Barrior",
                                                   gsys::GBuffer::Resolution(0));
        return;
    }
    case 8:
        if (!usesPassViewProjMaybe())
            return;
        cache->setPassViewProjIndex(Unk_710260af28::instance()->sub_7100F1EEA0());
        return;
    default:
        return;
    }
}

// 0x7100f2de80 (unnamed in the CSV; free function): draws one particle pass of a model render cache
// in the particle editor; the fourth argument is not used.
void sub_7100F2DE80(agl::DrawContext* draw, const gsys::RenderBufferContext& context,
                    gsys::ModelSceneContext* scene, void* unk, gsys::ModelRenderCache* cache) {
    cache->setPassViewProjIndex(Unk_710260af28::instance()->sub_7100F1EE98());
    scene->drawParticle(draw, context, static_cast<gsys::ParticlePass>(0x1a),
                        static_cast<gsys::ParticleShaderType>(0), 0, cache);
    cache->setPassViewProjIndex(Unk_710260af28::instance()->sub_7100F1EEA0());
}

bool Graphics::sub_7100F35E5C(f32 value, const sead::Vector3f* a, const sead::Vector3f* b) {
    if (!_378)
        return false;
    _378->sub_7101289934(0, a, b, value, ksys::VFR::instance()->getDeltaFrame());
    return (_378->mBlocks.getBufferPtr()->_1500 >> 2) & 1;
}

void Graphics::sub_7100F3590C(f32 value) {
    _370->sub_710129558C(value, 0);
}

void Graphics::sub_7100F35918(const sead::Color4f& color) {
    _370->sub_7101295560(0, color);
}

void Graphics::sub_7100F3592C(const sead::Vector3f& value) {
    _b70->_110 = value;
}

f32 Graphics::sub_7100F35F28() const {
    return _378->mBlocks.getBufferPtr()->_1520;
}

f32 Graphics::sub_7100F35F38() const {
    return _378->mBlocks.getBufferPtr()->_1524;
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

// 0x7100f300d0 (placeholder name): sets the demo toon light adjust colour parameter on the
// environment unit's current material.
void Graphics::sub_7100F300D0(const sead::Color4f& color) {
    auto lock = sead::makeScopedLock(_ed8);
    setMaterialParamColor4f(_ea8, _f58, "uking_dynamic_toon_light_adjust_for_demo", color);
}

void Graphics::setEnvMaterialParamF32(const sead::SafeString& name, f32 value) {
    auto lock = sead::makeScopedLock(_ed8);
    setMaterialParamF32(_ea8, _f58, name.cstr(), value);
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
    _ad8->_508 = 1;
}

void Graphics::sub_7100F35DC0(gsys::Layer* layer) {
    _ad8->setLayer(layer);
    _ad8->adjustTrimViewportToLayer();
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

KSYS_VISIBILITY_HIDDEN const f32 cGrudgeResetDistance = 20.0f;
KSYS_VISIBILITY_HIDDEN const f32 cItemFilterFadeStep = 0.4f;

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

void Graphics::initBeforeStageGenB() {}

void Graphics::initBeforeStageGenA() {}

// 0x7100f2dda0 (placeholder name): turns the cloud pass off and drops the lens flare enable flag.
void Graphics::sub_7100F2DDA0() {
    mModelScenes.unsafeAt(0)->mCloud->_460 = 0;
    if (mModelScenes.unsafeAt(0)->mOfxManager->getOfx<agl::fx::OfxLensFlare>(0))
        _284.resetBit(10);
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

// 0x7100f37b5c
void Unk_71024f4cc0::initShaderProgram(agl::ShaderProgramArchive* archive, sead::Heap* heap) {
    agl::ShaderProgram* program =
        archive->getShaderProgram(archive->searchShaderProgramIndex("map_visit_mark"));
    program->createUniformBlock(2, heap);
    program->setUniformName(0, "uProjectionMatrix");
    program->setUniformName(1, "uParamater");
    program->createImageLocation(2, heap);
    program->setAttributeName(0, "aPosition");
    program->setAttributeName(1, "aExtInfo");
}

// 0x7100f3ecc4 (CSV name): a free wrapper in the Graphics TU that feeds the current core's delta
// frame to the per-frame graphics update.
void gameSceneCalcGraphicsStuff() {
    Graphics* graphics = Graphics::instance();
    if (graphics == nullptr)
        return;
    graphics->sub_7100F2F20C(ksys::VFR::instance()->getDeltaFrame());
}

namespace gfx {

// 0x71024f4394 (defined in gameUnk_710129175c.cpp): hidden-visibility constant, so the load is a
// direct adrp + ldr rather than a folded literal.
KSYS_VISIBILITY_HIDDEN extern f32 cNoiseGaugeAmplitude;
// 0x71024f4390: the second constant in the same block, uploaded as the fourth parameter word.
KSYS_VISIBILITY_HIDDEN extern f32 cNoiseGaugeUnk0Maybe;

// 0x7100f20000: constructs the sampler, the scratch render buffer / target colour, the viewport, the
// uniform block, the two GPU memory blocks, the vertex / index streams and the debug texture page.
NoiseGauge::NoiseGauge() {}

// 0x7100f200b8: destroys the uniform block's GPU buffer first, then the members in reverse order.
NoiseGauge::~NoiseGauge() {
    mUniformBlock.destroy();
}

// 0x7100f201cc: fills the 16 noise colours, sets up the debug texture page, the uniform block,
// the vertex/index buffers and the vertex attribute.
// NON_MATCHING: the target compares the byte-offset induction variable at the loop bottom and
// keeps the amplitude in s10 across the random call; ours compares the element index and sinks
// the load. Same instruction set, different IV/load scheduling.
void NoiseGauge::initMaybe(sead::Heap* heap) {
    mPoints.tryAllocBuffer(16, heap, 8);
    for (s32 i = 0; i < 16; ++i) {
        sead::Vector4f& point = mPoints[i];
        point.x = sead::Mathf::pow(0.9f, f32(i));
        point.y = sead::GlobalRandom::instance()->getF32();
        point.z = (sead::GlobalRandom::instance()->getF32() * 2.0f - 1.0f) * cNoiseGaugeAmplitude;
        point.w = sead::GlobalRandom::instance()->getF32();
    }

    mRenderBuffer.setRenderTargetColorNullAll();
    mRenderBuffer.setRenderTargetColor(&mRenderTargetColor, 0);
    mRenderBuffer.setRenderTargetDepth(nullptr);

    mDebugPage.setUp(1, "NoiseGauge", heap);

    mUniformBlock.startDeclare(2, heap);
    mUniformBlock.declare_(agl::UniformBlock::cType_6, 1, 0, 1);
    mUniformBlock.declare_(agl::UniformBlock::cType_6, 0x10, 0, 1);
    mUniformBlock.create(heap, 2, 1);

    sub_7100F203D0(heap);

    mVertexAttribute.create(1, heap);
    mVertexAttribute.setVertexStream(0, &mVertexBuffer, 0);
    mVertexAttribute.setUp();
}

// 0x7100f203d0 (placeholder name): allocates and fills the vertex and index GPU blocks.
// NON_MATCHING: the original constructs one extra discarded GPUMemAddrBase(block, 0) at the start
// of each half (four address objects in all, of which two are never read); the two setUp call
// forms and every other instruction match. Frame size differs by those two stack objects.
void NoiseGauge::sub_7100F203D0(sead::Heap* heap) {
    mVertexData.allocBuffer_(0x80, heap, 4, agl::MemoryAttribute::Default);
    for (s32 i = 0; i < 0x80; ++i)
        static_cast<u8*>(mVertexData.getAddress())[i] = u8(255.0f * f32(i) / 127.0f);

    mVertexBuffer.setUpBuffer(agl::ConstGPUMemVoidAddr(mVertexData, 0), 1, 0x80);
    mVertexBuffer.setUpStream(0, agl::VertexStreamFormat(1), 0, false);

    mIndexData.allocBuffer_(0x100, heap, 4, agl::MemoryAttribute::Default);
    for (s32 i = 0; i < 0x80; ++i)
        static_cast<u16*>(mIndexData.getAddress())[i] = u16(i);

    agl::GPUMemAddrBase indexAddress(mIndexData, 0);
    mIndexStream.setUpStream_(indexAddress, agl::IndexStreamFormat(1), 0x80);
    mIndexStream.setPrimitiveType(NVN_DRAW_PRIMITIVE_LINE_STRIP);
}

// 0x7100f20774 (placeholder name): uploads the gauge parameters and the 16 noise points to the
// uniform block, then flushes the block's GPU cache.
// NON_MATCHING: target's 16-byte parameter blocks are built as two 8-byte stores per block
// (128/_10 then _14/const, and x/y then zero/w); ours stores each field separately, costing two
// extra instructions and a different load order in the flush block. Same instruction set.
void NoiseGauge::updateUniformBlockMaybe() {
    mUniformBlock.dcbz(0);

    {
        struct Data {
            f32 a, b, c, d;
        };
        Data data = {128.0f, _10, _14, cNoiseGaugeUnk0Maybe};
        mUniformBlock.setData(0, &data);

        for (s32 i = 0; i < 16; ++i) {
            const sead::Vector4f& point = mPoints[i];
            data.a = point.x;
            data.b = point.y;
            data.c = 0.0f;
            data.d = point.w;
            mUniformBlock.setData(1, &data, i);
        }
    }

    mUniformBlock.flushCPUCache();
}

// 0x7100f20580 (name is a guess): advances the gauge angle and the 16 noise points by the frame
// delta, chases the gauge parameter and uploads the new values.
void NoiseGauge::updateMaybe() {
    mFlags = (mFlags & 1) ? (mFlags | 2) : (mFlags & ~2);
    if (mFlags & 2)
        return;

    const s32 soundCount = ksys::snd::ExpressionSoundCtrl::instance()->mHandles.size();
    f32 speed = 0.0f;
    if (mFlags & 0x400)
        speed += mScale * sNoiseGaugeParams.speedScale;
    if (mFlags & 0x800) {
        s32 count = soundCount - sNoiseGaugeParams.soundCountBias;
        count = sead::Mathi::max(count, 0);
        speed += sNoiseGaugeParams.speedPerSound * f32(count);
    }

    _10 += (speed - _10) * sNoiseGaugeParams.chaseRate;
    _10 = sead::Mathf::clamp(_10, 0.0f, 1.0f);

    const f32 tau = sead::Mathf::pi2();
    const f32 delta = ksys::VFR::instance()->getDeltaFrame();
    _14 += delta * cNoiseGaugeAngleSpeedMaybe * tau;
    while (_14 > tau)
        _14 -= tau;

    for (s32 i = 0; i != 16; ++i) {
        sead::Vector4f& point = mPoints[i];
        point.y += delta * point.z * tau;
        while (point.y > tau)
            point.y -= tau;
        while (point.y < 0.0f)
            point.y += tau;
    }

    updateUniformBlockMaybe();
}

// 0x7100f20874 (name is a guess): toggles the uniform block's buffer index each frame unless the
// gauge's flag bit 1 is set, and rebinds the CPU address to the other block.
void NoiseGauge::toggleUniformBufferMaybe() {
    if (!(mFlags & 2)) {
        const s32 index = 1 - _3a8;
        _3a8 = index;
        mUniformBlock.setBufferIndexMaybe(index);
    }
}

// 0x7100f208e4 (placeholder name): if the scratch texture has not been allocated yet, allocates it,
// draws the gauge into it at two line widths and applies it to mSampler.
// NON_MATCHING: same instructions, but the physical-area normalization selects in the float
// registers (fcsel s) where the target selects the float bits in the integer registers (csel w),
// the rest of the frame is 0x10 larger (stack colouring), and the index-stream call arguments are
// evaluated in a different order. Register/slot allocation only.
void NoiseGauge::drawMaybe(f32 scale, agl::DrawContext* context) {
    if (mDynamicTexture)
        return;

    const f32 gauge_scale =
        sead::Mathf::clamp(scale * sNoiseGaugeParams.drawScale, 0.1f, 10.0f);
    const s32 size = s32(gauge_scale * f32(sNoiseGaugeParams.maxTextureSize));

    mDynamicTexture = agl::utl::DynamicTextureAllocator::instance()->alloc(
        context, "gfx::NoiseGauge", agl::TextureFormat::cTextureFormat_R8_uNorm, size, size, 1,
        nullptr, agl::utl::DynamicTextureAllocator::AllocateType(0), true, false);
    mDynamicTexture->setCompSel(agl::TextureCompSel::cTextureCompSel_One,
                                agl::TextureCompSel::cTextureCompSel_One,
                                agl::TextureCompSel::cTextureCompSel_One,
                                agl::TextureCompSel::cTextureCompSel_Red);
    mDynamicTexture->updateNVNtexture();
    mSampler.applyTextureData(*mDynamicTexture);
    mRenderTargetColor.applyTextureData(*mDynamicTexture, mRenderTargetColor.getMipLevel(),
                                       mRenderTargetColor.getLayer());

    const f32 extent = f32(size);
    const f32 width1 = gauge_scale * sNoiseGaugeParams.lineWidth1;
    const f32 width2 = gauge_scale * sNoiseGaugeParams.lineWidth2;
    mRenderBuffer.setVirtualSize(sead::Vector2f(extent, extent));
    mRenderBuffer.setPhysicalArea(0.0f, 0.0f, extent, extent);
    mViewport.setByFrameBuffer(mRenderBuffer);

    mRenderBuffer.bind(context);
    sead::Viewport viewport(mRenderBuffer);
    mRenderBuffer.fastClear(context, 0, 1, sead::Color4f(0.0f, 0.0f, 0.0f, 0.0f), 1.0f, 0,
                            viewport, true);

    sead::GraphicsContext graphics_context;
    graphics_context.setDepthTestEnable(false);
    graphics_context.setDepthWriteEnable(0);
    graphics_context.setBlendEnable(true, 0);
    graphics_context.setBlendControl(0, 2, 2, 2, 2, 1, 1);
    graphics_context.apply(context);

    agl::ShaderProgram* program = sNoiseGaugeParams.program;
    program->activate(context, true);
    const agl::UniformBlockLocation& location = program->getUniformBlockLocation(0);
    mUniformBlock.setUniform(context, mUniformBlock.getGPUAddressMaybe(), location, 0,
                             mUniformBlock.getBlockSizeMaybe());
    mVertexAttribute.activate(context);

    agl::driver::GraphicsDriverMgr::instance()->setLineWidth(context, width1);
    if (mIndexStream.getIndexCount()) {
        nvnCommandBufferDrawElements(context->getCommandBuffer()->ToData()->pNvnCommandBuffer,
                                     mIndexStream.getPrimitiveType(),
                                     NVNindexType(mIndexStream.getFormat()),
                                     mIndexStream.getIndexCount(), mIndexStream.getBufferAddress());
    }

    agl::driver::GraphicsDriverMgr::instance()->setLineWidth(context, width2);
    if (mIndexStream.getIndexCount()) {
        nvnCommandBufferDrawElements(context->getCommandBuffer()->ToData()->pNvnCommandBuffer,
                                     mIndexStream.getPrimitiveType(),
                                     NVNindexType(mIndexStream.getFormat()),
                                     mIndexStream.getIndexCount(), mIndexStream.getBufferAddress());
    }

    mRenderTargetColor.invalidateGPUCache(context);
}

// 0x7100f20c88: frees the noise gauge's scratch texture and puts the Black2D sampler (mSamplers[2],
// +0x38) back on the gauge's sampler.
void NoiseGauge::releaseMaybe() {
    if (mDynamicTexture) {
        agl::utl::DynamicTextureAllocator::instance()->free(mDynamicTexture);
        mDynamicTexture = nullptr;
        mSampler.applyTextureData(
            agl::utl::PrimitiveTexture::instance()->getBlack2DSampler()->getTextureData());
    }
}

}  // namespace gfx
