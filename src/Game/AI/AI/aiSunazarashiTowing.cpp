#include "Game/AI/AI/aiSunazarashiTowing.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

SunazarashiTowing::SunazarashiTowing(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SunazarashiTowing::~SunazarashiTowing() = default;

bool SunazarashiTowing::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SunazarashiTowing::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F5EDE0(0.0f);
        controller->sub_7100F5EDD8(1.0f);
    }
    changeChild("牽引開始");
}

void SunazarashiTowing::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SunazarashiTowing::loadParams_() {}

bool SunazarashiTowing::isChangeable() const {
    if (isCurrentChild("牽引開始") || isCurrentChild("プレイヤーを牽引"))
        return false;
    auto* child = getCurrentChild();
    if (isCurrentChild("牽引終了"))
        return child->isFinished();
    return ksys::act::ai::Ai::isChangeable();
}

}  // namespace uking::ai
