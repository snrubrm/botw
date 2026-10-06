#include "Game/AI/AI/aiWolfLinkWarp.h"
#include "Game/Actor/actWolfLink.h"
#include "KingSystem/Physics/System/physHavokAI.h"
#include "KingSystem/Physics/System/physRayCastForRequest.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"

namespace uking::ai {

namespace {
using Idx14f8 = act::WolfLink::Idx14f8;
// inline-only in the original; name is a guess. Evidence: same by-value-index timer read as in
// WolfLinkNormalRoot (10+ sites across its functions; the enum temporaries share one stack slot).
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

void WolfLinkWarp::sub_710060ECE0() {
    _b0 = ksys::phys::RayCastForRequest::allocRequest(nullptr, ksys::phys::GroundHit::NPC);
    if (!_b0)
        return;
    _b0->enableLayer(ksys::phys::ContactLayer::EntityAirWall);
    _b0->enableLayer(ksys::phys::ContactLayer::EntityGround);
    _b0->enableLayer(ksys::phys::ContactLayer::EntityGroundObject);
    _b0->enableLayer(ksys::phys::ContactLayer::EntityGroundSmooth);
    _b0->enableLayer(ksys::phys::ContactLayer::EntityGroundRough);
    _b0->enableLayer(ksys::phys::ContactLayer::EntityNPC);
    _b0->enableLayer(ksys::phys::ContactLayer::EntityNPC_NoHitPlayer);
    _b0->enableLayer(ksys::phys::ContactLayer::EntityObject);
    _b0->enableLayer(ksys::phys::ContactLayer::EntityPlayer);
    _b0->enableLayer(ksys::phys::ContactLayer::EntityRagdoll);
    _b0->enableLayer(ksys::phys::ContactLayer::EntityTree);
    sead::Vector3f start = _80;
    sead::Vector3f end = _80;
    start.y += 2.5f;
    end.y += -2.5f;
    _b0->setStartAndEnd(start, end);
    _b0->submitRequest(ksys::phys::ContactLayerType::Entity);
    setFlag(Flag::_5);
}

void WolfLinkWarp::sub_710060EE14() {
    if (_b0->hasHit()) {
        _b0->getHitPosition(&_80);
        clearFlag(Flag::_5);
        setFlag(Flag::_6);
    } else {
        clearFlag(Flag::_5);
        setFlag(Flag::_7);
    }
    if (_b0) {
        _b0->release();
        _b0 = nullptr;
    }
}

void WolfLinkWarp::calc_() {
    if (isFinished() || isFailed())
        return;
    if (isCurrentChild("ワープ前")) {
        if (*mWarpType_d != 4) {
            if (cannotUseWolfLinkAmiibo()) {
                setFailed();
                return;
            }
            _98.update();
            if (_98.value <= sead::Mathf::epsilon()) {
                setFailed();
                return;
            }
        }
        sub_710060DDFC();
    } else if (isCurrentChild("ワープ開始")) {
        x();
    } else if (isCurrentChild("ワープ")) {
        auto* child = getCurrentChild();
        if (child->isFinished() || child->isFailed()) {
            mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_20);
            changeChild("ワープ後", nullptr);
        }
    } else if (isCurrentChild("ワープ後")) {
        auto* child = getCurrentChild();
        if (child->isFinished() || child->isFailed())
            setFinished();
    }
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
