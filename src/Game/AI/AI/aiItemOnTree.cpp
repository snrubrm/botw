#include "Game/AI/AI/aiItemOnTree.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actPhysicsConstraints.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::ai {

ItemOnTree::ItemOnTree(const InitArg& arg) : ItemRoot(arg) {}

bool ItemOnTree::init_(sead::Heap* heap) {
    return ItemRoot::init_(heap);
}

void ItemOnTree::enter_(ksys::act::ai::InlineParamPack* params) {
    _a8 = 0;
    _ac = 0;
    _b0 = 0;
    _b4 = false;
    _b5 = false;
    ItemRoot::enter_(params);
}

void ItemOnTree::leave_() {
    ItemRoot::leave_();
}

void ItemOnTree::loadParams_() {
    ItemRoot::loadParams_();
    getStaticParam(&mFallPowerMin_s, "FallPowerMin");
    getStaticParam(&mFallPowerMax_s, "FallPowerMax");
    getStaticParam(&mFallOddsMin_s, "FallOddsMin");
    getStaticParam(&mFallOddsMax_s, "FallOddsMax");
    getStaticParam(&mFallIntervalRange_s, "FallIntervalRange");
    getStaticParam(&mFallCheckSpeedTh_s, "FallCheckSpeedTh");
    getStaticParam(&mAttOnTree_s, "AttOnTree");
    getStaticParam(&mAttOnGround_s, "AttOnGround");
}

bool ItemOnTree::handleMessage_(const ksys::Message& message) {
    if (isCurrentChild("通常") && message.getType() == 0x800001c) {
        if (message.getUserData())
            _a8 = *static_cast<const int*>(message.getUserData());
        _b4 = true;
    }
    return false;
}

void ItemOnTree::m34() {
    if (mActor->getMapObject()) {
        if (*mInitMotionStatus_m != 1)
            m35();
        else
            m36();
    } else {
        m36();
    }
}

void ItemOnTree::m35() {
    auto* actor = mActor;
    ksys::act::enableAttClient(actor, mAttOnTree_s);
    ksys::act::disableAttClient(actor, mAttOnGround_s);
    changeChild("通常");
}

void ItemOnTree::m36() {
    auto* actor = mActor;
    if (auto* body = actor->getMainBody()) {
        body->changeMotionType(ksys::phys::MotionType::Dynamic);
        actor->getConstraints().sub_7100D40338();
    }
    sub_7100731000(actor, true);
    ksys::act::disableAttClient(actor, mAttOnTree_s);
    ksys::act::enableAttClient(actor, mAttOnGround_s);
    changeChild("もげる");
}

}  // namespace uking::ai
