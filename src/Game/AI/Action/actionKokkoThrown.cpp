#include "Game/AI/Action/actionKokkoThrown.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::action {

KokkoThrown::KokkoThrown(const InitArg& arg) : Thrown(arg) {}

KokkoThrown::~KokkoThrown() = default;

bool KokkoThrown::init_(sead::Heap* heap) {
    return Thrown::init_(heap);
}

void KokkoThrown::enter_(ksys::act::ai::InlineParamPack* params) {
    Thrown::enter_(params);
    _c0 = 1.0f;
    _c4 = false;
    if (!_a4) {
        if (auto* actor = mActor) {
            if (!_a5) {
                if (auto* controller = actor->getCharacterController())
                    _c0 = controller->get110();
                else if (auto* body = actor->getMainBody())
                    _c0 = body->getGravityFactor();
            }
        }
    }
    *mIsChangeableStateFreeFall_a = false;
}

void KokkoThrown::leave_() {
    Thrown::leave_();
    if (auto* actor = mActor) {
        if (auto* controller = actor->getCharacterController())
            controller->sub_7100F5EEB8(_c0);
        else if (auto* body = actor->getMainBody())
            body->setGravityFactor(_c0);
    }
    *mIsChangeableStateFreeFall_a = true;
}

void KokkoThrown::loadParams_() {
    Thrown::loadParams_();
    getStaticParam(&mGravityScale_s, "GravityScale");
    getAITreeVariable(&mIsChangeableStateFreeFall_a, "IsChangeableStateFreeFall");
}

void KokkoThrown::calc_() {
    Thrown::calc_();
    if (!_c4) {
        if (auto* actor = mActor) {
            if (_a5) {
                if (auto* controller = actor->getCharacterController())
                    controller->sub_7100F5EEB8(*mGravityScale_s);
                else if (auto* body = actor->getMainBody())
                    body->setGravityFactor(*mGravityScale_s);
            }
        }
    }
    _c4 = _a5;
}

}  // namespace uking::action
