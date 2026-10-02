#include "Game/AI/AI/aiEnemyRecognizeTargetBase.h"

namespace uking::ai {

EnemyRecognizeTargetBase::EnemyRecognizeTargetBase(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyRecognizeTargetBase::~EnemyRecognizeTargetBase() = default;

bool EnemyRecognizeTargetBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnemyRecognizeTargetBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

bool EnemyRecognizeTargetBase::isChangeable() const {
    return getCurrentChild()->isChangeable();
}

// NON_MATCHING: the original computes &_c0 into a callee-saved register before the sender call
void EnemyRecognizeTargetBase::leave_() {
    if (_c0._30) {
        _90.sub_710070DCC0(&_c0._38._10, true);
        _c0.x();
    }
}

void EnemyRecognizeTargetBase::loadParams_() {
    getStaticParam(&mLostTimer_s, "LostTimer");
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mCryInterval_s, "CryInterval");
    getStaticParam(&mRandomCryInterval_s, "RandomCryInterval");
    getStaticParam(&mRandomCryIntervalMax_s, "RandomCryIntervalMax");
    getStaticParam(&mSpreadDist_s, "SpreadDist");
    getStaticParam(&mNoCryDist_s, "NoCryDist");
}

bool EnemyRecognizeTargetBase::m34() {
    return false;
}

bool EnemyRecognizeTargetBase::m35() {
    return true;
}

bool EnemyRecognizeTargetBase::handleMessage_(const ksys::Message& message) {
    return _c0.m2(message);
}

}  // namespace uking::ai
