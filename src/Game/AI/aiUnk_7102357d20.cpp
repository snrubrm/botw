#include "Game/AI/aiUnk_7102357d20.h"
#include <prim/seadScopedLock.h>
#include "Game/AI/aiUnk_71025be918.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Utils/Thread/MessageAck.h"

bool Unk_7102357d20::sub_710070DBB0(const ksys::MesTransceiverId& dest, bool ack) {
    _14 = false;
    if (!_8)
        return false;
    return _8->sendMessage(dest, _10, m2(), ack);
}

bool Unk_7102357d20::sub_710070DC38(ksys::act::Actor* actor, bool ack) {
    const auto* dest = actor->getMesTransceiverId();
    _14 = false;
    if (!_8)
        return false;
    return _8->sendMessage(*dest, _10, m2(), ack);
}

bool Unk_7102357d20::sub_710070DCC0(ksys::act::BaseProcLink* link, bool ack) {
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(link, &accessor);
    return sub_710070DD78(accessor, ack);
}

bool Unk_7102357d20::sub_710070DD78(const ksys::act::ActorLinkConstDataAccess& accessor,
                                    bool ack) {
    const auto* dest = accessor.getMessageTransceiverId();
    _14 = false;
    if (!_8)
        return false;
    return _8->sendMessage(*dest, _10, m2(), ack);
}

bool Unk_7102357d20::sub_710070DE10(const ksys::MesTransceiverId& dest, bool ack) {
    _14 = false;
    if (!_8)
        return false;
    return _8->sendMessageOnProcessingThread(dest, _10, m2(), ack);
}

bool Unk_7102357d20::sub_710070DE98(ksys::act::Actor* actor, bool ack) {
    const auto* dest = actor->getMesTransceiverId();
    _14 = false;
    if (!_8)
        return false;
    return _8->sendMessageOnProcessingThread(*dest, _10, m2(), ack);
}

bool Unk_7102357d20::sub_710070DF20(ksys::act::BaseProcLink* link, bool ack) {
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(link, &accessor);
    return sub_710070DFD8(accessor, ack);
}

bool Unk_7102357d20::sub_710070DFD8(const ksys::act::ActorLinkConstDataAccess& accessor,
                                    bool ack) {
    const auto* dest = accessor.getMessageTransceiverId();
    _14 = false;
    if (!_8)
        return false;
    return _8->sendMessageOnProcessingThread(*dest, _10, m2(), ack);
}

bool Unk_7102357d20::sub_710070E070(const ksys::MessageAck& ack) {
    if (ack.getType() != _10 || ack.getUserData() != m2())
        return false;
    _14 = ack.isDestinationValid() && ack.isSuccess();
    return true;
}

// ---- Senders with JobQueueLock-guarded payloads ----

Unk_710237ecc0::Unk_710237ecc0(ksys::act::Actor* actor) : Unk_7102357d20(actor, 0x800001e) {}

Unk_710237ecc0_Payload::Unk_710237ecc0_Payload() = default;

void Unk_710237ecc0_Payload::sub_710070E194(ksys::act::BaseProcLink* out) {
    sead::ScopedLock<sead::JobQueueLock> lock(&mLock);
    *out = mLink;
}

void Unk_710237ecc0_Payload::sub_710070E1F8(ksys::act::BaseProc* proc) {
    sead::ScopedLock<sead::JobQueueLock> lock(&mLock);
    mLink.acquire(proc, false);
}

Unk_71023b1608::Unk_71023b1608(ksys::act::Actor* actor) : Unk_7102357d20(actor, 0x800001b) {}

Unk_71023b1608_Payload::Unk_71023b1608_Payload() = default;

void Unk_71023b1608_Payload::sub_710070E374(ksys::act::BaseProcLink* out) {
    sead::ScopedLock<sead::JobQueueLock> lock(&mLock);
    *out = mLink;
}

void Unk_71023b1608_Payload::sub_710070E3D8(ksys::act::BaseProc* proc) {
    sead::ScopedLock<sead::JobQueueLock> lock(&mLock);
    mLink.acquire(proc, false);
}

void Unk_7102413c08_Payload::sub_710070E270(Unk_7102413c08_Payload* out) {
    sead::ScopedLock<sead::JobQueueLock> lock(&mLock);
    out->_4 = _4;
    out->_8 = _8;
}

void Unk_7102413c08::sub_710070E2BC(const Unk1& a, s32 b) {
    sead::ScopedLock<sead::JobQueueLock> lock(&_18.mLock);
    _18._4 = a;
    _18._8 = b;
}

void Unk_71023b0898_Payload::Data::sub_71009033FC(const Data& other) {
    _0 = other._0;
    _8 = other._8;
}

Unk_710001bf60::Unk_710001bf60(ksys::act::Actor* actor)
    : mActor(actor), _40(actor, 0x800002f), _58(actor, 0x8000030) {}

Unk_710001bf60::~Unk_710001bf60() = default;

// NON_MATCHING: the original presets the return value (false) before the null checks; we emit a separate
// `mov w0, wzr` block
bool Unk_710001bf60::sub_710001C000(s32 slot, const sead::SafeString& tg_name,
                                    const sead::SafeString& start_as,
                                    const sead::SafeString& loop_as, const sead::SafeString& end_as,
                                    const sead::SafeString& partial_bone,
                                    Unk_71025be918Data* data) {
    bool result = false;
    if (data) {
        if (mActor) {
            _78 = data;
            data->sub_7100707A88(slot, partial_bone);
            _70 = mActor->findPhysicsBodyByName(sub_71007A24D0()->cstr(), tg_name.cstr());
            _8 = slot;
            _10 = start_as;
            _20 = loop_as;
            _30 = end_as;
            result = true;
        }
    }
    return result;
}

void Unk_710001bf60::sub_710001C0D8() {
    if (_78)
        _78->sub_71007081B8();
    if (auto* as_list = mActor->getASList())
        as_list->startAnimationMaybe(-1.0f, -1.0f, _10, _8, 0, true);
    if (_70)
        sub_71007A35EC(_70);
    _c = 1;
}

void Unk_710001bf60::sub_710001C13C() {
    if (_70)
        sub_71007A3470(_70);
    if (auto* as_list = mActor->getASList())
        as_list->startAnimationMaybe(-1.0f, -1.0f, _30, _8, 0, true);
    _c = 3;
}

void Unk_710001bf60::sub_710001C194() {
    if (_c == 0)
        return;
    _c = 0;
    if (_78)
        _78->sub_7100708308();
    if (_70)
        sub_71007A3470(_70);
}

void Unk_710001bf60::sub_710001C1DC() {
    switch (_c) {
    case 1:
        if (auto* as_list = mActor->getASList()) {
            if (as_list->x_4(_8, 0)) {
                if (auto* as_list2 = mActor->getASList())
                    as_list2->startAnimationMaybe(-1.0f, -1.0f, _20, _8, 0, true);
                _c = 2;
            }
        }
        break;
    case 2:
        if (auto* as_list = mActor->getASList()) {
            if (as_list->x_4(_8, 0)) {
                if (_70)
                    sub_71007A3470(_70);
                if (auto* as_list2 = mActor->getASList())
                    as_list2->startAnimationMaybe(-1.0f, -1.0f, _30, _8, 0, true);
                _c = 3;
            }
        }
        break;
    case 3:
        if (auto* as_list = mActor->getASList()) {
            if (as_list->x_4(_8, 0)) {
                if (_78)
                    _78->sub_7100708308();
                _c = 0;
            }
        }
        break;
    }
}
