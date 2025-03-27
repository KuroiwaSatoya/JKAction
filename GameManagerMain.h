#pragma once

class GameManager {
public:
    virtual ~GameManager() = default;
    virtual void Update() = 0;        // ƒˆ‰¼‘zŠÖ”
    virtual void Display() = 0;       // ƒˆ‰¼‘zŠÖ”
};

