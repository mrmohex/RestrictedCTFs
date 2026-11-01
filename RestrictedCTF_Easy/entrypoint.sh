#!/bin/bash
set -e

if [ -z "$FLAG" ]; then
    echo "FLAG env var is required" >&2
    exit 1
fi

printf '%s\n' "$FLAG" > /root/secret/root.txt
chmod 600 /root/secret/root.txt
unset FLAG

cd /home/mohex
exec setpriv --reuid=mohex --regid=mohex --init-groups \
    env -i HOME=/home/mohex USER=mohex TERM="${TERM:-xterm}" HOSTNAME="$HOSTNAME" \
    /usr/local/bin/restricted-entry