#include "Game/AI/AI/aiGiantArmorRoot.h"
#include "Game/AI/aiUnk_710072D608.h"
#include "Game/Actor/actGiantArmor.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectGiantArmor.h"

namespace uking::ai {

GiantArmorRoot::GiantArmorRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GiantArmorRoot::~GiantArmorRoot() = default;

bool GiantArmorRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GiantArmorRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* armor = sead::DynamicCast<act::GiantArmor>(mActor)) {
        if (sead::DynamicCast<ksys::act::Actor>(armor->_be8.getProc(nullptr, nullptr))) {
            sub_71003F5F6C();
            return;
        }
    }
    auto* body = mActor->getMainBody();
    auto* physics = mActor->getPhysics();
    if (body && physics)
        physics->sub_7100FBAF18(body);
    changeChild("非装備", nullptr);
}

void GiantArmorRoot::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        auto* actor = mActor;
        auto* body = actor->getMainBody();
        auto* physics = actor->getPhysics();
        if (body && physics)
            physics->sub_7100FBAF18(body);
        changeChild("非装備", nullptr);
        return;
    }
    if (!child->isChangeable())
        return;
    bool missing_owner = true;
    if (auto* armor = sead::DynamicCast<act::GiantArmor>(mActor))
        missing_owner = !sead::DynamicCast<ksys::act::Actor>(armor->_be8.getProc(nullptr, nullptr));
    if (isCurrentChild("装備")) {
        if (missing_owner) {
            mActor->deleteLater(ksys::act::BaseProc::DeleteReason::_0);
            auto* actor = mActor;
            auto* body = actor->getMainBody();
            if (body) {
                auto* physics = actor->getPhysics();
                if (physics)
                    physics->sub_7100FBAF18(body);
            }
            changeChild("非装備", nullptr);
        }
    } else if (!missing_owner) {
        sub_71003F5F6C();
    }
}

void GiantArmorRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GiantArmorRoot::loadParams_() {}

// NON_MATCHING: argument-setup scheduling only. The original interleaves the trivial addVec3/addPointer
// setup (idx, pack address, vtable address) with the GParam loads and builds each key temp before the
// cstr() call; ours groups the loads first and builds the NodeName temp after. Register names differ
// (pack base x20 vs x21, x23 vs recomputed vtable address). All calls, branches and the pack
// constructor/destructor loops match exactly.
// 0x71003f5f6c
void GiantArmorRoot::sub_71003F5F6C() {
    if (auto* body = mActor->getMainBody())
        body->setContactLayer(ksys::phys::ContactLayer::EntityNoHit);

    ksys::act::ai::InlineParamPack pack;

    const sead::SafeString* name = &sead::SafeString::cEmptyString;
    if (auto* armor = sead::DynamicCast<act::GiantArmor>(mActor)) {
        auto* owner =
            sead::DynamicCast<ksys::act::Actor>(armor->_be8.getProc(nullptr, nullptr));
        const auto* giant_armor = armor->getParam()->getRes().mGParamList->getGiantArmor();
        pack.addVec3(giant_armor->mRotOffset.ref(), "RotOffset", -1);
        if (owner)
            name = ::sub_710072D608(owner, armor->_bf8);
    }
    pack.addPointer(const_cast<char*>(name->cstr()), "NodeName", ksys::AIDefParamType::String, -1);
    pack.addVec3(sead::Vector3f::zero, "TransOffset", -1);
    changeChild("装備", &pack);
}

}  // namespace uking::ai
