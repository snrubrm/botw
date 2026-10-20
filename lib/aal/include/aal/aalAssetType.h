#pragma once

// Known API subset of the SEAD_ENUM_EX wrapper documented in seadEnum.h.
// Enumerator spellings come from that existing source documentation; native
// lookup 0x7100b7906c uses the values 0, 1 and 0xff.
// The enum text API is not modelled here.
namespace aal {
class AssetType {
public:
    // Preserve the ordinary unscoped enum form used by the source macro;
    // no fixed underlying type is asserted.
    enum ValueType { Wave = 0, Stream = 1, Unknown = 0xff };

    // Inline SEAD_ENUM_EX conversion/equality protocol, repeated in
    // SoundSource::setup 0x7100b778e8, SoundController::setAssetInfo
    // 0x7100ba1fb4 and the game asset provider 0x7101060d14.
    AssetType(int value) {
        int index = findRelativeIndex_(static_cast<ValueType>(value));
        if (index == -1)
            index = 0;
        mIdx = index;
    }
    AssetType(ValueType value) : AssetType(static_cast<int>(value)) {}
    bool operator==(ValueType value) const { return mIdx == findRelativeIndex_(value); }
    bool operator!=(ValueType value) const { return mIdx != findRelativeIndex_(value); }
    // 0x7100ba1838: the SEAD_ENUM_EX query reads the indexed value from its shared array.
    int value() const;

private:
    // Maps the sparse enum value to its relative array index.
    static int findRelativeIndex_(ValueType value);
    int mIdx;
};
static_assert(sizeof(AssetType) == 4);
}  // namespace aal
