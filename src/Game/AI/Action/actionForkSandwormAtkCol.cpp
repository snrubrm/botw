#include "Game/AI/Action/actionForkSandwormAtkCol.h"
#include "Game/AI/aiUnk_7102451120.h"
#include "KingSystem/ActorSystem/actActor.h"

void sub_7100720330(ksys::act::Actor* actor);
void sub_710072027C(ksys::act::Actor* actor, bool use_toss, u32 min_damage);

namespace uking::action {

ForkSandwormAtkCol::ForkSandwormAtkCol(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkSandwormAtkCol::~ForkSandwormAtkCol() = default;

bool ForkSandwormAtkCol::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: max selects the minimum damage without the original duplicated bool branches.
void ForkSandwormAtkCol::enter_(ksys::act::ai::InlineParamPack* params) {
    mFlags.set(Flag::Changeable);
    auto* actor = mActor;
    sub_710072022C(actor);
    sub_710072027C(actor, *mIsUseTossAt_s, sead::Mathi::max(1, *mMinDamage_s));
    if (*mIsColNoHitPlayer_s)
        sub_7100720814(actor, 0);
}

void ForkSandwormAtkCol::leave_() {
    auto* actor = mActor;
    sub_7100720254(actor);
    sub_7100720330(actor);
    if (*mIsColNoHitPlayer_s)
        sub_71007208EC(actor);
}

void ForkSandwormAtkCol::loadParams_() {
    getStaticParam(&mMinDamage_s, "MinDamage");
    getStaticParam(&mIsUseTossAt_s, "IsUseTossAt");
    getStaticParam(&mIsColNoHitPlayer_s, "IsColNoHitPlayer");
}

void ForkSandwormAtkCol::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
