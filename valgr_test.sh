#!/bin/bash
valgrind --leak-check=full --gen-suppressions=all --suppressions=sdl.supp --track-origins=yes --log-file=valgrind-output.out ./prog.out
