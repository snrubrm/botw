#include "Game/AI/AI/aiGanonShockRoot.h"
#include "Game/Actor/actLastBoss.h"

namespace uking::ai {

GanonShockRoot::GanonShockRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GanonShockRoot::~GanonShockRoot() = default;

bool GanonShockRoot::isFinished() const {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("ショック")) {
            if (!*mIsDoRecoverAction_s)
                return true;
            auto* boss = sead::DynamicCast<act::LastBoss>(mActor);
            if (!boss)
                return true;
            if (boss->_14e8.isOn(2)) {
                auto* life = boss->getLife();
                return life && *life == 0;
            }
        }
        return true;
    }
    return mFlags.isOn(Flag::Finished);
}

bool GanonShockRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GanonShockRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    changeChild("ショック");
    if (auto* boss = sead::DynamicCast<act::LastBoss>(mActor)) {
        if (boss->_14e8.isOn(2)) {
            if (*mIsGuardJust_s)
                boss->_14e8.set(0x800);
            else
                boss->_14e8.set(0x400);
            if (boss->_14e8.isOn(4))
                boss->_14e8.reset(4);
            boss->_14f8._30.reset(1);
            boss->update();
        }
    }
    mFlags.reset(Flag::Changeable);
}

void GanonShockRoot::calc_() {
    auto* child = getCurrentChild();
    if (!child->isFinished() && !child->isFailed())
        return;

    if (isCurrentChild("ショック") && *mIsDoRecoverAction_s) {
        auto* boss = sead::DynamicCast<act::LastBoss>(mActor);
        if (boss && boss->_14e8.isOn(2)) {
            auto* life = boss->getLife();
            if (!life || *life != 0) {
                changeChild("瀕死時復帰");
                return;
            }
        }
    }
    setFinished();
}

void GanonShockRoot::leave_() {
    auto* boss = sead::DynamicCast<act::LastBoss>(mActor);
    if (!boss || !boss->_14e8.isOn(2))
        return;

    if (*mIsGuardJust_s)
        boss->_14e8.reset(0x800);
    else
        boss->_14e8.reset(0x400);
    if (boss->_14e8.isOff(4))
        boss->_14e8.set(4);
    boss->_14f8._30.set(1);
    if (!*mIsDoRecoverAction_s)
        boss->x();
}

void GanonShockRoot::loadParams_() {
    getStaticParam(&mIsDoRecoverAction_s, "IsDoRecoverAction");
    getStaticParam(&mIsGuardJust_s, "IsGuardJust");
}

}  // namespace uking::ai
