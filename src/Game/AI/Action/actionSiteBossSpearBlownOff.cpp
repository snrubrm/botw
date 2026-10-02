#include "Game/AI/Action/actionSiteBossSpearBlownOff.h"
#include "Game/AI/aiUnk_71007368A4.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

SiteBossSpearBlownOff::SiteBossSpearBlownOff(const InitArg& arg) : SiteBossBowBlowOff(arg) {}

SiteBossSpearBlownOff::~SiteBossSpearBlownOff() = default;

bool SiteBossSpearBlownOff::init_(sead::Heap* heap) {
    return SiteBossBowBlowOff::init_(heap);
}

void SiteBossSpearBlownOff::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F5F458(ksys::act::MotionType::Hover);
    SiteBossBowBlowOff::enter_(params);

    const auto& mtx = mActor->getMtx();
    const f32 angle = sead::Mathf::rad2deg(
        std::atan2(mtx(1, 2), std::sqrt(mtx(0, 2) * mtx(0, 2) + mtx(2, 2) * mtx(2, 2))));
    mActor->getASList()->x_6(9, 0, angle);
    playAS("DownWait", true, 0, 0, -1.0f);
}

void SiteBossSpearBlownOff::leave_() {
    SiteBossBowBlowOff::leave_();
}

void SiteBossSpearBlownOff::loadParams_() {
    SiteBossBowBlowOff::loadParams_();
    getStaticParam(&mDownTimeAtLater_s, "DownTimeAtLater");
}

void SiteBossSpearBlownOff::calc_() {
    SiteBossBowBlowOff::calc_();
}

s32 SiteBossSpearBlownOff::m37() {
    s32 time = SiteBossBowBlowOff::m37();
    if (checkHpRate(mActor, 0.5f))
        time += *mDownTimeAtLater_s;
    return time;
}

}  // namespace uking::action
