#include "Game/AI/AI/aiOctarockRoot.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

OctarockRoot::OctarockRoot(const InitArg& arg) : OctarockRootBase(arg) {}

OctarockRoot::~OctarockRoot() = default;

bool OctarockRoot::init_(sead::Heap* heap) {
    return OctarockRootBase::init_(heap);
}

void OctarockRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    OctarockRootBase::enter_(params);
}

void OctarockRoot::leave_() {
    OctarockRootBase::leave_();
}

void OctarockRoot::loadParams_() {
    OctarockRootBase::loadParams_();
    getStaticParam(&mIsWigBreakable_s, "IsWigBreakable");
    getStaticParam(&mItemName_s, "ItemName");
    getStaticParam(&mConnectRigidBodyName_s, "ConnectRigidBodyName");
    getStaticParam(&mConnectTgtBodyName_s, "ConnectTgtBodyName");
    getStaticParam(&mShootActorName_s, "ShootActorName");
    // FIXME: CALL _ZNK4sead22BufferedSafeStringBaseIcE22assureTerminationImpl_Ev @ 0x7100b0ce00
    // FIXME: CALL _ZN4sead20StringPrintFormatterC2EPNS_22BufferedSafeStringBaseIcEE @ 0x7100b0c320
    // FIXME: CALL _ZN4sead14PrintFormatterlsEPKc @ 0x7100b0bfd8
    // FIXME: CALL _ZN4sead14PrintFormatter20proceedToFormatMark_EPc @ 0x7100b0bde0
    // FIXME: CALL _ZN4sead14PrintFormatter5flushEv @ 0x7100b0bd94
    // FIXME: CALL sead__PrintFormatter__x @ 0x7100b0c528
    // FIXME: CALL _ZN4sead20StringPrintFormatterC2EPNS_22BufferedSafeStringBaseIcEE @ 0x7100b0c320
    // FIXME: CALL _ZN4sead14PrintFormatterlsEPKc @ 0x7100b0bfd8
    // FIXME: CALL _ZN4sead14PrintFormatter20proceedToFormatMark_EPc @ 0x7100b0bde0
    // FIXME: CALL _ZN4sead14PrintFormatter5flushEv @ 0x7100b0bd94
    // FIXME: CALL sead__PrintFormatter__x @ 0x7100b0c528
    // FIXME: CALL _ZN4sead20StringPrintFormatterC2EPNS_22BufferedSafeStringBaseIcEE @ 0x7100b0c320
    // FIXME: CALL _ZN4sead14PrintFormatterlsEPKc @ 0x7100b0bfd8
    // FIXME: CALL _ZN4sead14PrintFormatter20proceedToFormatMark_EPc @ 0x7100b0bde0
    // FIXME: CALL _ZN4sead14PrintFormatter5flushEv @ 0x7100b0bd94
    // FIXME: CALL sead__PrintFormatter__x @ 0x7100b0c528
    getStaticParam(&mExtraShootActorName_s, "ExtraShootActorName");
    getStaticParam(&mExtraShootActorKey_s, "ExtraShootActorKey");
    getMapUnitParam(&mCarryActorName_m, "CarryActorName");
    getAITreeVariable(&mVacuumedExplodingBomb_a, "VacuumedExplodingBomb");
    getAITreeVariable(&mOctarockFormChangeUnit_a, "OctarockFormChangeUnit");
}

void OctarockRoot::m37() {
    if (auto* body = mActor->findPhysicsBodyByName(sub_71007A24E4()->cstr(), "HeadBody"))
        body->setContactAll();
    changeChild("リアクション");
}

void OctarockRoot::m38() {
    if (isCurrentChild("水中"))
        *mIsTrgChangeUnderWaterState_a = true;
    changeChild("通常");
}

void OctarockRoot::m39() {
    EnemyRoot::m39();
}

bool OctarockRoot::m41() {
    return isCurrentChild("水中") || isCurrentChild("水中怒り");
}

void OctarockRoot::m45() {}

}  // namespace uking::ai
