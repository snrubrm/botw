#include "Game/AI/Behavior/behaviorBreakIceBlockAtAttackHit.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorAtk.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actTag.h"

namespace uking::behavior {

BreakIceBlockAtAttackHit::BreakIceBlockAtAttackHit(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

BreakIceBlockAtAttackHit::~BreakIceBlockAtAttackHit() = default;

bool BreakIceBlockAtAttackHit::m6(sead::Heap* heap) {
    return true;
}

void BreakIceBlockAtAttackHit::m8() {}

void BreakIceBlockAtAttackHit::m9() {}

void BreakIceBlockAtAttackHit::loadParams() {

}

void BreakIceBlockAtAttackHit::m7() {
    if (!hasAttackInfo(mActor))
        return;
    const int num = getNumAttackInfoMaybe(mActor);
    for (int i = 0; i < num; ++i) {
        auto* info = getAttackInfo(mActor, i);
        if (!info)
            continue;
        if (!ksys::act::hasTag(&info->_50, ksys::act::tags::IsIceMakerBlock))
            continue;
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&info->_50, &accessor);
        mActor->sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x8000004),
                            nullptr, true);
    }
}

}  // namespace uking::behavior
