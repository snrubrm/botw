#pragma once

#include "Game/AI/AI/aiLandHumEnemyNormal.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace ksys::act {
class Unk_71024dccf8;
}

namespace uking::ai {

class AssassinNormal : public LandHumEnemyNormal {
    SEAD_RTTI_OVERRIDE(AssassinNormal, LandHumEnemyNormal)
public:
    explicit AssassinNormal(const InitArg& arg);
    ~AssassinNormal() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    void m49(Unk1* out, s32 idx) override;
    s32 m52(s32 idx) override;
    s32 m53() override;
    bool m55() override {
        if (EnemyNormal::m55())
            return true;
        return isCurrentChild("不審物排除後");
    }
    bool m56(Unk2* out, Unk1* info) override;
    void m57(s32 type, Unk2* target) override;
    void m58(s32 type, Unk2* target) override;
    void m59() override;
    void m60(Unk3* out) override;
    void m61(Unk3* out) override;
    void m62(Unk3* result) override;
    bool m63(Unk3* result) override;

    virtual bool m74(Unk2* out, Unk1* info);
    virtual bool m75(const ksys::act::BaseProcLink& link) { return false; }

    // 0x710040ce58
    void sub_710040CE58();
    // 0x710040cf88
    bool sub_710040CF88(ksys::act::Unk_71024dccf8* filter, Unk2* out);
    // 0x710040d048: whether an awareness entry is a reachable target.
    bool sub_710040D048(ksys::act::Unk_7100d78e50* entry);
    // 0x710040d3a8
    void sub_710040D3A8(Unk2* target);

protected:
    ksys::act::BaseProcLink _400;
    sead::Vector3f _410;
};

}  // namespace uking::ai
