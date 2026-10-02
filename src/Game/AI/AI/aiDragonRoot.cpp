#include "Game/AI/AI/aiDragonRoot.h"
#include "Game/Actor/actDragon.h"
#include "Game/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::ai {

void Unk_71023e3a40::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6) {
    if (*a1 < 1)
        return;

    auto* damage_manager = sead::DynamicCast<dmg::DamageManager>(mDamageManager);
    if (!damage_manager)
        return;
    auto* dragon = sead::DynamicCast<act::Dragon>(damage_manager->mActor);
    if (!dragon)
        return;
    auto* body = damage_manager->sub_71006D69F8();
    if (!body)
        return;

    const sead::SafeString name = body->getHkBodyName();
    if (!dragon->sub_710000FDFC()) {
        name.findIndex("牙");
        name.findIndex("爪");
        name.findIndex("角");
        return;
    }

    if (name.findIndex("怨念") == -1) {
        *a1 = 0;
        *a5 = 12;
        return;
    }

    bool hit = false;
    if (name.findIndex("頭部") != -1)
        hit = dragon->_1f70.isOnBit(15);
    if (name.findIndex("胴前方") != -1)
        hit |= dragon->_1f70.isOnBit(16);
    if (name.findIndex("胴後方") != -1)
        hit |= dragon->_1f70.isOnBit(17);
    if (name.findIndex("尻尾") != -1)
        hit |= dragon->_1f70.isOnBit(18);
    if (hit) {
        *a1 = 1;
        *a5 = 12;
    }
}

DragonRoot::DragonRoot(const InitArg& arg) : DragonRootBase(arg) {}

DragonRoot::~DragonRoot() = default;

bool DragonRoot::init_(sead::Heap* heap) {
    return DragonRootBase::init_(heap);
}

void DragonRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    DragonRootBase::enter_(params);
}

void DragonRoot::leave_() {
    DragonRootBase::leave_();
}

void DragonRoot::loadParams_() {
    DragonRootBase::loadParams_();
    getStaticParam(&mChemicalBulletRate_s, "ChemicalBulletRate");
    getStaticParam(&mChemicalBulletNum_s, "ChemicalBulletNum");
    getStaticParam(&mUpdraftInterval_s, "UpdraftInterval");
    getStaticParam(&mReturnTime_s, "ReturnTime");
    getStaticParam(&mBodyHitDamage_s, "BodyHitDamage");
    getStaticParam(&mBodyHitPower_s, "BodyHitPower");
    getStaticParam(&mBodyHitImpact_s, "BodyHitImpact");
    getStaticParam(&mBodyHitShieldDamage_s, "BodyHitShieldDamage");
    getStaticParam(&mOnRailDistance_s, "OnRailDistance");
    getStaticParam(&mFarDistance_s, "FarDistance");
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mChemicalBulletArea_s, "ChemicalBulletArea");
    getStaticParam(&mChemicalWindArea_s, "ChemicalWindArea");
    getStaticParam(&mChemicalWindPower_s, "ChemicalWindPower");
    getStaticParam(&mChemicalWindLimitHeight_s, "ChemicalWindLimitHeight");
    getStaticParam(&mUpdraftPower_s, "UpdraftPower");
    getStaticParam(&mUpdraftTime_s, "UpdraftTime");
    getStaticParam(&mUpdraftBoost_s, "UpdraftBoost");
    getStaticParam(&mInitBackRailDistance_s, "InitBackRailDistance");
    getStaticParam(&mIsEmitChemical_s, "IsEmitChemical");
    getStaticParam(&mCommonTableName_s, "CommonTableName");
    getStaticParam(&mTsunoTableName_s, "TsunoTableName");
    getStaticParam(&mTsumeTableName_s, "TsumeTableName");
    getStaticParam(&mKibaTableName_s, "KibaTableName");
    getStaticParam(&mChemicalBulletActor_s, "ChemicalBulletActor");
    getStaticParam(&mDefaultMaterialAnmName_s, "DefaultMaterialAnmName");
    getStaticParam(&mHornAnmName_s, "HornAnmName");
    getAITreeVariable(&mCreateRailName_a, "CreateRailName");
}

bool DragonRoot::handleMessage_(const ksys::Message& message) {
    if (message.getType().value == 0x3000010) {
        mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_20);
        return true;
    }
    return false;
}

f32 DragonRoot::m34() {
    return _248;
}

void DragonRoot::m41() {
    sub_7100356CFC();
    _1d8 = 30;
    _24c.set(0x14);
}

void DragonRoot::m44() {}

bool DragonRoot::m47() {
    auto* dragon = sead::DynamicCast<act::Dragon>(mActor);
    if (!dragon)
        return false;
    if (_24c.isOnBit(7) && !dragon->_1f70.isOnBit(31))
        return true;
    return false;
}

}  // namespace uking::ai
