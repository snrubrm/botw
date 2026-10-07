#include "Game/AI/AI/aiGrudgeEyeball.h"
#include "Game/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Sound/sndMgr.h"

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
