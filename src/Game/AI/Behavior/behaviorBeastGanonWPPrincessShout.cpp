#include "Game/AI/Behavior/behaviorBeastGanonWPPrincessShout.h"
#include <prim/seadBitUtil.h>
#include <random/seadGlobalRandom.h>
#include "Game/AI/aiUnk_71025b2d88.h"

namespace uking::behavior {

BeastGanonWPPrincessShout::BeastGanonWPPrincessShout(const InitArg& arg)
    : SimpleAtvUnitOpenSimpleDialog(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops (SafeString member).
BeastGanonWPPrincessShout::~BeastGanonWPPrincessShout() {
    ;
}

bool BeastGanonWPPrincessShout::m6(sead::Heap* heap) {
    return SimpleAtvUnitOpenSimpleDialog::m6(heap);
}

void BeastGanonWPPrincessShout::m7() {
    SimpleAtvUnitOpenSimpleDialog::m7();
}

void BeastGanonWPPrincessShout::m8() {
    SimpleAtvUnitOpenSimpleDialog::m8();
}

void BeastGanonWPPrincessShout::m9() {
    SimpleAtvUnitOpenSimpleDialog::m9();
}

void BeastGanonWPPrincessShout::loadParams() {
    SimpleAtvUnitOpenSimpleDialog::loadParams();
    getStaticParam(&mSingleIdx_s, "SingleIdx");
    getStaticParam(&mlabelName2_s, "labelName2");
    getStaticParam(&mlabelName3_s, "labelName3");
    getStaticParam(&mlabelName4_s, "labelName4");
    getStaticParam(&mlabelName5_s, "labelName5");
    getStaticParam(&mlabelName6_s, "labelName6");
    getStaticParam(&mlabelName7_s, "labelName7");
    getStaticParam(&mlabelName8_s, "labelName8");
    getStaticParam(&mlabelName9_s, "labelName9");
    getStaticParam(&mlabelName10_s, "labelName10");
    getAITreeVariable(&mWeakPointActiveFlag_a, "WeakPointActiveFlag");
}

// NON_MATCHING: the block layout and the loops match; the original compares the active weak point count as
// `cmp w0, #1; b.gt` (we get `cmp #2; b.ge`) and keeps `bic` + `and 0xffff` for the "all labels used" test (we get eor/and)
void BeastGanonWPPrincessShout::m16() {
    _88 = 0;
    auto* weak_points = sead::DynamicCast<Unk_71025b2d88>(
        *static_cast<Unk_71025afb58**>(mWeakPointActiveFlag_a));
    s32 num_active = weak_points ? sead::BitFlagUtil::countOnBit(weak_points->mFlags) : 0;
    if (num_active <= 1) {
        u32 mask = 0;
        for (u32 i = 0; i != u32(*mSingleIdx_s); ++i)
            mask |= 1u << i;
        if (u16(mask & ~_8c.getDirect()) == 0)
            _8c.reset(mask);
        u32 candidates = 1;
        for (s32 i = 0; i < *mSingleIdx_s; ++i) {
            if (_8c.isOffBit(i)) {
                if (sead::GlobalRandom::instance()->getU32(candidates) == 0)
                    _88 = i;
                ++candidates;
            }
        }
    } else {
        u32 mask = 0;
        for (u32 i = 0; i != u32(*mSingleIdx_s); ++i)
            mask |= 1u << i;
        mask = ~mask & 0x3ff;
        if (u16(mask & ~_8c.getDirect()) == 0)
            _8c.reset(mask);
        u32 candidates = 1;
        for (s32 i = *mSingleIdx_s; i < 10; ++i) {
            if (_8c.isOffBit(i)) {
                if (sead::GlobalRandom::instance()->getU32(candidates) == 0)
                    _88 = i;
                ++candidates;
            }
        }
    }
    _8c.setBit(_88);
    SimpleAtvUnitOpenSimpleDialog::m16();
}

const sead::SafeString* BeastGanonWPPrincessShout::m14() {
    switch (_88) {
    case 1:
        return &mlabelName2_s;
    case 2:
        return &mlabelName3_s;
    case 3:
        return &mlabelName4_s;
    case 4:
        return &mlabelName5_s;
    case 5:
        return &mlabelName6_s;
    case 6:
        return &mlabelName7_s;
    case 7:
        return &mlabelName8_s;
    case 8:
        return &mlabelName9_s;
    case 9:
        return &mlabelName10_s;
    default:
        return &mlabelName_s;
    }
}

}  // namespace uking::behavior
