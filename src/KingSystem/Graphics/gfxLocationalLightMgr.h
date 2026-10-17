#pragma once

#include <container/seadBuffer.h>
#include <container/seadOffsetList.h>
#include <container/seadPtrArray.h>
#include <hostio/seadHostIONode.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/Utils/Types.h"

namespace gsys { class ModelUnit; }
namespace ksys::map { class Object; }
class Unk_7102519378;

namespace ksys::gfx {

// Graphics +0xaa0: constructor 0x7100f0aca8, allocation size 0x18d8.
// The light pools and shader resources outside this prefix are not modelled yet.
class LocationalLightMgr : public sead::hostio::Node {
public:
    LocationalLightMgr();
    virtual ~LocationalLightMgr();

    // Pooled binding between a placement object and its lights. Constructor 0x7100f17ffc.
    class ObjectLight {
    public:
        class Light;
        ObjectLight();
        void detachObject();

        sead::CriticalSection mCS;
        sead::OffsetList<Light> mLights;
        map::Object* mObject = nullptr;
    };
    KSYS_CHECK_SIZE_NX150(ObjectLight, 0x60);

    // 0x7100f13368: detach and return an active binding to the free list.
    bool sub_7100F13368(ObjectLight* light);
    // 0x7100f13420: remove the bindings of a model unit.
    void sub_7100F13420(gsys::ModelUnit* unit);
    // 0x7100f134e8: remove bindings whose objects lie in the open range.
    void sub_7100F134E8(map::Object* first, map::Object* last);
    // 0x7100f0ec30: removes the object's lights from the render layers, then releases its binding.
    void sub_7100F0EC30(map::Object* object);
    // 0x7100f13a58: returns a typed light record to its pool after checking its RTTI.
    bool sub_7100F13A58(Unk_7102519378* record);
    // Record updates 0x7101296bc4 / 0x7101298558 pass their manager at +0x50.
    // These read the manager's shared light thresholds, rather than record fields.
    f32 sub_7100F143E4() const;
    f32 sub_7100F143FC() const;

private:
    sead::CriticalSection mCS;
    u8 _48[0x4c8 - 0x48];
    sead::CriticalSection mObjectLightCS;
    sead::Buffer<ObjectLight> mObjectLights;
    sead::PtrArray<ObjectLight> mFreeObjectLights;
    sead::PtrArray<ObjectLight> mActiveObjectLights;
    u8 _538[0x18d8 - 0x538];
};

KSYS_CHECK_SIZE_NX150(LocationalLightMgr, 0x18d8);

}  // namespace ksys::gfx
