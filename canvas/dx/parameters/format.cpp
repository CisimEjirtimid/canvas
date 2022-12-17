#include "pch.h"

namespace cisim::canvas::dx::parameters
{
    ComponentCount from_mask(uchar mask)
    {
        if (mask & 0b1000)
            return ComponentCount::Four;
        if (mask & 0b0100)
            return ComponentCount::Three;
        if (mask & 0b0010)
            return ComponentCount::Two;
        if (mask & 0b0001)
            return ComponentCount::One;

        return ComponentCount::Unknown;
    }
}
