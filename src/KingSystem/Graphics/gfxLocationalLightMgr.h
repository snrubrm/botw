#pragma once

#include <cstddef>
#include <container/seadBuffer.h>
#include <container/seadOffsetList.h>
#include <container/seadPtrArray.h>
#include <hostio/seadHostIONode.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/Utils/Types.h"

namespace gsys { class ModelUnit; }
namespace ksys::map { class Object; }
namespace ksys::eft { class MothEffectEmitter; }
class Unk_7102519378;
class Unk_71025193e8;

namespace ksys::gfx {

// Graphics +0xaa0: constructor 0x7100f0aca8, allocation size 0x18d8.
// The light pools and shader resources outside this prefix are not modelled yet.
class LocationalLightMgr : public sead::hostio::Node {
    // Native Moth126f160 selects records from this actual active light pool.
    friend class ksys::eft::MothEffectEmitter;
    friend class LocationalLightRig;
public:
    LocationalLightMgr();
    virtual ~LocationalLightMgr();

    // Pooled binding between a placement object and its lights. Constructor 0x7100f17ffc.
    class ObjectLight {
    public:
        class Light;
        ObjectLight();
        // 0x7100f18030 (unnamed in the CSV): binds `object` and stores `this` in its +0x50 hook.
        // The counterpart of detachObject.
        void attachObject(map::Object* object);
        void detachObject();
        // 0x7100f18050: updates every attached light under the binding's lock.
        void updateLights();

        sead::CriticalSection mCS;
        sead::OffsetList<Light> mLights;
        map::Object* mObject = nullptr;
    };
    KSYS_CHECK_SIZE_NX150(ObjectLight, 0x60);

    // The subobject passed to F0CAF0/F15A00/F15A74 at manager +0x458.
    // RigLightPool is an inferred name for this independently locked pool.
    class RigLightPool {
    public:
        void init(s32 capacity, sead::Heap* heap);
        ObjectLight::Light* allocate();
        bool release(ObjectLight::Light* light);

        sead::CriticalSection mCS;
        sead::Buffer<ObjectLight::Light> mLights;
        sead::PtrArray<ObjectLight::Light> mFreeLights;
        sead::PtrArray<ObjectLight::Light> mActiveLights;
    };
    KSYS_CHECK_SIZE_NX150(RigLightPool, 0x70);
    static_assert(offsetof(RigLightPool, mLights) == 0x40);
    static_assert(offsetof(RigLightPool, mFreeLights) == 0x50);
    static_assert(offsetof(RigLightPool, mActiveLights) == 0x60);

    // 0x7100f15b18: the same pooled release for the render-light records at +0x538. The
    // destructors 0x7101296100 / 0x7101296178 hand it their record at +0x120, whose vtable is
    // 0x71025193f8 (class Unk_7102519378).
    class RenderLightPool {
    public:
        bool release(Unk_7102519378* light);

        sead::CriticalSection mCS;
        /// Records are stored as the first concrete record type; the base record is abstract
        /// (vtable slot 5 is __cxa_pure_virtual) and the subclasses only add virtuals.
        sead::Buffer<Unk_71025193e8> mLights;
        sead::PtrArray<Unk_7102519378> mFreeLights;
        sead::PtrArray<Unk_7102519378> mActiveLights;
    };
    KSYS_CHECK_SIZE_NX150(RenderLightPool, 0x70);

    // 0x7100f13368: detach and return an active binding to the free list.
    bool sub_7100F13368(ObjectLight* light);
    // 0x7100f1356c .. 0x7100f139cc: allocate a record from one of the nine record pools.
    Unk_7102519378* sub_7100F1356C();
    Unk_7102519378* sub_7100F135F8();
    Unk_7102519378* sub_7100F13684();
    Unk_7102519378* sub_7100F13710();
    Unk_7102519378* sub_7100F1379C();
    Unk_7102519378* sub_7100F13828();
    Unk_7102519378* sub_7100F138B4();
    Unk_7102519378* sub_7100F13940();
    Unk_7102519378* sub_7100F139CC();
    // 0x7100f13420: remove the bindings of a model unit.
    void sub_7100F13420(gsys::ModelUnit* unit);
    // 0x7100f134e8: remove bindings whose objects lie in the open range.
    void sub_7100F134E8(map::Object* first, map::Object* last);
    // 0x7100f0ec30: removes the object's lights from the render layers, then releases its binding.
    void sub_7100F0EC30(map::Object* object);
    // 0x7100f13a58: returns a typed light record to its pool after checking its RTTI.
    bool sub_7100F13A58(Unk_7102519378* record);
    // The record destructors 0x7101296100 / 0x7101296178 hand their record at +0x120 to the
    // render-light pool at +0x538 through the manager stored at record +0x50.
    bool releaseRenderLight(Unk_7102519378* light) { return mRenderLightPool.release(light); }
    // Record updates 0x7101296bc4 / 0x7101298558 pass their manager at +0x50.
    // These read the manager's shared light thresholds, rather than record fields.
    f32 sub_7100F143E4() const;
    f32 sub_7100F143FC() const;

    // 0x7100f1334c (placeholder name): sets bit 29 of the manager flags at +0x60.
    void sub_7100F1334C();

    // 0x7100f1356c / 0x7100f135f8: the nine identical record pools at +0x68..+0x3e8.
    // Each one stores 0x130-byte render-light records and returns them through init().
    class RecordLightPool {
    public:
        Unk_7102519378* allocate();

        sead::CriticalSection mCS;
        sead::Buffer<Unk_71025193e8> mLights;
        sead::PtrArray<Unk_7102519378> mFreeLights;
        sead::PtrArray<Unk_7102519378> mActiveLights;
    };
    KSYS_CHECK_SIZE_NX150(RecordLightPool, 0x70);

private:
    sead::CriticalSection mCS;
    u8 _48[0x18];
    // Ctor initialises this word to 0x1ff00000.
    u32 _60;
    u8 _64[4];
    RecordLightPool mRecordPools[9];
    RigLightPool mRigLightPool;
    sead::CriticalSection mObjectLightCS;
    sead::Buffer<ObjectLight> mObjectLights;
    sead::PtrArray<ObjectLight> mFreeObjectLights;
    sead::PtrArray<ObjectLight> mActiveObjectLights;
    RenderLightPool mRenderLightPool;
    u8 _5a8[0x18d8 - 0x5a8];
};

KSYS_CHECK_SIZE_NX150(LocationalLightMgr, 0x18d8);

}  // namespace ksys::gfx
