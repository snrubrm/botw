#include "Game/Actor/actRideable.h"
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

bool Unk_7100e8b2b8::sub_7100E8BFD4() {
    return !(_8.fetchOr(0x100) & 0x100);
}

s32 Unk_7100e8b2b8::sub_7100E8C03C() const {
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
