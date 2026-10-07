#pragma once

#include <basis/seadTypes.h>
#include <prim/seadEnum.h>
#include <nn/atk/BiquadFilterCallback.h>

namespace sead {
class Heap;
}

namespace aal {

/// Registers the biquad filter presets (low pass filter tables) of the audio engine. TODO: incomplete.
class BiquadFilterPreset {
public:
    SEAD_ENUM(PresetType, Unk0);
    s32 getAtkRegisterNum(PresetType preset) const;

    /// Provides the coefficients of a filter by looking up a table with the filter value in [0, 1].
    class BiquadFilterCallback : public nn::atk::IBiquadFilterCallback {
    public:
        ~BiquadFilterCallback() override;

        void GetCoefficients(nn::atk::BiquadFilterCoefficients* coefficients, int type,
                             f32 value) const override;
        virtual void getCofficientsImpl_(nn::atk::BiquadFilterCoefficients* coefficients, int type,
                                         f32 value) const;

    protected:
        const nn::atk::BiquadFilterCoefficients* mTable;
        s32 mTableSize;
    };

    /// The value is weighted: low values change the filter less.
    class BiquadFilterCallbackWithWeight : public BiquadFilterCallback {
    public:
        ~BiquadFilterCallbackWithWeight() override = default;

        void getCofficientsImpl_(nn::atk::BiquadFilterCoefficients* coefficients, int type,
                                 f32 value) const override;
    };

    BiquadFilterPreset();
    virtual ~BiquadFilterPreset();

    void initialize(s32 num, sead::Heap* heap);
    void finalize();

private:
    void* _8;
    void* _10;
    void* _18;
    void* _20;
    void* _28;
};
static_assert(sizeof(BiquadFilterPreset) == 0x30, "aal::BiquadFilterPreset size mismatch");

}  // namespace aal
