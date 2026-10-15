#include "Game/Actor/AI/aiTargetStateSelect.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

TargetStateSelect::TargetStateSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

TargetStateSelect::~TargetStateSelect() = default;

bool TargetStateSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void TargetStateSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    if (sub_71005D91A0(mActor, 1.5f)) {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
        changeChild("対象泳ぎ", &pack);
    } else if (sub_71005D90E0(mActor)) {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
        changeChild("対象騎乗", &pack);
    } else {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
        changeChild("対象通常", &pack);
    }
}

void TargetStateSelect::calc_() {
    const bool has_target = sub_71005D8F28(mActor);
    auto* child = getCurrentChild();
    if (has_target)
        child->setDynamicParam(sub_71005D9330(mActor), "TargetPos");
    if (!child->isChangeable())
        return;
    if (!has_target) {
        setFailed();
        return;
    }
    if (sub_71005D91A0(mActor, 1.5f)) {
        if (!isCurrentChild("対象泳ぎ")) {
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
            changeChild("対象泳ぎ", &pack);
        }
    } else if (sub_71005D90E0(mActor)) {
        if (!isCurrentChild("対象騎乗")) {
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
            changeChild("対象騎乗", &pack);
        }
    } else if (!isCurrentChild("対象通常")) {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
        changeChild("対象通常", &pack);
    }
}

void TargetStateSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void TargetStateSelect::loadParams_() {}

bool TargetStateSelect::isFailed() const {
    return ksys::act::ai::Ai::isFailed() || getCurrentChild()->isFailed();
}

bool TargetStateSelect::isFinished() const {
    return ksys::act::ai::Ai::isFinished() || getCurrentChild()->isFinished();
}

bool TargetStateSelect::isChangeable() const {
    return ksys::act::ai::Ai::isChangeable() || getCurrentChild()->isChangeable();
}

}  // namespace uking::ai
