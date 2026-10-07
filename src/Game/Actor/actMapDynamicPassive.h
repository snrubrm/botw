#pragma once

#include "KingSystem/ActorSystem/Profiles/actDynamicActor.h"

namespace uking::act {

// Name from the CSV (MapDynamicPassive::*; the namespace is a guess). Factory 0x710001c304: new(0xb98) +
// inlined ctor (sets _1c0 = 3). RTTI static 0x71025aea50. A map-placed dynamic actor that keeps the static
// compound instance of its map object in sync (like MapConstPassive).
// TODO: incomplete (m64 not written: it uses unnamed callees).
class MapDynamicPassive : public ksys::act::DynamicActor {
    SEAD_RTTI_OVERRIDE(MapDynamicPassive, ksys::act::DynamicActor)
public:
    explicit MapDynamicPassive(const CreateArg& arg);

    static ksys::act::BaseProc* construct(const CreateArg& arg, sead::Heap* heap);

protected:
    bool prepareInit_(sead::Heap* heap, PrepareArg& arg) override;
    void onPreDeleteStart_(PrepareArg& arg) override;
    void preDelete2_(const PreDeleteArg& arg) override;
    void onEnterDelete_() override;
    bool canWakeUp_() override;

public:
    void m63() override;
    void initMaybe() override;
    void calcMaybe() override;
    void updatePositionMaybe() override;
    void m73() override;
    void m76(ksys::VFR::ScopedDeltaSetter* setter) override;
    void onPlacementObjReset() override;

    /* 0xb90 */ ksys::map::Object* _b90 = nullptr;
};
KSYS_CHECK_SIZE_NX150(MapDynamicPassive, 0xb98);

}  // namespace uking::act
