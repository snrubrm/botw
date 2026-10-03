#include "Game/AI/AI/aiSiteBossRecognizeRoot.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "Game/Actor/actSiteBoss.h"
#include "KingSystem/ActorSystem/actAiRoot.h"

namespace uking::ai {

SiteBossRecognizeRoot::SiteBossRecognizeRoot(const InitArg& arg) : SiteBossRecognizeRootBase(arg) {}

SiteBossRecognizeRoot::~SiteBossRecognizeRoot() = default;

bool SiteBossRecognizeRoot::init_(sead::Heap* heap) {
    return SiteBossRecognizeRootBase::init_(heap);
}

void SiteBossRecognizeRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* boss = sead::DynamicCast<act::SiteBoss>(mActor);
    if (boss && boss->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_2000000) &&
        boss->_1558.isOnBit(15)) {
        m40();
        return;
    }
    SiteBossRecognizeRootBase::enter_(params);
}

void SiteBossRecognizeRoot::leave_() {
    SiteBossRecognizeRootBase::leave_();
}

void SiteBossRecognizeRoot::loadParams_() {
    SiteBossRecognizeRootBase::loadParams_();
    getStaticParam(&mIgnoreWaprDistMax_s, "IgnoreWaprDistMax");
    getStaticParam(&mIsCheckChildDevice_s, "IsCheckChildDevice");
    getStaticParam(&mIgnoreWarpDistRetFromDamage_s, "IgnoreWarpDistRetFromDamage");
    getStaticParam(&mChaseDist_s, "ChaseDist");
    getStaticParam(&mChaseDistOffset_s, "ChaseDistOffset");
}

// NON_MATCHING: the original computes both values and uses csel; we branch
void SiteBossRecognizeRoot::m34(bool on) {
    if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor))
        boss->_14c8._30.change(0x40, on);
}

// NON_MATCHING: the original keeps the "ret = false" branch; we get cset + and
bool SiteBossRecognizeRoot::m35() {
    bool ret = SiteBossRecognizeRootBase::m35();
    if (testRootAiFlag2(ksys::act::ai::RootAiFlag2::_0)) {
        if (++_94 < *mIgnoreWaprDistMax_s)
            ret = false;
    }
    return ret;
}

// NON_MATCHING: the original tests kind - 1 in {0, 4, 8} and kind in {0, 4, 8} separately (two
// bit tests) and keeps the "ret = false" branch
bool SiteBossRecognizeRoot::m36() {
    bool ret = SiteBossRecognizeRootBase::m36();
    if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor)) {
        const s32 kind = boss->_1534;
        if ((kind == 1 || kind == 5 || kind == 9 || kind == 0 || kind == 4 || kind == 8) &&
            boss->_1558.isOnBit(3)) {
            ret = false;
        }
    }
    return ret;
}

void SiteBossRecognizeRoot::m38(ksys::act::ai::InlineParamPack* params) {
    SiteBossRecognizeRootBase::m38(params);
    params->addBool(false, "IsCancelAttack", -1);
}

}  // namespace uking::ai
