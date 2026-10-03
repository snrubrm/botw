#include "Game/AI/AI/aiReflectableThrown.h"
#include "Game/Damage/dmgDamageManagerBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"

namespace uking::ai {

ReflectableThrown::ReflectableThrown(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

ReflectableThrown::~ReflectableThrown() = default;

bool ReflectableThrown::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void ReflectableThrown::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_71007A34B8(mActor, mHitColName_s);
    if (auto* parent = sead::DynamicCast<ksys::act::Actor>(mActor->getConnectedCalcParent()))
        _60 = parent->getPreviousPos();
    else
        mActor->getMtx().getTranslation(_60);
    _6c = mActor->getVelocity().length();
    _70.x();
    m34();
}

void ReflectableThrown::calc_() {
    getCurrentChild();
    int type = -1;
    if (sub_710053DA04(&type)) {
        _70.x();
        sub_710053DBA0(type);
    }
}

void ReflectableThrown::leave_() {
    sub_71007A3634(mActor, mHitColName_s);
}

void ReflectableThrown::loadParams_() {
    getStaticParam(&mIsReflectByGuard_s, "IsReflectByGuard");
    getStaticParam(&mIsReflectByArrow_s, "IsReflectByArrow");
    getStaticParam(&mHitColName_s, "HitColName");
    getStaticParam(&mRefSpeedRatioByJustGuard_s, "RefSpeedRatioByJustGuard");
}

bool ReflectableThrown::isFailed() const {
    return getCurrentChild()->isFailed();
}

bool ReflectableThrown::isFinished() const {
    return getCurrentChild()->isFinished() && !sub_710053DA04(nullptr);
}

bool ReflectableThrown::sub_710053DA04(int* out) const {
    if (!isCurrentChild("投擲"))
        return false;

    if (sub_71007A274C(mActor) && !sub_71007A4178(mActor, false)) {
        if (*mIsReflectByArrow_s) {
            if (out)
                *out = 0;
            return true;
        }
        auto* manager = mActor->getDamageMgr();
        if (!manager)
            return true;
        if (manager->getField50() != 8 && manager->getField50() != 3)
            return true;
    }

    auto* manager = mActor->getDamageMgr();
    if (!manager)
        return false;

    if (manager->getField54() == 7 || manager->getField54() == 8) {
        if (out)
            *out = 2;
        return true;
    }

    if (!*mIsReflectByGuard_s)
        return false;

    if (manager->getField50() == 8) {
        if (out)
            *out = 1;
        return true;
    }

    if (manager->getField54() != 6)
        return false;
    if (out)
        *out = 2;
    return true;
}

void ReflectableThrown::m34() {
    changeChild("投擲");
}

}  // namespace uking::ai
