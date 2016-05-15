#!/usr/bin/env bash

# Configure apache2.
echo -e "\n [RUN] Configure apache2."
cp docker_files/default.apache2.conf /etc/apache2/apache2.conf
service apache2 restart

# Start MySQL.
echo -e "\n [RUN] Start MySQL."
service mysql start

# Before install.
echo "\r\n [RUN] Updating system ...\r\n"
apt-get update
echo -e "\n [RUN] Composer self-update."
composer self-update

# Install NodeJS
echo -e "\n [RUN] Install NodeJS."
curl -sL https://deb.nodesource.com/setup_5.x | bash -
apt-get install -y nodejs

# Install Sass and Compass for Grunt to work.
echo -e "\n [RUN] Install Compass and Sass"
gem install compass

# Install Grunt & Bower.
echo -e "\n [RUN] Install Grunt."
npm install -g grunt-cli
echo -e "\n [RUN] Install Bower."
npm install -g bower

# Install php packages required for running a web server from drush on php 5.3
echo -e "\n [RUN] Install php packages."
apt-get install -y --force-yes php5-cgi php5-mysql

# Install Drush & create alias.
echo -e "\n [RUN] Install Drush."
export PATH="$HOME/.composer/vendor/bin:$PATH"
composer global require drush/drush:7.*
cd /var/www/html/productivity
mkdir ~/.drush/
cp docker_files/aliases.drushrc.php ~/.drush/aliases.drushrc.php
source /root/.bashrc

# Installation profile.
echo -e "\n [RUN] Installation profile."
cp default.config.sh config.sh
./install -dy

# Install Firefox (iceweasel)
echo -e "\n [RUN] Installing Firefox."
apt-get update
apt-get -y install iceweasel

# Install Selenium.
echo -e "\n [RUN] Installing Selenium."
# Create folder to place selenium in
echo -e "\n [RUN] Creating folder to place selenium in.\n"
mkdir ~/selenium
cd ~/selenium

# Get Selenium and install headless Java runtime
echo -e "\n [RUN] Installing Selenium and headless Java runtime.\n"
wget http://selenium-release.storage.googleapis.com/2.53/selenium-server-standalone-2.53.0.jar
cd /var/www/html/productivity/productivity
apt-get install openjdk-7-jre-headless -y

# Install headless GUI for browser.'Xvfb is a display server that performs graphical operations in memory'
echo -e "\n [RUN] Installing XVFB (headless GUI for Firefox).\n"
apt-get install xvfb -y

# Install Behat for backend.
echo -e "\n [RUN] Install Behat for back end."
cd /var/www/html/productivity/productivity/behat
curl -sS https://getcomposer.org/installer | php
php composer.phar update
cp behat.local.docker.yml behat.local.yml
cd ../..

# Install client and Behat for client
echo -e "\n [RUN] Install client and Behat for client."
cd client
npm cache clean
npm install
bower install --allow-root
cp config.docker.json config.json
cd ../behat
cp behat.local.docker.yml behat.local.yml
composer install --prefer-source
cd ..

# Start up Selenium server
echo -e "\n [RUN] Starting up Selenium server.\n"
DISPLAY=:1 xvfb-run java -jar ~/selenium/selenium-server-standalone-2.53.0.jar > ~/sel.log 2>&1 &

#Start Grunt server.
echo -e "\n [RUN] Starting Grunt server.\n"
cd client
grunt serve > ~/grunt.log 2>&1 &

echo -e "\n [WAIT] Servers needs some time to start...\n"
# Wait for Grunt to finish loading.
until $(curl --output /dev/null --silent --head --fail http://127.0.0.1:9001/); do sleep 1; echo '.'; done
echo -e "\nOkay."

# Output server logs:
echo -e "\n [RUN] Look at my Grunt log: \n"
cat ~/grunt.log
echo -e "\n [RUN] Look at my Selenium log: \n"
cat ~/sel.log

cd /var/www/html/productivity

# Run Behat tests for the client.
echo -e "\n [RUN] Start client tests.\n"
cd behat
./bin/behat --tags=~@wip
cd ..

# Run Behat tests for the backend.
echo -e "\n [RUN] Start back end tests.\n"
cd productivity/behat
./bin/behat --tags=~@wip
cd ../..
