#include "Game/AI/AI/aiEnemyNoticeSound.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

EnemyNoticeSound::EnemyNoticeSound(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyNoticeSound::~EnemyNoticeSound() = default;

bool EnemyNoticeSound::isFinished() const {
    if (ksys::act::ai::Ai::isFinished())
        return true;
    if (!isCurrentChild("行動"))
        return false;
    return getCurrentChild()->isFinished();
}

void EnemyNoticeSound::enter_(ksys::act::ai::InlineParamPack* params) {
    mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_1000000);
    mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_2000000);
    _40 = 30.0f;
    m34();
}

void EnemyNoticeSound::calc_() {
    if (!isCurrentChild("気づき")) {
        ksys::Timer::update(&_40, -1.0f);
        if (_40 < 0.0f) {
            mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_2000000);
            mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_1000000);
        }
    }

    m35();

    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("気づき")) {
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(*mTargetPos_d, "TargetPos", -1);
            changeChild("行動", &pack);
        } else if (getCurrentChild()->isFinished()) {
            setFinished();
        } else {
            setFailed();
        }
    }

    getCurrentChild()->setDynamicParam(*mTargetPos_d, "TargetPos");
}

void EnemyNoticeSound::leave_() {
    sub_71005DB3EC(mActor);
}

void EnemyNoticeSound::m34() {
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    changeChild("気づき", &pack);
}

void EnemyNoticeSound::changeToNotice() {
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    changeChild("気づき", &pack);
}

void EnemyNoticeSound::changeToAct() {
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    changeChild("行動", &pack);
}

void EnemyNoticeSound::loadParams_() {
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void EnemyNoticeSound::m35() {
    if (isCurrentChild("気づき")) {
        const sead::Vector3f pos = *mTargetPos_d;
        sub_71005DB1D8(mActor, pos);
    } else {
        sub_71005DB3EC(mActor);
    }
}

}  // namespace uking::ai
