#include "Game/AI/AI/aiGanonBeastMoveSelect.h"
#include <geom/seadGeometry.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapRail.h"

namespace uking::ai {

GanonBeastMoveSelect::GanonBeastMoveSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GanonBeastMoveSelect::~GanonBeastMoveSelect() = default;

bool GanonBeastMoveSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GanonBeastMoveSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    if (sub_71003E51DC())
        changeChild("移動");
    else
        changeChild("待機");
}

void GanonBeastMoveSelect::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (!isCurrentChild("移動") || *mIsMoveFinishEnd_s)
            setFinished();
        else
            changeChild("待機");
    } else {
        child->isChangeable();
    }
}

void GanonBeastMoveSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GanonBeastMoveSelect::loadParams_() {
    getStaticParam(&mDist_s, "Dist");
    getStaticParam(&mIsMoveFinishEnd_s, "IsMoveFinishEnd");
    getStaticParam(&mCentralPoint_s, "CentralPoint");
    getStaticParam(&mFrontOffset_s, "FrontOffset");
    getStaticParam(&mWallDist_s, "WallDist");
}

// NON_MATCHING: center-coordinate scheduling and shared false-return branches differ.
bool GanonBeastMoveSelect::sub_71003E51DC() {
    const auto& position = mActor->getMtx().getTranslation();
    sead::Vector3f outward(position.x - mCentralPoint_s->x, 0.0f,
                            position.z - mCentralPoint_s->z);
    outward.normalize();
    if (outward.dot(mActor->getMtx().getBase(2)) > 0.0f)
        return false;
    auto* object = mActor->getMapObject();
    if (!object || !object->getRails_0())
        return true;
    auto* rail = *object->getRails_0();
    if (!rail)
        return true;
    const s32 count = rail->getNumPoints();
    for (s32 i = 0; i < count; ++i) {
        const s32 next = i + 1 < count ? i + 1 : i + 1 - count;
        const auto first = rail->getPointTranslate(i);
        const auto second = rail->getPointTranslate(next);
        if (sub_71003E5500(&first, &second))
            return false;
    }
    return true;
}

// NON_MATCHING: projected-vector register allocation and the stack frame differ.
bool GanonBeastMoveSelect::sub_71003E5500(const sead::Vector3f* first,
                                        const sead::Vector3f* second) {
    auto* actor = mActor;
    const auto& matrix = actor->getMtx();
    sead::Vector3f direction(matrix.getBase(2).x, 0.0f, matrix.getBase(2).z);
    direction.normalize();
    sead::Vector3f position(matrix.getTranslation().x, 0.0f, matrix.getTranslation().z);
    position += direction * *mFrontOffset_s;
    const sead::Vector3f start(first->x, 0.0f, first->z);
    const sead::Vector3f end(second->x, 0.0f, second->z);
    if ((start - position).dot(direction) < 0.0f &&
        (end - position).dot(direction) < 0.0f)
        return false;
    const sead::Segment3f segment(start, end);
    f32 t = 0.0f;
    const f32 range_squared = *mDist_s * *mDist_s;
    const f32 distance_squared = sead::Geometry::calcSquaredDistancePointToSegment(position, segment, &t);
    if (distance_squared > range_squared)
        return false;
    auto toward = start + (end - start) * t - position;
    toward.normalize();
    const f32 alignment = direction.dot(toward);
    // The original rejects a greater distance and accepts unordered comparisons.
    return !(distance_squared > range_squared * (alignment * alignment));
}

}  // namespace uking::ai
