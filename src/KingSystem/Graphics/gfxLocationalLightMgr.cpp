#include "KingSystem/Graphics/gfxLocationalLightMgr.h"
#include "KingSystem/Graphics/gfxLocationalLightRig.h"
#include <prim/seadScopedLock.h>
#include "Game/gameUnkRttiPlaceholders.h"
#include "KingSystem/Map/mapObject.h"

namespace ksys::gfx {

// Shared light threshold read through the manager getter 0x7100f143fc.
static f32 sUnk_71024F3CC8 = 0.007f;
// 0x71024f3cc4 (.data, 0.3f): the lower light threshold. External linkage keeps the load: the
// original reads it as mutable data, it is not folded to the initial value.
KSYS_VISIBILITY_HIDDEN f32 sUnk_71024F3CC4 = 0.3f;

f32 LocationalLightMgr::sub_7100F143E4() const {
    return sUnk_71024F3CC4 < 0.001f ? 0.001f : sUnk_71024F3CC4;
}

f32 LocationalLightMgr::sub_7100F143FC() const {
    return sUnk_71024F3CC8;
}

// 0x7100f0b5b8 (placeholder name): stores `obj` at +0x58 and gives the allocation argument a
// maximum of 0x80 for the locational light rig type.
void LocationalLightMgr::sub_7100F0B5B8(void* obj, agl::env::EnvObjBuffer::AllocateArg* arg) {
    _58 = obj;
    arg->setContainMax(s16(*sTypeId), 0x80);
}

void LocationalLightMgr::RigLightPool::init(s32 capacity, sead::Heap* heap) {
    mLights.tryAllocBuffer(capacity, heap, 8);
    mFreeLights.allocBuffer(capacity, heap, 8);
    mActiveLights.allocBuffer(capacity, heap, 8);
    // Native iterates the requested count, including the Buffer bounds fallback
    // if the nothrow record allocation failed. Do not turn this into range-for.
    for (s32 i = 0; i < capacity; ++i)
        mFreeLights.pushBack(&mLights[i]);
}

LocationalLightMgr::ObjectLight::Light* LocationalLightMgr::RigLightPool::allocate() {
    auto lock = sead::makeScopedLock(mCS);
    auto* light = mFreeLights.popBack();
    if (light)
        mActiveLights.pushBack(light);
    return light;
}

// NON_MATCHING: the original walks the active array with a pointer loop; ours compares the
// pointer range and index separately. Same result.
bool LocationalLightMgr::RigLightPool::release(ObjectLight::Light* light) {
    auto lock = sead::makeScopedLock(mCS);
    s32 index = 0;
    for (auto* it = mActiveLights.dataBegin(); it != mActiveLights.dataEnd(); ++it, ++index) {
        if (*it == light) {
            mActiveLights.erase(index);
            mFreeLights.pushBack(light);
            return true;
        }
    }
    return false;
}

// NON_MATCHING: the original sets the bit with `(_60 & 0x20000000) + 0x20000000 | _60`, which also
// carries into bit 30 when bit 29 was already set.
void LocationalLightMgr::sub_7100F1334C() {
    _60 |= 0x20000000;
}

bool LocationalLightMgr::RenderLightPool::release(Unk_7102519378* light) {
    auto lock = sead::makeScopedLock(mCS);
    s32 index = 0;
    for (auto* it = mActiveLights.dataBegin(); it != mActiveLights.dataEnd(); ++it, ++index) {
        if (*it == light) {
            mActiveLights.erase(index);
            mFreeLights.pushBack(light);
            return true;
        }
    }
    return false;
}

// 0x7100f1356c / 0x7100f135f8: pops a record from the free list, pushes it on the active list
// and runs its init hook under the pool's lock.
Unk_7102519378* LocationalLightMgr::RecordLightPool::allocate() {
    auto lock = sead::makeScopedLock(mCS);
    auto* light = mFreeLights.popBack();
    if (light) {
        mActiveLights.pushBack(light);
        light->init();
    }
    return light;
}

// The nine record pools share this release; the original inlines it into each arm of
// sub_7100F13A58.
bool LocationalLightMgr::RecordLightPool::release(Unk_7102519378* light) {
    auto lock = sead::makeScopedLock(mCS);
    light->reset();
    s32 index = 0;
    for (auto* it = mActiveLights.dataBegin(); it != mActiveLights.dataEnd(); ++it, ++index) {
        if (*it == light) {
            mActiveLights.erase(index);
            mFreeLights.pushBack(light);
            return true;
        }
    }
    return false;
}

Unk_7102519378* LocationalLightMgr::sub_7100F1356C() {
    return mRecordPools[0].allocate();
}

Unk_7102519378* LocationalLightMgr::sub_7100F135F8() {
    return mRecordPools[1].allocate();
}

Unk_7102519378* LocationalLightMgr::sub_7100F13684() {
    return mRecordPools[2].allocate();
}

Unk_7102519378* LocationalLightMgr::sub_7100F13710() {
    return mRecordPools[3].allocate();
}

Unk_7102519378* LocationalLightMgr::sub_7100F1379C() {
    return mRecordPools[4].allocate();
}

Unk_7102519378* LocationalLightMgr::sub_7100F13828() {
    return mRecordPools[5].allocate();
}

Unk_7102519378* LocationalLightMgr::sub_7100F138B4() {
    return mRecordPools[6].allocate();
}

Unk_7102519378* LocationalLightMgr::sub_7100F13940() {
    return mRecordPools[7].allocate();
}

Unk_7102519378* LocationalLightMgr::sub_7100F139CC() {
    return mRecordPools[8].allocate();
}

// 0x7100f13a58: returns a record to the pool that owns its type. The record's type tag (vtable
// slot 5) picks the pool; the RTTI check verifies the tag before the record is touched.
// NON_MATCHING: our loop latch in the inlined release() orders `sub x9 (pointer); add x1 (index)`
// where the target has `add` then `sub` in all nine arms; everything else matches instruction for
// instruction.
bool LocationalLightMgr::sub_7100F13A58(Unk_7102519378* record) {
    if (!record)
        return false;

    switch (record->m5()) {
    case 0:
        if (!sead::IsDerivedFrom<Unk_71025193e8>(record))
            return false;
        return mRecordPools[0].release(record);
    case 1:
        if (!sead::IsDerivedFrom<Unk_7102519460>(record))
            return false;
        return mRecordPools[1].release(record);
    case 2:
        if (!sead::IsDerivedFrom<Unk_71025194d0>(record))
            return false;
        return mRecordPools[2].release(record);
    case 3:
        if (!sead::IsDerivedFrom<Unk_7102519540>(record))
            return false;
        return mRecordPools[3].release(record);
    case 4:
        if (!sead::IsDerivedFrom<Unk_71025195b0>(record))
            return false;
        return mRecordPools[4].release(record);
    case 5:
        if (!sead::IsDerivedFrom<Unk_7102519620>(record))
            return false;
        return mRecordPools[5].release(record);
    case 6:
        if (!sead::IsDerivedFrom<Unk_7102519690>(record))
            return false;
        return mRecordPools[6].release(record);
    case 7:
        if (!sead::IsDerivedFrom<Unk_7102519708>(record))
            return false;
        return mRecordPools[7].release(record);
    case 8:
        if (!sead::IsDerivedFrom<Unk_7102519778>(record))
            return false;
        return mRecordPools[8].release(record);
    }
    return false;
}

bool LocationalLightMgr::sub_7100F13368(ObjectLight* light) {
    static_assert(offsetof(LocationalLightMgr, mRigLightPool) == 0x458);
    static_assert(offsetof(LocationalLightMgr, mObjectLightCS) == 0x4c8);
    if (light)
        light->detachObject();
    auto lock = sead::makeScopedLock(mObjectLightCS);
    s32 index = 0;
    for (auto& active : mActiveObjectLights) {
        if (&active == light) {
            mActiveObjectLights.erase(index);
            mFreeObjectLights.pushBack(light);
            return true;
        }
        ++index;
    }
    return false;
}

void LocationalLightMgr::sub_7100F13420(gsys::ModelUnit* unit) {
    auto lock = sead::makeScopedLock(mCS);
    if (!unit)
        return;
    auto light_lock = sead::makeScopedLock(mObjectLightCS);
    auto* placement_mgr = map::PlacementMgr::instance();
    auto end = mActiveObjectLights.end();
    for (auto it = mActiveObjectLights.begin(); it != end;) {
        auto* object = it->mObject;
        if (placement_mgr->mPlacementActors->mActorData[object->getActorDataIdx()]._10 == unit) {
            sub_7100F0EC30(object);
            it = mActiveObjectLights.begin();
            end = mActiveObjectLights.end();
        } else {
            ++it;
        }
    }
}

void LocationalLightMgr::sub_7100F134E8(map::Object* first, map::Object* last) {
    auto lock = sead::makeScopedLock(mCS);
    auto end = mActiveObjectLights.end();
    for (auto it = mActiveObjectLights.begin(); it != end;) {
        auto* object = it->mObject;
        if (object > first && object < last) {
            sub_7100F0EC30(object);
            it = mActiveObjectLights.begin();
            end = mActiveObjectLights.end();
        } else {
            ++it;
        }
    }
}

}  // namespace ksys::gfx
