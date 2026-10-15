#include "Game/Actor/AI/aiWizzrobeRoam.h"
#include "random/seadGlobalRandom.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/Actor/aiUnk_7102431fa8.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Physics/System/physRayCastBodyQuery.h"

namespace uking::ai {

WizzrobeRoam::WizzrobeRoam(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WizzrobeRoam::~WizzrobeRoam() = default;

bool WizzrobeRoam::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

// NON_MATCHING: scheduling (the original subtracts the central height before scaling the offset and loads
// MexHeightLevel after the division)
void WizzrobeRoam::enter_(ksys::act::ai::InlineParamPack* params) {
    mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_2000000);
    mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_1000000);
    auto* unit = sead::DynamicCast<Unk_7102431fa8>(*static_cast<Unk_71025afb58**>(mWizzrobeMagicWeatherUnit_a));
    if (unit && unit->_10)
        unit->sub_7100741E14();

    s32 level;
    const f32 offset = *mHeightOffset_s;
    if (offset == 0.0f) {
        level = 0;
    } else {
        level = s32((offset * 0.5f + (mActor->getMtx().getTranslation().y - mCentralPos_d->y)) / offset);
        const s32 max_level = *mMexHeightLevel_s;
        if (level > max_level)
            level = max_level;
    }
    _88 = level;
    _8c = 0;

    s32 count = *mMoveCountMin_s;
    if (count < 1) {
        count = 1;
    } else if (count < *mMoveCountMax_s) {
        count = sead::GlobalRandom::instance()->getS32Range(count, *mMoveCountMax_s + 1);
    }
    _90 = count;
    sub_71005FE5CC();
}

void WizzrobeRoam::leave_() {
    ksys::act::ai::Ai::leave_();
}

void WizzrobeRoam::loadParams_() {
    getStaticParam(&mMoveCountMin_s, "MoveCountMin");
    getStaticParam(&mMoveCountMax_s, "MoveCountMax");
    getStaticParam(&mChangeHeightPer_s, "ChangeHeightPer");
    getStaticParam(&mMexHeightLevel_s, "MexHeightLevel");
    getStaticParam(&mTerritoryRadius_s, "TerritoryRadius");
    getStaticParam(&mTerritoryRadiusRnd_s, "TerritoryRadiusRnd");
    getStaticParam(&mRetryLength_s, "RetryLength");
    getStaticParam(&mHeightOffset_s, "HeightOffset");
    getDynamicParam(&mCentralPos_d, "CentralPos");
    getAITreeVariable(&mWizzrobeMagicWeatherUnit_a, "WizzrobeMagicWeatherUnit");
}

// NON_MATCHING: vector snapshots, ray argument scheduling and return registers differ.
sead::Vector3f WizzrobeRoam::sub_71005FEB18() {
    const sead::Vector3f actor_position = mActor->getMtx().getTranslation();
    const sead::Vector3f ray_start{actor_position.x, actor_position.y + 0.1f, actor_position.z};
    const f32 angle = static_cast<f32>(sead::GlobalRandom::instance()->getS32Range(0, 360)) /
                      360.0f * (2.0f * sead::Mathf::pi());
    const f32 base_radius = *mTerritoryRadius_s;
    const f32 random_radius = *mTerritoryRadiusRnd_s;
    const f32 radius = base_radius + sead::GlobalRandom::instance()->getF32Range(0.0f, random_radius);
    sead::Vector3f target;
    target.x = mCentralPos_d->x + cosf(angle) * radius;
    target.z = mCentralPos_d->z + sinf(angle) * radius;
    target.y = mCentralPos_d->y + static_cast<f32>(_88) * *mHeightOffset_s;
    sead::Vector3f hit;
    if (sub_71005FEDB4(ray_start, target, &hit))
        target = hit;
    if (sead::Vector2f{target.x - mActor->getMtx().getTranslation().x,
                       target.z - mActor->getMtx().getTranslation().z}.length() < *mRetryLength_s) {
        target.x = radius * cosf(angle + sead::Mathf::pi()) + mCentralPos_d->x;
        target.z = radius * sinf(angle + sead::Mathf::pi()) + mCentralPos_d->z;
        target.y = mCentralPos_d->y + static_cast<f32>(_88) * *mHeightOffset_s;
        if (sub_71005FEDB4(ray_start, target, &hit))
            target = hit;
        if (sead::Vector2f{target.x - mActor->getMtx().getTranslation().x,
                           target.z - mActor->getMtx().getTranslation().z}.length() < *mRetryLength_s)
            return mActor->getMtx().getTranslation();
    }
    return target;
}

// 0x71005fedb4
bool WizzrobeRoam::sub_71005FEDB4(sead::Vector3f start, sead::Vector3f end, sead::Vector3f* hit_pos) {
    ksys::phys::RayCastBodyQuery query(sub_710072E804(mActor, 0), ksys::phys::GroundHit::HitAll);
    query.enableLayer(ksys::phys::ContactLayer::EntityGround);
    query.enableLayer(ksys::phys::ContactLayer::EntityGroundRough);
    query.enableLayer(ksys::phys::ContactLayer::EntityGroundObject);
    query.enableLayer(ksys::phys::ContactLayer::EntityObject);
    query.enableLayer(ksys::phys::ContactLayer::EntityTree);
    query.setStartAndEnd(start, end);
    query.setNormalCheckingMode(ksys::phys::RayCast::NormalCheckingMode::_0);
    if (!query.worldRayCast(ksys::phys::ContactLayerType::Entity))
        return false;
    if (hit_pos)
        query.getHitPosition(hit_pos);
    return true;
}

// 0x71005fe85c
void WizzrobeRoam::sub_71005FE85C() {
    s32 level = _88;
    const s32 max_level = *mMexHeightLevel_s;
    if (max_level >= 1) {
        if (level == 0) {
            level = 1;
        } else if (level == max_level) {
            level -= 1;
        } else if (s32(sead::GlobalRandom::instance()->getU32()) >= 0) {
            level -= 1;
        } else {
            level += 1;
        }
    }
    sead::Vector3f pos = mActor->getMtx().getTranslation();
    pos.y = mCentralPos_d->y + f32(level) * *mHeightOffset_s;
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("高度変化", &pack);
}

// 0x71005fe5cc
void WizzrobeRoam::sub_71005FE5CC() {
    ++_8c;
    const sead::Vector3f pos = sub_71005FEB18();
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("移動", &pack);
}

// NON_MATCHING: the original duplicates the move-count computation per path (the GlobalRandom address stays in a callee-saved
// register from the height-change roll) and schedules the float loads / the height clamp differently.
// 0x71005fe6b0
void WizzrobeRoam::calc_() {
    auto* child = getCurrentChild();
    if (!child->isFinished() && !child->isFailed())
        return;

    if (isCurrentChild("移動")) {
        if (_8c < _90) {
            sub_71005FE5CC();
            return;
        }
        const s32 change_height_per = *mChangeHeightPer_s;
        if (s32(sead::GlobalRandom::instance()->getU32(100)) < change_height_per) {
            sub_71005FE85C();
            return;
        }
        _8c = 0;
    } else {
        s32 level;
        const f32 offset = *mHeightOffset_s;
        if (offset == 0.0f) {
            level = 0;
        } else {
            level = s32((offset * 0.5f + (mActor->getMtx().getTranslation().y - mCentralPos_d->y)) / offset);
            level = sead::Mathi::min(level, *mMexHeightLevel_s);
        }
        _88 = level;
        _8c = 0;
    }

    s32 count = *mMoveCountMin_s;
    if (count < 1) {
        count = 1;
    } else if (count < *mMoveCountMax_s) {
        count = sead::GlobalRandom::instance()->getS32Range(count, *mMoveCountMax_s + 1);
    }
    _90 = count;
    sub_71005FE5CC();
}

}  // namespace uking::ai
