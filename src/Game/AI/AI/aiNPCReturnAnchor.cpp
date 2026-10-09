#include "Game/AI/AI/aiNPCReturnAnchor.h"
#include "Game/AI/aiUnk_71007130BC.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actSchedule.h"
#include "KingSystem/ActorSystem/AS/ASList.h"

namespace uking::ai {

NPCReturnAnchor::NPCReturnAnchor(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

NPCReturnAnchor::~NPCReturnAnchor() = default;

bool NPCReturnAnchor::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void NPCReturnAnchor::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void NPCReturnAnchor::leave_() {
    ksys::act::ai::Ai::leave_();
}

void NPCReturnAnchor::loadParams_() {}

// 0x71004d6e7c
// NON_MATCHING: conditional schedule-field address selection uses reversed registers.
void NPCReturnAnchor::sub_71004D6E7C() {
    const bool bad_weather = wm::callIsRainingOrSnowingOrThunderStorm(true);
    auto* schedule = mActor->getSchedule();
    const sead::SafeString current = mActor->getASList()->sub_710115ECF4(0x3b, 1);
    const char* posture = sub_710071300C(bad_weather ? schedule->_1b8 : schedule->_1b4).getStringTop();
    if (current == posture) {
        sub_71004D70D8();
        return;
    }
    ksys::act::ai::InlineParamPack params;
    params.addString(posture, "Posture", -1);
    changeChild("姿勢変更", &params);
}

void NPCReturnAnchor::sub_71004D70D8() {
    const bool bad_weather = wm::callIsRainingOrSnowingOrThunderStorm(true);
    auto* schedule = mActor->getSchedule();
    const auto& name = bad_weather ? schedule->_170 : schedule->_160;
    const char* name_top = name.getStringTop();
    ksys::act::ai::InlineParamPack params;
    params.addString(name_top, "DynASName", -1);
    changeChild("到着", &params);
    setFinished();
}

void NPCReturnAnchor::calc_() {
    if (isCurrentChild("振り向く")) {
        if (getCurrentChild()->isFinished())
            sub_71004D6E7C();
    } else if (isCurrentChild("姿勢変更")) {
        if (getCurrentChild()->isFinished()) {
            sub_71004D70D8();
            setFinished();
        }
    }
}

}  // namespace uking::ai
