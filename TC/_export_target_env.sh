export ARCH=target

export TET_INSTALL_PATH=/opt/home/root/TETware  # path to mount
export TET_TARGET_PATH=$TET_INSTALL_PATH
export PATH=$TET_TARGET_PATH/bin:$PATH
export LD_LIBRARY_PATH=$TET_TARGET_PATH/lib/tet3:$LD_LIBRARY_PATH

export TET_ROOT=$TET_TARGET_PATH

set $(pwd)
export TET_SUITE_ROOT=$1

set $(date +%s)
FILE_NAME_EXTENSION=$1
