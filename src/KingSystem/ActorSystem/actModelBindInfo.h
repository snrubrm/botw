#pragma once

#include <gsys/gsysModelAccessKey.h>
#include <math/seadMatrix.h>
#include <prim/seadRuntimeTypeInfo.h>
#include "KingSystem/ActorSystem/actActorBind.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::act {

// Name from the CSV (ModelBindInfo::ctor 0x7100d3bd84): binds an actor to a bone of another
// actor's model. vtable 0x71024dadf8. Embedded in the BindAction family (+0x38).
// TODO: incomplete.
class ModelBindInfo : public ActorBind {
    SEAD_RTTI_OVERRIDE(ModelBindInfo, ActorBind)
public:
    ModelBindInfo();
    ~ModelBindInfo() override = default;

    bool m4(BaseProc* proc) override;
    bool m5(Actor* actor) override;
    void m10(BaseProcLink* link) override { _30.getKey().reset(); }

    /* 0x28 */ const char* _28 = nullptr;  // bone name (m4 searches _30 with it)
    /* 0x30 */ gsys::BoneAccessKeyEx _30;
    /* 0x68 */ sead::Matrix34f _68 = sead::Matrix34f::ident;
    /* 0x98 */ u32 _98 = 0;
};
KSYS_CHECK_SIZE_NX150(ModelBindInfo, 0xa0);

}  // namespace ksys::act
