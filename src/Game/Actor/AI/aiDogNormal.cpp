#include "Game/Actor/AI/aiDogNormal.h"
#include <random/seadGlobalRandom.h>
#include <cmath>
#include "Game/Actor/aiUnk_7100742478.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/aiRootAi.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "Game/Actor/Player/actPlayerInfo.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapObjectLink.h"

namespace uking::ai {

DogNormal::DogNormal(const InitArg& arg) : DomesticNormal(arg) {}

DogNormal::~DogNormal() = default;

bool DogNormal::init_(sead::Heap* heap) {
    if (!DomesticNormal::init_(heap))
        return false;

    auto* object = mActor->getMapObject();
    if (!object)
        return true;
    auto* link_data = object->getLinkData();
    if (!link_data || link_data->mLinksOther.links.size() < 1)
        return true;
    auto* other = link_data->mLinksOther.links(0).other_obj;
    if (!other)
        return true;
    link_data = other->getLinkData();
    if (!link_data || link_data->mLinksOther.links.size() < 1)
        return true;
    auto* target = link_data->mLinksOther.links(0).other_obj;
    if (!target)
        return true;

    if (target->isRevivalGameDataFlagOn())
        return true;

    _464.setBit(Flag(Flag::_0));
    const sead::Vector3f translate = target->getTranslate();
    _44c = translate;
    _458 = target->getRotate().y;
    return true;
}

void DogNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    DomesticNormal::enter_(params);
    _428.previous_value = _428.value = *mFriendTickRate_s;
}

void DogNormal::leave_() {
    DomesticNormal::leave_();
}

// NON_MATCHING: same flow, but the flag updates (enum stack round trips, `friendly` kept in a register and the
// set / reset arms) are laid out differently
void DogNormal::sub_7100364460() {
    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    const f32 dx = _440.x - pos.x;
    const f32 dz = _440.z - pos.z;
    if (dx * dx + dz * dz > *mFoodFriendDist_s * *mFoodFriendDist_s)
        return;

    if (_464.isOnBit(Flag(Flag::_1))) {
        bool friendly = false;
        if (auto* object = mActor->getMapObject()) {
            if (auto* link_data = object->getLinkData()) {
                if (link_data->mLinksOther.links.size() >= 1) {
                    if (auto* other = link_data->mLinksOther.links(0).other_obj) {
                        if (auto* second = other->getLinkData()) {
                            if (second->mLinksOther.links.size() >= 1) {
                                if (auto* target = second->mLinksOther.links(0).other_obj)
                                    friendly = !target->isRevivalGameDataFlagOn();
                            }
                        }
                    }
                }
            }
        }
        if (friendly)
            _464.setBit(Flag(Flag::_0));
        else
            _464.resetBit(Flag(Flag::_0));
        if (_464.isOnBit(Flag(Flag::_0))) {
            const s32 next = s32(_460) + 1;
            const f32 count = next < 0 ? 0.0f : sead::Mathf::min(f32(next), f32(*mNumFriendlyFoodForLeadTreasure_s));
            _460 = s32(count);
            if (s32(_460) < *mNumFriendlyFoodForLeadTreasure_s)
                changeToFriendly();
            else
                sub_7100364610();
        }
    }
    _45c = sead::Mathf::clamp(*mFoodFriendRate_s + _45c, 0.0f, 100.0f);
}

// Starts leading the player to the treasure (child 宝まで誘導): the target is a point next to the treasure.
void DogNormal::sub_7100364610() {
    sub_7100500B50(false, false, false);
    mActor->emitBasicSigOn();
    _464.setBit(Flag(Flag::_4));
    _464.setBit(Flag(Flag::_2));
    _460 = 0;

    const sead::Vector3f side = sead::Vector3f::ex;
    sead::Matrix34f rot;
    rot.makeR({0.0f, _458, 0.0f});
    sead::Vector3f dir;
    dir.setRotated(rot, side);
    dir.normalize();

    sead::Vector3f target = _44c;
    const s32 sign = (sead::GlobalRandom::instance()->getU32() & 2) - 1;
    target.setScaleAdd(f32(sign) * 2.5f, dir, target);

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(target, "TargetPos", -1);
    pack.addActor(uking::act::PlayerInfo::getSomeProcLink(), "LeaderActor", -1);
    changeChild("宝まで誘導", &pack);
}

void DogNormal::changeToFriendly() {
    sub_7100500B50(false, false, false);
    ksys::act::ai::InlineParamPack pack;
    pack.addActor(uking::act::PlayerInfo::getSomeProcLink(), "TargetActor", -1);
    pack.addFloat(0.0f, "DistanceKept", -1);
    changeChild("なつき", &pack);
    _464.setBit(Flag(Flag::_4));
}

bool DogNormal::sub_7100364170() {
    return !(isCurrentChild("宝まで誘導") || isCurrentChild("興味対象発見") || isCurrentChild("帰還") ||
             isCurrentChild("ふり向き") || isCurrentChild("逃走") || isCurrentChild("ダメージ逃走"));
}

void DogNormal::changeToTurn(const sead::Vector3f* pos, const sead::Vector3f* dir) {
    sub_7100500B50(false, false, false);
    ksys::act::ai::InlineParamPack pack;
    sead::Vector3f target = *pos;
    target.setScaleAdd(20.0f, *dir, target);
    pack.addVec3(target, "TargetPos", -1);
    changeChild("ふり向き", &pack);
}

bool DogNormal::m40() {
    return (isCurrentChild("徘徊") || isCurrentChild("なつき")) && _464.isOffBit(Flag(Flag::_4));
}

bool DogNormal::m41() {
    if (isCurrentChild("興味対象発見") && getCurrentChild()->isFinished()) {
        sub_7100364460();
        if (_464.isOnBit(Flag(Flag::_4)))
            return true;
    }
    return PreyNormal::m41();
}

bool DogNormal::m44() {
    return DomesticNormal::m44() || isCurrentChild("宝まで誘導") || isCurrentChild("なつき") ||
           isCurrentChild("ふり向き");
}

// NON_MATCHING: the Wait string comparison, vector copies and shared cleanup branches differ.
void DogNormal::calc_() {
    ksys::act::ActorLinkConstDataAccess accessor;
    if (!ksys::act::acquireActor(&act::PlayerInfo::getSomeProcLink(), &accessor) ||
        (accessor.sub_7100D12E64() &&
         !ksys::act::acquireActor(&act::PlayerInfo::instance()->getHorseLink(), &accessor))) {
        setFailed();
        return;
    }
    _434 = _440;
    _440 = accessor.getActorMtx().getTranslation();
    bool wait_event = false;
    if (!testRootAiFlag2(ksys::act::ai::RootAiFlag2::_0)) {
        auto* as_list = mActor->getASList();
        if (as_list->x_1(0, 0) == "Wait") {
            wait_event = as_list->x(22, nullptr, 0, 0,
                                    &ksys::as::ASList::Unk2::sub_71011638DC, true);
        }
    }
    if (wait_event)
        _464.setBit(Flag(Flag::_5));
    else
        _464.resetBit(Flag(Flag::_5));
    if (_464.isOnBit(Flag(Flag::_5))) {
        sub_7100363C94();
        return;
    }

    DomesticNormal::calc_();
    mActor->getASList()->x_6(16, 0, _45c);
    auto* child = getCurrentChild();
    if (isFinished() || isFailed() || !child)
        return;
    if (child->isFinishedOrFailed()) {
        if (isCurrentChild("宝まで誘導")) {
            // Native repeats and discards this failure query after the finished/failed test.
            child->isFailed();
            _45c = 0;
        } else if (isCurrentChild("なつき")) {
            child->isFailed();
            _45c = sead::Mathf::clamp(_45c - 100.0f, 0.0f, 100.0f);
        } else if (isCurrentChild("ふり向き")) {
            if (_464.isOnBit(Flag(Flag::_1))) {
                changeToFriendly();
                return;
            }
        } else {
            return;
        }
        sub_71004FCA60();
        return;
    }

    _464.resetBit(Flag(Flag::_4));
    sub_7100363C94();
    if (isCurrentChild("なつき")) {
        if (_464.isOffBit(Flag(Flag::_1)))
            sub_71004FCA60();
    } else if (sub_7100364170() && child->isChangeable() &&
               _464.isOnBit(Flag(Flag::_1)) && _464.isOffBit(Flag(Flag::_4))) {
        changeToFriendly();
    }
    if (!(isCurrentChild("徘徊") && _45c >= 25.0f) && !isCurrentChild("なつき"))
        return;
    const auto pos = mActor->getMtx().getTranslation();
    auto direction = _440 - pos;
    const auto forward = mActor->getMtx().getBase(2);
    direction.normalize();
    const f32 dx = _440.x - pos.x;
    const f32 dz = _440.z - pos.z;
    if (dx * dx + dz * dz >= 9.0f && forward.dot(direction) <= cosf(*mAngleTurnToPlayer_s)) {
        changeToTurn(&_440, &accessor.getVelocity());
        _464.setBit(Flag(Flag::_4));
    }
}

// NON_MATCHING: far-distance flag gating and home-distance loads are scheduled differently.
void DogNormal::sub_7100363C94() {
    if (sub_7100364170())
        _428.update();
    if (testRootAiFlag2(ksys::act::ai::RootAiFlag2::_0)) {
        _45c = sead::Mathf::clamp(_45c - 100.0f, 0.0f, 100.0f);
    } else if (_464.isOffBit(Flag(Flag::_6)) &&
               _428.value <= std::numeric_limits<f32>::epsilon()) {
        _428.previous_value = _428.value = *mFriendTickRate_s;
        const auto pos = mActor->getMtx().getTranslation();
        const f32 dx = _440.x - pos.x;
        const f32 dz = _440.z - pos.z;
        const f32 distance_sq = dx * dx + dz * dz;
        const f32 home_dx = _380.x - pos.x;
        const f32 home_dz = _380.z - pos.z;
        const f32 near_dist = *mNearFriendDist_s;
        const f32 max_follow_dist = *mMaxFollowDist_s;
        const f32 far_dist = _464.isOnBit(Flag(Flag::_1)) ? *mFarFriendFriendlyDist_s : *mFarFriendDist_s;
        if ((far_dist * far_dist <= distance_sq && _464.isOffBit(Flag(Flag::_5))) ||
            !sub_7100742278(2.0f, nullptr, mActor->m45(), &_440) ||
            !sub_7100742588(nullptr, mActor->m45(), &_440, 10.0f)) {
            _45c = sead::Mathf::clamp(_45c - 100.0f, 0.0f, 100.0f);
        } else if (max_follow_dist * max_follow_dist <= home_dx * home_dx + home_dz * home_dz &&
                   *mMaxFollowFriendDecayRate_s > 0) {
            _45c = sead::Mathf::clamp(_45c - *mMaxFollowFriendDecayRate_s, 0.0f, 100.0f);
        } else {
            const f32 moved_x = _440.x - _434.x;
            const f32 moved_z = _440.z - _434.z;
            if (moved_x * moved_x + moved_z * moved_z <=
                    *mNoMoveThreshold_s * *mNoMoveThreshold_s &&
                *mNoMoveFriendDecayRate_s > 0) {
                _45c = sead::Mathf::clamp(_45c - *mNoMoveFriendDecayRate_s, 0.0f, 100.0f);
            } else if (distance_sq <= near_dist * near_dist && *mNearFriendRate_s > 0) {
                _45c = sead::Mathf::clamp(_45c + *mNearFriendRate_s, 0.0f, 100.0f);
            }
        }
    }
    if (_464.isOffBit(Flag(Flag::_1)) && _45c >= 100.0f) {
        _464.setBit(Flag(Flag::_1));
        _428.previous_value = _428.value = _428.value + *mFramesKeepMaxFriendly_s;
        xlinkSearchAndEmit(mActor, "Attached", 2, nullptr);
    }
    if (_464.isOnBit(Flag(Flag::_1)) && _45c <= 0) {
        _464.resetBit(Flag(Flag::_1));
        if (_464.isOffBit(Flag(Flag::_2)))
            mActor->emitBasicSigOff();
        _460 = 0;
    }
}

void DogNormal::loadParams_() {
    DomesticNormal::loadParams_();
    getStaticParam(&mNumFriendlyFoodForLeadTreasure_s, "NumFriendlyFoodForLeadTreasure");
    getStaticParam(&mMaxFollowDist_s, "MaxFollowDist");
    getStaticParam(&mMaxFollowFriendDecayRate_s, "MaxFollowFriendDecayRate");
    getStaticParam(&mFoodFriendRate_s, "FoodFriendRate");
    getStaticParam(&mFoodFriendDist_s, "FoodFriendDist");
    getStaticParam(&mNearFriendRate_s, "NearFriendRate");
    getStaticParam(&mNearFriendDist_s, "NearFriendDist");
    getStaticParam(&mFarFriendDecayRate_s, "FarFriendDecayRate");
    getStaticParam(&mFarFriendDist_s, "FarFriendDist");
    getStaticParam(&mFarFriendFriendlyDist_s, "FarFriendFriendlyDist");
    getStaticParam(&mAttackFriendDecayRate_s, "AttackFriendDecayRate");
    getStaticParam(&mFriendTickRate_s, "FriendTickRate");
    getStaticParam(&mNoMoveFriendDecayRate_s, "NoMoveFriendDecayRate");
    getStaticParam(&mNoMoveThreshold_s, "NoMoveThreshold");
    getStaticParam(&mFramesKeepMaxFriendly_s, "FramesKeepMaxFriendly");
    getStaticParam(&mFramesStayAfterLead_s, "FramesStayAfterLead");
    getStaticParam(&mAngleTurnToPlayer_s, "AngleTurnToPlayer");
}

}  // namespace uking::ai
