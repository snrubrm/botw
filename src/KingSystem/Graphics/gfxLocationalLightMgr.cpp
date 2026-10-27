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

// Requests the shutdown stage: 0x20000000 first, 0x40000000 when it was already set.
void LocationalLightMgr::sub_7100F1334C() {
    if (_60 & 0x20000000)
        _60 |= 0x40000000;
    else
        _60 |= 0x20000000;
}

// 0x7100f10bec (empty in the original): the per-pass hook Graphics::drawModelSceneBG calls.
void LocationalLightMgr::sub_7100F10BEC(agl::DrawContext* draw_context) {}

// 0x7100f0cd60: allocates the render-light pool's records and gives every record to the free list.
void LocationalLightMgr::RenderLightPool::init(s32 capacity, sead::Heap* heap) {
    mLights.tryAllocBuffer(capacity, heap, 8);
    mFreeLights.allocBuffer(capacity, heap, 8);
    mActiveLights.allocBuffer(capacity, heap, 8);
    for (s32 i = 0; i < capacity; ++i)
        mFreeLights.pushBack(&mLights[i]);
}

bool LocationalLightMgr::RenderLightPool::release(Unk_71025197e8* light) {
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

// NON_MATCHING: the original's search loop keeps a byte trip count (`sub x9, x9, #8; cbnz`)
// instead of our `cmp w8, w23; b.ne`, so it does not keep the free list's address live across the
// loop and its frame is 0x10 smaller (same check, same erase and push order). Tried s64 / u64
// indices, a local count, and both loop bound forms; none gives the byte countdown naturally.
// 0x7100f142b0: takes the free render-light record at `pos` (erasing it from the free list),
// otherwise the last free record, pushes it onto the active list and returns it.
Unk_71025197e8* LocationalLightMgr::sub_7100F142B0(const sead::Vector3f& pos) {
    auto lock = sead::makeScopedLock(mRenderLightPool.mCS);
    Unk_71025197e8* light = nullptr;
    const s32 count = mRenderLightPool.mFreeLights.size();
    s32 index = 0;
    for (; index != count; ++index) {
        if (mRenderLightPool.mFreeLights.unsafeAt(index)->mPosition == pos)
            break;
    }
    if (index != count) {
        auto lock = sead::makeScopedLock(mRenderLightPool.mCS);
        light = mRenderLightPool.mFreeLights.at(index);
        mRenderLightPool.mFreeLights.erase(index);
        if (light)
            mRenderLightPool.mActiveLights.pushBack(light);
    }
    if (!light) {
        auto lock = sead::makeScopedLock(mRenderLightPool.mCS);
        light = mRenderLightPool.mFreeLights.popBack();
        if (light)
            mRenderLightPool.mActiveLights.pushBack(light);
    }
    return light;
}

// 0x7100f0c008 / 0x7100f0c13c / ...: the record pools' shared init.
template <typename T>
void LocationalLightMgr::LightPool<T>::init(s32 capacity, sead::Heap* heap) {
    mLights.tryAllocBuffer(capacity, heap, 8);
    mFreeLights.allocBuffer(capacity, heap, 8);
    mActiveLights.allocBuffer(capacity, heap, 8);
    for (s32 i = 0; i < capacity; ++i)
        mFreeLights.pushBack(&mLights[i]);
}

// 0x7100f1356c / 0x7100f135f8: pops a record from the free list, pushes it on the active list
// and runs its init hook under the pool's lock.
template <typename T>
T* LocationalLightMgr::LightPool<T>::allocate() {
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
template <typename T>
bool LocationalLightMgr::LightPool<T>::release(T* light) {
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

template class LocationalLightMgr::LightPool<Unk_71025193e8>;
template class LocationalLightMgr::LightPool<Unk_7102519460>;
template class LocationalLightMgr::LightPool<Unk_71025194d0>;
template class LocationalLightMgr::LightPool<Unk_7102519540>;
template class LocationalLightMgr::LightPool<Unk_71025195b0>;
template class LocationalLightMgr::LightPool<Unk_7102519620>;
template class LocationalLightMgr::LightPool<Unk_7102519690>;
template class LocationalLightMgr::LightPool<Unk_7102519708>;
template class LocationalLightMgr::LightPool<Unk_7102519778>;
// The object-light pool shares only init; its allocate / release are inlined at their call sites.
template void LocationalLightMgr::LightPool<LocationalLightMgr::ObjectLight>::init(s32,
                                                                                 sead::Heap*);

Unk_7102519378* LocationalLightMgr::sub_7100F1356C() {
    return mRecordPool0.allocate();
}

Unk_7102519378* LocationalLightMgr::sub_7100F135F8() {
    return mRecordPool1.allocate();
}

Unk_7102519378* LocationalLightMgr::sub_7100F13684() {
    return mRecordPool2.allocate();
}

Unk_7102519378* LocationalLightMgr::sub_7100F13710() {
    return mRecordPool3.allocate();
}

Unk_7102519378* LocationalLightMgr::sub_7100F1379C() {
    return mRecordPool4.allocate();
}

Unk_7102519378* LocationalLightMgr::sub_7100F13828() {
    return mRecordPool5.allocate();
}

Unk_7102519378* LocationalLightMgr::sub_7100F138B4() {
    return mRecordPool6.allocate();
}

Unk_7102519378* LocationalLightMgr::sub_7100F13940() {
    return mRecordPool7.allocate();
}

Unk_7102519378* LocationalLightMgr::sub_7100F139CC() {
    return mRecordPool8.allocate();
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
        return mRecordPool0.release(static_cast<Unk_71025193e8*>(record));
    case 1:
        if (!sead::IsDerivedFrom<Unk_7102519460>(record))
            return false;
        return mRecordPool1.release(static_cast<Unk_7102519460*>(record));
    case 2:
        if (!sead::IsDerivedFrom<Unk_71025194d0>(record))
            return false;
        return mRecordPool2.release(static_cast<Unk_71025194d0*>(record));
    case 3:
        if (!sead::IsDerivedFrom<Unk_7102519540>(record))
            return false;
        return mRecordPool3.release(static_cast<Unk_7102519540*>(record));
    case 4:
        if (!sead::IsDerivedFrom<Unk_71025195b0>(record))
            return false;
        return mRecordPool4.release(static_cast<Unk_71025195b0*>(record));
    case 5:
        if (!sead::IsDerivedFrom<Unk_7102519620>(record))
            return false;
        return mRecordPool5.release(static_cast<Unk_7102519620*>(record));
    case 6:
        if (!sead::IsDerivedFrom<Unk_7102519690>(record))
            return false;
        return mRecordPool6.release(static_cast<Unk_7102519690*>(record));
    case 7:
        if (!sead::IsDerivedFrom<Unk_7102519708>(record))
            return false;
        return mRecordPool7.release(static_cast<Unk_7102519708*>(record));
    case 8:
        if (!sead::IsDerivedFrom<Unk_7102519778>(record))
            return false;
        return mRecordPool8.release(static_cast<Unk_7102519778*>(record));
    }
    return false;
}

bool LocationalLightMgr::sub_7100F13368(ObjectLight* light) {
    static_assert(offsetof(LocationalLightMgr, mRigLightPool) == 0x458);
    static_assert(offsetof(LocationalLightMgr, mObjectPool) == 0x4c8);
    if (light)
        light->detachObject();
    auto lock = sead::makeScopedLock(mObjectPool.mCS);
    s32 index = 0;
    for (auto& active : mObjectPool.mActiveLights) {
        if (&active == light) {
            mObjectPool.mActiveLights.erase(index);
            mObjectPool.mFreeLights.pushBack(light);
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
    auto light_lock = sead::makeScopedLock(mObjectPool.mCS);
    auto* placement_mgr = map::PlacementMgr::instance();
    auto end = mObjectPool.mActiveLights.end();
    for (auto it = mObjectPool.mActiveLights.begin(); it != end;) {
        auto* object = it->mObject;
        if (placement_mgr->mPlacementActors->mActorData[object->getActorDataIdx()]._10 == unit) {
            sub_7100F0EC30(object);
            it = mObjectPool.mActiveLights.begin();
            end = mObjectPool.mActiveLights.end();
        } else {
            ++it;
        }
    }
}

void LocationalLightMgr::sub_7100F134E8(map::Object* first, map::Object* last) {
    auto lock = sead::makeScopedLock(mCS);
    auto end = mObjectPool.mActiveLights.end();
    for (auto it = mObjectPool.mActiveLights.begin(); it != end;) {
        auto* object = it->mObject;
        if (object > first && object < last) {
            sub_7100F0EC30(object);
            it = mObjectPool.mActiveLights.begin();
            end = mObjectPool.mActiveLights.end();
        } else {
            ++it;
        }
    }
}

}  // namespace ksys::gfx
