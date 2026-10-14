#include "Game/Actor/AI/aiEnemyNoiseTarget.h"
#include "Game/Actor/actEnemy.h"
#include "Game/Actor/actWeapon.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "Game/Actor/aiUnk_710073033C.h"
#include "Game/Actor/aiUnk_71007320F0.h"
#include "Game/gameUnk_71024739d0.h"
#include <random/seadGlobalRandom.h>
#include "KingSystem/Physics/System/physNavMeshCharacter.h"
#include "Game/Actor/aiAwarenessFilters.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

void EnemyNoiseTarget::sub_710039B064() {
    _d8 = false;
    if (auto* holder = sub_71005E2BCC(mActor)) {
        holder->_8 = -1;
        holder->_c = 0;
    }
    _bc = _ac;
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(_ac, "TargetPos", -1);
    changeChild("到達不能", &pack);
}

bool EnemyNoiseTarget::sub_710039B164() {
    const s32 weapon_idx = *mNoShieldEquipWpIdx_s;
    if (weapon_idx >= 0 && sub_71005D83E8(mActor, weapon_idx))
        return false;
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (!enemy || !enemy->_f54.isOnBit(4))
        return false;
    if (sub_71005DBB60(mActor, *mWeaponIdx_s))
        return false;
    return sub_71005DB96C(mActor) < 0;
}

bool EnemyNoiseTarget::sub_710039B240(ksys::act::BaseProcLink* out) {
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (enemy && !enemy->sub_7100016284(*mShieldIdx_s) && !enemy->sub_71000161A4(*mShieldIdx_s)) {
        auto& link = enemy->_c38[*mShieldIdx_s];
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(&link, &accessor);
        if (link.hasProcInCalcState() && !accessor.sub_7100D13448(-1)) {
            if (out)
                out->acquire(sead::DynamicCast<act::Weapon>(link.getProc(nullptr, nullptr)), false);
            return true;
        }
    }
    return false;
}

void EnemyNoiseTarget::sub_710039B400() {
    ksys::act::ai::InlineParamPack pack;
    pack.acquireActor(sead::DynamicCast<ksys::act::Actor>(_c8.getProc(nullptr, nullptr)),
                      "TargetWeapon", -1);
    changeChild("盾拾い", &pack);
}

// NON_MATCHING: accessor/vector stack slots and shared cleanup registers differ.
bool EnemyNoiseTarget::sub_710039B54C() {
    auto* actor = mActor;
    auto* awareness = actor->getAwareness();
    bool result = false;
    if (awareness) {
        if (auto* enemy = sead::DynamicCast<act::Enemy>(actor)) {
            ksys::act::acc::Weapon accessor;
            Unk_7102451808 filter;
            while (auto* entry = ksys::act::sub_7100D7EEE8(&awareness->_8, &filter)) {
                auto& link = entry->_0.mLink;
                ksys::act::acquireActor(&link, &accessor);
                if (!accessor.hasProc() || sub_71002F0258(accessor) != 4 ||
                    !link.hasProcInCalcState() ||
                    !sub_710073033C(mActor, &link, *mSearchShieldDist_s) ||
                    accessor.sub_7100D13448(-1) ||
                    !sub_710072E154(mActor, entry->_88, nullptr, -1) ||
                    accessor.sub_71002EF980())
                    continue;
                ksys::act::acquireActor(&link, &accessor);
                sead::Vector3f position;
                accessor.getActorMtx().getTranslation(position);
                if (enemy->sub_710001A2B0(position, enemy->getMtx().getTranslation(),
                                         *mNoShieldSearchDist_s))
                    _c8 = link;
            }
            result = _c8.hasProc();
        }
    }
    return result;
}

EnemyNoiseTarget::EnemyNoiseTarget(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyNoiseTarget::~EnemyNoiseTarget() = default;

bool EnemyNoiseTarget::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnemyNoiseTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* unk = sub_71005E2BCC(mActor)) {
        unk->_8 = -1;
        unk->_c = 0;
    }
    _b8 = 0;
    _a4 = _a8 = *mLostTime_s;
    _ac = sub_71005D9330(mActor);
    _c8.reset();

    if (!*mIsTrgChangeUnderWaterState_a &&
        mActor->getActorFlags2().isOff(ksys::act::Actor::ActorFlag2::_1000000) &&
        mActor->getActorFlags2().isOff(ksys::act::Actor::ActorFlag2::_2000000)) {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(_ac, "TargetPos", -1);
        changeChild("気づき", &pack);
        return;
    }

    auto* nav = mActor->m45();
    if (nav && (nav->_2a4 & 0xffff) == 0x17) {
        sub_710039B064();
        return;
    }

    if (sub_710039B164()) {
        auto* target = sub_71005D9050(mActor);
        if (!target || !sub_710073033C(mActor, target, *mNoShieldSearchDist_s)) {
            ksys::act::BaseProcLink link;
            if (sub_710039B240(&link) && link.hasProcInCalcState() &&
                sub_710073033C(mActor, &link, *mSearchShieldDist_s)) {
                _c8 = link;
                sub_710039B400();
                return;
            }
            if (sub_710039B54C() && _c8.hasProcInCalcState() &&
                sub_710073033C(mActor, &_c8, *mSearchShieldDist_s)) {
                sub_710039B400();
                return;
            }
        }
    }

    _a0 = _a4 == _a8 ? _a4 : sead::GlobalRandom::instance()->getS32Range(_a4, _a8);
    const sead::Vector3f target_pos = sub_71005D9330(mActor);
    const sead::Vector3f diff = target_pos - mActor->getMtx().getTranslation();
    const f32 far = *mFarDist_s + sub_71007320F0(mActor, *mWeaponIdx_s);
    if (diff.squaredLength() < far * far) {
        sub_710039B770();
        return;
    }
    const sead::Vector3f target_pos2 = sub_71005D9330(mActor);
    const sead::Vector3f diff2 = target_pos2 - mActor->getMtx().getTranslation();
    const f32 near = *mNearDist_s + sub_71007320F0(mActor, *mWeaponIdx_s);
    if (diff2.squaredLength() < near * near) {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(_ac, "TargetPos", -1);
        changeChild("騒ぐ", &pack);
        return;
    }
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(_ac, "TargetPos", -1);
    changeChild("接近", &pack);
}

void EnemyNoiseTarget::leave_() {
    if (auto* unit = sub_71005E2BCC(mActor)) {
        unit->_8 = -1;
        unit->_c = 0;
    }
}

void EnemyNoiseTarget::loadParams_() {
    getStaticParam(&mLostTime_s, "LostTime");
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mRerouteTimeMin_s, "RerouteTimeMin");
    getStaticParam(&mRerouteTimeMax_s, "RerouteTimeMax");
    getStaticParam(&mNearDist_s, "NearDist");
    getStaticParam(&mFarDist_s, "FarDist");
    getStaticParam(&mShieldIdx_s, "ShieldIdx");
    getStaticParam(&mSearchShieldDist_s, "SearchShieldDist");
    getStaticParam(&mNoShieldSearchDist_s, "NoShieldSearchDist");
    getStaticParam(&mUnReachableToRepathDist_s, "UnReachableToRepathDist");
    getStaticParam(&mNoShieldEquipWpIdx_s, "NoShieldEquipWpIdx");
    getStaticParam(&mTooFarPathDist_s, "TooFarPathDist");
    getAITreeVariable(&mIsTrgChangeUnderWaterState_a, "IsTrgChangeUnderWaterState");
}

// NON_MATCHING: the position / direction share the param pack slot in the original (scope), and the normalisation
// multiplies in the other operand order.
void EnemyNoiseTarget::sub_710039B770() {
    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    sead::Vector3f dir = pos;
    dir -= sub_71005D9330(mActor);
    dir.normalize();
    if (!sub_710090D904(pos, dir, 2.0f, 1.0f)) {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(_ac, "TargetPos", -1);
        changeChild("後退", &pack);
    } else {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(_ac, "TargetPos", -1);
        changeChild("騒ぐ", &pack);
    }
}

}  // namespace uking::ai
