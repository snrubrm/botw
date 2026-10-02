#include "Game/AI/AI/aiZoraHeroWarp2Player.h"
#include "Game/Actor/actNPC.h"
#include "KingSystem/ActorSystem/actActorUtil.h"

namespace uking::ai {

ZoraHeroWarp2Player::ZoraHeroWarp2Player(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

ZoraHeroWarp2Player::~ZoraHeroWarp2Player() = default;

bool ZoraHeroWarp2Player::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void ZoraHeroWarp2Player::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    ksys::act::disableAttClient(actor, "Ride");
    if (auto* npc = sead::DynamicCast<act::NPC>(actor))
        npc->_fe8 |= 0x10000000;
    changeChild("もぐる");
}

void ZoraHeroWarp2Player::leave_() {
    ksys::act::ai::Ai::leave_();
}

void ZoraHeroWarp2Player::loadParams_() {
    getStaticParam(&mDepthOffset_s, "DepthOffset");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
