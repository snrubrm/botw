#include "Game/gameGraphics.h"
#include "KingSystem/Graphics/gfxLocationalLightRig.h"
#include <gsys/gsysModel.h>
#include "Game/gameUnkRttiPlaceholders.h"
#include <prim/seadScopedLock.h>

namespace ksys::gfx {

// 0x710260ad70: the rig type id the factory registration 0x7100f18540 stores.
s16* sTypeId;

s32 LocationalLightRig::getTypeID() const {
    return *sTypeId;
}

LocationalLightRig* LocationalLightRig::create(sead::Heap* heap) {
    return new (heap, 8) LocationalLightRig;
}

// Parameter names, labels and meta strings are the originals at 0x7101e1c976 .. 0x7101e1ca8b.
// NON_MATCHING: the original's LocationalLightRig vtable has one more primary slot (its
// secondary address point is at +0x108, ours at +0x100), and the parameter string
// temporaries are scheduled differently.
LocationalLightRig::LocationalLightRig()
    : mLightType(0, "LightType", "ライト種類", "", this),
      mColor(sead::Color4f(1, 0, 0, 1), "Color", "色（輝度で正規化されます）", "", this),
      mIntensity(10.0f, "Intensity", "強度（明るさ）", "Min=0", this),
      mInnerRadius(0.3f, "InnerRadius", "光源半径（内側ライトの半径。スペキュラサイズにも影響。）",
                   "Min=0", this),
      mEnableEffectMoth(false, "EnableEffectMoth", "蛾エフェクト", "", this),
      mFlickeringIntensityRate(0.1f, "FlickeringIntensityRate", "揺れ強度率", "Min=0", this),
      mFlickeringSpeed(1.0f, "FlickeringSpeed", "揺れ速度", "Min=0", this) {
    mLights.initOffset(0x18);
}

LocationalLightMgr::ObjectLight::Light::Light() = default;

// NON_MATCHING: the bone-index store is scheduled before the flag / rig stores (same instructions,
// different order).
LocationalLightMgr::ObjectLight::Light::~Light() {
    if (mRenderLight) {
        mRig->mLightMgr->sub_7100F13A58(mRenderLight);
        mRenderLight = nullptr;
    }
    mFlags = 0;
    mRig = nullptr;
    mObjectLight = nullptr;
    mBoneIndex = -1;
    mEndBoneIndex = -1;
    mVisibilityMask = 0xffff;
}

// NON_MATCHING: clang folds the redundant `& 0xffff` after the mask test (one instruction).
void LocationalLightMgr::ObjectLight::Light::drawDebug(agl::DrawContext* context,
                                                       const sead::Matrix34f& view,
                                                       const sead::Matrix44f& projection,
                                                       int view_index) const {
    const u16 mask = mVisibilityMask & (1 << view_index);
    if (!mask)
        return;
    if (!mRenderLight)
        return;
    mRenderLight->drawDebug(context, view, projection, view_index);
}

// NON_MATCHING: the render-light pointer stays in a register instead of being reloaded for the
// release call and the record store.
void LocationalLightMgr::ObjectLight::Light::update() {
    if ((mFlags & 1) && mVisibilityMask != 0) {
        auto* mgr = mRig->mLightMgr;
        if (mRenderLight && mLightType != mRig->mLightType.ref()) {
            mgr->sub_7100F13A58(mRenderLight);
            mRenderLight = nullptr;
        }
        mLightType = mRig->mLightType.ref();
        mRenderLight = mLightType == 1 ? mgr->sub_7100F135F8()
                      : mLightType == 0 ? mgr->sub_7100F1356C()
                                        : nullptr;
        if (!mRenderLight)
            return;
        mRenderLight->_58 = mVisibilityMask;
        mRig->sub_7100F177F4(mRenderLight, this, nullptr);
    } else if (mRenderLight) {
        mRig->mLightMgr->sub_7100F13A58(mRenderLight);
        mRenderLight = nullptr;
    }
}

// 0x7100f18278: the per-frame update with a model unit; the unit's bone visibility and
// visibility mask select the light, then the render light is refreshed exactly as in update().
// NON_MATCHING: the render-light pointer and the rig type stay in different registers than the
// original's (the light store and the null test use the call result instead of a moved copy).
void LocationalLightMgr::ObjectLight::Light::update(gsys::ModelUnit* unit, u16 visibility_mask,
                                                   f32 delta_time) {
    if (delta_time > 0.0f) {
        if (unit->isBoneVisible(mBoneIndex) && mRig->isEnable())
            mVisibilityMask = unit->getVisibilityMask() & visibility_mask;
        else
            mVisibilityMask = 0;
    }
    if ((mFlags & 1) && mVisibilityMask != 0) {
        auto* mgr = mRig->mLightMgr;
        if (mRenderLight && mLightType != mRig->mLightType.ref()) {
            mgr->sub_7100F13A58(mRenderLight);
            mRenderLight = nullptr;
        }
        mLightType = mRig->mLightType.ref();
        Unk_7102519378* light;
        if (mLightType == 1)
            light = mgr->sub_7100F135F8();
        else if (mLightType == 0)
            light = mgr->sub_7100F1356C();
        else
            return;
        mRenderLight = light;
        if (!mRenderLight)
            return;
        mRenderLight->_58 = mVisibilityMask;
        mRig->sub_7100F177F4(mRenderLight, this, unit);
    } else if (mRenderLight) {
        mRig->mLightMgr->sub_7100F13A58(mRenderLight);
        mRenderLight = nullptr;
    }
}

void LocationalLightMgr::ObjectLight::updateLights() {
    auto lock = sead::makeScopedLock(mCS);
    for (auto& light : mLights)
        light.update();
}

void LocationalLightRig::drawDebug(agl::DrawContext* context, const sead::Matrix34f& view,
                                   const sead::Matrix44f& projection, int view_index) const {
    auto lock = sead::makeScopedLock(mCS);
    for (const auto& light : mLights) {
        if ((light.mFlags & 1) && light.mVisibilityMask != 0)
            light.drawDebug(context, view, projection, view_index);
    }
}

void LocationalLightRig::m11(int index, sead::Heap* heap) {
    gsys::ModelRig::m11(index, heap);
}

// NON_MATCHING: the secondary-base vtable is one slot earlier than the original.
LocationalLightRig::~LocationalLightRig() {}

// NON_MATCHING: adjacent halfword stores merge and initialization is reordered.
void LocationalLightRig::m24(gsys::Model* model, const gsys::BoneAccessKey& key,
                             const sead::SafeString& name) {
    auto lock = sead::makeScopedLock(mCS);
    if (name.endsWith("_End"))
        return;
    auto* light = mLightMgr->mRigLightPool.allocate();
    if (!light)
        return;
    light->mBoneIndex = key.bone_index;
    light->mFlags |= 1;
    light->mRig = this;
    light->mObjectLight = nullptr;
    light->mEndBoneIndex = -1;
    light->mVisibilityMask = 0;
    model->pushBack(key.model_unit_index, light);
    mLights.pushBack(light);
}

void LocationalLightRig::m25(gsys::Model*, const gsys::MaterialAccessKey&,
                             const sead::SafeString&) {}

// NON_MATCHING: OffsetList iterator offset handling and field stores differ.
void LocationalLightRig::m26(gsys::Model* model, int unit_index) {
    auto lock = sead::makeScopedLock(mCS);
    auto it = mLights.begin();
    while (it != mLights.end()) {
        auto* light = &*it;
        if (!model->hasRigObj(unit_index, light)) {
            ++it;
            continue;
        }
        mLights.erase(light);
        model->erase(unit_index, light);
        if (light->mRenderLight) {
            light->mRig->mLightMgr->sub_7100F13A58(light->mRenderLight);
            light->mRenderLight = nullptr;
        }
        light->mFlags = 0;
        light->mRig = nullptr;
        light->mObjectLight = nullptr;
        light->mBoneIndex = -1;
        light->mEndBoneIndex = -1;
        light->mVisibilityMask = 0xffff;
        mLightMgr->mRigLightPool.release(light);
        it = mLights.begin();
    }
}

// NON_MATCHING: formatting temporaries occupy separate stack slots.
void LocationalLightRig::genMessage(sead::hostio::Context* context) {
    sub_7100C83D44(context);
    sead::FormatFixedSafeString<256>("吊れたノード:%d", mLights.size());
    sead::FormatFixedSafeString<256>("GroupHeader=%s", m16().cstr());
    // Discarded calls are present at F17EBC/F17ED4 in the original.
    mLightType.getLabel().cstr();
    if (mLightType.ref() == 1) {
        sead::FormatFixedSafeString<256>(
            "“%s_○○”　～　“%s_○○_End”　を繋いだ直線状のライトを生成します。",
            mBonePrefix.ref().cstr(), mBonePrefix.ref().cstr());
    }
    mColor.genMessageParameter(context, mColor.getMeta());
    mIntensity.genMessageParameter(context, mIntensity.getMeta());
    mInnerRadius.genMessageParameter(context, mInnerRadius.getMeta());
    mFlickeringIntensityRate.genMessageParameter(context, mFlickeringIntensityRate.getMeta());
    mFlickeringSpeed.genMessageParameter(context, mFlickeringSpeed.getMeta());
    mEnableEffectMoth.genMessageParameter(context, mEnableEffectMoth.getMeta());
}

}  // namespace ksys::gfx

// 0x7100f1ab60: stores the two screen coordinates the map screen computes (each truncated to 16 bits).
void Unk_7100f185a4::setPosXY(s32 x, s32 y) {
    _50 = static_cast<u16>(x);
    _54 = static_cast<u16>(y);
}
