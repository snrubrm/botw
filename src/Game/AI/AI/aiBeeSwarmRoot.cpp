#include "Game/AI/AI/aiBeeSwarmRoot.h"
#include "KingSystem/ActorSystem/actAttackSensor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "Game/Actor/actSwarm.h"
#include "Game/Actor/actUnk_71025ae680.h"

namespace uking::ai {

BeeSwarmRoot::BeeSwarmRoot(const InitArg& arg) : SwarmRoot(arg) {}

BeeSwarmRoot::~BeeSwarmRoot() {
    auto& link = mActor->getCreateArgBaseProcLink();
    if (link.hasProc()) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&link, &accessor);
        mActor->sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x300000d),
                            nullptr, false);
    }
}

bool BeeSwarmRoot::init_(sead::Heap* heap) {
    return SwarmRoot::init_(heap);
}

void BeeSwarmRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    SwarmRoot::enter_(params);
    getActorAttackSensor(mActor)->_20 |= 8;
    if (auto* actor = sead::DynamicCast<act::Swarm>(mActor)) {
        if (auto* unit = sead::DynamicCast<uking::act::Unk_710244ff68>(actor->m159()))
            unit->_28 |= 1;
    }
}

void BeeSwarmRoot::calc_() {
    SwarmRoot::calc_();
}

void BeeSwarmRoot::leave_() {
    SwarmRoot::leave_();
}

void BeeSwarmRoot::loadParams_() {
    SwarmRoot::loadParams_();
}

bool BeeSwarmRoot::m35() {
    return SwarmRoot::m35();
}

}  // namespace uking::ai
