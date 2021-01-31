/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-01-30     imgcr       the first version
 */
#ifndef COMPONENTS_SCREEN_HXX_
#define COMPONENTS_SCREEN_HXX_
#include "colors.hxx"

class Screen {
public:
    virtual int getWidth() = 0;
    virtual int getHeight() = 0;
    virtual Colors::Rgb getPixel(int x, int y) = 0;
    virtual void setPixel(Colors::Rgb color, int x, int y) = 0;
    virtual void flush() = 0;
};



#endif /* COMPONENTS_SCREEN_HXX_ */
