#include "Game/AI/Action/actionAnimMatrixDriven.h"
#include <gsys/gsysModelAccessKey.h>
#include <gsys/gsysModel.h>
#include <gsys/gsysModelUnit.h>
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

AnimMatrixDriven::AnimMatrixDriven(const InitArg& arg) : ksys::act::ai::Action(arg) {}

AnimMatrixDriven::~AnimMatrixDriven() = default;

bool AnimMatrixDriven::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void AnimMatrixDriven::enter_(ksys::act::ai::InlineParamPack* params) {
    _58 = false;
    if (*mIsChangeable_d)
        mFlags.set(Flag::Changeable);
    else
        mFlags.reset(Flag::Changeable);
    auto* as_list = mActor->getASList();
    if (!as_list) {
        setFailed();
        return;
    }

    playAS(mASName_d.cstr(), *mIsIgnoreSame_d, *mASSlot_d, *mSequenceBank_d, -1.0f);
    if (*mStartFrame_d >= 0.0f) {
        mActor->getASList()->x_3(*mASSlot_d, *mSequenceBank_d,
                                 &ksys::as::ASList::Unk2::sub_7101163298, *mStartFrame_d);
    }

    sead::SafeString bone_name = "";
    const auto& key = as_list->_14;
    if (key.isValid()) {
        bone_name = mActor->getModel()
                        ->getUnits()
                        .unsafeAt(key.model_unit_index)
                        ->mModelUnit->getBoneName(key.bone_index);
    }
    if (bone_name != "Root") {
        as_list->sub_710115CE44("Root");
        _58 = true;
        if (!as_list->x_7(0, 0, &ksys::as::ASList::Unk2::sub_710002E82C) ||
            !as_list->_14.isValid()) {
            setFailed();
            return;
        }
    }
    _59 = true;
}

void AnimMatrixDriven::leave_() {
    if (_58) {
        _58 = false;
        mActor->getASList()->sub_710115D0AC();
    }
}

void AnimMatrixDriven::loadParams_() {
    getDynamicParam(&mASSlot_d, "ASSlot");
    getDynamicParam(&mSequenceBank_d, "SequenceBank");
    getDynamicParam(&mStartFrame_d, "StartFrame");
    getDynamicParam(&mIsIgnoreSame_d, "IsIgnoreSame");
    getDynamicParam(&mIsChangeable_d, "IsChangeable");
    getDynamicParam(&mASName_d, "ASName");
}

void AnimMatrixDriven::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
