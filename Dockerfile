FROM qmkfm/qmk_firmware:latest

ARG UID GID
RUN groupadd -g "$GID" qmk \
    && useradd -lm -s /bin/bash -u "$UID" -g qmk qmk

USER qmk
WORKDIR /home/qmk/work

CMD ["qmk", "compile", "-kb", "all", "-km", "default"]
