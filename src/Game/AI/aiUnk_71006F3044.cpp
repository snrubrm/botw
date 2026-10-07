#include "Game/AI/aiUnk_71006F3044.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "Game/Actor/actUnk_7100d3cd74.h"
#include "Game/Actor/actBeamBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Sound/sndMgr.h"

Unk_71006f3044::Unk_71006f3044(ksys::act::Actor* actor)
    : mActor(actor), _88(actor, 0x8000038), _a0(actor, 0x8000039) {}

// NON_MATCHING: the original loads the address of the dummy BaseProcLink directly; ours calls
// ksys::act::getDummyBaseProcLink().
ksys::act::BaseProcLink& Unk_71006f3044::sub_71006F3934() {
    if (_80._0) {
        if (auto* link = sead::DynamicCast<Unk_71023da520>(*_80._0)) {
            if (link->mRefCount >= 1)
                return sead::DynamicCast<Unk_71023da520>(*_80._0)->mLink;
        }
    }
    if (auto* parts = mActor->m101())
        return parts->getActorPartsActor(_28);
    return ksys::act::getDummyBaseProcLink();
}

void Unk_71006f3044::sub_71006F3A6C() {}

void Unk_71006f3044::sub_71006F3B14(bool on) {
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&sub_71006F3934(), &accessor);
    if (on)
        _a0.sub_710070DE10(*accessor.getMessageTransceiverId(), true);
    else
        _a0.sub_710070DBB0(*accessor.getMessageTransceiverId(), true);
}

void Unk_71006f3044::sub_71006F3A70(bool on) {
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&sub_71006F3934(), &accessor);
    if (!accessor.isStateCalc())
        accessor.setProperties(mActor->getMtx(), nullptr, nullptr, nullptr, false, 0, -1);
    if (on)
        _88.sub_710070DE10(*accessor.getMessageTransceiverId(), true);
    else
        _88.sub_710070DBB0(*accessor.getMessageTransceiverId(), true);
}

void Unk_71006f3044::sub_71006F3B84() {
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&sub_71006F3934(), &accessor);
    uking::act::sub_7100003C34(accessor);
}

void Unk_71006f3044::sub_71006F3BC4(const sead::Vector3f* dir) {
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&sub_71006F3934(), &accessor);
    sub_71002C7D1C(accessor, *dir);
}

// NON_MATCHING: the sound manager is loaded before the actor ID query, requiring an extra saved value.
bool Unk_71006f3044::sub_71006F38A4(ksys::act::Actor* actor) {
    if (_b8)
        return true;
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&sub_71006F3934(), &accessor);
    _b8 = ksys::snd::SoundMgr::instance()->_a8->sub_710104B68C(actor, accessor.getId());
    return _b8;
}
