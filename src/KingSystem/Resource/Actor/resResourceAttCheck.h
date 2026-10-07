#pragma once

#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include <prim/seadRuntimeTypeInfo.h>
#include <utility/aglParameter.h>
#include <utility/aglParameterList.h>
#include <utility/aglParameterObj.h>
#include "resResourceAttClient.h"
#include "resResourceAttPos.h"

namespace ksys::act {
class Actor;
class ActorConstDataAccess;
}  // namespace ksys::act

namespace ksys::res {

enum class AttCheckType {
    Line,
    Screen,
    AreaSphere,
    AreaFan,
    AreaCylinderFan,
    AreaBox,
    EachOtherArea,
    Angle,
    Weight,
    RideHorse,
    RideSpace,
    Swim,
    Carry,
    NoCarry,
    Grab,
    BootFirstTower,
    FireContact,
    CharacterOn,
    UnderWater,
};

class AttClient;

// Placeholder (no ctor / vtable): the argument struct AI code builds on the stack for
// AttCheck::check (through ActorConstDataAccess::sub_7100D13AE4). Only the fields AI code sets are
// known.
struct AttCheck_Unk1 {
    /* 0x00 */ sead::Matrix34f _0;
    /* 0x30 */ f32 _30;  // (a radius for Ride checks, EnemySearchHorse)
    /* 0x34 */ bool _34;
    /* 0x35 */ bool _35;
    /* 0x36 */ bool _36;
};

class AttCheck {
    SEAD_RTTI_BASE(AttCheck)
public:
    struct CreateArg {
        agl::utl::ResParameterList res_list;
        sead::Heap* heap;
        AttClient* client;
    };

    static AttCheck* make(const CreateArg& arg);

    explicit AttCheck(AttCheckType type) : mType{type} {}
    virtual ~AttCheck() = default;

    // FIXME: signatures and names
    // Slot 4 (res::AttClient::checkM4 calls it for every check with the matrix of that check).
    virtual void m4(act::Actor* actor, sead::Matrix34f* mtx);
    // Slot 5 (res::AttClient::check calls it for every check with the client's matrix `i`).
    virtual bool check(act::Actor* actor, const act::ActorConstDataAccess& accessor,
                       const sead::Matrix34f* mtx, const sead::Vector3f& pos,
                       const AttCheck_Unk1* arg, bool a6, bool a7);
    // Slot 6 (res::AttClient::checkM6: the maximum over the checks; `accessor` is a default-constructed one and `scale`
    // is the actor's scale).
    virtual float m6(const act::ActorConstDataAccess& accessor, const sead::Vector3f& scale);
    // Slot 7.
    virtual void m7(act::Actor* actor, const act::ActorConstDataAccess& accessor, bool a3) {}

    virtual bool parse(const CreateArg& arg);

    // For internal use by AttClient.
    agl::utl::ParameterList& getList_() { return mList; }

protected:
    bool init(const CreateArg& arg);

    AttClient* mClient = nullptr;
    AttCheckType mType{};
    agl::utl::ParameterObj mObj;
    agl::utl::ParameterList mList;
};

class AttCheckLine : public AttCheck {
    SEAD_RTTI_OVERRIDE(AttCheckLine, AttCheck)
public:
    using AttCheck::AttCheck;

    bool check(act::Actor* actor, const act::ActorConstDataAccess& accessor,
               const sead::Matrix34f* mtx, const sead::Vector3f& pos, const AttCheck_Unk1* arg,
               bool a6, bool a7) override;
    bool parse(const CreateArg& arg) override;

private:
    agl::utl::Parameter<float> mRadius;
    agl::utl::Parameter<bool> mAsLineOfSight;
};

class AttCheckScreen : public AttCheck {
    SEAD_RTTI_OVERRIDE(AttCheckScreen, AttCheck)
public:
    using AttCheck::AttCheck;

    bool check(act::Actor* actor, const act::ActorConstDataAccess& accessor,
               const sead::Matrix34f* mtx, const sead::Vector3f& pos, const AttCheck_Unk1* arg,
               bool a6, bool a7) override;
};

class AttCheckArea : public AttCheck {
    SEAD_RTTI_OVERRIDE(AttCheckArea, AttCheck)
public:
    using AttCheck::AttCheck;

    void m4(act::Actor* actor, sead::Matrix34f* mtx) override;
    bool check(act::Actor* actor, const act::ActorConstDataAccess& accessor,
               const sead::Matrix34f* mtx, const sead::Vector3f& pos, const AttCheck_Unk1* arg,
               bool a6, bool a7) override;
    float m6(const act::ActorConstDataAccess& accessor, const sead::Vector3f& scale) override;
    void m7(act::Actor* actor, const act::ActorConstDataAccess& accessor, bool a3) override;
    bool parse(const CreateArg& arg) override;

    // Slot 9: the area test of `check`: `local_pos` is `pos` in the area's matrix.
    virtual bool m9(const act::ActorConstDataAccess& link, const sead::Vector3f& local_pos,
                    const sead::Vector3f& pos, const AttCheck_Unk1* arg, bool a6, bool a7) {
        return true;
    }
    // Slot 10 (called by m6).
    virtual float m10(const act::ActorConstDataAccess& accessor, const sead::Vector3f& scale) {
        return 0;
    }
    // Slot 11 (called by m7).
    virtual void m11(const act::ActorConstDataAccess& link, const sead::Matrix34f& mtx,
                     const sead::Vector3f& scale, bool a4) {}

protected:
    AttPos mAttPos;
    agl::utl::Parameter<bool> mFromPlayer;
};

class AttCheckAreaSphere : public AttCheckArea {
    SEAD_RTTI_OVERRIDE(AttCheckAreaSphere, AttCheckArea)
public:
    using AttCheckArea::AttCheckArea;

    bool parse(const CreateArg& arg) override;
    bool m9(const act::ActorConstDataAccess& link, const sead::Vector3f& local_pos,
            const sead::Vector3f& pos, const AttCheck_Unk1* arg, bool a6, bool a7) override;
    float m10(const act::ActorConstDataAccess& accessor, const sead::Vector3f& scale) override;
    void m11(const act::ActorConstDataAccess& link, const sead::Matrix34f& mtx,
             const sead::Vector3f& scale, bool a4) override;

private:
    agl::utl::Parameter<bool> mForceEditModelArea;
    agl::utl::Parameter<float> mRadius;
    agl::utl::Parameter<float> mFixedRadius;
    agl::utl::Parameter<bool> mForceEditMargin;
    agl::utl::Parameter<float> mMarginRadius;
};

class AttCheckAreaFan : public AttCheckArea {
    SEAD_RTTI_OVERRIDE(AttCheckAreaFan, AttCheckArea)
public:
    using AttCheckArea::AttCheckArea;

    bool parse(const CreateArg& arg) override;
    bool m9(const act::ActorConstDataAccess& link, const sead::Vector3f& local_pos,
            const sead::Vector3f& pos, const AttCheck_Unk1* arg, bool a6, bool a7) override;
    float m10(const act::ActorConstDataAccess& accessor, const sead::Vector3f& scale) override;
    void m11(const act::ActorConstDataAccess& link, const sead::Matrix34f& mtx,
             const sead::Vector3f& scale, bool a4) override;

private:
    agl::utl::Parameter<bool> mAngleCheckIgnoreLockOn;
    agl::utl::Parameter<bool> mForceEditModelArea;
    agl::utl::Parameter<float> mRadius;
    agl::utl::Parameter<float> mAngle;
    agl::utl::Parameter<float> mTop;
    agl::utl::Parameter<float> mBottom;
    agl::utl::Parameter<float> mMarginRadius;
    agl::utl::Parameter<float> mMarginTop;
    agl::utl::Parameter<float> mMarginBottom;
    agl::utl::Parameter<bool> mForceEditMargin;
    agl::utl::Parameter<float> mFixedRadius;
    agl::utl::Parameter<float> mFixedTop;
    agl::utl::Parameter<float> mFixedBottom;
};

class AttCheckAreaCylinderFan : public AttCheckArea {
    SEAD_RTTI_OVERRIDE(AttCheckAreaCylinderFan, AttCheckArea)
public:
    using AttCheckArea::AttCheckArea;

    bool parse(const CreateArg& arg) override;
    bool m9(const act::ActorConstDataAccess& link, const sead::Vector3f& local_pos,
            const sead::Vector3f& pos, const AttCheck_Unk1* arg, bool a6, bool a7) override;
    float m10(const act::ActorConstDataAccess& accessor, const sead::Vector3f& scale) override;

private:
    agl::utl::Parameter<bool> mAngleCheckIgnoreLockOn;
    agl::utl::Parameter<bool> mForceEditModelArea;
    agl::utl::Parameter<float> mRadius;
    agl::utl::Parameter<float> mTop;
    agl::utl::Parameter<float> mBottom;
    agl::utl::Parameter<float> mAngle;
    agl::utl::Parameter<float> mFixedRadiusCylinder;
    agl::utl::Parameter<float> mFixedRadiusFan;
    agl::utl::Parameter<float> mFixedTop;
    agl::utl::Parameter<float> mFixedBottom;
    agl::utl::Parameter<bool> mForceEditMargin;
    agl::utl::Parameter<float> mMarginRadiusCylinder;
    agl::utl::Parameter<float> mMarginRadiusFan;
    agl::utl::Parameter<float> mMarginTop;
    agl::utl::Parameter<float> mMarginBottom;
};

class AttCheckAreaBox : public AttCheckArea {
    SEAD_RTTI_OVERRIDE(AttCheckAreaBox, AttCheckArea)
public:
    explicit AttCheckAreaBox(AttCheckType type) : AttCheckArea(type) {}

    bool parse(const CreateArg& arg) override;
    bool m9(const act::ActorConstDataAccess& link, const sead::Vector3f& local_pos,
            const sead::Vector3f& pos, const AttCheck_Unk1* arg, bool a6, bool a7) override;
    float m10(const act::ActorConstDataAccess& accessor, const sead::Vector3f& scale) override;
    void m11(const act::ActorConstDataAccess& link, const sead::Matrix34f& mtx,
             const sead::Vector3f& scale, bool a4) override;

private:
    agl::utl::Parameter<bool> mForceEditModelArea;
    agl::utl::Parameter<sead::Vector3f> mMin;
    agl::utl::Parameter<sead::Vector3f> mMax;
    agl::utl::Parameter<sead::Vector3f> mFixedMin;
    agl::utl::Parameter<sead::Vector3f> mFixedMax;
    agl::utl::Parameter<bool> mForceEditMargin;
    agl::utl::Parameter<sead::Vector3f> mMarginMin;
    agl::utl::Parameter<sead::Vector3f> mMarginMax;
};

class AttCheckEachOtherArea : public AttCheck {
    SEAD_RTTI_OVERRIDE(AttCheckEachOtherArea, AttCheck)
public:
    explicit AttCheckEachOtherArea(AttCheckType type);

    void m4(act::Actor* actor, sead::Matrix34f* mtx) override;
    bool check(act::Actor* actor, const act::ActorConstDataAccess& accessor,
               const sead::Matrix34f* mtx, const sead::Vector3f& pos, const AttCheck_Unk1* arg,
               bool a6, bool a7) override;
    float m6(const act::ActorConstDataAccess& accessor, const sead::Vector3f& scale) override;
    void m7(act::Actor* actor, const act::ActorConstDataAccess& accessor, bool a3) override;
    bool parse(const CreateArg& arg) override;

private:
    agl::utl::Parameter<bool> mForceEditModelArea;
    agl::utl::Parameter<float> mRadius;
    agl::utl::Parameter<float> mTop;
    agl::utl::Parameter<float> mBottom;
    agl::utl::Parameter<bool> mForceEditMargin;
    agl::utl::Parameter<float> mMarginRadius;
    agl::utl::Parameter<float> mMarginTop;
    agl::utl::Parameter<float> mMarginBottom;
    agl::utl::Parameter<float> mFixedRadius;
    agl::utl::Parameter<float> mFixedTop;
    agl::utl::Parameter<float> mFixedBottom;
    agl::utl::Parameter<float> mOffsetTop;
    agl::utl::Parameter<float> mOffsetBottom;
};

class AttCheckAngle : public AttCheck {
    SEAD_RTTI_OVERRIDE(AttCheckAngle, AttCheck)
public:
    using AttCheck::AttCheck;

    void m4(act::Actor* actor, sead::Matrix34f* mtx) override;
    bool check(act::Actor* actor, const act::ActorConstDataAccess& accessor,
               const sead::Matrix34f* mtx, const sead::Vector3f& pos, const AttCheck_Unk1* arg,
               bool a6, bool a7) override;
    bool parse(const CreateArg& arg) override;

private:
    AttPos mAttPos;
    agl::utl::Parameter<float> mAngle;
};

class AttCheckWeight : public AttCheck {
    SEAD_RTTI_OVERRIDE(AttCheckWeight, AttCheck)
public:
    using AttCheck::AttCheck;

    bool check(act::Actor* actor, const act::ActorConstDataAccess& accessor,
               const sead::Matrix34f* mtx, const sead::Vector3f& pos, const AttCheck_Unk1* arg,
               bool a6, bool a7) override;
};

class AttCheckRideHorse : public AttCheck {
    SEAD_RTTI_OVERRIDE(AttCheckRideHorse, AttCheck)
public:
    using AttCheck::AttCheck;

    bool check(act::Actor* actor, const act::ActorConstDataAccess& accessor,
               const sead::Matrix34f* mtx, const sead::Vector3f& pos, const AttCheck_Unk1* arg,
               bool a6, bool a7) override;
};

class AttCheckRideSpace : public AttCheck {
    SEAD_RTTI_OVERRIDE(AttCheckRideSpace, AttCheck)
public:
    using AttCheck::AttCheck;

    bool check(act::Actor* actor, const act::ActorConstDataAccess& accessor,
               const sead::Matrix34f* mtx, const sead::Vector3f& pos, const AttCheck_Unk1* arg,
               bool a6, bool a7) override;
};

class AttCheckSwim : public AttCheck {
    SEAD_RTTI_OVERRIDE(AttCheckSwim, AttCheck)
public:
    using AttCheck::AttCheck;

    bool check(act::Actor* actor, const act::ActorConstDataAccess& accessor,
               const sead::Matrix34f* mtx, const sead::Vector3f& pos, const AttCheck_Unk1* arg,
               bool a6, bool a7) override;
};

class AttCheckCarry : public AttCheck {
    SEAD_RTTI_OVERRIDE(AttCheckCarry, AttCheck)
public:
    using AttCheck::AttCheck;

    bool check(act::Actor* actor, const act::ActorConstDataAccess& accessor,
               const sead::Matrix34f* mtx, const sead::Vector3f& pos, const AttCheck_Unk1* arg,
               bool a6, bool a7) override;
};

class AttCheckNoCarry : public AttCheck {
    SEAD_RTTI_OVERRIDE(AttCheckNoCarry, AttCheck)
public:
    using AttCheck::AttCheck;

    bool check(act::Actor* actor, const act::ActorConstDataAccess& accessor,
               const sead::Matrix34f* mtx, const sead::Vector3f& pos, const AttCheck_Unk1* arg,
               bool a6, bool a7) override;
};

class AttCheckGrab : public AttCheck {
    SEAD_RTTI_OVERRIDE(AttCheckGrab, AttCheck)
public:
    using AttCheck::AttCheck;

    bool check(act::Actor* actor, const act::ActorConstDataAccess& accessor,
               const sead::Matrix34f* mtx, const sead::Vector3f& pos, const AttCheck_Unk1* arg,
               bool a6, bool a7) override;
};

class AttCheckBootFirstTower : public AttCheck {
    SEAD_RTTI_OVERRIDE(AttCheckBootFirstTower, AttCheck)
public:
    using AttCheck::AttCheck;

    bool check(act::Actor* actor, const act::ActorConstDataAccess& accessor,
               const sead::Matrix34f* mtx, const sead::Vector3f& pos, const AttCheck_Unk1* arg,
               bool a6, bool a7) override;
};

class AttCheckFireContact : public AttCheck {
    SEAD_RTTI_OVERRIDE(AttCheckFireContact, AttCheck)
public:
    using AttCheck::AttCheck;

    bool check(act::Actor* actor, const act::ActorConstDataAccess& accessor,
               const sead::Matrix34f* mtx, const sead::Vector3f& pos, const AttCheck_Unk1* arg,
               bool a6, bool a7) override;
};

class AttCheckCharacterOn : public AttCheck {
    SEAD_RTTI_OVERRIDE(AttCheckCharacterOn, AttCheck)
public:
    using AttCheck::AttCheck;

    bool check(act::Actor* actor, const act::ActorConstDataAccess& accessor,
               const sead::Matrix34f* mtx, const sead::Vector3f& pos, const AttCheck_Unk1* arg,
               bool a6, bool a7) override;
};

class AttCheckUnderWater : public AttCheck {
    SEAD_RTTI_OVERRIDE(AttCheckUnderWater, AttCheck)
public:
    using AttCheck::AttCheck;

    bool check(act::Actor* actor, const act::ActorConstDataAccess& accessor,
               const sead::Matrix34f* mtx, const sead::Vector3f& pos, const AttCheck_Unk1* arg,
               bool a6, bool a7) override;
};

}  // namespace ksys::res
