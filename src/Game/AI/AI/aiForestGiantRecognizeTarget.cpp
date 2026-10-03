#include "Game/AI/AI/aiForestGiantRecognizeTarget.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

ForestGiantRecognizeTarget::ForestGiantRecognizeTarget(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

ForestGiantRecognizeTarget::~ForestGiantRecognizeTarget() = default;

bool ForestGiantRecognizeTarget::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void ForestGiantRecognizeTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    if (!mActor->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_2000000)) {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
        changeChild("気づき", &pack);
    } else {
        changeToFound();
    }
    mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_2000000);
    mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_1000000);
}

void ForestGiantRecognizeTarget::changeToFound() {
    sub_71005DB3EC(mActor);
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    changeChild("発見", &pack);
}

// NON_MATCHING: ours folds `&mActor` (this + 8) into a pre-indexed load / shared pointer after the
// accessor block; the original reloads `[this + 8]` each time (addressing-mode choice only)
void ForestGiantRecognizeTarget::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("気づき")) {
            changeToFound();
        } else if (child->isFinished()) {
            setFinished();
        } else {
            setFailed();
        }
        return;
    }
    if (child->isChangeable()) {
        auto& link = sub_71005D94AC(mActor);
        if (link.hasProc()) {
            ksys::act::ActorConstDataAccess accessor;
            ksys::act::acquireActor(&link, &accessor);
            if (accessor.sub_7100D10E6C(26)) {
                setFinished();
                return;
            }
        }
    }
    child->setDynamicParam(sub_71005D9330(mActor), "TargetPos");
    if (isCurrentChild("気づき"))
        sub_71005DB1D8(mActor, sub_71005D9330(mActor));
}

void ForestGiantRecognizeTarget::leave_() {
    sub_71005DB3EC(mActor);
}

void ForestGiantRecognizeTarget::loadParams_() {}

}  // namespace uking::ai
