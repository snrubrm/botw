#include "Game/AI/AI/aiEnemyWaitViewItem.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

bool sub_71006DE574(const ksys::act::ActorConstDataAccess& accessor);
bool sub_71006DE3D8(const ksys::act::ActorConstDataAccess& accessor);
bool sub_71006DE4A4(const ksys::act::ActorConstDataAccess& accessor);

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

void EnemyWaitViewItem::m34() {}

void EnemyWaitViewItem::m35() {}

void EnemyWaitViewItem::m36() {}

// Picks the child from the EnemyShown params of the target (noise: cheer, happy: gather, sit: dejected,
// else watch); unless `force` is set, the current child is kept.
void EnemyWaitViewItem::sub_71003C3A2C(bool force) {
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(mTargetActor_d, &accessor);
    if (sub_71006DE574(accessor)) {
        if (force || !isCurrentChild("囃し立てる"))
            changeToCheer();
    } else if (sub_71006DE3D8(accessor)) {
        if (force || !isCurrentChild("団欒"))
            changeToGather();
    } else if (sub_71006DE4A4(accessor)) {
        if (force || !isCurrentChild("しょんぼり"))
            changeToDejected();
    } else {
        if (force || !isCurrentChild("注視"))
            changeToWatch();
    }
}

bool EnemyWaitViewItem::sub_71003C3C68() {
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(mTargetActor_d, &accessor);
    return sub_71006DE3D8(accessor);
}

void EnemyWaitViewItem::changeToGather() {
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(mTargetActor_d, &accessor);
    sead::Vector3f pos;
    accessor.getActorMtx().getTranslation(pos);

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("団欒", &pack);
}

void EnemyWaitViewItem::changeToDejected() {
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(mTargetActor_d, &accessor);
    sead::Vector3f pos;
    accessor.getActorMtx().getTranslation(pos);

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("しょんぼり", &pack);
}

void EnemyWaitViewItem::changeToWatch() {
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(mTargetActor_d, &accessor);
    sead::Vector3f pos;
    accessor.getActorMtx().getTranslation(pos);

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("注視", &pack);
}

void EnemyWaitViewItem::changeToCheer() {
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(mTargetActor_d, &accessor);
    sead::Vector3f pos;
    accessor.getActorMtx().getTranslation(pos);

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("囃し立てる", &pack);
}

}  // namespace uking::ai
