/*
    simbot is a simulator of a 2 wheels differential drive robot.
    Copyright (C) 2014-2015 Roberto Cometti <roberto@pagefault.io>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

    You can find the full license document in the root of this repository
    or online at <http://www.gnu.org/licenses/gpl-2.0.html>
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>
#include <math.h>
#include <assert.h>
#include <float.h>
#include <stdbool.h>
#include <time.h>

#include "scenario.h"
#include "robot.h"
#include "common.h"
#include "controller.h"

int main()
{
    printf("%s: This is SimBot!\n", __func__);

    init_scenario();
    init_robot();

    struct timespec timer_start;
    struct timespec timer_stop;

    while(is_window_open())
    {
        clock_gettime(CLOCK_REALTIME, &timer_start);

        update_robot_state();

        draw_window();

        draw_robot(get_robot_position(), get_robot_heading());

        commit_window();
        process_events();

        clock_gettime(CLOCK_REALTIME, &timer_stop);

        struct timespec elapsed_time = get_elapsed_time(timer_start, timer_stop);

        bound_frame_time(&elapsed_time);
    }

    terminate_window();
}

