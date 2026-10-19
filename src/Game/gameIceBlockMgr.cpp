#include "Game/gameIceBlockMgr.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physQueryContactPointInfo.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/Utils/Thread/Message.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace uking {

// createInstance is NON_MATCHING: store scheduling of the zeroed members in the inlined ctor.
SEAD_SINGLETON_DISPOSER_IMPL(IceBlockMgr)

IceBlockMgr::IceBlockMgr() = default;

// NON_MATCHING: register allocation of the last link reset (the original keeps it in x20).
IceBlockMgr::~IceBlockMgr() {
    _38.clear();
    if (_150) {
        delete _150;
        _150 = nullptr;
    }
    if (_158) {
        ksys::phys::QueryContactPointInfo::free(_158);
        _158 = nullptr;
    }
}

f32 IceBlockMgr::sub_710066F004() const {
    return sead::Mathf::clamp(_140 / 50.0f, 0.0f, 1.0f);
}

bool IceBlockMgr::sub_710066F038() const {
    return _140 > 0.0f;
}

// NON_MATCHING: same calls and stores; the original keeps the transceiver in x20 and the message
// type at sp+4, ours uses x21 and a 0x50 frame, and it copies the ez vector as three words instead
// of one 8-byte and one 4-byte load.
void IceBlockMgr::fadeEffectAndReleaseActorMaybe() {
    _100[_14c].fadeXLink();
    _fc = 0;
    _e9 = 0;
    _ec = sead::Vector3f::ez;

    ksys::act::ActorLinkConstDataAccess accessor;
    if (ksys::act::acquireActor(&_180, &accessor)) {
        mTransceiver.sendMessage(*accessor.getMessageTransceiverId(),
                                 ksys::MessageType(0x80000b7), nullptr, true);
        _180.reset();
    }
}

}  // namespace uking
