FROM registry.access.redhat.com/rhel6
RUN  yum install -y git make gcc
RUN  mkdir /mnt/nfs
COPY build-app.sh /tmp
RUN  chmod a+x /tmp/build-app.sh
ENTRYPOINT "/tmp/build-app.sh" 
