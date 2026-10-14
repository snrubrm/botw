#include "Game/Actor/AI/aiLifted.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actUnk_7100e4e084.h"

namespace uking::ai {

Lifted::Lifted(const InitArg& arg) : ksys::act::ai::Ai(arg) {}


void Lifted::enter_(ksys::act::ai::InlineParamPack* params) {
    _40 = 0;
    _48.x();
    auto* actor = mActor;
    if (auto* body = actor->getMainBody())
        body->changeMotionType(ksys::phys::MotionType::Dynamic);
    _44 = false;
    ksys::act::disableAllAttClients(actor);
    if (!isRootAiParamINot5() &&
        (actor->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_40000000) ||
         sub_71005DC444(actor))) {
        mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_40000000);
        changeChild("所持");
        return;
    }
    changeChild("待機");
}

void Lifted::calc_() {
    auto* actor = mActor;
    if (auto* physics = actor->getPhysics()) {
        if (physics->getFlags().isOn(ksys::phys::InstanceSet::Flag::_800))
            physics->getFlags().reset(ksys::phys::InstanceSet::Flag::_800);
    }

    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("所持")) {
            setFailed();
            actor->resetConnectedCalcParent(false);
        } else if (isCurrentChild("投擲") || isCurrentChild("設置")) {
            setFinished();
        }
    }

    if (isCurrentChild("所持")) {
        auto* parent = sead::DynamicCast<ksys::act::Actor>(actor->getConnectedCalcParent());
        if (!parent ||
            parent->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_40)) {
            if (!sub_71005DC470(actor)) {
                setFailed();
                return;
            }
            auto* data = actor->m100();
            if (!data || !data->_128) {
                setFailed();
                return;
            }
            sub_7100482000(sub_71005DC54C(actor), true);
        } else if (sub_71005DC470(actor)) {
            auto* player = sead::DynamicCast<ksys::act::PlayerBase>(actor->getConnectedCalcParent());
            sub_7100482000(sub_71005DC54C(actor), player != nullptr);
        } else if (sub_71005DC4F4(actor) || sub_71005DC4C8(actor)) {
            changeChild("設置");
        } else {
            auto* player = sead::DynamicCast<ksys::act::PlayerBase>(actor->getConnectedCalcParent());
            if (player && player->_c50.isOnBit(10)) {
                actor->resetConnectedCalcParent(false);
                actor->deleteLater(ksys::act::BaseProc::DeleteReason::_0);
            }
        }
    } else if (isCurrentChild("待機")) {
        if (!actor->getConnectedCalcParent()) {
            setFailed();
            return;
        }
        if (!sub_71005DC444(actor)) {
            _44 = true;
            return;
        }
        mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_40000000);
        changeChild("所持");
    }
}

void Lifted::sub_7100482000(const sead::Vector3f& velocity, bool is_shot_by_player) {
    auto* actor = mActor;
    ksys::act::ai::InlineParamPack params;
    if (velocity.x == 0.0f && velocity.y == 0.0f && velocity.z == 0.0f) {
        params.addFloat(0.0f, "Power", -1);
        params.addVec3(velocity, "TargetDir", -1);
        params.addBool(is_shot_by_player, "IsShootByPlayer", -1);
    } else {
        sead::Vector3f dir = velocity;
        const f32 power = dir.normalize();
        params.addFloat(power, "Power", -1);
        params.addVec3(dir, "TargetDir", -1);
        params.addBool(is_shot_by_player, "IsShootByPlayer", -1);
    }
    actor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_40000000);
    changeChild("投擲", &params);
}

void Lifted::leave_() {
    auto* actor = mActor;
    actor->resetConnectedCalcParent(false);
    sub_71005DC5DC(actor);
    if (*mIsGetItem_s) {
        ksys::act::enableAttClient(actor, "Catch");
        ksys::act::enableAttClient(actor, "Pick");
        ksys::act::enableAttClient(actor, "NoticeDo");
        ksys::act::enableAttClient(actor, "AutoAim");
        ksys::act::enableAttClient(actor, "NameBalloon");
    } else {
        ksys::act::enableAllAttClients(actor);
    }
    actor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_40000000);
    if (auto* physics = actor->getPhysics())
        physics->getFlags().reset(ksys::phys::InstanceSet::Flag::_800);
}

void Lifted::loadParams_() {
    getStaticParam(&mIsGetItem_s, "IsGetItem");
}

// NON_MATCHING: same code; the original shares one `return true` block between both branches, ours tail-duplicates it.
bool Lifted::handleMessage_(const ksys::Message* message) {
    if (message->getType() == 0x8000002) {
        auto* actor = mActor;
        actor->resetConnectedCalcParent(false);
        if (isCurrentChild("所持")) {
            if (auto* physics = actor->getPhysics())
                physics->getFlags().set(ksys::phys::InstanceSet::Flag::_800);
            changeChild("待機");
            setFinished();
        }
        return true;
    }

    if (isCurrentChild("投擲")) {
        auto* parent = sead::DynamicCast<ksys::act::Actor>(mActor->getConnectedCalcParent());
        if (!parent && !_48._30)
            return _48.m2(*message);
    }
    return false;
}

}  // namespace uking::ai
