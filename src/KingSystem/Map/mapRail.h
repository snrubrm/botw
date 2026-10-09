#pragma once

#include <container/seadBuffer.h>
#include <prim/seadTypedBitFlag.h>
#include "KingSystem/Map/mapMubinIter.h"

namespace ksys::map {

class Placement18;

class RailPoint {
    friend class Rail;

public:
    RailPoint()
        : mSRT{sead::Vector3f::ones, sead::Vector3f::zero, sead::Vector3f::zero},
          mCtrlPoints{{sead::Vector3f::zero, sead::Vector3f::zero}} {
        mPrevDistance = 0.0f;
        mNextDistance = 0.0f;
    }
    virtual ~RailPoint();
    virtual bool parse(MubinIter* iter, sead::Heap* heap);

    const MubinIter& getIter() const;
    const sead::Vector3f& getRotate() const;
    const sead::Vector3f& getTranslate() const;
    f32 getPrevDistance() const;
    f32 getNextDistance() const;

protected:
    SRT mSRT;
    ControlPoints mCtrlPoints;
    float mPrevDistance;
    float mNextDistance;
    MubinIter mIter;
};

class Rail {
public:
    Rail();
    virtual ~Rail();
    virtual void init(MubinIter* iter, sead::Heap* heap);
    virtual s32 x_18() { return 0; }
    // Whether this is a route (RailRoute overrides it; tested as a bool by AI_Query_CheckRoad).
    virtual bool x_20() { return false; }
    virtual RailPoint* allocPoint(sead::Heap* heap);
    virtual bool parse(MubinIter* iter);
    virtual void x_38() {}

    RailPoint* allocPointIdx(s32 idx, sead::Heap* heap);
    s32 getNumPoints() const;
    const RailPoint* getPoint(s32 idx) const;
    RailPoint* getPoint(s32 idx);

    const SRT& getPointSRT(s32 idx) const;
    const sead::Vector3f& getPointRotate(s32 idx) const;
    const sead::Vector3f& getPointTranslate(s32 idx) const;
    const sead::Vector3f& getControlPoint(s32 rail_idx, s32 pt_idx) const;

    sead::Vector3f calcTranslate(float progress) const;
    void calcTranslate(sead::Vector3f* pos_out, float progress) const;
    void calcTranslateRotate(sead::Vector3f* pos_out, sead::Vector3f* rot_out,
                             float progress) const;
    bool isClosed() const;
    bool isBezier() const;
    const u32& getHashId() const;
    const char* getUniqueName() const;

    enum class Flag : u32 {
        Closed = 1 << 0,
        Bezier = 1 << 1,
        RenderEnabled = 1 << 2,
        AutoPlacementEnabled = 1 << 3,
        Walkable = 1 << 4,
        EnableHorseTrace = 1 << 5,
    };

protected:
    // Constructors load the shared value at 0x7102600398.
    static u32 sHashBase;

    sead::TypedBitFlag<Flag> mFlags{};
    u32 mHashId = sHashBase;
    const char* mUniqueName{};
    sead::Buffer<RailPoint*> mRailPoints{};
    MubinIter mIter{};
};

class RailGuidePoint : public RailPoint {
    friend class RailGuide;

public:
    RailGuidePoint() : mWaitFrame(0.0f) {}
    ~RailGuidePoint() override = default;

    bool parse(MubinIter* iter, sead::Heap* heap) override;

protected:
    float mWaitFrame;
};

class RailRemainGuidePoint : public RailGuidePoint {
    friend class RailRemainGuide;

public:
    RailRemainGuidePoint();
    ~RailRemainGuidePoint() override;

    bool parse(MubinIter* iter, sead::Heap* heap) override;

protected:
    float mMoveSpeed;
};

class RailGuide : public Rail {
public:
    RailGuide();
    ~RailGuide() override;
    RailPoint* allocPoint(sead::Heap* heap) override;
};

class RailRemainGuide : public RailGuide {
public:
    RailRemainGuide();
    ~RailRemainGuide() override;

    RailPoint* allocPoint(sead::Heap* heap) override;
};

class RailConnectablePoint : public RailPoint {
    friend class RailConnectable;

public:
    explicit RailConnectablePoint(Rail* rail);
    ~RailConnectablePoint() override;

    bool parse(MubinIter* iter, sead::Heap* heap) override;

    Rail* getJunctionRail() const;
    RailConnectablePoint** getJunctionPoint() const;
    void parseJunctions(Placement18 p18, s32 idx, u32 hash, sead::Heap* heap);

protected:
    Rail* mJunctionRail;
    RailConnectablePoint** mJunctionPoint;
};

class RailConnectable : public Rail {
public:
    RailConnectable();
    ~RailConnectable() override;
    RailPoint* allocPoint(sead::Heap* heap) override;

    s32 x_18() override { return 1; }
    bool x_20() override { return true; }
    void x_38() override {}
};

class RailRoutePoint : public RailConnectablePoint {
    friend class RailRoute;

public:
    explicit RailRoutePoint(Rail* rail);
    ~RailRoutePoint() override;

    bool parse(MubinIter* iter, sead::Heap* heap) override;
    const char* getCheckPointName() const;

protected:
    const char* mEntryPointName;
    const char* mCheckPointName;
};

class RailRoute : public RailConnectable {
public:
    RailRoute();
    ~RailRoute() override;
    RailPoint* allocPoint(sead::Heap* heap) override;

    bool parse(MubinIter* iter) override;

    bool isRenderEnabled() const;
    bool isAutoPlacementEnabled() const;
    bool isWalkable() const;
    bool isHorseTraceEnabled() const;
    const char* getRouteId() const;
    const char* getCheckPointName(s32 idx) const;

protected:
    const char* mRouteId{};
};

}  // namespace ksys::map
