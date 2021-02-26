/*
 * Copyright (c) 2020-2021 SEMC Team
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 *   1. The origin of this software must not be misrepresented; you must
 *      not claim that you wrote the original software. If you use this
 *      software in a product, an acknowledgment in the product
 *      documentation would be appreciated but is not required.
 *
 *   2. Altered source versions must be plainly marked as such, and must
 *      not be misrepresented as being the original software.
 *
 *   3. This notice may not be removed or altered from any source
 *      distribution.
 */

#include <stddef.h>
#include <stdint.h>
#include <kernel/uart.h>
#include <common/stdio.h>
#include <common/stdlib.h>

void kernel_main(uint32_t r0, uint32_t r1, uint32_t atags)
{
    char buf[256];
    // Declare as unused
    (void) r0;
    (void) r1;
    (void) atags;

    uart_init();
    puts("Hello, kernel World!\n");
    while (1) {
        gets(buf,256);
        puts(buf);
        putc('\n');
    }
}