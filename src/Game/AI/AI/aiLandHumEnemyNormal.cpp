#include "Game/AI/AI/aiLandHumEnemyNormal.h"
#include <cmath>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actUnk_71002dccbc.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectEnemyLevel.h"

namespace uking::ai {

LandHumEnemyNormal::LandHumEnemyNormal(const InitArg& arg) : EnemyNormal(arg) {}

LandHumEnemyNormal::~LandHumEnemyNormal() = default;

bool LandHumEnemyNormal::init_(sead::Heap* heap) {
    return EnemyNormal::init_(heap);
}

void LandHumEnemyNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyNormal::enter_(params);
}

void LandHumEnemyNormal::calc_() {
    EnemyNormal::calc_();
}

void LandHumEnemyNormal::leave_() {
    EnemyNormal::leave_();
}

void LandHumEnemyNormal::loadParams_() {
    EnemyNormal::loadParams_();
    getStaticParam(&mTerrorIgnoreDist_s, "TerrorIgnoreDist");
    getStaticParam(&mExplosivesSearchDist_s, "ExplosivesSearchDist");
    getStaticParam(&mExplosivesSearchSpeed_s, "ExplosivesSearchSpeed");
    getStaticParam(&mExplosivesSearchAng_s, "ExplosivesSearchAng");
}

s32 LandHumEnemyNormal::m52(s32 idx) {
    static const s32 sTable[] = {0, 1, 2, 3, 9, 10, 4, 5, 6, 7, 8};
    return sTable[idx];
}

// NON_MATCHING: block placement (the original puts the shared "_0 = -1" block right after the
// first isCurrentChild check)
void LandHumEnemyNormal::m49(Unk1* out, s32 idx) {
    const s32 type = m52(idx);
    if (isCurrentChild("危険回避")) {
        out->_0 = -1;
    } else if (isCurrentChild("脅威感知")) {
        if (type == 9)
            out->_0 = -1;
        else
            EnemyNormal::m49(out, idx);
    } else if (isCurrentChild("浮遊物発見")) {
        switch (type) {
        case 2:
            out->_8 |= 0xf;
            break;
        case 4:
        case 5:
        case 6:
        case 7:
        case 10:
            out->_0 = -1;
            break;
        default:
            EnemyNormal::m49(out, idx);
            break;
        }
    } else {
        EnemyNormal::m49(out, idx);
    }
}

void LandHumEnemyNormal::m50(Unk1* out, s32 idx) {
    if (isCurrentChild("危険回避")) {
        out->_0 = -1;
        return;
    }
    EnemyNormal::m50(out, idx);
}

bool Unk_7102401238::m2(ksys::act::Unk_71024dc978* entry) {
    auto* target = sead::DynamicCast<ksys::act::Unk_71024dc858>(entry);
    if (!target)
        return false;
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&target->mLink, &accessor);
    return accessor.isFlyingBalloon();
}

bool LandHumEnemyNormal::m56(Unk2* out, Unk1* info) {
    switch (info->_0) {
    case 9: {
        auto* nav = mActor->m45();
        if (nav && (nav->_2a4 & 0xffff) == 0x17)
            return false;
        const auto* level = mActor->getParam()->getRes().mGParamList->getEnemyLevel();
        if (level && level->mIsKickBomb.ref()) {
            auto& link = sub_71005DE7F4(mActor, *mExplosivesSearchDist_s,
                                        *mExplosivesSearchSpeed_s, *mExplosivesSearchAng_s, true);
            if (link.hasProcInCalcState()) {
                out->sub_710039E308(&link);
                return true;
            }
        }
        break;
    }
    case 10: {
        Unk_7102401238 filter;
        if (auto* entry = sub_71003A04E0(false, &filter, info->_4, info->_8 & 0x40)) {
            out->sub_71003A02A4(entry);
            return true;
        }
        break;
    }
    default:
        break;
    }
    return false;
}

void LandHumEnemyNormal::m57(s32 type, Unk2* target) {
    if (type == 10) {
        _3f0 = *target->_0;
        return;
    }
    EnemyNormal::m57(type, target);
}

void LandHumEnemyNormal::m58(s32 type, Unk2* target) {
    switch (type) {
    case 9:
        changeToAvoidDanger(target);
        break;
    case 10:
        changeToFoundFloatingObject(target);
        break;
    default:
        break;
    }
}

// NON_MATCHING: register allocation (the original keeps the SafeString vtable in x20 and recomputes
// &accessor for the destructor)
void LandHumEnemyNormal::m59() {
    if (isCurrentChild("浮遊物発見")) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&_3f0, &accessor);
        if (accessor.hasProc()) {
            const sead::Vector3f pos = accessor.getActorMtx().getTranslation();
            getCurrentChild()->setDynamicParam(pos, "TargetPos");
        }
    } else {
        EnemyNormal::m59();
    }
}

void LandHumEnemyNormal::m60(Unk3* out) {
    if (isCurrentChild("浮遊物発見")) {
        out->_0 = 1;
        return;
    }
    if (isCurrentChild("危険回避")) {
        out->_0 = 1;
        return;
    }
    EnemyNormal::m60(out);
}

void LandHumEnemyNormal::m61(Unk3* out) {
    if (isCurrentChild("浮遊物発見") && !_3f0.hasProcInCalcState()) {
        out->_0 = 1;
        return;
    }
    EnemyNormal::m61(out);
}

bool LandHumEnemyNormal::m68(Unk2* out, Unk1* info) {
    bool far = false;
    if (mActor) {
        const sead::Vector3f pos = mActor->getMtx().getTranslation();
        sead::Vector3f home;
        mActor->getHomePos(&home);
        const f32 dx = pos.x - home.x;
        const f32 dz = pos.z - home.z;
        far = std::sqrt(dx * dx + dz * dz) >= *mTerrorIgnoreDist_s;
    }
    if (!far && EnemyNormal::m68(out, info))
        return true;

    const auto* level = mActor->getParam()->getRes().mGParamList->getEnemyLevel();
    if (level && level->mIsEscapeBomb.ref()) {
        auto& link = sub_71005DE7F4(mActor, *mExplosivesSearchDist_s, *mExplosivesSearchSpeed_s,
                                    *mExplosivesSearchAng_s, true);
        if (link.hasProcInCalcState()) {
            out->sub_710039E308(&link);
            return true;
        }
    }
    return false;
}

void LandHumEnemyNormal::changeToAvoidDanger(Unk2* target) {
    auto* link = target->_0;
    if (!ksys::act::isPlayerProfile(link)) {
        if (auto* unk = sub_71005D9D68(mActor))
            unk->sub_71002DC628(*link, 4);
    }

    ksys::act::ai::InlineParamPack params;
    params.addActor(*link, "TargetActor", -1);
    changeChild("危険回避", &params);
    sub_710039FAA4(target->_38);
}

void LandHumEnemyNormal::changeToFoundFloatingObject(Unk2* target) {
    ksys::act::ai::InlineParamPack params;
    params.addActor(*target->_0, "TargetActor", -1);
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(target->_0, &accessor);
    sead::Vector3f pos;
    accessor.getActorMtx().getTranslation(pos);
    params.addVec3(pos, "TargetPos", -1);
    changeChild("浮遊物発見", &params);
    sub_710039FAA4(target->_38);
}

}  // namespace uking::ai
