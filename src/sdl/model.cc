#include <cmath>
#include <cstdint>

class Bar {
public:

    Bar(float xPosition, float yPosition);

    const uint8_t BAR_HEIGHT  = 160;
    const uint8_t BAR_WIDTH = 20;
    const uint8_t BAR_SPEED = 3;
    float xPosition = 0;
    float yPosition = 0;
};
