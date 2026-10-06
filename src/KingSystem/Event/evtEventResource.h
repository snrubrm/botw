#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
#include <prim/seadDelegate.h>
#include <evfl/EvflAllocator.h>
#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actBaseProcHandle.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Event/evtDemoInfo.h"
#include "KingSystem/Resource/resHandle.h"
#include "KingSystem/Resource/resTempResourceLoader.h"
#include "KingSystem/Utils/Thread/LowPrioThreadMgr.h"

namespace sead {
class Heap;

}
namespace al {
class ByamlIter;
}

namespace ksys::xlink {
class XLink;
}

namespace ksys::res {
// CSV ResDerived (ctor 0x71011fc5c0: `res::Handle::Handle()` + its own vtable store; 71 callers): a res::Handle
// subclass that holds a model resource. Placeholder name; declared only.
class ResDerived : public Handle {
    SEAD_RTTI_OVERRIDE(ResDerived, Handle)
public:
    ResDerived();
    ~ResDerived() override;
    // 0x71011fc618 (CSV ResDerived::getModelRes)
    void* getModelRes();
};
}  // namespace ksys::res

namespace ksys::evt {

class EventFlowBase;
class ActorBindings;
class ResourceFlowchart;
class ResourceTimeline;

// Event xlink information (CSV EventXlinkInfo; vtable-less helper at EventResource + 0x1b8)
class EventXlinkInfo {
public:
    // 0x7100dc96a0 / 0x7100dc9780 (CSV EventXlinkInfo::x_1 / x_0; not decompiled)
    void x_1(EventFlowBase* flow);
    void x_0();
    // 0x7100dc9208 (CSV EventXlinkInfo::finishLoad; not decompiled)
    bool finishLoad(bool a1);
    // 0x7100dc9628: the XLink of the linked actor (null without an acquirable actor)
    xlink::XLink* sub_7100DC9628();

    // Only the members used by x_0 / x_1 are known; the extent is not recovered.
    u8 _0[8];
    /* 0x08 */ act::BaseProcHandle _8;
    /* 0x18 */ act::BaseProcLink _18;
};

// The event camera data of a resource (CSV CameraSystem; at EventResource + 0x148; ctor 0x7100da3b8c, init
// 0x7100da3fe0, not decompiled).
class CameraSystem {
public:
    using LoadFn = sead::Delegate1R<CameraSystem, void*, bool>;

    // 0x7100da3f00: polls the loading of the camera resources; true once they are loaded
    bool finishLoad();

    u8 _0[8];
    /* 0x08 */ s32 _8;  // 1: loading, 2: the low priority request has been submitted
    u8 _c[4];
    /* 0x10 */ sead::Buffer<res::Handle> _10;
    u8 _20[0x30 - 0x20];
    /* 0x30 */ s32 _30;
    u8 _34[0x2c8 - 0x34];
    /* 0x2c8 */ LoadFn _2c8;
};

// 0x7100dcb270 (CSV submitLowPriorityRequest): submits `request` to the LowPrioThreadMgr (if there is one).
void submitLowPriorityRequest(const util::LowPrioThreadMgr::Request& request);

// CSV EventBgmInfo (size 0x70; ctor 0x7100dc6e20, init 0x7100dc7180, finishLoad 0x7100dc7450; declared only).
// EventResource::_1c0.
class EventBgmInfo {
public:
    EventBgmInfo();
    void init(const sead::SafeString& event_name, sead::Heap* heap, bool is_timeline, al::ByamlIter* info,
              res::Handle* pack_handle);

    u8 _0[0x70];
};
static_assert(sizeof(EventBgmInfo) == 0x70);

// TODO
class EventResource {
public:
    // 0x7100dc2360 (CSV EventResource::ctor; not decompiled)
    explicit EventResource(sead::Heap* heap);
    // 0x7100dc28dc (CSV EventResource::initTimeline): `event_name` is the EventFlowBase's mEventName.
    void initTimeline(const sead::SafeString& event_name);
    // 0x7100dc29e8 (CSV EventResource::loadEventPack; not decompiled)
    void loadEventPack();
    // 0x7100dc2b7c (CSV EventResource::initFlowchart)
    void initFlowchart(const sead::SafeString& event_name, const sead::SafeString& entry_point);
    // 0x7100dc34f8 (CSV EventResource::load; not decompiled)
    bool load(bool a1);
    // 0x7100dc3698 (CSV unnamed): called by EventFlowBase::exitEventMaybe / x with the flow's resource.
    void sub_7100DC3698();

    // 0x7100dc245c (CSV EventResource::invokedParseExtraModelRes)
    bool invokedParseExtraModelRes();
    // 0x7100dc2d50 / 0x7100dc2eb4 (CSV EventResource::loadEventResources / finishLoad; not decompiled)
    void loadEventResources(bool a1);
    // 0x7100dc25b8 (CSV EventResource::loadCommon_DemoAndModel; not decompiled)
    void loadCommon_DemoAndModel(const sead::SafeString& event_name, al::ByamlIter* info,
                                 res::Handle* pack_handle, bool a1);
    bool finishLoad(bool a1);

    // 0x7100dc3368 / 0x7100dc33d4 / 0x7100dc421c (CSV EventResource::areCameraAndModelAndXlinkReady /
    // processResourceLoad / EventAddExtraModelRes_stuff; not decompiled)
    bool areCameraAndModelAndXlinkReady();
    bool processResourceLoad(bool a1);
    void EventAddExtraModelRes_stuff(void* a1);

    // 0x71008b5ac4 (CSV EventResource::formatInitStatus; not decompiled)
    void formatInitStatus(sead::BufferedSafeString* out);

    virtual ~EventResource();
    /* 0x08 */ ResourceFlowchart* mFlowchart;
    /* 0x10 */ ResourceTimeline* mTimeline;
    /* 0x18 */ ActorBindings* mActorBindings;
    /* 0x20 */ DemoInfo mDemoInfo;
    u8 _pad_after_demo[0x148 - 0x20 - sizeof(DemoInfo)];
    /* 0x148 */ CameraSystem* _148;
    /* 0x150 */ sead::Heap* mHeap;
    /* 0x158 */ res::ResDerived _158;
    u8 _1a8[8];
    /* 0x1b0 */ void* _1b0;
    /* 0x1b8 */ EventXlinkInfo* _1b8;
    /* 0x1c0 */ EventBgmInfo* _1c0;
    /* 0x1c8 */ res::TempResourceLoader* mTempResourceLoader;
    /* 0x1d0 */ u16 _1d0;
    u8 _1d2;
    /* 0x1d3 */ bool _1d3;
    u8 _1d4[4];
    /* 0x1d8 */ res::Handle* _1d8;
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
