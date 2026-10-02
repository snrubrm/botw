#include "Game/AI/AI/aiForestGiantNormal.h"
#include "Game/Actor/actEnemy.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actAiRoot.h"

namespace uking::ai {

ForestGiantNormal::ForestGiantNormal(const InitArg& arg) : EnemyNormal(arg) {}

ForestGiantNormal::~ForestGiantNormal() = default;

bool ForestGiantNormal::init_(sead::Heap* heap) {
    return EnemyNormal::init_(heap);
}

// NON_MATCHING: the original stores _3e4 alone and pairs _3dc/_3e0 into one 8-byte store
void ForestGiantNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    _3dc = 0;
    _3e0 = 120;
    _3e4 = 120;
    EnemyNormal::enter_(params);
    _3d8 = false;
}

void ForestGiantNormal::leave_() {
    EnemyNormal::leave_();
}

void ForestGiantNormal::loadParams_() {
    EnemyNormal::loadParams_();
    getStaticParam(&mSleepingHearAwnRatio_s, "SleepingHearAwnRatio");
}

bool ForestGiantNormal::handleMessage_(const ksys::Message& message) {
    if (message.getType() == 0x3000015) {
        _3d8 = false;
        return false;
    }
    if (message.getType() == 0x3000016) {
        _3d8 = true;
        return false;
    }
    return EnemyNormal::handleMessage_(message);
}

void ForestGiantNormal::m34() {
    if (mActor->getRootAi()->getI() == 5) {
        EnemyNormal::m34();
        return;
    }
    ksys::act::ai::InlineParamPack params;
    sead::Vector3f pos;
    m48(&pos);
    params.addVec3(pos, "CentralPos", -1);
    changeChild("初期待機", &params);
}

bool ForestGiantNormal::m54() {
    if (isCurrentChild("初期待機"))
        return true;
    return EnemyNormal::m54();
}

void ForestGiantNormal::m60(Unk3* out) {
    EnemyNormal::m60(out);
    if (out->_0 == 0 && isCurrentChild("プレイヤー発見"))
        out->_0 = 3;
}

bool ForestGiantNormal::m63(Unk3* result) {
    if (result->_0 != 3)
        return false;

    const auto& pos = sub_71005D98D8(mActor);
    ksys::act::ai::InlineParamPack params;
    params.addVec3(pos, "TargetPos", -1);
    changeChild("プレイヤー見失い", &params);
    return true;
}

bool ForestGiantNormal::m68(Unk2* out, Unk1* info) {
    if (!EnemyNormal::m68(out, info))
        return false;
    if (_3dc <= 0.0f)
        return true;
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (enemy && out->_0 && enemy->_c38(0) == *out->_0)
        return false;
    return true;
}

}  // namespace uking::ai
