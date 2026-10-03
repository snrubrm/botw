#include "Game/AI/AI/aiHeroSoulGiftRoot.h"
#include "KingSystem/ActorSystem/LOD/actLodState.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::ai {

HeroSoulGiftRoot::HeroSoulGiftRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

HeroSoulGiftRoot::~HeroSoulGiftRoot() = default;

bool HeroSoulGiftRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void HeroSoulGiftRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    _88 = false;
    _58 = mActor->getMtx();
    if (auto* lod = mActor->getLodState())
        lod->mFlags26.set(1);

    sead::Matrix34f mtx;
    if (m35(&mtx))
        mActor->setMtx(mtx, false, true);

    if (m37())
        changeChild("発動");
    else
        changeChild("待機");
}

// NON_MATCHING: register allocation (ours keeps the address of the player accessor in a callee-saved
// register for the destructor call; the original recomputes it)
bool HeroSoulGiftRoot::m34(sead::Matrix34f* mtx) {
    if (*mUseInitMtxForBasePos_s && *mUseInitMtxForBaseRot_s) {
        *mtx = _58;
        return true;
    }

    if (mActor->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_200)) {
        *mtx = sead::Matrix34f::ident;
        return true;
    }

    ksys::act::acc::PlayerBase player;
    player.getPlayerFromPlayerInfo();
    if (!player.hasProc())
        return false;

    if (*mUseInitMtxForBasePos_s) {
        const sead::Vector3f t = _58.getTranslation();
        *mtx = player.getActorMtx();
        mtx->setTranslation(t);
    } else {
        const bool use_rot = *mUseInitMtxForBaseRot_s;
        const auto& player_mtx = player.getActorMtx();
        if (use_rot) {
            const f32 x = player_mtx.m[0][3];
            const f32 y = player_mtx.m[1][3];
            const f32 z = player_mtx.m[2][3];
            *mtx = _58;
            mtx->m[0][3] = x;
            mtx->m[1][3] = y;
            mtx->m[2][3] = z;
        } else {
            *mtx = player_mtx;
        }
    }
    return true;
}

void HeroSoulGiftRoot::calc_() {
    {
        sead::Matrix34f mtx;
        if (m35(&mtx))
            mActor->setMtx(mtx, false, true);
    }

    if (_88) {
        m36();
        return;
    }

    auto* child = getCurrentChild();
    if (isCurrentChild("待機") && m37()) {
        changeChild("発動");
        return;
    }

    if (!child->isFinished() && !child->isFailed())
        return;

    if (isCurrentChild("発動"))
        sub_710042EEB4();
    else if (isCurrentChild("退場"))
        setFinished();
}

void HeroSoulGiftRoot::leave_() {
    if (auto* lod = mActor->getLodState())
        lod->mFlags26.reset(1);
}

void HeroSoulGiftRoot::loadParams_() {
    getStaticParam(&mUseInitMtxForBasePos_s, "UseInitMtxForBasePos");
    getStaticParam(&mUseInitMtxForBaseRot_s, "UseInitMtxForBaseRot");
    getStaticParam(&mPosOffset_s, "PosOffset");
    getStaticParam(&mRotOffset_s, "RotOffset");
}

bool HeroSoulGiftRoot::handleMessage_(const ksys::Message* message) {
    if (message->getType() == 0x8000036) {
        _88 = true;
        return true;
    }
    return false;
}

void HeroSoulGiftRoot::m36() {
    _88 = false;
    if (isCurrentChild("退場"))
        return;

    sub_710042EEB4();
}

void HeroSoulGiftRoot::sub_710042EEB4() {
    if (mActor->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_20))
        mActor->sleep(ksys::act::BaseProc::SleepWakeReason::_0);
    else
        changeChild("退場");
}

}  // namespace uking::ai
