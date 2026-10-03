#include "Game/AI/AI/aiOctarockRoot.h"
#include <prim/seadFormatPrint.h>
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "Game/Actor/actUnk_7100d3cd74.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"

namespace uking::ai {

OctarockRoot::OctarockRoot(const InitArg& arg) : OctarockRootBase(arg) {}

OctarockRoot::~OctarockRoot() {
    if (auto* parts = mActor->m101()) {
        parts->sub_7100D3CFEC("Wig");
        for (const auto& key : mShootActorKey_s) {
            {
                auto& link = parts->getActorPartsActor(key);
                ksys::act::ActorConstDataAccess accessor;
                ksys::act::acquireActor(&link, &accessor);
                if (accessor.hasProc()) {
                    mActor->sendMessage(*accessor.getMessageTransceiverId(),
                                        ksys::MessageType(0x300000f), nullptr, false);
                }
            }
            parts->sub_7100D3CFEC(key);
        }
        if (!mExtraShootActorKey_s.isEmpty())
            parts->sub_7100D3CFEC(mExtraShootActorKey_s);
    }
}

bool OctarockRoot::init_(sead::Heap* heap) {
    return OctarockRootBase::init_(heap);
}

void OctarockRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    if (auto* body = actor->getRigidBodyByName(sub_71007A250C()->cstr()))
        body->addToWorld();
    _368.mLink.reset();
    _318 = false;
    _328.sub_7100714918();
    OctarockRootBase::enter_(params);
}

// NON_MATCHING: regalloc (the original recomputes `this + 0x300` for the link copy instead of keeping it in a register)
bool OctarockRoot::handleMessage_(const ksys::Message* message) {
    if (_2c8.m2(*message)) {
        _368.mLink = _2c8._38.mLink;
        _2c8.x();
        _318 = true;
        _31c.set(15.0f, 15.0f, -1.0f);
        return true;
    }
    return OctarockRootBase::handleMessage_(message);
}

void OctarockRoot::leave_() {
    for (auto& handle : _290) {
        if (handle.isAllocatedOrFailed())
            handle.deleteProc();
    }
    if (auto* parts = mActor->m101()) {
        auto& wig = parts->getActorPartsActor("Wig");
        if (wig.hasProc()) {
            ksys::act::ActorConstDataAccess accessor;
            ksys::act::acquireActor(&wig, &accessor);
            accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
        }
    }
    OctarockRootBase::leave_();
}

// NON_MATCHING: the lib's StringPrintFormatter has no output destructor call (the original calls
// ~StringCutOffPrintOutput 0xb0c528 after each flush) and the frame is 8 bytes off (libwork)
void OctarockRoot::loadParams_() {
    OctarockRootBase::loadParams_();
    getStaticParam(&mIsWigBreakable_s, "IsWigBreakable");
    getStaticParam(&mItemName_s, "ItemName");
    getStaticParam(&mConnectRigidBodyName_s, "ConnectRigidBodyName");
    getStaticParam(&mConnectTgtBodyName_s, "ConnectTgtBodyName");
    getStaticParam(&mShootActorName_s, "ShootActorName");
    sead::FixedSafeString<64> key;
    for (u32 i = 0; i < 3; ++i) {
        (sead::StringPrintFormatter(&key) << "ShootActorKey%d", i + 1) << sead::flush;
        getStaticParam(&mShootActorKey_s[i], key);
    }
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
