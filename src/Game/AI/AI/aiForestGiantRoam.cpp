#include "Game/AI/AI/aiForestGiantRoam.h"
#include <prim/seadRuntimeTypeInfo.h>
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"

namespace uking::ai {

ForestGiantRoam::ForestGiantRoam(const InitArg& arg) : BokoblinRoam(arg) {}

ForestGiantRoam::~ForestGiantRoam() = default;

bool ForestGiantRoam::init_(sead::Heap* heap) {
    return BokoblinRoam::init_(heap);
}

// NON_MATCHING: scheduling of the loads for the squared XZ distance (the original loads the
// mReturnHomeDist_s pointer before the first subtraction)
void ForestGiantRoam::enter_(ksys::act::ai::InlineParamPack* params) {
    BokoblinRoam::enter_(params);
    _e8 = false;
    auto* actor = mActor;
    if (!sead::IsDerivedFrom<act::Enemy>(actor))
        return;

    auto* holder = static_cast<act::Enemy*>(actor)->_12d0;
    if (!holder)
        return;

    holder->_8 = -1;
    if (holder->_0)
        holder->_0->inlineReset();

    if (isRootAiParamINot5() || _e8)
        return;

    const f32 dx = mActor->getMtx().m[0][3] - mCentralPos_d->x;
    const f32 dz = mActor->getMtx().m[2][3] - mCentralPos_d->z;
    if (dx * dx + dz * dz >= *mReturnHomeDist_s * *mReturnHomeDist_s) {
        if (holder->_0) {
            holder->_0->sub_7100F75F8C(*mCentralPos_d);
            holder->_8 = 0;
        }
        _e8 = true;
    }
}

void ForestGiantRoam::leave_() {
    BokoblinRoam::leave_();
}

void ForestGiantRoam::loadParams_() {
    BokoblinRoam::loadParams_();
    getStaticParam(&mReturnHomeDist_s, "ReturnHomeDist");
}

}  // namespace uking::ai
