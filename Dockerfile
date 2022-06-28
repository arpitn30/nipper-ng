FROM gcc:9.5.0-buster as build

ARG WORKDIR_NAME=workspace

WORKDIR /$WORKDIR_NAME

COPY 0.11.10/ .

RUN make all

FROM debian:buster-20220622-slim

ARG WORKDIR_NAME=workspace

COPY --from=build --chown=root:root /$WORKDIR_NAME/nipper /usr/bin/
COPY --from=build --chown=root:root /$WORKDIR_NAME/nipper.conf /etc/
COPY --from=build --chown=root:root /$WORKDIR_NAME/man/nipper.1 /usr/share/man/man1/nipper.1
COPY --from=build --chown=root:root /$WORKDIR_NAME/man/nipper.conf.5 /usr/share/man/man5/nipper.conf.5

ENTRYPOINT [ "nipper" ]
