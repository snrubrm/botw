#include "Game/AI/AI/aiStalEnemyRoot.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_7100724C64.h"
#include "Game/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/Profiles/actBullet.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"

namespace uking::ai {

StalEnemyRoot::StalEnemyRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

StalEnemyRoot::~StalEnemyRoot() {
    auto* actor = mActor;
    sub_71007253C0(actor);
    sub_71007254A4(actor);
    if (mStalEnemyUnit_a && *static_cast<Unk_71024241a8**>(mStalEnemyUnit_a) == &_2e8)
        *static_cast<Unk_71024241a8**>(mStalEnemyUnit_a) = nullptr;
    if (_60) {
        delete _60;
        _60 = nullptr;
    }
}

bool StalEnemyRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void StalEnemyRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void StalEnemyRoot::leave_() {
    sub_71005DA114(mActor, &_38);
}

bool StalEnemyRoot::handleMessage_(const ksys::Message* message) {
    if (!isCurrentChild("所持") && _100.m2(*message))
        return true;

    auto* actor = mActor;
    if (!actor->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_40000000) && !_150._30 &&
        ksys::act::isAttClientEnabled(actor, "Grab")) {
        if (!isCurrentChild("所持") && !isCurrentChild("拾い合体") && _150.m2(*message)) {
            _150.sub_710070B5A0(actor);
            return true;
        }
    }

    if (message->getType() == 0x3000007) {
        _2e0 = true;
        return true;
    }
    return false;
}

void StalEnemyRoot::loadParams_() {
    getStaticParam(&mDeadCount_s, "DeadCount");
    getStaticParam(&mSearchFrame_s, "SearchFrame");
    getStaticParam(&mInWaterDepth_s, "InWaterDepth");
    getStaticParam(&mOutOfWaterOffset_s, "OutOfWaterOffset");
    getStaticParam(&mDeadCheckFrame_s, "DeadCheckFrame");
    getStaticParam(&mSpreadDist_s, "SpreadDist");
    getStaticParam(&mSmallSpreadDist_s, "SmallSpreadDist");
    getStaticParam(&mSearchDistXZ_s, "SearchDistXZ");
    getStaticParam(&mSearchDistY_s, "SearchDistY");
    getStaticParam(&mFallHeight_s, "FallHeight");
    getMapUnitParam(&mIsCreateStalPart_m, "IsCreateStalPart");
    getAITreeVariable(&mIsStopFallCheck_a, "IsStopFallCheck");
    getAITreeVariable(&mStalEnemyUnit_a, "StalEnemyUnit");
}

bool StalEnemyRoot::m34() {
    if (_2e8._8.isOnBit(0))
        return false;
    return sub_71005D6E28(mActor);
}

void StalEnemyRoot::m35(ksys::act::ai::InlineParamPack* params) {}

bool StalEnemyRoot::m36() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed())
        return true;
    return getCurrentChild()->isChangeable();
}

// 0x71005a2544
void Unk_7102424170::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, dmg::DamageCallbackInfo* a6) {
    if (*a5 == -1)
        return;

    if (!_24 && *a1 >= 1) {
        const s32* life = mDamageManager->mActor->getLife();
        if (!life || *life <= 1) {
            switch (*a4) {
            case 0:
            case 1:
            case 2: {
                if (*a4 == 0) {
                    auto* manager = sead::DynamicCast<dmg::DamageManager>(mDamageManager);
                    ksys::act::ActorConstDataAccess accessor;
                    if (manager && ksys::act::acquireActor(manager->m37(), &accessor) &&
                        accessor.getProfile() == "WeaponShield") {
                        return;
                    }
                }
                switch (*a5) {
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                case 15:
                case 17:
                    *a5 = 22;
                    break;
                }
                break;
            }
            default: {
                auto* manager = sead::DynamicCast<dmg::DamageManager>(mDamageManager);
                ksys::act::acc::Bullet accessor;
                if (manager && ksys::act::acquireActor(manager->m37(), &accessor) &&
                    accessor.isReflectThrownBullet()) {
                    *a5 = 22;
                }
                break;
            }
            }
        }
    }

    if (auto* info = sead::DynamicCast<dmg::DamageCallbackInfo>(a6)) {
        if ((info->mFlags & 1) && *a1 <= 0)
            *a1 = 1;
    }
}

}  // namespace uking::ai
