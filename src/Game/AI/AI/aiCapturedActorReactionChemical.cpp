#include "Game/AI/AI/aiCapturedActorReactionChemical.h"
#include "KingSystem/ActorSystem/Profiles/actDynamicActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

CapturedActorReactionChemical::CapturedActorReactionChemical(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

CapturedActorReactionChemical::~CapturedActorReactionChemical() = default;

bool CapturedActorReactionChemical::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void CapturedActorReactionChemical::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = sead::DynamicCast<ksys::act::DynamicActor>(mActor);
    if (actor && actor->m151(3)) {
        ksys::act::ai::InlineParamPack pack;
        pack.addBool(false, "IsEnableThrowOffAttack", -1);
        changeChild("凍結", &pack);
    } else {
        actor = sead::DynamicCast<ksys::act::DynamicActor>(mActor);
        if (actor && actor->m151(4)) {
            ksys::act::ai::InlineParamPack pack;
            pack.addBool(false, "IsEnableThrowOffAttack", -1);
            changeChild("感電", &pack);
        } else {
            changeChild("通常", nullptr);
        }
    }
}

void CapturedActorReactionChemical::leave_() {
    ksys::act::ai::Ai::leave_();
}

void CapturedActorReactionChemical::calc_() {
    auto* actor = sead::DynamicCast<ksys::act::DynamicActor>(mActor);
    if (actor && actor->m151(3)) {
        if (!*mOnEnterOnly_s && !isCurrentChild("凍結")) {
            ksys::act::ai::InlineParamPack pack;
            pack.addBool(false, "IsEnableThrowOffAttack", -1);
            changeChild("凍結", &pack);
            return;
        }
    } else {
        actor = sead::DynamicCast<ksys::act::DynamicActor>(mActor);
        if (actor && actor->m151(4)) {
            if (!*mOnEnterOnly_s && !isCurrentChild("感電")) {
                ksys::act::ai::InlineParamPack pack;
                pack.addBool(false, "IsEnableThrowOffAttack", -1);
                changeChild("感電", &pack);
                return;
            }
        } else if (!isCurrentChild("通常")) {
            changeChild("通常", nullptr);
            return;
        }
    }
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed())
        changeChild("通常", nullptr);
}

void CapturedActorReactionChemical::loadParams_() {
    getStaticParam(&mOnEnterOnly_s, "OnEnterOnly");
}

}  // namespace uking::ai
