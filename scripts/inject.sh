#!/bin/bash

export DYLD_LIBRARY_PATH=~/malloc
export DYLD_INSERT_LIBRARIES=libft_malloc.so
export DYLD_FORCE_FLAT_NAMESPACE=1
export LD_LIBRARY_PATH=~/malloc
export LD_INSERT_LIBRARIES=libft_malloc.so
export LD_FORCE_FLAT_NAMESPACE=1
export LD_PRELOAD=libft_malloc.so
