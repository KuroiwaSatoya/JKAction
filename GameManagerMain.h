#pragma once

class GameManager {
public:
    virtual ~GameManager() = default;
    virtual void Update() = 0;        // �������z�֐�
    virtual void Display() = 0;       // �������z�֐�
};

