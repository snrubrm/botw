#include "Game/Actor/AI/aiTrolleyRoot.h"
#include <cmath>
#include "Game/Actor/Player/actPlayerBase.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/Profiles/actDynamicActor.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/Constraint/physConstraint.h"
#include "KingSystem/Physics/Constraint/physFixedCs.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physInstanceSet.h"

namespace uking::ai {

// NON_MATCHING: static parameter zero-store order and the 0.02 constant load differ.
TrolleyRoot::TrolleyRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

TrolleyRoot::~TrolleyRoot() {
    if (_d0) {
        ksys::phys::Constraint::destroy(_d0);
        _d0 = nullptr;
    }
}

bool TrolleyRoot::init_(sead::Heap* heap) {
    auto* actor = sead::DynamicCast<ksys::act::DynamicActor>(mActor);
    if (!actor)
        return false;
    auto* physics = actor->getPhysics();
    actor->_a70 = &_d8;
    if (!physics)
        return false;
    auto* main_body = actor->getMainBody();
    if (!main_body)
        return false;
    auto* body = physics->findRigidBody("Barrier");
    if (!body)
        return false;
    ksys::phys::FixedCs::Param param;
    param.body_a = main_body;
    param.body_b = body;
    _d0 = ksys::phys::FixedCs::make(param, heap);
    return true;
}

void TrolleyRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    changeChild("転がり");
    if (_d0)
        _d0->sub_7100F69FF0();
}

// NON_MATCHING: player direction registers and accessor stack slots differ.
void TrolleyRoot::sub_71005D0CB4(ksys::act::Unk_71006dc134* arg) {
    auto* actor = mActor;
    auto* info = arg->_18;
    ksys::act::ActorLinkConstDataAccess source;
    if (info && ksys::act::acquireActor(&info->_d8, &source) && source.isPlayerProfile()) {
        bool use_player_angle = false;
        if (info->sub_71007A1F68(2)) {
            ksys::act::acc::PlayerBase player;
            player.getPlayerFromPlayerInfo();
            use_player_angle = player.x_26();
        }
        sead::Vector3f direction;
        if (use_player_angle) {
            f32 angle;
            {
                ksys::act::acc::PlayerBase player;
                player.getPlayerFromPlayerInfo();
                angle = player.x_44();
            }
            direction = {sinf(angle), 0.0f, cosf(angle)};
        } else {
            ksys::act::acc::PlayerBase player;
            player.getPlayerFromPlayerInfo();
            direction = player.getActorMtx().getBase(2);
        }
        arg->_0 = direction * arg->_0.length();
    } else {
        const f32 length = arg->_0.normalize();
        const f32 dot = _50.dot(arg->_0);
        if (dot > 0.5f)
            arg->_0 = _50 * length;
        else if (dot < -0.5f)
            arg->_0 = -(_50 * length);
        else
            arg->_0 *= length;
    }

    if (auto* body = actor->getMainBody()) {
        body->getCenterOfMassInWorld(&arg->_c);
        if (!actor->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_40)) {
            sead::Vector3f impulse = arg->_0;
            const f32 length = impulse.normalize();
            _c0 += impulse * sead::Mathf::min(body->getMass() * 40.0f, length);
            _5c = 0.0f;
            arg->_0 = {0.0f, 0.0f, 0.0f};
        }
    }
}

void TrolleyRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void TrolleyRoot::loadParams_() {
    getStaticParam(&mNearGoalDist_s, "NearGoalDist");
    getStaticParam(&mNearGoalLimitSpd_s, "NearGoalLimitSpd");
    getStaticParam(&mNearGoalReduceRate_s, "NearGoalReduceRate");
}

bool TrolleyRoot::handleMessage_(const ksys::Message* message) {
    if (!_70._30)
        _70.m2(*message);
    return false;
}

}  // namespace uking::ai
