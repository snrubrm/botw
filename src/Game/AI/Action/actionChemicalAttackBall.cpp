#include "Game/AI/Action/actionChemicalAttackBall.h"
#include "KingSystem/Chemical/chmSystemConfig.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectAttack.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

ChemicalAttackBall::ChemicalAttackBall(const InitArg& arg) : ChemicalAttack(arg) {}

ChemicalAttackBall::~ChemicalAttackBall() = default;

bool ChemicalAttackBall::init_(sead::Heap* heap) {
    return ChemicalAttack::init_(heap);
}

void ChemicalAttackBall::enter_(ksys::act::ai::InlineParamPack* params) {
    ChemicalAttack::enter_(params);
    if (auto* chemical = mActor->getChemicalStuff())
        chemical->sub_7100D91098(true);
}

void ChemicalAttackBall::leave_() {
    ChemicalAttack::leave_();
    if (auto* chemical = mActor->getChemicalStuff())
        chemical->sub_7100D91098(false);
}

void ChemicalAttackBall::loadParams_() {
    ChemicalAttack::loadParams_();
    getStaticParam(&mIsUseMyRange_s, "IsUseMyRange");
    getStaticParam(&mAttackType_s, "AttackType");
}

void ChemicalAttackBall::calc_() {
    ChemicalAttack::calc_();
}

int ChemicalAttackBall::m35() {
    switch (*mAttackType_s) {
    case 0:
        return 0x800;
    case 1:
        return 0x2000;
    default:
        return 0x800;
    }
}

float ChemicalAttackBall::m34() {
    if (*mIsUseMyRange_s)
        return mActor->getParam()->getRes().mGParamList->getAttack()->mRange.ref();
    return *mRange_m;
}

int ChemicalAttackBall::m36() {
    int flags = 0;
    if (auto* chemical = mActor->getChemicalStuff()) {
        if (chemical->_c0 == 2) {
            flags = 0x200;
        } else {
            const u32 attribute = chemical->mMaterial->attribute.ref();
            if (attribute & 0x8000)
                flags = 0x400;
            else if (((attribute & 0x108) == 0x108 && !(chemical->_be & 4)) || chemical->_1b8 > 0.0f)
                flags = 0x800;
        }
    }
    return flags | ChemicalAttack::m36();
}

}  // namespace uking::action
