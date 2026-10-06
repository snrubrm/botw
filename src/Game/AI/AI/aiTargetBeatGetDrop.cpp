#include "Game/AI/AI/aiTargetBeatGetDrop.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

ksys::act::BaseProcLink* sub_71005E0F68(ksys::act::Actor* actor);

namespace uking::ai {

TargetBeatGetDrop::TargetBeatGetDrop(const InitArg& arg) : TargetBeatCheck(arg) {}

TargetBeatGetDrop::~TargetBeatGetDrop() = default;

bool TargetBeatGetDrop::init_(sead::Heap* heap) {
    return TargetBeatCheck::init_(heap);
}

void TargetBeatGetDrop::enter_(ksys::act::ai::InlineParamPack* params) {
    TargetBeatCheck::enter_(params);
    _6c = false;
}

void TargetBeatGetDrop::calc_() {
    if (isCurrentChild("未撃破")) {
        _60 = sub_71005D9330(mActor);
        TargetBeatCheck::calc_();
        return;
    }
    if (!_6c)
        _6c = sub_71005E0F68(mActor)->hasProcInCalcState();
    sub_71005BCCE0();
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (_50.hasProcInCalcState())
            sub_71005BCF48();
        else if (child->isFinished())
            setFinished();
        else
            setFailed();
    } else {
        child->isChangeable();
    }
}

// NON_MATCHING: the original computes &_40 before &_50 for `_40 = _50` (pre-C++17 operand order of an
// overloaded operator=); we compute the right-hand side first.
void TargetBeatGetDrop::sub_71005BCF48() {
    _40 = _50;
    _50.reset();
    ksys::act::ai::InlineParamPack params;
    params.addActor(_40, "TargetBait", -1);
    params.addBool(false, "IsNotice", -1);
    changeChild("ドロップ取得", &params);
}

void TargetBeatGetDrop::leave_() {
    TargetBeatCheck::leave_();
}

void TargetBeatGetDrop::loadParams_() {
    TargetBeatCheck::loadParams_();
    getStaticParam(&mSearchDist_s, "SearchDist");
}

bool TargetBeatGetDrop::isChangeable() const {
    if (isCurrentChild("ドロップ取得") && !_6c)
        return false;
    return ksys::act::ai::Ai::isChangeable();
}

}  // namespace uking::ai
