# Define global arguments
ARG DEBIAN_FRONTEND="noninteractive"
ARG UID=1000
ARG USER=root

# POSIX compatible (Linux/Unix) base image
FROM debian:bullseye-slim

# Import global arguments
ARG DEBIAN_FRONTEND
ARG UID
ARG USER

# Define local arguments

# Create Non-Root User If Needed (CI will use root user)
RUN ["dash", "-c", "\
    if [ \"$USER\" != \"root\" ]; \
    then \
    addgroup \
     --gid ${UID} \
     \"${USER}\" \
 && adduser \
     --disabled-password \
     --gecos \"\" \
     --ingroup \"${USER}\" \
     --uid ${UID} \
     \"${USER}\" \
 && usermod \
     --append \
     --groups \"dialout,plugdev\" \
     \"${USER}\"; \
    fi \
"]
ENV PATH="/home/${USER}/.local/bin:${PATH}"

# Step 1. Install Prerequisites
# https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/linux-macos-setup.html#step-1-install-prerequisites
RUN ["dash", "-c", "\
    apt-get update --quiet \
 && apt-get install --assume-yes --no-install-recommends --quiet \
     bison \
     build-essential \
     catch2 \
     ccache \
     cmake \
     dfu-util \
     flex \
     gdb \
     git \
     gnupg \
     gperf \
     libffi-dev \
     libpython2.7 \
     libssl-dev \
     libusb-1.0-0 \
     nano \
     ninja-build \
     python3 \
     python3-pip \
     python3-setuptools \
     python3-venv \
     udev \
     valgrind \
     wget \
 && apt-get clean \
 && apt-get purge \
 && rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/* \
"]

# Install IDF as non-root user
WORKDIR /home/${USER}/
USER ${USER}

# Step 2. Get ESP-IDF
# https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/linux-macos-setup.html#step-2-get-esp-idf
# VERY important to lock to a specific commit on a specific version here.
# Pinned to v5.3 https://github.com/espressif/esp-idf/releases/tag/v5.3
RUN ["dash", "-c", "\
    mkdir esp \
 && cd esp/ \
 && git clone --recursive https://github.com/espressif/esp-idf.git --branch v5.3 ./idf  \
 && cd idf \
"]

# Step 2a. Apply IDF patches (optional)
# The following is an example that was necessary to fix a linker error in a previous version of IDF.
# You can use it as a template for your own patches.
# COPY ./idf_patches/bt_linker.diff /home/${USER}/esp/idf/bt_linker.diff
# RUN ["dash", "-c", "\
#     cd esp/idf \
#  && patch -p1 < bt_linker.diff \
#  && rm bt_linker.diff \
# "]


# Step 3. Set up the tools
# Change the target to match the specific chip you are using in your project
ENV IDF_TARGET="esp32"
ENV IDF_PATH="/home/${USER}/esp/idf"
ENV IDF_TOOLS_PATH="/home/${USER}/.espressif"

RUN ["dash", "-c", "\
    cd ./esp/idf \
 && ./install.sh \
"]

# Step 4. Set up the environment variables
# https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/linux-macos-setup.html#step-4-set-up-the-environment-variables
RUN echo "source /home/${USER}/esp/idf/export.sh" >> /home/${USER}/.bashrc
ENV LC_ALL=C