#include "Game/AI/AI/aiSiteBossRecognizeRootBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actLastBoss.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"

namespace uking::ai {

bool sUnk_71025ba278 = false;

SiteBossRecognizeRootBase::SiteBossRecognizeRootBase(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SiteBossRecognizeRootBase::~SiteBossRecognizeRootBase() = default;

bool SiteBossRecognizeRootBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

// NON_MATCHING: the original computes the getU32 argument before loading the GlobalRandom instance
// (C++14 evaluation order)
void SiteBossRecognizeRootBase::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    if (!actor)
        return;

    _64 = 0;
    if (mAttackNum_s)
        _60 = *mAttackNum_s + sead::GlobalRandom::instance()->getU32(*mAttackRandNum_s + 1);
    else
        _60 = 1;

    if (!actor->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_2000000))
        sub_7100478B7C();
    else if (m35())
        m40();
    else
        siteBossStuff();

    actor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_2000000);
}

// NON_MATCHING: the original computes the getU32 argument before loading the GlobalRandom instance (same as
// enter_); everything else is instruction-identical
void SiteBossRecognizeRootBase::calc_() {
    auto* child = getCurrentChild();
    if (!child) {
        setFailed();
        return;
    }

    sead::Vector3f target_pos;
    if (auto* actor = mActor) {
        auto* link = sub_71005D9050(actor);
        target_pos = link && link->hasProc() && ksys::act::isPlayerProfile(link) ?
                         sub_71005D9330(actor) :
                         getPlayerPosition();
    }
    child->setDynamicParam(target_pos, "TargetPos");

    if (!child->isFinished() && !child->isFailed())
        return;

    if (isCurrentChild("戦闘")) {
        if (m36() || getCurrentChild()->isFailed())
            m40();
        else
            siteBossStuff();
    } else if (isCurrentChild("ワープ移動")) {
        if (!child->isFinished() && !child->isFailed())
            return;

        if ((mActor->getMtx().getTranslation() - target_pos).length() >= *mForceWarpRetryDist_s) {
            m40();
        } else {
            _64 = 0;
            _60 = *mAttackNum_s + sead::GlobalRandom::instance()->getU32(*mAttackRandNum_s + 1);
            siteBossStuff();
        }
    } else if (isCurrentChild("気付く")) {
        if ((mActor->getMtx().getTranslation() - target_pos).length() >= *mWarpStartDist_s)
            m40();
        else
            siteBossStuff();
    }
}

void SiteBossRecognizeRootBase::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SiteBossRecognizeRootBase::loadParams_() {
    getStaticParam(&mAttackNum_s, "AttackNum");
    getStaticParam(&mAttackRandNum_s, "AttackRandNum");
    getStaticParam(&mWarpStartDist_s, "WarpStartDist");
    getStaticParam(&mForceWarpRetryDist_s, "ForceWarpRetryDist");
    getDynamicParam(&mIsAttackPatternFixed_d, "IsAttackPatternFixed");
}

void SiteBossRecognizeRootBase::m34(bool on) {}

bool SiteBossRecognizeRootBase::m36() {
    if (*mAttackNum_s == 0)
        return false;
    return _64 >= _60;
}

void SiteBossRecognizeRootBase::m37() {
    // The original performs the cast and discards the result.
    sead::DynamicCast<act::LastBoss>(mActor);
    m34(false);
}

void SiteBossRecognizeRootBase::m38(ksys::act::ai::InlineParamPack* params) {
    sead::Vector3f pos;
    SiteBossRecognizeRootBase::m39(&pos);
    params->addVec3(pos, "TargetPos", -1);
    params->addBool(*mIsAttackPatternFixed_d, "IsAttackPatternFixed", -1);
}

void SiteBossRecognizeRootBase::m39(sead::Vector3f* pos) {
    auto* actor = mActor;
    if (!actor)
        return;

    auto* link = sub_71005D9050(actor);
    if (link && link->hasProc() && ksys::act::isPlayerProfile(link))
        *pos = sub_71005D9330(actor);
    else
        *pos = getPlayerPosition();
}

void SiteBossRecognizeRootBase::sub_7100478F78(sead::Vector3f* pos) {
    auto* actor = mActor;
    if (!actor)
        return;

    auto* link = sub_71005D9050(actor);
    if (link && link->hasProc() && ksys::act::isPlayerProfile(link))
        *pos = sub_71005D9330(actor);
    else
        *pos = getPlayerPosition();
}

void SiteBossRecognizeRootBase::siteBossStuff() {
    sead::DynamicCast<act::LastBoss>(mActor);
    ksys::act::ai::InlineParamPack params;
    m38(&params);
    ++_64;
    changeChild("戦闘", &params);
}

void SiteBossRecognizeRootBase::sub_7100478B7C() {
    ksys::act::ai::InlineParamPack params;
    sead::Vector3f target_pos;
    if (auto* actor = mActor) {
        auto* link = sub_71005D9050(actor);
        target_pos = link && link->hasProc() && ksys::act::isPlayerProfile(link) ?
                         sub_71005D9330(actor) :
                         getPlayerPosition();
    }
    params.addVec3(target_pos, "TargetPos", -1);
    changeChild("気付く", &params);
}

bool SiteBossRecognizeRootBase::m35() {
    if (!sub_710072B8E4())
        return false;
    const sead::Vector3f player_pos = getPlayerPosition();
    return (mActor->getMtx().getTranslation() - player_pos).length() >= *mWarpStartDist_s;
}

// NON_MATCHING: sUnk_71025ba278 is reached through the GOT here (the original addresses it directly:
// a TU-local object that is never written, yet not folded); getU32 argument order as in enter_
void SiteBossRecognizeRootBase::m40() {
    if (sUnk_71025ba278) {
        _64 = 0;
        _60 = *mAttackNum_s + sead::GlobalRandom::instance()->getU32(*mAttackRandNum_s + 1);
        siteBossStuff();
        return;
    }

    m37();
    ksys::act::ai::InlineParamPack params;
    sead::Vector3f target_pos;
    if (auto* actor = mActor) {
        auto* link = sub_71005D9050(actor);
        target_pos = link && link->hasProc() && ksys::act::isPlayerProfile(link) ?
                         sub_71005D9330(actor) :
                         getPlayerPosition();
    }
    params.addVec3(target_pos, "TargetPos", -1);
    params.addBool(false, "IsReturnHome", -1);
    params.addBool(false, "IsForceWarp", -1);
    params.addBool(false, "IsPartsActorTgOn", -1);
    changeChild("ワープ移動", &params);
}

// NON_MATCHING: sUnk_71025ba278 through the GOT (see m40)
bool SiteBossRecognizeRootBase::m41() {
    return sUnk_71025ba278;
}

}  // namespace uking::ai
