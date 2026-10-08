#include "Game/AI/Action/actionEventWatchCannonHit.h"
#include "Game/Damage/dmgDamageManagerBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/System/VFR.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace uking::action {

EventWatchCannonHit::EventWatchCannonHit(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventWatchCannonHit::~EventWatchCannonHit() = default;

bool EventWatchCannonHit::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventWatchCannonHit::enter_(ksys::act::ai::InlineParamPack* params) {
    _38 = 0;
}

void EventWatchCannonHit::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventWatchCannonHit::loadParams_() {
    getDynamicParam(&mWatchFrame_d, "WatchFrame");
    getDynamicParam(&mXLinkKey_d, "XLinkKey");
}

// NON_MATCHING: the original tests the == case with `b.le` reusing the outer fcmp's flags (no
// second compare); ours emits a second fcmp for `else if (current <= target)` (b.ls). All other
// instructions match, including the VFR::getDeltaFrame() step, the (new >= target)/(new <= target)
// Yoda inner tests, the getField50()==4 / s32(getDamage())>=1 gates and the
// !isEmpty+cstr/xlinkSearchAndEmit tail.
void EventWatchCannonHit::calc_() {
    auto* watch = mWatchFrame_d;
    const f32 step = ksys::VFR::instance()->getDeltaFrame();
    const f32 target = *watch;
    const f32 current = _38;
    bool reached = false;
    if (current < target) {
        const f32 new_value = current + step;
        if (new_value >= target || new_value < current) {
            _38 = target;
            reached = true;
        } else {
            _38 = new_value;
        }
    } else if (current <= target) {
        reached = true;
    } else {
        const f32 new_value = current - step;
        if (new_value <= target || current < new_value) {
            _38 = target;
            reached = true;
        } else {
            _38 = new_value;
        }
    }
    auto* manager = mActor->getDamageMgr();
    if (manager && manager->getField50() == 4 && s32(manager->getDamage()) >= 1) {
        if (!mXLinkKey_d.isEmpty())
            xlinkSearchAndEmit(mActor, mXLinkKey_d.cstr(), 2, nullptr);
        setFinished();
        return;
    }
    if (reached)
        setFailed();
}

}  // namespace uking::action
