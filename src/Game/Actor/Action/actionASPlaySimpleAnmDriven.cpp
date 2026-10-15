#include "Game/Actor/Action/actionASPlaySimpleAnmDriven.h"
#include "Game/Actor/actEnemy.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/System/VFR.h"

namespace uking::action {

ASPlaySimpleAnmDriven::ASPlaySimpleAnmDriven(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ASPlaySimpleAnmDriven::~ASPlaySimpleAnmDriven() = default;

bool ASPlaySimpleAnmDriven::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ASPlaySimpleAnmDriven::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    auto* as_list = actor->getASList();
    auto* model = actor->getModel();
    f32 start_frame = -1.0f;
    if (auto* enemy = sead::DynamicCast<act::Enemy>(actor))
        start_frame = enemy->_e82 & 0x400 ? 0.0f : -1.0f;
    playAS(mASName_s.cstr(), *mIsIgnoreSame_s, 0, 0, start_frame);
    if (as_list && model)
        as_list->sub_710115BAF8("Root");
    if (*mIsChangeable_s)
        mFlags.set(Flag::Changeable);
}

void ASPlaySimpleAnmDriven::leave_() {
    auto* actor = mActor;
    if (auto* body = actor->getMainBody()) {
        body->setLinearVelocity(sead::Vector3f::zero);
        body->setAngularVelocity(sead::Vector3f::zero);
    }
    if (*mResetTransBoneOnLeave_s) {
        if (auto* as_list = actor->getASList())
            as_list->sub_710115CD0C();
    }
}

void ASPlaySimpleAnmDriven::loadParams_() {
    getStaticParam(&mIsIgnoreSame_s, "IsIgnoreSame");
    getStaticParam(&mIsChangeable_s, "IsChangeable");
    getStaticParam(&mResetTransBoneOnLeave_s, "ResetTransBoneOnLeave");
    getStaticParam(&mASName_s, "ASName");
}

// NON_MATCHING: matrix/vector scheduling and stack allocation.
void ASPlaySimpleAnmDriven::calc_() {
    auto* actor = mActor;
    auto* as_list = actor->getASList();
    auto* body = actor->getMainBody();
    auto* controller = actor->getCharacterController();
    sead::Vector3f linear = sead::Vector3f::zero;
    sead::Vector3f angular = sead::Vector3f::zero;
    if (as_list) {
        linear = as_list->sub_710115D2D4();
        angular = as_list->sub_710115D3B8();
    }
    sead::Matrix34f transform;
    transform = actor->getMtx();
    linear.rotate(transform);
    angular.rotate(transform);
    if (controller) {
        sub_7100737710(controller, linear);
        sub_7100737714(controller, angular);
    } else if (body) {
        sub_7100737718(body, linear);
        sub_710073771C(body, angular);
    } else {
        const f32 delta = ksys::VFR::instance()->getDeltaFrame();
        angular *= delta;
        sead::Matrix34f rotation;
        rotation.makeR(angular);
        linear *= delta;
        transform.m[0][3] += linear.x;
        transform.m[1][3] += linear.y;
        transform.m[2][3] += linear.z;
        transform *= rotation;
        actor->setMtx(transform, false, true);
    }
    if (isFinishedAS(0, 0)) {
        if (body && !controller) {
            body->setLinearVelocity(sead::Vector3f::zero);
            body->setAngularVelocity(sead::Vector3f::zero);
        }
        setFinished();
    }
}

}  // namespace uking::action
