#include "Game/Actor/AI/aiSiteBossRecognizeRoot.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "Game/Actor/actSiteBoss.h"
#include "KingSystem/ActorSystem/aiRootAi.h"

bool sub_71002D17D4(ksys::act::Actor* actor, const sead::Vector3f* home,
                  const sead::Vector3f* target, const sead::Vector3f* distance,
                  const sead::Vector3f* offset, bool special);

namespace uking::ai {

// 0x710058196c
bool SiteBossRecognizeRoot::sub_710058196C() {
    sead::Vector3f target;
    sub_7100478F78(&target);
    sead::Vector3f home;
    bool special = false;
    if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor)) {
        home = boss->_2318;
        special = (boss->_1534 & ~3) == 4;
    } else {
        mActor->getHomePos(&home);
    }
    return sub_71002D17D4(mActor, &home, &target, mChaseDist_s, mChaseDistOffset_s, special);
}

SiteBossRecognizeRoot::SiteBossRecognizeRoot(const InitArg& arg) : LastBossRecognizeRoot(arg) {}

SiteBossRecognizeRoot::~SiteBossRecognizeRoot() = default;

bool SiteBossRecognizeRoot::init_(sead::Heap* heap) {
    return LastBossRecognizeRoot::init_(heap);
}

void SiteBossRecognizeRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* boss = sead::DynamicCast<act::SiteBoss>(mActor);
    if (boss && boss->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_2000000) &&
        boss->_1558.isOnBit(15)) {
        m40();
        return;
    }
    LastBossRecognizeRoot::enter_(params);
}

void SiteBossRecognizeRoot::leave_() {
    LastBossRecognizeRoot::leave_();
}

void SiteBossRecognizeRoot::loadParams_() {
    LastBossRecognizeRoot::loadParams_();
    getStaticParam(&mIgnoreWaprDistMax_s, "IgnoreWaprDistMax");
    getStaticParam(&mIsCheckChildDevice_s, "IsCheckChildDevice");
    getStaticParam(&mIgnoreWarpDistRetFromDamage_s, "IgnoreWarpDistRetFromDamage");
    getStaticParam(&mChaseDist_s, "ChaseDist");
    getStaticParam(&mChaseDistOffset_s, "ChaseDistOffset");
}

void SiteBossRecognizeRoot::m34(bool on) {
    if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor))
        boss->_14c8._30.setDirect(on ? (boss->_14c8._30.getDirect() | 0x40) :
                                     (boss->_14c8._30.getDirect() & ~0x40));
}

bool SiteBossRecognizeRoot::m35() {
    bool ret = LastBossRecognizeRoot::m35();
    if (testRootAiFlag2(ksys::act::ai::RootAiFlag2::_0)) {
        if (++_94 < *mIgnoreWaprDistMax_s)
            return false;
    }
    return ret;
}

// NON_MATCHING: the original tests kind - 1 in {0, 4, 8} and kind in {0, 4, 8} separately (two
// bit tests) and keeps the "ret = false" branch
bool SiteBossRecognizeRoot::m36() {
    bool ret = LastBossRecognizeRoot::m36();
    if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor)) {
        const s32 kind = boss->_1534;
        if ((kind == 1 || kind == 5 || kind == 9 || kind == 0 || kind == 4 || kind == 8) &&
            boss->_1558.isOnBit(3)) {
            ret = false;
        }
    }
    return ret;
}

// NON_MATCHING: parameter and vector stack slots, flag reloads and child selection branches.
void SiteBossRecognizeRoot::m40() {
    if (m41()) {
        siteBossStuff();
        return;
    }
    _94 = 0;
    m37();
    ksys::act::ai::InlineParamPack params;
    sead::Vector3f target;
    sub_7100478F78(&target);
    params.addVec3(target, "TargetPos", -1);
    params.addVec3(*mChaseDist_s, "ChaseDist", -1);
    const bool within_range = sub_710058196C();
    params.addBool(!act::SiteBoss::sub_71002D3804(mActor, "WearFlame"), "IsPartsActorTgOn", -1);
    sead::Vector3f position;
    mActor->getMtx().getTranslation(position);
    auto* boss = sead::DynamicCast<act::SiteBoss>(mActor);
    sead::Vector3f home;
    bool return_home = !within_range;
    bool special = false;
    bool sync_effect = false;
    if (boss) {
        if (!within_range) {
            boss->_1558.setBit(15);
            if (boss->_1558.isOnBit(8))
                boss->_1558.setBit(17);
        } else {
            if (boss->_1558.isOnBit(15)) {
                if (boss->_1540) {
                    boss->_2390.sub_7100723418(30.0f);
                    boss->_1540 = 0;
                } else {
                    boss->_2390._8 = true;
                }
                return_home = true;
            }
            boss->_1558.resetBit(15);
            if (boss->_1558.isOnBit(8))
                boss->_1558.resetBit(17);
        }
        home = boss->_2318;
        special = (boss->_1534 & ~3) == 4;
        sync_effect = boss->_1558.isOnBit(17);
    } else {
        mActor->getHomePos(&home);
    }
    params.addBool(return_home, "IsReturnHome", -1);
    const bool fits = sub_71002D17D4(mActor, &home, &position, mChaseDist_s, mChaseDistOffset_s,
                                    special);
    params.addBool(false, "IsForceWarp", -1);
    params.addBool(sync_effect, "IsPartsWarpEffectSync", -1);
    const char* child;
    if (within_range && fits) {
        child = "ワープ移動";
    } else if (within_range) {
        child = "自身範囲外ワープ";
    } else {
        if (boss)
            boss->_2390._8 = false;
        child = "プレイヤー範囲外ワープ";
    }
    changeChild(child, &params);
}

void SiteBossRecognizeRoot::m38(ksys::act::ai::InlineParamPack* params) {
    LastBossRecognizeRoot::m38(params);
    params->addBool(false, "IsCancelAttack", -1);
}

}  // namespace uking::ai
