#include "Game/AI/Action/actionZoraHeroWaterFallJump.h"
#include "KingSystem/ActorSystem/AS/ASList.h"

namespace uking::action {

ZoraHeroWaterFallJump::ZoraHeroWaterFallJump(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ZoraHeroWaterFallJump::~ZoraHeroWaterFallJump() = default;

bool ZoraHeroWaterFallJump::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ZoraHeroWaterFallJump::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* as_list = mActor->getASList();
    auto* model = mActor->getModel();
    playAS(mASName_s.cstr(), false, 0, 0, -1.0f);
    if (as_list && model)
        as_list->sub_710115BAF8("Root");
}

void ZoraHeroWaterFallJump::leave_() {
    ksys::act::ai::Action::leave_();
}

void ZoraHeroWaterFallJump::loadParams_() {
    getStaticParam(&mASName_s, "ASName");
}

void ZoraHeroWaterFallJump::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
