#include "Game/AI/AI/aiPlayerWaterFall.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::ai {

PlayerWaterFall::PlayerWaterFall(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

PlayerWaterFall::~PlayerWaterFall() = default;

bool PlayerWaterFall::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PlayerWaterFall::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void PlayerWaterFall::leave_() {
    ksys::act::ai::Ai::leave_();
}

void PlayerWaterFall::loadParams_() {}

bool PlayerWaterFall::isFinished() const {
    if (isCurrentChild("ジャンプ")) {
        if (getCurrentChild()->isFinished())
            return true;
    }
    return false;
}

bool PlayerWaterFall::isFailed() const {
    if (getCurrentChild()->isFailed())
        return true;
    if (!static_cast<ksys::act::Player*>(mActor)->_207f) {
        if (isCurrentChild("潜水移動") || isCurrentChild("登り"))
            return true;
    }
    return false;
}

}  // namespace uking::ai
