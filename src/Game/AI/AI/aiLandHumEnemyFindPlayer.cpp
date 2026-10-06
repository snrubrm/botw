#include "Game/AI/AI/aiLandHumEnemyFindPlayer.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "Game/Damage/dmgInfoManager.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"

namespace uking::ai {

LandHumEnemyFindPlayer::LandHumEnemyFindPlayer(const InitArg& arg) : EnemyBaseFindPlayer(arg) {}

LandHumEnemyFindPlayer::~LandHumEnemyFindPlayer() = default;

void LandHumEnemyFindPlayer::enter_(ksys::act::ai::InlineParamPack* params) {
    _1e0 = false;
    if (mActor->get68f().load() || sub_71005D91A0(mActor, *mParams.mNoBurnWaterDepth_s))
        _1d8 = 1.0f;
    else
        _1d8 = 0.0f;
    _1e1 = sub_71005DA5AC(mActor, m53());
    if (!sub_710046096C()) {
        EnemyBaseFindPlayer::enter_(params);
        return;
    }

    const bool is_enemy = ksys::act::isEnemyProfile(&_1c8);
    sub_710037E9A4();
    if (is_enemy)
        changeToSummonChemicalAllies();
    else
        changeToApplyWeaponChemical();
}

void LandHumEnemyFindPlayer::getChemTargetPos(sead::Vector3f* pos) {
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&_1c8, &accessor);
    sead::Matrix34f mtx;
    accessor.sub_7100D11188(&mtx);
    pos->x = mtx.m[0][3];
    pos->y = mtx.m[1][3];
    pos->z = mtx.m[2][3];
}

void LandHumEnemyFindPlayer::changeToSummonChemicalAllies() {
    sead::Vector3f pos;
    getChemTargetPos(&pos);
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(pos, "TargetPos", -1);
    pack.addActor(_1c8, "TargetActor", -1);
    changeChild("ケミカル仲間招来", &pack);
}

void LandHumEnemyFindPlayer::changeToApplyWeaponChemical() {
    sead::Vector3f pos;
    getChemTargetPos(&pos);
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(pos, "TargetPos", -1);
    pack.addActor(_1c8, "TargetActor", -1);
    changeChild("武器ケミカル付与", &pack);
}

void LandHumEnemyFindPlayer::m44() {
    auto* child = getCurrentChild();
    if (isCurrentChild("ケミカル仲間招来") || isCurrentChild("武器ケミカル付与")) {
        sead::Vector3f pos;
        getChemTargetPos(&pos);
        child->setDynamicParam(pos, "TargetPos");
    } else {
        EnemyBaseFindPlayer::m44();
    }
}

void LandHumEnemyFindPlayer::leave_() {
    EnemyBaseFindPlayer::leave_();
    dmg::DamageInfoMgr::instance()->get4f8().sub_71006720C8(mActor);
}

void LandHumEnemyFindPlayer::loadParams_() {
    EnemyBaseFindPlayer::loadParams_();
    getStaticParam(&mParams.mExplosivesAvoidDist_s, "ExplosivesAvoidDist");
    getStaticParam(&mParams.mExplosivesAvoidSpeed_s, "ExplosivesAvoidSpeed");
    getStaticParam(&mParams.mExplosivesAvoidAng_s, "ExplosivesAvoidAng");
    getStaticParam(&mParams.mChemicalSearchDist_s, "ChemicalSearchDist");
    getStaticParam(&mParams.mNoSearchDist_s, "NoSearchDist");
    getStaticParam(&mParams.mVoltage_s, "Voltage");
    getStaticParam(&mParams.mChemicalActionDist_s, "ChemicalActionDist");
    getStaticParam(&mParams.mThrowWeaponPer_s, "ThrowWeaponPer");
    getStaticParam(&mParams.mThrowWeaponDist_s, "ThrowWeaponDist");
    getStaticParam(&mParams.mNoChemSearchWpIdx_s, "NoChemSearchWpIdx");
    getStaticParam(&mParams.mNoBurnWaterDepth_s, "NoBurnWaterDepth");
    getStaticParam(&mParams.mNearScaffoldDist_s, "NearScaffoldDist");
    getStaticParam(&mParams.mClimbVmin_s, "ClimbVmin");
    getStaticParam(&mParams.mClimbVmax_s, "ClimbVmax");
    getStaticParam(&mParams.mClimbHmax_s, "ClimbHmax");
}

bool LandHumEnemyFindPlayer::m43() {
    if (*mParams.mNearScaffoldDist_s > 0.0f && sub_71005D9744(mActor) == 3)
        return false;
    return EnemyBaseFindPlayer::m43();
}

// NON_MATCHING: the original ends with `if (dist <= Hmax) return true; return false;` as two
// branches (one dtor call shared); ours folds the compare into a cset
bool LandHumEnemyFindPlayer::sub_7100461B74() {
    if (*mParams.mClimbHmax_s < 0)
        return false;
    auto& link = sub_71005D94AC(mActor);
    if (!link.hasProc() || !ksys::act::isPlayerProfile(&link))
        return false;
    ksys::act::acc::PlayerBase player;
    ksys::act::acquireActor(&link, &player);
    if (!player.m186() && !player.m187())
        return false;
    const sead::Vector3f diff =
        player.getActorMtx().getTranslation() - mActor->getMtx().getTranslation();
    if (diff.y < *mParams.mClimbVmin_s || diff.y > *mParams.mClimbVmax_s)
        return false;
    if (sead::Mathf::sqrt(diff.x * diff.x + diff.z * diff.z) <= *mParams.mClimbHmax_s)
        return true;
    return false;
}

void LandHumEnemyFindPlayer::changeToGrabTargetWall() {
    _1dc = 15.0f;
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    changeChild("対象壁つかまり", &pack);
}

bool LandHumEnemyFindPlayer::sub_7100461D74() {
    if (!_1c8.hasProcInCalcState())
        return false;
    const bool a = sub_71005DA434(mActor, m53()) && !sub_71005DA434(mActor, *mParams.mNoChemSearchWpIdx_s);
    const bool b = sub_71005DA4F0(mActor, m53()) && !sub_71005DA4F0(mActor, *mParams.mNoChemSearchWpIdx_s);
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&_1c8, &accessor);
    if ((a && accessor.sub_7100D13448(-1)) ||
        (b && !(accessor.sub_7100D13080() < *mParams.mVoltage_s)))
        return true;
    return false;
}

void LandHumEnemyFindPlayer::m40() {
    if (sub_7100462A28()) {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
        changeChild("武器投げ", &pack);
    } else {
        EnemyBaseFindPlayer::m40();
    }
}

// m48 / m49 / m50 / m52 have identical bodies in the original (m51 adds the m38 tail).
bool LandHumEnemyFindPlayer::m48() {
    if (!(*mParams.mNearScaffoldDist_s <= 0)) {
        auto* actor = mActor;
        if (sub_71005D9744(actor) == 3) {
            const sead::Vector3f target = sub_71005D9330(actor);
            const sead::Vector3f diff = target - actor->getMtx().getTranslation();
            if (sead::Mathf::sqrt(diff.x * diff.x + diff.z * diff.z) <= *mParams.mNearScaffoldDist_s) {
                ksys::act::ai::InlineParamPack pack;
                pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
                changeChild("対象見張り台", &pack);
                return true;
            }
        }
    }
    if (sub_7100461B74()) {
        changeToGrabTargetWall();
        return true;
    }
    return false;
}

bool LandHumEnemyFindPlayer::m49() {
    if (!(*mParams.mNearScaffoldDist_s <= 0)) {
        auto* actor = mActor;
        if (sub_71005D9744(actor) == 3) {
            const sead::Vector3f target = sub_71005D9330(actor);
            const sead::Vector3f diff = target - actor->getMtx().getTranslation();
            if (sead::Mathf::sqrt(diff.x * diff.x + diff.z * diff.z) <= *mParams.mNearScaffoldDist_s) {
                ksys::act::ai::InlineParamPack pack;
                pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
                changeChild("対象見張り台", &pack);
                return true;
            }
        }
    }
    if (sub_7100461B74()) {
        changeToGrabTargetWall();
        return true;
    }
    return false;
}

bool LandHumEnemyFindPlayer::m50() {
    if (!(*mParams.mNearScaffoldDist_s <= 0)) {
        auto* actor = mActor;
        if (sub_71005D9744(actor) == 3) {
            const sead::Vector3f target = sub_71005D9330(actor);
            const sead::Vector3f diff = target - actor->getMtx().getTranslation();
            if (sead::Mathf::sqrt(diff.x * diff.x + diff.z * diff.z) <= *mParams.mNearScaffoldDist_s) {
                ksys::act::ai::InlineParamPack pack;
                pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
                changeChild("対象見張り台", &pack);
                return true;
            }
        }
    }
    if (sub_7100461B74()) {
        changeToGrabTargetWall();
        return true;
    }
    return false;
}

bool LandHumEnemyFindPlayer::m51() {
    if (!(*mParams.mNearScaffoldDist_s <= 0)) {
        auto* actor = mActor;
        if (sub_71005D9744(actor) == 3) {
            const sead::Vector3f target = sub_71005D9330(actor);
            const sead::Vector3f diff = target - actor->getMtx().getTranslation();
            if (sead::Mathf::sqrt(diff.x * diff.x + diff.z * diff.z) <= *mParams.mNearScaffoldDist_s) {
                ksys::act::ai::InlineParamPack pack;
                pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
                changeChild("対象見張り台", &pack);
                return true;
            }
        }
    }
    if (sub_7100461B74()) {
        changeToGrabTargetWall();
        return true;
    }
    if (m38()) {
        changeToNoNavMesh();
        return true;
    }
    return false;
}

bool LandHumEnemyFindPlayer::m52() {
    if (!(*mParams.mNearScaffoldDist_s <= 0)) {
        auto* actor = mActor;
        if (sub_71005D9744(actor) == 3) {
            const sead::Vector3f target = sub_71005D9330(actor);
            const sead::Vector3f diff = target - actor->getMtx().getTranslation();
            if (sead::Mathf::sqrt(diff.x * diff.x + diff.z * diff.z) <= *mParams.mNearScaffoldDist_s) {
                ksys::act::ai::InlineParamPack pack;
                pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
                changeChild("対象見張り台", &pack);
                return true;
            }
        }
    }
    if (sub_7100461B74()) {
        changeToGrabTargetWall();
        return true;
    }
    return false;
}

}  // namespace uking::ai
