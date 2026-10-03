#include "Game/AI/AI/aiMoonAI.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Graphics/gfxUnk_710260af28.h"

namespace uking::ai {

MoonAI::MoonAI(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

bool MoonAI::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void MoonAI::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* as_list = mActor->getASList()) {
        as_list->startAnimationMaybe(-1.0f, -1.0f, "Wait", 0, 0, true);
        as_list->x_3(0, 0, &ksys::as::ASList::Unk2::sub_7101163298, 0.0f);
        as_list->startAnimationMaybe(-1.0f, -1.0f, "Change", 1, 0, true);
        as_list->x_3(1, 0, &ksys::as::ASList::Unk2::sub_7101163298, 0.0f);
    }
    Unk_710260af28::instance()->sub_7100F1ECE8(mActor->getModel());
    Unk_710260af28::instance()->sub_7100F1ED28(mActor->getModel(), false);
    changeChild("通常");
}

void MoonAI::calc_() {}

void MoonAI::leave_() {
    ksys::act::ai::Ai::leave_();
}

void MoonAI::loadParams_() {}

}  // namespace uking::ai
