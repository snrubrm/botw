#include "Game/AI/AI/aiWolfLinkWarp.h"
#include "Game/Actor/actWolfLink.h"
#include "KingSystem/Physics/System/physHavokAI.h"
#include "KingSystem/Physics/System/physRayCastForRequest.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"

namespace uking::ai {

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

// NON_MATCHING: the original's enum temporaries share one stack slot with the InlineParamPack
// (they have lifetime markers, as inlined by-value parameters would) and _a8 is loaded first
void WolfLinkWarp::enter_(ksys::act::ai::InlineParamPack* params) {
    _8c = ksys::Timer(*mTransitFrames_s, *mTransitFrames_s);
    _98 = ksys::Timer(*mFramesUntilFail_s, *mFramesUntilFail_s);
    _c0.makeAllZero();
    _c0.setBit(Flag(Flag::_0));
    using Idx = act::WolfLink::Idx14f8;
    if (!(_a8->_14f8[Idx(Idx::_10)].value <= sead::Mathf::epsilon()))
        _c0.setBit(Flag(Flag::_1));

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
    _c0.makeAllZero();
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
