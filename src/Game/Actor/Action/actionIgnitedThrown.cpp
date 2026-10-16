#include "Game/Actor/Action/actionIgnitedThrown.h"
#include <algorithm>
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "Game/Actor/aiXlinkHandle.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actBaseProcAccessor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/aiRootAi.h"
#include "KingSystem/System/VFR.h"
#include "KingSystem/ActorSystem/actActorUnk6b8.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include "KingSystem/XLink/xlinkXLink.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actUnk_7100e4e084.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectAttack.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectLiftable.h"

namespace uking::action {

IgnitedThrown::IgnitedThrown(const InitArg& arg) : ksys::act::ai::Action(arg) {}

IgnitedThrown::~IgnitedThrown() = default;

bool IgnitedThrown::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void IgnitedThrown::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
    _70 = true;
    if (*mAS_s.getStringTop() != sead::SafeString::cNullChar)
        playAS(mAS_s.cstr(), true, 0, 0, -1.0f);
    auto* actor = mActor;
    actor->mDrawDistanceFlags.set(1);
    if (auto* body = actor->getMainBody())
        body->changeMotionType(ksys::phys::MotionType::Dynamic);
    const auto* attack = actor->getParam()->getRes().mGParamList->getAttack();
    const f32 power = attack->mPower.ref() * *mDamageScale_s;
    const ksys::res::GParamListObjectLiftable* liftable = nullptr;
    if (const auto* param = actor->getParam()) {
        if (const auto* gparams = param->getRes().mGParamList)
            liftable = gparams->getLiftable();
    }
    s32 level;
    if (!liftable) {
        level = *mReactionLevel_s;
        if (level < 0) {
            const s32 ipower = static_cast<s32>(power);
            level = ipower < -2 ? 0 : std::min((ipower - 1) / 4, 2);
        }
    } else if (liftable->mThrowReactionLevel.ref() < 0) {
        const s32 ipower = static_cast<s32>(power);
        level = ipower < -2 ? 0 : std::min((ipower - 1) / 4, 2);
    } else {
        level = *mReactionLevel_s;
    }
    sub_71005DBC94(actor, static_cast<s32>(power), level, *mIsAbleGuard_s, false,
                   *mIsForceOnly_s, false);
    if (auto* chemical = actor->getChemicalStuff()) {
        _72 = (chemical->_c >> 6) & 1;
        chemical->sub_7100D91098(true);
    }
    auto* unk = mActor->m100();
    _71 = false;
    if (!unk || !unk->sub_7100E50390(mActor)) {
        auto* parent_maybe = mActor->getConnectedCalcParent();
        if (!parent_maybe) {
            if (actor->getCreateArgBaseProcLink().hasProc())
                sub_7100738CB0(actor, &actor->getCreateArgBaseProcLink());
        } else {
            auto* parent = mActor->getConnectedCalcParent();
            sub_7100738C88(actor,
                           sead::IsDerivedFrom<ksys::act::Actor>(parent) ?
                               static_cast<ksys::act::Actor*>(parent) :
                               nullptr);
        }
    }
    _71 = true;
    _74.reset(10.0f);
    if (*mIsScaling_s && mActor->getRootAi()->getI() != 5)
        mActor->mScale.set(0.2f, 0.2f, 0.2f);
    if (!*mIsFadeIn_s)
        mActor->clearFadeInCreate();
    _9e = false;
    if (unk) {
        ksys::act::ActorLinkConstDataAccess accessor;
        if (unk->sub_7100E50334(&accessor) && accessor.hasTag(0x5f20e8b5u))  // EnemyOctarock
            _9e = true;
    }
    _90 = sead::Vector3f::zero;
    _9c = false;
    _9d = true;
}

void IgnitedThrown::leave_() {
    auto* actor = mActor;
    sub_71005DC02C(actor);
    if (auto* chemical = actor->getChemicalStuff())
        chemical->sub_7100D91098(_72);
    if (_71)
        sub_7100738DC8(actor);
    xlink::fade(_80, -1);
}

void IgnitedThrown::loadParams_() {
    getStaticParam(&mReactionLevel_s, "ReactionLevel");
    getStaticParam(&mDamageScale_s, "DamageScale");
    getStaticParam(&mFinishWaterDepth_s, "FinishWaterDepth");
    getStaticParam(&mIsScaling_s, "IsScaling");
    getStaticParam(&mIsFinishedByOneHit_s, "IsFinishedByOneHit");
    getStaticParam(&mIsFadeIn_s, "IsFadeIn");
    getStaticParam(&mIsAbleGuard_s, "IsAbleGuard");
    getStaticParam(&mIsForceOnly_s, "IsForceOnly");
    getStaticParam(&mAS_s, "AS");
}

// NON_MATCHING: stack slots of the three core id temporaries (VFR delta lookups) are permuted.
void IgnitedThrown::calc_() {
    if (_70) {
        _70 = false;
    } else if (*mIsScaling_s) {
        auto* actor = mActor;
        ksys::VFR::chase(&actor->mScale.x, 1.0f, 0.2f);
        ksys::VFR::chase(&actor->mScale.y, 1.0f, 0.2f);
        ksys::VFR::chase(&actor->mScale.z, 1.0f, 0.2f);
    }
    if (_71) {
        if (_74.value > sead::Mathf::epsilon())
            _74.update();
        else
            sub_7100738DC8(mActor);
    }
    sub_71001B5C4C();
}

// NON_MATCHING: the original keeps &_9d in a register (x23) across the property update.
// Octarock balloons: drives the xlink velocity property and the "Thrown" sound (faded while _6b8->_8f >= 1,
// emitted again afterwards). A velocity component that changed sign by at least 0.2 counts as a bounce.
void IgnitedThrown::sub_71001B5C4C() {
    if (!_9e)
        return;
    auto* actor = mActor;
    if (!actor->mXLink)
        return;
    auto* user = actor->mXLink->_50;
    if (!user)
        return;

    const auto& velocity = actor->mVelocity;
    bool bounced = false;
    for (int i = 0; i < 3; ++i) {
        const f32 sign = velocity.e[i] >= 0.0f ? 1.0f : -1.0f;
        const f32 prev_sign = _90.e[i] >= 0.0f ? 1.0f : -1.0f;
        if (sign != prev_sign && sead::Mathf::abs(velocity.e[i] - _90.e[i]) >= 0.2f) {
            bounced = true;
            break;
        }
    }
    if (!bounced || _9d)
        user->setPropertyValue(3, velocity.y);

    auto* unk = mActor->_6b8;
    if (unk && unk->_8f >= 1) {
        xlink::fade(_80, -1);
        _9c = true;
    } else {
        if (_9c || _9d)
            _80 = ksys::eft::searchAndEmitSLink(mActor, "Thrown", false);
        _9c = false;
    }
    _90 = actor->mVelocity;
    _9d = false;
}

bool IgnitedThrown::isFinished() const {
    if (ksys::act::ai::Action::isFinished())
        return true;
    if (_70)
        return false;
    auto* actor = mActor;
    if (isLandedMaybe(actor, false) || isBgGroundHit(actor, false))
        return true;
    if (*mIsFinishedByOneHit_s && sub_71007A4178(mActor, false))
        return true;
    if (*mFinishWaterDepth_s >= 0.0f) {
        f32 depth;
        if (mActor->get68f()) {
            const f32 y = mActor->getMtx().m[1][3];
            depth = mActor->get6f0() - y;
        } else {
            depth = 0.0f;
        }
        return depth >= *mFinishWaterDepth_s;
    }
    return false;
}

}  // namespace uking::action
