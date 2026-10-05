#include "Game/AI/AI/aiEnemyWarnNoticeEndChase.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"

namespace uking::ai {

EnemyWarnNoticeEndChase::EnemyWarnNoticeEndChase(const InitArg& arg) : EnemyWarnNoticeSelect(arg) {}

EnemyWarnNoticeEndChase::~EnemyWarnNoticeEndChase() = default;

bool EnemyWarnNoticeEndChase::init_(sead::Heap* heap) {
    return EnemyWarnNoticeSelect::init_(heap);
}

void EnemyWarnNoticeEndChase::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyWarnNoticeSelect::enter_(params);
    _14c = false;
}

void EnemyWarnNoticeEndChase::leave_() {
    EnemyWarnNoticeSelect::leave_();
}

void EnemyWarnNoticeEndChase::calc_() {
    const s32 condition = sub_71003C4EA4();
    if (condition != 0) {
        sub_71003C5B04(&_13c);
        _14c = ksys::act::isPlayerProfile(mTargetActor_d);
    }
    if (!isCurrentChild("追跡")) {
        EnemyWarnNoticeSelect::calc_();
        return;
    }

    ksys::Timer::update(&_148, -1.0f);
    if (_148 < 0.0f) {
        mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_2000000);
        mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_1000000);
    }
    if (condition != 0)
        _ac.reset();
    else
        _ac.update();
    sub_71003C56A8();
    if (!_14c)
        mActor->m93(2, 0.0f);

    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (sub_71003C5418(condition))
            sub_71003C4CB4(false);
        else
            setFinished();
        return;
    }
    if (child->isChangeable() && (sub_71003C5418(condition) || sub_71003C544C()))
        sub_71003C4CB4(false);
    child->setDynamicParam(_13c, "TargetPos");
}

void EnemyWarnNoticeEndChase::loadParams_() {
    EnemyWarnNoticeSelect::loadParams_();
}

void EnemyWarnNoticeEndChase::m34() {
    _148 = 30.0f;
    ksys::act::ai::InlineParamPack params;
    params.addVec3(_13c, "TargetPos", -1);
    changeChild("追跡", &params);
}

}  // namespace uking::ai
