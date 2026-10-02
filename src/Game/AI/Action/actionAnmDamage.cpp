#include "Game/AI/Action/actionAnmDamage.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::action {

AnmDamage::AnmDamage(const InitArg& arg) : SmallDamageBase(arg) {}

AnmDamage::~AnmDamage() = default;

bool AnmDamage::init_(sead::Heap* heap) {
    return SmallDamageBase::init_(heap);
}

void AnmDamage::enter_(ksys::act::ai::InlineParamPack* params) {
    SmallDamageBase::enter_(params);
    playAS(mAS_s.cstr(), false, 0, 0, -1.0f);
}

void AnmDamage::leave_() {
    SmallDamageBase::leave_();
}

void AnmDamage::loadParams_() {
    TakeHitImpactForce::loadParams_();
    getStaticParam(&mAS_s, "AS");
}

void AnmDamage::calc_() {
    SmallDamageBase::calc_();
}

// NON_MATCHING: the original passes a 0x18-byte stack object (a SafeString followed by another field, like
// the ASList::x query objects) instead of a plain SafeString
bool AnmDamage::isChangeable() const {
    const sead::SafeString name;
    return sub_71005DD798(mActor, 2, &name, 0, 0);
}

}  // namespace uking::action
