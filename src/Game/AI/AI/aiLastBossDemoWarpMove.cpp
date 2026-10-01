#include "Game/AI/AI/aiLastBossDemoWarpMove.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

LastBossDemoWarpMove::LastBossDemoWarpMove(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

LastBossDemoWarpMove::~LastBossDemoWarpMove() = default;

bool LastBossDemoWarpMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void LastBossDemoWarpMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void LastBossDemoWarpMove::leave_() {
    ksys::act::ai::Ai::leave_();
}

void LastBossDemoWarpMove::loadParams_() {}

void LastBossDemoWarpMove::calc_() {
    auto* child = getCurrentChild();
    if (!child || (!child->isFinished() && !child->isFailed()))
        return;

    if (isCurrentChild("ワープ消失"))
        m35();
    else if (isCurrentChild("ワープ移動"))
        setFinished();
}

void LastBossDemoWarpMove::m34() {
    ksys::act::ai::InlineParamPack pack;
    pack.addBool(true, "IsPartsWarpEffectSync", -1);
    changeChild("ワープ消失", &pack);
}

void LastBossDemoWarpMove::m35() {
    changeChild("ワープ移動");
}

}  // namespace uking::ai
