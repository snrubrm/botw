#include "Game/Actor/AI/aiWizzrobeCombat.h"
#include "Game/Actor/aiUnk_71007320F0.h"
#include <random/seadGlobalRandom.h>
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectWizzrobe.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "Game/Actor/Damage/dmgInfoManager.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actActorHeapUtil.h"
#include "KingSystem/ActorSystem/aiRootAi.h"
#include "KingSystem/Physics/System/physRayCastBodyQuery.h"

namespace uking::ai {

// NON_MATCHING: vector component loads and subtraction register scheduling differ.
bool WizzrobeCombat::sub_71005FACD8() {
    const f32 distance = (sub_71005D9330(mActor) - mActor->getMtx().getTranslation()).length();
    if (!(distance < sub_71007320F0(mActor, 0) * 1.5f))
        return false;
    auto* target = sub_71005D9050(mActor);
    if (!target || ksys::act::isPlayerProfile(target))
        return true;
    if (_59d)
        return true;
    return sead::GlobalRandom::instance()->getS32Range(1, 100) < 16;
}

WizzrobeCombat::WizzrobeCombat(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WizzrobeCombat::~WizzrobeCombat() {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        if (mSummonBufferSize_s) {
            sead::FixedSafeString<64> name;
            for (s32 i = 0; i < *mSummonBufferSize_s; ++i) {
                name.format("%s_%d", mSummonBufferKey_s.cstr(), i);
                enemy->sub_7100D3CFEC(name);
            }
        }
    }
}

bool WizzrobeCombat::init_(sead::Heap* heap) {
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (!enemy)
        return false;
    sead::FixedSafeString<64> name;
    for (s32 i = 0; i < *mSummonBufferSize_s; ++i) {
        name.format("%s_%d", mSummonBufferKey_s.cstr(), i);
        if (!enemy->sub_7100D3CED8(name, heap))
            return false;
    }
    mMagicWeatherType = 0;
    mSelectedSummonActor = nullptr;
    sub_71005FA684();
    return true;
}

void WizzrobeCombat::sub_71005FA684() {
    for (auto& actor : mSummonActors) {
        actor.name.clear();
        actor.isFlyActor = false;
    }
    const auto* params = getGParamList()->getWizzrobe();
    if (params) {
        mMagicWeatherType = params->mMagicWeatherType.ref();
        const sead::SafeString names = params->mSummonActorName.ref();
        s32 index = 0;
        for (auto it = names.tokenBegin(","); names.tokenEnd(",") != it; ++it) {
            it.get(&mSummonActors[index].name);
            if (!mSummonActors[index].name.isEmpty())
                ++index;
            if (index == mSummonActors.size())
                break;
        }
    }
    auto* info = ksys::act::InfoData::instance();
    if (info) {
        for (auto& actor : mSummonActors) {
            if (!actor.name.isEmpty()) {
                info->getInvalidLifeConditions(actor.name.cstr(), actor.conditions);
                actor.isFlyActor = info->hasTag(actor.name.cstr(), 0xd3231bed);
            }
        }
    }
}

// NON_MATCHING: summon-selection branch layout and actor creation argument scheduling.
void WizzrobeCombat::enter_(ksys::act::ai::InlineParamPack* params) {
    _59c = false;
    if (*mSummonCount_s > *mSummonCount_a &&
        (!_98.isAllocatedOrFailed() || (!_98.isProcReady() && _98.hasProcCreationFailed()))) {
        if (_98.isAllocatedOrFailed())
            _98.deleteProcIfFailed();
        _98.deleteProc();
        mSelectedSummonActor = nullptr;
        _598 = 0;
        u32 count = 0;
        for (const auto& actor : mSummonActors) {
            if (actor.name.isEmpty())
                break;
            ++count;
        }
        if (count) {
            s32 choice = (sead::GlobalRandom::instance()->getU32() & 0x7fffffff) % count;
            for (s32 idx = 0; idx < mSummonActors.size(); ++idx) {
                if (mSummonActors[idx].name.isEmpty())
                    break;
                if (choice == 0) {
                    mSelectedSummonActor = &mSummonActors[idx];
                    ksys::act::ActorCreator::instance()->requestCreateActor(
                        mSelectedSummonActor->name.cstr(),
                        ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(), &_98, nullptr,
                        nullptr, 1);
                    break;
                }
                --choice;
            }
        }
    }
    if (!testRootAiFlag2(ksys::act::ai::RootAiFlag2::_0)) {
        _59d = true;
        if (sead::GlobalRandom::instance()->getS32Range(1, 100) < 21 && sub_71005FACD8()) {
            sub_71005FADC4();
            return;
        }
    }
    sub_71005FAE9C();
}

// NON_MATCHING: vector rotation and target component snapshots.
void WizzrobeCombat::sub_71005FAE9C() {
    ksys::act::ai::InlineParamPack pack;
    _590 = sub_71005FC1D0();
    const auto offset = *mTargetOffset_s;
    const auto matrix = sub_71005D96A8(mActor);
    sead::Vector3f target;
    target.setRotated(matrix, sead::Vector3f{offset.x, 0.0f, offset.z});
    const auto& attention = sub_71005D9330(mActor);
    target.x += attention.x;
    target.y = offset.y + _590 * *mHeightOffset_s + attention.y;
    target.z += attention.z;
    pack.addVec3(target, "TargetPos", -1);
    pack.addVec3(sub_71005D9330(mActor), "AttPos", -1);
    changeChild("移動", &pack);
}

// NON_MATCHING: random-selection branch layout and register allocation.
s32 WizzrobeCombat::sub_71005FC1D0() {
    auto* actor = mActor;
    const f32 height = actor->getMtx().m[1][3];
    const auto& target = sub_71005D9330(actor);
    const f32 offset = *mHeightOffset_s;
    if (offset == 0.0f)
        return 0;
    s32 max_level = *mMaxHeightLevel_s;
    s32 level = static_cast<s32>((offset * 0.5f + (height - (target.y + mTargetOffset_s->y))) / offset);
    const s32* life = actor->getLife();
    if ((life ? *life : 1) / actor->getMaxLife() < 1)
        max_level = sead::Mathi::max(max_level - 1, 0);
    if (level < -1) {
        level = 0;
    } else if (level <= 0) {
        level = (~sead::GlobalRandom::instance()->getU32()) & 1;
    } else if (level > max_level + 1) {
        return sead::Mathi::max(max_level, 0);
    } else if (level < max_level) {
        switch (sead::GlobalRandom::instance()->getU32(3)) {
        case 0:
            --level;
            break;
        case 1:
            ++level;
            break;
        }
    } else {
        if (sead::GlobalRandom::instance()->getU32() & 1)
            level = sead::Mathi::max(max_level - 1, 0);
        else
            level = max_level;
    }
    return sead::Mathi::min(level, max_level);
}

void WizzrobeCombat::leave_() {
    if (_59c) {
        auto& status = act::DamageInfoMgr::instance()->get790();
        if (status.sub_7100672B1C(mActor))
            status.sub_7100672888(mActor);
    }
}

void WizzrobeCombat::loadParams_() {
    getStaticParam(&mWeatherMagicRate_s, "WeatherMagicRate");
    getStaticParam(&mSummonRate_s, "SummonRate");
    getStaticParam(&mSummonBufferSize_s, "SummonBufferSize");
    getStaticParam(&mMaxHeightLevel_s, "MaxHeightLevel");
    getStaticParam(&mSummonCount_s, "SummonCount");
    getStaticParam(&mAttackLength_s, "AttackLength");
    getStaticParam(&mHeightOffset_s, "HeightOffset");
    getStaticParam(&mSummonBufferKey_s, "SummonBufferKey");
    getStaticParam(&mTargetOffset_s, "TargetOffset");
    getAITreeVariable(&mSummonCount_a, "SummonCount");
    getAITreeVariable(&mIsWizzrobeInBattleAreaFlag_a, "IsWizzrobeInBattleAreaFlag");
}

bool WizzrobeCombat::isChangeable() const {
    if (ksys::act::ai::Ai::isChangeable())
        return true;
    auto* child = getCurrentChild();
    if (child->isFinished())
        return true;
    return child->isFailed();
}

// 0x71005fadc4
void WizzrobeCombat::sub_71005FADC4() {
    _59d = false;
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    changeChild("武器攻撃", &pack);
}

// 0x71005fc01c
void WizzrobeCombat::sub_71005FC01C() {
    ksys::act::ai::InlineParamPack pack;
    pack.addPointer(&_98, "IgniteHandle", ksys::AIDefParamType::BaseProcHandle, -1);
    pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    changeChild("召喚魔法", &pack);
}

// 0x71005fc498
bool WizzrobeCombat::sub_71005FC498(const sead::Vector3f& start, const sead::Vector3f& end) {
    ksys::phys::RayCastBodyQuery query(nullptr, ksys::phys::GroundHit::HitAll);
    query.enableLayer(ksys::phys::ContactLayer::EntityGroundObject);
    query.enableLayer(ksys::phys::ContactLayer::EntityObject);
    query.enableLayer(ksys::phys::ContactLayer::EntityWater);
    query.enableLayer(ksys::phys::ContactLayer::EntityGround);
    query.enableLayer(ksys::phys::ContactLayer::EntityGroundSmooth);
    query.enableLayer(ksys::phys::ContactLayer::EntityGroundRough);
    query.setStartAndEnd(start, end);
    query.setNormalCheckingMode(ksys::phys::RayCast::NormalCheckingMode::_0);
    bool result = false;
    if (query.worldRayCast(ksys::phys::ContactLayerType::Entity)) {
        const auto material = query.getMaterialMask().getMaterial();
        result = material != ksys::phys::Material::Bog && material != ksys::phys::Material::Water;
    }
    return result;
}

}  // namespace uking::ai
