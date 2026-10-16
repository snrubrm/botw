#include "KingSystem/Event/evtEventMgrStruct3.h"
#include "KingSystem/Event/evtEventFlowMgr.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actInfoData.h"

namespace ksys::evt {

// 0x7100dc12a4
// NON_MATCHING: FixedSafeString vptr lifetime and normal Vector2 copy initialization differ.
EventMgrStruct3B::EventMgrStruct3B() = default;

// 0x7100dc1340
void EventMgrStruct3B::sub_7100DC1340(s32 a1, s32 a2, const sead::SafeString& name) {
    _0 = name;
    _160 = 0;
    _164 = a1;
    _168 = a2;
}

// 0x7100dc1448
void EventMgrStruct3B::sub_7100DC1448(bool force) {
    for (s32 i = 0; i < _160; ++i) {
        if (force || !_60[i]->_120)
            _60[i]->unload(force);
    }
    _0.clear();
    _58 = 0;
    _160 = 0;
}

// 0x7100dc22e0
void EventMgrStruct3B::sub_7100DC22E0() {
    if (--_58 != 0)
        return;
    for (s32 i = 0; i < _160; ++i)
        _60[i]->unload(true);
    _0.clear();
    _58 = 0;
    _160 = 0;
}

// 0x71012799c4
EventMgrStruct3A::EventMgrStruct3A() = default;

// 0x71012799d0
EventMgrStruct3A::~EventMgrStruct3A() = default;

// 0x71012799d4
void EventMgrStruct3A::assignToActor(act::Actor* actor) {
    mAssigned = true;
    mActor = actor;
    mHasUniqueName = act::InfoData::instance()->hasTag(actor->getName().cstr(), 0xcab53f3d);
    if (mHasUniqueName && !mActor->getUniqueName())
        mHasUniqueName = false;
}

}  // namespace ksys::evt
