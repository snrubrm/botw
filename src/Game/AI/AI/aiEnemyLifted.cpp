#include "Game/AI/AI/aiEnemyLifted.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "Game/Damage/dmgDamageCallback.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/ActorSystem/Profiles/actDynamicActor.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::ai {

EnemyLifted::EnemyLifted(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

bool EnemyLifted::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnemyLifted::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* dynamic = sead::DynamicCast<ksys::act::DynamicActor>(mActor))
        dynamic->_a68 &= ~1;
    setDamageCallbackTiming(mActor, 4, &_48);
    auto* actor = mActor;
    actor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_40000000);
    actor->getPhysics()->sub_7100FBADDC();
    changeChild("所持");
}

void EnemyLifted::leave_() {
    auto* actor = mActor;
    actor->resetConnectedCalcParent(false);
    sub_71005DC5DC(actor);
    ksys::act::enableAttClient(actor, "Grab");
    if (auto* dynamic = sead::DynamicCast<ksys::act::DynamicActor>(actor))
        dynamic->_a68 |= 1;
    sub_71005DA114(mActor, &_48);
    actor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_40000000);
    if (auto* physics = actor->getPhysics())
        physics->getFlags().reset(ksys::phys::InstanceSet::Flag::_800);
}

void EnemyLifted::m34() {}

bool EnemyLifted::handleMessage_(const ksys::Message* message) {
    if (message->getType() != 0x8000002)
        return false;
    auto* parent = sead::DynamicCast<ksys::act::PlayerBase>(mActor->getConnectedCalcParent());
    auto* actor = mActor;
    actor->resetConnectedCalcParent(false);
    if (isCurrentChild("所持")) {
        if (auto* physics = actor->getPhysics())
            physics->getFlags().set(ksys::phys::InstanceSet::Flag::_800);
        sub_7100396E8C(sead::Vector3f::zero, parent != nullptr);
    }
    return true;
}

void EnemyLifted::loadParams_() {}

bool EnemyLifted::isFinished() const {
    if (ksys::act::ai::Ai::isFinished())
        return true;
    if (isCurrentChild("着地"))
        return getCurrentChild()->isFinished();
    return false;
}

// NON_MATCHING: the original ends both branches with their own IsShootByPlayer / flag / changeChild tail (tail-duplicated),
// ours joins them; same operations.
void EnemyLifted::sub_7100396E8C(const sead::Vector3f& direction, bool player_parent) {
    ksys::act::ai::InlineParamPack pack;
    if (direction.x == 0.0f && direction.y == 0.0f && direction.z == 0.0f) {
        pack.addFloat(0.0f, "Power", -1);
        pack.addVec3(direction, "TargetDir", -1);
    } else {
        sead::Vector3f normalized = direction;
        const f32 power = normalized.normalize();
        pack.addFloat(power, "Power", -1);
        pack.addVec3(normalized, "TargetDir", -1);
    }
    pack.addBool(player_parent, "IsShootByPlayer", -1);
    mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_40000000);
    _38 = sead::Vector3f::zero;
    changeChild("投擲", &pack);
}

}  // namespace uking::ai
