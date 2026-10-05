#include "Game/AI/AI/aiTreasureBoxRoot.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::ai {

TreasureBoxRoot::TreasureBoxRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

TreasureBoxRoot::~TreasureBoxRoot() = default;

bool TreasureBoxRoot::init_(sead::Heap* heap) {
    if (*mIsInGround_m)
        _79 = false;
    return true;
}

// NON_MATCHING: the ground-state condition is combined with the captured query results.
void TreasureBoxRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    auto* map = actor->getMapObject();
    const bool linked = actor->checkLinkBasicSig();
    const bool used = actor->isWaitRevivalForUsed();
    const bool revival = map && map->checkRevivalFlag(ksys::map::ActorData::Flag::RevivalEnable);
    if (auto* body = actor->getMainBody())
        body->getMotionType();
    if (!*mIsInGround_m || linked || used || revival || _79)
        enter_init();
    else
        sub_71005CEA88();
}

void TreasureBoxRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void TreasureBoxRoot::loadParams_() {
    getStaticParam(&mInGroundOffsetY_s, "InGroundOffsetY");
    getStaticParam(&mInGroundScale_s, "InGroundScale");
    getStaticParam(&mOnGroundOffsetY_s, "OnGroundOffsetY");
    getStaticParam(&mOnGroundScale_s, "OnGroundScale");
    getStaticParam(&mJumpPower_s, "JumpPower");
    getStaticParam(&mDebugDraw_s, "DebugDraw");
    getMapUnitParam(&mIsInGround_m, "IsInGround");
    getMapUnitParam(&mEnableRevival_m, "EnableRevival");
}

bool TreasureBoxRoot::handleMessage_(const ksys::Message* message) {
    if (message->getType() != ksys::MessageType(0x3000007))
        return false;

    auto* actor = mActor;
    if (*mEnableRevival_m)
        actor->becomePreActor(ksys::act::Actor::DeleteType::_1, ksys::act::BaseProc::DeleteReason::_0);
    else
        actor->sleep(ksys::act::BaseProc::SleepWakeReason::_0);
    return true;
}

}  // namespace uking::ai
