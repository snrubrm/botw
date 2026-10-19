#include "Game/gameIceBlockMgr.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physQueryContactPointInfo.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/Utils/Thread/Message.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actActorHeapUtil.h"

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

// NON_MATCHING: same calls and checks; ours keeps the transceiver in x22 and the accessor address
// in x21, while the original keeps the transceiver in x21 and recomputes sp+8 for the destructor.
void IceBlockMgr::createBlockMaybe() {
    {
        ksys::act::ActorLinkConstDataAccess accessor;
        if (ksys::act::acquireActor(&_180, &accessor)) {
            mTransceiver.sendMessage(*accessor.getMessageTransceiverId(),
                                     ksys::MessageType(0x80000b7), nullptr, true);
            _180.reset();
        }
    }

    if (_170.isAllocatedOrFailed()) {
        if (!_170.hasProcCreationFailed())
            return;
        _170.deleteProc();
    }
    if (_170.isAllocatedOrFailed()) {
        if (!_170.hasProcCreationFailed())
            return;
        _170.deleteProc();
    }

    ksys::act::ActorCreator::instance()->requestCreateActor(
        "Obj_IceMakerBlock", ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(), &_170,
        nullptr, nullptr, 2);
}

// NON_MATCHING: same calls; ours keeps the message type in w24 and the accessor address in x22,
// while the original keeps the type in w23 and recomputes sp+8 for the destructor.
void IceBlockMgr::handOverToActorMaybe(ksys::act::ActorLinkConstDataAccess& other) {
    if (other.hasProc(_180))
        return;

    {
        ksys::act::ActorLinkConstDataAccess accessor;
        if (ksys::act::acquireActor(&_180, &accessor)) {
            mTransceiver.sendMessage(*accessor.getMessageTransceiverId(),
                                     ksys::MessageType(0x80000b7), nullptr, true);
            _180.reset();
        }
    }

    if (other.linkAcquire(&_180)) {
        mTransceiver.sendMessage(*other.getMessageTransceiverId(), ksys::MessageType(0x80000b6),
                                 nullptr, true);
    }
}

void IceBlockMgr::cleanupLinksMaybe() {
    _38.clear();

    auto* transceiver = &mTransceiver;

    if (_60.hasProcInCalcState()) {
        const ksys::MesTransceiverId* id;
        {
            ksys::act::ActorLinkConstDataAccess accessor;
            ksys::act::acquireActor(&_60, &accessor);
            id = accessor.getMessageTransceiverId();
        }
        transceiver->sendMessage(*id, ksys::MessageType(0x8000004), nullptr, true);
    } else {
        ksys::act::ActorLinkConstDataAccess accessor;
        if (ksys::act::acquireActor(&_60, &accessor))
            accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
    }

    if (_70.hasProcInCalcState()) {
        const ksys::MesTransceiverId* id;
        {
            ksys::act::ActorLinkConstDataAccess accessor;
            ksys::act::acquireActor(&_70, &accessor);
            id = accessor.getMessageTransceiverId();
        }
        transceiver->sendMessage(*id, ksys::MessageType(0x8000004), nullptr, true);
    } else {
        ksys::act::ActorLinkConstDataAccess accessor;
        if (ksys::act::acquireActor(&_70, &accessor))
            accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
    }

    if (_80.hasProcInCalcState()) {
        const ksys::MesTransceiverId* id;
        {
            ksys::act::ActorLinkConstDataAccess accessor;
            ksys::act::acquireActor(&_80, &accessor);
            id = accessor.getMessageTransceiverId();
        }
        transceiver->sendMessage(*id, ksys::MessageType(0x8000004), nullptr, true);
    } else {
        ksys::act::ActorLinkConstDataAccess accessor;
        if (ksys::act::acquireActor(&_80, &accessor))
            accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
    }
}

// NON_MATCHING: same calls; ours keeps the accessor address in x21 across getMessageTransceiverId,
// the original recomputes sp+8 for the destructor and keeps the transceiver in x21.
void IceBlockMgr::resetAllMaybe() {
    cleanupLinksMaybe();
    _60.reset();
    _70.reset();
    _80.reset();
    _e8 = 0;
    _f8 = 0;
    fadeEffectAndReleaseActorMaybe();

    if (_170.isAllocatedOrFailed())
        _170.deleteProc();

    {
        auto* transceiver = &mTransceiver;
        ksys::act::ActorLinkConstDataAccess accessor;
        if (ksys::act::acquireActor(&_180, &accessor)) {
            transceiver->sendMessage(*accessor.getMessageTransceiverId(),
                                     ksys::MessageType(0x80000b7), nullptr, true);
            _180.reset();
        }
    }

    _140 = 0;
    _144 = 0;
    _148 = -4.0f;
    _14d = 0;
    _14e = 0;
}

}  // namespace uking
