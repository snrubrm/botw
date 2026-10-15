#include "Game/Actor/AI/aiGolemReaction.h"
#include "Game/Actor/aiUnk_7102450410.h"
#include <math/seadMathCalcCommon.h>
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/aiUnk_7102357210.h"
#include "Game/Actor/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorAtk.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include <prim/seadDelegate.h>
#include <limits>
#include "Game/Actor/actEnemy.h"
#include "Game/Actor/aiUnk_7100724C64.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/ActorSystem/aiRootAi.h"

namespace uking::ai {

// Placeholder name for the original 16-byte callback constructed by the arm-contact query.
// Its vtable has invoke, clone and isNoDummy slots of the IDelegate2R interface.
class Unk_71023f52d0 : public sead::IDelegate2R<ksys::phys::RigidBody*, ksys::phys::RigidBody*, bool> {
public:
    explicit Unk_71023f52d0(ksys::act::ActorAtk::Unk_710079e64c::Unk1* entry) : mEntry(entry) {}
    bool invoke(ksys::phys::RigidBody*, ksys::phys::RigidBody* other) override;
private:
    ksys::act::ActorAtk::Unk_710079e64c::Unk1* mEntry;
};
KSYS_CHECK_SIZE_NX150(Unk_71023f52d0, 0x10);

// NON_MATCHING: the pointer equality compares its operands in the opposite order (both source orders
// produce the same code).
bool Unk_71023f52d0::invoke(ksys::phys::RigidBody*, ksys::phys::RigidBody* other) {
    return other == mEntry->_c8;
}

// NON_MATCHING: the recovered callback vtable is loaded through the GOT rather than addressed directly.
void GolemReaction::sub_71003FF3F8(bool* right, bool* left) {
    if (!right || !left)
        return;
    auto* actor = mActor;
    const s32 count = sub_71007A26AC(actor);
    for (s32 i = 0; i < count; ++i) {
        auto* entry = sub_71007A255C(actor, i);
        if (!entry || !(entry->_50 & 0x10))
            continue;
        Unk_71023f52d0 filter(entry);
        auto* right_body = mActor->findPhysicsBodyByName(ksys::act::getStr_Tgt().cstr(),
                                                       mRightArmTgtBodyName_s.cstr());
        if (right_body && ksys::act::sub_7100EEB078(right_body, nullptr, &filter)) {
            *right = true;
            return;
        }
        auto* left_body = mActor->findPhysicsBodyByName(ksys::act::getStr_Tgt().cstr(),
                                                      mLeftArmTgtBodyName_s.cstr());
        if (left_body && ksys::act::sub_7100EEB078(left_body, nullptr, &filter)) {
            *left = true;
            return;
        }
    }
}

GolemReaction::GolemReaction(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GolemReaction::~GolemReaction() = default;

bool GolemReaction::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

// NON_MATCHING: the two damage type compares (0x1b / 0x16) are emitted in the opposite order
void GolemReaction::enter_(ksys::act::ai::InlineParamPack* params) {
    _120 = true;
    _128.mTimer = ksys::Timer(0, 0);
    mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_80000000);
    if (*mGolemClimbedTime_a > 0.0f) {
        *mGolemClimbedTime_a = sead::Mathf::clampMin(
            *mGolemClimbedTime_a, f32(*mClimbLimitTime_s - *mClampRestClimbTime_s));
    }

    auto* actor = mActor;
    auto* life = actor->getLife();
    if (life && *life <= 0) {
        mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::Alive);
        changeChild("死亡");
        return;
    }

    if (sub_71005DD798(mActor, 0x13, nullptr, 0, 0)) {
        sub_71003FE9C4();
        sub_7100708FF0(mActor, 30.0f);
        changeChild("起き上がる");
        return;
    }

    if (sead::DynamicCast<act::DamageManager>(actor->getDamageMgr())) {
        if (sub_71003FEAB0())
            return;

        auto* damage_mgr = mActor->getDamageMgr();
        if (damage_mgr && damage_mgr->getField54() <= 0x15 && *mGolemClimbedTime_a > 0.0f) {
            changeChild("小ダメージ");
            return;
        }

        damage_mgr = mActor->getDamageMgr();
        const s32 type = damage_mgr ? damage_mgr->getField54() : -1;
        if (type != 0x1b && type != 0x16 && !sub_71003FEC7C()) {
            changeChild("小ダメージ");
            return;
        }
    }

    auto* damage_mgr = mActor->getDamageMgr();
    if (damage_mgr && damage_mgr->getField50() == 4)
        _128.mTimer.reset(*mIgnoreBombTime_s);
    changeChild("ふっとび");
}

// NON_MATCHING: state branches merge into shared bomb processing; timer stores and child dispatch differ.
void GolemReaction::calc_() {
    const f32 epsilon = std::numeric_limits<f32>::epsilon();
    if (!(_128.mTimer.value <= epsilon))
        _128.sub_7100D3BCE4();
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("死亡")) {
            callDeleteAndCreateDropAndEmit(mActor, 0);
            return;
        }
        // An unordered climb time also ends this reaction.
        if (!(static_cast<f32>(*mClimbLimitTime_s) <= *mGolemClimbedTime_a)) {
            setRootAiFlag(ksys::act::ai::RootAiFlag::_0);
            setFinished();
            return;
        }
        changeChild("振り落し");
    }
    if (_120) {
        _120 = false;
    } else {
        auto* damage = mActor->getDamageMgr();
        if (damage && damage->getField54() >= 6 && !isCurrentChild("死亡")) {
            if (sub_71005DD798(mActor, 0x13, nullptr, 0, 0)) {
                sub_71003FE9C4();
            } else {
                const bool shake_off = isCurrentChild("振り落し");
                damage = mActor->getDamageMgr();
                const s32 type = damage ? damage->getField54() : -1;
                const bool strong = type == 0x16 || type == 0x1b;
                bool bomb;
                bool chemical_reaction;
                if (shake_off) {
                    damage = mActor->getDamageMgr();
                    bomb = damage && damage->getField50() == 4;
                    chemical_reaction = sub_71003FEC7C();
                } else {
                    chemical_reaction = sub_71003FEC7C();
                    damage = mActor->getDamageMgr();
                    bomb = damage && damage->getField50() == 4;
                }
                damage = mActor->getDamageMgr();
                const bool climbed = damage && damage->getField54() <= 0x15 &&
                                     *mGolemClimbedTime_a > 0.0f;
                bool blow = false;
                bool right = false;
                bool left = false;
                if (bomb) {
                    auto* actor = mActor;
                    const s32 count = sub_71007A26AC(actor);
                    bool found = false;
                    for (s32 i = 0; i < count; ++i) {
                        auto* entry = sub_71007A255C(actor, i);
                        if (!entry || !(entry->_50 & 0x10))
                            continue;
                        if (_140 == entry->_d8 && !(_128.mTimer.value <= epsilon))
                            continue;
                        _140 = entry->_d8;
                        sub_71003FF3F8(&right, &left);
                        found = true;
                        break;
                    }
                    if (found) {
                        if (right || left) {
                            _128.mTimer.reset(static_cast<f32>(*mIgnoreBombTime_s));
                            if (right)
                                sub_71003FF79C(mBodyArmRName1_s, mBodyArmRName2_s, "",
                                               mRightArmTgtBodyName_s, mChmArmRName_s,
                                               mArmRMaterialName_s, mBreakArmRXLinkKey_s);
                            else
                                sub_71003FF79C(mBodyArmLName1_s, mBodyArmLName2_s, "",
                                               mLeftArmTgtBodyName_s, mChmArmLName_s,
                                               mArmLMaterialName_s, mBreakArmLXLinkKey_s);
                            blow = true;
                        } else {
                            blow = shake_off || chemical_reaction;
                        }
                    }
                } else if (shake_off) {
                    blow = strong || (!climbed && chemical_reaction);
                } else if (climbed && isCurrentChild("小ダメージ")) {
                    if (!(static_cast<f32>(*mClimbLimitTime_s) <= *mGolemClimbedTime_a))
                        changeChild("小ダメージ");
                    else
                        changeChild("振り落し");
                } else {
                    blow = strong || (chemical_reaction && !isCurrentChild("ふっとび"));
                }
                if (blow) {
                    if (!right && !left) {
                        damage = mActor->getDamageMgr();
                        if (damage && damage->getField50() == 4)
                            _128.mTimer.reset(static_cast<f32>(*mIgnoreBombTime_s));
                    }
                    changeChild("ふっとび");
                }
            }
        }
    }
    auto* life = mActor->getLife();
    if (life && *life <= 0 && !isCurrentChild("死亡")) {
        mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::Alive);
        changeChild("死亡");
    }
}

void GolemReaction::sub_71003FF79C(const sead::SafeString& body1, const sead::SafeString& body2,
                                  const sead::SafeString& str, const sead::SafeString& target,
                                  const sead::SafeString& chm, const sead::SafeString& material,
                                  const sead::SafeString& xlink_key) {
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (!enemy)
        return;
    if (auto* chemical = enemy->sub_71011D8A54(chm)) {
        auto* controller = sead::DynamicCast<Unk_7102450410>(
            *static_cast<Unk_71025afb58**>(mGolemChemicalController_a));
        if (controller) {
            if (auto* entry = controller->sub_7100708E90(chemical))
                entry->sub_7100708A0C();
        }
    }
    if (auto* physics = enemy->getPhysics()) {
        if (auto* body = enemy->findPhysicsBodyByName(sub_71007A24E4()->cstr(), body1.cstr()))
            body->setContactLayer(ksys::phys::ContactLayer::EntityNoHit);
        if (auto* body = enemy->findPhysicsBodyByName(sub_71007A24E4()->cstr(), body2.cstr()))
            body->setContactLayer(ksys::phys::ContactLayer::EntityNoHit);
        if (auto* body = enemy->findPhysicsBodyByName(sub_71007A250C()->cstr(), str.cstr()))
            body->setContactLayer(ksys::phys::ContactLayer::EntityNoHit);
        if (!material.isEmpty()) {
            sub_7100725960(mActor, material, false);
            sub_71007259CC(mActor, material, false);
        }
        if (auto* body = physics->findX(*sub_71007A24D0(), target))
            body->setContactLayer(ksys::phys::ContactLayer::SensorNoHit);
    }
    xlinkSearchAndEmit(mActor, xlink_key.cstr(), 2, nullptr);
}

void GolemReaction::leave_() {
    sub_7100708FF0(mActor, 200.0f);
    mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_80000000);
}

void GolemReaction::loadParams_() {
    getStaticParam(&mClimbLimitTime_s, "ClimbLimitTime");
    getStaticParam(&mClampRestClimbTime_s, "ClampRestClimbTime");
    getStaticParam(&mIgnoreBombTime_s, "IgnoreBombTime");
    getStaticParam(&mRightArmTgtBodyName_s, "RightArmTgtBodyName");
    getStaticParam(&mLeftArmTgtBodyName_s, "LeftArmTgtBodyName");
    getStaticParam(&mBreakArmLXLinkKey_s, "BreakArmLXLinkKey");
    getStaticParam(&mBodyArmLName1_s, "BodyArmLName1");
    getStaticParam(&mBodyArmLName2_s, "BodyArmLName2");
    getStaticParam(&mChmArmLName_s, "ChmArmLName");
    getStaticParam(&mArmLMaterialName_s, "ArmLMaterialName");
    getStaticParam(&mBreakArmRXLinkKey_s, "BreakArmRXLinkKey");
    getStaticParam(&mBodyArmRName1_s, "BodyArmRName1");
    getStaticParam(&mBodyArmRName2_s, "BodyArmRName2");
    getStaticParam(&mChmArmRName_s, "ChmArmRName");
    getStaticParam(&mArmRMaterialName_s, "ArmRMaterialName");
    getAITreeVariable(&mGolemClimbedTime_a, "GolemClimbedTime");
    getAITreeVariable(&mGolemChemicalController_a, "GolemChemicalController");
}

bool GolemReaction::sub_71003FEC7C() {
    if (auto* damage_mgr = mActor->getDamageMgr()) {
        if (damage_mgr->getField54() == 21 || damage_mgr->checkDamageFlags(0))
            return true;
    }
    auto* controller = sead::DynamicCast<Unk_7102450410>(
        *static_cast<Unk_71025afb58**>(mGolemChemicalController_a));
    return sub_71007090F4(controller);
}

void GolemReaction::sub_71003FE9C4() {
    auto* damage = mActor->getDamageMgr();
    if (damage && damage->getField50() == 4) {
        bool right = false;
        bool left = false;
        sub_71003FF3F8(&right, &left);
        if (left) {
            sub_71003FF79C(mBodyArmLName1_s, mBodyArmLName2_s, "", mLeftArmTgtBodyName_s,
                           mChmArmLName_s, mArmLMaterialName_s, mBreakArmLXLinkKey_s);
        }
        if (right) {
            sub_71003FF79C(mBodyArmRName1_s, mBodyArmRName2_s, "", mRightArmTgtBodyName_s,
                           mChmArmRName_s, mArmRMaterialName_s, mBreakArmRXLinkKey_s);
        }
    }
}

bool GolemReaction::sub_71003FEAB0() {
    auto* damage = mActor->getDamageMgr();
    if (damage && damage->getField50() == 4) {
        auto* actor = mActor;
        const s32 num = sub_71007A26AC(actor);
        for (s32 i = 0; i < num; ++i) {
            auto* info = sub_71007A255C(actor, i);
            if (info && (info->_50 & 0x10)) {
                if (!(_140 == info->_d8) || _128.mTimer.value <= sead::Mathf::epsilon()) {
                    _140 = info->_d8;
                    bool right = false;
                    bool left = false;
                    sub_71003FF3F8(&right, &left);
                    if (!right) {
                        if (!left)
                            return false;
                        _128.mTimer.reset(f32(*mIgnoreBombTime_s));
                        sub_71003FF79C(mBodyArmLName1_s, mBodyArmLName2_s, "", mLeftArmTgtBodyName_s,
                                       mChmArmLName_s, mArmLMaterialName_s, mBreakArmLXLinkKey_s);
                    } else {
                        _128.mTimer.reset(f32(*mIgnoreBombTime_s));
                        sub_71003FF79C(mBodyArmRName1_s, mBodyArmRName2_s, "", mRightArmTgtBodyName_s,
                                       mChmArmRName_s, mArmRMaterialName_s, mBreakArmRXLinkKey_s);
                    }
                    changeChild("ふっとび");
                    return true;
                }
            }
        }
    }
    return false;
}

}  // namespace uking::ai
