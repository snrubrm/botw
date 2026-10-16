#include "Game/Actor/Action/actionSiteBossLswordAtkWithChemical.h"
#include "Game/Actor/actEnemy.h"
#include "Game/Actor/actSiteBoss.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actActorHeapUtil.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actInstParamPack.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActorAtk.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physCollisionInfo.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include "KingSystem/Physics/System/physRayCastBodyQuery.h"
#include "KingSystem/Utils/MathUtil.h"
#include <math/seadQuat.h>
#include <limits>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "Game/Actor/Player/actPlayerInfo.h"

namespace uking::action {

SiteBossLswordAtkWithChemical::SiteBossLswordAtkWithChemical(const InitArg& arg)
    : SiteBossLswordAttack(arg), _1c8() {}

SiteBossLswordAtkWithChemical::~SiteBossLswordAtkWithChemical() {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        if (mEmitNum_s) {
            for (s32 i = 0; i < *mEmitNum_s * 2; ++i) {
                const sead::FormatFixedSafeString<32> name("%s%d", mEmitPartsName_s.cstr(), i);
                if (enemy->getActorPartsActor(name).hasProc()) {
                    ksys::act::ActorLinkConstDataAccess accessor;
                    ksys::act::acquireActor(&enemy->getActorPartsActor(name), &accessor);
                    accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
                }
                enemy->sub_7100D3CFEC(name);
            }
        }
    }
    _1a0 = nullptr;
    _1a8.freeBuffer();
    _1b8.freeBuffer();
}

bool SiteBossLswordAtkWithChemical::init_(sead::Heap* heap) {
    if (!SiteBossLswordAttack::init_(heap))
        return false;

    if (!sub_71005D6D10()) {
        ksys::act::InstParamPack params;
        s32 level = getNumberOfDeadBlights();
        if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor)) {
            const s32 kind = boss->_1534 & ~3;
            if (kind == 4)
                level = 3;
            else if (kind == 8)
                level = 4;
        }
        const s32 add_power = *mAddAttackPower_s * level;
        const s32 attack_power = *mEmitAttackDamage_s + add_power;
        const s32 min_damage = *mEmitActorMinDamage_s + add_power;
        params->add(attack_power, "AttackPower");
        params->add(*mScaleTime_s, "ScaleTime");
        params->add(min_damage, "AtMinDamage");

        if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
            for (s32 i = 0; i < *mEmitNum_s * 2; ++i) {
                const sead::FormatFixedSafeString<32> name("%s%d", mEmitPartsName_s.cstr(), i);
                ksys::act::BaseProc* proc = ksys::act::ActorCreator::instance()->createActor(
                    mEmitActorName_s.cstr(), ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(),
                    &params, true, false);
                if (auto* actor = sead::DynamicCast<ksys::act::Actor>(proc)) {
                    enemy->_1128.sub_7100D3CED8(name, heap);
                    enemy->_1128.sub_7100D3D108(name, actor);
                }
            }
        }
    }

    if (!_1a0)
        _1a0 = mActor->findPhysicsBodyByName(sub_71007A250C()->cstr(), "BgSensor");
    _1a8.tryAllocBuffer(*mEmitNum_s, heap);
    _1b8.tryAllocBuffer(*mEmitNum_s, heap);
    return true;
}

void SiteBossLswordAtkWithChemical::enter_(ksys::act::ai::InlineParamPack* params) {
    SiteBossLswordAttack::enter_(params);
    _188 = false;
    _189 = false;
    _18a = false;
    _198 = 0;
    _18c = ksys::Timer(*mEmitStartFrame_s, *mEmitStartFrame_s, 0.0f);
    for (s32 i = 0, n = _1a8.size(); i < n; ++i)
        _1a8(i) = false;
    for (s32 i = 0, n = _1b8.size(); i < n; ++i)
        _1b8(i) = sead::Vector3f::zero;
}

void SiteBossLswordAtkWithChemical::leave_() {
    SiteBossLswordAttack::leave_();
    if (sub_710072B7C4() || _189)
        sub_710025B7CC();
}

void SiteBossLswordAtkWithChemical::loadParams_() {
    SiteBossLswordAttack::loadParams_();
    getStaticParam(&mEmitNum_s, "EmitNum");
    getStaticParam(&mEmitInterval_s, "EmitInterval");
    getStaticParam(&mEmitAttackDamage_s, "EmitAttackDamage");
    getStaticParam(&mEmitActorMinDamage_s, "EmitActorMinDamage");
    getStaticParam(&mEmitOffsetFromParent_s, "EmitOffsetFromParent");
    getStaticParam(&mEmitIntervalDist_s, "EmitIntervalDist");
    getStaticParam(&mEmitIntervalRotate_s, "EmitIntervalRotate");
    getStaticParam(&mEmitScale_s, "EmitScale");
    getStaticParam(&mEmitMaxScale_s, "EmitMaxScale");
    getStaticParam(&mScaleTime_s, "ScaleTime");
    getStaticParam(&mEmitStartFrame_s, "EmitStartFrame");
    getStaticParam(&mEmitAngleFromParent_s, "EmitAngleFromParent");
    getStaticParam(&mEmitActorSpeedRotate_s, "EmitActorSpeedRotate");
    getStaticParam(&mEmitActorName_s, "EmitActorName");
    getStaticParam(&mEmitPartsName_s, "EmitPartsName");
    getStaticParam(&mCallSEKeyAtAtOn_s, "CallSEKeyAtAtOn");
    getStaticParam(&mEmitActorSpeed_s, "EmitActorSpeed");
}

// NON_MATCHING: register allocation around the index conversion only.
bool SiteBossLswordAtkWithChemical::sub_710025B4B0(int index) {
    sead::Matrix34f base_mtx;
    ksys::util::sub_71011F0260(&base_mtx, sead::Vector3f::ez, sead::Vector3f::ey,
                               sead::Vector3f::zero, false);

    sead::Vector3f pos;
    m37(&pos);
    const sead::Matrix34f mtx = mActor->getMtx();
    const f32 base_dist = m38();
    const f32 i = f32(u32(index));
    const f32 dist = base_dist + i * *mEmitIntervalDist_s;
    sead::Quatf rotation;
    rotation.setAxisRadian(sead::Vector3f::ey, *mEmitAngleFromParent_s + i * *mEmitIntervalRotate_s);
    sead::Matrix34f rotation_mtx;
    rotation_mtx.fromQuat(rotation);
    sead::Vector3f offset{0.0f, 0.0f, dist};
    offset.rotate(mtx);
    offset.rotate(rotation_mtx);
    pos += offset;

    ksys::phys::RayCastBodyQuery query(nullptr, ksys::phys::GroundHit::HitAll);
    query.enableLayer(ksys::phys::ContactLayer::EntityGround);
    query.enableLayer(ksys::phys::ContactLayer::EntityGroundRough);
    query.enableLayer(ksys::phys::ContactLayer::EntityGroundObject);
    sead::Vector3f start = pos;
    start.y += 5.0f;
    query.setStartAndDisplacementScaled(start, {0.0f, -1.0f, 0.0f}, 8.0f);
    sead::Vector3f hit_pos = pos;
    bool hit = false;
    if (query.worldRayCast(ksys::phys::ContactLayerType::Entity)) {
        query.getHitPosition(&hit_pos);
        _1b8[index] = hit_pos;
        hit = true;
    }
    return hit;
}

// NON_MATCHING: the final emit-all loop (the original guards with num != 0 and loops unsigned).
void SiteBossLswordAtkWithChemical::calc_() {
    SiteBossLswordAttack::calc_();

    if (sub_71005DD780(mActor, 0x3b, nullptr, 0, 0) && _1a0 && _1a0->getCollisionInfo() &&
        _1a0->getCollisionInfo()->getCollidingBodies().size() != 0) {
        ksys::eft::searchAndEmitSLink(mActor, "StraightAttackSwing_HitGround", false);
    }

    auto* boss = sead::DynamicCast<act::SiteBoss>(mActor);
    if (!boss || !boss->_1558.isOnBit(0))
        return;

    ksys::as::ASList::Unk4 query;
    if (sub_71005DD66C(mActor, &query, 0, 0) && !_188) {
        _188 = true;
        _18c = ksys::Timer(*mEmitStartFrame_s, *mEmitStartFrame_s);
        bool emitted = false;
        for (s32 i = 0; i < *mEmitNum_s; ++i) {
            const bool result = sub_710025B4B0(i);
            _1a8[i] = result;
            emitted |= result;
        }
        if (emitted && !mCallSEKeyAtAtOn_s.isEmpty()) {
            xlinkSearchAndEmit(mActor, mCallSEKeyAtAtOn_s.cstr(), 1, &_1c8);
            _18a = true;
        }
    }

    if (_188) {
        if (sub_710072B7C4()) {
            _189 = true;
            sub_710025B7CC();
        } else {
            const s32 num = getNumAttackInfoMaybe(mActor);
            for (s32 i = 0; i < num; ++i) {
                auto* info = getAttackInfo(mActor, i);
                if (info && (info->_18 & 2)) {
                    _189 = true;
                    sub_710025B7CC();
                    break;
                }
            }
        }
    }

    _18c.update();
    if (_18c.value <= std::numeric_limits<f32>::epsilon()) {
        const s32 interval = *mEmitInterval_s;
        const s32 num = *mEmitNum_s;
        if (interval >= 1) {
            if (num > _198) {
                sub_710025B95C(_198);
                _18c = ksys::Timer(f32(*mEmitInterval_s), f32(*mEmitInterval_s));
                ++_198;
            }
        } else if (num > _198 && num != 0) {
            for (s32 i = 0; i < *mEmitNum_s; ++i)
                sub_710025B95C(i);
        }
    }
}

void SiteBossLswordAtkWithChemical::m37(sead::Vector3f* pos) {
    mActor->getMtx().getTranslation(*pos);
}

f32 SiteBossLswordAtkWithChemical::m38() {
    return *mEmitOffsetFromParent_s;
}

int SiteBossLswordAtkWithChemical::m39() {
    return 2;
}

}  // namespace uking::action

namespace uking::action {

// Sleeps the emitted parts actors and fades the held xlink event.
void SiteBossLswordAtkWithChemical::sub_710025B7CC() {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        if (*mEmitNum_s >= 1) {
            for (s32 i = 0; i < *mEmitNum_s * 2; ++i) {
                const sead::FormatFixedSafeString<32> name("%s%d", mEmitPartsName_s.cstr(), i);
                if (enemy->getActorPartsActor(name).hasProc()) {
                    ksys::act::ActorLinkConstDataAccess accessor;
                    ksys::act::acquireActor(&enemy->getActorPartsActor(name), &accessor);
                    if (accessor.isStateCalc())
                        accessor.sleep(ksys::act::BaseProc::SleepWakeReason::_0);
                }
            }
        }
    }
    if (!mCallSEKeyAtAtOn_s.isEmpty() && _18a) {
        if (_1c8.sub_7101241AD8(1))
            _1c8.fadeXLink();
    }
}

}  // namespace uking::action
