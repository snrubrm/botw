#include "Game/Actor/actRideable.h"
#include "Game/gameHorseMgr.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include "KingSystem/Utils/Thread/Message.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/Attention/actActorAttention.h"
#include "KingSystem/ActorSystem/Attention/actAttClient.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectHorseUnit.h"

namespace uking::act {

Unk_7100e8b2b8::Unk_7100e8b2b8() = default;

Unk_7100e8b2b8::~Unk_7100e8b2b8() = default;

bool Unk_7100e8b2b8::m10(const ksys::Message& message) {
    return message.getType() == 0x380001f;
}

bool Unk_7100e8b2b8::sub_7100E8BFF4() {
    if (auto* mgr = HorseMgr::instance())
        return mgr->sub_7100E84AB8(mActor);
    return false;
}

bool Unk_7100e8b2b8::sub_7100E8C018() {
    if (auto* mgr = HorseMgr::instance())
        return mgr->isLinkedToActor(mActor);
    return false;
}

ksys::act::Actor* Unk_7100e8b2b8::sub_7100E8B644() {
    return sead::DynamicCast<ksys::act::Actor>(_20.getProc(nullptr, nullptr));
}

ksys::act::Actor* Unk_7100e8b2b8::sub_7100E8B6E0() {
    return sead::DynamicCast<ksys::act::Actor>(_20.getProc(nullptr, mActor));
}

void Unk_7100e8b2b8::sub_7100E8BD6C(ksys::act::BaseProc* proc) {
    if (proc)
        _20.acquire(proc, false);
    else
        _20.reset();
}

void Unk_7100e8b2b8::sub_7100E8BD80() {
    auto* attention = mActor->getAttention();
    if (!attention)
        return;
    if (auto* client = attention->getClientByName("Ride"))
        client->enable();
    attention->getClientByName("Ride2");
    if (auto* client = attention->getClientByName("JumpRide"))
        client->enable();
}

void Unk_7100e8b2b8::sub_7100E8BE10() {
    auto* attention = mActor->getAttention();
    if (!attention)
        return;
    if (auto* client = attention->getClientByName("Ride"))
        client->disable();
    if (auto* client = attention->getClientByName("Ride2"))
        client->disable();
    if (auto* client = attention->getClientByName("JumpRide"))
        client->disable();
}

// 0x71024ec700: two SafeStrings in read-only data.
static const sead::SafeString sRiderBoneNames[] = {"Saddle_Root", "Root"};

// NON_MATCHING: the original loads _10 after reloading the spilled flag (ours before)
const sead::SafeString& Unk_7100e8b2b8::sub_7100E8B524() const {
    const Flag10 flag = Flag10::_7;
    return (_10 & (1u << flag)) ? sRiderBoneNames[0] : sRiderBoneNames[1];
}

// NON_MATCHING: only the register of the shared `1` constant (w10 instead of w11) and its position differ
void Unk_7100e8b2b8::m7() {
    const u32 mask4 = 1u << Flag10(Flag10::_4);
    const bool is_set = _10 & mask4;
    const u32 mask = 1u << Flag10(Flag10::_5);
    if (is_set)
        _10 |= mask;
    else
        _10 &= ~mask;
    _10 &= 0xffffffe1;
    switch (int(Unk8(_8 & 0xff))) {
    case Unk8::_1:
        xlinkEventOn(mActor, 0x1d, 1, false);
        break;
    case Unk8::_2:
        xlinkEventOn(mActor, 0x1d, 2, false);
        break;
    case Unk8::_3:
        xlinkEventOn(mActor, 0x1d, 3, false);
        break;
    default:
        xlinkEventOn(mActor, 0x1d, 0, false);
        break;
    }
}

bool Unk_7100e8b2b8::sub_7100E8BFD4() {
    return !(_8.fetchOr(0x100) & 0x100);
}

ksys::act::Unk_7100d14598 Unk_7100e8b2b8::sub_7100E8C03C() const {
    return mActor->getParam()->getRes().mGParamList->getHorseUnit()->mRiddenAnimalType.ref();
}

bool Unk_7100e8b2b8::sub_7100E8C068(sead::Vector3f* pos) {
    const Unk8 type = _8 & 0xff;
    if (int(type) != Unk8::_3)
        return false;
    ksys::act::ActorConstDataAccess accessor;
    if (!ksys::act::acquireActor(&_20, &accessor))
        return false;
    pos->set(accessor.getPreviousPos2());
    return true;
}

}  // namespace uking::act
