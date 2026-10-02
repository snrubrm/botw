#include "Game/AI/Action/actionForkAnimDriveFreeMoving.h"
#include <gsys/gsysModelAccessKey.h>
#include <gsys/gsysModel.h>
#include <gsys/gsysModelUnit.h>
#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

ForkAnimDriveFreeMoving::ForkAnimDriveFreeMoving(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkAnimDriveFreeMoving::~ForkAnimDriveFreeMoving() = default;

bool ForkAnimDriveFreeMoving::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkAnimDriveFreeMoving::enter_(ksys::act::ai::InlineParamPack* params) {
    _30 = false;
    auto* as_list = mActor->getASList();
    if (!as_list) {
        setFailed();
        return;
    }

    if (!_20.isEmpty()) {
        sead::SafeString bone_name = "";
        const auto& key = as_list->_14;
        if (key.isValid()) {
            bone_name = mActor->getModel()
                            ->getUnits()
                            .unsafeAt(key.model_unit_index)
                            ->mModelUnit->getBoneName(key.bone_index);
        }
        if (bone_name != _20) {
            as_list->sub_710115CE44(_20);
            _30 = true;
            if (!as_list->x_7(0, 0, &ksys::as::ASList::Unk2::sub_710002E82C) ||
                !as_list->_14.isValid()) {
                setFailed();
                return;
            }
        }
    }
    mFlags.set(Flag::Changeable);
}

void ForkAnimDriveFreeMoving::leave_() {
    if (_30) {
        _30 = false;
        mActor->getASList()->sub_710115D0AC();
    }
}

void ForkAnimDriveFreeMoving::loadParams_() {}

void ForkAnimDriveFreeMoving::calc_() {
    auto* as_list = mActor->getASList();
    auto* controller = mActor->getCharacterController();
    if (!as_list || !controller) {
        setFailed();
        return;
    }
    act::sub_7100E7F6FC(as_list, controller, 1.0f);
}

}  // namespace uking::action
