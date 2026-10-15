#include "Game/Actor/AI/aiSwimEnemyFindPlayer.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include <math/seadMathCalcCommon.h>
#include <cmath>
#include "KingSystem/System/Timer.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/aiUnk_71007320F0.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "Game/gameStatisticsMgr.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "Game/Actor/Player/actPlayerBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"

namespace uking::ai {

SwimEnemyFindPlayer::SwimEnemyFindPlayer(const InitArg& arg) : EnemyBaseFindPlayer(arg) {}

SwimEnemyFindPlayer::~SwimEnemyFindPlayer() = default;

bool SwimEnemyFindPlayer::init_(sead::Heap* heap) {
    return EnemyBaseFindPlayer::init_(heap);
}

void SwimEnemyFindPlayer::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyBaseFindPlayer::enter_(params);
}

// NON_MATCHING: shared transition tails and child-state branch layout differ.
void SwimEnemyFindPlayer::calc_() {
    auto* child = getCurrentChild();
    if (isCurrentChild("対象見張り台")) {
        if (child->isFinished() || child->isFailed()) {
            if (sub_710037EEAC()) {
                setFailed();
                return;
            }
            if (m35()) {
                m40();
                return;
            }
            if (*mNearScaffoldDist_s > 0.0f && sub_71005D9744(mActor) == 3) {
                sub_710037EDA4();
                return;
            }
        } else {
            if (!child->isChangeable())
                return;
            m44();
            if (*mNearScaffoldDist_s > 0.0f && sub_71005D9744(mActor) == 3)
                return;
        }
    } else if (isCurrentChild("対象壁つかまり")) {
        if (child->isFinished() || child->isFailed()) {
            if (sub_710037EEAC()) {
                setFailed();
                return;
            }
            if (m35()) {
                m40();
                return;
            }
            if (sub_71005B3F30()) {
                _170 = 15.0f;
                sub_710037EDA4();
                return;
            }
            ksys::Timer::update(&_170, -1.0f);
            if (!(_170 >= 0.0f))
                _170 = 0.0f;
            if (_170 > 0.0f) {
                sub_710037EDA4();
                return;
            }
        } else {
            if (!child->isChangeable())
                return;
            m44();
            if (sub_71005B3F30()) {
                _170 = 15.0f;
                return;
            }
            ksys::Timer::update(&_170, -1.0f);
            if (!(_170 >= 0.0f))
                _170 = 0.0f;
            if (_170 > 0.0f)
                return;
        }
    } else {
        EnemyBaseFindPlayer::calc_();
        return;
    }
    if (sub_710037EEAC())
        setFailed();
    else if (m35())
        m40();
    else
        sub_710037EDA4();
}

void SwimEnemyFindPlayer::leave_() {
    EnemyBaseFindPlayer::leave_();
}

void SwimEnemyFindPlayer::loadParams_() {
    EnemyBaseFindPlayer::loadParams_();
    getStaticParam(&mIsAbleToLand_s, "IsAbleToLand");
    getStaticParam(&mNearScaffoldDist_s, "NearScaffoldDist");
    getStaticParam(&mClimbVmin_s, "ClimbVmin");
    getStaticParam(&mClimbVmax_s, "ClimbVmax");
    getStaticParam(&mClimbHmax_s, "ClimbHmax");
}

bool SwimEnemyFindPlayer::m35() {
    auto* actor = mActor;
    if (!actor)
        return false;
    return sub_710072E0A0(actor, sub_71005D9330(actor), actor->getMtx(),
                          *mAttackRange_s + sub_71007320F0(actor, *mWeaponIdx_s), *mAttackVMin_s,
                          *mAttackVMax_s, sead::Mathf::pi(), 0.8f, 1.2f);
}

bool SwimEnemyFindPlayer::m36(bool b) {
    if (!*mIsAbleToLand_s) {
        if (auto* link = sub_71005D9050(mActor)) {
            ksys::act::ActorLinkConstDataAccess accessor;
            ksys::act::acquireActor(link, &accessor);
            if (accessor.sub_7100D110E4() <= 0.0f)
                return false;
        }
    }
    return sub_710072F8E4(mActor, sub_71005D9330(mActor), nullptr, 3.0f);
}

bool SwimEnemyFindPlayer::m37() {
    const sead::Vector3f& target = sub_71005D98D8(mActor);
    if (!*mIsAbleToLand_s) {
        if (auto* mgr = StatisticsMgr::instance()) {
            f32 depth = 0.0f;
            mgr->query(&depth, 1, mgr->getStatsPointer("water_depth"), &target);
            if (depth <= 0.0f)
                return false;
        }
    }
    return sub_710072F8E4(mActor, target, nullptr, 3.0f);
}

bool SwimEnemyFindPlayer::m38() {
    if (!mActor)
        return false;
    auto* nav = mActor->m45();
    if (nav && nav->_1d8 == 13 && (nav->_2a4 & 0xffff) == 7)
        return false;
    return EnemyBaseFindPlayer::m38();
}

// 0x71005b4054
void SwimEnemyFindPlayer::sub_71005B4054() {
    _170 = 15.0f;
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    changeChild("対象壁つかまり", &pack);
}

// NON_MATCHING: same logic; the original keeps the early-out branches separate (b.mi / b.lt / b.hi to one `mov w19, 0` block
// and `orr w19, 1` for the final compare instead of cset) and schedules the matrix loads differently
// 0x71005b3f30
bool SwimEnemyFindPlayer::sub_71005B3F30() {
    bool result = false;
    if (!(*mClimbHmax_s < 0.0f)) {
        auto& link = sub_71005D94AC(mActor);
        if (link.hasProc() && ksys::act::isPlayerProfile(&link)) {
            ksys::act::acc::PlayerBase player;
            ksys::act::acquireActor(&link, &player);
            if (player.m186() || player.m187()) {
                const sead::Matrix34f& mtx = player.getActorMtx();
                const sead::Matrix34f& actor_mtx = mActor->getMtx();
                const f32 dy = mtx(1, 3) - actor_mtx(1, 3);
                if (!(dy < *mClimbVmin_s) && !(dy > *mClimbVmax_s)) {
                    const f32 dx = mtx(0, 3) - actor_mtx(0, 3);
                    const f32 dz = mtx(2, 3) - actor_mtx(2, 3);
                    if (sead::Mathf::sqrt(dx * dx + dz * dz) <= *mClimbHmax_s)
                        result = true;
                }
            }
        }
    }
    return result;
}


bool SwimEnemyFindPlayer::m48() {
    if (!(*mNearScaffoldDist_s <= 0.0f)) {
        auto* actor = mActor;
        if (sub_71005D9744(actor) == 3) {
            const sead::Vector3f& target = sub_71005D9330(actor);
            const sead::Vector2f target_xz(target.x, target.z);
            const sead::Vector2f pos_xz(actor->getMtx()(0, 3), actor->getMtx()(2, 3));
            if ((target_xz - pos_xz).length() <= *mNearScaffoldDist_s) {
                ksys::act::ai::InlineParamPack pack;
                pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
                changeChild("対象見張り台", &pack);
                return true;
            }
        }
    }
    if (sub_71005B3F30()) {
        sub_71005B4054();
        return true;
    }
    return false;
}

bool SwimEnemyFindPlayer::m49() {
    if (!(*mNearScaffoldDist_s <= 0.0f)) {
        auto* actor = mActor;
        if (sub_71005D9744(actor) == 3) {
            const sead::Vector3f& target = sub_71005D9330(actor);
            const sead::Vector2f target_xz(target.x, target.z);
            const sead::Vector2f pos_xz(actor->getMtx()(0, 3), actor->getMtx()(2, 3));
            if ((target_xz - pos_xz).length() <= *mNearScaffoldDist_s) {
                ksys::act::ai::InlineParamPack pack;
                pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
                changeChild("対象見張り台", &pack);
                return true;
            }
        }
    }
    if (sub_71005B3F30()) {
        sub_71005B4054();
        return true;
    }
    return false;
}

bool SwimEnemyFindPlayer::m51() {
    if (!(*mNearScaffoldDist_s <= 0.0f)) {
        auto* actor = mActor;
        if (sub_71005D9744(actor) == 3) {
            const sead::Vector3f& target = sub_71005D9330(actor);
            const sead::Vector2f target_xz(target.x, target.z);
            const sead::Vector2f pos_xz(actor->getMtx()(0, 3), actor->getMtx()(2, 3));
            if ((target_xz - pos_xz).length() <= *mNearScaffoldDist_s) {
                ksys::act::ai::InlineParamPack pack;
                pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
                changeChild("対象見張り台", &pack);
                return true;
            }
        }
    }
    if (sub_71005B3F30()) {
        sub_71005B4054();
        return true;
    }
    if (m38()) {
        changeToNoNavMesh();
        return true;
    }
    return false;
}

bool SwimEnemyFindPlayer::m52() {
    if (!(*mNearScaffoldDist_s <= 0.0f)) {
        auto* actor = mActor;
        if (sub_71005D9744(actor) == 3) {
            const sead::Vector3f& target = sub_71005D9330(actor);
            const sead::Vector2f target_xz(target.x, target.z);
            const sead::Vector2f pos_xz(actor->getMtx()(0, 3), actor->getMtx()(2, 3));
            if ((target_xz - pos_xz).length() <= *mNearScaffoldDist_s) {
                ksys::act::ai::InlineParamPack pack;
                pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
                changeChild("対象見張り台", &pack);
                return true;
            }
        }
    }
    if (sub_71005B3F30()) {
        sub_71005B4054();
        return true;
    }
    return false;
}

}  // namespace uking::ai
