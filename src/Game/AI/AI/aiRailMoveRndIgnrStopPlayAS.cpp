#include "Game/AI/AI/aiRailMoveRndIgnrStopPlayAS.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

RailMoveRndIgnrStopPlayAS::RailMoveRndIgnrStopPlayAS(const InitArg& arg)
    : RailMoveRandomIgnoreStop(arg) {}

RailMoveRndIgnrStopPlayAS::~RailMoveRndIgnrStopPlayAS() = default;

bool RailMoveRndIgnrStopPlayAS::init_(sead::Heap* heap) {
    return RailMoveRandomIgnoreStop::init_(heap);
}

void RailMoveRndIgnrStopPlayAS::enter_(ksys::act::ai::InlineParamPack* params) {
    RailMoveRandomIgnoreStop::enter_(params);
}

void RailMoveRndIgnrStopPlayAS::leave_() {
    RailMoveRandomIgnoreStop::leave_();
}

void RailMoveRndIgnrStopPlayAS::loadParams_() {
    RailMoveRandomIgnoreStop::loadParams_();
}

void RailMoveRndIgnrStopPlayAS::calc_() {
    RailMoveRandomIgnoreStop::calc_();
    auto* child = getCurrentChild();
    if ((child->isFinished() || child->isFailed()) && isCurrentChild("ＡＳ再生"))
        sub_710032C088();
}

void RailMoveRndIgnrStopPlayAS::m39() {
    const char* as_key = sub_7100EEF358(_40._8.rail, _40._30.progress);
    if (!as_key || sead::SafeString(as_key).isEmpty()) {
        RailMoveRandomIgnoreStop::m39();
        return;
    }

    ksys::act::ai::InlineParamPack params;
    params.addString(as_key, "DynASKey", -1);
    changeChild("ＡＳ再生", &params);
}

}  // namespace uking::ai
