#@# vim: set filetype=dockerfile:
# Copyright (c) Microsoft Corporation.
# Licensed under the MIT License.

FROM ubuntu/squid
LABEL maintainer "Larry Osterman<github.com/LarryOsterman>"

ENV NGINX_VERSION 1.23.1

##
# dependent packages for docker build
##

WORKDIR /tmp

RUN apt-get -y update 

##
# application deployment
##

WORKDIR /

COPY ./squid.conf /etc/squid/squid.conf
COPY ./proxypasswd /etc/squid/passwords

EXPOSE 3129

STOPSIGNAL SIGTERM

ENTRYPOINT squid -f /etc/squid/squid.conf && sleep 10 && tail -f /var/log/squid/access.log
