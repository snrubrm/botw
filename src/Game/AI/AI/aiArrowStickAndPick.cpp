#include "Game/AI/AI/aiArrowStickAndPick.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

ArrowStickAndPick::ArrowStickAndPick(const InitArg& arg) : CommonPickedItem(arg) {}

ArrowStickAndPick::~ArrowStickAndPick() { ; }

void ArrowStickAndPick::enter_(ksys::act::ai::InlineParamPack* params) {
    _110 = false;
    CommonPickedItem::enter_(params);
}

void ArrowStickAndPick::loadParams_() {
    CommonPickedItem::loadParams_();
    getDynamicParam(&mStickPos_d, "StickPos");
    getDynamicParam(&mStickPosDiv_d, "StickPosDiv");
    getDynamicParam(&mStickActor_d, "StickActor");
    getDynamicParam(&mStickBodyName_d, "StickBodyName");
}

void ArrowStickAndPick::m37() {
    if (_110)
        return;
    _110 = true;
    CommonPickedItem::m37();
}

void ArrowStickAndPick::m38() {
    sub_7100355A14();
    ksys::act::ai::InlineParamPack params;
    params.addVec3(*mStickPos_d, "StickPos", -1);
    params.addVec3(*mStickPosDiv_d, "StickPosDiv", -1);
    params.addActor(*mStickActor_d, "StickActor", -1);
    params.addString(mStickBodyName_d, "StickBodyName", -1);
    changeChild("通常", &params);
}

}  // namespace uking::ai
