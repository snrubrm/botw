#include "Game/Actor/AI/aiSandwormRoot.h"
#include "Game/Actor/aiUnk_7102451120.h"
#include "Game/Actor/actEnemy.h"
#include "Game/Actor/actSandworm.h"
#include "Game/Actor/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/Profiles/actBullet.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "Game/Actor/Player/actPlayerInfo.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectSandworm.h"
#include <gsys/gsysModel.h>
#include <limits>

// 0x71002ccc20 (free function, declared only): one of the SiteBoss / Enemy part names by index (a static table).
const sead::SafeString& sub_71002CCC20(s32 idx);

namespace uking::ui {
// 0x7100a96310 (defined in uiScreenFacade.cpp, not declared in a header).
s32 sub_7100A96310();
}  // namespace uking::ui

namespace uking::ai {

SandwormRoot::SandwormRoot(const InitArg& arg) : EnemyRoot(arg) {}

SandwormRoot::~SandwormRoot() = default;

bool SandwormRoot::init_(sead::Heap* heap) {
    if (!EnemyRoot::init_(heap))
        return false;

    if (auto* sandworm = sead::DynamicCast<act::Sandworm>(mActor))
        sandworm->_1650 = mActor->findPhysicsBodyByName(sub_71007A24E4()->cstr(), "Spine_1");
    return true;
}

void SandwormRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    _250._24 = *mWeakPointDamageRate_s;
    auto* actor = mActor;
    setDamageCallbackTiming(actor, 0, &_250);
    sub_7100720140(actor);
    _288 = 0;
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
    _1e8.x();
    _238.mTimer.reset(0.0f);
    _278.sub_7100721380(std::numeric_limits<f32>::infinity(), mActor);
}

void SandwormRoot::leave_() {
    sub_71005DA114(mActor, &_250);
    if (_288 != 0) {
        auto* actor = mActor;
        sub_7100720140(actor);
        sub_7100720A70(actor);
    }
    _288 = 0;
    EnemyRoot::leave_();
}

void SandwormRoot::loadParams_() {
    EnemyRoot::loadParams_();
    getStaticParam(&mSandOffset_s, "SandOffset");
    getStaticParam(&mWeakPointDamageRate_s, "WeakPointDamageRate");
}

// 0x710055d7c8
void Unk_710241c6c0::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, act::DamageCallbackInfo* a6) {
    if (*a1 < 1)
        return;
    auto* manager = sead::DynamicCast<act::DamageManager>(mDamageManager);
    if (!manager)
        return;
    auto* enemy = sead::DynamicCast<act::Enemy>(manager->mActor);
    if (!enemy)
        return;

    if (*a4 == 4) {
        auto* attacker = manager->getAttacker();
        if (enemy->_1128.getActorPartsActor(sub_71002CCC20(0)) == *attacker ||
            enemy->_1128.getActorPartsActor(sub_71002CCC20(1)) == *attacker) {
            *a1 = 0;
            *a4 = -1;
            *a5 = -1;
            return;
        }
    }

    if (*a4 == 3) {
        auto* attacker = manager->getAttacker();
        ksys::act::acc::Bullet accessor;
        if (ksys::act::acquireActor(attacker, &accessor)) {
            if (accessor.getName() == "BombArrow_A" && !accessor.sub_71000057DC()) {
                *a5 = 22;
                return;
            }
        }
    }

    if (auto* body = enemy->findPhysicsBodyByName(sub_71007A24D0()->cstr(), "Body")) {
        if (manager->isDamageSourceObjectMaybe(body)) {
            *a1 = s32(_24 * f32(*a1));
            if (auto* info = sead::DynamicCast<act::DamageCallbackInfo>(a6))
                info->mFlags |= 0x2001;
        }
    }
}

// NON_MATCHING: regalloc (ours keeps &_1e8._38.mLink in a callee-saved register; the original recomputes it)
// A hit by a weak-point attack (message 0x8000042): remembers the attacker and applies its attack power as
// damage type 22.
bool SandwormRoot::handleMessage_(const ksys::Message* message) {
    if (!_1e8.m2(*message))
        return EnemyRoot::handleMessage_(message);

    sub_7100720A00(mActor, nullptr);
    if (auto* manager = mActor->getDamageMgr()) {
        ksys::act::ActorLinkConstDataAccess accessor;
        if (ksys::act::acquireActor(&_1e8._38.mLink, &accessor)) {
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

// Bombs held by the two parts actors follow the "Spine_4" bone; when the weak-point timer runs out, the sleeping
// "RemoteBomb" parts are placed there and hit the Sandworm with their attack power (damage type 22).
void SandwormRoot::calc_() {
    auto* actor = mActor;
    if (!sub_71005D8F28(actor) && sub_7100720038(actor))
        sub_710072009C(actor);
    if (auto* sandworm = sead::DynamicCast<act::Sandworm>(actor))
        sandworm->sub_71002CDDE8();

    if (_1e8._30) {
        sub_710072009C(actor);
        _1e8.x();
        if (_238.mTimer.value <= sead::Mathf::epsilon())
            _238.mTimer.reset(8.0f);
    } else if (!(_238.mTimer.value <= sead::Mathf::epsilon())) {
        _238.sub_7100D3BCE4();
        if (_238.mTimer.value <= sead::Mathf::epsilon()) {
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
    sub_710055E304();
}

// NON_MATCHING: the original adds the squared components as y + x then z + (y + x) and loads the player x alone
// (ours: x + y, z; one ldp)
void SandwormRoot::sub_710055E304() {
    auto* actor = mActor;
    if (isCurrentChild("リアクション")) {
        const s32* life = actor->getLife();
        if (life && *life <= 0) {
            if (_288 != 0) {
                auto* a = mActor;
                sub_7100720140(a);
                sub_7100720A70(a);
            }
            _288 = 0;
            return;
        }
    }

    if (sub_710072B8E4()) {
        const sead::Vector3f& player_pos = getPlayerPosition();
        const auto* param = actor->getParam()->getRes().mGParamList->getSandworm();
        if (param) {
            const f32 dist = (actor->getMtx().getTranslation() - player_pos).length();
            const bool flag = sub_71005D8F28(actor);
            switch (_288) {
            case 0:
                if (flag) {
                    auto* a = mActor;
                    sub_71007200B8(a);
                    sub_7100720A30(a);
                    _288 = 2;
                } else if (dist < param->mShowLifeGageDist.ref()) {
                    auto* a = mActor;
                    sub_71007200B8(a);
                    sub_7100720A30(a);
                    _288 = 1;
                }
                break;
            case 1:
                if (flag)
                    _288 = 2;
                else if (dist > param->mShowLifeGageDist.ref() + param->mShowLifeGageOffset.ref())
                    goto hide;
                break;
            case 2:
                if (flag)
                    break;
                if (dist > param->mShowLifeGageDist.ref() + param->mShowLifeGageOffset.ref())
                    goto hide;
                _288 = 1;
                break;
            hide: {
                auto* a = mActor;
                sub_7100720140(a);
                sub_7100720A70(a);
                _288 = 0;
                break;
            }
            }
        }
    }

    if (_288 != 0)
        ui::sub_7100A96310();
}

}  // namespace uking::ai
