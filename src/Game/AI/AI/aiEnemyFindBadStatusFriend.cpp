#include "Game/AI/AI/aiEnemyFindBadStatusFriend.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace uking::ai {

EnemyFindBadStatusFriend::EnemyFindBadStatusFriend(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyFindBadStatusFriend::~EnemyFindBadStatusFriend() = default;

bool EnemyFindBadStatusFriend::isFailed() const {
    return ksys::act::ai::Ai::isFailed() || getCurrentChild()->isFailed();
}

bool EnemyFindBadStatusFriend::isFinished() const {
    return ksys::act::ai::Ai::isFinished() || getCurrentChild()->isFinished();
}

bool EnemyFindBadStatusFriend::isChangeable() const {
    return getCurrentChild()->isChangeable();
}

bool EnemyFindBadStatusFriend::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnemyFindBadStatusFriend::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_710038BFB0();
}

void EnemyFindBadStatusFriend::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnemyFindBadStatusFriend::loadParams_() {
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

void EnemyFindBadStatusFriend::sub_710038BFB0() {
    ksys::act::ai::InlineParamPack pack;
    sead::Vector3f pos;
    ksys::act::ActorConstDataAccess acc;
    ksys::act::acquireActor(mTargetActor_d, &acc);
    acc.getActorMtx().getTranslation(pos);
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("ビタロック", &pack);
}

void EnemyFindBadStatusFriend::calc_() {
    auto* child = getCurrentChild();
    ksys::act::ActorConstDataAccess acc;
    ksys::act::acquireActor(mTargetActor_d, &acc);
    if (child->isChangeable() && !acc.sub_7100D10FB8())
        setFailed();
    sead::Vector3f pos;
    acc.getActorMtx().getTranslation(pos);
    child->setDynamicParam(pos, "TargetPos");
}

}  // namespace uking::ai
