#include "Game/Actor/Action/actionGanonChemicalPillarAttack.h"
#include <math/seadQuat.h>
#include <random/seadGlobalRandom.h>
#include "Game/Actor/Player/actPlayerInfo.h"
#include "KingSystem/Physics/System/physRayCastBodyQuery.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/Actor/actEnemy.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actActorHeapUtil.h"
#include "KingSystem/ActorSystem/actInstParamPack.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include <limits>
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::action {

GanonChemicalPillarAttack::GanonChemicalPillarAttack(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

GanonChemicalPillarAttack::~GanonChemicalPillarAttack() {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        if (mPillarNum_s) {
            for (s32 i = 0; i <= *mPillarNum_s; ++i) {
                const sead::FormatFixedSafeString<64> name("IronPile%d", i);
                if (enemy->getActorPartsActor(name).hasProc()) {
                    ksys::act::ActorLinkConstDataAccess accessor;
                    ksys::act::acquireActor(&enemy->getActorPartsActor(name), &accessor);
                    accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
                }
                enemy->sub_7100D3CFEC(name);
            }
        }
    }
}

// NON_MATCHING: register allocation of the offset and the pile rotation products.
void GanonChemicalPillarAttack::sub_7100178498(s32 index) {
    ksys::phys::RayCastBodyQuery query(nullptr, ksys::phys::GroundHit::HitAll);
    query.enableLayer(ksys::phys::ContactLayer::EntityGround);
    query.enableLayer(ksys::phys::ContactLayer::EntityGroundRough);
    query.enableLayer(ksys::phys::ContactLayer::EntityGroundObject);

    sead::Vector3f pos = _d8;
    const f32 distance = *mAppearPosDist_s;
    if (u32(index) >= 2) {
        sead::Vector3f offset;
        if (u32(index) >= 6) {
            pos = *mTargetPos_d;
            offset = sead::Vector3f::zero;
            if (sub_710072B6C8()) {
                const f32 x = sead::GlobalRandom::instance()->getF32Range(3.0f, 6.0f);
                const f32 z = sead::GlobalRandom::instance()->getF32Range(3.0f, 6.0f);
                const f32 sign_x = s32((sead::GlobalRandom::instance()->getU32() & 2) - 1);
                const f32 sign_z = s32((sead::GlobalRandom::instance()->getU32() & 2) - 1);
                offset.x = x * sign_x;
                offset.z = z * sign_z;
            }
        } else {
            sead::Quatf rotation;
            rotation.setAxisRadian(sead::Vector3f::ey,
                                   f32(u32(index - 1)) * (sead::Mathf::pi2() / 5));
            sead::Matrix34f rotation_mtx;
            rotation_mtx.fromQuat(rotation);
            offset = {distance, 0, 0};
            offset.rotate(rotation_mtx);
        }
        pos += offset;
    } else if (index != 0) {
        pos += sead::Vector3f(distance, 0, 0);
    }
    pos.y += *mAppearPosHeight_s;
    query.setStartAndDisplacementScaled(pos, {0.0f, -1.0f, 0.0f}, *mAppearPosHeight_s);
    sead::Vector3f hit_pos = pos;
    if (query.worldRayCast(ksys::phys::ContactLayerType::Entity)) {
        query.getHitPosition(&hit_pos);
        hit_pos.y += *mAppearPosHeight_s;
    }
    const sead::Matrix34f mtx(sead::Matrix33f::ident, hit_pos);

    const sead::FormatFixedSafeString<64> name("IronPile%d",
                                               index + (_c8 <= index && _c8 >= 0));
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        if (enemy->getActorPartsActor(name).hasProc()) {
            ksys::act::ActorLinkConstDataAccess accessor;
            ksys::act::acquireActor(&enemy->getActorPartsActor(name), &accessor);
            if (accessor.isStateSleep()) {
                const sead::Vector3f scale{*mPileScale_s, *mPileScale_s, *mPileScale_s};
                accessor.setProperties(mtx, nullptr, nullptr, &scale, false, 0, -1);
            }
        }
    }
}

s32 GanonChemicalPillarAttack::sub_71001788F4() {
    const s32 start = _c0;
    if (_cc != -1)
        return start > _cc ? start : start - 1;

    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        for (u32 i = start; i < 19; ++i) {
            const sead::FormatFixedSafeString<64> name("IronPile%d", i);
            if (enemy->getActorPartsActor(name).hasProc()) {
                ksys::act::ActorLinkConstDataAccess accessor;
                ksys::act::acquireActor(&enemy->getActorPartsActor(name), &accessor);
                if (accessor.sub_7100D13BB8()) {
                    const sead::Vector3f diff =
                        accessor.getActorMtx().getTranslation() - mActor->getMtx().getTranslation();
                    if (diff.squaredLength() <= 16.0f) {
                        _cc = i;
                        return i;
                    }
                }
            }
        }
    }
    return start;
}

bool GanonChemicalPillarAttack::sub_7100178AA0() {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        for (u32 i = 0; i < 19; ++i) {
            const sead::FormatFixedSafeString<64> name("IronPile%d", i);
            if (enemy->getActorPartsActor(name).hasProc()) {
                ksys::act::ActorLinkConstDataAccess accessor;
                ksys::act::acquireActor(&enemy->getActorPartsActor(name), &accessor);
                if (accessor.isStateCalc() && !accessor.sub_7100D13BB8())
                    return false;
            }
        }
    }
    return true;
}

void GanonChemicalPillarAttack::sub_7100178DC4(s32 index, ksys::act::ActorLinkConstDataAccess* accessor) {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        const sead::FormatFixedSafeString<64> name("IronPile%d", index);
        if (enemy->getActorPartsActor(name).hasProc())
            ksys::act::acquireActor(&enemy->getActorPartsActor(name), accessor);
    }
}

bool GanonChemicalPillarAttack::init_(sead::Heap* heap) {
    if (sub_71005D6D10())
        return true;
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (!enemy)
        return true;

    ksys::act::InstParamPack params;
    params->add(sead::SafeString("Normal"), "DropTable");
    params->add(false, "EnableRevival");
    params->add(false, "IsFixedPlace");
    params->add(true, "IsInGround");
    params->add(*mAttackPower_s, "AttackPower");
    params->add(*mAttackPowerForPlayer_s, "AttackPowerForPlayer");
    params->add(*mAtMinPower_s, "AtMinDamage");
    params->add(0, "AddAtkPower");
    params->add(mCreateActorName_s, "ActorName");

    for (int i = 0; i <= *mPillarNum_s; ++i) {
        sead::FormatFixedSafeString<64> name("IronPile%d", i);
        enemy->_1128.sub_7100D3CED8(name, heap);
        auto* actor = ksys::act::ActorCreator::instance()->createActor(
            "GanonIronPile", ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(), &params, true,
            false);
        if (actor) {
            actor->clearFadeInCreate();
            enemy->_1128.sub_7100D3D108(name, actor);
        }
    }
    return true;
}

// NON_MATCHING: the original keeps `_b8` / `_b9` as two byte stores (no strh merge) and schedules the stores of the
// final block differently (_c8 load before the third word of *mTargetPos_d, `_cc` store last).
void GanonChemicalPillarAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    _e4 = ksys::Timer(0.0f, 0.0f);
    _b9 = true;
    _b8 = true;
    auto* actor = mActor;
    _ba = false;
    _bc = 0;
    _c8 = -1;
    if (auto* enemy = sead::DynamicCast<act::Enemy>(actor)) {
        for (s32 i = 0; i <= *mPillarNum_s; ++i) {
            const sead::FormatFixedSafeString<64> name("IronPile%d", i);
            if (enemy->getActorPartsActor(name).hasProc()) {
                ksys::act::ActorLinkConstDataAccess accessor;
                ksys::act::acquireActor(&enemy->getActorPartsActor(name), &accessor);
                if (accessor.sub_7100D13BB8()) {
                    _c8 = i;
                } else {
                    enemy->sendMessage(*accessor.getMessageTransceiverId(),
                                       ksys::MessageType(0x8000004), nullptr, true);
                }
            }
        }
        if (!mCreatePileASName_s.isEmpty())
            playAS(mCreatePileASName_s.cstr(), false, 0, 0, -1.0f);
        else if (!mWaitASName_s.isEmpty())
            playAS(mWaitASName_s.cstr(), false, 0, 0, -1.0f);
        _d8 = *mTargetPos_d;
        _c0 = 0;
        _d0 = 0;
        _d4 = 120.0f;
        _c4 = _c8 == -1 ? *mPillarNum_s : *mPillarNum_s + 1;
        _cc = -1;
        mFlags.set(Flag::Changeable);
    }
}

void GanonChemicalPillarAttack::leave_() {
    sub_71005D74E8(mActor);
}

void GanonChemicalPillarAttack::loadParams_() {
    getStaticParam(&mAttackPower_s, "AttackPower");
    getStaticParam(&mAtMinPower_s, "AtMinPower");
    getStaticParam(&mAttackPowerForPlayer_s, "AttackPowerForPlayer");
    getStaticParam(&mPillarNum_s, "PillarNum");
    getStaticParam(&mPillarInterval_s, "PillarInterval");
    getStaticParam(&mPillarOffset_s, "PillarOffset");
    getStaticParam(&mAppearPosDist_s, "AppearPosDist");
    getStaticParam(&mAppearPosHeight_s, "AppearPosHeight");
    getStaticParam(&mIgnitionInterval_s, "IgnitionInterval");
    getStaticParam(&mPileScale_s, "PileScale");
    getStaticParam(&mCreateActorName_s, "CreateActorName");
    getStaticParam(&mASName_s, "ASName");
    getStaticParam(&mWaitASName_s, "WaitASName");
    getStaticParam(&mCreatePileASName_s, "CreatePileASName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

// NON_MATCHING: the original branches straight to the shared tail where this keeps a "created" flag, and
// compares the pillar index unsigned.
void GanonChemicalPillarAttack::calc_() {
    if (_b8) {
        _b8 = false;
        return;
    }

    auto* controller = mActor->getCharacterController();
    if (!controller) {
        setFailed();
        return;
    }
    controller->sub_7100F5F6FC(sead::Vector3f::zero);
    controller->sub_7100F5FB24(sead::Vector3f::zero);
    sub_71005D7444(mActor, *mTargetPos_d, true, true);

    if (_b9) {
        _e4.update();
        if (_e4.value <= std::numeric_limits<f32>::epsilon()) {
            sub_7100178498(_bc);
            ++_bc;
            if (_bc < *mPillarNum_s / 2)
                playAS(mASName_s.cstr(), true, 0, 0, -1.0f);
            if (_bc < *mPillarNum_s)
                _e4 = ksys::Timer(*mIgnitionInterval_s, *mIgnitionInterval_s);
            else
                _b9 = false;
        }
    }

    if (sub_71005DD780(mActor, 0x47, nullptr, 0, 0)) {
        _ba = true;
        _d0 = f32(*mPillarInterval_s);
        return;
    }
    if (!_ba)
        return;

    if (isFinishedAS(0, 0))
        playAS(mWaitASName_s.cstr(), false, 0, 0, -1.0f);

    const f32 prev = _d0;
    ksys::Timer::update(&_d0, -1.0f);
    if (_d0 > 0.0f)
        return;

    if (prev > 0.0f) {
        sub_71001788F4();
        bool created = true;
        if (_c0 <= 18) {
            ksys::act::ActorLinkConstDataAccess accessor;
            sub_7100178DC4(_c0, &accessor);
            if (accessor.isStateCalc()) {
                mActor->sendMessage(*accessor.getMessageTransceiverId(),
                                    ksys::MessageType(0x800005b), nullptr, true);
            } else {
                created = false;
            }
        }
        if (created) {
            _d4 = 120.0f;
            ++_c0;
        } else {
            ksys::Timer::update(&_d4, -2.0f);
            if (_d4 < 0.0f)
                setFinished();
        }
        if (_c0 < _c4) {
            _ba = true;
            _d0 = f32(*mPillarInterval_s);
            return;
        }
    } else if (_c0 < _c4) {
        return;
    }

    ksys::Timer::update(&_d4, -1.0f);
    if (sub_7100178AA0() || _d4 < 0.0f)
        setFinished();
}

}  // namespace uking::action
