#include "Game/AI/AI/aiWizzrobeCombat.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/System/physRayCastBodyQuery.h"

namespace uking::ai {

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
    return ksys::act::ai::Ai::init_(heap);
}

void WizzrobeCombat::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void WizzrobeCombat::leave_() {
    ksys::act::ai::Ai::leave_();
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
