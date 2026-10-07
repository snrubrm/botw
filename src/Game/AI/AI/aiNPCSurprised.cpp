#include "Game/AI/AI/aiNPCSurprised.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actTag.h"
#include "Game/AI/aiUnk_7100711020.h"

namespace uking::ai {

NPCSurprised::NPCSurprised(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

NPCSurprised::~NPCSurprised() = default;

bool NPCSurprised::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void NPCSurprised::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ActorConstDataAccess accessor;
    if (ksys::act::acquireActor(mTerrorEmitter_d, &accessor)) {
        if (accessor.hasTag(ksys::act::tags::Explosive))
            sub_7100712388(mActor, accessor, "TerrorExplosion");
        else if (accessor.getName() == "Explode")
            sub_7100712388(mActor, accessor, "TerrorLightning");
        else if (*mTerrorLayer_d & 0x10)
            sub_7100712388(mActor, accessor, "TerrorImpulse");
    }
    sub_71005D7518(mActor, false);
    ksys::act::setEnabledTalkAndLockOn(mActor, false);
    changeChild("驚く");
}

void NPCSurprised::calc_() {
    if (isCurrentChild("驚く")) {
        if (getCurrentChild()->isFinished()) {
            if (!*mIsNeedUnEquipWeapon_d || sub_71005DB7E4(mActor, 0))
                setFinished();
            else
                changeChild("納刀");
        }
    } else if (isCurrentChild("納刀")) {
        if (getCurrentChild()->isFinished())
            setFinished();
    }
}

void NPCSurprised::leave_() {
    sub_71005D7518(mActor, true);
    mActor->x_6();
}

void NPCSurprised::loadParams_() {
    getDynamicParam(&mTerrorLayer_d, "TerrorLayer");
    getDynamicParam(&mIsNeedUnEquipWeapon_d, "IsNeedUnEquipWeapon");
    getDynamicParam(&mTerrorEmitter_d, "TerrorEmitter");
}

}  // namespace uking::ai
