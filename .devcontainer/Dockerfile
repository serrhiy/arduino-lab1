FROM debian:trixie@sha256:f24f7dcd8af3131f29d8d0c6c044cb313cec78ff2db6e0376c798c968dccf898

ARG USER_NAME=dev

RUN apt-get update && \ 
    apt-get install -y --no-install-recommends sudo git python3 pipx && \
    rm -rf /var/lib/apt/lists/*

RUN useradd -ms /bin/bash ${USER_NAME} && \
    echo "${USER_NAME} ALL=(ALL) NOPASSWD:ALL" > /etc/sudoers.d/${USER_NAME}

USER ${USER_NAME}

RUN pipx install platformio && pipx ensurepath
