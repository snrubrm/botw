#include "Game/AI/AI/aiTargetBaitTypeSelect.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace uking::ai {

TargetBaitTypeSelect::TargetBaitTypeSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

TargetBaitTypeSelect::~TargetBaitTypeSelect() = default;

void TargetBaitTypeSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_71005BC0B4(params);
}

void TargetBaitTypeSelect::sub_71005BC0B4(ksys::act::ai::InlineParamPack* params) {
    auto* bait = sead::DynamicCast<Unk_7102370e70>(*mTargetBaitActorLink_a);
    if (bait && bait->mLink.hasProc()) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&bait->mLink, &accessor);
        if (accessor.hasTag(0xb5dc29d8u))
            changeChild("虫", params);
        else
            changeChild("その他", params);
        bait->mLink.reset();
        return;
    }
    changeChild("その他", params);
}

void TargetBaitTypeSelect::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (getCurrentChild()->isFinished())
            setFinished();
        else
            setFailed();
    }
}

void TargetBaitTypeSelect::loadParams_() {
    getAITreeVariable(&mTargetBaitActorLink_a, "TargetBaitActorLink");
}

}  // namespace uking::ai
