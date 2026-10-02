#include "Game/AI/Action/actionForkAlwaysSetModelEffect.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/System/physInstanceSet.h"

namespace uking::action {

ForkAlwaysSetModelEffect::ForkAlwaysSetModelEffect(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ForkAlwaysSetModelEffect::~ForkAlwaysSetModelEffect() = default;

bool ForkAlwaysSetModelEffect::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkAlwaysSetModelEffect::enter_(ksys::act::ai::InlineParamPack* params) {
    _28 = 0;
    if (auto* as_list = mActor->getASList())
        as_list->x_3(0, 0, &ksys::as::ASList::Unk2::sub_71011631BC, 0.0f);
    if (auto* physics = mActor->getPhysics())
        physics->getFlags().set(ksys::phys::InstanceSet::Flag::_20000);
}

void ForkAlwaysSetModelEffect::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkAlwaysSetModelEffect::loadParams_() {
    getStaticParam(&mTimer_s, "Timer");
}

// NON_MATCHING: the original loads *mTimer_s before _28 and mActor after the clamp (scheduling; a once-used
// `ratio` local fixes the actor load only)
void ForkAlwaysSetModelEffect::calc_() {
    ksys::Timer::update(&_28, 1.0f);
    mActor->x_3(sead::Mathf::clamp(_28 * (1.0f / f32(*mTimer_s)), 0.0f, 1.0f));
    if (_28 >= f32(*mTimer_s))
        setFinished();
}

}  // namespace uking::action
