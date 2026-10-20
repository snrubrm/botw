#pragma once

#include <cstddef>
#include <gsys/gsysIModelRigObj.h>
#include <gsys/gsysModelRig.h>
#include "KingSystem/Graphics/gfxLocationalLightMgr.h"

namespace sead::hostio {
class Context;
}

class Unk_7102519378;

namespace gsys {
class ModelUnit;
}

namespace ksys::gfx {

class LocationalLightRig;

// F0CAF0 allocates 0x88-byte records and calls F18190. Model::pushBack uses
// the inherited node at +8; F16F08 links the two owned nodes at +0x18/+0x28.
class LocationalLightMgr::ObjectLight::Light : public gsys::IModelRigObj {
public:
    Light();
    virtual ~Light();
    void update(gsys::ModelUnit* unit, u16 visibility_mask, f32 delta_time) override;
    // 0x7100f180c0: the same update without a model unit (the binding's per-frame refresh).
    void update();
    // The named EnvObj drawDebug ABI is forwarded by F17D90 to this slot.
    // Receiver constness is inferred from the read-only debug traversal.
    virtual void drawDebug(agl::DrawContext* context, const sead::Matrix34f& view,
                           const sead::Matrix44f& projection, int view_index) const;

    sead::ListNode mRigNode;
    sead::ListNode mObjectNode;
    u8 mFlags = 0;
    LocationalLightRig* mRig = nullptr;
    ObjectLight* mObjectLight = nullptr;
    s16 mBoneIndex = -1;
    s16 mEndBoneIndex = -1;
    u16 mVisibilityMask = 0;
    // F172F0 writes both bone/world positions; the constructor leaves them uninitialized.
    sead::Vector3f mPosition;
    sead::Vector3f mEndPosition;
    s32 mLightType = -1;
    Unk_7102519378* mRenderLight = nullptr;
    // F177F4 advances these with the frame step and FlickeringSpeed parameter.
    f32 mFadeTimer = 0;
    f32 mFlickeringPhase = 0;
};
KSYS_CHECK_SIZE_NX150(LocationalLightMgr::ObjectLight::Light, 0x88);
static_assert(offsetof(LocationalLightMgr::ObjectLight::Light, mRigNode) == 0x18);
static_assert(offsetof(LocationalLightMgr::ObjectLight::Light, mObjectNode) == 0x28);
static_assert(offsetof(LocationalLightMgr::ObjectLight::Light, mRig) == 0x40);
static_assert(offsetof(LocationalLightMgr::ObjectLight::Light, mPosition) == 0x58);
static_assert(offsetof(LocationalLightMgr::ObjectLight::Light, mRenderLight) == 0x78);
static_assert(offsetof(LocationalLightMgr::ObjectLight::Light, mFadeTimer) == 0x80);

// Native F18540 registers "LocationalLightRig", factory F18508 and size 0x3a8.
// The namespace follows the owning game graphics subsystem. F160DC constructs
// ModelRig at +0, the mutex at +0x260, and these seven named parameter objects.
// Lifetime and virtual bodies remain undecompiled. The appended event slot is
// still unresolved: our vtable has one slot fewer than the original's, so the
// secondary vtable address point is at +0x100 instead of +0x108 in the
// constructor.
class LocationalLightRig : public gsys::ModelRig {
    SEAD_RTTI_OVERRIDE(LocationalLightRig, agl::env::EnvObj)
public:
    // 0x7100f18508: the factory the rig registration 0x7100f18540 passes.
    static LocationalLightRig* create(sead::Heap* heap);
    LocationalLightRig();
    ~LocationalLightRig() override;
    s32 getTypeID() const override;
    void m23(gsys::Model* model) override;
    void m24(gsys::Model* model, const gsys::BoneAccessKey& key,
             const sead::SafeString& name) override;
    void m25(gsys::Model* model, const gsys::MaterialAccessKey& key,
             const sead::SafeString& name) override;
    void m26(gsys::Model* model, int unit_index) override;
    void drawDebug(agl::DrawContext* context, const sead::Matrix34f& view,
                   const sead::Matrix44f& projection, int view_index) const override;
    // F17E50 forwards the actual context to ParameterBase::genMessageParameter.
    // This new game slot is separate from ModelRig's four registration callbacks.
    virtual void genMessage(sead::hostio::Context* context);

    // 0x7100f177f4 (declaration only): computes the light transform and writes the record.
    void sub_7100F177F4(Unk_7102519378* render_light,
                        LocationalLightMgr::ObjectLight::Light* light, gsys::ModelUnit* unit);

    // drawDebug locks it from a const method.
    mutable sead::CriticalSection mCS;
    LocationalLightMgr* mLightMgr = nullptr;
    sead::OffsetList<LocationalLightMgr::ObjectLight::Light> mLights;
    agl::utl::Parameter<s32> mLightType;
    agl::utl::Parameter<sead::Color4f> mColor;
    agl::utl::Parameter<f32> mIntensity;
    agl::utl::Parameter<f32> mInnerRadius;
    agl::utl::Parameter<bool> mEnableEffectMoth;
    agl::utl::Parameter<f32> mFlickeringIntensityRate;
    agl::utl::Parameter<f32> mFlickeringSpeed;

protected:
    void m11(int index, sead::Heap* heap) override;
};
KSYS_CHECK_SIZE_NX150(LocationalLightRig, 0x3a8);
static_assert(offsetof(LocationalLightRig, mCS) == 0x260);
static_assert(offsetof(LocationalLightRig, mLightMgr) == 0x2a0);
static_assert(offsetof(LocationalLightRig, mLights) == 0x2a8);
static_assert(offsetof(LocationalLightRig, mLightType) == 0x2c0);
static_assert(offsetof(LocationalLightRig, mColor) == 0x2e0);
static_assert(offsetof(LocationalLightRig, mIntensity) == 0x308);
static_assert(offsetof(LocationalLightRig, mInnerRadius) == 0x328);
static_assert(offsetof(LocationalLightRig, mEnableEffectMoth) == 0x348);
static_assert(offsetof(LocationalLightRig, mFlickeringIntensityRate) == 0x368);
static_assert(offsetof(LocationalLightRig, mFlickeringSpeed) == 0x388);

}  // namespace ksys::gfx
