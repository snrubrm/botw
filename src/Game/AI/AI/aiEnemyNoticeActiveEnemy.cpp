#include "Game/AI/AI/aiEnemyNoticeActiveEnemy.h"
#include <random/seadGlobalRandom.h>

namespace uking::ai {

EnemyNoticeActiveEnemy::EnemyNoticeActiveEnemy(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyNoticeActiveEnemy::~EnemyNoticeActiveEnemy() = default;

bool EnemyNoticeActiveEnemy::init_(sead::Heap* heap) {
    _4c = 15;
    _50 = 30;
    return true;
}

void EnemyNoticeActiveEnemy::enter_(ksys::act::ai::InlineParamPack* params) {
    _48 = _4c == _50 ? _4c : sead::GlobalRandom::instance()->getS32Range(_4c, _50);
    sub_71003A4B3C();
}

void EnemyNoticeActiveEnemy::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnemyNoticeActiveEnemy::loadParams_() {
    getDynamicParam(&mTargetActor_d, "TargetActor");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
