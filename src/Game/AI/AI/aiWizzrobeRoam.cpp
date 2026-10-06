#include "Game/AI/AI/aiWizzrobeRoam.h"
#include "random/seadGlobalRandom.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

WizzrobeRoam::WizzrobeRoam(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WizzrobeRoam::~WizzrobeRoam() = default;

bool WizzrobeRoam::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void WizzrobeRoam::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void WizzrobeRoam::leave_() {
    ksys::act::ai::Ai::leave_();
}

void WizzrobeRoam::loadParams_() {
    getStaticParam(&mMoveCountMin_s, "MoveCountMin");
    getStaticParam(&mMoveCountMax_s, "MoveCountMax");
    getStaticParam(&mChangeHeightPer_s, "ChangeHeightPer");
    getStaticParam(&mMexHeightLevel_s, "MexHeightLevel");
    getStaticParam(&mTerritoryRadius_s, "TerritoryRadius");
    getStaticParam(&mTerritoryRadiusRnd_s, "TerritoryRadiusRnd");
    getStaticParam(&mRetryLength_s, "RetryLength");
    getStaticParam(&mHeightOffset_s, "HeightOffset");
    getDynamicParam(&mCentralPos_d, "CentralPos");
    getAITreeVariable(&mWizzrobeMagicWeatherUnit_a, "WizzrobeMagicWeatherUnit");
}

// 0x71005fe85c
void WizzrobeRoam::sub_71005FE85C() {
    s32 level = _88;
    const s32 max_level = *mMexHeightLevel_s;
    if (max_level >= 1) {
        if (level == 0) {
            level = 1;
        } else if (level == max_level) {
            level -= 1;
        } else if (s32(sead::GlobalRandom::instance()->getU32()) >= 0) {
            level -= 1;
        } else {
            level += 1;
        }
    }
    sead::Vector3f pos = mActor->getMtx().getTranslation();
    pos.y = mCentralPos_d->y + f32(level) * *mHeightOffset_s;
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("高度変化", &pack);
}

// 0x71005fe5cc
void WizzrobeRoam::sub_71005FE5CC() {
    ++_8c;
    const sead::Vector3f pos = sub_71005FEB18();
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("移動", &pack);
}

}  // namespace uking::ai
