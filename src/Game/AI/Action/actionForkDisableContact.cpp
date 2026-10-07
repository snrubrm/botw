#include "Game/AI/Action/actionForkDisableContact.h"
#include <prim/seadFormatPrint.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"

namespace uking::action {

// 0x710014abf4: the contact layer filter handed to sub_7100EEB078 (the first argument is unused).
bool sub_710014ABF4(ksys::phys::RigidBody*, ksys::phys::RigidBody* other) {
    const ksys::phys::ContactLayer layer = other->getContactLayer();
    if (int(layer) == ksys::phys::ContactLayer::EntityGround)
        return false;
    if (int(layer) == ksys::phys::ContactLayer::EntityGroundObject)
        return false;
    if (int(layer) == ksys::phys::ContactLayer::EntityGroundRough)
        return false;
    if (int(layer) == ksys::phys::ContactLayer::EntityGroundSmooth)
        return false;
    if (int(layer) == ksys::phys::ContactLayer::EntityTree)
        return false;
    return int(layer) != ksys::phys::ContactLayer::EntityWater;
}

ForkDisableContact::ForkDisableContact(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkDisableContact::~ForkDisableContact() = default;

// NON_MATCHING: loop-variable form only (the original walks a byte offset 0x20..0x70 over the names; ours a plain index)
bool ForkDisableContact::init_(sead::Heap* heap) {
    for (int i = 0; i < 5; ++i) {
        auto* body = mActor->findPhysicsBodyByName(ksys::act::getStr_Body().cstr(),
                                                   mRigidBodyName_s[i].cstr());
        if (!body) {
            body = mActor->findPhysicsBodyByName(ksys::act::getStr_EntitySensor().cstr(),
                                                 mRigidBodyName_s[i].cstr());
        }
        mBodies[i].mBody = body;
        mBodies[i].mIsEnabled = true;
    }
    return true;
}

void ForkDisableContact::enter_(ksys::act::ai::InlineParamPack* params) {
    mFlags.set(Flag::Changeable);
}

void ForkDisableContact::leave_() {
    sub_710014B0F0();
}

// NON_MATCHING: regalloc only (the original computes &mRigidBodyName_s[0] before the first getStaticParam call)
void ForkDisableContact::loadParams_() {
    getStaticParam(&mParams.mRecoverDelayTimeMin_s, "RecoverDelayTimeMin");
    sead::FixedSafeString<64> key;
    for (u32 i = 0; i < 5; i++) {
        (sead::StringCutOffPrintFormatter(&key) << "RigidBodyName%d", i) << sead::flush;
        getStaticParam(&mRigidBodyName_s[i], key);
    }
}

void ForkDisableContact::sub_710014AED0() {
    for (auto& entry : mBodies) {
        if (auto* body = entry.mBody) {
            body->enableContactLayer(ksys::phys::ContactLayer::EntityPlayer);
            body->enableContactLayer(ksys::phys::ContactLayer::EntityNPC);
            body->enableContactLayer(ksys::phys::ContactLayer::EntityNPC_NoHitPlayer);
            body->enableContactLayer(ksys::phys::ContactLayer::EntityRagdoll);
        }
        entry.mIsEnabled = false;
    }
}

void ForkDisableContact::sub_710014B0F0() {
    for (auto& entry : mBodies) {
        if (auto* body = entry.mBody; body && !entry.mIsEnabled) {
            body->disableContactLayer(ksys::phys::ContactLayer::EntityPlayer);
            body->disableContactLayer(ksys::phys::ContactLayer::EntityNPC);
            body->disableContactLayer(ksys::phys::ContactLayer::EntityNPC_NoHitPlayer);
            body->disableContactLayer(ksys::phys::ContactLayer::EntityRagdoll);
            entry.mIsEnabled = true;
        }
    }
}

void ForkDisableContact::sub_710014B018() {
    for (int i = 0; i < 5; ++i) {
        auto& entry = mBodies[i];
        if (auto* body = entry.mBody; body && !entry.mIsEnabled) {
            sead::Delegate2RFunc<ksys::phys::RigidBody*, ksys::phys::RigidBody*, bool> filter(
                &sub_710014ABF4);
            bool enabled = false;
            if (!ksys::act::sub_7100EEB078(body, nullptr, &filter)) {
                body->disableContactLayer(ksys::phys::ContactLayer::EntityPlayer);
                body->disableContactLayer(ksys::phys::ContactLayer::EntityNPC);
                body->disableContactLayer(ksys::phys::ContactLayer::EntityNPC_NoHitPlayer);
                body->disableContactLayer(ksys::phys::ContactLayer::EntityRagdoll);
                enabled = true;
            }
            entry.mIsEnabled = enabled;
        }
    }
}

void ForkDisableContact::calc_() {
    if (m32()) {
        sub_710014AED0();
        mRecoverTimer.reset(*mParams.mRecoverDelayTimeMin_s);
    } else if (!m33()) {
        if (mRecoverTimer.value <= sead::Mathf::epsilon())
            sub_710014B018();
        else
            mRecoverTimer.update();
    }
}

}  // namespace uking::action
