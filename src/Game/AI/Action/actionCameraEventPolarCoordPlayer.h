#pragma once

#include <container/seadSafeArray.h>
#include <math/seadMatrix.h>
#include <prim/seadSafeString.h>
#include "Game/AI/Action/actionCameraEventPolarCoord.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace ksys::act {
class ActorConstDataAccess;
}

namespace ksys::map {
class Object;
}

namespace uking::action {

// Up to three reference actors (m62 gives their kind: 0-3, -1 = unused); m60 / m61 give the
// positions the polar coordinate is computed from.
class CameraEventPolarCoordPlayer : public CameraEventPolarCoord {
    SEAD_RTTI_OVERRIDE(CameraEventPolarCoordPlayer, CameraEventPolarCoord)
public:
    explicit CameraEventPolarCoordPlayer(const InitArg& arg);
    // inline: CameraEventPolarCoordPlayerRel's destructor inlines it.
    ~CameraEventPolarCoordPlayer() override = default;

protected:
    void m47() override;
    bool m48() override;
    void m49() override;
    void m56(act::Unk_7100922700* out) override;
    const ksys::act::BaseProcLink* m59() override;

    virtual void m60(sead::Vector3f* out);
    virtual void m61(sead::Vector3f* out);
    virtual int m62(int idx);
    virtual int m63();
    virtual bool m64();

    // 0x7100768208: updates the three reference actors.
    void sub_7100768208();
    // 0x7100768474: looks up reference actor `idx` (by its kind _94[idx]).
    void sub_7100768474(int idx);
    // 0x71007685c0: stores the matrix of reference actor `idx`.
    void sub_71007685C0(int idx);
    // 0x71007686a8 / 0x71007686d8: callbacks of sub_71009248D4 for reference actor _1d8.
    void sub_71007686A8(ksys::act::ActorConstDataAccess* accessor);
    void sub_71007686D8(ksys::map::Object* object);

    sead::SafeArray<s32, 3> _94{};
    // Actor names / unique names of the reference actors (kind 3).
    sead::SafeArray<sead::SafeString, 3> _a0;
    sead::SafeArray<sead::SafeString, 3> _d0;
    // Value-initialised in the constructor (memset).
    sead::SafeArray<s32, 3> _100;
    sead::SafeArray<s32, 3> _10c;
    sead::SafeArray<ksys::act::BaseProcLink, 3> _118;
    sead::SafeArray<sead::Matrix34f, 3> _148;
    s32 _1d8;
};

}  // namespace uking::action
