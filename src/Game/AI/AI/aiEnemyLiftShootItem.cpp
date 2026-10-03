#include "Game/AI/AI/aiEnemyLiftShootItem.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

EnemyLiftShootItem::EnemyLiftShootItem(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

bool EnemyLiftShootItem::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnemyLiftShootItem::enter_(ksys::act::ai::InlineParamPack* params) {
    changeToLift();
}

void EnemyLiftShootItem::changeToLift() {
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(mShootItem_d, &accessor);
    sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x8000001), mActor);
    ksys::act::ai::InlineParamPack pack;
    pack.addActor(*mShootItem_d, "TargetActor", -1);
    pack.addVec3(sub_7100397DB4(), "TargetPos", -1);
    changeChild("持ち上げ", &pack);
}

// NON_MATCHING: the original loads `ez` (as three floats, before the matrix copy ends) and multiplies with the
// vector operand first (`ez.x * m00`); ours loads it after the accessor setup and multiplies `m00 * ez.x`
sead::Vector3f EnemyLiftShootItem::sub_7100397DB4() {
    const sead::Vector3f ez = sead::Vector3f::ez;
    const sead::Matrix34f mtx = mActor->getMtx();
    ksys::act::ActorConstDataAccess accessor;
    if (ksys::act::acquireActor(mShootItem_d, &accessor))
        return accessor.getPreviousPos();
    return mtx * ez;
}

void EnemyLiftShootItem::leave_() {
    if (mActor->getConnectedCalcChild())
        mActor->resetConnectedCalcChild(false);
}

void EnemyLiftShootItem::loadParams_() {
    getStaticParam(&mShootAngle_s, "ShootAngle");
    getStaticParam(&mShootDist_s, "ShootDist");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mShootItem_d, "ShootItem");
}

}  // namespace uking::ai
