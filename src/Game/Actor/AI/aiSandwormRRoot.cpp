#include "Game/Actor/AI/aiSandwormRRoot.h"
#include "Game/Actor/aiUnk_7102451120.h"
#include "Game/Actor/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "Game/Actor/actSandworm.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/Player/actPlayerInfo.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectSandworm.h"
#include <gsys/gsysModel.h>
#include <limits>
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/ActorSystem/Profiles/actBullet.h"

// 0x71002ccc20 (free function, declared only; as in aiSandwormRoot.cpp).
const sead::SafeString& sub_71002CCC20(s32 idx);

namespace uking::ui {
// 0x7100a96310 (defined in uiScreenFacade.cpp, not declared in a header).
s32 sub_7100A96310();
}  // namespace uking::ui

namespace uking::ai {

void Unk_710241c878::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5,
                          act::DamageCallbackInfo* a6) {
    if (auto* damage_mgr = sead::DynamicCast<act::DamageManager>(mDamageManager))
        mOwner->m45(a1, a2, a3, a4, a5, a6, damage_mgr);
}

SandwormRRoot::SandwormRRoot(const InitArg& arg) : EnemyRoot(arg) {}

SandwormRRoot::~SandwormRRoot() = default;

bool SandwormRRoot::init_(sead::Heap* heap) {
    if (!EnemyRoot::init_(heap))
        return false;

    if (auto* sandworm = sead::DynamicCast<act::Sandworm>(mActor))
        sandworm->_1650 = mActor->findPhysicsBodyByName(sub_71007A24E4()->cstr(), "Spine_1");
    return true;
}

void SandwormRRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    setDamageCallbackTiming(actor, 0, &_258);
    sub_7100720140(actor);
    _298 = 0;
    if (isRootAiParamINot5()) {
        if (auto* as_list = mActor->getASList())
            as_list->startAnimationMaybe(-1.0f, -1.0f, "SwimNormal", 0, 0, true);
    }
    EnemyRoot::enter_(params);
    if (auto* sandworm = sead::DynamicCast<act::Sandworm>(actor)) {
        const f32 offset = *mSandOffset_s;
        sandworm->_159c = offset;
        sandworm->_15b0 = offset;
    }
    sub_71007A397C(actor);
    _1f0.x();
    _240.mTimer.reset(0.0f);
    _288.sub_7100721380(std::numeric_limits<f32>::infinity(), mActor);

    if (ksys::act::hasTag(mActor, 0x12AD8456u)) {
        _29c.makeAllZero();
        for (s32 i = 0; i < sub_71005D7854(mActor); ++i) {
            if (sub_71005D83E8(mActor, i))
                _29c.set(1 << i);
        }
    }
}

void SandwormRRoot::leave_() {
    sub_71005DA114(mActor, &_258);
    if (_298 != 0) {
        auto* actor = mActor;
        sub_7100720140(actor);
        sub_7100720A70(actor);
    }
    _298 = 0;
    EnemyRoot::leave_();
}

void SandwormRRoot::loadParams_() {
    EnemyRoot::loadParams_();
    getStaticParam(&mSandOffset_s, "SandOffset");
    getStaticParam(&mWeakPointDamageRate_s, "WeakPointDamageRate");
    getStaticParam(&mWeakChimicalDamageRate_s, "WeakChimicalDamageRate");
}

// NON_MATCHING: regalloc (same as SandwormRoot::handleMessage_)
// A hit by a weak-point attack (message 0x8000042): remembers the attacker and applies its attack power as
// damage type 22.
bool SandwormRRoot::handleMessage_(const ksys::Message* message) {
    if (!_1f0.m2(*message))
        return EnemyRoot::handleMessage_(message);

    sub_7100720A00(mActor, nullptr);
    if (auto* manager = mActor->getDamageMgr()) {
        ksys::act::ActorLinkConstDataAccess accessor;
        if (ksys::act::acquireActor(&_1f0._38.mLink, &accessor)) {
            act::Struct20_2 damage;
            damage.mField_8 = accessor.getAttackPower();
            damage.mField_14 = 4;
            damage.mField_18 = 22;
            if (manager->mStruct20_a) {
                manager->mField_30.lock();
                manager->mStruct20_a->combineMaybe(&damage);
                manager->mField_30.unlock();
            }
        }
    }
    return true;
}

// 0x710055f874
void SandwormRRoot::m45(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, act::DamageCallbackInfo* a6,
                        act::DamageManager* damage_mgr) {
    if (*a1 < 1)
        return;
    auto* enemy = sead::DynamicCast<act::Enemy>(damage_mgr->mActor);
    if (!enemy)
        return;

    if (*a4 == 4) {
        auto* attacker = damage_mgr->getAttacker();
        if (enemy->_1128.getActorPartsActor(sub_71002CCC20(0)) == *attacker ||
            enemy->_1128.getActorPartsActor(sub_71002CCC20(1)) == *attacker) {
            *a1 = 0;
            *a4 = -1;
            *a5 = -1;
            return;
        }
    }

    if (*a4 == 3) {
        auto* attacker = damage_mgr->getAttacker();
        ksys::act::acc::Bullet accessor;
        if (ksys::act::acquireActor(attacker, &accessor)) {
            if (accessor.getName() == "BombArrow_A" && !accessor.sub_71000057DC())
                *a5 = 22;
        }
    }

    bool weak_point_hit = false;
    if (auto* body = enemy->findPhysicsBodyByName(sub_71007A24D0()->cstr(), "Body")) {
        if (damage_mgr->isDamageSourceObjectMaybe(body)) {
            weak_point_hit = true;
            *a1 = s32(*mWeakPointDamageRate_s * f32(*a1));
        }
    }

    ksys::act::ActorLinkConstDataAccess accessor;
    auto* chemical = ksys::act::acquireActor(damage_mgr->m37(), &accessor) ? accessor.sub_7100D14E0C() : nullptr;
    if (chemical && (chemical->mMaterial->attribute.ref() & 0x108) == 0x108 && !(chemical->_be & 4) &&
        chemical->_1b8 > 0.0f) {
        *a1 = s32(f32(*a1) * *mWeakChimicalDamageRate_s);
    } else if (!weak_point_hit) {
        return;
    }
    if (auto* info = sead::DynamicCast<act::DamageCallbackInfo>(a6))
        info->mFlags |= 0x2001;
}

// Bombs held by the two parts actors follow the "Spine_4" bone; when the weak-point timer runs out, the sleeping
// "RemoteBomb" parts are placed there and hit the Sandworm with their attack power (damage type 22).
void SandwormRRoot::calc_() {
    auto* actor = mActor;
    if (!sub_71005D8F28(actor) && sub_7100720038(actor))
        sub_710072009C(actor);
    if (auto* sandworm = sead::DynamicCast<act::Sandworm>(actor))
        sandworm->sub_71002CDDE8();

    if (_1f0._30) {
        sub_710072009C(actor);
        _1f0.x();
        if (_240.mTimer.value <= sead::Mathf::epsilon())
            _240.mTimer.reset(8.0f);
    } else if (!(_240.mTimer.value <= sead::Mathf::epsilon())) {
        _240.sub_7100D3BCE4();
        if (_240.mTimer.value <= sead::Mathf::epsilon()) {
            if (auto* enemy = sead::DynamicCast<act::Enemy>(actor)) {
                sead::Matrix34f mtx = enemy->getMtx();
                ksys::act::ActorLinkConstDataAccess accessor;
                auto* manager = enemy->getDamageMgr();
                for (s32 i = 0; i < 2; ++i) {
                    if (!ksys::act::acquireActor(&enemy->getActorPartsActor(sub_71002CCC20(i)), &accessor))
                        continue;
                    if (!accessor.isStateSleep())
                        continue;
                    if (accessor.getName().findIndex("RemoteBomb") == -1)
                        continue;

                    if (auto* model = enemy->getModel()) {
                        const auto key = model->searchBone("Spine_4");
                        if (key.isValid())
                            model->getBoneWorldMatrix(key, &mtx);
                    }
                    accessor.setProperties(mtx, nullptr, nullptr, nullptr, false, 7, -1);
                    sub_7100720A00(enemy, nullptr);
                    if (manager) {
                        act::Struct20_2 damage;
                        damage.mField_8 = accessor.getAttackPower();
                        damage.mField_14 = 4;
                        damage.mField_18 = 22;
                        if (manager->mStruct20_a) {
                            manager->mField_30.lock();
                            manager->mStruct20_a->combineMaybe(&damage);
                            manager->mField_30.unlock();
                        }
                    }
                }
            }
        }
    }

    EnemyRoot::calc_();
    sub_710055F3E0();

    // Necklace weapons the actor no longer holds.
    if (ksys::act::hasTag(mActor, 0x12AD8456u)) {
        for (s32 i = 0; i < sub_71005D7854(mActor); ++i) {
            if (_29c.isOn(1 << i) && !sub_71005D83E8(mActor, i)) {
                _29c.reset(1 << i);
                if (auto* sandworm = sead::DynamicCast<act::Sandworm>(mActor))
                    sandworm->setNecklaceFlag(i);
            }
        }
    }
}

// NON_MATCHING: the original adds the squared components as y + x then z + (y + x) and loads the player x alone
// (ours: x + y, z; one ldp)
void SandwormRRoot::sub_710055F3E0() {
    auto* actor = mActor;
    if (isCurrentChild("リアクション")) {
        const s32* life = actor->getLife();
        if (life && *life <= 0) {
            if (_298 != 0) {
                auto* a = mActor;
                sub_7100720140(a);
                sub_7100720A70(a);
            }
            _298 = 0;
            return;
        }
    }

    if (sub_710072B8E4()) {
        const sead::Vector3f& player_pos = getPlayerPosition();
        const auto* param = actor->getParam()->getRes().mGParamList->getSandworm();
        if (param) {
            const f32 dist = (actor->getMtx().getTranslation() - player_pos).length();
            const bool flag = sub_71005D8F28(actor);
            switch (_298) {
            case 0:
                if (flag) {
                    auto* a = mActor;
                    sub_71007200B8(a);
                    sub_7100720A30(a);
                    _298 = 2;
                } else if (dist < param->mShowLifeGageDist.ref()) {
                    auto* a = mActor;
                    sub_71007200B8(a);
                    sub_7100720A30(a);
                    _298 = 1;
                }
                break;
            case 1:
                if (flag)
                    _298 = 2;
                else if (dist > param->mShowLifeGageDist.ref() + param->mShowLifeGageOffset.ref())
                    goto hide;
                break;
            case 2:
                if (flag)
                    break;
                if (dist > param->mShowLifeGageDist.ref() + param->mShowLifeGageOffset.ref())
                    goto hide;
                _298 = 1;
                break;
            hide: {
                auto* a = mActor;
                sub_7100720140(a);
                sub_7100720A70(a);
                _298 = 0;
                break;
            }
            }
        }
    }

    if (_298 != 0)
        ui::sub_7100A96310();
}

}  // namespace uking::ai
