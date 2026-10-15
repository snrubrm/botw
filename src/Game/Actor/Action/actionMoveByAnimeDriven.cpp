#include "Game/Actor/Action/actionMoveByAnimeDriven.h"
#include <gsys/gsysModelAccessKey.h>
#include <gsys/gsysModel.h>
#include <gsys/gsysModelUnit.h>
#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

MoveByAnimeDriven::MoveByAnimeDriven(const InitArg& arg) : ksys::act::ai::Action(arg) {}

MoveByAnimeDriven::~MoveByAnimeDriven() = default;

bool MoveByAnimeDriven::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void MoveByAnimeDriven::enter_(ksys::act::ai::InlineParamPack* params) {
    _50 = false;
    auto* as_list = mActor->getASList();
    if (!as_list) {
        setFailed();
        return;
    }

    playAS(m32(), *mIsIgnoreSameAS_s, 0, 0, -1.0f);
    if (!as_list->x_7(0, 0, &ksys::as::ASList::Unk2::sub_710002E82C)) {
        setFailed();
        return;
    }

    if (!mTargetBoneName_s.isEmpty()) {
        sead::SafeString bone_name = "";
        const auto& key = as_list->_14;
        if (key.isValid()) {
            bone_name = mActor->getModel()
                            ->getUnits()
                            .unsafeAt(key.model_unit_index)
                            ->mModelUnit->getBoneName(key.bone_index);
        }
        if (bone_name != mTargetBoneName_s) {
            as_list->sub_710115CE44(mTargetBoneName_s);
            _50 = true;
            if (!as_list->x_7(0, 0, &ksys::as::ASList::Unk2::sub_710002E82C) ||
                !as_list->_14.isValid()) {
                setFailed();
                return;
            }
        }
    }

    if (*mIsChangeable_s)
        mFlags.set(Flag::Changeable);
}

bool MoveByAnimeDriven::reenter_(ksys::act::ai::ActionBase* other, bool x) {
    if (!ksys::act::ai::Action::reenter_(other, true))
        return false;
    _50 = false;
    if (!sead::DynamicCast<MoveByAnimeDriven>(other))
        return false;

    if (!mTargetBoneName_s.isEmpty()) {
        auto* as_list = mActor->getASList();
        sead::SafeString bone_name = "";
        const auto& key = as_list->_14;
        if (key.isValid()) {
            bone_name = mActor->getModel()
                            ->getUnits()
                            .unsafeAt(key.model_unit_index)
                            ->mModelUnit->getBoneName(key.bone_index);
        }
        if (bone_name != mTargetBoneName_s) {
            as_list->sub_710115CE44(mTargetBoneName_s);
            _50 = true;
        }
    }
    return true;
}

void MoveByAnimeDriven::leave_() {
    if (_50) {
        _50 = false;
        mActor->getASList()->sub_710115D0AC();
    }
}

void MoveByAnimeDriven::loadParams_() {
    getStaticParam(&mIsChangeable_s, "IsChangeable");
    getStaticParam(&mIsIgnoreSameAS_s, "IsIgnoreSameAS");
    getStaticParam(&mASKeyName_s, "ASKeyName");
    getStaticParam(&mTargetBoneName_s, "TargetBoneName");
}

// NON_MATCHING: MotionType temporary spill and vector scheduling.
void MoveByAnimeDriven::calc_() {
    auto* as_list = mActor->getASList();
    auto* controller = mActor->getCharacterController();
    if (!as_list || !controller) {
        setFailed();
        return;
    }
    if (controller->sub_7100F5F0E4() == ksys::act::MotionType::Hover) {
        sead::Vector3f direction = as_list->sub_710115D2D4();
        sead::Vector3f angular_velocity = as_list->sub_710115D3B8();
        direction.setRotated(mActor->getMtx(), direction);
        const f32 speed = direction.normalize();
        if (direction == sead::Vector3f::zero)
            direction = controller->get64();
        controller->sub_7100F5EDD8(1.0f);
        controller->sub_7100F5EDE0(0.0f);
        controller->sub_7100F5EDBC(direction);
        controller->sub_7100F5E7F0(speed * 30.0f);
        angular_velocity *= 30.0f;
        controller->sub_7100F5FB24(angular_velocity);
    } else {
        m33();
    }
    if (as_list->x_1(0, 0) == m32() && isFinishedAS(0, 0))
        setFinished();
}

const char* MoveByAnimeDriven::m32() {
    return mASKeyName_s.cstr();
}

void MoveByAnimeDriven::m33() {
    auto* as_list = mActor->getASList();
    auto* controller = mActor->getCharacterController();
    if (as_list && controller)
        act::sub_7100E7F318(as_list, controller, 1.0f);
}

}  // namespace uking::action
