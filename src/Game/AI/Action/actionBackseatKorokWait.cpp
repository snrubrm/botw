#include "Game/AI/Action/actionBackseatKorokWait.h"
#include "Game/Actor/actNPC.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "Game/Actor/actNPC.h"

namespace uking::action {

BackseatKorokWait::BackseatKorokWait(const InitArg& arg) : ksys::act::ai::Action(arg) {}

BackseatKorokWait::~BackseatKorokWait() = default;

bool BackseatKorokWait::init_(sead::Heap* heap) {
    if (auto* npc = sead::DynamicCast<act::NPC>(mActor))
        npc->_1060 = 0;
    return true;
}

void BackseatKorokWait::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    if (!actor->isCalc()) {
        const sead::Vector3f& pos = actor->getMtx().getTranslation();
        const f32 x = pos.x;
        const f32 y = pos.y;
        const f32 z = pos.z;
        const sead::Vector3f& player = getPlayerPosition();
        const f32 px = player.x;
        const f32 py = player.y;
        const f32 pz = player.z;
        const sead::Vector3f dist{x - px, y - py, z - pz};
        if (dist.length() < *mDisappearDist_s) {
            _70 = true;
            mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_20);
        } else {
            _70 = false;
        }
        if (auto* npc = sead::DynamicCast<act::NPC>(mActor))
            npc->_1060 = 0;
    }
    playAS(mWaitASName_s.cstr(), false, 0, 0, -1.0f);
}

void BackseatKorokWait::leave_() {
    ksys::act::ai::Action::leave_();
}

void BackseatKorokWait::loadParams_() {
    getStaticParam(&mAppearDist_s, "AppearDist");
    getStaticParam(&mDisappearDist_s, "DisappearDist");
    getStaticParam(&mWaitASName_s, "WaitASName");
    getStaticParam(&mAppearASName_s, "AppearASName");
    getStaticParam(&mDisappearASName_s, "DisappearASName");
    getMapUnitParam(&mPlacementType_m, "PlacementType");
}

void BackseatKorokWait::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
