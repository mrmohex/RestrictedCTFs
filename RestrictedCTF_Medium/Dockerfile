
FROM ubuntu:24.04

RUN apt-get update && \
    apt-get install -y --no-install-recommends \
        bash coreutils findutils file gawk wget net-tools sudo nano \
        gcc libc6-dev less \
    && rm -rf /var/lib/apt/lists/*

RUN useradd -m -s /bin/bash mohex

RUN mkdir -p /opt/allowed

RUN ln -s /usr/bin/ls /opt/allowed/ls && \
    ln -s /usr/bin/id /opt/allowed/id && \
    ln -s /usr/bin/echo /opt/allowed/echo && \
    ln -s /usr/bin/file /opt/allowed/file && \
    ln -s /usr/bin/less /opt/allowed/less && \
    ln -s /usr/bin/whoami /opt/allowed/whoami && \
    ln -s /usr/bin/su /opt/allowed/su

RUN printf '%s\n' \
    '#!/bin/bash' \
    'for arg in "$@"; do' \
    '    case "$arg" in' \
    '        -exec|-execdir|-ok|-okdir)' \
    '            echo "find: option not permitted" >&2' \
    '            exit 1' \
    '            ;;' \
    '    esac' \
    'done' \
    'exec /usr/bin/find "$@"' \
    > /opt/allowed/find && \
    chmod 755 /opt/allowed/find

COPY --chmod=644 banner.txt /opt/banner.txt

RUN printf '%s\n' \
    '#!/bin/bash' \
    'printf "\033[1;31m"; /bin/cat /opt/banner.txt; printf "\033[0m\n"' \
    'export PATH=/opt/allowed' \
    'export PS1="\u@\h:\w\$ "' \
    'exec /bin/rbash --norc --noprofile' \
    > /usr/local/bin/restricted-entry && \
    chmod 755 /usr/local/bin/restricted-entry

RUN echo 'Welcome to the restricted CTF lab' > /home/mohex/welcome.txt && \
    chown -R root:root /opt/allowed && \
    chmod 755 /opt/allowed

RUN mkdir -p /root/secret && \
    chmod 700 /root/secret

# IMPORTANT: Remove the old passwd misconfiguration
RUN chown root:root /etc/passwd && \
    chmod 644 /etc/passwd

RUN mkdir -p /opt/data && \
    chown mohex:mohex /opt/data && \
    chmod 755 /opt/data && \
    echo "Welcome to Secure Reader" > /opt/data/welcome.txt && \
    chown mohex:mohex /opt/data/welcome.txt

COPY --chmod=700 entrypoint.sh /entrypoint.sh

COPY verify.c /tmp/verify.c

RUN gcc -O2 -o /home/mohex/verify /tmp/verify.c && \
    chown root:root /home/mohex/verify && \
    chmod 4755 /home/mohex/verify && \
    rm /tmp/verify.c

COPY secure-reader.c /tmp/secure-reader.c

RUN gcc -O2 -Wall -Wextra \
    -o /usr/local/bin/secure-reader \
    /tmp/secure-reader.c && \
    chown root:root /usr/local/bin/secure-reader && \
    chmod 4755 /usr/local/bin/secure-reader && \
    rm /tmp/secure-reader.c

ENTRYPOINT ["/entrypoint.sh"]
