#pragma once

namespace drawIt_intern {

class touch {
   public:
    virtual bool touched(uint16_t x, uint16_t y) = 0;

    void setTouch(bool activated) {
        _touch = activated;
    }

    bool getTouch() {
        return _touch;
    }

   protected:
    bool _touch = true;
};

}  // namespace drawIt_intern