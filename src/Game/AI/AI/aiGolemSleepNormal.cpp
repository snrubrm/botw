#include "Game/AI/AI/aiGolemSleepNormal.h"
#include "Game/AI/aiUnk_7102357210.h"
#include "Game/Actor/actGiantEnemy.h"

namespace uking::ai {

GolemSleepNormal::GolemSleepNormal(const InitArg& arg) : SpecialEnemySleep(arg) {}

GolemSleepNormal::~GolemSleepNormal() = default;

bool GolemSleepNormal::init_(sead::Heap* heap) {
    return SpecialEnemySleep::init_(heap);
}

void GolemSleepNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    SpecialEnemySleep::enter_(params);
}

void GolemSleepNormal::leave_() {
    SpecialEnemySleep::leave_();
}

bool GolemSleepNormal::handleAck_(const ksys::MessageAck& ack) {
    if (_a8.sub_710070E070(ack))
        return true;
    return _90.sub_710070E070(ack);
}

void GolemSleepNormal::m34() {
    if (auto* giant = sead::DynamicCast<act::GiantEnemy>(mActor))
        giant->_1568 = 0;
    sub_7100708FF0(mActor, 30.0f);
    SpecialEnemySleep::m34();
}

void GolemSleepNormal::loadParams_() {
    SpecialEnemySleep::loadParams_();
    getAITreeVariable(&mGolemChemicalController_a, "GolemChemicalController");
}

}  // namespace uking::ai
