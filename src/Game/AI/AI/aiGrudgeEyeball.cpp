#include "Game/AI/AI/aiGrudgeEyeball.h"
#include "Game/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/Sound/sndSound.h"

namespace uking::ai {

void Unk_71023f64e0::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, dmg::DamageCallbackInfo* a6) {
    if (*a5 != -1)
        *a1 = 0;
}

GrudgeEyeball::GrudgeEyeball(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GrudgeEyeball::~GrudgeEyeball() = default;

bool GrudgeEyeball::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GrudgeEyeball::enter_(ksys::act::ai::InlineParamPack* params) {
    if (*mEyeballFirstState_m == 0) {
        if (auto* damage_mgr = mActor->getDamageMgr()) {
            if (auto* manager = sead::DynamicCast<uking::dmg::DamageManager>(damage_mgr)) {
                manager->removeDamageCallback(&_40);
                _70 = false;
            }
        }
        changeChild("開けて待機", nullptr);
    } else {
        if (!_70) {
            if (auto* damage_mgr = mActor->getDamageMgr()) {
                if (auto* manager = sead::DynamicCast<uking::dmg::DamageManager>(damage_mgr)) {
                    manager->addDamageCallback(4, &_40);
                    _70 = true;
                }
            }
        }
        changeChild("閉じて待機", nullptr);
    }
    if (auto* sound = ksys::snd::SoundMgr::instance()->_38->_48)
        sound->sub_7101035B50(mActor);
}

// NON_MATCHING: the 開けて待機 life test compiles to `cmp #1; b.lt` instead of `cmp #0; b.le`; the rest matches.
void GrudgeEyeball::calc_() {
    const auto removeCallback = [this] {
        if (auto* damage_mgr = mActor->getDamageMgr()) {
            if (auto* manager = sead::DynamicCast<uking::dmg::DamageManager>(damage_mgr)) {
                manager->removeDamageCallback(&_40);
                _70 = false;
            }
        }
    };
    const auto addCallback = [this] {
        if (_70)
            return;
        if (auto* damage_mgr = mActor->getDamageMgr()) {
            if (auto* manager = sead::DynamicCast<uking::dmg::DamageManager>(damage_mgr)) {
                manager->addDamageCallback(4, &_40);
                _70 = true;
            }
        }
    };

    auto* actor = mActor;
    auto* child = getCurrentChild();
    if (actor->checkBasicSig()) {
        if (isCurrentChild("閉じて待機") || isCurrentChild("開けて待機") || isCurrentChild("閉じる")) {
            removeCallback();
            changeChild("発見");
            return;
        }
    } else if (*mEyeballFirstState_m == 0) {
        if (!isCurrentChild("開けて待機")) {
            auto* life = actor->getLife();
            if (!life || *life > 0) {
                removeCallback();
                changeChild("開けて待機");
                return;
            }
        }
    } else if (!isCurrentChild("閉じて待機") && !isCurrentChild("閉じる") &&
               !isCurrentChild("閉じてダメージ")) {
        auto* life = actor->getLife();
        if (!life || *life > 0) {
            addCallback();
            changeChild("閉じる");
            return;
        }
    }

    if ((isCurrentChild("閉じて待機") || isCurrentChild("閉じてダメージ")) &&
        sub_71007A274C(actor)) {
        changeChild("閉じてダメージ");
        return;
    }

    if (!child->isFinished() && !child->isFailed())
        return;
    if (!isCurrentChild("閉じる") && !isCurrentChild("閉じてダメージ"))
        return;
    addCallback();
    changeChild("閉じて待機");
}

void GrudgeEyeball::leave_() {
    if (auto* damage_mgr = mActor->getDamageMgr()) {
        if (auto* manager = sead::DynamicCast<uking::dmg::DamageManager>(damage_mgr)) {
            manager->removeDamageCallback(&_40);
            _70 = false;
        }
    }
    if (auto* sound = ksys::snd::SoundMgr::instance()->_38->_48)
        sound->sub_7101035C50(mActor->getId(), mActor->getHashId());
}

void GrudgeEyeball::loadParams_() {
    getMapUnitParam(&mEyeballFirstState_m, "EyeballFirstState");
}

}  // namespace uking::ai
