FROM registry.access.redhat.com/rhel6
RUN cp /mnt/nfs/app /bin
ENTRYPOINT /bin/app
