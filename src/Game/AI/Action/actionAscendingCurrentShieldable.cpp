#include "Game/AI/Action/actionAscendingCurrentShieldable.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Sound/sndMgr.h"
#include "KingSystem/Utils/InitTimeInfo.h"

namespace uking::action {

namespace {
ksys::util::InitConstants sInitConstants;
ksys::util::InitTimeInfo sInitTimeInfo;
}  // namespace

AscendingCurrentShieldable::AscendingCurrentShieldable(const InitArg& arg)
    : AscendingCurrent(arg) {}

AscendingCurrentShieldable::~AscendingCurrentShieldable() = default;

bool AscendingCurrentShieldable::init_(sead::Heap* heap) {
    return AscendingCurrent::init_(heap);
}

void AscendingCurrentShieldable::enter_(ksys::act::ai::InlineParamPack* params) {
    AscendingCurrent::enter_(params);
}

void AscendingCurrentShieldable::leave_() {
    AscendingCurrent::leave_();
}

void AscendingCurrentShieldable::loadParams_() {
    AscendingCurrent::loadParams_();
}

void AscendingCurrentShieldable::calc_() {
    AscendingCurrent::calc_();
    if (_68.isActive()) {
        const f32 volume = ksys::snd::SoundMgr::instance()->_a8->sub_710104B558(mActor);
        if (volume >= 0.0f)
            _68.setVolumeScale(sead::Mathf::clampMin(volume, 0.0f));
    }
}

}  // namespace uking::action
