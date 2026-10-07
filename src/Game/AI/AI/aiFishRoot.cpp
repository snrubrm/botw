#include "Game/AI/AI/aiFishRoot.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/Physics/System/physRayCastForRequest.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actChemical.h"

namespace uking::ai {

FishRoot::FishRoot(const InitArg& arg) : SimpleWildlifeRoot(arg) {}

// NON_MATCHING: regalloc of the element destructor loop (we hoist the element address `end - 0xe8` into x21 for the two
// calls; the original recomputes it in each branch).
FishRoot::~FishRoot() {
    _1d0.freeBuffer();
    if (_1b8)
        _1b8->release();
    _1b8 = nullptr;
    if (_1c0)
        _1c0->release();
    _1c0 = nullptr;
}

// NON_MATCHING: the original moves `start` into x1 after negating the height (scheduling only).
bool FishRoot::sub_71003CE608(const sead::Vector3f& start) {
    _1c0 = ksys::phys::RayCastForRequest::allocRequest(mActor->getPhysics()->get188(0),
                                                       ksys::phys::GroundHit::HitAll);
    if (_1c0) {
        _1c0->enableLayer(ksys::phys::ContactLayer::EntityGroundObject);
        _1c0->enableLayer(ksys::phys::ContactLayer::EntityGround);
        _1c0->enableLayer(ksys::phys::ContactLayer::EntityGroundSmooth);
        _1c0->enableLayer(ksys::phys::ContactLayer::EntityGroundRough);
        _1c0->setStartAndDisplacementScaled(start, sead::Vector3f::ey, -mActor->getAabb().getSizeY());
        _1c0->submitRequest(ksys::phys::ContactLayerType::Entity);
    }
    return true;
}

bool FishRoot::init_(sead::Heap* heap) {
    return SimpleWildlifeRoot::init_(heap);
}

void FishRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    SimpleWildlifeRoot::enter_(params);
}

void FishRoot::calc_() {
    sub_71003CC878();
    SimpleWildlifeRoot::calc_();
    const sead::Vector3f position = mActor->getMtx().getTranslation();
    _1a4 = (position - getPlayerPosition()).squaredLength();
    sub_71003CCA34();
}

void FishRoot::leave_() {
    if (_1b8)
        _1b8->release();
    _1b8 = nullptr;
    if (_1c0)
        _1c0->release();
    _1c0 = nullptr;
    SimpleWildlifeRoot::leave_();
}

void FishRoot::loadParams_() {
    SimpleWildlifeRoot::loadParams_();
    getStaticParam(&mInWaterDepth_s, "InWaterDepth");
    getStaticParam(&mOnGroundDepth_s, "OnGroundDepth");
    getStaticParam(&mNextJumpTimeBase_s, "NextJumpTimeBase");
    getStaticParam(&mNextJumpTimeRand_s, "NextJumpTimeRand");
    getStaticParam(&mAllowReturnThreatDist_s, "AllowReturnThreatDist");
    getStaticParam(&mFrameUntilOutOfWater_s, "FrameUntilOutOfWater");
    getStaticParam(&mDistRunFromPlayerOnReturn_s, "DistRunFromPlayerOnReturn");
    getStaticParam(&mIgnoreFoodBase_s, "IgnoreFoodBase");
    getStaticParam(&mIgnoreFoodRand_s, "IgnoreFoodRand");
    getStaticParam(&mIgnoreFoodAfterSuccessBase_s, "IgnoreFoodAfterSuccessBase");
    getStaticParam(&mIgnoreFoodAfterSuccessRand_s, "IgnoreFoodAfterSuccessRand");
}

bool FishRoot::m34() {
    return SimpleWildlifeRoot::m34();
}

bool FishRoot::m35() {
    if (SimpleWildlifeRoot::m35())
        return true;
    auto* chemical = mActor->sub_71011D8A34(0);
    if (chemical && chemical->_1b8 > 0.0f)
        return true;
    auto* cc = mActor->getCharacterController();
    if (cc && mActor->get68f().load()) {
        if ((cc->_116 & 0x14) == 0x10)
            return true;
    }
    return false;
}

bool FishRoot::m36() {
    return false;
}

void FishRoot::m39() {
    if (_c4.value <= sead::Mathf::epsilon()) {
        if (!isCurrentChild("初期配置帰還") && !isCurrentChild("ジャンプ") && sub_710034342C()) {
            if (!isCurrentChild("帰還"))
                mActor->getMtx().getTranslation(_184);
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(_b8, "TargetPos", -1);
            changeChild("逃走", &pack);
        }
    }
}

void FishRoot::m41() {
    if (!isCurrentChild("地上待機")) {
        if (auto* controller = mActor->getCharacterController()) {
            controller->sub_7100F60604();
            controller->sub_7100F63700(true);
        }
        _1b0 = 0;
        changeChild("地上待機");
    }
}

void FishRoot::m40() {
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F60604();
    SimpleWildlifeRoot::m40();
}

void FishRoot::changeToDiscoverInterest() {
    if (!isCurrentChild("興味対象発見")) {
        ksys::act::ActorConstDataAccess accessor;
        if (ksys::act::acquireActor(&_150, &accessor)) {
            ksys::act::ai::InlineParamPack pack;
            sead::Vector3f pos;
            accessor.getActorMtx().getTranslation(pos);
            pack.addVec3(pos, "TargetPos", -1);
            pack.addActor(_150, "TargetActor", -1);
            changeChild("興味対象発見", &pack);
        }
    }
}

void FishRoot::changeToReturn() {
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(_190, "TargetPos", -1);
    pack.addVec3(_184, "MoveAwayFromPos", -1);
    changeChild("帰還", &pack);
}

void FishRoot::changeToReturnToInitialPlacement(bool is_escape) {
    if (!isCurrentChild("初期配置帰還")) {
        mActor->getCharacterController();
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(_190, "TargetPos", -1);
        pack.addBool(is_escape, "IsEscape", -1);
        changeChild("初期配置帰還", &pack);
    }
}

}  // namespace uking::ai
