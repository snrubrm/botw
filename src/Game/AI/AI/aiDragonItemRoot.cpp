#include "Game/AI/AI/aiDragonItemRoot.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/Actor/actDragon.h"
#include "KingSystem/Utils/Thread/Message.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::ai {

DragonItemRoot::DragonItemRoot(const InitArg& arg) : ItemRoot(arg) {}

// The original keeps the vtable store that a defaulted destructor drops (same form as upstream's
// GameDataFlagSelector::~GameDataFlagSelector() { ; }, commit 96101229).
DragonItemRoot::~DragonItemRoot() {
    ;
}

bool DragonItemRoot::init_(sead::Heap* heap) {
    return ItemRoot::init_(heap);
}

void DragonItemRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ItemRoot::enter_(params);
    auto* actor = mActor;
    _128 = actor->getMainBody();
    _130 = actor->getMtx().getTranslation();
    _13c = 0;
    _140 = 0;
    _144 = 0;
    _148 = *mFlyStartTime_s;
    _14c.reset(0x2f);
    _150 = 0;
    _154 = 0;
    if (!*mIsInitFromCarryBox_a) {
        auto* parent = sead::DynamicCast<act::Dragon>(sead::DynamicCast<ksys::act::Actor>(
            actor->getCreateArgBaseProcLink().getProc(nullptr, nullptr)));
        if (parent) {
            _14c.change(1, parent->_1e0c == 3);
            if (!mActor->getModelBindInfo()) {
                actor->setConnectedCalcParent(parent, false);
                _14c.set(8);
            }
        }
    }
    mActor->get689() = true;
}

void DragonItemRoot::leave_() {
    ItemRoot::leave_();
}

void DragonItemRoot::loadParams_() {
    ItemRoot::loadParams_();
    getStaticParam(&mFlyStartTime_s, "FlyStartTime");
    getStaticParam(&mClearFlagTimeAtRunel_s, "ClearFlagTimeAtRunel");
    getStaticParam(&mGravity_s, "Gravity");
    getStaticParam(&mFlyStartHeightAtRunel_s, "FlyStartHeightAtRunel");
    getStaticParam(&mTailXLinkEventName_s, "TailXLinkEventName");
    getStaticParam(&mAuraXLinkEventName_s, "AuraXLinkEventName");
    getStaticParam(&mFlyPrepareXinkEventName_s, "FlyPrepareXinkEventName");
    getStaticParam(&mFlyStartXinkEventName_s, "FlyStartXinkEventName");
    getStaticParam(&mHitGroundXLinkEventName_s, "HitGroundXLinkEventName");
    getStaticParam(&mLightShaftXLinkEventName_s, "LightShaftXLinkEventName");
    getStaticParam(&mActivateXlinkEventName_s, "ActivateXlinkEventName");
    getStaticParam(&mDestroySwitchGameData_s, "DestroySwitchGameData");
    getStaticParam(&mClearFlagLabel_s, "ClearFlagLabel");
    getStaticParam(&mDropItemFlagLabel_s, "DropItemFlagLabel");
    getMapUnitParam(&mTargetPosition_m, "TargetPosition");
    getAITreeVariable(&mIsInitFromCarryBox_a, "IsInitFromCarryBox");
    getAITreeVariable(&mIsInsideObserverArea_a, "IsInsideObserverArea");
}

// NON_MATCHING: parameter-pack count and string-call preparation are scheduled differently.
void DragonItemRoot::sub_710036CE54(ksys::act::Actor* actor) {
    if (auto* dragon = sead::DynamicCast<act::Dragon>(actor)) {
        ksys::act::ai::InlineParamPack params;
        params.addString(dragon->_1f78.cstr(), "NodeName", -1);
        params.addVec3(sead::Vector3f::zero, "RotOffset", -1);
        params.addVec3({dragon->_1fac, dragon->_1fbc, dragon->_1fcc}, "TransOffset", -1);
        mActor->getMainBody()->enableContactLayer(ksys::phys::ContactLayer::SensorAttackEnemy);
        changeChild("体に貼り付く", &params);
    }
}

bool DragonItemRoot::handleMessage_(const ksys::Message* message) {
    if (message->getType() == 0x3000009) {
        *mIsInsideObserverArea_a = true;
        return true;
    }
    return false;
}

}  // namespace uking::ai
