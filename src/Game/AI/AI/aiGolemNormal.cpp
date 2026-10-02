#include "Game/AI/AI/aiGolemNormal.h"
#include "Game/AI/aiAwarenessFilters.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiRoot.h"
#include "Game/Actor/actEnemy.h"

namespace uking::ai {

GolemNormal::GolemNormal(const InitArg& arg) : EnemyNormal(arg) {}

GolemNormal::~GolemNormal() = default;

bool GolemNormal::init_(sead::Heap* heap) {
    return EnemyNormal::init_(heap);
}

void GolemNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyNormal::enter_(params);
}

void GolemNormal::leave_() {
    if (auto* enemy = sead::DynamicCast<uking::act::Enemy>(mActor))
        enemy->_e90 = 4;
    EnemyNormal::leave_();
}

void GolemNormal::loadParams_() {
    EnemyNormal::loadParams_();
}

void GolemNormal::m34() {
    if (mActor->getRootAi()->getI() == 5)
        EnemyNormal::m34();
    else
        changeChild("初期待機");
}

void GolemNormal::m37() {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
        enemy->_e90 = 1;
    EnemyNormal::m37();
}

void GolemNormal::m38() {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
        enemy->_e90 = 1;
    EnemyNormal::m38();
}

s32 GolemNormal::m52(s32 idx) {
    static const s32 sTable[] = {0, 9, 1, 2, 3, 4, 5, 6, 7, 8};
    return sTable[idx];
}

void GolemNormal::m58(s32 type, Unk2* target) {
    if (type == 9)
        m40();
}

bool GolemNormal::m54() {
    if (EnemyNormal::m54())
        return true;
    return isCurrentChild("初期待機");
}

void GolemNormal::m49(Unk1* out, s32 idx) {
    if (m52(idx) != 9) {
        EnemyNormal::m49(out, idx);
        return;
    }

    out->_0 = isCurrentChild("プレイヤー発見") || isCurrentChild("怒り") ? -1 : 9;
}

// NON_MATCHING: register allocation (&filter kept in a callee-saved register)
bool GolemNormal::m56(Unk2* out, Unk1* info) {
    if (info->_0 == 9) {
        if (auto* awareness = mActor->getAwareness()) {
            Unk_71024514c0 filter(mActor);
            filter._30 = 2;
            auto* sensor = awareness->_260[0];
            auto* entry = sensor ? ksys::act::sub_7100D7EEE8(&sensor->_8, &filter) : nullptr;
            if (entry && !m46(entry->_88, entry->mLink)) {
                out->sub_71003A02A4(entry);
                return true;
            }
        }
    }
    return false;
}

void GolemNormal::m57(s32 type, Unk2* target) {
    if (type == 9) {
        sub_71005D8DE8(mActor, *target->_0, &target->_8, nullptr);
        return;
    }
    EnemyNormal::m57(type, target);
}

}  // namespace uking::ai
