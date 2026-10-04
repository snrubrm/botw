#pragma once

#include <basis/seadTypes.h>
#include <evfl/EvflAllocator.h>
#include "KingSystem/Event/evtDemoInfo.h"

namespace sead {
class Heap;

}
namespace ksys::evt {

// TODO
class EventResource {
public:
    // 0x7100dc28dc (CSV EventResource::initTimeline): `flow_data` is the EventFlowBase's data at +0x10.
    void initTimeline(void* flow_data);
    // 0x7100dc2b7c (CSV EventResource::initFlowchart)
    void initFlowchart(void* flow_data, void* flowchart_data);
    // 0x7100dc34f8 (CSV EventResource::load; not decompiled)
    bool load(bool a1);
    // 0x7100dc3698 (CSV unnamed): called by EventFlowBase::exitEventMaybe / x with the flow's resource.
    void sub_7100DC3698();

    u8 _0[0x20];
    /* 0x20 */ DemoInfo mDemoInfo;
    u8 _pad_after_demo[0x1b8 - 0x20 - sizeof(DemoInfo)];
    /* 0x1b8 */ void* _1b8;
};

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
