#pragma once

namespace aal {

/// Calculates the spatial parameters (distance attenuation, angle, doppler...) of a sound source for each
/// listener, from a SpatialCalculator::Setting.
/// TODO: incomplete. Only the functions that game code calls are declared.
class SpatialCalculator {
public:
    /// Detaches the calculator from its shape; with `reset_position`, also forgets the position/matrix
    /// pointers of the setting. Returns whether a shape was attached.
    bool detachShape(bool reset_position);
};

}  // namespace aal
