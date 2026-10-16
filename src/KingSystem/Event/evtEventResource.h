#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
#include <prim/seadDelegate.h>
#include <evfl/EvflAllocator.h>
#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actBaseProcHandle.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Event/evtDemoInfo.h"
#include "KingSystem/Resource/Event/resDemoASLoader.h"
#include "KingSystem/Resource/resHandle.h"
#include "KingSystem/Resource/resResDerived.h"
#include "KingSystem/Resource/resTempResourceLoader.h"
#include "KingSystem/Sound/sndBgmMgr.h"
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


namespace ksys::evt {

class EventFlowBase;
class ActorBindings;
class ResourceFlowchart;
class ResourceTimeline;

// Event xlink information (CSV EventXlinkInfo; helper at EventResource + 0x1b8)
class EventXlinkInfo {
public:
    // 0x7100dc8ca8 (CSV EventXlinkInfo::ctor)
    EventXlinkInfo();
    // 0x7100dc8db4 / 0x7100dc8ec4: deletes the linked actor
    virtual ~EventXlinkInfo();

    // 0x7100dc96a0 / 0x7100dc9780 (CSV EventXlinkInfo::x_1 / x_0; not decompiled)
    void x_1(EventFlowBase* flow);
    void x_0();
    // 0x7100dc8ee8 (CSV EventXlinkInfo::init): reads elink_user / slink_user from `iter`, loads the SLink bars into
    // _a0 and requests Effect/<elink_user>.esetlist
    void init(bool a1, const al::ByamlIter& iter, sead::Heap* heap, res::Handle* pack);
    // 0x7100dc9208 (CSV EventXlinkInfo::finishLoad; not decompiled)
    bool finishLoad(bool a1);
    // 0x7100dc9628: the XLink of the linked actor (null without an acquirable actor)
    xlink::XLink* sub_7100DC9628();
    // 0x7100dc9404 (CSV unnamed): requests the actor; true when the request was made
    bool sub_7100DC9404();
    // 0x7100dc9da0 (CSV EventXlinkInfo::x; called by init2): false for Demo709_0, Demo721_0 and the three
    // Electric_Relic_BattleField entry points
    bool sub_7100DC9DA0(const sead::SafeString& event_name, const sead::SafeString& entry_point);

    // An element of the two arrays allocated by init2 (0x7100dc9828; three strings each)
    struct Entry {
        sead::SafeString _0;
        sead::SafeString _10;
        sead::SafeString _20;
    };
    static_assert(sizeof(Entry) == 0x30);

    /* 0x08 */ act::BaseProcHandle _8;
    /* 0x18 */ act::BaseProcLink _18;
    /* 0x28 */ sead::Buffer<Entry> _28;
    /* 0x38 */ sead::Buffer<Entry> _38;
    /* 0x48 */ sead::FixedSafeString<64> _48;
    /* 0xa0 */ snd::Unk_7102502950 _a0;
    /* 0xc0 */ bool _c0 = false;
    /* 0xc8 */ sead::FixedSafeString<64> _c8;
    /* 0x120 */ res::Handle _120;
    /* 0x170 */ bool _170 = false;
    /* 0x178 */ sead::Heap* mHeap = nullptr;  // set by init (0x7100dc8ee8)
    /* 0x180 */ bool _180 = false;
    /* 0x181 */ bool _181 = false;
    /* 0x182 */ bool _182 = false;
};
static_assert(sizeof(EventXlinkInfo) == 0x188);

// The event camera data of a resource (CSV CameraSystem; at EventResource + 0x148; ctor 0x7100da3b8c, init
// 0x7100da3fe0, not decompiled).
class CameraSystem {
public:
    using LoadFn = sead::Delegate1R<CameraSystem, void*, bool>;

    // 0x7100da3db4 / 0x7100da3edc (CSV unnamed; not decompiled)
    virtual ~CameraSystem();

    // 0x7100da3f00: polls the loading of the camera resources; true once they are loaded
    bool finishLoad();
    // Constructor DA3B8C binds this member to LoadFn; finishLoad submits that callback.
    bool sub_7100DA3D14(void* user_data);

    /* 0x08 */ s32 _8;  // 1: loading, 2: the low priority request has been submitted
    u8 _c[4];
    /* 0x10 */ sead::Buffer<res::Handle> _10;
    u8 _20[0x30 - 0x20];
    /* 0x30 */ s32 _30;
    u8 _34[0x2c8 - 0x34];
    /* 0x2c8 */ LoadFn _2c8;
};

// 0x7100dcb270 (CSV submitLowPriorityRequest): submits `request` to the LowPrioThreadMgr (false if there is none).
bool submitLowPriorityRequest(const LowPrioThreadMgr::Request& request);

// CSV EventBgmInfo (size 0x70; ctor 0x7100dc6e20, init 0x7100dc7180, finishLoad 0x7100dc7450; declared only).
// EventResource::_1c0.
class EventBgmInfo {
public:
    EventBgmInfo();
    virtual ~EventBgmInfo();
    void init(const sead::SafeString& event_name, sead::Heap* heap, bool is_timeline, al::ByamlIter* info,
              res::Handle* pack_handle);

    // BGM names (the destructor 0x7100dc6f74 releases each one from the sound system before freeing the buffer).
    sead::Buffer<sead::FixedSafeString<64>> _8;
    sead::FixedSafeString<64> _18{sead::SafeString::cEmptyString};
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
    /* 0xc0 */ res::Handle _c0;
    /* 0x110 */ sead::FixedSafeString<32> _110;
    /* 0x148 */ CameraSystem* _148;
    /* 0x150 */ sead::Heap* mHeap;
    /* 0x158 */ res::ResDerived _158;
    /* 0x1a8 */ res::DemoASLoader* _1a8{};
    /* 0x1b0 */ void* _1b0{};
    /* 0x1b8 */ EventXlinkInfo* _1b8{};
    /* 0x1c0 */ EventBgmInfo* _1c0{};
    /* 0x1c8 */ res::TempResourceLoader* mTempResourceLoader;
    /* 0x1d0 */ u16 _1d0 = 0;
    u8 _1d2;
    /* 0x1d3 */ bool _1d3;
    u8 _1d4[4];
    /* 0x1d8 */ res::Handle* _1d8;
    union {
        /* 0x1e0 */ u32 _1e0 = 0;
        u8 _1e0_bytes[4];
    };
    /* 0x1e8 */ sead::DelegateR<EventResource, bool> _1e8{this, &EventResource::invokedParseExtraModelRes};
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
