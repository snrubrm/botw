#include "Game/AI/AI/aiWizzrobeCombatMove.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71006F5B14.h"
#include "Game/Actor/actEnemy.h"
#include "Game/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include <gsys/gsysModel.h>
#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiRoot.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
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
    mFlags.set(Flag::Changeable);
    _bc = 0;
    s32 count = *mMoveCountMin_s;
    auto* actor = mActor;
    if (count < 1)
        count = 1;
    else if (count < *mMoveCountMax_s)
        count = sead::GlobalRandom::instance()->getS32Range(count, *mMoveCountMax_s + 1);
    _c0 = count;
    if (actor->getASList() && !mIgnoreHideActionASName_s.isEmpty() &&
        mIgnoreHideActionASName_s == actor->getASList()->x_1(0, 0)) {
        sub_71005FC9C0();
        xlinkSearchAndEmit(actor, "Doron", 2, nullptr);
        sub_71005FCB74();
        return;
    }
    if (testRootAiFlag2(ksys::act::ai::RootAiFlag2::_0) &&
        (*mAttPos_d - actor->getMtx().getTranslation()).length() < *mEscapeLength_s)
        changeChild("上昇隠れ", nullptr);
    else
        changeChild("消える", nullptr);
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

// NON_MATCHING: temporary SafeString stack slots and branch scheduling differ.
void WizzrobeCombatMove::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("消える") || isCurrentChild("上昇隠れ")) {
            sub_71005FC9C0();
            sub_71005FCB74();
        } else if (isCurrentChild("中行動")) {
            if (_c0 > _bc) {
                sub_71005FCB74();
            } else if (getCurrentChild()->isFailed() && _bc == 1 &&
                       (mStartPosition - mActor->getMtx().getTranslation()).length() < 2.0f) {
                sub_71005FCB74();
            } else {
                sub_71005FD0AC();
                ksys::act::ai::InlineParamPack params;
                params.addVec3(*mAttPos_d, "TargetPos", -1);
                changeChild("現れる", &params);
            }
        } else if (isCurrentChild("現れる")) {
            setFinished();
        }
    } else {
        if (isCurrentChild("中行動")) {
            if (!sub_71005D8F28(mActor)) {
                sub_71005FD0AC();
                ksys::act::ai::InlineParamPack params;
                params.addVec3(*mAttPos_d, "TargetPos", -1);
                changeChild("現れる", &params);
            } else if (!*mIsWizzrobeInBattleAreaFlag_a) {
                sub_71005FD0AC();
                ksys::act::ai::InlineParamPack params;
                params.addVec3(*mAttPos_d, "TargetPos", -1);
                changeChild("現れる", &params);
            }
        }
        if (isCurrentChild("現れる"))
            child->setDynamicParam(*mAttPos_d, "TargetPos");
    }
}

void WizzrobeCombatMove::sub_71005FD0AC() {
    if (!_c8)
        return;
    auto* actor = mActor;
    if (sead::IsDerivedFrom<uking::act::Enemy>(actor)) {
        static_cast<uking::act::Enemy*>(actor)->_e90 = _c4;
        ksys::act::enableAllAttClients(actor);
        sub_71005D8D4C(actor, 1.0f, 0, false);
        if (actor->getModel())
            actor->getModel()->sub_7100BF8CB8(false, -1);
        sub_71006F5A80(actor->getChemicalStuff());
    }
    actor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_10000);
    if (auto* controller = actor->getCharacterController()) {
        controller->sub_7100F62CA8(true);
        controller->sub_7100F63554(true);
    }
    auto* damage = actor->getDamageMgr();
    if (sead::IsDerivedFrom<uking::dmg::DamageManager>(damage))
        static_cast<uking::dmg::DamageManager*>(damage)->_212 &= ~0x10;
    _c8 = false;
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
