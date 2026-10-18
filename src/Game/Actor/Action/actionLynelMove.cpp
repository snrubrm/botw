#include "Game/Actor/Action/actionLynelMove.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/Actor/actRideable.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"
#include "KingSystem/System/VFR.h"
#include "Game/Actor/aiUnk_71007377D4.h"

namespace uking::action {

LynelMove::LynelMove(const InitArg& arg) : AnimalMove(arg) {}

LynelMove::~LynelMove() = default;

bool LynelMove::init_(sead::Heap* heap) {
    return AnimalMove::init_(heap);
}

void LynelMove::enter_(ksys::act::ai::InlineParamPack* params) {
    AnimalMove::enter_(params);
    _88.sub_710070F9CC(mActor);
}

void LynelMove::leave_() {
    if (auto* nav = mActor->m45())
        nav->sub_7100F76314();
    _88.sub_710070F9CC(mActor);
    AnimalMove::leave_();
}

void LynelMove::loadParams_() {
    AnimalMove::loadParams_();
    getStaticParam(&mTimeForCalcCheckCliffDist_s, "TimeForCalcCheckCliffDist");
    _88.sub_710070F984(this);
}

void LynelMove::calc_() {
    AnimalMove::calc_();
    const sead::Vector3f* target = m32();
    sead::Vector3f dir = *target - mActor->getMtx().getTranslation();
    dir.y = 0.0f;
    const f32 length = dir.normalize();
    _88.sub_710070FA84(mActor, &dir, length);
}

bool LynelMove::m34(const sead::Vector3f& pos, float x) {
    const f32 dist = *mTimeForCalcCheckCliffDist_s * (ksys::VFR::instance()->getDeltaFrame() * x);
    if (dist > 0.0f && sub_710072FEC4(mActor, pos, dist, nullptr, true, nullptr))
        return false;
    return true;
}

// NON_MATCHING: gear/row source enum identities and movement-argument scheduling differ.
bool LynelMove::m35(act::RideableBase* rideable, s32 gear_type, s32 gear,
                   s32 min_gear_at_auto_down, const sead::Vector3f& direction) {
    auto* nav = mActor->m45();
    if (!nav)
        return AnimalMoveBase::m35(rideable, gear_type, gear, min_gear_at_auto_down, direction);

    const s32 current_gear = rideable->_18._b == 0 ? rideable->_18._9 : rideable->_18._b;
    s32 row = rideable->_18._a;
    const auto* speed = &act::sUnk_7102603058;
    if (current_gear != 0 && rideable->_170) {
        if (row >= rideable->_178)
            row = 0;
        speed = &rideable->_170->mGears[row][current_gear - 1];
    }
    const f32 scale = speed->mSpeed * rideable->_164;
    nav->sub_7100F76260(direction * scale);
    return rideable->sub_7100E63470(gear_type, gear, min_gear_at_auto_down, 0);
}

}  // namespace uking::action
