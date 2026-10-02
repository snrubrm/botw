#include "Game/AI/AI/aiPlayerAttack.h"
#include "Game/gameUnk_710246d058.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/ActorSystem/AS/ASList.h"

namespace uking::ai {

PlayerAttack::PlayerAttack(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

bool PlayerAttack::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PlayerAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void PlayerAttack::loadParams_() {}

bool PlayerAttack::isFinished() const {
    if (isCurrentChild("小攻撃") || isCurrentChild("大攻撃")) {
        if (static_cast<ksys::act::PlayerBase*>(mActor)->m224())
            return true;
    }
    if (isCurrentChild("ガード攻撃")) {
        if (static_cast<ksys::act::PlayerBase*>(mActor)->_c40.isOnBit(9))
            return false;
    }
    if (isCurrentChild("大剣回転斬り") &&
        static_cast<ksys::act::PlayerBase*>(mActor)->get17d0()->controllerCheckPressedMaybe(14) &&
        mActor->getASList()->x_1(0, 0) == "CutChargeLswordSpin") {
        return true;
    }
    auto* child = getCurrentChild();
    if (!child->isFinished() && !child->isFailed())
        return false;
    return true;
}

bool PlayerAttack::isChangeable() const {
    if (isCurrentChild("ガード攻撃")) {
        if (static_cast<ksys::act::PlayerBase*>(mActor)->_c40.isOnBit(9))
            return false;
    }
    return getCurrentChild()->isChangeable();
}

}  // namespace uking::ai
