#!/bin/bash
bash test_standard.sh > test_standard.log
bash test_leaks.sh > test_leaks.log
bash test_sanitize.sh > test_sanitize.log