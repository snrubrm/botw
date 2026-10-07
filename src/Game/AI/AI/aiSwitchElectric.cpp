#include "Game/AI/AI/aiSwitchElectric.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/System/VFR.h"

namespace uking::ai {

SwitchElectric::SwitchElectric(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

bool SwitchElectric::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SwitchElectric::enter_(ksys::act::ai::InlineParamPack* params) {
    changeChild("オフ");
}

void SwitchElectric::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SwitchElectric::loadParams_() {
    getStaticParam(&mElecReq_s, "ElecReq");
    getStaticParam(&mVolReq_s, "VolReq");
}

void SwitchElectric::calc_() {
    auto* child = getCurrentChild();
    auto* chemical = mActor->getChemicalStuff();
    if (!child->isChangeable() && !child->isFinished() && !child->isFailed())
        return;

    const f32 energy =
        chemical->sub_7100D945BC(*mElecReq_s, *mVolReq_s, ksys::VFR::instance()->getDeltaFrame());
    if (!isCurrentChild("オン") && energy >= 1.0f) {
        changeChild("オン");
        return;
    }
    if (!isCurrentChild("オフ") && energy < 1.0f)
        changeChild("オフ");
}

}  // namespace uking::ai
