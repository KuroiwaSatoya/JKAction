#pragma once

class GameManagerMain {
public:
    virtual ~GameManagerMain() = default;
    virtual void Update() = 0;        // �������z�֐�
    virtual void Display() = 0;       // �������z�֐�
};

