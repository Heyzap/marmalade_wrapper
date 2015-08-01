#!/usr/bin/env python
# coding=utf-8
import os
import sys

exe = '/Applications/Marmalade.app/Contents/s3e/bin/s3e'
if os.name == 'nt':
    exe += '.bat'

cmd = list(sys.argv)
cmd[0] = exe

cmd.append('-via:"/Users/monroe/dev/marmalade_wrapper/heyzaptest/build_heyzaptest_scons_aarch64/heyzaptest_gcc_aarch64_release.via"')
os.execvp(cmd[0], cmd)
