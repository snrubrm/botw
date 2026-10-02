#include "Game/AI/AI/aiLynelNormal.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "Game/AI/aiUnk_71005D6D10.h"

// The functions of the listener Unk_71024056a8 are in this translation unit in the original
// (LynelNormal's D1 and handleMessage_ inline them).
Unk_71024056a8::~Unk_71024056a8() = default;

bool Unk_71024056a8::m2(const ksys::Message& message) {
    if (message.getType() != 0x80000ac)
        return false;

    auto* payload = static_cast<Unk_71024056a8_Payload*>(message.getUserData());
    if (!payload)
        return false;

    {
        sead::ScopedLock<sead::JobQueueLock> lock(&payload->mLock);
        _34._0 = payload->_0;
    }
    _30 = true;
    _18 = message.getSource();
    return true;
}

namespace uking::ai {

LynelNormal::LynelNormal(const InitArg& arg) : LandHumEnemyNormal(arg) {}

LynelNormal::~LynelNormal() = default;

bool LynelNormal::init_(sead::Heap* heap) {
    if (!LandHumEnemyNormal::init_(heap))
        return false;
    _45c = false;
    _458 = 0;
    return true;
}

void LynelNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    LandHumEnemyNormal::enter_(params);
}

void LynelNormal::leave_() {
    LandHumEnemyNormal::leave_();
}

void LynelNormal::loadParams_() {
    LandHumEnemyNormal::loadParams_();
    getAITreeVariable(&mLynelAreaAlarmPoint_a, "LynelAreaAlarmPoint");
    getAITreeVariable(&mLynelAIFlags_a, "LynelAIFlags");
    getAITreeVariable(&mLynelNoticeAttackRepeatNum_a, "LynelNoticeAttackRepeatNum");
}

// NON_MATCHING: csel operand order (target selects the `&` value on _45c == 0)
void LynelNormal::calc_() {
    if (_45c)
        *mLynelAIFlags_a |= 0x10;
    else
        *mLynelAIFlags_a &= ~0x10;
    *mLynelAreaAlarmPoint_a = _458;
    LandHumEnemyNormal::calc_();
    _45c = false;
    _458 = 0;
}

bool LynelNormal::handleMessage_(const ksys::Message& message) {
    if (_418.m2(message)) {
        _458 = sead::Mathi::max(_458, _418._34._0);
        _45c = true;
        _418.x();
        return true;
    }
    return LandHumEnemyNormal::handleMessage_(message);
}

void LynelNormal::m37() {
    *mLynelNoticeAttackRepeatNum_a = 0;
    LandHumEnemyNormal::m37();
}

void LynelNormal::m49(Unk1* out, s32 idx) {
    LandHumEnemyNormal::m49(out, idx);
    const s32 type = m52(idx);
    if (out->_0 != -1 || !isCurrentChild("攻撃反応"))
        return;
    if (type == 9) {
        out->_0 = 9;
    } else if (type == 2) {
        out->_8 |= 0x480;
        out->_0 = 2;
    }
}

void LynelNormal::m57(s32 type, Unk2* target) {
    LandHumEnemyNormal::m57(type, target);
    switch (type) {
    case 0:
    case 1:
        *mLynelNoticeAttackRepeatNum_a = 0;
        break;
    default:
        break;
    }
}

void LynelNormal::m60(Unk3* out) {
    LandHumEnemyNormal::m60(out);
    if (out->_0 == 0 && isCurrentChild("プレイヤー発見"))
        out->_0 = 3;
}

bool LynelNormal::m63(Unk3* result) {
    if (result->_0 != 3)
        return false;

    const auto& pos = sub_71005D98D8(mActor);
    ksys::act::ai::InlineParamPack params;
    params.addVec3(pos, "TargetPos", -1);
    changeChild("プレイヤー見失い", &params);
    return true;
}

}  // namespace uking::ai
