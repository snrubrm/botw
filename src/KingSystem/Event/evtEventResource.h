#pragma once

#include <basis/seadTypes.h>
#include <evfl/EvflAllocator.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Event/evtDemoInfo.h"

namespace sead {
class Heap;

}
namespace ksys::evt {

class EventFlowBase;
class ActorBindings;

// Event xlink information (CSV EventXlinkInfo; vtable-less helper at EventResource + 0x1b8)
class EventXlinkInfo {
public:
    // 0x7100dc96a0 / 0x7100dc9780 (CSV EventXlinkInfo::x_1 / x_0; not decompiled)
    void x_1(EventFlowBase* flow);
    void x_0();
    // 0x7100dc9208 (CSV EventXlinkInfo::finishLoad; not decompiled)
    bool finishLoad(bool a1);
};

// The event camera data of a resource (CSV CameraSystem; at EventResource + 0x148; ctor 0x7100da3b8c, init
// 0x7100da3fe0, not decompiled).
class CameraSystem {
public:
    // 0x7100da3f00: polls the loading of the camera resources; true once they are loaded
    bool finishLoad();
};

// TODO
class EventResource {
public:
    // 0x7100dc2360 (CSV EventResource::ctor; not decompiled)
    explicit EventResource(sead::Heap* heap);
    // 0x7100dc28dc (CSV EventResource::initTimeline): `flow_data` is the EventFlowBase's data at +0x10.
    void initTimeline(void* flow_data);
    // 0x7100dc2b7c (CSV EventResource::initFlowchart)
    void initFlowchart(void* flow_data, void* flowchart_data);
    // 0x7100dc34f8 (CSV EventResource::load; not decompiled)
    bool load(bool a1);
    // 0x7100dc3698 (CSV unnamed): called by EventFlowBase::exitEventMaybe / x with the flow's resource.
    void sub_7100DC3698();

    // 0x7100dc3368 / 0x7100dc33d4 / 0x7100dc421c (CSV EventResource::areCameraAndModelAndXlinkReady /
    // processResourceLoad / EventAddExtraModelRes_stuff; not decompiled)
    bool areCameraAndModelAndXlinkReady();
    bool processResourceLoad(bool a1);
    bool EventAddExtraModelRes_stuff(void* a1);

    // 0x71008b5ac4 (CSV EventResource::formatInitStatus; not decompiled)
    void formatInitStatus(sead::BufferedSafeString* out);

    virtual ~EventResource();
    u8 _8[0x10];
    /* 0x18 */ ActorBindings* mActorBindings;
    /* 0x20 */ DemoInfo mDemoInfo;
    u8 _pad_after_demo[0x148 - 0x20 - sizeof(DemoInfo)];
    /* 0x148 */ CameraSystem* _148;
    u8 _150[0x1b8 - 0x150];
    /* 0x1b8 */ EventXlinkInfo* _1b8;
    u8 _1c0[0x1d3 - 0x1c0];
    /* 0x1d3 */ bool _1d3;
    u8 _1d4[0x1e0 - 0x1d4];
    union {
        /* 0x1e0 */ u32 _1e0;
        u8 _1e0_bytes[4];
    };
    u8 _1e4[0x208 - 0x1e4];
};
static_assert(sizeof(EventResource) == 0x208);

void* eventFlowAlloc(size_t size, size_t alignment, void* userdata);
void eventFlowFree(void* ptr, void* userdata);

inline evfl::AllocateArg makeEvflAllocateArg(sead::Heap* heap) {
    evfl::AllocateArg arg{};
    arg.alloc = eventFlowAlloc;
    arg.free = eventFlowFree;
    arg.alloc_userdata = heap;
    arg.free_userdata = heap;
    return arg;
}

}  // namespace ksys::evt
