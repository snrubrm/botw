#include "Game/AI/Action/actionPauseMenuPlayerWait.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

PauseMenuPlayerWait::PauseMenuPlayerWait(const InitArg& arg) : ksys::act::ai::Action(arg) {}

PauseMenuPlayerWait::~PauseMenuPlayerWait() = default;

bool PauseMenuPlayerWait::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void PauseMenuPlayerWait::enter_(ksys::act::ai::InlineParamPack* params) {
    mFlags.set(Flag::Changeable);
    playAS("PauseMenuWait", true, 0, 0, -1.0f);
    playAS("FaceDefault", true, 1, 0, -1.0f);
    playAS("SkinColor", true, 2, 0, -1.0f);
    if (auto* as_list = mActor->getASList()) {
        as_list->x_3(2, 0, &ksys::as::ASList::Unk2::sub_7101163298,
                     as_list->x_5(2, 0, &ksys::as::ASList::Unk2::sub_710116323C));
    }
    mActor->x_22(sead::Vector3f::zero, sead::Vector3f::zero);
}

void PauseMenuPlayerWait::leave_() {
    ksys::act::ai::Action::leave_();
}

void PauseMenuPlayerWait::loadParams_() {}

void PauseMenuPlayerWait::calc_() {
    mActor->x_22(sead::Vector3f::zero, sead::Vector3f::zero);
}

}  // namespace uking::action
