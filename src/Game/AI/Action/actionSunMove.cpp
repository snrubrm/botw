#include "Game/AI/Action/actionSunMove.h"
#include "KingSystem/Graphics/gfxUnk_710260af28.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

SunMove::SunMove(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SunMove::~SunMove() = default;

bool SunMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SunMove::enter_(ksys::act::ai::InlineParamPack* params) {
    Unk_710260af28::instance()->sub_7100F1ECE8(mActor->getModel());
    Unk_710260af28::instance()->sub_7100F1ED28(mActor->getModel(), false);
}

void SunMove::leave_() {
    ksys::act::ai::Action::leave_();
}

void SunMove::loadParams_() {}

void SunMove::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
