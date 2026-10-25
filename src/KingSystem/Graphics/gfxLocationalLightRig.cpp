#include "Game/gameGraphics.h"
#include "KingSystem/Graphics/gfxLocationalLightRig.h"
#include <gsys/gsysModel.h>
#include <gsys/gsysG3dResMaterialEx.h>
#include <utility/aglDynamicTextureAllocator.h>
#include <utility/aglPrimitiveTexture.h>
#include "Game/gameUnkRttiPlaceholders.h"
#include <prim/seadScopedLock.h>
#include "KingSystem/Graphics/gfxUkingModelRenderOptionsMgr.h"

namespace ksys::gfx {

// 0x710260ad68: only written by the class registration below.
KSYS_VISIBILITY_HIDDEN s32 sUnk_710260AD68;

u16* sTypeId;

s32 LocationalLightRig::getTypeID() const {
    return s16(*sTypeId);
}

agl::env::EnvObj* LocationalLightRig::create(sead::Heap* heap) {
    return new (heap, 8) LocationalLightRig;
}

// 0x7100f18540: registers the rig type with the environment-object manager.
void sub_7100F18540() {
    sUnk_710260AD68 = 0;
    sTypeId = agl::env::EnvObj::registClass("LocationalLightRig", "LocationalLightRig",
                                            LocationalLightRig::create, 0, sizeof(LocationalLightRig));
}

// Parameter names, labels and meta strings are the originals at 0x7101e1c976 .. 0x7101e1ca8b.
// NON_MATCHING: the parameter string temporaries are scheduled differently.
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

void LocationalLightMgr::ObjectLight::Light::drawDebug(agl::DrawContext* context,
                                                       const sead::Matrix34f& view,
                                                       const sead::Matrix44f& projection,
                                                       int view_index) const {
    if (!getVisibilityMaskMaybe().isOnBit(view_index))
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

void LocationalLightRig::initialize(int index, sead::Heap* heap) {
    gsys::ModelRig::initialize(index, heap);
}

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

void LocationalLightRig::listenPropertyEventEnvObj(const sead::hostio::PropertyEvent* event) {
    gsys::ModelRig::listenPropertyEventEnvObj(event);
}

}  // namespace ksys::gfx

// NON_MATCHING: the entry loop's pointer increment and counter decrement are scheduled in the
// opposite order (one instruction; same size).
// NON_MATCHING: the trailing member stores are emitted in a different order (the constructor and
// its values are complete; only the independent store order differs, same size).
// 0x7100f185a4: constructs the cameras, projection, render targets and buffers of the map renderer.
Unk_7100f185a4::Unk_7100f185a4() {
    _fc8 = nullptr;
    _fc0 = nullptr;
    _fe0 = 0;
    mIdBuffers[0].mSize = 0;
    mIdBuffers[0].mIds = nullptr;
    mIdBuffers[1].mSize = 0;
    mIdBuffers[1].mIds = nullptr;
    _1008 = 0;
    _1009 = 0;
}

// 0x7100f18704: releases the unit groups the renderer owns (bit 0 of +0x21 set) and the group table.
Unk_7100f185a4::~Unk_7100f185a4() {
    for (u64 i = 0; i != 0x40; ++i) {
        const u32 group_count = mUnitGroups.size();
        UnitGroup* group = *(group_count > i ? mUnitGroups.getBufferPtr() + i
                                             : mUnitGroups.getBufferPtr());
        if (!group)
            continue;
        if (!(group->_21 & 1))
            continue;

        UnitEntry* entry = group->mEntries.getBufferPtr();
        const u32 count = group->mEntries.size();
        for (u64 j = 0; j != count; ++j)
            entry[j].mRefs.freeBuffer();
        group->mEntries.freeBuffer();

        const s32 index = group->_20;
        delete group;
        mUnitGroups[index] = nullptr;
    }
    mUnitGroups.freeBuffer();
}

// NON_MATCHING: the entry loop's pointer increment and counter decrement are scheduled in the
// opposite order (one instruction; same size).
// 0x7100f19928: removes the unit group the model render data registered; a group owned by the
// renderer (bit 0 of +0x21 set) only has its entries cleared.
void Unk_7100f185a4::sub_7100F19928(ksys::gfx::ModelRenderDataMaybe* data) {
    ksys::gfx::ModelRenderDataMaybe::Block* block = data->_88;
    UnitGroup* group = block->mGroup;
    if (!group)
        return;

    if (group->_21 & 1) {
        UnitEntry* entry = group->mEntries.getBufferPtr();
        const u32 count = group->mEntries.size();
        for (u64 i = 0; i != count; ++i)
            entry[i].mColorSetMaybe = 0;
    } else {
        mUnitGroups[group->_20] = nullptr;

        UnitEntry* entry = group->mEntries.getBufferPtr();
        const u32 count = group->mEntries.size();
        for (u64 i = 0; i != count; ++i)
            entry[i].mRefs.freeBuffer();
        group->mEntries.freeBuffer();
        delete group;
    }

    block->mGroup = nullptr;
}

// NON_MATCHING: the flags loop's peeled first block uses the +0x60 address as its induction (so the
// increment folds into the last store) instead of the original's +0x5f (same stores).
// 0x7100f19c4c: moves every unit's flags byte to +0x60 and clears it, for every present group with
// bit 0 of +0x21 clear.
void Unk_7100f185a4::sub_7100F19C4C() {
    for (u64 i = 0; i != 0x40; ++i) {
        const u32 group_count = mUnitGroups.size();
        UnitGroup* group = *(group_count > i ? mUnitGroups.getBufferPtr() + i
                                             : mUnitGroups.getBufferPtr());
        if (!group)
            continue;
        if (group->_21 & 1)
            continue;

        const u32 count = group->mEntries.size();
        if (count == 0)
            continue;

        UnitEntry* entry = group->mEntries.getBufferPtr();
        for (u64 j = 0; j != count; ++j) {
            UnitEntry* e = entry + j;
            const u8 flags = e->mFlags;
            e->mFlags = 0;
            e->_60 = flags;
        }
    }
}

// 0x7100f19f90: sets the colour and bit 0 of the flags of map unit `id`.
void Unk_7100f185a4::setMapUnitColorMaybe(s32 id, const sead::Color4f& color) {
    if (id == -1)
        return;

    Unk_7100f185a4::UnitGroup* group = mUnitGroups[id >> 16];
    if (!group)
        return;
    const s32 index = s16(id);
    const s32 count = group->mEntries.size();
    UnitEntry* entry = group->mEntries.getBufferPtr();
    if (u32(count) > u32(index))
        entry += index;
    if (!entry)
        return;

    if (entry->mColorSetMaybe && entry->mColor == color)
        return;
    entry->mColor = color;
    entry->mFlags |= 1;
}

// 0x7100f1a30c: stores the two-float value and bit 3 of the flags of map unit `id`.
void Unk_7100f185a4::setMapUnitValueMaybe(s32 id, const sead::Vector2f& value) {
    if (id == -1)
        return;

    Unk_7100f185a4::UnitGroup* group = mUnitGroups[id >> 16];
    if (!group)
        return;
    const s32 index = s16(id);
    const s32 count = group->mEntries.size();
    UnitEntry* entry = group->mEntries.getBufferPtr();
    if (u32(count) > u32(index))
        entry += index;
    if (!entry)
        return;

    if (!entry->mColorSetMaybe || (entry->mType == 3 && entry->_54 != value)) {
        entry->_54 = value;
        entry->mFlags |= 8;
    }
}

// 0x7100f1a1b4: stores the three vectors of map unit `id` when they or the compared flag bit differ.
void Unk_7100f185a4::setMapUnitTransformMaybe(s32 id, const sead::Vector3f& value30,
                                              const sead::Vector3f& value48,
                                              const sead::Vector3f& value3c) {
    if (id == -1)
        return;

    Unk_7100f185a4::UnitGroup* group = mUnitGroups[id >> 16];
    if (!group)
        return;
    const s32 index = s16(id);
    const s32 count = group->mEntries.size();
    UnitEntry* entry = group->mEntries.getBufferPtr();
    if (u32(count) > u32(index))
        entry += index;
    if (!entry)
        return;

    if (entry->mColorSetMaybe) {
        if (entry->_30 == value30 && entry->_3c == value3c && entry->_48 == value48 &&
            ((entry->_60 >> 4) & 1) == ((entry->mFlags & 0x10) >> 4))
            return;
    }
    entry->_30 = value30;
    entry->_3c = value3c;
    entry->_48 = value48;
    entry->mFlags |= 4;
}

// NON_MATCHING: the reference-record loop's counter decrement is scheduled one slot before the
// pointer increment (otherwise identical).
// 0x7100f1a034: sets the visibility flag of map unit `id`; a type 3 unit whose reference records
// contain 0xfe also updates the visibility flag of every unit of the group.
void Unk_7100f185a4::setMapUnitVisibleMaybe(s32 id, bool visible) {
    if (id == -1)
        return;

    Unk_7100f185a4::UnitGroup* group = mUnitGroups[id >> 16];
    if (!group)
        return;
    const s32 index = s16(id);
    const s32 count = group->mEntries.size();
    UnitEntry* entry = group->mEntries.getBufferPtr();
    if (u32(count) > u32(index))
        entry += index;
    if (!entry)
        return;

    entry->mFlags = visible ? (entry->mFlags | 0x12) : ((entry->mFlags & ~0x12) | 0x02);

    if (entry->mType != 3)
        return;
    if (entry->mRefs.size() == 0)
        return;

    bool found = false;
    const UnitEntry::RefRecord* ref = entry->mRefs.getBufferPtr();
    s32 n = entry->mRefs.size();
    while (n != 0) {
        if (ref->_2 == 0xfe) {
            found = true;
            break;
        }
        ++ref;
        --n;
    }
    if (!found)
        return;

    group = mUnitGroups[id >> 16];
    const s32 group_count = group->mEntries.size();
    if (group_count == 0)
        return;
    UnitEntry* entries = group->mEntries.getBufferPtr();
    if (visible) {
        for (s32 i = 0; i != group_count; ++i)
            entries[i].mFlags |= 0x20;
    } else {
        for (s32 i = 0; i != group_count; ++i)
            entries[i].mFlags &= 0xdf;
    }
}

// 0x7100f1ab60: stores the two screen coordinates the map screen computes (each truncated to 16 bits).
void Unk_7100f185a4::setPosXY(s32 x, s32 y) {
    _50 = static_cast<u16>(x);
    _54 = static_cast<u16>(y);
}

// 0x7100f1ab70: sets camera A's direct matrix from `camera`, refreshes its view matrix and stores
// the projection's field of view; a look-at camera also contributes its at vector.
void Unk_7100f185a4::setCameraMaybe(const sead::Camera& camera, f32 fov) {
    mCameraA.setDirectMatrix(camera.getMatrix());
    mCameraA.updateViewMatrix();
    _1e8 = fov;
    if (sead::IsDerivedFrom<sead::LookAtCamera>(&camera))
        _1f8 = static_cast<const sead::LookAtCamera*>(&camera)->getAt();
}

// 0x7100f1ac58: clears the render queue and the frame flag, flips the id buffer and clears the new
// buffer's ids.
void Unk_7100f185a4::sub_7100F1AC58() {
    _828 = 0;
    mRenderQueue.clear();
    _1008 = 1 - _1008;

    IdBuffer& buffer = mIdBuffers[_1008];
    const s32 size = buffer.mSize;
    for (s32 i = 0; i < size; ++i)
        buffer.mIds[i] = 0;
}

// 0x7100f1f1f8: primary table slot 0x90. Sets the reverse polygon offset flag of the render state
// from the material's shader option.
void Unk_7100f185a4::setMaterialReversePolygonOffsetMaybe(
    const gsys::IModelResourceCallback::MaterialArg& arg) {
    if (arg.material->isShaderOptionBool("uking_reverse_polygon_offset")) {
        arg.render_info->_8 |= 0x40;
        arg.render_info->_a |= 0x4;
    } else {
        arg.render_info->_8 = arg.render_info->_8 & 0xbf;
    }
}

// 0x7100f1f278: slot 3 of the object's IModelResourceCallback table; same body.
void Unk_7100f185a4::m3(const gsys::IModelResourceCallback::MaterialArg& arg) {
    if (arg.material->isShaderOptionBool("uking_reverse_polygon_offset")) {
        arg.render_info->_8 |= 0x40;
        arg.render_info->_a |= 0x4;
    } else {
        arg.render_info->_8 = arg.render_info->_8 & 0xbf;
    }
}

// 0x7100f1b6e0: frees the dynamic map texture and puts the Black2D sampler (mSamplers[2], +0x38)
// back on mSampler0.
void Unk_7100f185a4::freeDynamicTextureMaybe() {
    if (_8c0) {
        agl::utl::DynamicTextureAllocator::instance()->free(_8c0);
        _8c0 = nullptr;
        mSampler0.applyTextureData(
            agl::utl::PrimitiveTexture::instance()->getBlack2DSampler()->getTextureData());
    }
}

// 0x7100f1f170: slot 11 of the object's IModelMgrCallback table. The original shares the teardown
// with ksys::gfx::UkingModelRenderOptionsMgr::destroyModelRenderData, so the body is the same.
void Unk_7100f185a4::sub_7100F1F170(ksys::gfx::ModelRenderDataMaybe* data) {
    if (auto* map = Graphics::instance()->getMapRendererMaybe())
        map->sub_7100F19928(data);
    if (auto* far = Graphics::instance()->getFarModelRendererMaybe())
        far->sub_7100EFDCE8(data);
    if (auto* grudge = Graphics::instance()->getGrudgeRendererMaybe())
        grudge->sub_710128F148(data);
    if (auto* block = data->_88) {
        if (block->_30)
            delete[] block->_30;
        delete block;
        data->_88 = nullptr;
    }
}
