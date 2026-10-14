#include "Game/Actor/AI/aiSeqPredictOctarockAttack.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actLodState.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include <math/seadBoundBox.h>
#include "Game/Actor/aiUnk_71007368A4.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/System/VFR.h"

namespace uking::ai {

SeqPredictOctarockAttack::SeqPredictOctarockAttack(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SeqPredictOctarockAttack::~SeqPredictOctarockAttack() = default;

bool SeqPredictOctarockAttack::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SeqPredictOctarockAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    _4c = *mTargetPos_d;
    _58 = *mTargetVel_d;
    _48 = true;
    sub_7100564154();
}

void SeqPredictOctarockAttack::sub_7100564154() {
    if (auto* lod = mActor->getLodState())
        lod->mFlags26.set(1);
    ksys::act::ai::InlineParamPack params;
    params.addVec3(_4c, "TargetPos", -1);
    params.addVec3(_58, "TargetVel", -1);
    changeChild("先行動", &params);
}

void SeqPredictOctarockAttack::calc_() {
    sub_710056439C();
    sub_71005DB3EC(mActor);
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("先行動")) {
            sub_710056464C();
            return;
        }
        if (isCurrentChild("中行動")) {
            sub_7100564738();
            return;
        }
        setFinished();
    } else {
        child->isChangeable();
    }
    child->setDynamicParam(_4c, "TargetPos");
    child->setDynamicParam(_58, "TargetVel");
}

// Tracks the predicted target: copies the target position / velocity while the attack AS allows it, else moves the
// last position along the last velocity (stopping when it enters the actor's body).
void SeqPredictOctarockAttack::sub_710056439C() {
    auto* as_list = mActor->getASList();
    if (!as_list) {
        _4c = *mTargetPos_d;
        _58 = *mTargetVel_d;
        return;
    }

    if (as_list->x(34, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_710116383C, true))
        _48 = false;

    if (!as_list->x(34, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011638DC, true) && _48) {
        _4c = *mTargetPos_d;
        _58 = *mTargetVel_d;
    } else if (_58.x != 0.0f || _58.y != 0.0f || _58.z != 0.0f) {
        sead::Vector3f pos = _4c;
        pos += _58 * ksys::VFR::instance()->getDeltaFrame();
        sead::BoundBox3f box;
        auto* body = sub_71007394DC(mActor);
        bool inside = false;
        if (body) {
            body->getAabbInWorld(&box);
            inside = box.isInside(pos);
        }
        if (inside)
            _58 = sead::Vector3f::zero;
        else
            _4c = pos;
    }

    if (as_list->x(71, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011637EC, true))
        _48 = true;
}

void SeqPredictOctarockAttack::sub_710056464C() {
    ksys::act::ai::InlineParamPack params;
    params.addVec3(_4c, "TargetPos", -1);
    params.addVec3(_58, "TargetVel", -1);
    changeChild("中行動", &params);
}

void SeqPredictOctarockAttack::sub_7100564738() {
    if (auto* lod = mActor->getLodState())
        lod->mFlags26.reset(1);
    ksys::act::ai::InlineParamPack params;
    params.addVec3(_4c, "TargetPos", -1);
    params.addVec3(_58, "TargetVel", -1);
    changeChild("後行動", &params);
}

void SeqPredictOctarockAttack::leave_() {
    if (auto* lod = mActor->getLodState())
        lod->mFlags26.reset(1);
}

void SeqPredictOctarockAttack::loadParams_() {
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mTargetVel_d, "TargetVel");
}

}  // namespace uking::ai
