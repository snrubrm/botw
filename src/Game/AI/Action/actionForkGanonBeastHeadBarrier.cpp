#include "Game/AI/Action/actionForkGanonBeastHeadBarrier.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace uking::action {

ForkGanonBeastHeadBarrier::ForkGanonBeastHeadBarrier(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ForkGanonBeastHeadBarrier::~ForkGanonBeastHeadBarrier() = default;

bool ForkGanonBeastHeadBarrier::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkGanonBeastHeadBarrier::enter_(ksys::act::ai::InlineParamPack* params) {
    mFlags.set(Flag::Changeable);
}

void ForkGanonBeastHeadBarrier::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkGanonBeastHeadBarrier::loadParams_() {
    getStaticParam(&mBarrierRad_s, "BarrierRad");
    getStaticParam(&mBarrierFront_s, "BarrierFront");
    getStaticParam(&mBarrierBack_s, "BarrierBack");
    getStaticParam(&mBarrierHeight_s, "BarrierHeight");
    getStaticParam(&mBarrierHeightMax_s, "BarrierHeightMax");
}

// NON_MATCHING: identical instructions; the original computes `this + 0x48` (the sender) after the lock address and spin
// load, we compute it before.
void ForkGanonBeastHeadBarrier::calc_() {
    if (!sub_7100154628())
        return;

    auto* actor = mActor;
    _48.x(actor, actor->getMtx().getTranslation());
    _48.sub_710070DCC0(&ksys::act::PlayerInfo::getSomeProcLink(), false);

    Unk_71012419b4 handle;
    xlinkSearchAndEmit(mActor, "Shockwave", 2, &handle);
    handle.sub_71012419B4(getPlayerPosition());
}

}  // namespace uking::action
