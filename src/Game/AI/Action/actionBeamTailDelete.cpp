#include "Game/AI/Action/actionBeamTailDelete.h"
#include <xlink2/xlink2Event.h>
#include "Game/Actor/actBeamBase.h"

namespace uking::action {

BeamTailDelete::BeamTailDelete(const InitArg& arg) : ksys::act::ai::Action(arg) {}

BeamTailDelete::~BeamTailDelete() = default;

bool BeamTailDelete::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void BeamTailDelete::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* beam = sead::DynamicCast<uking::act::Beam>(mActor))
        beam->sub_7100002BF8();
}

void BeamTailDelete::leave_() {
    ksys::act::ai::Action::leave_();
}

void BeamTailDelete::loadParams_() {}

void BeamTailDelete::calc_() {
    if (auto* beam = sead::DynamicCast<uking::act::Beam>(mActor)) {
        if (beam->_c48 && beam->_c48->getCreateId() == beam->_c50)
            return;
    }
    setFinished();
}

}  // namespace uking::action
