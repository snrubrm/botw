#pragma once

#include <cstddef>
#include <container/seadBuffer.h>
#include <container/seadOffsetList.h>
#include <container/seadPtrArray.h>
#include <environment/aglEnvObjBuffer.h>
#include <hostio/seadHostIONode.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/Utils/Types.h"

namespace gsys { class ModelUnit; }
namespace ksys::map { class Object; }
namespace ksys::eft { class MothEffectEmitter; }
class Unk_7102519378;
class Unk_71025193e8;
class Unk_7102519460;
class Unk_71025194d0;
class Unk_7102519540;
class Unk_71025195b0;
class Unk_7102519620;
class Unk_7102519690;
class Unk_7102519708;
class Unk_7102519778;
class Unk_71025197e8;

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

    // 0x7100f15b18: the pooled release for the render-light records at +0x538 (the 0x1e0-byte
    // Unk_71025197e8 records, not the 0x130-byte light records). The 0x130-byte records'
    // destructors hand their record at +0x120 to this pool.
    class RenderLightPool {
    public:
        // 0x7100f0cd60: allocates `capacity` records (0x1e0 bytes each) and the two PtrArrays, then
        // puts every record on the free list.
        void init(s32 capacity, sead::Heap* heap);
        bool release(Unk_71025197e8* light);

        sead::CriticalSection mCS;
        sead::Buffer<Unk_71025197e8> mLights;
        sead::PtrArray<Unk_71025197e8> mFreeLights;
        sead::PtrArray<Unk_71025197e8> mActiveLights;
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
    // 0x7100f0b5b8 (placeholder name): stores `obj` at +0x58 and gives the allocation argument a
    // maximum of 0x80 for one env object type.
    void sub_7100F0B5B8(void* obj, agl::env::EnvObjBuffer::AllocateArg* arg);
    // 0x7100f13060 (placeholder name): re-registers the manager's env objects for `obj`.
    void sub_7100F13060(void* obj);
    // 0x7100f131c0 (placeholder name): the same re-registration for the second record array.
    void sub_7100F131C0(void* obj);
    // 0x7100f13420: remove the bindings of a model unit.
    void sub_7100F13420(gsys::ModelUnit* unit);
    // 0x7100f134e8: remove bindings whose objects lie in the open range.
    void sub_7100F134E8(map::Object* first, map::Object* last);
    // 0x7100f0ec30: removes the object's lights from the render layers, then releases its binding.
    void sub_7100F0EC30(map::Object* object);
    // 0x7100f13a58: returns a typed light record to its pool after checking its RTTI.
    bool sub_7100F13A58(Unk_7102519378* record);
    // 0x7100f142b0 (pointer type from the +0x538 pool): takes the free record whose position
    // equals `pos`, otherwise the last free record, and pushes it onto the active list.
    Unk_71025197e8* sub_7100F142B0(const sead::Vector3f& pos);
    // The 0x130-byte light records' destructors hand the record at +0x120 to the +0x538 pool.
    bool releaseRenderLight(Unk_71025197e8* light) { return mRenderLightPool.release(light); }
    // Record updates 0x7101296bc4 / 0x7101298558 pass their manager at +0x50.
    // These read the manager's shared light thresholds, rather than record fields.
    f32 sub_7100F143E4() const;
    f32 sub_7100F143FC() const;

    // 0x7100f1334c (placeholder name): sets bit 29 of the manager flags at +0x60, or bit 30 when
    // bit 29 was already set.
    void sub_7100F1334C();
    // inline-only in the original; name is a guess: the record updates (0x7101296bc4, 0x7101297bb4,
    // 0x7101298558) test bit 13 of the manager flags at +0x60.
    bool testFlag2000() const { return _60 & 0x2000; }

    // The locked pool of light records: a CriticalSection, the record buffer and the free / active
    // pointer arrays. The original is one template with a pool per record class; its init
    // (0x7100f0c008 .. 0x7100f0cc28) allocates the records and fills the free list, allocate
    // (0x7100f1356c ..) pops one to the active list and release returns it.
    template <typename T>
    class LightPool {
    public:
        void init(s32 capacity, sead::Heap* heap);
        T* allocate();
        bool release(T* light);

        sead::CriticalSection mCS;
        sead::Buffer<T> mLights;
        sead::PtrArray<T> mFreeLights;
        sead::PtrArray<T> mActiveLights;
    };
    KSYS_CHECK_SIZE_NX150(LightPool<Unk_71025193e8>, 0x70);

private:
    sead::CriticalSection mCS;
    u8 _48[0x10];
    // 0x7100f0b5b8: the environment object being registered.
    void* _58;
    // Ctor initialises this word to 0x1ff00000.
    u32 _60;
    u8 _64[4];
    LightPool<Unk_71025193e8> mRecordPool0;
    LightPool<Unk_7102519460> mRecordPool1;
    LightPool<Unk_71025194d0> mRecordPool2;
    LightPool<Unk_7102519540> mRecordPool3;
    LightPool<Unk_71025195b0> mRecordPool4;
    LightPool<Unk_7102519620> mRecordPool5;
    LightPool<Unk_7102519690> mRecordPool6;
    LightPool<Unk_7102519708> mRecordPool7;
    LightPool<Unk_7102519778> mRecordPool8;
    RigLightPool mRigLightPool;
    LightPool<ObjectLight> mObjectPool;
    RenderLightPool mRenderLightPool;
    u8 _5a8[0x18d8 - 0x5a8];
};

KSYS_CHECK_SIZE_NX150(LocationalLightMgr, 0x18d8);

}  // namespace ksys::gfx
