#ifndef DRIVE_H
#define DRIVE_H
#include "hardware.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "queuesys.h"
#include "timer.h"
#include "buttons.h"

int drive_lift();
int drive_to_first();

#endif