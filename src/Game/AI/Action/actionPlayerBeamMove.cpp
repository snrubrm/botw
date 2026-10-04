#include "Game/AI/Action/actionPlayerBeamMove.h"
#include "Game/AI/aiXlinkHandle.h"
#include "KingSystem/ActorSystem/Profiles/actBullet.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"

namespace uking::action {

PlayerBeamMove::PlayerBeamMove(const InitArg& arg) : WindCutter(arg) {}

PlayerBeamMove::~PlayerBeamMove() = default;

void PlayerBeamMove::enter_(ksys::act::ai::InlineParamPack* params) {
    WindCutter::enter_(params);
    _c8 = ksys::eft::searchAndEmitSLink(mActor, "Beam", false);
}

void PlayerBeamMove::leave_() {
    WindCutter::leave_();
    xlink::fade(_c8, -1);
}

void PlayerBeamMove::loadParams_() {
    WindCutter::loadParams_();
}

bool PlayerBeamMove::m33() {
    if (WindCutter::m33())
        return true;
    return hasAttackInfo(mActor);
}

f32 PlayerBeamMove::m34() {
    if (auto* bullet = sead::DynamicCast<ksys::act::Bullet>(mActor))
        return bullet->_ca8;
    return WindCutter::m34();
}

int PlayerBeamMove::m37() {
    if (auto* bullet = sead::DynamicCast<ksys::act::Bullet>(mActor))
        return bullet->_cac;
    return WindCutter::m37();
}

}  // namespace uking::action
