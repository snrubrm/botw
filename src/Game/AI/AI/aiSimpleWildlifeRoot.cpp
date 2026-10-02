#include "Game/AI/AI/aiSimpleWildlifeRoot.h"
#include "Game/AI/aiUnk_710072BA90.h"
#include "Game/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actAiRoot.h"

namespace uking::ai {

// NON_MATCHING: the original addresses everything from `this` (we keep this+0x38 in a register)
SimpleWildlifeRoot::SimpleWildlifeRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SimpleWildlifeRoot::~SimpleWildlifeRoot() = default;

void SimpleWildlifeRoot::m9() {
    auto* root_ai = mActor->getRootAi();
    _f4 = (root_ai && root_ai->getI() == 4) || *mIsLocatorCreate_m;
    if (mActor->hasPlacementLinkWithTypeFreeze())
        _f5 = true;

    bool* is_amiibo = nullptr;
    if (mActor->getRootAi()->getAITreeVariable(&is_amiibo, "IsAmiibo"))
        _f6 = *is_amiibo;
}

bool SimpleWildlifeRoot::init_(sead::Heap* heap) {
    m9();
    return true;
}

void SimpleWildlifeRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SimpleWildlifeRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SimpleWildlifeRoot::loadParams_() {
    getStaticParam(&mInvalidTgtTimerVal_s, "InvalidTgtTimerVal");
    getStaticParam(&mInvalidEscapeTimerVal_s, "InvalidEscapeTimerVal");
    getStaticParam(&mIsDeleteWhenDead_s, "IsDeleteWhenDead");
    getStaticParam(&mIsDeadWhenPut_s, "IsDeadWhenPut");
    getStaticParam(&mIsEscapeWhenPut_s, "IsEscapeWhenPut");
    getStaticParam(&mIsDeadWhenDrop_s, "IsDeadWhenDrop");
    getMapUnitParam(&mIsPlayerPut_m, "IsPlayerPut");
    getMapUnitParam(&mIsLocatorCreate_m, "IsLocatorCreate");
    getMapUnitParam(&mIsCreateDead_m, "IsCreateDead");
    mActor->getRootAi()->getAITreeVariable2(&mIsDrop_a, "IsDrop");
}

// NON_MATCHING: the original tests the damage type as a 30..34 range minus 32 (ccmp) instead of a
// bit mask
bool SimpleWildlifeRoot::m35() {
    if (isCurrentChild("死亡"))
        return false;

    auto* damage_mgr = sub_710072BA90(mActor);
    if (!damage_mgr)
        return false;

    const s32 damage_type = damage_mgr->getField54();
    const s32* life = mActor->getLife();
    if (life && *life <= 0)
        return true;

    switch (damage_type) {
    case 30:
    case 31:
    case 33:
    case 34:
        return true;
    default:
        return false;
    }
}

void SimpleWildlifeRoot::m40() {
    if (isCurrentChild("死亡"))
        return;

    if (*mIsDeleteWhenDead_s)
        ksys::act::disableAllAttClients(mActor);
    else
        ksys::act::enableAttClient(mActor, "NoticeDo");
    changeChild("死亡");
}

void SimpleWildlifeRoot::m41() {
    m38();
}

void SimpleWildlifeRoot::m42() {
    if (*mIsDeadWhenPut_s || *mIsCreateDead_m) {
        m40();
    } else if (*mIsEscapeWhenPut_s) {
        _c4 = ksys::Timer(-1.0f, -1.0f);
        m39();
    } else {
        m38();
    }
}

void SimpleWildlifeRoot::m43() {
    if (*mIsDeadWhenDrop_s || *mIsCreateDead_m)
        m40();
    else
        m38();
}

void SimpleWildlifeRoot::m44() {
    m38();
    _c4 = ksys::Timer(150.0f, 150.0f);
    _d0 = ksys::Timer(*mInvalidTgtTimerVal_s, *mInvalidTgtTimerVal_s);
    _f5 = false;
}

bool Unk_71023dcc38::m0() {
    return _28;
}

}  // namespace uking::ai
