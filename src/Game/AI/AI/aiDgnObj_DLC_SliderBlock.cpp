#include "Game/AI/AI/aiDgnObj_DLC_SliderBlock.h"
#include <gsys/gsysModel.h>
#include "KingSystem/Utils/Thread/Message.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/System/VFR.h"

namespace uking::ai {

DgnObj_DLC_SliderBlock::DgnObj_DLC_SliderBlock(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

DgnObj_DLC_SliderBlock::~DgnObj_DLC_SliderBlock() = default;

bool DgnObj_DLC_SliderBlock::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void DgnObj_DLC_SliderBlock::enter_(ksys::act::ai::InlineParamPack* params) {
    mActor->sub_71011DA824(this);
}

// NON_MATCHING: the original selects 1.0f / 200.0f with branches (the else arm loads the constant
// from the literal pool); we get an fcsel.
void DgnObj_DLC_SliderBlock::calc_() {
    if (!mActor)
        return;
    auto* body = mActor->getMainBody();
    if (!body)
        return;
    f32 max = 200.0f;
    if (ksys::VFR::instance()->hasCustomTimeMultiplier())
        max = 1.0f;
    body->setMaxLinearVelocity(max);
    body->setMaxAngularVelocity(max);
}

bool DgnObj_DLC_SliderBlock::handleMessage_(const ksys::Message* message) {
    if (message && message->getType() == 0x3000003) {
        if (auto* body = mActor->getMainBody()) {
            body->setMaxLinearVelocity(1.0f);
            body->setMaxAngularVelocity(1.0f);
        }
    }
    return false;
}

bool DgnObj_DLC_SliderBlock::m4(ksys::act::BaseProc* proc) {
    return false;
}

// Moves the model to the home matrix's translation shifted along its x axis by _60 (which is updated
// from the main body's position unless the actor has ActorFlag2 _40 set).
bool DgnObj_DLC_SliderBlock::m5(ksys::act::BaseProc* proc) {
    auto* body = mActor->getMainBody();
    auto* model = mActor->getModel();
    if (!body || !model)
        return false;

    sead::Matrix34f mtx;
    mActor->getHomeMtx(&mtx);
    sead::Vector3f axis;
    mtx.getBase(axis, 0);
    sead::Vector3f origin;
    mtx.getTranslation(origin);
    if (!mActor->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_40)) {
        sead::Vector3f position;
        body->getPosition(&position);
        _60 = axis.dot(position - origin);
    }
    mtx.setTranslation(origin + axis * _60);
    model->setMatrix(mtx);
    model->updateWorldMatrix();
    return true;
}

bool DgnObj_DLC_SliderBlock::hasUpdateForPreDeleteCb() {
    return true;
}

bool DgnObj_DLC_SliderBlock::updateForPreDelete() {
    return true;
}

void DgnObj_DLC_SliderBlock::leave_() {
    mActor->sub_71011DA834(this);
}

void DgnObj_DLC_SliderBlock::loadParams_() {}

}  // namespace uking::ai
