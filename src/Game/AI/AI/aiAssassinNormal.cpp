#include "Game/AI/AI/aiAssassinNormal.h"
#include "Game/AI/aiAwarenessFilters.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actEnemy.h"
#include "Game/Actor/actUnk_71002dccbc.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

AssassinNormal::AssassinNormal(const InitArg& arg) : LandHumEnemyNormal(arg) {}

AssassinNormal::~AssassinNormal() = default;

bool AssassinNormal::init_(sead::Heap* heap) {
    return LandHumEnemyNormal::init_(heap);
}

void AssassinNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    LandHumEnemyNormal::enter_(params);
    mActor->getMtx().getTranslation(_410);
    _400.reset();
}

void AssassinNormal::calc_() {
    LandHumEnemyNormal::calc_();
}

void AssassinNormal::leave_() {
    LandHumEnemyNormal::leave_();
}

void AssassinNormal::loadParams_() {
    LandHumEnemyNormal::loadParams_();
}

s32 AssassinNormal::m53() {
    return 12;
}

void AssassinNormal::m49(Unk1* out, s32 idx) {
    if (isCurrentChild("音気づき")) {
        if (m52(idx) == 11) {
            auto* unk = sub_71005D9E64(mActor);
            if (unk && !unk->sub_71002DCCBC(0x80)) {
                out->_0 = -1;
                return;
            }
        }
    } else if (isCurrentChild("気配気づき")) {
        if (m52(idx) == 11) {
            out->_0 = -1;
            return;
        }
    } else if (isCurrentChild("不審物発見")) {
        s32 type = m52(idx);
        switch (type) {
        case 4:
        case 6:
        case 7:
        case 10:
        case 11:
            type = -1;
            break;
        default:
            break;
        }
        out->_0 = type;
        return;
    }
    LandHumEnemyNormal::m49(out, idx);
}

s32 AssassinNormal::m52(s32 idx) {
    static const s32 sTable[] = {0, 1, 2, 3, 11, 9, 4, 5, 6, 7, 8, 10};
    return sTable[idx];
}

bool AssassinNormal::m56(Unk2* out, Unk1* info) {
    if (info->_0 == 11)
        return m74(out, info);
    return LandHumEnemyNormal::m56(out, info);
}

void AssassinNormal::m57(s32 type, Unk2* target) {
    if (type != 11) {
        LandHumEnemyNormal::m57(type, target);
        return;
    }

    if (!isCurrentChild("音気づき") && !isCurrentChild("諦め") && !isCurrentChild("不審物発見") &&
        !isCurrentChild("不審物排除後")) {
        sub_710040CE58();
    }
    if (auto* unk = sub_71005D9D68(mActor))
        unk->sub_71002DC628(*target->_0, 0x80);
    _400 = *target->_0;
}

void AssassinNormal::m58(s32 type, Unk2* target) {
    if (type == 11) {
        sub_710040D3A8(target);
        return;
    }
    LandHumEnemyNormal::m58(type, target);
}

void AssassinNormal::m59() {
    auto* child = getCurrentChild();
    if (!isCurrentChild("不審物発見")) {
        LandHumEnemyNormal::m59();
        return;
    }

    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&_400, &accessor);
    sead::Vector3f pos;
    accessor.getActorMtx().getTranslation(pos);
    child->setDynamicParamImpl(_400, "TargetActor", &ksys::act::ai::ParamPack::setActor);
    child->setDynamicParam(pos, "TargetPos");
}

void AssassinNormal::m60(Unk3* out) {
    if (isCurrentChild("不審物発見")) {
        out->_0 = 3;
        return;
    }
    LandHumEnemyNormal::m60(out);
}

void AssassinNormal::m61(Unk3* out) {
    if (!isCurrentChild("不審物発見")) {
        LandHumEnemyNormal::m61(out);
        return;
    }

    if (!_400.hasProcInCalcState())
        out->_0 = 3;

    auto* unk = sub_71005D9D68(mActor);
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&_400, &accessor);
    if (accessor.sub_7100D10E6C(30)) {
        out->_0 = 3;
        if (unk)
            unk->sub_71002DCBDC(0x80);
    }
    if (accessor.checkFlag25()) {
        out->_0 = 3;
        if (unk)
            unk->sub_71002DCBDC(0x80);
    }
    if (sub_71005DEC08(&_400, mActor, 999.0f, 999.0f, sead::Mathf::pi())) {
        out->_0 = 3;
        if (unk)
            unk->sub_71002DCBDC(0x80);
    }
}

void AssassinNormal::m62(Unk3* result) {
    if (result->_0 == 3) {
        _400.reset();
        return;
    }
    EnemyNormal::m62(result);
}

bool AssassinNormal::m63(Unk3* result) {
    if (result->_0 != 3)
        return false;

    _3ac.reset(8);
    ksys::act::ai::InlineParamPack params;
    params.addVec3(_410, "TargetPos", -1);
    changeChild("不審物排除後", &params);
    return true;
}

bool AssassinNormal::m74(Unk2* out, Unk1* info) {
    if (auto* unk = sub_71005D9D68(mActor)) {
        const sead::Vector3f pos = mActor->getMtx().getTranslation();
        auto* link = unk->sub_71002DCEDC(0x80, pos);
        if (link->hasProcInCalcState()) {
            out->_44 |= 4;
            out->sub_710039E308(link);
            return true;
        }
    }

    Unk_71024513f8 filter;
    return sub_710040CF88(&filter, out);
}

bool AssassinNormal::sub_710040CF88(ksys::act::Unk_71024dccf8* filter, Unk2* out) {
    if (!mActor)
        return false;
    auto* awareness = mActor->getAwareness();
    if (!awareness)
        return false;

    while (awareness->_260[3]) {
        auto* entry = ksys::act::sub_7100D7EEE8(&awareness->_260[3]->_8, filter);
        if (!entry)
            break;
        if (sub_710040D048(entry)) {
            out->sub_71003A02A4(entry);
            return true;
        }
    }

    filter->_8 = -1;
    while (awareness->_260[0]) {
        auto* entry = ksys::act::sub_7100D7EEE8(&awareness->_260[0]->_8, filter);
        if (!entry)
            return false;
        if (sub_710040D048(entry)) {
            out->sub_71003A02A4(entry);
            return true;
        }
    }
    return false;
}

void AssassinNormal::sub_710040CE58() {
    mActor->getMtx().getTranslation(_410);
}

void AssassinNormal::sub_710040D3A8(Unk2* target) {
    _3ac.reset(8);
    if (target->_44 & 4) {
        if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
            enemy->_e74 = 15.0f;
    }

    ksys::act::ai::InlineParamPack params;
    params.addActor(*target->_0, "TargetActor", -1);
    params.addVec3(target->_38, "TargetPos", -1);
    changeChild("不審物発見", &params);
}

}  // namespace uking::ai
