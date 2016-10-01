#!/usr/bin/env bash


################################################################################
#
# This script will sync Danel profile with the platform profile.
#
#
################################################################################

WORKING_DIR="/Users/brice/Sites/productivity/productivity"
WORKING_DIR_app="/Users/brice/Sites/productivity/www/app/dist"
PLATFORM_DIR="/Users/brice/Sites/productivity_pantheon"
ALIAS="@productivity.dev"

# Danel
rsync -azvr --delete-after --exclude=".git" --exclude=".idea" profiles/ $PLATFORM_DIR
rsync -azvr --delete-after --exclude=".git" --exclude=".idea" $WORKING_DIR_app app/

cd $PLATFORM_DIR
git pull
git checkout master
git add .
git commit -am"Update site"
git push
drush $ALIAS uli
cd $WORKING_DIR
