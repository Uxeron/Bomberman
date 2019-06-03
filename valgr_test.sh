#!/bin/bash
valgrind --leak-check=full --suppressions=sdl.supp --track-origins=yes --log-file=valgrind-output.out ./prog.out
