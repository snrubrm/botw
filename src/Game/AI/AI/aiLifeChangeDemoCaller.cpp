#include "Game/AI/AI/aiLifeChangeDemoCaller.h"
#include "Game/Damage/dmgDamageManagerBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Event/evtMetadata.h"

namespace uking::ai {

LifeChangeDemoCaller::LifeChangeDemoCaller(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

LifeChangeDemoCaller::~LifeChangeDemoCaller() = default;

bool LifeChangeDemoCaller::init_(sead::Heap* heap) {
    _244 = false;
    ksys::evt::Metadata metadata(mDemoName_s.cstr(), mDemoEntryPoint_s.cstr(), "");
    metadata.setSkipIsStartableAirCheck(*mIsIgnorePlayerLand_s);
    _70.initWithEvent_(mActor, &metadata);
    return true;
}

void LifeChangeDemoCaller::enter_(ksys::act::ai::InlineParamPack* params) {
    if (!_244)
        _70.loadEvent();
    const s32* life = mActor->getLife();
    _240 = life ? *life : 1;
    changeChild("行動", params);
}

void LifeChangeDemoCaller::calc_() {
    const s32* life_ptr = mActor->getLife();
    const s32 life = life_ptr ? *life_ptr : 1;
    if (_244 || life == _240)
        return;

    if (!(f32(life) < f32(mActor->getMaxLife()) * *mLifeRatio_s))
        return;

    if (_70.callEvent(false)) {
        _244 = true;
        _70.unloadEvent();
    }
    if (auto* damage_mgr = mActor->getDamageMgr())
        damage_mgr->mField_34 = true;
}

bool LifeChangeDemoCaller::isFailed() const {
    return getCurrentChild()->isFailed();
}

bool LifeChangeDemoCaller::isFinished() const {
    return getCurrentChild()->isFinished();
}

bool LifeChangeDemoCaller::isChangeable() const {
    return getCurrentChild()->isChangeable();
}

void LifeChangeDemoCaller::leave_() {
    if (auto* damage_mgr = mActor->getDamageMgr())
        damage_mgr->mField_34 = false;
    if (_70.mEventFlow)
        _70.unloadEvent();
}

void LifeChangeDemoCaller::loadParams_() {
    getStaticParam(&mLifeRatio_s, "LifeRatio");
    getStaticParam(&mOnlyOnce_s, "OnlyOnce");
    getStaticParam(&mIsIgnorePlayerLand_s, "IsIgnorePlayerLand");
    getStaticParam(&mDemoName_s, "DemoName");
    getStaticParam(&mDemoEntryPoint_s, "DemoEntryPoint");
}

}  // namespace uking::ai
