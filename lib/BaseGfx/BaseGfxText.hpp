/* MIT License
 *
 * Copyright (c) 2019 - 2022 Andreas Merkle <web@blue-andi.de>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/*******************************************************************************
    DESCRIPTION
*******************************************************************************/
/**
 * @brief  Base GFX text
 * @author Andreas Merkle <web@blue-andi.de>
 *
 * @addtogroup gfx
 *
 * @{
 */

#ifndef __BASE_GFX_TEXT_HPP__
#define __BASE_GFX_TEXT_HPP__

/******************************************************************************
 * Compile Switches
 *****************************************************************************/

/******************************************************************************
 * Includes
 *****************************************************************************/
#include <stdint.h>
#include "BaseGfx.hpp"
#include "BaseFont.hpp"

/******************************************************************************
 * Macros
 *****************************************************************************/

/******************************************************************************
 * Types and Classes
 *****************************************************************************/

/**
 * The BaseGfxText class provides generic text handling, based on the configured
 * font.
 * 
 * Features:
 * - Provides a text cursor
 * - Text wrap around
 */
template < typename TColor >
class BaseGfxText
{
public:

    /**
     * Constructs a base text object, without graphical font representation.
     * Note, until no GFXfont is assigned, it can not draw any character.
     */
    BaseGfxText() :
        m_cursorX(0),
        m_cursorY(0),
        m_textColor(0U),
        m_isTextWrapEnabled(false),
        m_font()
    {
    }

    /**
     * Constructs a text object by copy.
     * 
     * @param[in] text  Base text, which to copy.
     */
    BaseGfxText(const BaseGfxText& text) :
        m_cursorX(text.m_cursorX),
        m_cursorY(text.m_cursorY),
        m_textColor(text.m_textColor),
        m_isTextWrapEnabled(text.m_isTextWrapEnabled),
        m_font(text.m_font)
    {
    }

    /**
     * Constructs a base text with the given GFXfont.
     * 
     * @param[in] gfxFont   GFXfont
     * @param[in] color     Text color
     */
    BaseGfxText(const GFXfont* gfxFont, const TColor& color = 0U) :
        m_cursorX(0),
        m_cursorY(0),
        m_textColor(color),
        m_isTextWrapEnabled(false),
        m_font(gfxFont)
    {
    }

    /**
     * Destroys the base text.
     */
    ~BaseGfxText()
    {
    }

    /**
     * Get cursor position.
     *
     * @param[out] x x-coordinate
     * @param[out] y y-coordinate
     */
    void getTextCursorPos(int16_t& x, int16_t& y) const
    {
        x = m_cursorX;
        y = m_cursorY;
    }

    /**
     * Get cursor x-position.
     *
     * @return Cursor x-position
     */
    int16_t getTextCursorPosX() const
    {
        return m_cursorX;
    }

    /**
     * Get cursor y-position.
     *
     * @return Cursor y-position
     */
    int16_t getTextCursorPosY() const
    {
        return m_cursorY;
    }

    /**
     * Move text cursor to position.
     *
     * @param[in] x x-coordinate
     * @param[in] y y-coordinate
     */
    void setTextCursorPos(int16_t x, int16_t y)
    {
        m_cursorX = x;
        m_cursorY = y;
    }

    /**
     * Get text color.
     *
     * @return Text color
     */
    TColor getTextColor() const
    {
        return m_textColor;
    }

    /**
     * Set text color.
     *
     * @param[in] color Text color
     */
    void setTextColor(const TColor& color)
    {
        m_textColor = color;
    }

    /**
     * Is text wrap around enabled?
     *
     * @return If text wrap around is enabled, it will return true otherwise false.
     */
    bool isTextWrapEnabled() const
    {
        return m_isTextWrapEnabled;
    }

    /**
     * Set text wrap around behaviour.
     *
     * @param[in] isEnabled Enable (true) wrap around or disable (false) it
     */
    void setTextWrap(bool isEnabled)
    {
        m_isTextWrapEnabled = isEnabled;
    }

    /**
     * Get font.
     *
     * @return font
     */
    BaseFont<TColor>& getFont()
    {
        return m_font;
    }

    /**
     * Set GFXfont.
     *
     * @param[in] gfxFont   GFXfont
     */
    void setFont(const BaseFont<TColor>& font)
    {
        m_font = font;
    }

    /**
     * Get bounding box of text.
     *
     * @param[out]  width       Width in pixel
     * @param[out]  height      Height in pixel
     * @param[in]   text        Text
     * @param[out]  boxWidth    Bounding box width in pixel
     * @param[out]  boxHeight   Bounding box height in pixel
     * 
     * @return If successful, it will return true otherwise false.
     */
    bool getTextBoundingBox(uint16_t width, uint16_t height, const char* text, uint16_t& boxWidth, uint16_t& boxHeight) const
    {
        bool status = false;

        if ((nullptr != text) &&
            (nullptr != m_font.getGfxFont()))
        {
            size_t      idx         = 0U;
            uint16_t    lineWidth   = 0U;

            boxWidth   = 0U;
            boxHeight  = 0U;

            while('\0' != text[idx])
            {
                uint16_t charWidth  = 0U;
                uint16_t charHeight = 0U;

                if ('\n' == text[idx])
                {
                    if (boxWidth < lineWidth)
                    {
                        boxWidth = lineWidth;
                    }

                    lineWidth = 0U;
                    boxHeight += m_font.getHeight();
                }
                else if (true == m_font.getCharBoundingBox(text[idx], charWidth, charHeight))
                {
                    if (0U == idx)
                    {
                        boxHeight += charHeight;
                    }

                    /* If text wrap around is enabled and the character is clipping,
                     * jump to the next line.
                     */
                    if (true == m_isTextWrapEnabled)
                    {
                        if (width < (lineWidth + charWidth))
                        {
                            if (boxWidth < lineWidth)
                            {
                                boxWidth = lineWidth;
                            }

                            lineWidth = 0U;
                            boxHeight += charHeight;
                        }
                    }

                    lineWidth += charWidth;
                }
                else
                {
                    ;
                }

                ++idx;
            }

            if (boxWidth < lineWidth)
            {
                boxWidth = lineWidth;
            }

            status = true;
        }

        return status;
    }

    /**
     * Draw single character at current cursor position. The cursor is
     * automatically moved to the new position. Wrap around handling is
     * performed if configured.
     * 
     * A newline will place the cursor on the begin of the next line.
     *
     * @param[in] gfx           Graphics interface
     * @param[in] singleChar    Single character which to draw
     */
    void drawChar(BaseGfx<TColor>& gfx, char singleChar)
    {
        if (nullptr == m_font.getGfxFont())
        {
            return;
        }

        /* If text wrap around is enabled and the character is clipping,
         * jump to the next line.
         */
        if (true == m_isTextWrapEnabled)
        {
            uint16_t charBoxWidth   = 0U;
            uint16_t charBoxHeight  = 0U;

            if (true == m_font.getCharBoundingBox(singleChar, charBoxWidth, charBoxHeight))
            {
                if (gfx.getWidth() < (m_cursorX + charBoxWidth))
                {
                    m_cursorX = 0;
                    m_cursorY += charBoxHeight;
                }
            }
        }

        m_font.drawChar(gfx, m_cursorX, m_cursorY, singleChar, m_textColor);
    }

    /**
     * Draw a text at given cursor position.
     *
     * @param[in] gfx   Graphics interface
     * @param[in] text  Text which to draw
     */
    void drawText(BaseGfx<TColor>& gfx, const char* text)
    {
        size_t idx = 0U;

        if (nullptr == m_font)
        {
            return;
        }

        while('\0' != text[idx])
        {
            drawChar(gfx, text[idx]);
            ++idx;
        }
    }

private:

    int16_t             m_cursorX;              /**< Cursor x-coordinate */
    int16_t             m_cursorY;              /**< Cursor y-coordinate */
    TColor              m_textColor;            /**< Text color */
    bool                m_isTextWrapEnabled;    /**< Is text wrap around enabled or not? */
    BaseFont<TColor>    m_font;                 /**< The graphical font, which to use. */

};

/******************************************************************************
 * Functions
 *****************************************************************************/

#endif  /* __BASE_GFX_TEXT_HPP__ */

/** @} */