# Ubuntu Version: plucky - 25.04
ARG UBUNTU_VARIANT="plucky"

FROM ubuntu:${UBUNTU_VARIANT}

# Restate the variant to use it later on in the llvm and cmake installations
ARG UBUNTU_VARIANT

# Create a user matching your host user
ARG USERNAME
ARG USER_UID
ARG USER_GID
ARG FORWARD_LOCAL_USER
RUN if [ "${FORWARD_LOCAL_USER}" = "true" ]; then \
    echo "User: $USERNAME, UID: $USER_UID, GID: $USER_GID"; \
    touch /var/mail/ubuntu && chown ubuntu /var/mail/ubuntu; \
    userdel -r ubuntu || true; \
    if ! getent group $USER_GID >/dev/null; then \
    groupadd --gid $USER_GID $USERNAME; \
    fi; \
    useradd --uid $USER_UID --gid $USER_GID -m -s /bin/bash $USERNAME; \
    echo "$USERNAME ALL=(ALL) NOPASSWD:ALL" > /etc/sudoers.d/$USERNAME; \
    chmod 0440 /etc/sudoers.d/$USERNAME; \
    fi

# Run apt-get update
RUN apt-get update && export DEBIAN_FRONTEND=noninteractive

# Install apt-utils
RUN export DEBIAN_FRONTEND=noninteractive \
    && apt-get install -y --no-install-recommends \
    apt-utils

# Install Common Software from Standard Ubuntu Repo
RUN export DEBIAN_FRONTEND=noninteractive \
    && apt-get install -y --no-install-recommends \
    axel \
    git \
    git-lfs \
    gpg-agent \
    htop \
    nano \
    python3 \
    python3-pip \
    ssh \
    software-properties-common \
    wget


# Add toolchain repo for downloading the wanted version of gcc and g++
RUN add-apt-repository -y ppa:ubuntu-toolchain-r/test

# Add llvm repo for clang
ARG LLVM_VER="19"
ARG LLVM_URL="http://apt.llvm.org/${UBUNTU_VARIANT}/"
ARG LLVM_PKG="llvm-toolchain-${UBUNTU_VARIANT}-${LLVM_VER}"
RUN wget -O - https://apt.llvm.org/llvm-snapshot.gpg.key 2>/dev/null \
    | gpg --dearmor - \
    | tee /etc/apt/trusted.gpg.d/llvm.gpg >/dev/null
RUN echo "deb ${LLVM_URL} ${LLVM_PKG} main" > /etc/apt/sources.list.d/llvm.list

# Add cmake/ccmake's Kitware repo
ARG CMAKE_URL="https://apt.kitware.com/ubuntu/"
RUN CMAKE_PKG="${UBUNTU_VARIANT}" ; \
    if dpkg --compare-versions "$(lsb_release -rs)" gt "24.04"; then \
    CMAKE_PKG="noble" ; \
    fi ; \
    wget -O - https://apt.kitware.com/keys/kitware-archive-latest.asc 2>/dev/null \
    | gpg --dearmor - | tee /etc/apt/trusted.gpg.d/kitware.gpg >/dev/null && \
    echo "deb ${CMAKE_URL} ${CMAKE_PKG} main" > /etc/apt/sources.list.d/kitware.list

# Run apt-get update
RUN apt-get update && export DEBIAN_FRONTEND=noninteractive


# Install gcc, g++ and gdb
ARG GCC_VER="13"
RUN export DEBIAN_FRONTEND=noninteractive \
    && apt-get install -y --no-install-recommends \
    gcc-${GCC_VER} \
    g++-${GCC_VER} \
    gdb

# Set gcc-${GCC_VER} as default gcc (Using toolchain's repo)
RUN update-alternatives --install /usr/bin/gcc gcc $(which gcc-${GCC_VER}) 100
RUN update-alternatives --install /usr/bin/g++ g++ $(which g++-${GCC_VER}) 100


# Install clang, lldb and clang-tidy (Using llvm's repo)
RUN export DEBIAN_FRONTEND=noninteractive \
    && apt-get install -y --no-install-recommends \
    clang-${LLVM_VER} \
    lldb-${LLVM_VER} \
    lld-${LLVM_VER} \
    clangd-${LLVM_VER} \
    llvm-${LLVM_VER}-dev \
    libclang-${LLVM_VER}-dev \
    clang-tidy-${LLVM_VER}

# Set clang-${LLVM_VER} as default clang
RUN update-alternatives --install /usr/bin/clang clang $(which clang-${LLVM_VER}) 100
RUN update-alternatives --install /usr/bin/clang++ clang++ $(which clang++-${LLVM_VER}) 100

# Set the default clang-tidy, so CMake can find it
RUN update-alternatives --install /usr/bin/clang-tidy clang-tidy $(which clang-tidy-${LLVM_VER}) 1


# Install common build tools
RUN export DEBIAN_FRONTEND=noninteractive \
    && apt-get install -y --no-install-recommends \
    cmake \
    cmake-curses-gui \
    make \
    meson \
    ninja-build


# Install CCache, a caching tool for compilers
# https://ccache.dev/
RUN export DEBIAN_FRONTEND=noninteractive \
    && apt-get install -y --no-install-recommends \
    ccache


# Install CppCheck, a C++ static analysis tool
# https://cppcheck.sourceforge.io/
RUN export DEBIAN_FRONTEND=noninteractive \
    && apt-get install -y --no-install-recommends \
    cppcheck


# Install Doxygen, a code documentation tool
# https://www.doxygen.nl/
ARG INSTALL_DOXYGEN=false
RUN if [[ "${INSTALL_DOXYGEN}" == "true" ]]; then \
    apt-get install -y --no-install-recommends doxygen graphviz; \
    else \
    echo "Doxygen not installed by user configuration"; \
    fi


# Install include-what-you-use, a tool for managing C++ headers
# https://github.com/include-what-you-use/include-what-you-use
# The last two commands (`mkdir` and `ln -s`) are to ensure that the Clang include directory is
# available in the expected location for IWYU to function correctly
# as explained at https://github.com/include-what-you-use/include-what-you-use#how-to-install:
# `You need to copy the Clang include directory to the expected location before
#  running (similarly, use include-what-you-use -print-resource-dir to learn
#  exactly where IWYU wants the headers).`
ARG INSTALL_IWYU=true
ENV IWYU=/home/iwyu
ENV IWYU_BUILD=${IWYU}/build
ENV IWYU_SRC=${IWYU}/include-what-you-use
RUN if [[ "${INSTALL_IWYU}" == "true" ]] ; then \
    mkdir -p ${IWYU_BUILD} && \
    git clone --branch clang_${LLVM_VER} \
    https://github.com/include-what-you-use/include-what-you-use.git \
    ${IWYU_SRC} && CC=clang-${LLVM_VER} CXX=clang++-${LLVM_VER} cmake -S ${IWYU_SRC} \
    -B ${IWYU_BUILD} \
    -G "Unix Makefiles" -DCMAKE_PREFIX_PATH=/usr/lib/llvm-${LLVM_VER} && \
    cmake --build ${IWYU_BUILD} -j && \
    cmake --install ${IWYU_BUILD} && \
    mkdir -p $(include-what-you-use -print-resource-dir 2>/dev/null) && \
    ln -s $(readlink -f /usr/lib/clang/${LLVM_VER}/include) \
    $(include-what-you-use -print-resource-dir 2>/dev/null)/include\
    else \
    echo "IWYU not installed by user configuration"; \
    fi


# Install Conan for dependency management
# Notes:
#   1. By default, anything you run in Docker is done as superuser.
#      Conan runs some install commands as superuser, and will prepend `sudo` to
#      these commands, unless `CONAN_SYSREQUIRES_SUDO=0` is in your env variables.
#   2. Some packages request that Conan use the system package manager to install
#      a few dependencies. The flag CONAN_SYSREQUIRES_MODE allows Conan to proceed with these installations;
#      leaving this flag undefined can cause some installation failures.
ARG INSTALL_CONAN=true
RUN if [[ "${INSTALL_CONAN}" == "true" ]] ; then \
    python3 -m pip install --upgrade pip setuptools && \
    python3 -m pip install conan && \
    conan --version; \
    export CONAN_SYSREQUIRES_SUDO=0; \
    export CONAN_SYSREQUIRES_MODE=enabled; \
    else \
    echo "Conan not installed by user configuration"; \
    fi


## Cleanup cached apt data
RUN export DEBIAN_FRONTEND=noninteractive \
    && apt-get autoremove -y --purge \
    && apt-get clean \
    && apt-get autoclean \
    && rm -rf /var/lib/apt/lists/*


CMD ["/bin/bash"]
