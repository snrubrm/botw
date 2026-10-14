#include "Game/AI/AI/aiEnemyFindShootable.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Resource/Actor/resResourceAttCheck.h"

namespace uking::ai {

EnemyFindShootable::EnemyFindShootable(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

bool EnemyFindShootable::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnemyFindShootable::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ActorLinkConstDataAccess acc;
    ksys::act::acquireActor(mParams.mTargetActor_d, &acc);
    acc.getActorMtx().getTranslation(_68);
    _74 = acc.sub_7100D10E6C(30);
    mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_2000000);
    mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_1000000);

    changeToApproach();
}

// NON_MATCHING: stack slots of the two accessors, the original passes a stack copy of _68 to sub_71005DB1D8, and
// the AttOffset matrix product is scheduled differently (as in LandHumEnemyUnarmedBattle::sub_7100470D54).
void EnemyFindShootable::calc_() {
    ksys::act::ActorLinkConstDataAccess target;
    ksys::act::acquireActor(mParams.mTargetActor_d, &target);
    target.getActorMtx().getTranslation(_68);
    _74 = target.sub_7100D10E6C(30);

    if (isCurrentChild("接近"))
        sub_71005DB1D8(mActor, _68);
    else
        sub_71005DB3EC(mActor);

    // Whether the target can be grabbed from the AttOffset point (its "Grab" attention check).
    const auto canGrab = [this] {
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(mParams.mTargetActor_d, &accessor);
        auto* actor = mActor;
        ksys::res::AttCheck_Unk1 arg;
        arg._0 = actor->getMtx();
        const auto& base_offset = *mParams.mAttOffset_s;
        const auto& scale = actor->getScale();
        const sead::Vector3f offset(base_offset.x * scale.x, base_offset.y * scale.y,
                                    base_offset.z * scale.z);
        sead::Vector3f position;
        position.setMul(actor->getMtx(), offset);
        arg._0.setTranslation(position);
        arg._36 = false;
        arg._35 = true;
        arg._34 = *mParams.mCanGrabHeavy_s;
        arg._30 = *mParams.mGrabCheckRadius_s;
        return accessor.sub_7100D13AE4("Grab", mActor, &arg, false);
    };

    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (!isCurrentChild("接近")) {
            setFinished();
            return;
        }
        if (canGrab())
            changeToAction();
        else
            setFailed();
    } else if (getCurrentChild()->isChangeable() && isCurrentChild("接近")) {
        if (!mParams.mTargetActor_d->hasProc() || _74 ||
            sub_71005DEC08(mParams.mTargetActor_d, mActor, *mParams.mChaseItemDist_s,
                           *mParams.mChaseItemSpeed_s, sead::Mathf::piHalf())) {
            setFailed();
            return;
        }
        if (canGrab())
            changeToAction();
    }

    const bool approaching = isCurrentChild("接近");
    getCurrentChild()->setDynamicParam(approaching ? _68 : sub_71005D9330(mActor), "TargetPos");
}

void EnemyFindShootable::leave_() {
    if (mActor->getConnectedCalcChild())
        mActor->resetConnectedCalcChild(false);
    sub_71005DB3EC(mActor);
}

void EnemyFindShootable::loadParams_() {
    getDynamicParam(&mParams.mTargetActor_d, "TargetActor");
    getStaticParam(&mParams.mAttOffset_s, "AttOffset");
    getStaticParam(&mParams.mCanGrabHeavy_s, "CanGrabHeavy");
    getStaticParam(&mParams.mGrabCheckRadius_s, "GrabCheckRadius");
    getStaticParam(&mParams.mChaseItemDist_s, "ChaseItemDist");
    getStaticParam(&mParams.mChaseItemSpeed_s, "ChaseItemSpeed");
}

void EnemyFindShootable::changeToAction() {
    ksys::act::ai::InlineParamPack pack;
    pack.addActor(*mParams.mTargetActor_d, "ShootItem", -1);
    pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    changeChild("アクション", &pack);
}

}  // namespace uking::ai
