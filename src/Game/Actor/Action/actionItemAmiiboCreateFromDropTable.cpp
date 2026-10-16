#include "Game/Actor/Action/actionItemAmiiboCreateFromDropTable.h"
#include <random/seadGlobalRandom.h>
#include "KingSystem/Physics/RigidBody/Shape/physBoxShape.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBodyBox.h"

namespace uking::action {

ItemAmiiboCreateFromDropTable::ItemAmiiboCreateFromDropTable(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ItemAmiiboCreateFromDropTable::~ItemAmiiboCreateFromDropTable() = default;

// NON_MATCHING: parameter initialization and store scheduling.
bool ItemAmiiboCreateFromDropTable::init_(sead::Heap* heap) {
    ksys::phys::BoxParam param;
    param.center_of_mass = {0.0f, 0.0f, 0.0f};
    param.toi = true;
    param.translate = {0.0f, -0.52f, 0.0f};
    param.extents = {1.5f, 1.0f, 1.5f};
    param.motion_type = ksys::phys::MotionType::Fixed;
    param.mass = 10.0f;
    param.contact_layer = ksys::phys::ContactLayer::EntityGround;
    param.groundhit = ksys::phys::GroundHit::HitAll;
    param.common.material = ksys::phys::Material::AirWall;
    param.no_hit_ground = true;
    _a80 = ksys::phys::BoxRigidBody::make(&param, heap);
    return _a80 != nullptr;
}

void ItemAmiiboCreateFromDropTable::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ItemAmiiboCreateFromDropTable::leave_() {
    if (!_a8d)
        _a80->removeFromWorldAndResetLinks();
}

void ItemAmiiboCreateFromDropTable::loadParams_() {
    getStaticParam(&mCreateInterval_s, "CreateInterval");
    getStaticParam(&mClearSealNum_s, "ClearSealNum");
    getStaticParam(&mHitRateAdjustStart_s, "HitRateAdjustStart");
    getStaticParam(&mHitRateAdjustEnd_s, "HitRateAdjustEnd");
    getStaticParam(&mCreateArea_s, "CreateArea");
    getStaticParam(&mBigHitRate1st_s, "BigHitRate1st");
    getStaticParam(&mBigHitRate2nd_s, "BigHitRate2nd");
    getStaticParam(&mBigHitRate3rd_s, "BigHitRate3rd");
    getStaticParam(&mGreatHitRate1st_s, "GreatHitRate1st");
    getStaticParam(&mGreatHitRate2nd_s, "GreatHitRate2nd");
    getStaticParam(&mGreatHitRate3rd_s, "GreatHitRate3rd");
    getStaticParam(&mDropNumRate1st_s, "DropNumRate1st");
    getStaticParam(&mDropNumRate2nd_s, "DropNumRate2nd");
    getStaticParam(&mDropNumRate3rd_s, "DropNumRate3rd");
    getStaticParam(&mSmallHitRate1st_s, "SmallHitRate1st");
    getStaticParam(&mSmallHitRate2nd_s, "SmallHitRate2nd");
    getStaticParam(&mSmallHitRate3rd_s, "SmallHitRate3rd");
    getStaticParam(&mPairActor_0_s, "PairActor_0");
    getStaticParam(&mPairActor_1_s, "PairActor_1");
    getStaticParam(&mPairActor_2_s, "PairActor_2");
    getStaticParam(&mFlagActor_0_s, "FlagActor_0");
    getStaticParam(&mFlagActor_1_s, "FlagActor_1");
    getStaticParam(&mFlagActor_2_s, "FlagActor_2");
    getStaticParam(&mNotFlagActor_0_s, "NotFlagActor_0");
    getStaticParam(&mNotFlagActor_1_s, "NotFlagActor_1");
    getStaticParam(&mCreateOffset_s, "CreateOffset");
    parsePairActor(&mPairActors[0], mPairActor_0_s);
    parsePairActor(&mPairActors[1], mPairActor_1_s);
    parsePairActor(&mPairActors[2], mPairActor_2_s);
    parseFlagActor(&mFlagActors[0], mFlagActor_0_s);
    parseFlagActor(&mFlagActors[1], mFlagActor_1_s);
    parseFlagActor(&mFlagActors[2], mFlagActor_2_s);
    parseFlagActor(&mFlagActors[3], mNotFlagActor_0_s);
    parseFlagActor(&mFlagActors[4], mNotFlagActor_1_s);
}

void ItemAmiiboCreateFromDropTable::parsePairActor(PairActor* out, const sead::SafeString& names) {
    s32 i = 0;
    auto it = names.tokenBegin(",");
    const auto end = names.tokenEnd(",");
    for (; end != it; ++it, ++i) {
        sead::FixedSafeString<64> token;
        it.get(&token);
        if (i == 0)
            out->first = token;
        else if (i == 1)
            out->second = token;
    }
}

void ItemAmiiboCreateFromDropTable::parseFlagActor(FlagActor* out, const sead::SafeString& names) {
    s32 i = 0;
    auto it = names.tokenBegin(",");
    const auto end = names.tokenEnd(",");
    for (; end != it; ++it, ++i) {
        if (i == 0) {
            sead::FixedSafeString<128> token;
            it.get(&token);
            out->actor = token;
        } else if (i == 1) {
            sead::FixedSafeString<64> token;
            it.get(&token);
            out->flag = token;
        }
    }
}

void ItemAmiiboCreateFromDropTable::calc_() {
    ksys::act::ai::Action::calc_();
}

// NON_MATCHING: register allocation of the three previous offsets
void ItemAmiiboCreateFromDropTable::sub_71001BBDEC() {
    sead::Vector2f prev1 = sead::Vector2f::zero;
    sead::Vector2f prev2 = sead::Vector2f::zero;
    sead::Vector2f prev3 = sead::Vector2f::zero;
    for (s32 i = 0; i < 50; ++i) {
        sead::Vector2f pos;
        for (s32 tries = 0; tries < 100; ++tries) {
            pos.x = sead::GlobalRandom::instance()->getF32Range(-1.0f, 1.0f);
            pos.y = sead::GlobalRandom::instance()->getF32Range(-1.0f, 1.0f);
            if ((pos - prev1).squaredLength() > 0.25f && (pos - prev2).squaredLength() > 0.25f &&
                (pos - prev3).squaredLength() > 0.25f) {
                break;
            }
        }
        _8d0[i] = pos;
        prev3 = prev2;
        prev2 = prev1;
        prev1 = pos;
    }
    _a60 = false;
}

}  // namespace uking::action
