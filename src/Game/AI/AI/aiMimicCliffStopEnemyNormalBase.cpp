#include "Game/AI/AI/aiMimicCliffStopEnemyNormalBase.h"
#include "Game/AI/aiAwarenessFilters.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007368A4.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Map/mapPlacementMgr.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/System/physRayCastBodyQuery.h"
#include "KingSystem/System/VFR.h"
#include "KingSystem/System/Timer.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::ai {

MimicCliffStopEnemyNormalBase::MimicCliffStopEnemyNormalBase(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

MimicCliffStopEnemyNormalBase::~MimicCliffStopEnemyNormalBase() = default;

bool MimicCliffStopEnemyNormalBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void MimicCliffStopEnemyNormalBase::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    if (auto* awareness = actor->getAwareness())
        awareness->enable();

    _1dc = 0xff;
    _80 = 0;
    if (sub_71005DCF80(&_80, actor, actor->getMtx().getBase(1) * -7.0f, false)) {
        sub_71005DD27C(actor, _80, 1.0f);
        *mMimicryMaterial_a = _80;
        _1dc = 0;
    }

    sub_71005DD34C(mActor, false);
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
        enemy->_e84.set(0x10000);
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F62BB0();

    _7c = 0;
    _88.setName("Spine_1");
    _130.setName("Waist");
    actor->boneHandleStuff(&_88, false);
    actor->boneHandleStuff(&_130, false);
    _1d8 = 0;
    changeChild("待機");
}

// NON_MATCHING: the original keeps a "found" flag and one filter destructor call per sensor block and
// copies the entry position element-wise (both blocks match when written as one inline helper with
// an output pointer)
void MimicCliffStopEnemyNormalBase::calc_() {
    sub_7100352994();
    sub_7100352B60();
    if (_7c > 0)
        ksys::Timer::update(&_7c, -1.0f);

    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        changeChild("待機");
        return;
    }
    if (!child->isChangeable())
        return;

    if (isCurrentChild("音気づき")) {
        if (sub_7100352D14())
            return;

        if (auto* awareness = mActor->getAwareness()) {
            bool found = false;
            sead::Vector3f pos;
            {
                Unk_7102451678 filter;
                auto* sensor = awareness->_260[1];
                if (sensor && sensor->_8.size() >= 1) {
                    if (auto* entry = ksys::act::sub_7100D78E30(&sensor->_8, 0)) {
                        pos = entry->_88;
                        found = true;
                    }
                }
            }
            if (found) {
                _70 = pos;
                child->setDynamicParam(_70, "TargetPos");
                _7c = *mNoticeSoundTime_s;
                return;
            }
        }

        if (_7c <= 0)
            changeChild("待機");
    } else if (isCurrentChild("待機")) {
        if (_1dc == 0xff) {
            if (ksys::map::PlacementMgr::instance()->isStaticCompoundReady(
                    mActor->getMtx().getTranslation(), false)) {
                if (sub_71005DCF80(&_80, mActor, mActor->getMtx().getBase(1) * -7.0f, true)) {
                    sub_71005DD27C(mActor, _80, 1.0f);
                    *mMimicryMaterial_a = _80;
                    _1dc = 0;
                } else {
                    _1dc = 1;
                }
            }
        }

        sub_71005DD34C(mActor, false);
        if (sub_7100352D14())
            return;

        if (auto* awareness = mActor->getAwareness()) {
            bool found = false;
            sead::Vector3f pos;
            {
                Unk_7102451678 filter;
                auto* sensor = awareness->_260[1];
                if (sensor && sensor->_8.size() >= 1) {
                    if (auto* entry = ksys::act::sub_7100D78E30(&sensor->_8, 0)) {
                        pos = entry->_88;
                        found = true;
                    }
                }
            }
            if (found) {
                _70 = pos;
                _7c = *mNoticeSoundTime_s;
                ksys::act::ai::InlineParamPack params;
                params.addVec3(_70, "TargetPos", -1);
                changeChild("音気づき", &params);
            }
        }
    }
}

void MimicCliffStopEnemyNormalBase::sub_7100352994() {
    const auto& mtx = mActor->getMtx();
    sead::Vector3f front;
    mtx.getBase(front, 2);
    sead::Vector3f pos;
    mtx.getTranslation(pos);

    sead::Vector3f dir;
    sub_710035307C(&dir, *mOffsetHand_s);
    dir -= pos + front * *mOffsetHandRotBase_s;
    dir.normalize();

    sead::Vector3f axis;
    f32 angle;
    ksys::util::sub_71011EEB08(&axis, &angle, front, dir, sead::Vector3f::ey);
    ksys::VFR::lerp(&_1d8, axis.x * angle, 0.25f, sead::Mathf::deg2rad(13), sead::Mathf::deg2rad(3));
    sead::Matrix34f rot;
    rot.makeR({0, 0, _1d8});
    _88._68 = rot;
}

void MimicCliffStopEnemyNormalBase::sub_7100352B60() {
    const auto& mtx = mActor->getMtx();
    sead::Vector3f front;
    mtx.getBase(front, 2);
    sead::Vector3f side;
    mtx.getBase(side, 0);
    sead::Vector3f pos;
    mtx.getTranslation(pos);

    sead::Vector3f dir;
    sub_710035307C(&dir, *mOffsetTail_s);
    dir = -(dir - pos);
    ksys::util::sub_71011EFA00(&dir, dir, side);
    dir.normalize();

    sead::Vector3f axis;
    f32 angle;
    ksys::util::sub_71011EEB08(&axis, &angle, front, dir, sead::Vector3f::ey);
    sead::Matrix34f rot;
    rot.makeR({0, 0, axis.x * angle});
    _130._68 = rot;
}

// NON_MATCHING: stack layout (the original's parameter pack and name temporary lie above the filter)
bool MimicCliffStopEnemyNormalBase::sub_7100352D14() {
    auto* actor = mActor;
    auto* awareness = actor->getAwareness();
    if (!awareness)
        return false;

    Unk_7102451678 filter;
    auto* sensor = awareness->_260[0];
    if (!sensor)
        return false;
    auto* entry = ksys::act::sub_7100D7EEE8(&sensor->_8, &filter);
    if (!entry)
        return false;
    if (enemyTeamStuff(mActor, &entry->_0.mLink))
        return false;

    sub_71005D8DE8(actor, entry->_0.mLink, &entry->_58, nullptr);
    ksys::act::ai::InlineParamPack params;
    params.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    changeChild("気づき", &params);
    return true;
}

void MimicCliffStopEnemyNormalBase::sub_710035307C(sead::Vector3f* out, f32 offset) {
    auto* actor = mActor;
    sead::Vector3f pos;
    actor->getMtx().getTranslation(pos);
    ksys::phys::RayCastBodyQuery query(nullptr, ksys::phys::GroundHit::HitAll);

    pos += actor->getMtx().getBase(2) * offset;
    const sead::Vector3f up = actor->getMtx().getBase(1);
    query.setStartAndEnd(pos + up, pos - up * 8.0f);
    query.enableLayer(ksys::phys::ContactLayer::EntityGround);
    query.enableLayer(ksys::phys::ContactLayer::EntityGroundRough);
    query.enableLayer(ksys::phys::ContactLayer::EntityGroundObject);
    if (query.worldRayCast(ksys::phys::ContactLayerType::Entity))
        query.getHitPosition(out);
}

void MimicCliffStopEnemyNormalBase::leave_() {
    auto* actor = mActor;
    *mIsStartResetMimicry_a = true;
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (enemy && !enemy->m151(3))
        enemy->_e84.reset(0x10000);
    else
        *mIsCliffFreeze_a = true;

    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F62BB8();
    sub_71005DD34C(mActor, true);
    if (auto* awareness = actor->getAwareness())
        awareness->disable();
    actor->sub_71011DA868(&_88);
    actor->sub_71011DA868(&_130);
}

void MimicCliffStopEnemyNormalBase::loadParams_() {
    getStaticParam(&mNoticeSoundTime_s, "NoticeSoundTime");
    getStaticParam(&mOffsetHand_s, "OffsetHand");
    getStaticParam(&mOffsetTail_s, "OffsetTail");
    getStaticParam(&mOffsetHandRotBase_s, "OffsetHandRotBase");
    getAITreeVariable(&mMimicryMaterial_a, "MimicryMaterial");
    getAITreeVariable(&mIsStartResetMimicry_a, "IsStartResetMimicry");
    getAITreeVariable(&mIsCliffFreeze_a, "IsCliffFreeze");
}

}  // namespace uking::ai
