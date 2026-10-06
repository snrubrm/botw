#include "Game/AI/AI/aiOnCliffSurfaceSelect.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actAiRoot.h"
#include "KingSystem/Map/mapPlacementMgr.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/Physics/System/physRayCastBodyQuery.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::ai {

OnCliffSurfaceSelect::OnCliffSurfaceSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

OnCliffSurfaceSelect::~OnCliffSurfaceSelect() = default;

bool OnCliffSurfaceSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void OnCliffSurfaceSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    if (*mOnCliff_m && !testRootAiFlag2(ksys::act::ai::RootAiFlag2::_0) &&
        !testRootAiFlag2(ksys::act::ai::RootAiFlag2::_4) && mActor->getMtx()(1, 1) < 0.99f) {
        sead::Matrix34f home;
        mActor->getHomeMtx(&home);
        if (home(1, 1) < 0.99f) {
            sub_71004F277C(true);
            return;
        }
    }
    if (*mIsCliffFreeze_a) {
        sub_71004F296C();
    } else {
        auto* actor = mActor;
        sead::Matrix34f home;
        actor->getHomeMtx(&home);
        if (home(1, 1) < 0.99f) {
            ksys::util::sub_71011F00EC(&home, actor->getMtx().getBase(2), sead::Vector3f::ey,
                                     actor->getMtx().getTranslation(), false);
            actor->sub_71011C8B04(home);
        }
        changeChild("通常", nullptr);
    }
}

void OnCliffSurfaceSelect::calc_() {
    if (isCurrentChild("初期化待機")) {
        if (ksys::map::PlacementMgr::instance()->isStaticCompoundReady(
                    mActor->getMtx().getTranslation(), false))
            sub_71004F277C(false);
        return;
    }
    auto* child = getCurrentChild();
    if ((child->isFinished() || child->isFailed()) && isCurrentChild("解凍後")) {
        auto* actor = mActor;
        sead::Matrix34f home;
        actor->getHomeMtx(&home);
        if (home(1, 1) < 0.99f) {
            ksys::util::sub_71011F00EC(&home, actor->getMtx().getBase(2), sead::Vector3f::ey,
                                     actor->getMtx().getTranslation(), false);
            actor->sub_71011C8B04(home);
        }
        changeChild("通常", nullptr);
    }
}

// NON_MATCHING: only the stack slots of the by-value temporaries differ (frame layout)
// 0x71004f277c
void OnCliffSurfaceSelect::sub_71004F277C(bool flag) {
    auto* actor = mActor;
    sead::Matrix34f matrix;
    ksys::phys::RayCastBodyQuery query(nullptr, ksys::phys::GroundHit::HitAll);
    ksys::act::sub_7100EEACE8(&query);
    const auto& mtx = actor->getMtx();
    const sead::Vector3f start = mtx.getTranslation() + mtx.getBase(1);
    const sead::Vector3f displacement = -mtx.getBase(1);
    query.setStartAndDisplacementScaled(start, displacement, 8.0f);
    const char* child;
    if (query.worldRayCast(ksys::phys::ContactLayerType::Entity)) {
        sead::Vector3f hit_pos;
        query.getHitPosition(&hit_pos);
        ksys::util::sub_71011F00EC(&matrix, mtx.getBase(2), query.getHitNormalInline(), hit_pos,
                                 false);
        actor->sub_71011C8B04(matrix);
        actor->setMtx(matrix, false, true);
        ksys::act::sub_7100EE58C0(mActor, matrix);
        if (auto* physics = actor->getPhysics())
            physics->setMtxAndScale(matrix, false, false, actor->getScale().x);
        child = "壁張り付き";
    } else if (flag) {
        child = "初期化待機";
    } else {
        auto* home_actor = mActor;
        home_actor->getHomeMtx(&matrix);
        if (matrix(1, 1) < 0.99f) {
            ksys::util::sub_71011F00EC(&matrix, home_actor->getMtx().getBase(2),
                                     sead::Vector3f::ey, home_actor->getMtx().getTranslation(),
                                     false);
            home_actor->sub_71011C8B04(matrix);
        }
        child = "通常";
    }
    changeChild(child, nullptr);
}

// 0x71004f296c
void OnCliffSurfaceSelect::sub_71004F296C() {
    *mIsCliffFreeze_a = false;
    const auto& mtx = mActor->getMtx();
    sead::Vector3f target = mtx.getTranslation();
    target += mtx.getBase(1) * 5.0f;
    target.y -= 5.0f;
    ksys::act::ai::InlineParamPack params;
    params.addVec3(target, "TargetPos", -1);
    changeChild("解凍後", &params);
}

void OnCliffSurfaceSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void OnCliffSurfaceSelect::loadParams_() {
    getMapUnitParam(&mOnCliff_m, "OnCliff");
    getAITreeVariable(&mIsCliffFreeze_a, "IsCliffFreeze");
}

}  // namespace uking::ai
