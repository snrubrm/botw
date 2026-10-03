#include "Game/AI/Action/actionMoveToHomeMtx.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "math/seadMathCalcCommon.h"

namespace uking::action {

MoveToHomeMtx::MoveToHomeMtx(const InitArg& arg) : ksys::act::ai::Action(arg) {}

MoveToHomeMtx::~MoveToHomeMtx() = default;

bool MoveToHomeMtx::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void MoveToHomeMtx::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void MoveToHomeMtx::leave_() {
    ksys::act::ai::Action::leave_();
}

void MoveToHomeMtx::loadParams_() {
    getStaticParam(&mToHomeMtxLocal_s, "ToHomeMtxLocal");
    getStaticParam(&mSetEnd_s, "SetEnd");
    getStaticParam(&mDisableModelDraw_s, "DisableModelDraw");
}

void MoveToHomeMtx::calc_() {
    auto* actor = mActor;
    if (auto* body = actor->getMainBody()) {
        sead::Matrix34f mtx;
        if (*mToHomeMtxLocal_s)
            mtx = actor->getHomeMtxRaw();
        else
            actor->getHomeMtx(&mtx);
        body->changePositionAndRotation(mtx, sead::Mathf::epsilon());
    }
    if (*mDisableModelDraw_s)
        actor->setModelDrawEnabled(true);
    if (*mSetEnd_s)
        setFinished();
}

}  // namespace uking::action
