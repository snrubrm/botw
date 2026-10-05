#include "Game/AI/Action/actionMoveByAnimeDrivenToTarget.h"
#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::action {

MoveByAnimeDrivenToTarget::MoveByAnimeDrivenToTarget(const InitArg& arg) : MoveByAnimeDriven(arg) {}

MoveByAnimeDrivenToTarget::~MoveByAnimeDrivenToTarget() = default;

bool MoveByAnimeDrivenToTarget::init_(sead::Heap* heap) {
    return MoveByAnimeDriven::init_(heap);
}

void MoveByAnimeDrivenToTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    MoveByAnimeDriven::enter_(params);
    _68.sub_710000102C(0.0f);
}

bool MoveByAnimeDrivenToTarget::reenter_(ksys::act::ai::ActionBase* other, bool x) {
    if (!MoveByAnimeDriven::reenter_(other, true))
        return false;
    auto* action = sead::DynamicCast<MoveByAnimeDrivenToTarget>(other);
    if (!action)
        return false;
    _68.sub_710000103C(action->_68);
    return true;
}

void MoveByAnimeDrivenToTarget::leave_() {
    MoveByAnimeDriven::leave_();
}

void MoveByAnimeDrivenToTarget::loadParams_() {
    MoveByAnimeDriven::loadParams_();
    getStaticParam(&mAnimRotateMax_s, "AnimRotateMax");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

// NON_MATCHING: The natural vector operations produce different instruction scheduling and frame layout.
void MoveByAnimeDrivenToTarget::calc_() {
    auto* actor = mActor;
    auto* as_list = actor->getASList();
    if (!as_list)
        return;
    const auto position = actor->getMtx().getTranslation();
    auto* controller = actor->getCharacterController();
    auto* body = actor->getMainBody();
    sead::Vector3f direction;
    if (controller) {
        act::sub_7100E7F318(as_list, controller, 1.0f);
        if (auto* nav = actor->m45()) {
            _68.sub_7100001050(as_list, nav, controller, *mAnimRotateMax_s);
            return;
        }
        direction = *mTargetPos_d - position;
    } else {
        if (!body)
            return;
        sead::Quatf rotation;
        body->getRotation(&rotation);
        sead::Vector3f linear = as_list->sub_710115D2D4();
        sead::Vector3f angular = as_list->sub_710115D3B8();
        linear.rotate(rotation);
        linear *= 30.0f;
        angular *= 30.0f;
        body->setLinearVelocity(linear + sead::Vector3f(0.0f, (mTargetPos_d->y - position.y) * 30.0f,
                                                      0.0f));
        body->setAngularVelocity(angular);
        direction = *mTargetPos_d - position;
        const f32 speed = sead::Vector2f(linear.x, linear.z).length();
        const f32 distance = direction.length();
        if (distance > 0.0f)
            direction *= speed / distance;
        ksys::as::ASList::Unk4 query;
        if (as_list->sub_710115FBC8(24, &query, &ksys::as::ASList::Unk2::sub_71011638DC, true))
            return;
    }
    const auto forward = actor->getMtx().getBase(2);
    _68.sub_71000010E0(as_list, direction, forward, *mAnimRotateMax_s);
}

}  // namespace uking::action
