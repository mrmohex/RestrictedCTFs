FROM ubuntu:24.04

RUN apt-get update && \
    apt-get install -y --no-install-recommends \
        bash coreutils findutils file gawk wget net-tools sudo nano \
        gcc libc6-dev \
    && rm -rf /var/lib/apt/lists/*

RUN useradd -m -s /bin/bash mohex

RUN mkdir -p /opt/allowed

RUN echo "mohex ALL=(root) NOPASSWD: /usr/bin/whoami" >> /etc/sudoers


RUN ln -s /usr/bin/ls /opt/allowed/ls && \
    ln -s /usr/bin/awk /opt/allowed/awk && \
    ln -s /usr/bin/id /opt/allowed/id && \
    ln -s /usr/bin/whoami /opt/allowed/whoami

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

RUN mkdir -p /root/secret && chmod 700 /root/secret


RUN chmod 664 /etc/passwd && \
    chown mohex:mohex /etc/passwd

COPY --chmod=700 entrypoint.sh /entrypoint.sh
COPY verify.c /tmp/verify.c

RUN gcc -O2 -o /home/mohex/verify /tmp/verify.c && \
    chown root:root /home/mohex/verify && \
    chmod 4755 /home/mohex/verify

ENTRYPOINT ["/entrypoint.sh"]
