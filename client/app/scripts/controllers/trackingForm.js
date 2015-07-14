'use strict';

/**
 * @ngdoc function
 * @name clientApp.controller:CompaniesCtrl
 * @description
 * # CompaniesCtrl
 * Controller of the clientApp
 */
angular.module('clientApp')
  .controller('TrackingFormCtrl', function ($scope, $stateParams, $state, $log, projects, Tracking, tracking, Config, Preferences) {

    $scope.tracking = tracking;
    if (Config.debug) {
      console.log(tracking);
    }

    // Get the state of the calendar from the user's preferences, Using
    // JSON.parse because local-storage stores variables only as strings.
    $scope.calendar = angular.isDefined(Preferences.getCalendarPreference()) ? JSON.parse(Preferences.getCalendarPreference()) : false;
    $scope.calendarState = $scope.calendar ? 'Hide' : 'Show';

    /**
     * Toggles calendar.
     *
     * Shows/Hides the calender triggered by clicking on the "Show calendar"
     * button changes the text in the button as well, The calendar get it's
     * state from the preferences service, this way we can maintain it's state
     * through out the session.
     */
    $scope.toggleCalendar = function() {
      $scope.calendar = !$scope.calendar;
      Preferences.setCalendarPreference($scope.calendar);
      $scope.calendarState = $scope.calendar ? 'Hide' : 'Show';
    };

    // Prepare header for table.
    var endDay = new Date($stateParams.year, $stateParams.month, 0).getDate();
    $scope.days = [];
    for (var i = 1; i <= endDay; i++) {
      $scope.days.push(i);
    }
    var monthNames = [ "January", "February", "March", "April", "May", "June",
      "July", "August", "September", "October", "November", "December" ];


    $scope.month = $stateParams.month;
    $scope.monthString = monthNames[$scope.month-1];
    $scope.year = $stateParams.year;
    $scope.day = $stateParams.day;
    $scope.employee = $stateParams.username;

    $scope.nextMonth = $scope.month + 1;
    $scope.nextYear =  $scope.year;
    $scope.prevMonth = $scope.month - 1;
    $scope.prevYear =  $scope.year;

    if ($scope.month == 12) {
      $scope.nextMonth = 1;
      $scope.nextYear =  $scope.year + 1;
    }
    if ($scope.month == 1) {
      $scope.prevMonth = 12;
      $scope.prevYear =  $scope.year - 1;
    }

    // Disable submit button.
    $scope.creating = false;
    // Initialize values.


    $scope.projects = projects;
    $scope.message = '';
    $scope.messageClass = 'alert-success';


    // Prepare form for create new.
    if ($stateParams.id == 'new' || $stateParams.id == 'undefined') {
      $scope.title = 'What have you done on the '  + $stateParams.day + '/' + $stateParams.month + '/' +  $stateParams.year + ' ?';
      $scope.data = {};
      $scope.data.period = 'hour';
      $scope.data.type = 'regular';
      $scope.data.employee = $stateParams.username;
    }
    else {
      $scope.title = 'Your report for the '  + $stateParams.day + '/' + $stateParams.month + '/' +  $stateParams.year + ' ?';
      // Fill with existing nid.
      angular.forEach(tracking[$stateParams.day], function(value, key) {
        if (value.id == $stateParams.id) {
          $scope.data = value;
        }
      });
    }

    /* Configuration of the ui-calendar. */
    $scope.uiConfig = {
      calendar:{
        height: 400,
        editable: false,
        day: $scope.day,
        month: $scope.month - 1,
        year: $scope.year,
        header:{
          left: '',
          center: '',
          right: ''
        }
      }
    };

    /* Extract all tracking items to events for the ui-calendar */
    $scope.calendarEventTypes = {
      regular : {
        className: 'regular-event',
        events: []
      },
      weekend : {
        className: 'weekend-event',
        events: []
      },
      miluim : {
        className: 'miluim-event',
        events: []
      },
      vacation : {
        className: 'vacation-event',
        events: []
      },
      sick : {
        className: 'sick-event',
        events: []
      },
      empty : {
        className: 'empty-event',
        events: []
      },
      convention : {
        className: 'convention-event',
        events: []
      },
      funday : {
        className: 'funday-event',
        events: []
      },
      special : {
        className: 'special-event',
        events: []
      },
      global : {
        className: 'global-event',
        events: []
      }
    };

    angular.forEach(tracking, function(events) {
      angular.forEach(events, function(event) {
        // Check if object to avoid considering "sum" array as an event.
        if(angular.isObject(event)) {
          if (event.type == 'regular') {
            var hours = parseFloat(event.length);
            var suffix = hours > 1 ? ' Hours' : ' Hour';
            $scope.calendarEventTypes.regular.events.push({
              title: event.projectName + ' - ' + hours + suffix,
              start: new Date(event.date*1000),
              description: hours,
              allDay: true,
              type: event.type,
              url: '#/tracking/' + $scope.employee + '/' + $scope.year + '/' + $scope.month + '/' + event.day + '/' + event.id
            });
          }
          else {
            $scope.calendarEventTypes[event.type].events.push({
              title: event.type == 'global' ? 'Global day' : event.projectName,
              start: new Date($scope.year, $scope.month - 1, event.day),
              allDay: true,
              type: event.type,
              url: event.type == 'empty' ? '#/tracking/' + $scope.employee + '/' + $scope.year + '/' + $scope.month + '/' + event.day + '/new' : ''
            });
          }
        }
      });
    });
    // Add all the events types to Calendar's events source.
    $scope.eventSources = [];
    angular.forEach($scope.calendarEventTypes, function(calendarEvent) {
      this.push(calendarEvent);
    }, $scope.eventSources);

    /* End of ui-calendar settings */

    $scope.save = function(data) {
      // Indicate we are in the middle of creation.
      $scope.creating = true;

      // Convert date to timestamp,
      // Need to add the hour to make a more accurate events.
      var date = $stateParams.year + '.' + $stateParams.month + '.' +  $stateParams.day + ' 12:00:00';
      data.date = new Date(date).getTime() / 1000;

      if (Config.debug) {
        console.log(data);
      }

      // Convert date to timestamp.
      Tracking.save(data).then(function(newData) {
        $scope.creating = false;

        if (newData.error) {
          $scope.messageClass = 'alert-danger';
          $scope.message = newData.title;
          return;
        }
        // Success.
        $scope.messageClass = 'alert-success';
        $scope.message = 'Saved successfully.';

        // The tracking entity was un-published successfully,
        // need to reload.
        if (newData.data[0].status == 0) {
          // Redirect to item to update.
          $state.go('dashboard.tracking-form', {
              username: $stateParams.username,
              year: $stateParams.year,
              month: $stateParams.month,
              day: $stateParams.day,
              id: 'new'
            },
            {
              reload: true
            });
          return;
        }

        var trackingItem = newData.data[0];
        // Push new value.
        if (trackingItem.new) {
          tracking[trackingItem.day].push(trackingItem);
          $stateParams.id = trackingItem.id;
        }

        // Redirect to item to update.
        $state.go('dashboard.tracking-form', {
            username: trackingItem.employee,
            year: $stateParams.year,
            month: $stateParams.month,
            day: trackingItem.day,
            id: trackingItem.id
          },
          {
            reload: true
          });
      });
    };

    /**
     * Determine if the current user is the owner of the entity (Time tracking).
     *
     * @param data
     *  The data of the entity.
     *
     * @returns {*|boolean}
     */
    $scope.owner = function(data) {
      return data && data.hasOwnProperty('id') && $stateParams.username == data.employee;
    };

    /**
     * Remove entity (Time tracking) from the work log by un-publishing it.
     * Sets status to 0 and call the save function.
     *
     * @param data
     *  The data of the entity.
     */
    $scope.remove = function(data) {
      if ($stateParams.username != data.employee) {
        return false;
      }
      data.status = 0;

      $scope.save(data);
    };

    /**
     * Create a default description when a project is selected;
     * Fetch Github PRs from the current day and list them in the description.
     */
    $scope.updateDescription = function() {
      Tracking.getGithubPRs($scope.data.projectID, $scope.employee, $scope.day, $scope.month, $scope.year)
        .success(function(data) {
          $scope.data.description = '';
          angular.forEach(data.data, function(pr) {
            $scope.data.description += '#' + pr.issue + ': ' + pr.label + '\n';
          });
        });
    }
  });



