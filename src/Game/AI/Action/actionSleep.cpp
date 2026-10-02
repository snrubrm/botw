#include "Game/AI/Action/actionSleep.h"
#include "Game/Actor/actEnemy.h"

namespace uking::action {

Sleep::Sleep(const InitArg& arg) : ActionWithPosAngReduce(arg) {}

Sleep::~Sleep() = default;

bool Sleep::init_(sead::Heap* heap) {
    return ActionWithPosAngReduce::init_(heap);
}

void Sleep::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionWithPosAngReduce::enter_(params);
    m32();
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
        enemy->_e84.set(0x100);
}

void Sleep::leave_() {
    ActionWithPosAngReduce::leave_();
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
        enemy->_e84.reset(0x100);
}

void Sleep::loadParams_() {
    ActionWithPosAngReduce::loadParams_();
}

void Sleep::calc_() {
    ActionWithPosAngReduce::calc_();
}

void Sleep::m32() {
    playAS("Sleep", true, 0, 0, -1.0f);
}

}  // namespace uking::action
