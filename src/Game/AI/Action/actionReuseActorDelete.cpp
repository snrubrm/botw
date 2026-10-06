#include "Game/AI/Action/actionReuseActorDelete.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/Profiles/actBullet.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

ReuseActorDelete::ReuseActorDelete(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ReuseActorDelete::~ReuseActorDelete() = default;

bool ReuseActorDelete::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: register allocation (the original reloads `mActor` into `this`'s register in the shared
// reuse block and keeps one reload fewer on the bullet checks).
void ReuseActorDelete::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    if (*mIsReuseActor_m) {
        bool reuse = false;
        if (*mIsCheckCreateParent_s && actor->getCreateArgBaseProcLink().hasProc()) {
            reuse = true;
        } else if (auto* bullet = sead::DynamicCast<ksys::act::Bullet>(actor)) {
            if (*mIsCheckBulletHolder_s && bullet->_bd0._0.hasProc())
                reuse = true;
            else if (*mIsCheckBulletAttacker_s && bullet->_ba0.hasProc())
                reuse = true;
        }
        if (reuse) {
            auto* reused = mActor;
            if (reused->isDeletedOrDeleting())
                return;
            if (auto* info = reused->m135())
                info->_4 = 1;
            reused->emitDisappearEffect();
            reused->sleep(ksys::act::BaseProc::SleepWakeReason::_0);
            return;
        }
        if (auto* info = mActor->m135())
            info->_4 = 1;
    } else {
        if (auto* info = actor->m135())
            info->_4 = 1;
    }
    callDeleteAndCreateDropAndEmit(mActor, 0);
}

void ReuseActorDelete::leave_() {
    ksys::act::ai::Action::leave_();
}

void ReuseActorDelete::loadParams_() {
    getStaticParam(&mIsCheckCreateParent_s, "IsCheckCreateParent");
    getStaticParam(&mIsCheckBulletAttacker_s, "IsCheckBulletAttacker");
    getStaticParam(&mIsCheckBulletHolder_s, "IsCheckBulletHolder");
    getMapUnitParam(&mIsReuseActor_m, "IsReuseActor");
}

void ReuseActorDelete::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
