FROM gizra/drupal-lamp

ADD . /var/www/html/productivity
WORKDIR /var/www/html/productivity

USER root

# Add a bash script to finalize all
RUN chmod +x /var/www/html/productivity/docker_files/run.sh
ENTRYPOINT ["/var/www/html/productivity/docker_files/run.sh"]

EXPOSE 22 80 3306 4444 8080 9001