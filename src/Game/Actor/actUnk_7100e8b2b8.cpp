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

// NON_MATCHING: ours gets a frame record (stp x29, x30; the first temporary at x29 - 4) although the function only tail
// calls; the body (flag updates, type dispatch) is identical
void Unk_7100e8b2b8::m7() {
    const u32 mask4 = 1u << Flag10(Flag10::_4);
    const bool is_set = _10 & mask4;
    const u32 mask = 1u << Flag10(Flag10::_5);
    if (is_set)
        _10 |= mask;
    else
        _10 &= ~mask;
    _10 &= 0xffffffe1;
    const Unk8 type = _8 & 0xff;
    switch (int(type)) {
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

u32 Unk_7100e8b2b8::sub_7100E8C03C() const {
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
