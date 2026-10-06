#include "Game/AI/Action/actionMoonMove.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Graphics/gfxUnk_710260af28.h"

namespace uking::action {

MoonMove::MoonMove(const InitArg& arg) : ksys::act::ai::Action(arg) {}

MoonMove::~MoonMove() = default;

bool MoonMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void MoonMove::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* list = mActor->getASList()) {
        list->startAnimationMaybe(-1.0f, -1.0f, "Wait", 0, 0, true);
        list->x_3(0, 0, &ksys::as::ASList::Unk2::sub_7101163298, 0.0f);
        list->startAnimationMaybe(-1.0f, -1.0f, "Change", 1, 0, true);
        list->x_3(1, 0, &ksys::as::ASList::Unk2::sub_7101163298, 0.0f);
    }
    Unk_710260af28::instance()->sub_7100F1ECE8(mActor->getModel());
    Unk_710260af28::instance()->sub_7100F1ED28(mActor->getModel(), false);
}

void MoonMove::leave_() {
    ksys::act::ai::Action::leave_();
}

void MoonMove::loadParams_() {}

void MoonMove::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
