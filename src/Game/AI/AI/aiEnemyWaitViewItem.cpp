#include "Game/AI/AI/aiEnemyWaitViewItem.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace uking::ai {

EnemyWaitViewItem::EnemyWaitViewItem(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyWaitViewItem::~EnemyWaitViewItem() = default;

bool EnemyWaitViewItem::isFailed() const {
    return ksys::act::ai::Ai::isFailed() || getCurrentChild()->isFailed();
}

bool EnemyWaitViewItem::isFinished() const {
    return ksys::act::ai::Ai::isFinished();
}

bool EnemyWaitViewItem::isChangeable() const {
    return getCurrentChild()->isChangeable();
}

bool EnemyWaitViewItem::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnemyWaitViewItem::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_71003C3A2C(true);
}

void EnemyWaitViewItem::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnemyWaitViewItem::loadParams_() {
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

void EnemyWaitViewItem::calc_() {
    if (!mTargetActor_d->hasProc())
        setFailed();

    auto* child = getCurrentChild();
    if (child->isChangeable())
        sub_71003C3A2C(false);

    ksys::act::ActorConstDataAccess acc;
    ksys::act::acquireActor(mTargetActor_d, &acc);
    sead::Vector3f pos;
    acc.getActorMtx().getTranslation(pos);
    child->setDynamicParam(pos, "TargetPos");
}

}  // namespace uking::ai
