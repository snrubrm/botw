#include "Game/AI/aiUnk_710038ffb8.h"
#include "Game/AI/aiUnk_7102357d20.h"
#include "Game/Actor/actEnemy.h"
#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

Unk_710038ffb8::~Unk_710038ffb8() {
    // Keep the original vtable store, as in upstream GameDataFlagSelector::~GameDataFlagSelector()
    // { ; } (commit 96101229).
    ;
}

Unk_71023e7d28::~Unk_71023e7d28() = default;

Unk_71023e7b98::~Unk_71023e7b98() = default;
Unk_71023e7be8::~Unk_71023e7be8() = default;
Unk_71023e7c10::~Unk_71023e7c10() = default;

s32 Unk_710038ffb8::sub_7100390A90() {
    _3c8 = 0x10;
    *_8 = 0;
    _3a0.reset();
    return 0;
}

void Unk_710038ffb8::sub_71003910E4() {
    _3c8 |= 2;
    *_8 = false;
    ksys::act::ai::InlineParamPack pack;
    pack.addActor(_390, "TargetActor", -1);
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&_390, &accessor);
    sead::Vector3f pos;
    accessor.getActorMtx().getTranslation(pos);
    pack.addVec3(pos, "TargetPos", -1);
    _10->changeChild("聞く", &pack);
}

void Unk_710038ffb8::sub_71003916F4() {
    _3c8 |= 2;
    *_8 = false;
    if (auto* enemy = sead::DynamicCast<uking::act::Enemy>(_10->getActor()))
        enemy->_e84.resetBit(12);
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(_330._34._0, "TargetPos", -1);
    _10->changeChild("注意", &pack);
}

void Unk_710038ffb8::sub_710039184C() {
    _3c8 |= 2;
    *_8 = false;
    if (auto* enemy = sead::DynamicCast<uking::act::Enemy>(_10->getActor()))
        enemy->_e84.resetBit(12);
    ksys::act::ai::InlineParamPack pack;
    pack.addActor(_390, "TargetActor", -1);
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&_390, &accessor);
    sead::Vector3f pos;
    accessor.getActorMtx().getTranslation(pos);
    pack.addVec3(pos, "TargetPos", -1);
    _10->changeChild("呼びかけ", &pack);
}

void Unk_710038ffb8::sub_7100391A10() {
    _3c8 |= 2;
    *_8 = false;
    ksys::act::ai::InlineParamPack pack;
    pack.addActor(_390, "TargetActor", -1);
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&_390, &accessor);
    sead::Vector3f pos;
    accessor.getActorMtx().getTranslation(pos);
    pack.addVec3(pos, "TargetPos", -1);
    _10->changeChild("向き直り", &pack);
}

// NON_MATCHING: load order of the global random pointer and the upper bound.
void Unk_710038ffb8::sub_7100391B5C() {
    _3c8 |= 2;
    *_8 = false;
    s32 time = *_40;
    if (time != *_20)
        time = sead::GlobalRandom::instance()->getS32Range(time, *_48);
    _3b0 = time;
    if (auto* enemy = sead::DynamicCast<uking::act::Enemy>(_10->getActor()))
        enemy->_e84.resetBit(12);
    ksys::act::ai::InlineParamPack pack;
    pack.addActor(_390, "TargetActor", -1);
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&_390, &accessor);
    sead::Vector3f pos;
    accessor.getActorMtx().getTranslation(pos);
    pack.addVec3(pos, "TargetPos", -1);
    _10->changeChild("話す", &pack);
}

void Unk_710038ffb8::sub_7100392230() {
    _10->getStaticParam(&_18, "ReactDelayMin");
    _10->getStaticParam(&_20, "ReactDelayMax");
    _10->getStaticParam(&_28, "DanceReactRand");
    _10->getStaticParam(&_30, "TalkEndDelayMin");
    _10->getStaticParam(&_38, "TalkEndDelayMax");
    _10->getStaticParam(&_40, "TalkChangeViewTargetTimerMin");
    _10->getStaticParam(&_48, "TalkChangeViewTargetTimerMax");
    _10->getStaticParam(&_50, "FortressTag");
    _10->getAITreeVariable(&_8, "IsNextActionReserved");
}
