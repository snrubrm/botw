#include "Game/AI/AI/aiPriestBossLineFormationFall.h"
#include "Game/AI/aiUnk_7102450fa8.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

PriestBossLineFormationFall::PriestBossLineFormationFall(const InitArg& arg)
    : PriestBossFormation(arg) {}

PriestBossLineFormationFall::~PriestBossLineFormationFall() = default;

bool PriestBossLineFormationFall::init_(sead::Heap* heap) {
    return PriestBossFormation::init_(heap);
}

void PriestBossLineFormationFall::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBossFormation::enter_(params);
    m43();
    _94 = false;
}

void PriestBossLineFormationFall::leave_() {
    PriestBossFormation::leave_();
}

void PriestBossLineFormationFall::loadParams_() {
    PriestBossFormation::loadParams_();
    getStaticParam(&mWarpHightOffset_s, "WarpHightOffset");
}

void PriestBossLineFormationFall::m34(Unk_7102450fa8* unit) {
    if (!unit)
        return;
    unit->sub_7100719534(mActor);
    PriestBossFormation::m34(unit);
}

void PriestBossLineFormationFall::m42() {
    sead::FixedSafeString<16> name;
    name.format("%d", sub_7100518B50());
    mActor->getASList()->goLimpFromHeadShotMaybe(0x2f, name, 0);
    changeChild("攻撃前");
}

void PriestBossLineFormationFall::m43() {
    if (!isCurrentChild("攻撃"))
        changeChild("待機");
}

}  // namespace uking::ai
