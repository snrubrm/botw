#include "Game/AI/AI/aiWizzrobeCombatMove.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/System/physRayCastBodyQuery.h"

namespace uking::ai {

WizzrobeCombatMove::WizzrobeCombatMove(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

// The original keeps the vtable store that a defaulted destructor drops (same form as upstream's
// GameDataFlagSelector::~GameDataFlagSelector() { ; }, commit 96101229).
WizzrobeCombatMove::~WizzrobeCombatMove() {
    ;
}

bool WizzrobeCombatMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void WizzrobeCombatMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void WizzrobeCombatMove::leave_() {
    sub_71005FD0AC();
}

void WizzrobeCombatMove::loadParams_() {
    getStaticParam(&mMoveCountMin_s, "MoveCountMin");
    getStaticParam(&mMoveCountMax_s, "MoveCountMax");
    getStaticParam(&mDistY_s, "DistY");
    getStaticParam(&mRetryLength_s, "RetryLength");
    getStaticParam(&mMaxDistXZ_s, "MaxDistXZ");
    getStaticParam(&mMinDistXZ_s, "MinDistXZ");
    getStaticParam(&mEscapeLength_s, "EscapeLength");
    getStaticParam(&mIgnoreHideActionASName_s, "IgnoreHideActionASName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mAttPos_d, "AttPos");
    getAITreeVariable(&mIsWizzrobeInBattleAreaFlag_a, "IsWizzrobeInBattleAreaFlag");
}

bool WizzrobeCombatMove::isFinished() const {
    if (isCurrentChild("現れる") && getCurrentChild()->isFinished())
        return true;
    return ksys::act::ai::Ai::isFinished();
}

// 0x71005fd24c
bool WizzrobeCombatMove::sub_71005FD24C(sead::Vector3f* hit_position, sead::Vector3f start,
                                      sead::Vector3f end) {
    using namespace ksys::phys;
    RayCastBodyQuery query(sub_710072E804(mActor, 0), GroundHit::HitAll);
    query.enableLayer(ContactLayer::EntityGround);
    query.enableLayer(ContactLayer::EntityGroundRough);
    query.enableLayer(ContactLayer::EntityGroundObject);
    query.enableLayer(ContactLayer::EntityObject);
    query.enableLayer(ContactLayer::EntityTree);
    if (!(mActor->get68f().load() & 2))
        query.enableLayer(ContactLayer::EntityWater);
    query.setStartAndEnd(start, end);
    query.setNormalCheckingMode(RayCast::NormalCheckingMode::_0);
    if (!query.worldRayCast(ContactLayerType::Entity))
        return false;
    if (hit_position)
        query.getHitPosition(hit_position);
    return true;
}

}  // namespace uking::ai
