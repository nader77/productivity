[![Build Status](https://travis-ci.org/Gizra/productivity.svg)](https://travis-ci.org/Gizra/productivity)


# Gizra Productivity 
Productity is Gizra's ERP/Project management system, and is part of The Gizra Way
methodology, the system manages the following areas:

## Features

### Time tracking
Part of the Gizra Way is to time box every development task,
and to monitor per issue time spent, this is a very hard task and therefore we
created a flow to make this easy for developers to recored there work.
The system is tightly coupled with Github, since we use Github issue queue for
all project, the system knows to pull all your work from Github and display it
in the time tracking page, leaving the developer to just type the amount of time
spent on each task.
![https://raw.githubusercontent.com/Gizra/productivity/master/assets/images/Gizra_-_Tracking_form.png]
(https://raw.githubusercontent.com/Gizra/productivity/master/assets/images/Gizra_-_Tracking_form.png)

### Time Boxing
Each task is estimated and the time is recorded on the issue Title using a suffix in square brackets.
![https://raw.github.com/Gizra/productivity/master/assets/images/Block_access.png]
(https://raw.github.com/Gizra/productivity/master/assets/images/Block_access.png)

### Project overview
On this page you can see the project information such as the total hours spent, contracts, extra time, budget and payments overview.

### Payment
Track customer payment according to the milestones and term payment.

### Alerts and monitoring
Productivity sends notification when a project scope reach 25%, 50%, 75% and 100%, when a developer did not record his time, and more.


### GitHub/Normal login on the application.
There's two options for the login page:

 1. The normal username and password page.
 2. A GitHub connect button.
 
To toggle between the two options on the front-end you can edit the `config.json` file in the `client` directory,
Setting `githubClientId` to the `Client ID` provided by the application in GitHub will enable the GitHub connection button,
Setting `githubClientId` to `FALSE` will enable the normal login page.

When choosing the GitHub connect login, You have to provide the application's `Client ID` and `Client secret` to the backend as well which should be done through the `config.sh` (`default.config.sh` on first install) file in the `ROOT` directory in the `post_install` function.
