#include "Game/AI/Action/actionSiteBossCreateIceSplinter.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

SiteBossCreateIceSplinter::SiteBossCreateIceSplinter(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

SiteBossCreateIceSplinter::~SiteBossCreateIceSplinter() = default;

bool SiteBossCreateIceSplinter::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SiteBossCreateIceSplinter::enter_(ksys::act::ai::InlineParamPack* params) {
    playAS(mASName_s.cstr(), true, 0, 0, -1.0f);
    _38 = false;
    _44[1] = 0;
}

void SiteBossCreateIceSplinter::leave_() {
    ksys::act::ai::Action::leave_();
}

void SiteBossCreateIceSplinter::loadParams_() {
    getStaticParam(&mASName_s, "ASName");
    getDynamicParam(&mIgnitionNum_d, "IgnitionNum");
}

bool SiteBossCreateIceSplinter::isFinished() const {
    if (mActor->getASList()->x(0x47, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011637EC, true) ||
        ksys::act::ai::ActionBase::isFinished()) {
        return true;
    }
    return isFinishedAS(0, 0);
}

void SiteBossCreateIceSplinter::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
