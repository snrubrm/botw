#include "Game/Actor/AI/aiSiteBossShootArrowRoot.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "Game/Actor/actSiteBoss.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"

bool sub_71002D2B5C(bool* side, ksys::act::Actor* actor, const gsys::BoneAccessKeyEx& key,
                  f32 angle, f32 scale);

namespace uking::ai {

// 0x7100585f94
bool SiteBossShootArrowRoot::sub_7100585F94() {
    if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor)) {
        if (!boss->_1558.isOnBit(8) || boss->_1560.sub_710066C074() == *mChildDeviceMax_s)
            return false;
    }
    if (_122)
        return sub_7100586218(*mChildDeviceSupplyNum_s);
    const bool created = sub_7100586218(*mChildDeviceMax_s);
    _122 = true;
    return created;
}

// NON_MATCHING: initial cast select and loop counter registers.
bool SiteBossShootArrowRoot::sub_7100586218(s32 count) {
    auto* boss = sead::DynamicCast<act::SiteBoss>(mActor);
    if (!boss || count == 0 || *mChildDeviceMax_s == 0)
        return false;
    sead::BitFlag32 create_flags;
    u32 index = 0;
    do {
        auto& link = boss->_1560._1e0[index];
        bool create = !sead::IsDerivedFrom<ksys::act::Actor>(link.getProc(nullptr, nullptr));
        if (!create) {
            auto* actor = sead::DynamicCast<ksys::act::Actor>(link.getProc(nullptr, nullptr));
            // The native repeats this runtime type query before checking the actor state.
            create = sead::IsDerivedFrom<ksys::act::Actor>(actor) && actor->isSleep();
        }
        if (create) {
            create_flags.setBit(index);
            --count;
        }
        ++index;
    } while (count != 0 && index < u32(*mChildDeviceMax_s));
    if (create_flags.isZero())
        return false;
    ksys::act::ai::InlineParamPack params;
    params.addBool(create_flags.isOnBit(0), "IsCreateA", -1);
    params.addBool(create_flags.isOnBit(1), "IsCreateB", -1);
    params.addBool(create_flags.isOnBit(2), "IsCreateC", -1);
    params.addBool(create_flags.isOnBit(3), "IsCreateD", -1);
    changeChild("子機生成", &params);
    return true;
}

const sead::SafeArray<s32, 8> sUnk_7101e7abb4[12] = {
    {{50, 0, 0, 0, 0, 50, 0, 0}},     {{100, 0, 0, 0, 0, 0, 0, 0}},
    {{50, 0, 0, 0, 0, 50, 0, 0}},     {{100, 0, 0, 0, 0, 0, 0, 0}},
    {{0, 20, 35, 10, 10, 25, 0, 0}},  {{0, 35, 35, 20, 10, 0, 0, 0}},
    {{50, 0, 0, 0, 0, 50, 0, 0}},     {{100, 0, 0, 0, 0, 0, 0, 0}},
    {{0, 15, 25, 15, 15, 10, 20, 0}}, {{0, 20, 35, 10, 10, 0, 25, 0}},
    {{33, 0, 0, 0, 0, 33, 34, 0}},    {{50, 0, 0, 0, 0, 0, 50, 0}},
};

SiteBossShootArrowRoot::SiteBossShootArrowRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SiteBossShootArrowRoot::~SiteBossShootArrowRoot() = default;

bool SiteBossShootArrowRoot::init_(sead::Heap* heap) {
    if (mActor->getModel())
        _128.search(mActor->getModel(), "Head");
    else
        _128.getKey().reset();
    _122 = false;
    for (int i = 0; i < 12; ++i) {
        for (int j = 0; j < 8; ++j)
            _160[i][j] = sUnk_7101e7abb4[i][j];
    }
    return true;
}

void SiteBossShootArrowRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    if (_11c != 0) {
        sub_7100584940(false);
        --_11c;
    } else {
        sub_7100584940(true);
        _11c = *mChildDeviceSupplyInterval_s;
    }
    _120 = false;
    _121 = false;

    if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor)) {
        boss->_1530 = 0;
        for (int i = 0; i < 24; ++i) {
            auto* link = boss->_1560.sub_710066DE24(i);
            if (link->hasProcInCalcState()) {
                ksys::act::ActorLinkConstDataAccess accessor;
                ksys::act::acquireActor(link, &accessor);
                accessor.sleep(ksys::act::BaseProc::SleepWakeReason::_0);
            }
        }
    }

    _110 = ksys::Timer(0, 0);
}

// NON_MATCHING: avoidance predicate argument load order.
void SiteBossShootArrowRoot::calc_() {
    auto* boss = sead::DynamicCast<act::SiteBoss>(mActor);
    if (!boss)
        return;
    boss->_1558.resetBit(3);
    const sead::Vector3f target = *mTargetPos_d;
    sub_71005DB0A8(mActor, target);
    auto* child = getCurrentChild();
    if (!child)
        return;
    child->setDynamicParam(target, "TargetPos");
    const bool cancel_attack = *mIsCancelAttack_d;
    child->setDynamicParam(cancel_attack, "IsCancelAttack");
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("子機生成")) {
            sub_7100584940(false);
            ++_11c;
            return;
        }
        if (isCurrentChild("待機")) {
            setFinished();
            return;
        }
        if (isCurrentChild("回避")) {
            getCurrentChild()->setDynamicParam(target, "PlayerPos");
            ++boss->_1530;
            const f32 wait = *mAvoidWaitCount_s;
            const f32 wait_range = *mAvoidWaitCountRand_s;
            const f32 time = wait + wait_range * sead::GlobalRandom::instance()->getF32();
            _110 = ksys::Timer(time, time);
            sub_71005857EC(false);
            return;
        }
        if (isCurrentChild(mNoWaitWarpAttackKey_s.cstr()))
            setFinished();
        else
            sub_71005857EC(true);
    } else if (isCurrentChild("待機")) {
        _110.update();
        if (_110.value <= sead::Mathf::epsilon() &&
            static_cast<act::SiteBoss*>(mActor)->sub_71002D2AE0(*mAvoidLifeRate_s, boss->_1530,
                                                             *mAvoidCountMax_s) &&
            !boss->sub_71002D33D0(20.0f) && boss->sub_71002D33D0(120.0f)) {
            bool side = false;
            if (sub_71002D2B5C(&side, mActor, _128, *mAvoidAngle_s, 1.2f))
                sub_71005858E4(side);
        }
    }
}

void SiteBossShootArrowRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SiteBossShootArrowRoot::loadParams_() {
    getStaticParam(&mChildDeviceMax_s, "ChildDeviceMax");
    getStaticParam(&mChildDeviceSupplyNum_s, "ChildDeviceSupplyNum");
    getStaticParam(&mChildDeviceSupplyInterval_s, "ChildDeviceSupplyInterval");
    getStaticParam(&mAtMinDamage_s, "AtMinDamage");
    getStaticParam(&mArrowRainBaseDamage_s, "ArrowRainBaseDamage");
    getStaticParam(&mArrowRainAddDamage_s, "ArrowRainAddDamage");
    getStaticParam(&mAvoidCountMax_s, "AvoidCountMax");
    getStaticParam(&mSeqAvoidRate_s, "SeqAvoidRate");
    getStaticParam(&mUpDownAvoidRate_s, "UpDownAvoidRate");
    getStaticParam(&mPatternShiftFirstLifeRate_s, "PatternShiftFirstLifeRate");
    getStaticParam(&mPatternShiftSecondLifeRate_s, "PatternShiftSecondLifeRate");
    getStaticParam(&mPatternShiftThirdLifeRate_s, "PatternShiftThirdLifeRate");
    getStaticParam(&mCancelCreateTornadoHeight_s, "CancelCreateTornadoHeight");
    getStaticParam(&mAvoidAngle_s, "AvoidAngle");
    getStaticParam(&mAvoidLifeRate_s, "AvoidLifeRate");
    getStaticParam(&mAvoidDist_s, "AvoidDist");
    getStaticParam(&mAvoidDistRand_s, "AvoidDistRand");
    getStaticParam(&mAvoidWaitCount_s, "AvoidWaitCount");
    getStaticParam(&mAvoidWaitCountRand_s, "AvoidWaitCountRand");
    getStaticParam(&mTornadoCreateHeight_s, "TornadoCreateHeight");
    getStaticParam(&mNoWaitWarpAttackKey_s, "NoWaitWarpAttackKey");
    getStaticParam(&mChaseDist_s, "ChaseDist");
    getStaticParam(&mChaseDistOffset_s, "ChaseDistOffset");
    getDynamicParam(&mIsAttackPatternFixed_d, "IsAttackPatternFixed");
    getDynamicParam(&mIsCancelAttack_d, "IsCancelAttack");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

// NON_MATCHING: avoidance-vector stack slots and height-selection scheduling differ.
void SiteBossShootArrowRoot::sub_71005858E4(bool side) {
    if (_121)
        side = sead::GlobalRandom::instance()->getU32(100) < (_120 ? 20u : 60u);
    else
        _121 = true;
    _120 = side;
    const f32 distance = *mAvoidDist_s;
    const f32 distance_range = *mAvoidDistRand_s;
    const f32 avoid_distance = distance + distance_range * sead::GlobalRandom::instance()->getF32();
    bool slerp = false;
    const sead::Vector3f target = *mTargetPos_d;
    sead::Vector3f avoid;
    const bool horizon = sub_71002D2D9C(&avoid, &slerp, mActor, target, side, avoid_distance);
    const s32 roll = static_cast<s32>(sead::GlobalRandom::instance()->getF32() * 100.0f);
    const s32 rate = *mUpDownAvoidRate_s;
    if (roll < rate) {
        const f32 height = mActor->getMtx().getTranslation().y;
        sead::Vector3f home;
        mActor->getHomePos(&home);
        home += *mChaseDistOffset_s;
        const f32 upper = (home.y + mChaseDist_s->y) + mChaseDistOffset_s->y;
        const f32 lower = mChaseDistOffset_s->y + (home.y - mChaseDist_s->y);
        const s32 half_rate = static_cast<s32>(static_cast<f32>(rate) * 0.5f);
        const f32 scale = height < (upper + lower) * 0.5f ? 1.5f : 0.5f;
        const s32 threshold = static_cast<s32>(static_cast<f32>(half_rate) * scale);
        if (roll < threshold)
            avoid.y += upper >= height + mChaseDist_s->y ? 0.25f : -0.25f;
        else
            avoid.y += lower > height - mChaseDist_s->y ? 0.25f : -0.25f;
    }
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(target, "TargetPos", -1);
    pack.addVec3(target, "PlayerPos", -1);
    pack.addVec3(avoid, "AvoidVec", -1);
    pack.addBool(horizon, "IsAvoidHorizon", -1);
    pack.addFloat(avoid_distance, "AvoidDist", -1);
    pack.addBool(slerp, "IsSlerp", -1);
    changeChild("回避", &pack);
}

// 0x71005857ec
void SiteBossShootArrowRoot::sub_71005857EC(bool reset_end_time) {
    ksys::act::ai::InlineParamPack pack;
    pack.addBool(reset_end_time, "IsResetEndTime", -1);
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    changeChild("待機", &pack);
}

}  // namespace uking::ai
