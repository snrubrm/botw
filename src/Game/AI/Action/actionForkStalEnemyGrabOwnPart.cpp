#include "Game/AI/Action/actionForkStalEnemyGrabOwnPart.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_7100724C64.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

ForkStalEnemyGrabOwnPart::ForkStalEnemyGrabOwnPart(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ForkStalEnemyGrabOwnPart::~ForkStalEnemyGrabOwnPart() = default;

bool ForkStalEnemyGrabOwnPart::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: one instruction — ours tests the acquireActor result as `eor + tbnz`
// (clang's default lowering for a named bool, verified in isolation); the original has a
// plain `tbz`, which needs the call result tested directly — impossible here since the call
// precedes the target check. Everything else matches.
void ForkStalEnemyGrabOwnPart::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
    _48 = false;
    _49 = false;
    mFlags.set(Flag::Changeable);
    if (!sub_7100724D7C(mActor))
        setFailed();
    auto* actor = mActor;
    if (!actor->getConnectedCalcChild()) {
        auto* link = &sub_7100724F08(actor, *mPartIndex_d);
        auto* proc = link->getProc(nullptr, nullptr);
        auto* target =
            sead::IsDerivedFrom<ksys::act::Actor>(proc) ? static_cast<ksys::act::Actor*>(proc)
                                                        : nullptr;
        ksys::act::ActorConstDataAccess accessor;
        if (link->hasProc()) {
            bool acquired = ksys::act::acquireActor(link, &accessor);
            if (target) {
                if (acquired) {
                    if (!accessor.isStateSleep()) {
                        setFailed();
                    } else {
                        accessor.setThisActorAsChild(actor, false);
                        sub_71005DC208(actor, target, 0);
                        sub_71005DC41C(target);
                    }
                }
            }
        }
    }
}

void ForkStalEnemyGrabOwnPart::leave_() {
    auto* actor = mActor;
    if (_48 && actor->getConnectedCalcChild()) {
        if (auto* child = sead::DynamicCast<ksys::act::Actor>(actor->getConnectedCalcChild()))
            sub_71005DC41C(child);
    }
    if (_49) {
        _49 = false;
        sub_71007275C8(sub_7100724D7C(actor));
    }
}

void ForkStalEnemyGrabOwnPart::loadParams_() {
    getStaticParam(&mSeqBank_s, "SeqBank");
    getStaticParam(&mTargetBone_s, "TargetBone");
    getStaticParam(&mBoneName_s, "BoneName");
    getDynamicParam(&mPartIndex_d, "PartIndex");
}

void ForkStalEnemyGrabOwnPart::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
