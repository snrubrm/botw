#include "Game/AI/AI/aiSiteBossBowRoot.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiRoot.h"

void sub_71002C65C8(ksys::act::Actor* actor, bool a1, bool a2);

namespace uking::ai {

SiteBossBowRoot::SiteBossBowRoot(const InitArg& arg) : SiteBossRoot(arg) {}

SiteBossBowRoot::~SiteBossBowRoot() = default;

bool SiteBossBowRoot::init_(sead::Heap* heap) {
    return SiteBossRoot::init_(heap);
}

void SiteBossBowRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    SiteBossRoot::enter_(params);
}

void SiteBossBowRoot::leave_() {
    SiteBossRoot::leave_();
    if (!isActorGoingBackToRootAi()) {
        _120 = 0;
        sub_7100576744(0);
        sub_7100576744(1);
        sub_7100576744(2);
        sub_7100576744(3);
    }
    if (!mActor->getRootAi()->isActorDeletedOrDeleting() && _124) {
        _124 = false;
        sub_71002C65C8(mActor, false, true);
    }
}

void SiteBossBowRoot::loadParams_() {
    SiteBossRoot::loadParams_();
    getStaticParam(&mArrowRainAttackPower_s, "ArrowRainAttackPower");
    getStaticParam(&mAtMinPower_s, "AtMinPower");
    getStaticParam(&mReflectArrowAttackPower_s, "ReflectArrowAttackPower");
    getStaticParam(&mDemoName_s, "DemoName");
}

}  // namespace uking::ai
