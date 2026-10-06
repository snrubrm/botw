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

// NON_MATCHING: scheduling of the rotation vector math around the payload lock (the original loads the
// vector first and interleaves the multiplications with the lock acquisition).
void GuardianMiniChangeWeapon::sub_710041A6DC() {
    sead::Vector3f dir = sead::Vector3f::ey * static_cast<f32>(*mRotValue_s) * 2.0943952f;
    _a0->_18.set(dir, *mRotSpeed_s);
    _a0->sub_710070DBB0(*mActor->getMessageTransceiver().getId(), true);
    changeChild("武器切替");
    if (auto* as_list = mActor->getASList()) {
        if (as_list->x_1(1, 0) != mDamageASName_s)
            sub_710041AA18();
    }
}

void GuardianMiniChangeWeapon::enter_(ksys::act::ai::InlineParamPack* params) {
    mActor->getDamageMgr();
    setDamageCallbackTiming(mActor, 4, &_78);
    changeChild("切替開始");
}

void GuardianMiniChangeWeapon::calc_() {
    sub_710041A554();
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("切替開始")) {
            sub_710041A6DC();
            return;
        }
    }

    child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("切替終了"))
            setFinished();
    }
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

void GuardianMiniChangeWeapon::sub_710041AA18() {
    auto* actor = mActor;
    if (!actor)
        return;
    auto* as_list = actor->getASList();
    if (!as_list)
        return;
    as_list->startAnimationMaybe(-1.0f, -1.0f, as_list->x_1(0, 0).cstr(), 1, 0, true);
    as_list->x_3(1, 0, &ksys::as::ASList::Unk2::sub_7101163298,
                 as_list->x_5(0, 0, &ksys::as::ASList::Unk2::sub_71011632F8));
}

void GuardianMiniChangeWeapon::sub_710041AAD4() {
    changeChild("切替終了");
    auto* as_list = mActor->getASList();
    if (!as_list)
        return;
    if (as_list->x_1(1, 0) != mDamageASName_s)
        sub_710041AA18();
}

bool GuardianMiniChangeWeapon::handleMessage_(const ksys::Message* message) {
    if (_a8.m2(*message) && _a8._34._10) {
        _a8.x();
        sub_710041AAD4();
        return true;
    }
    return false;
}

}  // namespace uking::ai
