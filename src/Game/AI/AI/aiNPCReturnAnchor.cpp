#include "Game/AI/AI/aiNPCReturnAnchor.h"
#include "Game/AI/aiUnk_71007130BC.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actSchedule.h"

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
