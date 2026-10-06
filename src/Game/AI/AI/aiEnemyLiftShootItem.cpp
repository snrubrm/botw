#include "Game/AI/AI/aiEnemyLiftShootItem.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "Game/AI/aiUnk_71005D6D10.h"
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

// NON_MATCHING: only the stack slot assignment differs (the original overlaps the SafeString temporaries and the
// `target` copy with the InlineParamPack's slot at sp+0x28 and keeps `position` below it); logic, branches and calls match
// Child names: 持ち上げ (lift), 移動 (move), 回転 (turn), 投げつけ (throw).
void EnemyLiftShootItem::calc_() {
    if (!isCurrentChild("持ち上げ")) {
        const sead::Vector3f target = *mTargetPos_d;
        sub_71005DB1D8(mActor, target);
    } else {
        sub_71005DB3EC(mActor);
    }
    auto* child = getCurrentChild();
    if (!child->isFinished() && !child->isFailed()) {
        if (child->isChangeable() && isCurrentChild("移動")) {
            auto* connected = mActor->getConnectedCalcChild();
            if (!connected || (mActor->getConnectedCalcChild() &&
                               mActor->getConnectedCalcChild()->getState() !=
                                   ksys::act::BaseProc::State::Calc))
                setFailed();
            child->setDynamicParam(*mTargetPos_d, "TargetPos");
        }
    } else {
        bool throw_item = true;
        if (isCurrentChild("移動") || isCurrentChild("回転")) {
            if (child->isFailed()) {
                const sead::Vector3f position =
                    mActor->getMtx().getTranslation() + mActor->getMtx().getBase(2) * 3.0f;
                ksys::act::ai::InlineParamPack pack;
                pack.addVec3(position, "TargetPos", -1);
                changeChild("投げつけ", &pack);
                throw_item = false;
            }
        } else if (!isCurrentChild("持ち上げ")) {
            setFinished();
            throw_item = false;
        } else if (!child->isFinished()) {
            setFailed();
            throw_item = false;
        }
        if (throw_item)
            sub_7100397A64();
    }
    if (isCurrentChild("投げつけ"))
        child->setDynamicParam(*mTargetPos_d, "TargetPos");
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
