#include "Game/AI/Action/actionLevelFlyLookDownToTgtHeight.h"

namespace uking::action {

LevelFlyLookDownToTgtHeight::LevelFlyLookDownToTgtHeight(const InitArg& arg) : LevelFlyLook(arg) {}

LevelFlyLookDownToTgtHeight::~LevelFlyLookDownToTgtHeight() = default;

bool LevelFlyLookDownToTgtHeight::init_(sead::Heap* heap) {
    return LevelFlyLook::init_(heap);
}

void LevelFlyLookDownToTgtHeight::enter_(ksys::act::ai::InlineParamPack* params) {
    LevelFlyLook::enter_(params);
}

void LevelFlyLookDownToTgtHeight::leave_() {
    LevelFlyLook::leave_();
}

void LevelFlyLookDownToTgtHeight::loadParams_() {
    LevelFlyLook::loadParams_();
}

void LevelFlyLookDownToTgtHeight::calc_() {
    LevelFlyLook::calc_();
}

float LevelFlyLookDownToTgtHeight::m32() {
    return mTargetPos_d->y - *mHeight_s;
}

bool LevelFlyLookDownToTgtHeight::m33(float x) {
    return m32() >= x;
}

}  // namespace uking::action
