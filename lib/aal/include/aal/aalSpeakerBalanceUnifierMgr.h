#pragma once

namespace aal {

class SpeakerBalanceUnifier;

/// Manages the speaker balance unifiers. TODO: only setupInteriorSize is declared.
class SpeakerBalanceUnifierMgr {
public:
    /// 0x7100b942f0 (declared only)
    void setupInteriorSize();
    /// 0x7100b945dc (declared only)
    void freeSpeakerBalanceUnifier(SpeakerBalanceUnifier* unifier);
};

}  // namespace aal
