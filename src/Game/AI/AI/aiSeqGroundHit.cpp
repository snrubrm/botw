#include "Game/AI/AI/aiSeqGroundHit.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"

namespace uking::ai {

SeqGroundHit::SeqGroundHit(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SeqGroundHit::~SeqGroundHit() = default;

bool SeqGroundHit::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SeqGroundHit::enter_(ksys::act::ai::InlineParamPack* params) {
    changeChild("空中", params);
}

void SeqGroundHit::calc_() {
    if (!isCurrentChild("空中"))
        return;

    auto* child = getCurrentChild();
    if (*mIsCheckChangeable_s && !child->isChangeable())
        return;

    if (sub_7100562078() || child->isFinished() || child->isFailed())
        changeChild("地上");
}

// NON_MATCHING: the original keeps every case separate with shared `true` / `false` returns (the
// isLanded call is not a tail call and the Atomic flag is tested with cbnz); ours tail-calls the last
// call and keeps the results in w20 (cset).
bool SeqGroundHit::sub_7100562078() {
    auto* actor = mActor;
    bool hit = false;
    switch (*mCheckType_s) {
    case 0:
        hit = isBgGroundHit(actor, false);
        break;
    case 1:
        hit = sub_71007A4178(actor, true) || isBgGroundHit(actor, true) ||
              isLandedMaybe(actor, true) || actor->get68f();
        break;
    case 2:
        hit = actor->get68f();
        break;
    case 3:
        hit = isBgGroundHit(actor, true) || isLandedMaybe(actor, true) || actor->get68f();
        break;
    case 4:
        hit = isBgGroundHit(actor, true) || isLandedMaybe(actor, true);
        break;
    }
    return hit;
}

bool SeqGroundHit::isFailed() const {
    return ksys::act::ai::Ai::isFailed() ||
           (getCurrentChild()->isFailed() && (isCurrentChild("地上") || *mIsNoHitEnd_s));
}

bool SeqGroundHit::isFinished() const {
    return ksys::act::ai::Ai::isFinished() ||
           (getCurrentChild()->isFinished() && (isCurrentChild("地上") || *mIsNoHitEnd_s));
}

void SeqGroundHit::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SeqGroundHit::loadParams_() {
    getStaticParam(&mCheckType_s, "CheckType");
    getStaticParam(&mIsCheckChangeable_s, "IsCheckChangeable");
    getStaticParam(&mIsNoHitEnd_s, "IsNoHitEnd");
}

}  // namespace uking::ai
