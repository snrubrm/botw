#include "Game/AI/AI/aiPriestBossCloneBananaMode.h"
#include "Game/AI/aiUnk_7102450fa8.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

PriestBossCloneBananaMode::PriestBossCloneBananaMode(const InitArg& arg)
    : PriestBossBananaMode(arg) {}

PriestBossCloneBananaMode::~PriestBossCloneBananaMode() = default;

bool PriestBossCloneBananaMode::init_(sead::Heap* heap) {
    return PriestBossBananaMode::init_(heap);
}

void PriestBossCloneBananaMode::enter_(ksys::act::ai::InlineParamPack* params) {
    sead::Vector3f target_pos = sead::Vector3f::zero;
    if (sub_7100505BE4()->_28.hasProc()) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&sub_7100505BE4()->_28, &accessor);
        accessor.getActorMtx().getTranslation(target_pos);
    }

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(target_pos, "TargetPos", -1);
    pack.addActor(sub_7100505BE4()->_28, "TargetActor", -1);
    changeChild("バナナ夢中", &pack);
    mFlags.set(ksys::act::ai::ActionBase::Flag::Changeable);
}

// NON_MATCHING: stack slots of the Flag temporaries (the original shares the string temporary's)
void PriestBossCloneBananaMode::calc_() {
    if (!isCurrentChild("バナナ夢中")) {
        auto* child = getCurrentChild();
        if (child->isFinished() || child->isFailed())
            setFinished();
        return;
    }

    if (isChangeable() &&
        !sub_7100505BE4()->_78.isOnBit(Unk_7102450fa8::Flag(Unk_7102450fa8::Flag::_8))) {
        changeChild("解除");
        return;
    }

    if (!sub_7100505BE4()->_78.isOnBit(Unk_7102450fa8::Flag(Unk_7102450fa8::Flag::_7)))
        return;

    sead::Vector3f target_pos = sead::Vector3f::zero;
    if (sub_7100505BE4()->_28.hasProc()) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&sub_7100505BE4()->_28, &accessor);
        accessor.getActorMtx().getTranslation(target_pos);
    }
    getCurrentChild()->setDynamicParam(target_pos, "TargetPos");
    getCurrentChild()->setDynamicParamImpl(sub_7100505BE4()->_28, "TargetActor",
                                           &ksys::act::ai::ParamPack::setActor);
}

void PriestBossCloneBananaMode::leave_() {
    PriestBossBananaMode::leave_();
}

void PriestBossCloneBananaMode::loadParams_() {
    PriestBossBananaMode::loadParams_();
}

}  // namespace uking::ai
