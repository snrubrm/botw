#include "Game/AI/AI/aiWizzrobeBlownOff.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::ai {

WizzrobeBlownOff::WizzrobeBlownOff(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WizzrobeBlownOff::~WizzrobeBlownOff() = default;

bool WizzrobeBlownOff::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void WizzrobeBlownOff::enter_(ksys::act::ai::InlineParamPack* params) {
    _48 = false;
    _49 = false;
    changeChild("ふっとび", params);
}

void WizzrobeBlownOff::leave_() {
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F605C8(sead::Vector3f::zero);
}

void WizzrobeBlownOff::loadParams_() {
    getStaticParam(&mDrownDepth_s, "DrownDepth");
    getStaticParam(&mIsForceGetUp_s, "IsForceGetUp");
}

bool WizzrobeBlownOff::isFinished() const {
    if (ksys::act::ai::Ai::isFinished())
        return true;
    if (isCurrentChild("起き上がり") || isCurrentChild("チャンスタイム")) {
        if (getCurrentChild()->isFinished())
            return true;
    }
    return false;
}

bool WizzrobeBlownOff::isFailed() const {
    if (ksys::act::ai::Ai::isFailed())
        return true;
    if (isCurrentChild("起き上がり") || isCurrentChild("チャンスタイム")) {
        if (getCurrentChild()->isFailed())
            return true;
    }
    return false;
}

}  // namespace uking::ai
