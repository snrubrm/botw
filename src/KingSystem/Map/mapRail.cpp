#include "KingSystem/Map/mapRail.h"
#include <heap/seadHeapMgr.h>
#include "KingSystem/Utils/MathUtil.h"
#include "KingSystem/Utils/SafeDelete.h"

namespace ksys::map {

static bool isNearZero(const sead::Vector3f& v) {
    return v.x <= 0.01f && v.x >= -0.01f && v.y <= 0.01f && v.y >= -0.01f && v.z <= 0.01f &&
           v.z >= -0.01f;
}

static void calcBezierPoint(sead::Vector3f* out, const sead::Vector3f& p0, const sead::Vector3f& c0,
                            const sead::Vector3f& c1, const sead::Vector3f& p1, float t) {
    const float s = 1.0f - t;
    const float s2 = s * s;
    const float t2 = t * t;
    out->setScale(p0, s * s2);
    *out = *out + c0 * (t * s2 * 3.0f) + c1 * (t2 * s * 3.0f);
    out->setScaleAdd(t * t2, p1, *out);
}

static void calcBezierTangent(sead::Vector3f* out, const sead::Vector3f& p0,
                              const sead::Vector3f& c0, const sead::Vector3f& c1,
                              const sead::Vector3f& p1, float t) {
    const float s = 1.0f - t;
    const float t3 = t * 3.0f;
    out->setScale(p0, s * s * -3.0f);
    *out = *out + c0 * (s * 3.0f * (1.0f - t3)) + c1 * (t3 * (2.0f - t3));
    out->setScaleAdd(t * t * 3.0f, p1, *out);
}

RailPoint::~RailPoint() = default;

const MubinIter& RailPoint::getIter() const {
    return mIter;
}

const sead::Vector3f& RailPoint::getRotate() const {
    return mSRT.rotate;
}

const sead::Vector3f& RailPoint::getTranslate() const {
    return mSRT.translate;
}

f32 RailPoint::getPrevDistance() const {
    return mPrevDistance;
}

f32 RailPoint::getNextDistance() const {
    return mNextDistance;
}

bool RailPoint::parse(MubinIter* iter, sead::Heap* heap) {
    iter->getScale(&mSRT.scale);
    iter->getRotate(&mSRT.rotate);

    bool success = true;
    success &= iter->tryGetFloatArrayByKey(mSRT.translate.e.data(), "Translate");
    success &= iter->tryGetParamFloatByKey(&mPrevDistance, "PrevDistance");
    success &= iter->tryGetParamFloatByKey(&mNextDistance, "NextDistance");
    iter->tryGetControlPoints(&mCtrlPoints);

    return success;
}

Rail::Rail() = default;

Rail::~Rail() {
    mRailPoints.freeBuffer();
}

void Rail::init(MubinIter* iter, sead::Heap* heap) {
    parse(iter);

    MubinIter result;
    if (iter->tryGetParamIterByKey(&result, "RailPoints")) {
        s32 size = result.getSize();
        mRailPoints.allocBufferAssert(size, heap);
        for (int i = 0; i < size; ++i) {
            MubinIter node_iter;
            if (result.tryGetIterByIndex(&node_iter, i)) {
                RailPoint* point = allocPointIdx(i, heap);
                point->mIter = node_iter;
                point->parse(&node_iter, heap);
            }
        }
    }

    x_38();
}

RailPoint* Rail::allocPointIdx(s32 idx, sead::Heap* heap) {
    mRailPoints[idx] = allocPoint(heap);
    return mRailPoints[idx];
}

s32 Rail::getNumPoints() const {
    return mRailPoints.size();
}

const RailPoint* Rail::getPoint(s32 idx) const {
    if (idx < 0 || idx >= mRailPoints.size())
        return nullptr;
    return mRailPoints[idx];
}

RailPoint* Rail::getPoint(s32 idx) {
    if (idx < 0 || idx >= mRailPoints.size())
        return nullptr;
    return mRailPoints[idx];
}

const SRT& Rail::getPointSRT(s32 idx) const {
    return mRailPoints[idx]->mSRT;
}

const sead::Vector3f& Rail::getPointRotate(s32 idx) const {
    return mRailPoints[idx]->mSRT.rotate;
}

const sead::Vector3f& Rail::getPointTranslate(s32 idx) const {
    return mRailPoints[idx]->mSRT.translate;
}

const sead::Vector3f& Rail::getControlPoint(s32 rail_idx, s32 pt_idx) const {
    return mRailPoints[rail_idx]->mCtrlPoints[pt_idx];
}

sead::Vector3f Rail::calcTranslate(float progress) const {
    sead::Vector3f pos;
    calcTranslateRotate(&pos, nullptr, progress);
    return pos;
}

void Rail::calcTranslate(sead::Vector3f* pos_out, float progress) const {
    calcTranslateRotate(pos_out, nullptr, progress);
}

// NON_MATCHING: the original evaluates the near-zero control point checks as a branch chain
// (y/z loads not speculated; `t` tested between y and z) and lays out the blocks differently
void Rail::calcTranslateRotate(sead::Vector3f* pos_out, sead::Vector3f* rot_out,
                               float progress) const {
    const s32 num_points = mRailPoints.size();
    if (num_points == 1) {
        *pos_out = mRailPoints[0]->mSRT.translate;
        if (rot_out)
            rot_out->set(0, 0, 0);
        return;
    }

    if (isClosed()) {
        const float n = num_points;
        progress -= n * sead::Mathf::floor(progress / n);
    }

    s32 idx = sead::Mathf::floor(progress);
    if (!isClosed() && idx == num_points - 1)
        idx = num_points - 2;

    const s32 next_idx = (idx + 1) % num_points;
    const float t = progress - idx;
    const RailPoint* p0 = mRailPoints[idx];
    const RailPoint* p1 = mRailPoints[next_idx];

    if (!isBezier()) {
        util::lerp(pos_out, p0->mSRT.translate, p1->mSRT.translate, t);
        if (rot_out) {
            rot_out->setSub(p1->mSRT.translate, p0->mSRT.translate);
            rot_out->normalize();
        }
        return;
    }

    calcBezierPoint(pos_out, p0->mSRT.translate, p0->mCtrlPoints[1] + p0->mSRT.translate,
                    p1->mCtrlPoints[0] + p1->mSRT.translate, p1->mSRT.translate, t);

    if (!rot_out)
        return;

    if (isNearZero(p0->mCtrlPoints[1]) && t < 0.01f) {
        rot_out->setAdd(p1->mSRT.translate, p1->mCtrlPoints[0]);
        *rot_out -= p0->mSRT.translate;
    } else if (isNearZero(p1->mCtrlPoints[0]) && t > 0.99f) {
        rot_out->setSub(p1->mSRT.translate, p0->mCtrlPoints[1]);
        *rot_out -= p0->mSRT.translate;
    } else {
        calcBezierTangent(rot_out, p0->mSRT.translate, p0->mCtrlPoints[1] + p0->mSRT.translate,
                          p1->mCtrlPoints[0] + p1->mSRT.translate, p1->mSRT.translate, t);
    }
    rot_out->normalize();
}

bool Rail::isClosed() const {
    return mFlags.isOn(Flag::Closed);
}

bool Rail::isBezier() const {
    return mFlags.isOn(Flag::Bezier);
}

const u32& Rail::getHashId() const {
    return mHashId;
}

const char* Rail::getUniqueName() const {
    return mUniqueName;
}

RailPoint* Rail::allocPoint(sead::Heap* heap) {
    return new (heap) RailPoint;
}

bool Rail::parse(MubinIter* iter) {
    bool success = true;

    success &= iter->tryGetParamUIntByKey(&mHashId, "HashId");
    success &= iter->tryGetParamStringByKey(&mUniqueName, "UniqueName");

    bool closed = false;
    if (!iter->tryGetParamBoolByKey(&closed, "IsClosed")) {
        success = false;
    } else if (closed) {
        mFlags.set(Flag::Closed);
    } else {
        mFlags.reset(Flag::Closed);
    }

    const char* type = nullptr;
    if (!iter->tryGetParamStringByKey(&type, "RailType")) {
        success = false;
    } else {
        mFlags.change(Flag::Bezier, sead::SafeString(type) == "Bezier");
    }

    return success;
}

bool RailGuidePoint::parse(MubinIter* iter, sead::Heap* heap) {
    bool success = true;
    success &= RailPoint::parse(iter, heap);
    success &= iter->tryGetParamFloatByKey(&mWaitFrame, "WaitFrame");
    return success;
}

RailGuide::RailGuide() = default;

RailGuide::~RailGuide() = default;

bool RailRemainGuidePoint::parse(MubinIter* iter, sead::Heap* heap) {
    bool success = true;
    success &= RailGuidePoint::parse(iter, heap);
    success &= iter->tryGetParamFloatByKey(&mMoveSpeed, "MoveSpeed");
    return success;
}

RailRemainGuide::RailRemainGuide() = default;

RailRemainGuide::~RailRemainGuide() = default;

RailPoint* RailRemainGuide::allocPoint(sead::Heap* heap) {
    return new (heap) RailRemainGuidePoint;
}

RailConnectablePoint::RailConnectablePoint() = default;

RailConnectablePoint::~RailConnectablePoint() {
    sead::HeapMgr::instance()->getCurrentHeap();

    if (mJunctionPoint)
        util::safeDeleteArray(mJunctionPoint);
}

Rail* RailConnectablePoint::getJunctionRail() const {
    return mJunctionRail;
}

RailConnectablePoint** RailConnectablePoint::getJunctionPoint() const {
    return mJunctionPoint;
}

bool RailConnectablePoint::parse(MubinIter* iter, sead::Heap* heap) {
    return RailPoint::parse(iter, heap);
}

RailRoutePoint::RailRoutePoint() = default;

RailRoutePoint::~RailRoutePoint() = default;

const char* RailRoutePoint::getCheckPointName() const {
    return mCheckPointName;
}

bool RailRoutePoint::parse(MubinIter* iter, sead::Heap* heap) {
    bool success = true;
    success &= RailConnectablePoint::parse(iter, heap);
    iter->tryGetParamStringByKey(&mEntryPointName, "EntryPointName");
    iter->tryGetParamStringByKey(&mCheckPointName, "CheckPointName");
    return success;
}

RailRoute::RailRoute() {
    mFlags.set(Flag::AutoPlacementEnabled);
    mFlags.set(Flag::EnableHorseTrace);
    mFlags.set(Flag::Walkable);
}

RailRoute::~RailRoute() = default;

bool RailRoute::isRenderEnabled() const {
    return mFlags.isOn(Flag::RenderEnabled);
}

bool RailRoute::isAutoPlacementEnabled() const {
    return mFlags.isOn(Flag::AutoPlacementEnabled);
}

bool RailRoute::isWalkable() const {
    return mFlags.isOn(Flag::Walkable);
}

bool RailRoute::isHorseTraceEnabled() const {
    return mFlags.isOn(Flag::EnableHorseTrace);
}

const char* RailRoute::getRouteId() const {
    return mRouteId;
}

const char* RailRoute::getCheckPointName(s32 idx) const {
    return static_cast<RailRoutePoint*>(mRailPoints[idx])->mCheckPointName;
}

bool RailRoute::parse(MubinIter* iter) {
    int success = Rail::parse(iter);

    bool result = false;
    if (iter->tryGetParamBoolByKey(&result, "RenderEnabled")) {
        if (result) {
            mFlags.set(Flag::RenderEnabled);
        } else {
            mFlags.reset(Flag::RenderEnabled);
        }
    }

    if (iter->tryGetParamBoolByKey(&result, "AutoPlacementEnabled")) {
        if (result) {
            mFlags.set(Flag::AutoPlacementEnabled);
        } else {
            mFlags.reset(Flag::AutoPlacementEnabled);
        }
    } else {
        success = false;
    }

    if (iter->tryGetParamBoolByKey(&result, "IsWalkable")) {
        if (result) {
            mFlags.set(Flag::Walkable);
        } else {
            mFlags.reset(Flag::Walkable);
        }
    } else {
        success = false;
    }

    if (iter->tryGetParamBoolByKey(&result, "IsEnableHorseTrace")) {
        if (result) {
            mFlags.set(Flag::EnableHorseTrace);
        } else {
            mFlags.reset(Flag::EnableHorseTrace);
        }
    }

    success &= iter->tryGetParamStringByKey(&mRouteId, "RouteId");
    return success;
}

}  // namespace ksys::map
