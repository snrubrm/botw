#include "Game/AI/AI/aiWolfLinkWarp.h"
#include "Game/Actor/actWolfLink.h"
#include "KingSystem/Physics/System/physHavokAI.h"
#include "KingSystem/Physics/System/physRayCastForRequest.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"

namespace uking::ai {

namespace {
using Idx14f8 = act::WolfLink::Idx14f8;
// Inline-only in the original (by-value index parameter: the enum temporary gets lifetime markers).
f32 getTimerValue(act::WolfLink* wolf, Idx14f8 idx) {
    return wolf->_14f8[idx].value;
}
}  // namespace

WolfLinkWarp::WolfLinkWarp(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WolfLinkWarp::~WolfLinkWarp() {
    if (_b8) {
        ksys::phys::HavokAI::instance()->destroyQuery(_b8);
        _b8 = nullptr;
    }
    if (_b0) {
        _b0->release();
        _b0 = nullptr;
    }
}

bool WolfLinkWarp::init_(sead::Heap* heap) {
    _a8 = sead::DynamicCast<act::WolfLink>(mActor);
    return _a8 != nullptr;
}

void WolfLinkWarp::enter_(ksys::act::ai::InlineParamPack* params) {
    _8c = ksys::Timer(*mTransitFrames_s, *mTransitFrames_s);
    _98 = ksys::Timer(*mFramesUntilFail_s, *mFramesUntilFail_s);
    _c0 = 0;
    setFlag(Flag::_0);
    if (!(getTimerValue(_a8, Idx14f8(Idx14f8::_10)) <= sead::Mathf::epsilon()))
        setFlag(Flag::_1);

    ksys::act::ai::InlineParamPack pack;
    pack.addActor(ksys::act::PlayerInfo::getSomeProcLink(), "LeaderActor", -1);
    changeChild("ワープ前", &pack);
}

void WolfLinkWarp::leave_() {
    if (_b8) {
        ksys::phys::HavokAI::instance()->destroyQuery(_b8);
        _b8 = nullptr;
    }
    if (_b0) {
        _b0->release();
        _b0 = nullptr;
    }
    _c0 = 0;
    using Idx = act::WolfLink::Idx14f8;
    _a8->sub_71002F2E78(Idx::_10);
}

void WolfLinkWarp::loadParams_() {
    getStaticParam(&mNumCalcPerFrame_s, "NumCalcPerFrame");
    getStaticParam(&mFramesUntilFail_s, "FramesUntilFail");
    getStaticParam(&mTransitFrames_s, "TransitFrames");
    getStaticParam(&mWarpFromPlayerOffset_s, "WarpFromPlayerOffset");
    getStaticParam(&mInitialAngle_s, "InitialAngle");
    getStaticParam(&mAreaSearchRadius_s, "AreaSearchRadius");
    getStaticParam(&mAreaSearchCharacterRadius_s, "AreaSearchCharacterRadius");
    getStaticParam(&mAreaThreshold_s, "AreaThreshold");
    getDynamicParam(&mWarpType_d, "WarpType");
}

}  // namespace uking::ai
