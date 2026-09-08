FROM debian:trixie@sha256:f24f7dcd8af3131f29d8d0c6c044cb313cec78ff2db6e0376c798c968dccf898

ARG USER_NAME=dev
ARG LLVM_VERSION=21

RUN apt-get update && \ 
    apt-get install -y --no-install-recommends sudo git python3 pipx clang-format-${LLVM_VERSION} && \
    ln -sf /usr/bin/clang-format-${LLVM_VERSION} /usr/local/bin/clang-format && \
    rm -rf /var/lib/apt/lists/*

RUN useradd -ms /bin/bash ${USER_NAME} && \
    echo "${USER_NAME} ALL=(ALL) NOPASSWD:ALL" > /etc/sudoers.d/${USER_NAME}

USER ${USER_NAME}

RUN pipx install platformio && pipx ensurepath
