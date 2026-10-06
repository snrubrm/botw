#include "Game/AI/AI/aiLynelNoticeAttacked.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"

namespace uking::ai {

LynelNoticeAttacked::LynelNoticeAttacked(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

LynelNoticeAttacked::~LynelNoticeAttacked() = default;

bool LynelNoticeAttacked::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void LynelNoticeAttacked::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

bool LynelNoticeAttacked::isFailed() const {
    return getCurrentChild()->isFailed();
}

bool LynelNoticeAttacked::isFinished() const {
    return getCurrentChild()->isFinished();
}

void LynelNoticeAttacked::leave_() {
    ksys::act::ai::Ai::leave_();
}

void LynelNoticeAttacked::loadParams_() {
    getStaticParam(&mRepeatMax_s, "RepeatMax");
    getStaticParam(&mRepeatResetTime_s, "RepeatResetTime");
    getStaticParam(&mForceReturnDistFromHomePos_s, "ForceReturnDistFromHomePos");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getAITreeVariable(&mLynelNoticeAttackRepeatNum_a, "LynelNoticeAttackRepeatNum");
}

void LynelNoticeAttacked::sub_7100494D04() {
    sead::Vector3f target;
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
        enemy->_e08._10.getTranslation(target);
    else
        target = getPlayerPosition();
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(target, "TargetPos", -1);
    changeChild("発見", &pack);
}

void LynelNoticeAttacked::calc_() {
    if (_6c.value <= sead::Mathf::epsilon()) {
        *mLynelNoticeAttackRepeatNum_a = 0;
        _6c = ksys::Timer(1.0f, 1.0f, 0.0f);
    } else {
        _6c.update();
    }

    if (*mLynelNoticeAttackRepeatNum_a >= 1) {
        const sead::Vector3f diff = mActor->getMtx().getTranslation() - _60;
        if (diff.x * diff.x + diff.z * diff.z > 16.0f)
            *mLynelNoticeAttackRepeatNum_a = 0;
    }
}

}  // namespace uking::ai
