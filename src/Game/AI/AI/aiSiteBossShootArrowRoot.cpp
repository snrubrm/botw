#include "Game/AI/AI/aiSiteBossShootArrowRoot.h"
#include "Game/Actor/actSiteBoss.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"

namespace uking::ai {

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
                ksys::act::ActorConstDataAccess accessor;
                ksys::act::acquireActor(link, &accessor);
                accessor.sleep(ksys::act::BaseProc::SleepWakeReason::_0);
            }
        }
    }

    _110 = ksys::Timer(0, 0);
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

}  // namespace uking::ai
