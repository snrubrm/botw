#include "Game/AI/AI/aiPlayerCutJump.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"

namespace uking::ai {

PlayerCutJump::PlayerCutJump(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

bool PlayerCutJump::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PlayerCutJump::enter_(ksys::act::ai::InlineParamPack* params) {
    if (hasPendingChildChange())
        changeChild(mPendingChildIdx);
    else if (static_cast<ksys::act::PlayerBase*>(mActor)->m194())
        changeChild("落下斬り");
    else
        changeChild("ジャンプ斬り");
}

void PlayerCutJump::calc_() {
    handlePendingChildChange();
}

void PlayerCutJump::loadParams_() {}

}  // namespace uking::ai
