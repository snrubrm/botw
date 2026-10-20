#include "Game/Actor/AI/aiDragonRoot.h"
#include "Game/Actor/actDragon.h"
#include "Game/Actor/aiUnk_710072BA90.h"
#include "KingSystem/Map/mapMubinIter.h"
#include "KingSystem/Physics/System/physRayCastBodyQuery.h"
#include "Game/gameSceneSubsys14.h"
#include "Game/Actor/Damage/dmgDamageCallback.h"
#include "KingSystem/Sound/sndBgmMgr.h"
#include "KingSystem/System/VFR.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "Game/Actor/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actAttackSensor.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Map/mapRail.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Utils/Thread/Message.h"
#include <gfx/seadCamera.h>
#include <gfx/seadProjection.h>
#include <gfx/seadViewport.h>
#include "KingSystem/Camera/CameraMgr.h"
#include "KingSystem/System/CameraS1.h"

namespace uking::ai {

void DragonRoot::Unk2::sub_710036B89C() {
    for (auto& entry : _0) {
        if (entry._0.isAllocatedOrFailed() && entry._0.isProcReady()) {
            if (auto* actor = sead::DynamicCast<ksys::act::Actor>(entry._0.getProc())) {
                entry._10.acquire(actor, false);
                entry._0.releaseAndWakeProc();
            }
        }
    }
}

void Unk_71023e3a40::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, act::DamageCallbackInfo* a6) {
    if (*a1 < 1)
        return;

    auto* damage_manager = sead::DynamicCast<act::DamageManager>(mDamageManager);
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

DragonRoot::DragonRoot(const InitArg& arg) : ControlRailRoot(arg) {}

DragonRoot::~DragonRoot() = default;

bool DragonRoot::init_(sead::Heap* heap) {
    if (!ControlRailRoot::init_(heap))
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
    ControlRailRoot::enter_(params);
    auto* dragon = sead::DynamicCast<act::Dragon>(mActor);
    if (!dragon)
        return;

    _248 = dragon->x_0() * (1.0f / ksys::VFR::instance()->getDeltaFrame());
    if (!dragon->_1f70.isOnBit(28))
        setDamageCallbackTiming(dragon, 0, &_98);
    if (!isRootAiParamINot5())
        return;

    if (!dragon->_1f70.isOnBit(28)) {
        if (auto* bgm = ksys::snd::sub_7100FFE094()) {
            bgm->_58 = true;
            bgm->sub_7101001808(dragon->sub_710000FE10());
        }
    }
    dragon->sub_710000E500(mDefaultMaterialAnmName_s);
    dragon->sub_710000EA88(mHornAnmName_s);
}

bool DragonRoot::reenter_(ksys::act::ai::ActionBase* other, bool x) {
    if (!ControlRailRoot::reenter_(other, true))
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

void DragonRoot::sub_710036F80C() {
    sub_71007A44E4(mActor, true);
    getActorAttackSensor(mActor)->activateAttackSensor(0x2000, 0x800c, *mBodyHitDamage_s,
                                                       *mBodyHitPower_s, 1.0f, *mBodyHitImpact_s,
                                                       *mBodyHitShieldDamage_s, -1, false, 1, -1);
    if (auto* set = mActor->getPhysics()->findBodyByName(*sub_71007A24BC())) {
        const s32 count = set->getRigidBodies().size();
        for (s32 i = 0; i < count; ++i) {
            auto* body = set->getRigidBodies()[i];
            if ((body->isAddedToWorld() || body->isAddingBodyToWorld()) && body &&
                body->getContactLayer() == ksys::phys::ContactLayer::SensorAttackEnemy) {
                sub_71007A2B64(body, nullptr);
            }
        }
    }
}

// NON_MATCHING: calls the non-const Rail::getPoint (the original uses the const overload; the rail
// pointer is non-const here).
void DragonRoot::calc_() {
    ControlRailRoot::calc_();
    if (isFinished() || isFailed())
        return;

    auto* dragon = sead::DynamicCast<act::Dragon>(mActor);
    if (!dragon)
        return;

    if (!dragon->_1f70.isOnBit(30))
        dragon->setGameDataFlag(true, "Appearance_Today", -1);
    if (!dragon->_1f70.isOnBit(28)) {
        if (auto* bgm = ksys::snd::sub_7100FFE094())
            bgm->_5c = dragon->_1f6c;
    }
    if (_250.isProcReady()) {
        _250.releaseAndWakeProc();
        _24c.set(0x80);
    }

    m42();
    m43();

    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("レールに向かう")) {
            if (child->isFinished())
                m41();
            else
                m40(-1.0f);
        } else if (isCurrentChild("帰還")) {
            dragon->deleteLater(ksys::act::BaseProc::DeleteReason::_0);
            setFinished();
        }
    } else if (child->isChangeable()) {
        if (m47()) {
            ksys::phys::RayCastBodyQuery query(nullptr, ksys::phys::GroundHit::HitAll);
            query.enableLayer(ksys::phys::ContactLayer::EntityGround);
            query.enableLayer(ksys::phys::ContactLayer::EntityGroundObject);
            query.enableLayer(ksys::phys::ContactLayer::EntityGroundRough);
            query.enableLayer(ksys::phys::ContactLayer::EntityGroundSmooth);
            query.enableLayer(ksys::phys::ContactLayer::EntityHitOnlyGround);
            query.enableLayer(ksys::phys::ContactLayer::EntityWater);
            sead::Vector3f dir;
            sub_7100010168(dragon, &dir);
            query.setStartAndDisplacementScaled(dragon->getMtx().getTranslation(), dir, 60.0f);
            query.setNormalCheckingMode(ksys::phys::RayCast::NormalCheckingMode::_0);
            if (!query.worldRayCast(ksys::phys::ContactLayerType::Entity) && dragon->_1e0c != 3 &&
                !isCurrentChild("帰還")) {
                changeChild("帰還");
            }
            act::sub_710000AE6C();
        }

        if (isCurrentChild("移動") && sub_7100357268(0.5f))
            changeChild("帰還");

        if (!dragon->_1f70.isOnBit(28)) {
            auto* damage_mgr = sub_710072BA90(dragon);
            if (damage_mgr && s32(damage_mgr->getDamage()) >= 1) {
                m45(damage_mgr);
                const s32 max_life = dragon->getMaxLife();
                if (auto* life = dragon->getLife())
                    *life = max_life;
            }
        }

        if (dragon->_1e0c != 3) {
            if (!(_1e0 > f32(*mReturnTime_s))) {
                ksys::Timer::update(&_1e0, 1.0f);
            } else if (!dragon->_1f70.isOnBit(28)) {
                if (!isCurrentChild("帰還"))
                    changeChild("帰還");
            } else if (!m46()) {
                dragon->deleteLater(ksys::act::BaseProc::DeleteReason::_0);
            }
        }
    }

    if (!dragon->_1f70.isOnBit(28) && hasAttackInfo(dragon)) {
        if (auto* info = getAttackInfo(mActor, 0))
            m44(info->_0);
    }

    if (_24c.isOn(4)) {
        if (!_24c.isOn(8) && _1d8-- < 0) {
            if (_24c.isOn(0x10))
                dragon->sub_710000EC50();
            mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_20);
            mActor->get68c() = 0;
            _24c.set(8);
        }
    } else if (_24c.isOn(8) && _1d8-- < 0) {
        mActor->get68c() = 1;
        _24c.reset(8);
    }

    if (_24c.isOn(8)) {
        ksys::Timer::update(&_1dc, 1.0f);
        if (_1dc > 30.0f) {
            const bool was_on = dragon->_1f70.isOnBit(28);
            dragon->_1f70.setBit(21);
            if (!was_on) {
                sub_71007A458C(mActor, true);
                sub_710036F80C();
            }
        }
    }

    f32 scale;
    if (auto* point = _38._8.rail->getPoint(s32(_38._30.progress))) {
        sead::Vector3f point_scale;
        point->getIter().getScale(&point_scale);
        scale = point_scale.x;
    } else {
        scale = 1.0f;
    }
    _248 = _248 + (scale * *mSpeed_s - _248) * 0.05f;
}

// NON_MATCHING: the original computes &_1f0 once before the payload lock and reuses it for the send.
void DragonRoot::leave_() {
    if (auto* dragon = sead::DynamicCast<act::Dragon>(mActor)) {
        isActorDeletedOrDeleting();
        if (!dragon->_1f70.isOnBit(28)) {
            sub_71005DA114(mActor, &_98);
            if (isActorDeletedOrDeleting()) {
                if (auto* bgm = ksys::snd::sub_7100FFE094())
                    bgm->_58 = false;
                if (_24c.isOnBit(0)) {
                    {
                        sead::ScopedLock<sead::JobQueueLock> lock(&_1f0._18.mLock);
                        _1f0._18._0 = false;
                    }
                    if (!isActorDeletedOrDeleting()) {
                        _1f0.sub_710070DBB0(*GameSceneSubsys14::instance()->mTransceiver.getId(),
                                            true);
                    }
                    _24c.resetBit(0);
                }
            }
        }
    }
    ControlRailRoot::leave_();
}

void DragonRoot::loadParams_() {
    ControlRailRoot::loadParams_();
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

void DragonRoot::m40(f32 start_progress) {
    auto* dragon = sead::DynamicCast<act::Dragon>(mActor);
    if (!dragon)
        return;

    f32 progress = start_progress;
    if (progress < 0) {
        const sead::Vector3f pos = dragon->getMtx().getTranslation();
        sub_710035797C(&progress, nullptr, pos);
    }
    sub_7100356764(_38._8.rail, progress);

    sead::Vector3f target;
    sead::Vector3f dir;
    _38._8.rail->calcTranslateRotate(&target, &dir, progress);
    dir.normalize();
    f32 distance = (dragon->getMtx().getTranslation() - target).length();
    if (distance > 0) {
        distance = sead::Mathf::max(distance, 100.0f);
        dir *= distance;
        target -= dir;
        ksys::act::ai::InlineParamPack params;
        params.addVec3(target, "TargetPos", -1);
        params.addVec3(dir, "TargetVec", -1);
        changeChild("レールに向かう", &params);
    } else {
        m41();
    }
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

// NON_MATCHING: the flag at bit 8 is tested before the BaseProcHandle pointer.
void DragonRoot::m45(act::DamageManager* damage_mgr) {
    auto* dragon = sead::DynamicCast<act::Dragon>(mActor);
    if (!dragon || _24c.isOnBit(5) || _250.getUnit() || _24c.isOnBit(8) || _250.hasFailed())
        return;
    dragon->_1f70.setBit(29);
    _230 = 0.0f;
    spawnDrop(dragon, damage_mgr, sead::Vector3f::zero, sead::Vector3f::zero);
}

// NON_MATCHING: the four screen-bounds compares are chained in a different order (fccmp sequence).
bool DragonRoot::m46() {
    auto* camera = ksys::CameraMgr::instance()->getLookAtCamera();
    if (!camera)
        return false;

    sead::Vector3f look;
    camera->getLookVectorByMatrix(&look);
    for (s32 i = 0; i < 5; ++i) {
        sead::Matrix34f mtx = sead::Matrix34f::ident;
        switch (i) {
        case 0:
            mActor->sub_71011D57F8(&mtx, "Head");
            break;
        case 1:
            mActor->sub_71011D57F8(&mtx, "Wrist_A_L");
            break;
        case 2:
            mActor->sub_71011D57F8(&mtx, "Wrist_B_L");
            break;
        case 3:
            mActor->sub_71011D57F8(&mtx, "Wrist_C_L");
            break;
        case 4:
            mActor->sub_71011D57F8(&mtx, "Spine_31");
            break;
        default:
            break;
        }

        const sead::Vector3f pos = mtx.getTranslation();
        if ((pos - camera->getPos()).dot(look) < 0) {
            if (auto* viewport = ksys::CameraMgr::instance()->sub_7100D8C4C8()) {
                f32 x;
                f32 y;
                {
                    sead::PerspectiveProjection projection;
                    sub_7100D8AED0(camera, &projection);
                    sead::Vector2f screen;
                    camera->projectByMatrix(&screen, pos, projection, *viewport);
                    screen.x /= viewport->getSizeX();
                    x = screen.x;
                    screen.y /= viewport->getSizeY();
                    y = screen.y;
                }
                if (x > -0.5f && x < 0.5f && y > -0.5f && y < 0.5f)
                    return true;
            }
        }
    }
    return false;
}

bool DragonRoot::m47() {
    auto* dragon = sead::DynamicCast<act::Dragon>(mActor);
    if (!dragon)
        return false;
    if (_24c.isOnBit(7) && !dragon->_1f70.isOnBit(31))
        return true;
    return false;
}

}  // namespace uking::ai
