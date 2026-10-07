#include "Game/AI/AI/aiGuardianBeamAttack.h"
#include "Game/Actor/actGuardian.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Utils/Thread/Message.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/System/physRayCastBodyQuery.h"

namespace uking::ai {

GuardianBeamAttack::GuardianBeamAttack(const InitArg& arg) : GuardianBeamAttackBase(arg) {}

GuardianBeamAttack::~GuardianBeamAttack() {
    if (_78) {
        delete _78;
        _78 = nullptr;
    }
}

bool Unk_71023f6f80::m5(ksys::act::BaseProc* proc) {
    _a0->sub_710040FC24();
    return false;
}

bool GuardianBeamAttack::init_(sead::Heap* heap) {
    if (!GuardianBeamAttackBase::init_(heap))
        return false;
    _78 = new (heap, 8) Unk_71023f6f80(this);
    return true;
}

void GuardianBeamAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    GuardianBeamAttackBase::enter_(params);
    auto* guardian = sub_7100411DE0();
    changeChild("待機");
    if (guardian) {
        _78->x(guardian);
        auto* info = _78;
        info->_28 = guardian->sub_710003B2EC().cstr();
        info->_30.getKey().reset();
        _78->_68 = sead::Matrix34f::ident;
        mActor->sub_71011DA824(_78);
    }
}

void GuardianBeamAttack::sub_710040F7C0(bool prepare) {
    if (auto* guardian = sub_7100411DE0()) {
        if (auto* target = guardian->_15a8) {
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(target->_18, "TargetPos", -1);
            changeChild(prepare ? "照準準備" : "照準", &pack);
        }
    }
}

void GuardianBeamAttack::sub_710040F8B8() {
    auto* guardian = sub_7100411DE0();
    if (guardian && guardian->sub_710003B2A8()) {
        if (auto* target = guardian->_15a8) {
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(target->_c, "TargetPos", -1);
            changeChild("チャージ", &pack);
            guardian->sub_710003B3FC();
        } else {
            changeChild("待機");
        }
    }
}

void GuardianBeamAttack::leave_() {
    GuardianBeamAttackBase::leave_();
    mActor->sub_71011DA834(_78);
    _48.fade();
    _58.fade();
}

sead::Vector2f GuardianBeamAttack::sub_7100410730(const sead::Vector3f& dir,
                                                  const sead::Vector3f& start) {
    f32 length = *mLightLength_s;
    f32 radius = *mLightRadius_s;
    ksys::phys::RayCastBodyQuery query(nullptr, ksys::phys::GroundHit::HitAll);
    query.enableLayer(ksys::phys::ContactLayer::EntityGround);
    query.enableLayer(ksys::phys::ContactLayer::EntityGroundObject);
    query.enableLayer(ksys::phys::ContactLayer::EntityNPC);
    sead::Vector3f pos = dir * length + start;
    query.setStartAndEnd(start, pos);
    query.setGroupHandlerIfAny(sub_710072E804(mActor, 0));
    if (query.worldRayCast(ksys::phys::ContactLayerType::Entity)) {
        query.getHitPosition(&pos);
        const f32 distance = (start - pos).length();
        if (*mAdjustRadius_s) {
            length = distance + *mLightLengthOffset_s;
        } else {
            const f32 ratio = radius / length;
            length = distance + *mLightLengthOffset_s;
            radius = ratio * length;
        }
    } else {
        length += *mLightLengthOffset_s;
    }
    return {radius, length};
}

bool GuardianBeamAttack::handleMessage_(const ksys::Message* message) {
    if (message->getType() == 0x3000003) {
        _48.fade();
        _58.fade();
        changeChild("待機");
        return true;
    }
    return false;
}

void GuardianBeamAttack::loadParams_() {
    GuardianBeamAttackBase::loadParams_();
    getStaticParam(&mLightRadius_s, "LightRadius");
    getStaticParam(&mLightLength_s, "LightLength");
    getStaticParam(&mLightLengthOffset_s, "LightLengthOffset");
    getStaticParam(&mEarSpeed_s, "EarSpeed");
    getStaticParam(&mAdjustRadius_s, "AdjustRadius");
}

}  // namespace uking::ai
