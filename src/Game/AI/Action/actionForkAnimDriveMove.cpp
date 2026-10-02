#include "Game/AI/Action/actionForkAnimDriveMove.h"
#include <gsys/gsysModelAccessKey.h>
#include <gsys/gsysModel.h>
#include <gsys/gsysModelUnit.h>
#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

ForkAnimDriveMove::ForkAnimDriveMove(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkAnimDriveMove::~ForkAnimDriveMove() = default;

bool ForkAnimDriveMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkAnimDriveMove::enter_(ksys::act::ai::InlineParamPack* params) {
    _30 = false;
    auto* as_list = mActor->getASList();
    if (!as_list) {
        setFailed();
        return;
    }

    if (!mTargetBone_s.isEmpty()) {
        sead::SafeString bone_name = "";
        const auto& key = as_list->_14;
        if (key.isValid()) {
            bone_name = mActor->getModel()
                            ->getUnits()
                            .unsafeAt(key.model_unit_index)
                            ->mModelUnit->getBoneName(key.bone_index);
        }
        if (bone_name != mTargetBone_s) {
            as_list->sub_710115CE44(mTargetBone_s);
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

void ForkAnimDriveMove::leave_() {
    if (_30) {
        _30 = false;
        mActor->getASList()->sub_710115D0AC();
    }
}

void ForkAnimDriveMove::loadParams_() {
    getStaticParam(&mTargetBone_s, "TargetBone");
}

void ForkAnimDriveMove::calc_() {
    auto* as_list = mActor->getASList();
    auto* controller = mActor->getCharacterController();
    if (!as_list || !controller) {
        setFailed();
        return;
    }
    act::sub_7100E7F318(as_list, controller, 1.0f);
}

}  // namespace uking::action
