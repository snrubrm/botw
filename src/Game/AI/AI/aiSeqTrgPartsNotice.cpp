#include "Game/AI/AI/aiSeqTrgPartsNotice.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace uking::ai {

SeqTrgPartsNotice::SeqTrgPartsNotice(const InitArg& arg) : SeqTwoAction(arg) {}

// The original keeps the vtable store that a defaulted destructor drops (same form as upstream's
// GameDataFlagSelector::~GameDataFlagSelector() { ; }, commit 96101229).
SeqTrgPartsNotice::~SeqTrgPartsNotice() {
    ;
}

bool SeqTrgPartsNotice::init_(sead::Heap* heap) {
    return SeqTwoAction::init_(heap);
}

void SeqTrgPartsNotice::enter_(ksys::act::ai::InlineParamPack* params) {
    SeqTwoAction::enter_(params);
}

void SeqTrgPartsNotice::calc_() {
    if (isFinished() || isFailed())
        return;

    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (*mParams.mIsFinishByNoNoticeActionEnd_s) {
            if (child->isFinished())
                setFinished();
            else
                setFailed();
            return;
        }
    } else if (child->isChangeable() && isCurrentChild("先行動")) {
        if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
            auto& link = enemy->getActorPartsActor(mParams.mPartsName_s);
            if (!link.hasProcInCalcState()) {
                changeChild("後行動");
                return;
            }
            ksys::act::ActorConstDataAccess accessor;
            ksys::act::acquireActor(&link, &accessor);
            if (accessor.sub_7100D10E6C(25)) {
                changeChild("後行動");
                return;
            }
        }
    }

    SeqTwoAction::calc_();
}

void SeqTrgPartsNotice::leave_() {
    SeqTwoAction::leave_();
}

void SeqTrgPartsNotice::loadParams_() {
    SeqTwoAction::loadParams_();
    getStaticParam(&mParams.mPartsName_s, "PartsName");
    getStaticParam(&mParams.mIsFinishByNoNoticeActionEnd_s, "IsFinishByNoNoticeActionEnd");
}

}  // namespace uking::ai
