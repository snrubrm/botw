#include "Game/AI/AI/aiStalPartRoot.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::ai {

StalPartRoot::StalPartRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

StalPartRoot::~StalPartRoot() = default;

bool StalPartRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void StalPartRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void StalPartRoot::leave_() {
    auto* actor = mActor;
    if (auto* enemy = sead::DynamicCast<act::Enemy>(actor))
        enemy->_e90 = 3;
    ksys::act::disableAllAttClients(actor);
    sub_71005A8A8C(false);
    actor->resetConnectedCalcParent(false);
    sub_71005DC5DC(actor);
}

void StalPartRoot::loadParams_() {
    getStaticParam(&mInvincibleTime_s, "InvincibleTime");
}

bool StalPartRoot::handleMessage_(const ksys::Message& message) {
    if (message.getType() == 0x3000003)
        sub_71005A8A8C(false);
    return false;
}

}  // namespace uking::ai
