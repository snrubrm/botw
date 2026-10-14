#include "Game/Actor/Action/actionChemicalAttack.h"
#include "KingSystem/Chemical/chmSystemConfig.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectAttack.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Terrain/teraSystem.h"

namespace uking::action {

ChemicalAttack::ChemicalAttack(const InitArg& arg) : EmitAttackBase(arg) {}

ChemicalAttack::~ChemicalAttack() = default;

bool ChemicalAttack::init_(sead::Heap* heap) {
    return EmitAttackBase::init_(heap);
}

void ChemicalAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    EmitAttackBase::enter_(params);
    if (auto* chemical = mActor->getChemicalStuff())
        chemical->sub_7100D91098(true);
}

void ChemicalAttack::leave_() {
    EmitAttackBase::leave_();
    if (auto* chemical = mActor->getChemicalStuff())
        chemical->sub_7100D91098(false);
}

void ChemicalAttack::loadParams_() {
    EmitAttackBase::loadParams_();
    getStaticParam(&mIsUseMyRange_s, "IsUseMyRange");
    getStaticParam(&mAttackType_s, "AttackType");
}

void ChemicalAttack::calc_() {
    EmitAttackBase::calc_();
    auto* terrain = ksys::tera::Terrain::instance();
    if (terrain && terrain->isGrassEnabled()) {
        auto* grass = terrain->sub_710114DE4C();
        const sead::Vector3f position = mActor->getMtx().getTranslation();
        grass->sub_7101150A7C(&position, _7c, 0.0f);
    }
}

int ChemicalAttack::m35() {
    switch (*mAttackType_s) {
    case 0:
        return 0x800;
    case 1:
        return 0x2000;
    default:
        return 0x800;
    }
}

float ChemicalAttack::m34() {
    if (*mIsUseMyRange_s)
        return mActor->getParam()->getRes().mGParamList->getAttack()->mRange.ref();
    return *mRange_m;
}

int ChemicalAttack::m36() {
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
    return flags | EmitAttackBase::m36();
}

}  // namespace uking::action
