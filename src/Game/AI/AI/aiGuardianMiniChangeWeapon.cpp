#include "Game/AI/AI/aiGuardianMiniChangeWeapon.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

GuardianMiniChangeWeapon::GuardianMiniChangeWeapon(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GuardianMiniChangeWeapon::~GuardianMiniChangeWeapon() {
    if (_a0) {
        delete _a0;
        _a0 = nullptr;
    }
}

bool GuardianMiniChangeWeapon::init_(sead::Heap* heap) {
    _a0 = new (heap) Unk_71023f83e8(mActor, 0x8000021);
    return _a0 != nullptr;
}

void GuardianMiniChangeWeapon::enter_(ksys::act::ai::InlineParamPack* params) {
    mActor->getDamageMgr();
    setDamageCallbackTiming(mActor, 4, &_78);
    changeChild("切替開始");
}

bool GuardianMiniChangeWeapon::isChangeable() const {
    return false;
}

void GuardianMiniChangeWeapon::leave_() {
    sub_71005DA114(mActor, &_78);
    if (mActor) {
        if (auto* as_list = mActor->getASList()) {
            as_list->sub_710115C11C();
            as_list->sub_710115BED4(true);
        }
    }
}

void GuardianMiniChangeWeapon::loadParams_() {
    getStaticParam(&mRotValue_s, "RotValue");
    getStaticParam(&mRotSpeed_s, "RotSpeed");
    getStaticParam(&mRootNodeName_s, "RootNodeName");
    getStaticParam(&mDamageNodeName_s, "DamageNodeName");
    getStaticParam(&mDamageASName_s, "DamageASName");
}

bool GuardianMiniChangeWeapon::isFinished() const {
    return ActionBase::isFinished() ||
           (isCurrentChild("切替終了") && getCurrentChild()->isFinished());
}

bool GuardianMiniChangeWeapon::handleMessage_(const ksys::Message& message) {
    if (_a8.m2(message) && _a8._34._10) {
        _a8.x();
        sub_710041AAD4();
        return true;
    }
    return false;
}

}  // namespace uking::ai
