#include "Game/AI/AI/aiSunAI.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Graphics/gfxUnk_710260af28.h"

namespace uking::ai {

SunAI::SunAI(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

bool SunAI::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SunAI::enter_(ksys::act::ai::InlineParamPack* params) {
    Unk_710260af28::instance()->sub_7100F1ECE8(mActor->getModel());
    Unk_710260af28::instance()->sub_7100F1ED28(mActor->getModel(), false);
    changeChild("通常");
}

void SunAI::calc_() {}

void SunAI::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SunAI::loadParams_() {}

}  // namespace uking::ai
