[![Build Status](https://magnum.travis-ci.com/Gizra/productivity.svg?token=p2M1EeCrd3dY32WxWj3X&branch=master)](https://magnum.travis-ci.com/Gizra/productivity)

# Productivity.io
Productity is Gizra's ERP/Project management system, and is part of The Gizra Way
methodology, the system manages the following areas:

## Features

* Time tracking - Part of the Gizra Way is to time box every development task,
and to monitor per issue time spent, this is a very hard task and therefore we
created a flow to make this easy for developers to recored there work.
The system is tightly coupled with Github, since we use Github issue queue for
all project, the system knows to pull all your work from Github and display it
in the time tracking page, leaving the developer to just type the amount of time
spent on each task.
![https://raw.githubusercontent.com/Gizra/productivity/master/assets/images/Gizra_-_Tracking_form.png]
(https://raw.githubusercontent.com/Gizra/productivity/master/assets/images/Gizra_-_Tracking_form.png)

Time Boxing - Each task is estimated and the time is recorded on the issue Title
using a suffix in square brackets ```[2h]```
![https://raw.github.com/Gizra/productivity/master/assets/images/Block_access.png]
(https://raw.github.com/Gizra/productivity/master/assets/images/Block_access.png)

* Project overview - On this page you can see the project information such as
the total hours spent, contracts, extra time, budget and payments overview.

* Payment - Track customer payment according to the milestones and term payment.

* Alert and monitoring,the system will send notification when a project scope
reach 25%, 50%, 75% and 100%, when a developer did not record his time, and more.


## Installation

**Warning:** you need to setup [Drush](https://github.com/drush-ops/drush)
first or the installation and update scripts will not work.

Clone the project from [GitHub](https://github.com/Gizra/productivity.io).

#### Create config file

Copy the example configuration file to config.sh:

	$ cp default.config.sh config.sh

Edit the configuration file, fill in the blanks.


#### Run the install script

Run the install script from within the root of the repository:

	$ ./install

You can login automatically when the installation is done. Add the -l argument
when you run the install script.

  $ ./install -l


#### Configure web server

Create a vhost for your webserver, point it to the `REPOSITORY/ROOT/www` folder.
(Restart/reload your webserver).

Add the local domain to your ```/etc/hosts``` file.

Open the URL in your favorite browser.



## Reinstall

You can Reinstall the platform any type by running the install script.

	$ ./install


#### The install script will perform following steps:

1. Delete the /www folder.
2. Recreate the /www folder.
3. Download and extract all contrib modules, themes & libraries to the proper
   subfolders of the profile.
4. Download and extract Drupal 7 core in the /www folder
5. Create an empty sites/default/files directory
6. Makes a symlink within the /www/profiles directory to the /productivity
   directory.
7. Run the Drupal installer (Drush) using the Productivity profile.

#### Warning!

* The install script will not preserve the data located in the
  sites/default/files directory.
* The install script will clear the database during the installation.

**You need to take backups before you run the install script!**



## Upgrade

It is also possible to upgrade Drupal core and contributed modules and themes
without destroying the data in tha database and the sites/default directory.

Run the upgrade script:

	$ ./upgrade

You can login automatically when the upgrade is finished. Add the -l argument
when you run the upgrade script.

  $ ./upgrade -l


#### The upgrade script will perform following steps:

1. Create a backup of the sites/default folder.
2. Delete the /www folder.
3. Recreate the /www folder.
4. Download and extract all contrib modules, themes & libraries to the proper
   subfolders of the profile.
5. Download and extract Drupal 7 core in the /www folder.
6. Makes a symlink within the /www/profiles directory to the
   /productivity 7. directory.
7. Restore the backup of the sites/default folder.
