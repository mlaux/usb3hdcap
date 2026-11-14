#!/bin/bash
cd "$(dirname "$0")" || exit 1

CHECKPATCH="${CHECKPATCH:-/lib/modules/$(uname -r)/build/scripts/checkpatch.pl}"

exec "$CHECKPATCH" --no-tree --file --terse --show-types \
	--ignore SPDX_LICENSE_TAG,FILE_PATH_CHANGES \
	"$@" usb3hdcap*.c usb3hdcap*.h
