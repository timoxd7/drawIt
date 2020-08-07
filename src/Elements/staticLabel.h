#pragma once

namespace drawIt {

/**
 * @brief A Label saved in fixed-size storage, for Example in Stack. Labels longer than the fixed Size will be truncated.
 * 
 * @tparam D The Display Class
 * @tparam FontClass Class of the Font
 * @tparam maxCharCount Maximum number of Chars in the Label (excluding the null-terminator)
 */
template <class D, class FontClass, uint16_t maxCharCount>
class staticLabel : public drawIt_intern::visuals, public drawIt_intern::color {
   public:
    /**
     * @brief Construct a new label object
     * 
     * @param _display The Display
     * @param x_origin Origin = upper left of the label, x
     * @param y_origin Origin = upper left of the label, y
     * @param x_length Length of the new draw rect which is placed over the text to cover up the things underneath
     * @param y_length Length of the new draw rect which is placed over the text to cover up the things underneath
     */
    staticLabel(D& dsp, uint16_t x_origin = 0, uint16_t y_origin = 0, uint16_t x_length = 0, uint16_t y_length = 0)
        : _display(dsp) {
        this->changeOrigin(x_origin, y_origin);
        this->changeLength(x_length, y_length);
        this->setVisibility(true);
        _label[0] = '\0';
    }

    void draw() {
        undraw();

        _display.setCursor(this->_origin.x, this->_origin.y);
        
        if (_fontSet)
            _display.setFont(_font);
        
        if (_textSizeSet)
            _display.setTextSize(_textSize);
        
        _display.setTextColor(this->_color.outline);

        _display.print(_label);
    }

    void undraw() {
        if (_autoSize.active) {
            size_t labelLength = strlen(_label);
            this->changeLength(_autoSize.width * labelLength, _autoSize.height);
        }

        _display.fillRect(this->_origin.x, this->_origin.y, this->_length.x, this->_length.y, this->_color.background);
    }

    /**
     * @brief Set the Label. If the String is too long, the rest gets cut off.
     * 
     * @param newLabel 
     */
    void setLabel(const char* newLabel) {
        size_t newLabelSize = strlen(newLabel);

        if (newLabelSize > maxCharCount) {
            memcpy(_label, newLabel, maxCharCount * sizeof(char));
            _label[maxCharCount] = '\0';
        } else {
            strcpy(_label, newLabel);
        }
    }

    const char* getLabel() {
        return _label;
    }

    /**
     * @brief Automatically set the size (of the "re-draw-box") by font size
     * 
     */
    void autoSizeByFont(bool active, uint16_t fontHeight, uint16_t singleCharWidth) {
        _autoSize.active = active;
        _autoSize.height = fontHeight;
        _autoSize.width = singleCharWidth;
    }

    /**
     * @brief Disable the automatic size-calculation based on given font size
     * 
     */
    void disableAutoSize() {
        _autoSize.active = false;
    }

    void setFont(FontClass font) {
        _fontSet = true;
        _font = font;
    }

    void setTextSize(uint16_t textSize) {
        _textSizeSet = true;
        _textSize = textSize;
    }

   protected:
    D& _display;
    char _label[maxCharCount + 1];  // +1 for \0

    bool _fontSet = false;
    FontClass _font;

    bool _textSizeSet = false;
    uint16_t _textSize;

    struct {
        bool active = false;
        uint16_t width = 0;
        uint16_t height = 0;
    } _autoSize;
};

}  // namespace drawIt