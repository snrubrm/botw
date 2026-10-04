#include "Game/AI/Action/actionGetItemAnotherActor.h"

namespace uking::act {
struct WeaponModifierInfo;
}

// Declaration-only helpers; their original source namespace is unknown.
bool actorHasTagCanGetPouch(const sead::SafeString& actor_name);
void getDemoGetAnotherActor(ksys::act::Actor* actor, const sead::SafeString& actor_name,
                           bool can_get_pouch, bool option, uking::act::WeaponModifierInfo* modifier);

namespace uking::action {

GetItemAnotherActor::GetItemAnotherActor(const InitArg& arg) : ksys::act::ai::Action(arg) {}

GetItemAnotherActor::~GetItemAnotherActor() = default;

bool GetItemAnotherActor::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void GetItemAnotherActor::enter_(ksys::act::ai::InlineParamPack* params) {
    m32(mGetActorName_d);
    mFlags.set(Flag::Changeable);
}

void GetItemAnotherActor::leave_() {
    ksys::act::ai::Action::leave_();
}

void GetItemAnotherActor::loadParams_() {
    getDynamicParam(&mGetActorName_d, "GetActorName");
    getAITreeVariable(&mGetNumLeft_a, "GetNumLeft");
}

// NON_MATCHING: the actor load and boolean argument evaluation are scheduled differently.
void GetItemAnotherActor::m32(const sead::SafeString& actor_name) {
    getDemoGetAnotherActor(mActor, actor_name, actorHasTagCanGetPouch(actor_name), false, nullptr);
}

void GetItemAnotherActor::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
