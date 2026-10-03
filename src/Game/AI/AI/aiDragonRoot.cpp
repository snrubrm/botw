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
    if (!DragonRootBase::init_(heap))
        return false;

    mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_20);
    _1dc = 0;
    _1e0 = 0;
    _1e4 = {0, 0, 0};

    Unk_71023b0898_Payload::Data data;
    data._8.acquire(mActor, false);
    data._0 = 5;
    _1f0._18.x(data);

    auto* dragon = sead::DynamicCast<act::Dragon>(mActor);
    if (!dragon)
        return false;

    if (!dragon->_1f70.isOnBit(28)) {
        const s32 num = *mChemicalBulletNum_s;
        if (num > 0)
            _238._0.tryAllocBuffer(num, heap);
    }
    dragon->x(dragon->getMtx());
    return true;
}

void DragonRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    DragonRootBase::enter_(params);
}

bool DragonRoot::reenter_(ksys::act::ai::ActionBase* other, bool x) {
    if (!DragonRootBase::reenter_(other, true))
        return false;
    auto* root = sead::DynamicCast<DragonRoot>(other);
    if (!root)
        return false;
    auto* other_dragon = sead::DynamicCast<act::Dragon>(root->mActor);
    if (!other_dragon)
        return false;
    auto* dragon = sead::DynamicCast<act::Dragon>(mActor);
    if (!dragon)
        return false;

    dragon->sub_710000C160(other_dragon);
    _248 = root->_248;
    _1e0 = root->_1e0;
    _24c = root->_24c;
    _24c.reset(0x43);
    _24c.set(0x40);
    mActor->getActorFlags2().change(ksys::act::Actor::ActorFlag2::_20, !root->_24c.isOn(8));
    mActor->clearFadeInCreate();
    return true;
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

bool DragonRoot::handleMessage_(const ksys::Message* message) {
    if (message->getType() == 0x3000010) {
        mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_20);
        return true;
    }
    return false;
}

f32 DragonRoot::m34() {
    return _248;
}

void DragonRoot::m38() {
    sub_7100357314(0.1f);
    sead::Vector3f pos;
    sub_710035797C(nullptr, &pos, mActor->getMtx().getTranslation());
    m40(-1.0f);
}

void DragonRoot::m41() {
    sub_7100356CFC();
    _1d8 = 30;
    _24c.set(0x14);
}

// NON_MATCHING: the original tests bit 8 of _24c between the two BaseProcHandle fields
void DragonRoot::m43() {
    auto* dragon = sead::DynamicCast<act::Dragon>(mActor);
    if (!dragon || dragon->_1f70.isOnBit(28))
        return;
    _24c.reset(0x20);
    if (!_24c.isOn(8) || _250.isAllocatedOrFailed() || _24c.isOn(0x100) || m47())
        _24c.set(0x20);
}

void DragonRoot::m44(const sead::Vector3f& pos) {}

bool DragonRoot::m47() {
    auto* dragon = sead::DynamicCast<act::Dragon>(mActor);
    if (!dragon)
        return false;
    if (_24c.isOnBit(7) && !dragon->_1f70.isOnBit(31))
        return true;
    return false;
}

}  // namespace uking::ai
