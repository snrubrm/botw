#include "Game/AI/AI/aiZoraHeroWarp2Player.h"
#include "Game/AI/aiUnk_71006F5B14.h"
#include "Game/Actor/actNPC.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

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

void ZoraHeroWarp2Player::calc_() {
    auto* child = getCurrentChild();
    if (!child->isFinished() && !child->isFailed())
        return;
    if (!isCurrentChild("もぐる")) {
        setFinished();
        return;
    }
    sead::Vector3f pos = *mTargetPos_d;
    pos.y -= *mDepthOffset_s;
    ksys::act::sub_7100EE5B18(mActor, pos);
    if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F5F6FC(sead::Vector3f::zero);
        controller->sub_7100F5FB24(sead::Vector3f::zero);
    }
    changeChild("でてくる");
}

void ZoraHeroWarp2Player::leave_() {
    auto* actor = mActor;
    ksys::act::enableAttClient(actor, "Ride");
    if (auto* npc = sead::DynamicCast<act::NPC>(actor))
        npc->_fe8 &= ~0x10000000;
    if (!actor->get68f() && sub_71006F566C(actor))
        sub_71006F55D8(actor);
}

void ZoraHeroWarp2Player::loadParams_() {
    getStaticParam(&mDepthOffset_s, "DepthOffset");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
