#include "Game/AI/AI/aiLynelTackleMove.h"
#include <cfloat>
#include <cmath>
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::ai {

LynelTackleMove::LynelTackleMove(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

LynelTackleMove::~LynelTackleMove() = default;

bool LynelTackleMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void LynelTackleMove::enter_(ksys::act::ai::InlineParamPack* params) {
    _58 = ksys::Timer(5, 5);
    sub_710049B8F0();
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    changeChild("近づき", &pack);
}

bool LynelTackleMove::isFailed() const {
    return ksys::act::ai::Ai::isFailed() || getCurrentChild()->isFailed();
}

bool LynelTackleMove::isChangeable() const {
    return false;
}

void LynelTackleMove::leave_() {
    sub_710049BEC4();
}

void LynelTackleMove::loadParams_() {
    getStaticParam(&mThroughDist_s, "ThroughDist");
    getStaticParam(&mCloseEndAngle_s, "CloseEndAngle");
    getStaticParam(&mCloseEndDist_s, "CloseEndDist");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

bool LynelTackleMove::isFinished() const {
    return ActionBase::isFinished() || (isCurrentChild("通り過ぎ") && getCurrentChild()->isFinished());
}

void LynelTackleMove::sub_710049B8F0() {
    if (auto* controller = mActor->getCharacterController()) {
        controller->enableContactLayer(ksys::phys::ContactLayer::EntityPlayer);
        controller->enableContactLayer(ksys::phys::ContactLayer::EntityRagdoll);
    }

    auto* body = mActor->getRigidBodyByName(ksys::act::getStr_Body().cstr());
    if (!body)
        return;
    for (int i = 0, n = body->getRigidBodies().size(); i < n; ++i) {
        if (auto* rigid_body = body->getRigidBody(i)) {
            rigid_body->enableContactLayer(ksys::phys::ContactLayer::EntityPlayer);
            rigid_body->enableContactLayer(ksys::phys::ContactLayer::EntityRagdoll);
        }
    }
}

void LynelTackleMove::changeToPassThrough() {
    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    sead::Vector3f dir;
    mActor->getMtx().getBase(dir, 2);
    dir.normalize();
    const f32 dist = dir.dot(*mTargetPos_d - pos) + *mThroughDist_s;
    const sead::Vector3f target = pos + dir * dist;
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(target, "TargetPos", -1);
    changeChild("通り過ぎ", &pack);
}

void LynelTackleMove::sub_710049BEC4() {
    if (auto* controller = mActor->getCharacterController()) {
        controller->disableContactLayer(ksys::phys::ContactLayer::EntityPlayer);
        controller->disableContactLayer(ksys::phys::ContactLayer::EntityRagdoll);
    }

    auto* body = mActor->getRigidBodyByName(ksys::act::getStr_Body().cstr());
    if (!body)
        return;
    for (int i = 0, n = body->getRigidBodies().size(); i < n; ++i) {
        if (auto* rigid_body = body->getRigidBody(i)) {
            rigid_body->disableContactLayer(ksys::phys::ContactLayer::EntityPlayer);
            rigid_body->disableContactLayer(ksys::phys::ContactLayer::EntityRagdoll);
        }
    }
}

// NON_MATCHING: backend load scheduling only (same values, registers and branches) — the original
// hoists the child-vtable reloads above the tbnz/tbz in the isFinished/isFailed/isChangeable chain
// and loads all four ANGLE direction components before either fsub
void LynelTackleMove::calc_() {
    if (!(_58.value <= FLT_EPSILON))
        _58.update();

    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (child->isFailed()) {
            setFailed();
            return;
        }
        if (isCurrentChild("近づき"))
            changeToPassThrough();
        else
            setFinished();
        return;
    }

    if (child->isChangeable()) {
        if (isCurrentChild("近づき")) {
            auto* actor = mActor;
            sead::Vector3f dir;
            dir.y = 0.0f;
            dir.x = mTargetPos_d->x - actor->getMtx().m[0][3];
            dir.z = mTargetPos_d->z - actor->getMtx().m[2][3];
            const f32 len = dir.normalize();
            if (len <= *mCloseEndDist_s) {
                changeToPassThrough();
                return;
            }
            sead::Vector3f fwd;
            fwd.x = actor->getMtx().m[0][2];
            fwd.z = actor->getMtx().m[2][2];
            fwd.y = 0.0f;
            fwd.normalize();
            if (!(dir.x * fwd.x + dir.y * fwd.y + dir.z * fwd.z >= std::cos(*mCloseEndAngle_s))) {
                changeToPassThrough();
                return;
            }
        }
        if (_58.value <= FLT_EPSILON) {
            sead::Vector3f dir;
            sub_71000891C8(&dir, mActor);
            if (sub_710072FEC4(mActor, dir, mActor->getVelocity().dot(dir) + 3.5f, nullptr,
                               true, nullptr)) {
                setFailed();
                return;
            }
        }
    }
    if (!isCurrentChild("近づき"))
        return;
    getCurrentChild()->setDynamicParam(*mTargetPos_d, "TargetPos");
}

bool LynelTackleMove::handleMessage_(const ksys::Message* message) {
    if (message->getType() == 0x3000003)
        sub_710049BEC4();
    else if (message->getType() == 0x3000004)
        sub_710049B8F0();
    return false;
}

}  // namespace uking::ai
