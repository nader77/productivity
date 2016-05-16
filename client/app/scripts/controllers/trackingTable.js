'use strict';

/**
 * @ngdoc function
 * @name clientApp.controller:CompaniesCtrl
 * @description
 * # CompaniesCtrl
 * Controller of the clientApp
 */
angular.module('clientApp')
  .controller('TrackingTableCtrl', function ($scope, tracking, trackingProject, $stateParams, $log, Config) {
    var endDay = new Date($stateParams.year, $stateParams.month, 0).getDate();
    var days = [];
    for (var i = 1; i <= endDay; i++) {
      days.push(i);
    }
    $scope.trackingProject = trackingProject;
    $scope.employeeRows = tracking;
    
    // Calculate the total sum per employee for all projects.
    angular.forEach($scope.employeeRows, function (employeeRow, employeeName){

      // Initialize a totalSum var.
      var totalSum = 0;

      // Check if employeeRow.sum is object to know that is not empty
      // (if empty the property will be an empty array and not an object).
      if (angular.isObject(employeeRow.sum)) {

        angular.forEach(employeeRow.sum, function(projectSum){
            totalSum += projectSum;
        });

        // Set totalSum property to the employeeRows.
        $scope.employeeRows[employeeName]['totalSum'] = totalSum;
      }
    });

    $scope.year = $stateParams.year;
    $scope.month = $stateParams.month;

    $scope.nextMonth = $scope.month + 1;
    $scope.nextYear =  $scope.year;
    $scope.prevMonth = $scope.month - 1;
    $scope.prevYear =  $scope.year;

    if ($scope.month === 12) {
      $scope.nextMonth = 1;
      $scope.nextYear =  $scope.year + 1;
    }
    if ($scope.month === 1) {
      $scope.prevMonth = 12;
      $scope.prevYear =  $scope.year - 1;
    }


    $scope.days = days;

    if (Config.debug) {
      console.log($scope.employeeRows);
    }

  });
