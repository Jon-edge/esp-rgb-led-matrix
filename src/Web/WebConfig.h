/* MIT License
 *
 * Copyright (c) 2019 Andreas Merkle <web@blue-andi.de>
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
@brief  WebConfig
@author Andreas Merkle <web@blue-andi.de>

@section desc Description
This module provides web related configurations.

*******************************************************************************/
/** @defgroup webconfig WebConfig
 * This module provides web related configurations.
 *
 * @{
 */

#ifndef __WEBCONFIG_H__
#define __WEBCONFIG_H__

/******************************************************************************
 * Compile Switches
 *****************************************************************************/

/******************************************************************************
 * Includes
 *****************************************************************************/

namespace WebConfig
{

/******************************************************************************
 * Constants
 *****************************************************************************/

/** Web server port */
static const uint32_t   WEBSERVER_PORT          = 80u;

/** Project title, used by the web pages. */
static const char       PROJECT_TITLE[]         = "esp-rgb-led-matrix";

/** Web server login user */
static const char       WEB_LOGIN_USER[]        = "luke";

/** Web server login password */
static const char       WEB_LOGIN_PASSWORD[]    = "skywalker";

/******************************************************************************
 * Macros
 *****************************************************************************/

/******************************************************************************
 * Types and Classes
 *****************************************************************************/

/******************************************************************************
 * Functions
 *****************************************************************************/

}

#endif  /* __WEBCONFIG_H__ */

/** @} */