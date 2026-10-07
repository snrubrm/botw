#pragma once

#include "Game/AI/aiUnk_7100FFDFDC.h"
#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class BeastGanonBgmCtrl : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(BeastGanonBgmCtrl, ksys::act::ai::Behavior)
public:
    explicit BeastGanonBgmCtrl(const InitArg& arg);
    ~BeastGanonBgmCtrl() override;
    bool hasUpdateForPreDeleteCb() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;
    bool updateForPreDelete() override;

    // inline-only in the original; name is a guess (the same sequence is inlined into m7 and m8).
    void applyLevelMaybe() {
        if (*mLevel_s != -1) {
            Unk_BgmLevel level;
            level.value = *mLevel_s == 3 ? 2 : *mLevel_s == 2;
            if (auto* bgm = sub_7100FFE468())
                bgm->sub_710100FE0C(&level);
        } else if (auto* bgm = sub_7100FFE468()) {
            if (!bgm->m10())
                bgm->sub_710100FF38();
        }
        _30 = true;
    }

    /* 0x28 */ const int* mLevel_s{};
    /* 0x30 */ bool _30 = false;
};
KSYS_CHECK_SIZE_NX150(BeastGanonBgmCtrl, 0x38);

}  // namespace uking::behavior
