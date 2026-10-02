#include "Game/AI/Action/actionNPCTurnToPosition.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

// NON_MATCHING: store scheduling (the original zeroes the params before _44 / _54)
NPCTurnToPosition::NPCTurnToPosition(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCTurnToPosition::~NPCTurnToPosition() = default;

bool NPCTurnToPosition::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void NPCTurnToPosition::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void NPCTurnToPosition::leave_() {
    ksys::act::ai::Action::leave_();
}

void NPCTurnToPosition::loadParams_() {
    getDynamicParam(&mPosX_d, "PosX");
    getDynamicParam(&mPosY_d, "PosY");
    getDynamicParam(&mPosZ_d, "PosZ");
}

// NON_MATCHING: register allocation; `move` is read uninitialised when there is no ASList (as in
// the original)
void NPCTurnToPosition::calc_() {
    auto* controller = mActor->getCharacterController();
    if (_44) {
        if (!controller)
            return;
        controller->sub_7100F5EDD8(0.0f);
        controller->sub_7100F5FB24(sead::Vector3f::zero);
        return;
    }

    if (!controller)
        return;

    if (_54) {
        _70.updateStats();
        _58 += _70.mean;
        sead::Vector3f dir = _58;
        dir.y = 0.0f;
        dir.normalize();
        controller->sub_7100F5FDF0(dir);
        _64.update();
        if (_64.value <= sead::Mathf::epsilon()) {
            controller->sub_7100F5E7F0(0.0f);
            controller->sub_7100F5FB24(sead::Vector3f::zero);
            setFinished();
        }
    } else if (_45) {
        controller->sub_7100F5FB24(sead::Vector3f::zero);
        setFinished();
        return;
    } else {
        const auto& mtx = mActor->getMtx();
        sead::Vector3f front = mtx.getBase(2);
        front.y = 0.0f;
        front.normalize();

        sead::Vector3f move;
        if (auto* as_list = mActor->getASList())
            move = as_list->sub_710115D3B8();

        sead::Vector3f axis;
        f32 angle;
        ksys::util::sub_71011EEB08(&axis, &angle, front, _38, sead::Vector3f::ey);
        if (angle < sead::Mathf::abs(move.y)) {
            controller->sub_7100F5FB24({0.0f, angle * axis.y * 30.0f, 0.0f});
            _45 = true;
        } else if (isFinishedAS(0, 0)) {
            _45 = true;
        } else {
            controller->sub_7100F5FB24(move * 30.0f);
        }
    }
    controller->sub_7100F5EDD8(0.0f);
}

}  // namespace uking::action
