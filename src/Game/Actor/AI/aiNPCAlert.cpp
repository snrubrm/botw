#include "Game/Actor/AI/aiNPCAlert.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "Game/Actor/aiUnk_7100711020.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "Game/Actor/Damage/dmgDamageManagerBase.h"
#include "Game/Actor/Player/actPlayerInfo.h"
#include "Game/Actor/Player/actPlayerBase.h"
#include <cmath>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Resource/Actor/resResourceAwareness.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectNpc.h"

namespace uking::ai {

NPCAlert::NPCAlert(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

NPCAlert::~NPCAlert() = default;

bool NPCAlert::init_(sead::Heap* heap) {
    auto* actor = mActor;
    _70 = actor->getParam()->getRes().mAwareness->sight_angle.ref();
    _74 = actor->getParam()->getRes().mGParamList->getNpc()->mIsNotTurnDetect.ref();
    return true;
}

// 0x71004bcdf8
// NON_MATCHING: scheduling / registers of the angle computation (the original computes the dot product first)
// and the branch condition form.
void NPCAlert::enter_(ksys::act::ai::InlineParamPack* params) {
    _76 = false;
    _77 = false;
    if (mTerrorEmitter_d) {
        if (ksys::act::isPlayerProfile(mTerrorEmitter_d)) {
            ksys::act::acc::PlayerBase player;
            if (ksys::act::acquireActor(&act::PlayerInfo::instance()->getPlayerLink(), &player)) {
                if (player.x_30() || player.m181())
                    sub_7100712388(mActor, player, "TerrorSword");
                else if (player.m180())
                    sub_7100712388(mActor, player, "TerrorArrow");
            }
        } else if (ksys::act::hasTag(mTerrorEmitter_d, 0xffb4932f)) {
            ksys::act::ActorLinkConstDataAccess emitter;
            if (mTerrorEmitter_d) {
                ksys::act::acquireActor(mTerrorEmitter_d, &emitter);
                sub_7100712388(mActor, emitter, "TerrorBomb");
            }
        }
    }

    if (!*mIsSitting_d && !_74) {
        const auto& mtx = mActor->getMtx();
        sead::Vector3f dir(mTargetPos_d->x - mtx(0, 3), 0.0f, mTargetPos_d->z - mtx(2, 3));
        dir.normalize();
        const sead::Vector3f front = mtx.getBase(2);
        sead::Vector3f cross;
        cross.setCross(front, dir);
        if (std::atan2(cross.length(), front.dot(dir)) >= sead::Mathf::deg2rad(5.0f)) {
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(*mTargetPos_d, "TargetPos", -1);
            auto* damage_mgr = sead::DynamicCast<act::DamageManagerBase>(mActor->getDamageMgr());
            if (damage_mgr && damage_mgr->getField54() == 0xf) {
                _76 = true;
                changeChild("反応する", &pack);
            } else {
                changeChild("気付く", &pack);
            }
            return;
        }
    }

    ksys::act::ai::InlineParamPack pack;
    pack.addBool(false, "TerrorOccurring", -1);
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    changeChild("警戒", &pack);
}

void NPCAlert::loadParams_() {
    getStaticParam(&mMinReactionTime_s, "MinReactionTime");
    getStaticParam(&mReleaseDist_s, "ReleaseDist");
    getDynamicParam(&mTerrorLevel_d, "TerrorLevel");
    getDynamicParam(&mIsTimeOver_d, "IsTimeOver");
    getDynamicParam(&mIsSitting_d, "IsSitting");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mTerrorEmitter_d, "TerrorEmitter");
}

}  // namespace uking::ai
